/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief IWDG������ӿ�
 * \internal
 * \par Modification history
 * - 1.00 19-3-7  adw, first implementation
 * \endinternal
 */

#include "am_usb.h"
#include "am_int.h"
#include "am_zmf159_usbd.h"
#include "am_usbd_ch9.h"
#include "amhw_zmf159_usb.h"
#include "amhw_zmf159_rcc.h"


static uint8_t __rxusbbufodd[16] = {0};
static uint8_t __txusbbufodd[16] = {0};

static uint8_t __epindatanum[16] = {0};

static uint8_t __set_addr = 0;
/**
 * \brief ͨ��wValue��ֵѰ��ָ����������
 *
 * \retval �ɹ�����������ָ�룬ʧ�ܷ���NULL
 *
 * \note �������������¼�����������ͨ���˷����
 */
static uint8_t * __find_desc_by_wValue1 (const am_zmf159_usbd_dev_t *p_dev,
                                         uint16_t                 w_value)
{
    int i = 0;

    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
        if (w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
            return (uint8_t *)(p_dev->p_info->p_devinfo->p_descriptor[i].p_desc);
        }
    }
    return NULL;
}

static am_usb_status_t __ep_init(am_zmf159_usbd_dev_t      *p_dev,
                                 am_usbd_endpoint_init_t   *epinit,
                                 amhw_zmf159_usb_bdt_t     *p_usb_bdt,
                                 uint32_t                   databufadd)
{
    uint8_t i = 0;
    uint16_t max_packet_size = epinit->max_packet_size;
    uint8_t  endpoint = (epinit->endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK);

    for (i = 0; i < p_dev->max_ep_num; i++) {
        /* �˵��������б���ָ��������˵� */
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE &&
            p_dev->device.endpoint_info[i].ep_address == epinit->endpoint_address) {
            break;
        }
    }

    if (i == p_dev->max_ep_num)
        return AM_USB_STATUS_INVALID_REQUEST;

    if (endpoint >= p_dev->max_ep_num)
        return AM_USB_STATUS_INVALID_PARAMETER;
    if (epinit->transfer_type > AM_USB_ENDPOINT_INTERRUPT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    /* ���ö˵��ܴ��������ֽڸ��� */
    if (max_packet_size > AM_USBD_MAX_EP_DATA_CNT)
        max_packet_size = AM_USBD_MAX_EP_DATA_CNT;

//    am_kprintf("reset init ep: %x \r\n", endpoint);

    p_usb_bdt->rx_buf[0].format = 0;
    p_usb_bdt->rx_buf[0].adress = databufadd;
    p_usb_bdt->rx_buf[0].format |= 0x40 << 16;   //����64byte
    p_usb_bdt->rx_buf[0].format |= 1<<7;

    p_usb_bdt->rx_buf[1].format = 0;
    p_usb_bdt->rx_buf[1].format |= 0x40 << 16;   //����64byte
    p_usb_bdt->rx_buf[1].adress = p_usb_bdt->rx_buf[0].adress + 0x40;
    p_usb_bdt->rx_buf[1].format |= 1<<6;
    p_usb_bdt->rx_buf[1].format |= 1<<7;

    p_usb_bdt->tx_buf[0].format = 0x00;
    p_usb_bdt->tx_buf[0].adress = p_usb_bdt->rx_buf[0].adress + 0x80;

    p_usb_bdt->tx_buf[1].format = 0x00;
    p_usb_bdt->tx_buf[1].adress = p_usb_bdt->rx_buf[0].adress + 0xC0;

    for(i = 0; i < 64; i++)
    {
        *(uint8_t*)(p_usb_bdt->tx_buf[0].adress + i) = 0;
        *(uint8_t*)(p_usb_bdt->tx_buf[1].adress + i) = 0;
        *(uint8_t*)(p_usb_bdt->rx_buf[0].adress + i) = 0;
        *(uint8_t*)(p_usb_bdt->rx_buf[1].adress + i) = 0;
    }

    // ����ǿ��ƶ˵�, ֱ������Ϊ0x0d, ����˵�����Ϊ0x05,�������Ϊ0x09
    // ������������ң���ʹ��
    if (endpoint == 0) {
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x0d);
    } else if ((epinit->endpoint_address >> 7) & 0x01) { // ������䷽��Ϊ����Ļ�
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x05);
    } else {
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x09);
    }

    p_dev->device.endpoint_info[endpoint].stalled = 0;
    p_dev->device.endpoint_info[endpoint].max_packet_size = max_packet_size;
    p_dev->device.endpoint_info[endpoint].transfer_type = epinit->transfer_type;

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ĳ���˵�ȥ��ʼ��
 *
 *  \param[in] p_dev       : USB�豸
 *  \param[in] endpoint    : ָ���Ķ˵�
 */
