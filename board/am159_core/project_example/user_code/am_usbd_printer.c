/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB_printer ������ʵ�ֺ���
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-12  adw, first implementation.
 * \endinternal
 */

/***************************************************************************
  include
***************************************************************************/

#include "am_usb.h"
#include "am_usb_spec.h"
#include "am_usb_osa_bm.h"
#include "am_usbd_printer.h"


/* ��Ҫ����USB��ʱ��ȥ��ע�ͣ������ڴ����д�ӡ������USB�жϺ��������� ,Ƶ���Ĵ�ӡ��ʹusb��Ӧ����ʱ��ö��ʧ�� */
//#define USB_DEBUG

// ��ӡ���豸������
static void __usbd_printer_class_request(void     *p_arg,
                                         uint8_t   b_requrest)
{
    uint8_t tmp = 0;
    am_usbd_printer_t *p_dev = (am_usbd_printer_t *)(p_arg);

    AM_USB_OSA_SR_ALLOC();

    AM_USB_OSA_ENTER_CRITICAL();
    if (b_requrest > AM_USBD_PRINTER_SOFT_RESET + 1) {
        return ;
    }

    switch (b_requrest)
    {
        case AM_USBD_PRINTER_GET_DEVICE_ID:   //��ȡid
        {
            for(tmp = 0; tmp < p_dev->p_info->p_printer_id_len; ++tmp) {
                p_dev->p_printer_buff[tmp] = *(p_dev->p_info->p_printer_id + tmp);
            }

            tmp = p_dev->p_info->p_printer_id_len;
            p_dev->p_printer_buff[0] = (uint8_t)AM_USB_SHORT_GET_HIGH(tmp);
            p_dev->p_printer_buff[1] = (uint8_t)AM_USB_SHORT_GET_LOW(tmp);

            // ��������
            am_usbd_send(p_dev->p_dev, 0, p_dev->p_printer_buff, tmp);
            break;
        }

        case AM_USBD_PRINTER_GET_PORT_STATUS:  // ��ȡ�˿�״̬
        {
            tmp = p_dev->port_state;
            am_usbd_send(p_dev->p_dev, 0, &tmp, 1);
            break;
        }

        case AM_USBD_PRINTER_SOFT_RESET:      // �����λ
        {
            break;
        }

        default :
        {
            AM_USB_OSA_EXIT_CRITICAL();
            break;
        }
    }
    AM_USB_OSA_EXIT_CRITICAL();
}

static am_usb_status_t am_printer_send_cb(void *p_arg)
{
    am_usbd_printer_t *p_prt = (am_usbd_printer_t *)p_arg;

    if(p_prt->s_funcs.pfn_send_cb != NULL) {
        (p_prt->s_funcs.pfn_send_cb)(p_prt->s_funcs.p_send_arg);
    }

    return AM_USB_STATUS_SUCCESS;
}

static am_usb_status_t am_printer_recv_cb(void *p_arg)
{
    am_usbd_printer_t *p_prt = (am_usbd_printer_t *)p_arg;

    if (p_arg == NULL) {
        return AM_USB_STATUS_ERROR;
    }

    am_usbd_recv(p_prt->p_dev,
                 p_prt->endpoint.endpoint_out,
                 p_prt->p_printer_buff,
                 p_prt->p_dev->endpoint_info[p_prt->endpoint.endpoint_out].max_packet_size);

    /* ����Ч���ݳ��ȵĺ�һλ��Ϊ'\0'����ʾ���ݽ���λ�� */
    p_prt->p_printer_buff[p_prt->p_dev->endpoint_info[p_prt->endpoint.endpoint_out].val_length] = '\0';

    if (p_prt->r_funcs.pfn_recv_cb != NULL) {
        p_prt->r_funcs.pfn_recv_cb(p_prt->r_funcs.p_recv_arg,
                                 p_prt->p_printer_buff,
                                 p_prt->p_dev->endpoint_info[p_prt->endpoint.endpoint_out].val_length);
    }

    return AM_USB_STATUS_SUCCESS;
}


am_usb_status_t am_usbd_printer_send(am_usbd_printer_handle handle, uint8_t ep, uint8_t *p_buff, uint32_t length)
{
    if (handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }
    //am_kprintf("%d ", ep);
    return am_usbd_send(handle->p_dev, ep, p_buff, length);
}

