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
 * \brief     USBD��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_DCI_H
#define __AM_USB_DCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_usbd.h"
#include "am_usb_spec.h"
#include "am_usbd_ch9.h"

/**
 * \addtogroup am_if_usb_dci
 * \copydoc am_usb_dci.h
 * @{
 */

/** \brief Control type for controller */
typedef enum am_usbd_control_type {
    AM_USBD_CONTROL_RUN = 0U,            /**< \brief ʹ���豸 */
    AM_USBD_CONTROL_STOP,                /**< \brief ֹͣ�豸 */
    AM_USBD_CONTROL_ENDPOINT_INIT,       /**< \brief ��ʼ���豸 */
    AM_USBD_CONTROL_ENDPOINT_DEINIT,     /**< \brief ���ʼ�� */
    AM_USBD_CONTROL_ENDPOINT_STALL,      /**< \brief �˵����� */
    AM_USBD_CONTROL_ENDPOINT_UNSTALL,    /**< \brief �˵������ */
    AM_USBD_CONTROL_GET_DEVICE_STATUS,   /**< \brief ��ȡ�豸״̬ */
    AM_USBD_CONTROL_GET_ENDPOINT_STATUS, /**< \brief ��ȡ�˵�״̬ */
	AM_USBD_CONTROL_SET_ENDPOINT_STATUS, /**< \brief ���ö˵�״̬ */
    AM_USBD_CONTROL_SET_DEVICE_ADDRESS,  /**< \brief �����豸��ַ */
    AM_USBD_CONTROL_GET_SYNCH_FRAME,     /**< \brief ��ȡͬ��֡ */
    AM_USBD_CONTROL_RESUME,              /**< \brief �豸���� */
    AM_USBD_CONTROL_SET_DEFAULT_STATUS,  /**< \brief ���ÿ�����Ĭ��ֵ */
    AM_USBD_CONTROL_GET_SPEED,           /**< \brief ��ȡ��ǰ�ٶ� */
    AM_USBD_CONTROL_GET_OTG_STATUS,      /**< \brief ��ȡOTG״̬ */
    AM_USBD_CONTROL_SET_OTG_STATUS,      /**< \brief ����OUG״̬ */
    AM_USBD_CONTROL_SET_TEST_MODE,       /**< \brief ����ģʽ */
} am_usbd_control_type_t;

/** \brief ��ʼ�� */
typedef am_usb_status_t (*am_usbd_init_t)(am_usbd_handle_t handle);

/** \brief ���ʼ�� */
typedef am_usb_status_t (*am_usbd_deinit_t)(am_usbd_handle_t handle);

/** \brief ���ͺ��� */
typedef am_usb_status_t (*am_usbd_send_t)(am_usbd_handle_t handle,
                                         uint8_t           endpoint,
                                         uint8_t          *p_buffer,
                                         uint32_t          length);

/** \brief ���պ��� */
typedef uint8_t (*am_usbd_recv_t)(am_usbd_handle_t  handle,
                                  uint8_t           endpoint,
                                  uint8_t          *p_buffer,
                                  uint32_t          length);

/** \brief ȡ�� */
typedef am_usb_status_t (*am_usbd_cancel_t)(am_usbd_handle_t handle,
                                           uint8_t           endpoint);

/** \brief ���� */
typedef am_usb_status_t (*am_usbd_control_t)(am_usbd_handle_t       handle,
                                             am_usbd_control_type_t command,
                                             void                  *p_param);

/** \brief �˵�ص���������*/
typedef void (*am_usbd_ep_callback_t)(void *p_arg);

/* ��������ص���������.*/
typedef uint8_t (*am_vendor_request_t)(void *p_arg, uint8_t b_requrest);

/* ������ص���������.*/
typedef uint8_t (*am_class_request_t)(void *p_arg, uint8_t b_requrest);