static am_usb_status_t __ep_deinit (am_zmf159_usbd_dev_t *p_dev,
                                    uint8_t               endpoint)
{
    endpoint &= AM_USBD_ENDPOINT_NUMBER_MASK;

    amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x02);  /* ���ܶ˵� */

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵�����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ
 */
static am_usb_status_t __ep_stall (am_zmf159_usbd_dev_t *p_dev,
                                   uint8_t               endpoint_addr)
{
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;

    p_dev->device.endpoint_info[endpoint].stalled = 1;    /* ����������־ */

    amhw_zmf159_ep_halt_set(ZMF159_USB, endpoint, 1);

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ���ö˵㲻����
 *
 * \param[in] p_dev         : USB�豸
 * \param[in] endpoint_addr : �˵��ַ  D7�� 1��USB_IN  0��USB_OUT
 */
static am_usb_status_t __ep_unstall (am_zmf159_usbd_dev_t *p_dev,
                                     uint8_t               endpoint_addr)
{
    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;

    p_dev->device.endpoint_info[endpoint].stalled = 0;

    __rxusbbufodd[endpoint] = 0;
    __txusbbufodd[endpoint] = 0;
    __epindatanum[endpoint] = 0;
    amhw_zmf159_ep_halt_set(ZMF159_USB, endpoint, 0);

    return AM_USB_STATUS_SUCCESS;
}

static void  __usb_device_reset(am_usbd_handle_t handle)
{
    uint8_t i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_zmf159_usbd_dev_t   *p_dev = (am_zmf159_usbd_dev_t *)handle;

    p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;

    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

    for(i = 0; i < p_dev->max_ep_num; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
            endpoint.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
            endpoint.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
            endpoint.transfer_type = p_dev->device.endpoint_info[i].transfer_type;
            __ep_init(p_dev, &endpoint, p_dev->p_usb_bdt + i, (uint32_t)(p_dev->p_usb_bdt) + 0x200 + 0x100 * i);
        }
    }

    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    __txusbbufodd[0] = 0;
    amhw_zmf159_addr_set(ZMF159_USB, 0);
//    p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
}

static am_usb_status_t __usb_device_init(am_usbd_handle_t handle)
{
    int i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_zmf159_usbd_dev_t   *p_dev = (am_zmf159_usbd_dev_t *)handle;

    amhw_zmf159_bdt_page_set(ZMF159_USB, 0x20007000);
    amhw_zmf159_addr_set(ZMF159_USB, 0);
    p_dev->device.device_address = 0;

    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

    /* ���SETUP���� */
    p_dev->device.setup_data.bm_request_type = 0;
    p_dev->device.setup_data.b_request       = 0;
    p_dev->device.setup_data.w_value         = 0;
    p_dev->device.setup_data.w_index         = 0;
    p_dev->device.setup_data.w_length        = 0;

    for(i = 0; i < p_dev->max_ep_num; i++) {
        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
            endpoint.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
            endpoint.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
            endpoint.transfer_type = p_dev->device.endpoint_info[i].transfer_type;
            __ep_init(p_dev, &endpoint, p_dev->p_usb_bdt + i, (uint32_t)(p_dev->p_usb_bdt) + 0x200 + 0x100 * i);
        }
    }
    __txusbbufodd[0] = 0;

    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);

    amhw_zmf159_usb_int_enable(ZMF159_USB,
                               ZMF159_USB_INT_STAT_RST | ZMF159_USB_INT_STAT_TOK_DNE);

    // ���ж�
//    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_RST);
//    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_TOK_DNE);


    return AM_USB_STATUS_SUCCESS;
}

static am_usb_status_t __usb_device_deinit(am_usbd_handle_t handle)
{
    am_zmf159_usbd_dev_t   *p_dev = (am_zmf159_usbd_dev_t *)handle;
    uint8_t i = 0;

    // �����ж�
    amhw_zmf159_usb_int_disable(ZMF159_USB, 0x00);

    // ���õ�ַΪ0
    amhw_zmf159_addr_set(ZMF159_USB, 0);
    p_dev->device.device_address = 0;

    // ���ܶ˵�
    for (i = 0; i < p_dev->max_ep_num; i++) {
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, i, 0x02);
    }
    if (p_dev->p_info->pfn_plfm_deinit)
        p_dev->p_info->pfn_plfm_deinit();

    p_dev->p_usb_bdt = NULL;

    return AM_USB_STATUS_SUCCESS;
}

static am_usb_status_t __usb_device_send(am_usbd_handle_t handle, uint8_t ep, uint8_t *p_buf, uint32_t len)
{
    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;

    uint32_t i = 0;
    uint8_t *pBuf = NULL;

    am_kprintf("send buf : %x %x %x... len : %d\r\n", p_buf[0], p_buf[1], p_buf[2], len);

    pBuf = (uint8_t*)((p_dev->p_usb_bdt + ep)->tx_buf[__txusbbufodd[ep]].adress) ;

    (p_dev->p_usb_bdt + ep)->tx_buf[__txusbbufodd[ep]].format &= 0x00ff00;

    for (i = 0; i < len; i++) {
        pBuf[i] = *p_buf;
        p_buf++;
    }

    (p_dev->p_usb_bdt + ep)->tx_buf[__txusbbufodd[ep]].format |= (len << 16) | (__epindatanum[ep] << 6);
    __epindatanum[ep] = !__epindatanum[ep];

    // �������� OWN
    (p_dev->p_usb_bdt+ep)->tx_buf[__txusbbufodd[ep]].format |= 1 << 7;
    __txusbbufodd[ep] = !__txusbbufodd[ep] ;

    return AM_USB_STATUS_SUCCESS;
}