am_usb_status_t am_usbd_printer_recv_request_callback(am_usbd_printer_handle p_dev,
                                                      am_printer_recv_cb_t   pfn_cb,
                                                      void                  *p_arg)
{
    if (p_dev == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    p_dev->r_funcs.pfn_recv_cb = pfn_cb;
    p_dev->r_funcs.p_recv_arg  = p_arg;

    return AM_USB_STATUS_SUCCESS;
}

// ��ӡ���˵㷢�������ж�����
am_usb_status_t am_usbd_printer_send_request_callback(am_usbd_printer_handle p_dev,
                                                      am_printer_send_cb_t   pfn_cb,
                                                      void                  *p_arg)
{
    if (p_dev == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    p_dev->s_funcs.pfn_send_cb = pfn_cb;
    p_dev->s_funcs.p_send_arg  = p_arg;

    return AM_USB_STATUS_SUCCESS;
}

// ��ӡ���˵㷢�������ж�����
am_usb_status_t am_usbd_printer_vendor_request_callback(am_usbd_printer_handle handle,
                                                        am_vendor_request_t    pfn_cb,
                                                        void                  *p_arg)
{
    if (handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    handle->p_dev->vendor_req.pfn_vendor = pfn_cb;
    handle->p_dev->vendor_req.p_arg      = p_arg;

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief ��ʼ��USB
 *
 * \param[in] p_dev     : ָ��USB�豸
 * \param[in] p_info    : ָ��USB�豸��Ϣ
 *
 * \return USB��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_usbd_printer_handle am_usbd_printer_init (am_usbd_printer_t             *p_dev,
                                             const am_usbd_printer_info_t  *p_info,
                                             am_usbd_dev_t                 *p_usbd)
{
    uint8_t i = 0;
    if (NULL == p_dev  || NULL == p_info) {
        return NULL;
    }

    p_dev->p_dev   = p_usbd;
    p_dev->p_dev->class_req.pfn_class = __usbd_printer_class_request;
    p_dev->p_dev->class_req.p_arg     = p_dev;


    p_dev->p_info  = p_info;

    p_dev->port_state     = AM_USBD_PRINTER_PORT_STATUS_DEFAULT_VALUE;  // ��ӡ������Ϊȱʡֵ
    p_dev->p_printer_buff = p_dev->p_info->p_printer_buff;

    p_dev->r_funcs.pfn_recv_cb = NULL;
    p_dev->r_funcs.p_recv_arg  = 0;

    p_dev->s_funcs.pfn_send_cb = NULL;
    p_dev->s_funcs.p_send_arg  = 0;

    p_dev->endpoint.endpoint_in  = 0;
    p_dev->endpoint.endpoint_out = 0;

    // ������������˵�
    for(i = 1; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->p_dev->endpoint_info[i].inuse) {   // �˵��Ƿ�Ǳ�ʹ��
            if ((p_dev->p_dev->endpoint_info[i].ep_address & AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK)
                    == AM_USB_DESC_ENDPOINT_ADDR_DIR_IN) {
                p_dev->endpoint.endpoint_in = i;
            }

            if ((p_dev->p_dev->endpoint_info[i].ep_address & AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK )
                    == AM_USB_DESC_ENDPOINT_ADDR_DIR_OUT) {
                p_dev->endpoint.endpoint_out = i;
            }
        }
    }

    /* �����ӡ���жϻص�����*/
    p_dev->p_dev->endpoint_info[p_dev->endpoint.endpoint_out].pfn_callback = am_printer_recv_cb;
    p_dev->p_dev->endpoint_info[p_dev->endpoint.endpoint_out].p_arg = p_dev;

    p_dev->p_dev->endpoint_info[p_dev->endpoint.endpoint_in].pfn_callback = am_printer_send_cb;
    p_dev->p_dev->endpoint_info[p_dev->endpoint.endpoint_in].p_arg = p_dev;

    am_usbd_init(p_dev->p_dev);

    // ���ؿ��� handle
    return p_dev;
}

/**
 * \brief USB Device ȥ��ʼ��
 *
 * \param[in] p_info : ָ��USB�豸��Ϣ
 */
void am_usbd_printer_deinit (am_usbd_printer_t *p_dev)
{
    if (p_dev != NULL) {
        am_usbd_deinit(p_dev->p_dev);
    }
}


/*end of file */