/** \brief usb device ���ƽӿڽṹ�� */
typedef struct am_usbd_interface {
    am_usbd_init_t    pfn_device_init;      /**< \brief �豸��ʼ�� */
    am_usbd_deinit_t  pfn_device_deinit;    /**< \brief �豸��ʼ�� */
    am_usbd_send_t    pfn_device_send;      /**< \brief �豸�������� */
    am_usbd_recv_t    pfn_device_recv;      /**< \brief �豸�������� */
    am_usbd_cancel_t  pfn_device_cancel;    /**< \brief ȡ���˵㴫�� */
    am_usbd_control_t pfn_device_control;   /**< \brief �豸���ƺ��� */
} am_usbd_interface_t;


/** \brief �˵�״̬�ṹ */
typedef struct am_usbd_ep_info {
    uint8_t                inuse;           /**< \brief �˵��Ƿ�ᱻʹ�� */
    uint8_t                stalled;         /**< \brief �˵��Ƿ����� */
    uint8_t                ep_address;      /**< \brief �˵��ַ������ + �˵�ţ�*/

    /** \brief �˵㴫���� �� (���ƴ���, ͬ������, ��������, �жϴ���)*/
    uint8_t                transfer_type;   /**< \brief �˵���������*/
    uint8_t                val_length;      /**< \brief �˵���Ч���ݳ���*/
    uint16_t               max_packet_size; /**< \brief �˵�һ���Դ����������С */
    am_usbd_ep_callback_t  pfn_callback;    /**< \brief �˵�ص�����ָ�� */
    void                  *p_arg;           /**< \brief �˵�ص����� */
} am_usbd_ep_info_t;


/** \brief USB�豸��Ϣ�ṹ��*/
typedef struct am_usbd_devinfo {
    const am_usbd_descriptor_t *p_descriptor;       /**< \brief �������׵�ַ */
    uint8_t                     descriptor_num;     /**< \brief ���������� */
}am_usbd_devinfo_t ;

/* ������ص������ṹ�嶨��*/
typedef struct am_usbd_class_req_callback {
    am_class_request_t   pfn_class;   /**< \brief ������ص�����*/
    void                *p_arg;       /**< \brief ������ص���������*/
}am_usbd_class_req_cb_t;

/* ��������ص������ṹ�嶨��*/
typedef struct am_vendor_req_callback {
	am_vendor_request_t  pfn_vendor;  /**< \brief ��������ص�����*/
	void                *p_arg;       /**< \brief ��������ص���������*/
}am_usbd_vendor_req_cb_t;


/** \brief ����usb device*/
typedef struct am_usbd_dev am_usbd_dev_t;

/** \brief �����׼�豸����������*/
typedef void (*am_std_request_t)(am_usbd_dev_t *p_dev);


typedef struct __endpoint_info
{
  uint16_t   length;               /**< \brief ��Ҫ���ջ��߷��͵��ֽ���  */
  uint16_t   offset;               /**< \brief ���ջ��߷������ݵ�ƫ����  */
  uint16_t   packet_size;          /**< \brief USB�豸�����������ֽ���  */
//  uint8_t   *(*pfn_copy_data)(void *p_arg, uint16_t *p_length);
  uint8_t   *p_buf;
}am_data_info_t;


/** \brief USB device struct  */
struct am_usbd_dev {
	/**
	 *  \brief ������handle
	 *
	 *  �����ײ������handle Ϊ���ϲ�ӿڵ��ã�����an_usbd_send����
	 */
	am_usbd_handle_t      ctrl_handle;

    uint8_t               device_address;   /**< \brief �豸��ַ */
    uint8_t               state;            /**< \brief �豸״̬ */

    uint8_t               cur_feature;      /**< \brief �豸����*/
    uint8_t               cur_config;       /* Selected configuration */
    uint8_t               cur_interface;    /* Selected interface of current configuration */
    uint8_t               cur_alt;          /* Selected Alternate Setting of current
                                             interface*/

    uint16_t               sta_info;