static am_usb_status_t __usb_device_recv(am_usbd_handle_t handle, uint8_t ep, uint8_t *p_buf, uint32_t len)
{
    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint32_t i    = 0;
    uint8_t *pBuf = NULL;
    uint8_t avali_data_cnt = 0;     /* fifo����Ч���ݸ��� */

    // ��ȡ��ַ
    pBuf = (uint8_t*)((p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].adress) ;

    // ��Ч��������
    avali_data_cnt = (((p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format) >> 16) & 0x3ff;
    p_dev->device.endpoint_info[ep].val_length = avali_data_cnt;

    if (avali_data_cnt == 0)
        return AM_USB_STATUS_ERROR;
    else if (avali_data_cnt < len)
        error = AM_USB_STATUS_ALLOC_FAIL;
    else if (avali_data_cnt == len)
        error = AM_USB_STATUS_SUCCESS;
    else if (avali_data_cnt > len) {
        error = AM_USB_STATUS_SUCCESS;
        avali_data_cnt = len;
    }

    for (i = 0; i < avali_data_cnt; i++) {
       *p_buf = pBuf[i];
        p_buf++;
    }


    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format &= 0x00ff00;//�������,���stall
    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format |= (64 << 16);//�����������ֽ�
    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format |= 1 << 7;

    return error;
}


static am_usb_status_t __usb_device_cancel(am_usbd_handle_t handle, uint8_t ep)
{
    // todo
    return AM_USB_STATUS_ERROR;
}


static am_usb_status_t __usb_device_control(am_usbd_handle_t handle, am_usbd_control_type_t type, void *param)
{
    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;
    am_usb_status_t error = AM_USB_STATUS_ERROR;
    uint8_t *temp8;
    uint8_t temp;
    am_usbd_ep_status_t *endpointStatus = NULL;
    uint8_t endpoint = 0;

    if (!handle)
        return AM_USB_STATUS_INVALID_HANDLE;

    switch ((int)type) {
        case AM_USBD_CONTROL_RUN:
            amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_STOP:
            amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_EN);
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_ENDPOINT_INIT:     /* ��ĳ���˵��ʼ�� */
            if (param) {
                // ��ȡ�˵�
                temp = (((am_usbd_endpoint_init_t *)param)->endpoint_address & 0x0f);
                error = __ep_init(p_dev,
                                 (am_usbd_endpoint_init_t *)param,
                                 p_dev->p_usb_bdt + temp,
                                 (uint32_t)p_dev->p_usb_bdt + 0x200 + 0x100 * temp);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_DEINIT:   /* ��ĳ���˵�ȥ��ʼ�� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __ep_deinit(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_STALL:    /* ���ƶ˵����� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __ep_stall(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_ENDPOINT_UNSTALL:  /* ���ƶ˵㲻���� */
            if (param) {
                temp8 = (uint8_t *)param;
                error = __ep_unstall(p_dev, *temp8);
            }
            break;

        case AM_USBD_CONTROL_GET_DEVICE_STATUS: /* ��ȡ�豸״̬ */

            break;

        case AM_USBD_CONTROL_GET_ENDPOINT_STATUS:   /* ͨ���˵��ַ��ȡ�˵�״̬ */
            if (param) {
                endpointStatus = (am_usbd_ep_status_t *)param;

                endpoint = (endpointStatus->endpoint_address) & AM_USBD_ENDPOINT_NUMBER_MASK;

                if (endpoint < p_dev->max_ep_num) {
                    endpointStatus->endpoint_status = p_dev->device.endpoint_info[endpoint].stalled;
                    error = AM_USB_STATUS_SUCCESS;
                } else {
                    error = AM_USB_STATUS_INVALID_PARAMETER;
                }
            }
            break;

        case AM_USBD_CONTROL_SET_DEVICE_ADDRESS:    /* ����USB�豸��ַ */
            if (param) {
            	__set_addr = 1;
//                temp8 = (uint8_t *)param;
//                amhw_zmf159_addr_set(ZMF159_USB, *temp8);
                error = AM_USB_STATUS_SUCCESS;
            }
            break;

        case AM_USBD_CONTROL_GET_SYNCH_FRAME:
            break;

        case AM_USBD_CONTROL_RESUME:
            amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_RESUME);

            break;

            /* ����Ĭ��״̬ */
        case AM_USBD_CONTROL_SET_DEFAULT_STATUS:
            error = AM_USB_STATUS_SUCCESS;
            break;

        case AM_USBD_CONTROL_GET_SPEED:
            if (param) {
                temp8 = (uint8_t *)param;
                *temp8 = AM_USB_SPEED_FULL;
                error = AM_USB_STATUS_SUCCESS;
            }
            break;

        case AM_USBD_CONTROL_GET_OTG_STATUS:
            break;
        case AM_USBD_CONTROL_SET_OTG_STATUS:
            break;
        case AM_USBD_CONTROL_SET_TEST_MODE:
            break;
        default:
            break;
    }

    return error;
}

static const am_usbd_interface_t __g_usb_device_interface = {
    __usb_device_init,
    __usb_device_deinit,
    __usb_device_send,
    __usb_device_recv,
    __usb_device_cancel,
    __usb_device_control
};

// ���Ϳհ�
//static void __usbd_send0_package(am_zmf159_usbd_dev_t *p_dev)
//{
//    switch (p_dev->device.running_ctrl_state) {
//    case AM_USBD_CTRL_SETUP:
//         p_dev->device.running_ctrl_state = AM_USBD_CTRL_IN;
//         break;
//
//    case AM_USBD_CTRL_IN:
//        __epindatanum[0] = 1;
//        __usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);
//        p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
//        break;
//
//    default:
//        p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
//    }
//}


