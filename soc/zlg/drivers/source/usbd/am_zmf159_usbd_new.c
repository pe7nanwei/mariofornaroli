/////*******************************************************************************
////*                                 AMetal
////*                       ----------------------------
////*                       innovating embedded platform
////*
////* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
////* All rights reserved.
////*
////* Contact information:
////* web site:    http://www.zlg.cn/
////*******************************************************************************/
////
/////**
//// * \file
//// * \brief IWDG������ӿ�
//// * \internal
//// * \par Modification history
//// * - 1.00 19-3-7  adw, first implementation
//// * \endinternal
//// */
//
//#include "am_usbd.h"
//#include "am_zmf159_usbd.h"
//#include "am_int.h"
//#include "amhw_zmf159_usb.h"
//#include "amhw_zmf159_rcc.h"
//
//#define Type_Recipient (p_dev->device.setup_data.b_request & (0x60 | 0x1f))
//
//
//#define __ENDPOINT_CTR     (0x03)
//#define __ENDPOINT_IN      (0x01)
//#define __ENDPOINT_OUT     (0x02)
//
//static uint8_t __rxusbbufodd[16] = {0};
//static uint8_t __txusbbufodd[16] = {0};
//
//static uint8_t __epindatanum[16] = {0};
//
//static uint8_t __setup_packet[8]  = {0};
//
//
///**
// * \brief ͨ��wValue��ֵѰ��ָ����������
// *
// * \retval �ɹ�����������ָ�룬ʧ�ܷ���NULL
// *
// * \note �������������¼�����������ͨ���˷����
// */
//static uint8_t * __find_desc_by_wValue1 (const am_zmf159_usbd_dev_t *p_dev,
//                                         uint16_t                    w_value)
//{
//    int i = 0;
//
//    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
//        if (w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
//            return (uint8_t *)(p_dev->p_info->p_devinfo->p_descriptor[i].p_desc);
//        }
//    }
//    return NULL;
//}
//
//static am_usb_status_t __ep_init(am_zmf159_usbd_dev_t      *p_dev,
//                                 am_usbd_endpoint_init_t   *epinit,
//                                 amhw_zmf159_usb_bdt_t     *p_usb_bdt,
//                                 uint32_t                   databufadd)
//{
//    uint8_t i = 0;
//    uint16_t max_packet_size = epinit->max_packet_size;
//    uint8_t  endpoint = (epinit->endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK);
//
//    for (i = 0; i < p_dev->max_ep_num; i++) {
//        /* �˵��������б���ָ��������˵� */
//        if (p_dev->device.endpoint_info[i].inuse == AM_TRUE &&
//            p_dev->device.endpoint_info[i].ep_address == epinit->endpoint_address) {
//            break;
//        }
//    }
//
//    if (i == p_dev->max_ep_num)
//        return AM_USB_STATUS_INVALID_REQUEST;
//
//    if (endpoint >= p_dev->max_ep_num)
//        return AM_USB_STATUS_INVALID_PARAMETER;
//    if (epinit->transfer_type > AM_USB_ENDPOINT_INTERRUPT)
//        return AM_USB_STATUS_INVALID_PARAMETER;
//
//    /* ���ö˵��ܴ��������ֽڸ��� */
//    if (max_packet_size > AM_USBD_MAX_EP_DATA_CNT)
//        max_packet_size = AM_USBD_MAX_EP_DATA_CNT;
//
////    am_kprintf("reset init ep: %x \r\n", endpoint);
//
//    p_usb_bdt->rx_buf[0].format = 0;
//    p_usb_bdt->rx_buf[0].adress = databufadd;
//    p_usb_bdt->rx_buf[0].format |= 0x40 << 16;   //����64byte
//    p_usb_bdt->rx_buf[0].format |= 1<<7;
//
//    p_usb_bdt->rx_buf[1].format = 0;
//    p_usb_bdt->rx_buf[1].format |= 0x40 << 16;   //����64byte
//    p_usb_bdt->rx_buf[1].adress = p_usb_bdt->rx_buf[0].adress + 0x40;
//    p_usb_bdt->rx_buf[1].format |= 1<<6;
//    p_usb_bdt->rx_buf[1].format |= 1<<7;
//
//    p_usb_bdt->tx_buf[0].format = 0x00;
//    p_usb_bdt->tx_buf[0].adress = p_usb_bdt->rx_buf[0].adress + 0x80;
//
//    p_usb_bdt->tx_buf[1].format = 0x00;
//    p_usb_bdt->tx_buf[1].adress = p_usb_bdt->rx_buf[0].adress + 0xC0;
//
//	for(i = 0; i < 64; i++) {
//		*(uint8_t*)(p_usb_bdt->tx_buf[0].adress + i) = 0;
//		*(uint8_t*)(p_usb_bdt->tx_buf[1].adress + i) = 0;
//		*(uint8_t*)(p_usb_bdt->rx_buf[0].adress + i) = 0;
//		*(uint8_t*)(p_usb_bdt->rx_buf[1].adress + i) = 0;
//	}
//
//	// ����ǿ��ƶ˵�, ֱ������Ϊ0x0d, ����˵�����Ϊ0x05,�������Ϊ0x09
//	// ������������ң���ʹ��
//	if (endpoint == 0) {
//		amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x0d);
//	} else if ((epinit->endpoint_address >> 7) & 0x01) { // ������䷽��Ϊ����Ļ�
//		amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x05);
//	} else {
//		amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x09);
//	}
//
//    p_dev->device.endpoint_info[endpoint].stalled = 0;
//    p_dev->device.endpoint_info[endpoint].max_packet_size = max_packet_size;
//    p_dev->device.endpoint_info[endpoint].transfer_type = epinit->transfer_type;
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
///**
// * \brief ��ĳ���˵�ȥ��ʼ��
// *
// *  \param[in] p_dev       : USB�豸
// *  \param[in] endpoint    : ָ���Ķ˵�
// */
//static am_usb_status_t __ep_deinit (am_zmf159_usbd_dev_t *p_dev,
//                                    uint8_t               endpoint)
//{
//    endpoint &= AM_USBD_ENDPOINT_NUMBER_MASK;
//
//    amhw_zmf159_ep_ctrl_set(ZMF159_USB, endpoint, 0x02);  /* ���ܶ˵� */
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
///**
// * \brief ���ö˵�����
// *
// * \param[in] p_dev         : USB�豸
// * \param[in] endpoint_addr : �˵��ַ
// */
//static am_usb_status_t __ep_stall (am_zmf159_usbd_dev_t *p_dev,
//                                   uint8_t               endpoint_addr)
//{
//    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;
//
//    p_dev->device.endpoint_info[endpoint].stalled = 1;    /* ����������־ */
//
//    amhw_zmf159_ep_halt_set(ZMF159_USB, endpoint, 1);
//    return AM_USB_STATUS_SUCCESS;
//}
//
///**
// * \brief ���ö˵㲻����
// *
// * \param[in] p_dev         : USB�豸
// * \param[in] endpoint_addr : �˵��ַ  D7�� 1��USB_IN  0��USB_OUT
// */
//static am_usb_status_t __ep_unstall (am_zmf159_usbd_dev_t *p_dev,
//                                     uint8_t               endpoint_addr)
//{
//    uint8_t endpoint = endpoint_addr & AM_USBD_ENDPOINT_NUMBER_MASK;
//
//    p_dev->device.endpoint_info[endpoint].stalled = 0;
//
//    __rxusbbufodd[endpoint] = 0;
//    __txusbbufodd[endpoint] = 0;
//    __epindatanum[endpoint] = 0;
//    amhw_zmf159_ep_halt_set(ZMF159_USB, endpoint, 0);
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
//
//static void __usb_device_reset(am_zmf159_usbd_dev_t   *p_dev)
//{
//    int i = 0;
//    am_usbd_endpoint_init_t endpoint;
//
//	uint8_t *p_tmp = __find_desc_by_wValue1(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
//
//    p_dev->Current_Configuration = 0;
//    p_dev->Current_Feature = *(p_tmp + 7);
//    p_dev->Current_Interface = 0;
//
//    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);
//
//    // �˵��ʼ��
//    for(i = 0; i < p_dev->max_ep_num; i++) {
//    	if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
//    		endpoint.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
//            endpoint.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
//            endpoint.transfer_type = p_dev->device.endpoint_info[i].transfer_type;
//            __ep_init(p_dev, &endpoint, p_dev->p_usb_bdt + i, (uint32_t)(p_dev->p_usb_bdt) + 0x200 + 0x100 * i);
//    	}
//    }
//
//    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
//    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
//    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);
//
//    __txusbbufodd[0] = 0;
//    amhw_zmf159_addr_set(ZMF159_USB, 0);
//}
//
//
//static am_usb_status_t __usb_device_init(am_usbd_handle_t handle)
//{
//    int i = 0;
//    am_usbd_endpoint_init_t endpoint;
//    am_zmf159_usbd_dev_t   *p_dev = (am_zmf159_usbd_dev_t *)handle;
//
//    p_dev->Current_Configuration = 0;
//
//    amhw_zmf159_bdt_page_set(ZMF159_USB, 0x20007000);
//    amhw_zmf159_addr_set(ZMF159_USB, 0);
//
//    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
//    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);
//
////    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
//
//    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);
//
////    __txusbbufodd[0] = 0;
//
//    amhw_zmf159_addr_set(ZMF159_USB, 0);
//    p_dev->device.device_address = 0;
//
//    /* ���SETUP���� */
//    p_dev->device.setup_data.bm_request_type = 0;
//    p_dev->device.setup_data.b_request       = 0;
//    p_dev->device.setup_data.w_value         = 0;
//    p_dev->device.setup_data.w_index         = 0;
//    p_dev->device.setup_data.w_length        = 0;
//
//    for(i = 0; i < p_dev->max_ep_num; i++) {
//    	if (p_dev->device.endpoint_info[i].inuse == AM_TRUE) {
//    		endpoint.endpoint_address = p_dev->device.endpoint_info[i].ep_address;
//            endpoint.max_packet_size = p_dev->device.endpoint_info[i].max_packet_size;
//            endpoint.transfer_type = p_dev->device.endpoint_info[i].transfer_type;
//            __ep_init(p_dev, &endpoint, p_dev->p_usb_bdt + i, (uint32_t)(p_dev->p_usb_bdt) + 0x200 + 0x100 * i);
//    	}
//    }
//
//    __txusbbufodd[0] = 0;
//
//
//    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);
//
//    amhw_zmf159_usb_int_enable(ZMF159_USB,
//    		                   ZMF159_USB_INT_STAT_RST | ZMF159_USB_INT_STAT_TOK_DNE);
//
////    // ���ж�
////    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_RST);
////    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_TOK_DNE);
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
//static am_usb_status_t __usb_device_deinit(am_usbd_handle_t handle)
//{
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
//static am_usb_status_t __usb_device_send(am_usbd_handle_t handle, uint8_t ep, uint8_t *p_buf, uint32_t len)
//{
//    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;
//
//    uint32_t i = 0;
//    uint8_t *pBuf = NULL;
//
//    am_kprintf("send buf : %x %x %x\r\n", p_buf[0], p_buf[1], p_buf[2]);
//
//    pBuf = (uint8_t*)((p_dev->p_usb_bdt + ep)->tx_buf[__txusbbufodd[ep]].adress) ;
//
//    (p_dev->p_usb_bdt + ep)->tx_buf[__txusbbufodd[ep]].format &= 0x00ff00;
//
//    for (i = 0; i < len; i++) {
//        pBuf[i] = *p_buf;
//        p_buf++;
//    }
//
////    am_kprintf("send buf : %x %x %x\r\n", pBuf[0], pBuf[1], pBuf[2]);
//
//    (p_dev->p_usb_bdt+ep)->tx_buf[__txusbbufodd[ep]].format |= (len<<16)|(__epindatanum[ep]<<6)/**/;
//    __epindatanum[ep] = !__epindatanum[ep];
//
//    // �������� OWN
//    (p_dev->p_usb_bdt+ep)->tx_buf[__txusbbufodd[ep]].format |= 1 << 7;
//    __txusbbufodd[ep] = !__txusbbufodd[ep];
//
//    //�ȴ��������
////    while(((pUSB_OTG_BDT+EPNum)->tx_buf[txUsbBufOdd[EPNum]].format >> 7) & 0x01);
//
//
//    return AM_USB_STATUS_SUCCESS;
//}
//
//static am_usb_status_t __usb_device_recv(am_usbd_handle_t handle, uint8_t ep, uint8_t *p_buf, uint32_t len)
//{
//    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;
//    am_usb_status_t error = AM_USB_STATUS_ERROR;
//    uint32_t i    = 0;
//    uint8_t *pBuf = NULL;
//    uint8_t avali_data_cnt = 0;     /* fifo����Ч���ݸ��� */
//
//    // ��ȡ��ַ
//    pBuf = (uint8_t*)((p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].adress) ;
//
//    // ��Ч��������
//    avali_data_cnt = (((p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format) >> 16) & 0x3ff;
//    p_dev->device.endpoint_info[ep].val_length = avali_data_cnt;
//
//    if (avali_data_cnt == 0)
//        return AM_USB_STATUS_ERROR;
//    else if (avali_data_cnt < len)
//        error = AM_USB_STATUS_ALLOC_FAIL;
//    else if (avali_data_cnt == len)
//        error = AM_USB_STATUS_SUCCESS;
//    else if (avali_data_cnt > len) {
//        error = AM_USB_STATUS_SUCCESS;
//        avali_data_cnt = len;
//    }
//
//    for (i = 0; i < avali_data_cnt; i++) {
//       *p_buf = pBuf[i];
//        p_buf++;
//    }
//
//
//    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format &= 0x00ff00;//�������,���stall
//    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format |= (64 << 16);//�����������ֽ�
//    (p_dev->p_usb_bdt + ep)->rx_buf[__rxusbbufodd[ep]].format |= 1 << 7;
//
//    return error;
//}
//
//
//static am_usb_status_t __usb_device_cancel(am_usbd_handle_t handle, uint8_t ep)
//{
//    // todo
//    return AM_USB_STATUS_ERROR;
//}
//
//
//static am_usb_status_t __usb_device_control(am_usbd_handle_t handle, am_usbd_control_type_t type, void *param)
//{
//    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)handle;
//    am_usb_status_t error = AM_USB_STATUS_ERROR;
//    uint8_t *temp8;
//    uint8_t temp;
//    am_usbd_ep_status_t *endpointStatus = NULL;
//    uint8_t endpoint = 0;
//
//    if (!handle)
//        return AM_USB_STATUS_INVALID_HANDLE;
//
//    switch ((int)type) {
//        case AM_USBD_CONTROL_RUN:
//            amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);
//            error = AM_USB_STATUS_SUCCESS;
//            break;
//
//        case AM_USBD_CONTROL_STOP:
//            amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_EN);
//            error = AM_USB_STATUS_SUCCESS;
//            break;
//
//        case AM_USBD_CONTROL_ENDPOINT_INIT:     /* ��ĳ���˵��ʼ�� */
//            if (param) {
//                // ��ȡ�˵�
//                temp = (((am_usbd_endpoint_init_t *)param)->endpoint_address & 0x0f);
//                error = __ep_init(p_dev,
//                                 (am_usbd_endpoint_init_t *)param,
//                                 p_dev->p_usb_bdt + temp,
//                                 (uint32_t)p_dev->p_usb_bdt + 0x200 + 0x100 * temp);
//            }
//            break;
//
//        case AM_USBD_CONTROL_ENDPOINT_DEINIT:   /* ��ĳ���˵�ȥ��ʼ�� */
//            if (param) {
//                temp8 = (uint8_t *)param;
//                error = __ep_deinit(p_dev, *temp8);
//            }
//            break;
//
//        case AM_USBD_CONTROL_ENDPOINT_STALL:    /* ���ƶ˵����� */
//            if (param) {
//                temp8 = (uint8_t *)param;
//                error = __ep_stall(p_dev, *temp8);
//            }
//            break;
//
//        case AM_USBD_CONTROL_ENDPOINT_UNSTALL:  /* ���ƶ˵㲻���� */
//            if (param) {
//                temp8 = (uint8_t *)param;
//                error = __ep_unstall(p_dev, *temp8);
//            }
//            break;
//
//        case AM_USBD_CONTROL_GET_DEVICE_STATUS: /* ��ȡ�豸״̬ */
//
//            break;
//
//        case AM_USBD_CONTROL_GET_ENDPOINT_STATUS:   /* ͨ���˵��ַ��ȡ�˵�״̬ */
//            if (param) {
//                endpointStatus = (am_usbd_ep_status_t *)param;
//
//                endpoint = (endpointStatus->endpoint_address) & AM_USBD_ENDPOINT_NUMBER_MASK;
//
//                if (endpoint < p_dev->max_ep_num) {
//                    endpointStatus->endpoint_status = p_dev->device.endpoint_info[endpoint].stalled;
//                    error = AM_USB_STATUS_SUCCESS;
//                } else {
//                    error = AM_USB_STATUS_INVALID_PARAMETER;
//                }
//            }
//            break;
//
//        case AM_USBD_CONTROL_SET_DEVICE_ADDRESS:    /* ����USB�豸��ַ */
//            if (param) {
//                temp8 = (uint8_t *)param;
////                am_kprintf();
//                amhw_zmf159_addr_set(ZMF159_USB, *temp8);
//                error = AM_USB_STATUS_SUCCESS;
//            }
//            break;
//
//        case AM_USBD_CONTROL_GET_SYNCH_FRAME:
//            break;
//
//        case AM_USBD_CONTROL_RESUME:
//            amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_RESUME);
//            break;
//
//            /* ����Ĭ��״̬ */
//        case AM_USBD_CONTROL_SET_DEFAULT_STATUS:
//            error = AM_USB_STATUS_SUCCESS;
//            break;
//
//        case AM_USBD_CONTROL_GET_SPEED:
//            if (param) {
//                temp8 = (uint8_t *)param;
//                *temp8 = AM_USB_SPEED_FULL;
//                error = AM_USB_STATUS_SUCCESS;
//            }
//            break;
//
//        case AM_USBD_CONTROL_GET_OTG_STATUS:
//            break;
//        case AM_USBD_CONTROL_SET_OTG_STATUS:
//            break;
//        case AM_USBD_CONTROL_SET_TEST_MODE:
//            break;
//        default:
//            break;
//    }
//
//    return error;
//}
//
//static const am_usbd_interface_t __g_usb_device_interface = {
//    __usb_device_init,
//    __usb_device_deinit,
//    __usb_device_send,
//    __usb_device_recv,
//    __usb_device_cancel,
//    __usb_device_control
//};
//
//
//static uint8_t __standard_clearfeature(am_zmf159_usbd_dev_t  *p_dev)
//{
//	return 0;
//}
//
//static uint8_t __standard_setdevicefeature(am_zmf159_usbd_dev_t  *p_dev)
//{
//	AM_BIT_SET(p_dev->Current_Feature, 5);
//  return 0; // USB_SUCCESS
//}
//
//
//
//
//static uint8_t __standard_setconfiguration(am_zmf159_usbd_dev_t  *p_dev)
//{
//
//  if ((p_dev->device.setup_data.w_value <= 1)
//      && (p_dev->device.setup_data.w_index == 0)) /*call Back usb spec 2.0*/
//  {
//    p_dev->Current_Configuration = p_dev->device.setup_data.w_value;
//    return 0; // USB_SUCCESS
//  }
//  else
//  {
//    return 2; // USB_UNSUPPORT
//  }
//}
//
//
//static void __nodata_setup0(am_zmf159_usbd_dev_t  *p_dev)
//{
//	  uint8_t Result = 2; // USB_UNSUPPORT
//	  uint32_t RequestNo = p_dev->device.setup_data.b_request;
//	  uint32_t ControlState;
//
//	  if (Type_Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE))
//	  {
//	    /* Device Request*/
//	    /* SET_CONFIGURATION*/
//	    if (RequestNo == AM_USB_REQ_STANDARD_SET_CONFIGURATION)
//	    {
//	      Result = __standard_setconfiguration(p_dev);
//	    }
//
//	    /*SET ADDRESS*/
//	    else if (RequestNo == AM_USB_REQ_STANDARD_SET_ADDRESS)
//	    {
//	      if ((p_dev->device.setup_data.w_value > 127)
//	          || (p_dev->device.setup_data.w_index != 0)
//	          || (p_dev->Current_Configuration != 0))
//	        /* Device Address should be 127 or less*/
//	      {
//	        ControlState = 8; // STALLED
//
//	        goto exit_NoData_Setup0;
//	      } else {
//	        Result = 0; // USB_SUCCESS
//	      }
//	    }
//	    /*SET FEATURE for Device*/
//	    else if (RequestNo == AM_USB_REQ_STANDARD_SET_FEATURE)
//	    {
//	      if ((p_dev->device.setup_data.w_value == AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP)
//	          && (p_dev->device.setup_data.w_index == 0)
//	          && (AM_BIT_ISSET(p_dev->Current_Feature, 5)))
//	      {
//	        Result = __standard_setdevicefeature(p_dev);
//	      }
//	      else
//	      {
//	        Result = 2; // USB_UNSUPPORT
//	      }
//	    }
//	    /*Clear FEATURE for Device */
//	    else if (RequestNo == AM_USB_REQ_STANDARD_CLEAR_FEATURE)
//	    {
//	      if ((p_dev->device.setup_data.w_value == AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP)
//	          && (p_dev->device.setup_data.w_index == 0)
//	          && (AM_BIT_ISSET(p_dev->Current_Feature, 5)))
//	      {
//	        Result = __standard_clearfeature(p_dev);
//	      }
//	      else
//	      {
//	        Result = 2; // USB_UNSUPPORT
//	      }
//	    }
//
//	  }
//
//	  /* Interface Request*/
//	  else if (Type_Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
//	  {
//	    /*SET INTERFACE*/
//	    if (RequestNo == SET_INTERFACE)
//	    {
//	      Result = __standard_setinterface(p_dev);
//	    }
//	  }
//
//	  /* EndPoint Request*/
//	  else if (Type_Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | ENDPOINT_RECIPIENT))
//	  {
//	    /*CLEAR FEATURE for EndPoint*/
//	    if (RequestNo == CLEAR_FEATURE)
//	    {
//	      Result = Standard_ClearFeature();
//	    }
//	    /* SET FEATURE for EndPoint*/
//	    else if (RequestNo == SET_FEATURE)
//	    {
//	      Result = Standard_SetEndPointFeature();
//	    }
//	  }
//	  else
//	  {
//	    Result = USB_UNSUPPORT;
//
//	  }
//
//	  // ������
//	  if (Result != USB_SUCCESS)
//	  {
//	    Result = (*pProperty->Class_NoData_Setup)(RequestNo);
//	    if (Result == USB_NOT_READY)
//	    {
//	      ControlState = PAUSE;
//	      goto exit_NoData_Setup0;
//	    }
//	  }
//
//	  if (Result != USB_SUCCESS)
//	  {
//	    goto exit_NoData_Setup0;
//	  }
//
//	  ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */
//
//	  // ���Ϳհ�
//	  USB_StatusIn();
//
//	exit_NoData_Setup0:
//	  pInformation->ControlState = ControlState;
//	  return;
//}
//
//
//
//static void __setup0_process(am_zmf159_usbd_dev_t  *p_dev)
//{
//    uint8_t *pBuf ;
//  if (p_dev->device.running_ctrl_state != 9)
//  {
//	  am_kprintf("setup\r\n");
//    pBuf = __setup_packet;
//    __usb_device_recv(p_dev, 0, pBuf, 8);
//    p_dev->device.setup_data.bm_request_type = pBuf[0];//USB->rSETUP[0];  // bmRequestType
//    p_dev->device.setup_data.b_request       = pBuf[1];//USB->rSETUP[1];       // bRequest */
//    p_dev->device.setup_data.w_value  = pBuf[3]|(pBuf[2]<<8);//(USB->rSETUP[3])|(USB->rSETUP[2]<<8);   // wValue
//    p_dev->device.setup_data.w_index  = pBuf[5]|(pBuf[4]<<8);//(USB->rSETUP[5])|(USB->rSETUP[4]<<8);  // wIndex
//    p_dev->device.setup_data.w_length = pBuf[6]|(pBuf[7]<<8);//(USB->rSETUP[6])|(USB->rSETUP[7]<<8);  // wLength
//  }
//
//  am_kprintf("req: %d \r\n", p_dev->device.setup_data.b_request);
//  p_dev->device.running_ctrl_state = 1; // SETTING_UP
//
//  if (p_dev->device.setup_data.w_length == 0)
//  {
//    /* Setup with no data stage */
//    __nodata_setup0(p_dev);
//  } else {
//    /* Setup with data stage */
////    Data_Setup0();
//  }
//}
//
//
//
//static void __token_isr(am_zmf159_usbd_dev_t  *p_dev)
//{
//  uint32_t wEpIntSta = 0,wEpxIntSta = 0;
//  uint32_t wEpStat;
//  uint8_t txUsbBufOddTemp;
//  uint8_t EPindex;
//
////  wEpStat = _GetEP_INT_STA();
////  _ClrUSB_INT_STA(OTG_FS_INT_STAT_DNE) ;
//  wEpStat = amhw_zmf159_usb_stat_get(ZMF159_USB);
//  amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_TOK_DNE);
//  wEpIntSta = (wEpStat>>4)&0xf;           //��ȡ�ж϶˵��
//
//  if(wEpIntSta == 0)       //�˵�0
//  {
//      EPindex = 0;
//      am_kprintf("ep int 0\r\n");
//      if(((wEpStat>>3)&0x01) == 0)//RX
//      {
//        __rxusbbufodd[0] = (wEpStat>>2)&0x1;
//        wEpxIntSta = p_dev->p_usb_bdt->rx_buf[__rxusbbufodd[0]].format;
//      } else {
//        txUsbBufOddTemp = (wEpStat>>2)&0x1;
//        wEpxIntSta = p_dev->p_usb_bdt->tx_buf[txUsbBufOddTemp].format;
//        p_dev->p_usb_bdt->tx_buf[txUsbBufOddTemp].format = 0;
//      }
//      wEpxIntSta = (wEpxIntSta >> 2)&0xf;
//
//      if(wEpxIntSta == 0x0D)//setup
//      {
//        //USB_OTG_FS->CTL &= ~(1<<5);//tip
//          amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_TXD_SUSPEND_TOKBSY);
//        __epindatanum[0] = 1;
//        __setup0_process(p_dev);
//        return;
//      }
//
//      if(wEpxIntSta == 0x01)//|EPn_INT_STATE_OUTNACK
//      {
//    	  am_kprintf("ep OUTNACK\r\n");
////        Out0_Process();
//        return;
//      }
//
//      if(wEpxIntSta == 0x9)//|EPn_INT_STATE_ACK
//      {
//    	  am_kprintf("ep INACK\r\n");
////        In0_Process();
//
//        return;
//      }
//  }/* if(EPindex == 0) */
//  else if(wEpIntSta != 0) {
//    EPindex = wEpIntSta;
//    if(((wEpStat>>3)&0x01) == 0)//RX
//    {
//      __rxusbbufodd[wEpIntSta] = (wEpStat>>2)&0x1;
//      wEpxIntSta = (p_dev->p_usb_bdt+EPindex)->rx_buf[__rxusbbufodd[EPindex]].format;
//    } else {
//      txUsbBufOddTemp = (wEpStat>>2)&0x1;
//      wEpxIntSta = (p_dev->p_usb_bdt + EPindex)->rx_buf[txUsbBufOddTemp].format;
//      (p_dev->p_usb_bdt+EPindex)->rx_buf[txUsbBufOddTemp].format = 0;
//    }
//
//    wEpxIntSta = (wEpxIntSta >> 2) & 0xf; // ����˵��ж� ��������˵��ж�
//
//    // �˵��жϻص�
//    if (p_dev->device.endpoint_info[p_dev->int_ep].pfn_callback != NULL) {
//        (p_dev->device.endpoint_info[p_dev->int_ep].pfn_callback)(p_dev->device.endpoint_info[p_dev->int_ep].p_arg);
//    }
//  }/* if(EPindex != 0)*/
//}
//
//static void  __usbd_isr_function(void *p_arg)
//{
//    am_zmf159_usbd_dev_t  *p_dev = (am_zmf159_usbd_dev_t *)p_arg;
//	volatile uint16_t wIstr = 0;
//    wIstr = amhw_zmf159_usb_int_get(ZMF159_USB);
//  if(wIstr & ZMF159_USB_INT_STAT_RST)
//  {
//	  am_kprintf("reset\r\n");
////    _ClrUSB_INT_STA(OTG_FS_INT_STAT_RST) ;
//      amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_RST);
//      __usb_device_reset(p_dev);
//
//  }
//
//  if(wIstr & ZMF159_USB_INT_STAT_TOK_DNE)
//  {
//    am_kprintf("token\r\n");
//    __token_isr(p_dev);   //���ӳ���������жϱ�־
//  }
//}
//
//
//// ���������л�ȡ�˵�ʹ�����
//static am_err_t __init_ep_info(am_zmf159_usbd_dev_t           *p_dev)
//{
//    uint8_t  ret     = 0;       /* ���巵��ֵ */
//    uint8_t *p_tmp   = NULL;    /* ���ݻ���ָ�� */
//    uint8_t  ep_num  = 0;       /* �˵�� */
//    uint8_t  tmp     = 0;       /* ��ʱ����*/
//    uint8_t  offset  = 0;       /* ƫ����*/
//    uint8_t  len     = 0;       /* �������ܳ��� */
//    am_usb_descriptor_endpoint_t  *p_desc_ep   = NULL;
//    /* ��ȡ���������� */
//    p_tmp = __find_desc_by_wValue1(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
//    if (p_tmp == NULL)
//        return AM_ERROR;
//    /*���������������������������ܳ���*/
//    len = (uint8_t)( ( *(p_tmp + 2) ) | ( ( *(p_tmp + 3)) >> 8 ) );
//    /* �Ҷ˵�������*/
//    while (tmp < len) {
//        offset  = *(p_tmp);   /* �����������ֽ���,��һ��Ϊ����������*/
//        p_tmp  +=   offset;   /* ��ƫ�� */
//        tmp    +=   offset;
//        /* ����Ƕ˵�������*/
//        if ((*(p_tmp + 1) == AM_USB_DESC_TYPE_ENDPOINT) && (*p_tmp = AM_USB_DESC_LENGTH_ENDPOINT)) {
//            p_desc_ep = (am_usb_descriptor_endpoint_t *)p_tmp;  // �˵�������
//            // �˵��
//            ep_num = p_desc_ep->b_endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK;
//            am_kprintf("inuse endpoint: %d \n", ep_num);
//            p_dev->device.endpoint_info[ep_num].inuse = 1;  // ��ʾ�˵㱻ʹ��
//            p_dev->device.endpoint_info[ep_num].ep_address = p_desc_ep->b_endpoint_address;
//            p_dev->device.endpoint_info[ep_num].max_packet_size = (p_desc_ep->wmax_packet_size[1] << 8) |
//                                                                   p_desc_ep->wmax_packet_size[0];
//            p_dev->device.endpoint_info[ep_num].transfer_type = p_desc_ep->bm_attributes;
//            p_dev->device.endpoint_info[ep_num].stalled = 0;
//            ret++;
//        }
//    }
//    return ret;
//}
//
//
//
///**
// * \brief ��ʼ��USB
// *
// * \param[in] p_dev     : ָ��USB�豸
// * \param[in] p_info    : ָ��USB�豸��Ϣ
// *
// * \return USB��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
// */
//am_usbd_dev_t *am_zmf159_usbd_init (am_zmf159_usbd_dev_t           *p_dev,
//                                    const am_zmf159_usbd_devinfo_t *p_info)
//{
//    int i = 0;
//
//    if (NULL == p_dev  || NULL == p_info) {
//        return NULL;
//    }
//
//    p_dev->max_ep_num = AM_ZMF159MAX_EP_NUM;   // ��ֵ���˵���
//    p_dev->p_usb_bdt  = NULL;                  // ��ʼ��ҳ��ַΪNULL
//    p_dev->int_stat   = 0;
//    p_dev->int_ep     = 0;
//
//    p_dev->p_info = p_info;
//    p_dev->device.p_info = p_info->p_devinfo;
//
//    p_dev->device.ctrl_handle = p_dev;
//    p_dev->device.p_interface = &__g_usb_device_interface;
//
//    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
//        p_dev->device.endpoint_info[i].pfn_callback = NULL;
//        p_dev->device.endpoint_info[i].p_arg = NULL;
//    }
//
//    /* ��ʼ����������*/
//    p_dev->device.vendor_req.pfn_vendor = NULL;
//    p_dev->device.vendor_req.p_arg      = NULL;
//
//    p_dev->device.class_req.pfn_class   = NULL;
//    p_dev->device.class_req.p_arg       = NULL;
//
//    p_dev->device.device_address = 0;
//    p_dev->device.state          = AM_USBD_STATE_DEFAULT;
//
//    //    p_dev->int_ep_union.int_ep_flag = 0;
//
//    //    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++)
//    //        p_dev->ep_int_type_union.ep_int_type[i] = 0;
//
//    p_dev->device.setup_data.bm_request_type = 0;
//    p_dev->device.setup_data.b_request = 0;
//    p_dev->device.setup_data.w_value = 0;
//    p_dev->device.setup_data.w_index = 0;
//    p_dev->device.setup_data.w_length = 0;
//
//
//    /**< \brief ���ö˵�0��Ĭ������ */
//    p_dev->device.endpoint_info[0].stalled          = 0;
//    p_dev->device.endpoint_info[0].ep_address       = 0;
//    p_dev->device.endpoint_info[0].max_packet_size  = AM_USBD_MAX_EP_DATA_CNT;
//    p_dev->device.endpoint_info[0].transfer_type    = AM_USB_ENDPOINT_CONTROL;
//    p_dev->device.endpoint_info[0].inuse            = 1;
//    p_dev->device.endpoint_info[0].val_length       = 0;
//
//    for (i = 1 ;i < AM_USBD_MAX_EP_CNT; i++) {
//        p_dev->device.endpoint_info[i].stalled          = 0;
//        p_dev->device.endpoint_info[i].ep_address       = 0;
//        p_dev->device.endpoint_info[i].max_packet_size  = 0;
//        p_dev->device.endpoint_info[i].transfer_type    = 0;
//        p_dev->device.endpoint_info[i].inuse            = 0;
//        p_dev->device.endpoint_info[i].val_length       = 0;
//    }
//    if (__init_ep_info(p_dev) == -1) {
//#ifdef USB_DEBUG
//        am_kprintf("fail to init endpoint\n");
//#endif
//    }
//
//    p_dev->device.running_ctrl_state = 2;
//
////        am_usbd_ch9_std_request(&(p_dev->device));
//
//
//    if (p_info->pfn_plfm_init) {
//        p_info->pfn_plfm_init();
//    }
//
//    //Enable usb clock
//    amhw_zmf159_rcc_ahb2_enable(AMHW_ZMF159_RCC_AHB2_USBFS);
//
//    am_int_connect(p_info->inum, __usbd_isr_function, (void *)p_dev);
//    am_int_enable(p_info->inum);
//
//    return &(p_dev->device);
//}
//
///**
// * \brief USB Device ȥ��ʼ��
// *
// * \param[in] p_info : ָ��USB�豸��Ϣ
// */
//void am_zmf159_usbd_deinit (const am_zmf159_usbd_devinfo_t *p_info)
//{
//    if (p_info != NULL && p_info->pfn_plfm_deinit != NULL) {
//        p_info->pfn_plfm_deinit();
//    }
//}
//
//
//
//
//
//
//
///////* end of file */