    const am_usbd_interface_t *p_interface;    /**< \brief �������ӿ� */

    /** \brief ��׼�豸������ָ�������ָ��*/
    const am_std_request_t    *pfn_std_request;

    am_usb_request_funcs_t    *p_funcs;

    /** \brief USB device ��Ϣ�ṹ��, �����������Ϣ*/
    const am_usbd_devinfo_t   *p_info;

    /**< \brief ������ص�����, ��USB���б���ֵ*/
    am_usbd_class_req_cb_t    class_req;

    /**< \brief ��������ص��������ɾ���Ĳ��̶��幦�ܣ���֧�ֵ������ж�Ӧ�ӿ� */
    am_usbd_vendor_req_cb_t   vendor_req;

    /** \brief ���յ���setup���е�����USB��׼�豸����ṹ */
    am_usb_setup_t            setup_data;

    /** \brief �˵�״̬ */
    am_usbd_ep_info_t         endpoint_info[AM_USBD_MAX_EP_CNT];

    am_data_info_t            ctrl_info;
};

/*****************************************************************************
 * API
 ****************************************************************************/

am_static_inline
am_usb_status_t am_usbd_init(am_usbd_dev_t  *p_dev)
{
    return p_dev->p_interface->pfn_device_init(p_dev->ctrl_handle);
}

/**
 * \brief ��ʼ�� USB
 *
 * \param[in] handle                  usb�豸���
 *
 * \retval  AM_USB_STATUS_SUCCESS               ֪ͨ�ɹ�
 * \retval  AM_USB_STATUS_ERROR                 ֪ͨʧ��
 * \retval  AM_USB_STATUS_INVALID_REQUEST       USB ��Ӧ����
 * \retval  AM_USB_STATUS_INVALID_HANDLE        ��Ч�ľ��
 * \retval  AM_USB_STATUS_INVALID_PARAMETER     ��������
 */
am_static_inline
am_usb_status_t am_usbd_send(am_usbd_dev_t   *p_dev,
                             uint8_t          endpoint_address,
                             uint8_t         *buffer,
                             uint32_t         length)
{
    return p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle,
                                               endpoint_address,
                                               buffer,
                                               length);
}

/**
 * \brief USB��������
 *
 */
am_static_inline
uint8_t am_usbd_recv(am_usbd_dev_t   *p_dev,
                     uint8_t          endpoint,
                     uint8_t         *buffer,
                     uint32_t         length)
{
    return p_dev->p_interface->pfn_device_recv(p_dev->ctrl_handle,
                                               endpoint,
                                               buffer,
                                               length);
}

/**
 * \brief USB���ÿ�������
 *
 */
am_static_inline
am_usb_status_t am_usbd_control(am_usbd_dev_t         *p_dev,
                                am_usbd_control_type_t type,
                                void                  *param)
{
    return p_dev->p_interface->pfn_device_control(p_dev->ctrl_handle,
                                                  type,
                                                  param);
}


/**
 * \brief USBȡ������
 *
 */
am_static_inline
am_usb_status_t am_usbd_cancel(am_usbd_dev_t   *p_dev,
                               uint8_t          endpoint)
{
    return p_dev->p_interface->pfn_device_cancel(p_dev->ctrl_handle, endpoint);
}

/**
 * \brief USB���ʼ������
 *
 */
am_static_inline
am_usb_status_t am_usbd_deinit(am_usbd_dev_t   *p_dev)
{
    return p_dev->p_interface->pfn_device_deinit(p_dev->ctrl_handle);
}

am_static_inline
void am_usbd_protocol_stack_version(am_usb_version_t *p_usb)
{
	p_usb->major  = AM_USB_STACK_VERSION_MAJOR;
	p_usb->minor  = AM_USB_STACK_VERSION_MINOR;
	p_usb->bugfix = AM_USB_STACK_VERSION_BUGFIX;
}
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_DCI_H */