/**
 * \brief ������
 */
static void __ctrl_deal_handle (am_zmf159_usbd_dev_t *p_dev)
{
    if((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_TYPE_MASK) ==    // ��׼�豸����
            AM_USB_REQ_TYPE_TYPE_STANDARD) {
        if(p_dev->device.setup_data.b_request <= AM_USB_REQ_STANDARD_SYNCH_FRAME) {
            (p_dev->device.pfn_std_request[p_dev->device.setup_data.b_request])(&(p_dev->device));
        }

    // �豸������ ���� ���Ϳհ�
    } else if ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK)
             == AM_USB_REQ_TYPE_DIR_IN) {
    	__usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);

        // ���豸����
    } else if ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_TYPE_MASK)
             == AM_USB_REQ_TYPE_TYPE_CLASS) {

        if(p_dev->device.class_req.pfn_class != NULL) {
            (p_dev->device.class_req.pfn_class)(p_dev->device.class_req.p_arg, p_dev->device.setup_data.b_request);
            p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
        }

    } else if ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_TYPE_MASK)
            == AM_USB_REQ_TYPE_TYPE_VENDOR) {
        if(p_dev->device.vendor_req.pfn_vendor != NULL) {
            (p_dev->device.vendor_req.pfn_vendor)(p_dev->device.vendor_req.p_arg, p_dev->device.setup_data.b_request);
            p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
        }
    }
}



static void __usb_in_process(am_zmf159_usbd_dev_t *p_dev)
{
    if ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) ==
                                                 AM_USB_REQ_TYPE_DIR_IN) {

       p_dev->device.running_ctrl_state = AM_USBD_CTRL_IN;
        __ctrl_deal_handle(p_dev);
    } else {
    	__usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);
    }
//    uint8_t istd_req = ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_TYPE_MASK)
//                         == AM_USB_REQ_TYPE_TYPE_STANDARD);
//
//    // ����Ǳ�׼�豸��������õ�ַ����
//    if ((p_dev->device.setup_data.b_request == AM_USB_REQ_STANDARD_SET_ADDRESS) &&
//        istd_req) {
//        (p_dev->device.pfn_std_request[AM_USB_REQ_STANDARD_SET_ADDRESS])(&(p_dev->device));
//    }
//    __usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);

}




static void __setup0_process(am_zmf159_usbd_dev_t *p_dev)
{
//    uint8_t *pBuf ;
    // ��ȡsetup���ݰ�
  if (p_dev->device.running_ctrl_state == AM_USBD_CTRL_IDLE) {
       //��ȡsetup���ݰ�
      __usb_device_recv(p_dev, 0, (uint8_t *)&(p_dev->device.setup_data), 8);
      p_dev->device.running_ctrl_state = AM_USBD_CTRL_SETUP;

      am_kprintf("setup_data: %x %x %x %x %x\r\n",
              p_dev->device.setup_data.bm_request_type,
              p_dev->device.setup_data.b_request,
              p_dev->device.setup_data.w_value,
              p_dev->device.setup_data.w_index,
              p_dev->device.setup_data.w_length);
  }

  if ((p_dev->device.setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) ==
                                               AM_USB_REQ_TYPE_DIR_IN) {
      p_dev->device.running_ctrl_state = AM_USBD_CTRL_IN;
  }

  /* �ж��������͵����� */
  switch ((p_dev->device.setup_data.bm_request_type >> 5) & 0x03) {

      /* ��׼�������� */
      case 0:
          // �Ϸ������ж�
          if (p_dev->device.setup_data.b_request <= AM_USB_REQ_STANDARD_SYNCH_FRAME) {
              (p_dev->device.pfn_std_request[p_dev->device.setup_data.b_request])(&(p_dev->device));
          }

          break;

      /* ������ */
      case 1:
          if(p_dev->device.class_req.pfn_class != NULL) {
              (p_dev->device.class_req.pfn_class)(p_dev->device.class_req.p_arg, p_dev->device.setup_data.b_request);
          }
          p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
          break;

      /* �������� */
      case 2:
          if(p_dev->device.vendor_req.pfn_vendor != NULL) {
              (p_dev->device.vendor_req.pfn_vendor)(p_dev->device.vendor_req.p_arg, p_dev->device.setup_data.b_request);
          }
          p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;
          break;

      default:
          break;
  }

}


static void __usbd_token_isr(am_zmf159_usbd_dev_t *p_dev)
{
    uint32_t ep_int_sta = 0,epx_int_sta = 0;  // �˵��ж�״̬
    uint32_t wepstat;                         // �˵�״̬
    uint8_t  txusbbufoddtemp = 0;
//    uint8_t  buff[32] = {0};

    wepstat = amhw_zmf159_usb_stat_get(ZMF159_USB);
    // ���USB token�ж�
    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_TOK_DNE);

    //��ȡ�ж϶˵��
    ep_int_sta = (wepstat >> 4) & 0xf;

    p_dev->int_ep = ep_int_sta;  // �����ж϶˵��

    //�˵�0 �ж�
    if (p_dev->int_ep == 0) {

        am_kprintf("ep int 0\r\n");
        // �ж��Ƿ����жϻ��ǽ����ж�
        if(((wepstat >> 3) & 0x01) == 0) {//RX ���ʹ���

          __rxusbbufodd[0] = (wepstat >> 2) & 0x1;
          epx_int_sta = p_dev->p_usb_bdt->rx_buf[__rxusbbufodd[0]].format;
        } else {                       // ���մ���
          txusbbufoddtemp = (wepstat >> 2) & 0x1;
          epx_int_sta = p_dev->p_usb_bdt->tx_buf[txusbbufoddtemp].format;
          p_dev->p_usb_bdt->tx_buf[txusbbufoddtemp].format = 0;
        }
        // ��ȡ�ж����� TOK_PID[0~3]
        epx_int_sta = (epx_int_sta >> 2) & 0xf;

        //setup
        if(epx_int_sta == 0x0D) {
            amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_TXD_SUSPEND_TOKBSY);
            __epindatanum[0] = 1;

            __setup0_process(p_dev);
        }

        if(epx_int_sta == 0x01) {//|EPn_INT_STATE_OUTNACK
            am_kprintf("STATE_OUTNACK\r\n");
            // todo out0 process
            // ���հ�
            __epindatanum[0] = 1;
            __usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);
        }

        if (epx_int_sta == 0x9) { //|EPn_INT_STATE_ACK
            am_kprintf("STATE_INACK\r\n");
            __usb_device_send(p_dev, 0, (uint8_t *)&p_dev->device.setup_data, 0);
//            __usb_in_process(p_dev);
        }

        // �жϻص�
        if (p_dev->device.endpoint_info[0].pfn_callback != NULL) {
            (p_dev->device.endpoint_info[0].pfn_callback)(p_dev->device.endpoint_info[0].p_arg);
        }

    } else if (p_dev->int_ep != 0) {

        if(((wepstat >> 3) & 0x01) == 0) {//RX

          __rxusbbufodd[ep_int_sta] = (wepstat >> 2) & 0x1;
          epx_int_sta = (p_dev->p_usb_bdt + p_dev->int_ep)->rx_buf[__rxusbbufodd[p_dev->int_ep]].format;
        } else {
          txusbbufoddtemp = (wepstat >> 2) & 0x1;
          epx_int_sta = (p_dev->p_usb_bdt + p_dev->int_ep)->rx_buf[txusbbufoddtemp].format;
          (p_dev->p_usb_bdt + p_dev->int_ep)->rx_buf[txusbbufoddtemp].format = 0;
        }
        epx_int_sta = (epx_int_sta >> 2) & 0xf; // wEpxIntSta = 0x01  out; wEpxIntSta = 0x09  in

        // �˵��жϻص�
        if (p_dev->device.endpoint_info[p_dev->int_ep].pfn_callback != NULL) {
            (p_dev->device.endpoint_info[p_dev->int_ep].pfn_callback)(p_dev->device.endpoint_info[p_dev->int_ep].p_arg);
        }

    }  // �Ƕ˵�0 �ж�

    p_dev->int_ep = 0;   // ����ж�״̬
}


// USBD �жϻص�����
static void __usbd_isr_function(void *p_arg)
{
    am_zmf159_usbd_dev_t *p_dev =(am_zmf159_usbd_dev_t *) p_arg;
    uint8_t int_status;

    if (NULL == p_dev) {
        return;
    }

    int_status = amhw_zmf159_usb_int_get(ZMF159_USB);
//    amhw_zmf159_usb_int_clear(ZMF159_USB, int_status);
    p_dev->int_stat = int_status;

//    am_kprintf("int��%x \r\n", int_status);
    // ��λ���߸�λ�ж�
    if(int_status & ZMF159_USB_INT_STAT_RST) {
    //    ���ж�״̬
        am_kprintf("reset\r\n");

        amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_RST);
        __usb_device_reset(p_dev);
    }

    if(int_status & ZMF159_USB_INT_STAT_TOK_DNE) {
        am_kprintf("token\r\n");
        __usbd_token_isr(p_dev);
    }
    p_dev->int_stat = 0;

    /*****************Test set address code*****************/
    if (__set_addr == 1) {
    	__set_addr = 0;
    	am_kprintf("__set_addr: %x\r\n", p_dev->device.setup_data.w_value);
    	amhw_zmf159_addr_set(ZMF159_USB, p_dev->device.setup_data.w_value);
    }
    /*******************************************************/
}


// �������������л�ȡ�˵�ʹ�����
static am_err_t __init_ep_info(am_zmf159_usbd_dev_t           *p_dev)
{
    uint8_t   ret    = 0;       /* ���巵��ֵ */
    uint8_t *p_tmp   = NULL;    /* ���ݻ���ָ�� */
    uint8_t  ep_num  = 0;       /* �˵�� */
    uint8_t  tmp     = 0;       /* ��ʱ����*/
    uint8_t  offset  = 0;       /* ƫ����*/
    uint8_t  len     = 0;       /* �������ܳ��� */
    am_usb_descriptor_endpoint_t  *p_desc_ep   = NULL;
    /* ��ȡ���������� */
    p_tmp = __find_desc_by_wValue1(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
    if (p_tmp == NULL)
        return AM_ERROR;
    /*���������������������������ܳ���*/
    len = (uint8_t)( ( *(p_tmp + 2) ) | ( ( *(p_tmp + 3)) >> 8 ) );
    /* �Ҷ˵�������*/
    while (tmp < len) {
        offset  = *(p_tmp);   /* �����������ֽ���,��һ��Ϊ����������*/
        p_tmp  +=   offset;   /* ��ƫ�� */
        tmp    +=   offset;
        /* ����Ƕ˵�������*/
        if ((*(p_tmp + 1) == AM_USB_DESC_TYPE_ENDPOINT) && (*p_tmp = AM_USB_DESC_LENGTH_ENDPOINT)) {
            p_desc_ep = (am_usb_descriptor_endpoint_t *)p_tmp;  // �˵�������
            // �˵��
            ep_num = p_desc_ep->b_endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK;
//            am_kprintf("inuse endpoint: %d \n", ep_num);
            p_dev->device.endpoint_info[ep_num].inuse = 1;  // ��ʾ�˵㱻ʹ��
            p_dev->device.endpoint_info[ep_num].ep_address = p_desc_ep->b_endpoint_address;
            p_dev->device.endpoint_info[ep_num].max_packet_size = (p_desc_ep->wmax_packet_size[1] << 8) |
                                                                   p_desc_ep->wmax_packet_size[0];
            p_dev->device.endpoint_info[ep_num].transfer_type = p_desc_ep->bm_attributes;
            p_dev->device.endpoint_info[ep_num].stalled = 0;
            ret++;
        }
    }
    return ret;
}

/**
 * \brief ��ʼ��USB
 *
 * \param[in] p_dev     : ָ��USB�豸
 * \param[in] p_info    : ָ��USB�豸��Ϣ
 *
 * \return USB��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_usbd_dev_t *am_zmf159_usbd_init (am_zmf159_usbd_dev_t           *p_dev,
                                    const am_zmf159_usbd_devinfo_t *p_info)
{
    int i = 0;

    if (NULL == p_dev  || NULL == p_info) {
        return NULL;
    }

    __set_addr = 0;

    p_dev->max_ep_num = AM_ZMF159MAX_EP_NUM;   // ��ֵ���˵���
    p_dev->p_usb_bdt  = NULL;                  // ��ʼ��ҳ��ַΪNULL
    p_dev->int_stat   = 0;
    p_dev->int_ep     = 0;

    p_dev->p_info     = p_info;

    p_dev->device.p_info = p_info->p_devinfo;

    p_dev->device.ctrl_handle = p_dev;
    p_dev->device.p_interface = &__g_usb_device_interface;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->device.endpoint_info[i].pfn_callback = NULL;
        p_dev->device.endpoint_info[i].p_arg = NULL;
    }

    /* ��ʼ����������*/
    p_dev->device.vendor_req.pfn_vendor = NULL;
    p_dev->device.vendor_req.p_arg      = NULL;

    p_dev->device.class_req.pfn_class   = NULL;
    p_dev->device.class_req.p_arg       = NULL;

    p_dev->device.device_address = 0;
    p_dev->device.state          = AM_USBD_STATE_DEFAULT;

    p_dev->device.setup_data.bm_request_type = 0;
    p_dev->device.setup_data.b_request = 0;
    p_dev->device.setup_data.w_value = 0;
    p_dev->device.setup_data.w_index = 0;
    p_dev->device.setup_data.w_length = 0;

    /**< \brief ���ö˵�0��Ĭ������ */
    p_dev->device.endpoint_info[0].stalled          = 0;
    p_dev->device.endpoint_info[0].ep_address       = 0;
    p_dev->device.endpoint_info[0].max_packet_size  = AM_USBD_MAX_EP_DATA_CNT;
    p_dev->device.endpoint_info[0].transfer_type    = AM_USB_ENDPOINT_CONTROL;
    p_dev->device.endpoint_info[0].inuse            = 1;
    p_dev->device.endpoint_info[0].val_length       = 0;

    for (i = 1 ;i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->device.endpoint_info[i].stalled          = 0;
        p_dev->device.endpoint_info[i].ep_address       = 0;
        p_dev->device.endpoint_info[i].max_packet_size  = 0;
        p_dev->device.endpoint_info[i].transfer_type    = 0;
        p_dev->device.endpoint_info[i].inuse            = 0;
        p_dev->device.endpoint_info[i].val_length       = 0;
    }
    if (__init_ep_info(p_dev) == -1) {
#ifdef USB_DEBUG
        am_kprintf("fail to init endpoint\n");
#endif
    }

    p_dev->device.running_ctrl_state = AM_USBD_CTRL_IDLE;

    am_usbd_ch9_std_request(&(p_dev->device));


    if (p_info->pfn_plfm_init) {
        p_info->pfn_plfm_init();
    }

    //Enable usb clock
    amhw_zmf159_rcc_ahb2_enable(AMHW_ZMF159_RCC_AHB2_USBFS);

    am_int_connect(p_info->inum, __usbd_isr_function, (void *)p_dev);
    am_int_enable(p_info->inum);

    return &(p_dev->device);
}

/**
 * \brief USB Device ȥ��ʼ��
 *
 * \param[in] p_info : ָ��USB�豸��Ϣ
 */
void am_zmf159_usbd_deinit (const am_zmf159_usbd_devinfo_t *p_info)
{
    if (p_info != NULL && p_info->pfn_plfm_deinit != NULL) {
        p_info->pfn_plfm_deinit();
    }
}

///* end of file */
