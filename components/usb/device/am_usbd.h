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
 * \brief USBD
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_H
#define __AM_USBD_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"
#include "am_usb.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**< \brief ������������ */
#define AM_USBD_CTRL_SETUP    0x00
#define AM_USBD_CTRL_IN       0x01
#define AM_USBD_CTRL_OUT      0x02
#define AM_USBD_CTRL_IDLE     0xFF


/** \brief �豸�Ƿ�֧���Թ��� (0:��֧�֣�1:֧��)*/
#define AM_USBD_CONFIG_SELF_POWER                ((0x80) | (1 << 6U))
#define AM_USBD_CONFIG_NOT_SELF_POWER            ((0x80) | (0 << 6U))

/** \brief �豸�Ƿ�֧��Զ�̻��ѹ���(0:��֧�֣�1:֧��) */
#define AM_USBD_CONFIG_REMOTE_WAKEUP             ((0x80) | (1 << 5U))
#define AM_USBD_CONFIG_NOT_REMOTE_WAKEUP         ((0x80) | (0 << 5U))


#define AM_USBD_SPECIFIC_BCD_VERSION             (0x0200U)
#define AM_USBD_DEMO_BCD_VERSION                 (0x0101U)

#define AM_USBD_CLASS                            (0x00U)
#define AM_USBD_SUBCLASS                         (0x00U)
#define AM_USBD_PROTOCOL                         (0x00U)
#define AM_USBD_MAX_POWER                        (0x32U)

/**< \brief ֧�ֵ����˵���� */
#define AM_USBD_MAX_EP_CNT                       (10)

/**< \brief һ�����շ�������ֽڸ��� */
#define AM_USBD_MAX_EP_DATA_CNT                  (64U)

/**< \brief �˵�����*/
#define AM_USBD_ENDPOINT_NUMBER_MASK             (0x0FU)

/** \brief ��ȡ/����״̬���� */
typedef enum am_usbd_status {
    AM_USBD_STATUS_TEST_MODE = 1U, /**< \brief ����ģʽ״̬ */
    AM_USBD_STATUS_SPEED,          /**< \brief ��ǰ�ٶ�״̬ */
    AM_USBD_STATUS_OTG,            /**< \brief OTG ״̬ */
    AM_USBD_STATUS_DEVICE,         /**< \brief �豸״̬ */
    AM_USBD_STATUS_ENDPOINT,       /**< \brief �˵��豸״̬ */
    AM_USBD_STATUS_DEVICE_STATE,   /**< \brief �豸״̬ */
    AM_USBD_STATUS_ADDRESS,        /**< \brief �豸��ַ״̬ */
    AM_USBD_STATUS_SYNCH_FRAME,    /**< \brief ��ǰ֡״̬ */
    AM_USBD_STATUS_BUS,            /**< \brief ����״̬ */
} am_usbd_status_t;

/** \brief USB 2.0 �豸״̬���� */
typedef enum am_usbd_state {
    AM_USBD_STATE_CONFIGURED = 0U, /**< \brief �豸״̬, ���� */
    AM_USBD_STATE_ADDRESS,         /**< \brief �豸״̬, ��ַ */
    AM_USBD_STATE_DEFAULT,         /**< \brief �豸״̬, Ĭ��*/
    AM_USBD_STATE_ADDRESSING,      /**< \brief �豸״̬, ��ַ���� */
    AM_USBD_STATE_TEST_MODE,       /**< \brief �豸״̬, ����ģʽ */
} am_usbd_state_t;


/** \brief �豸�ص��¼����� */
typedef enum am_usbd_event {
    AM_USBD_EVENT_BUS_RESET = 1U,                  /**< \brief ��⵽USB���߸�λ�ź�  */
    AM_USBD_EVENT_SUSPEND,                         /**< \brief ��⵽USB������ͣ�ź� */
    AM_USBD_EVENT_RESUME,                          /**< \brief ��⵽USB���߻ָ��ź� */
    AM_USBD_EVENT_ERROR,                           /**< \brief �����Ϸ����˴��� */
    AM_USBD_EVENT_DETACH,                          /**< \brief USB �豸�������жϿ��� */
    AM_USBD_EVENT_ATTACH,                          /**< \brief USB �豸���������� */
    AM_USBD_EVENT_SET_CONFIGURATION,               /**< \brief �������� */
    AM_USBD_EVENT_SET_INTERFACE,                   /**< \brief ���ýӿ�  */

    AM_USBD_EVENT_GET_DEVICE_DESCRIPTOR,           /**< \brief ��ȡ�豸���� */
    AM_USBD_EVENT_GET_CONFIGURATION_DESCRIPTOR,    /**< \brief ��ȡ�������� */
    AM_USBD_EVENT_GET_STRING_DESCRIPTOR,           /**< \brief ��ȡ�ַ������� */
    AM_USBD_EVENT_GET_HID_DESCRIPTOR,              /**< \brief ��ȡ HID ���� */
    AM_USBD_EVENT_GET_HID_REPORT_DESCRIPTOR,       /**< \brief ��ȡ HID �������� */
    AM_USBD_EVENT_GET_HID_PHYSICAL_DESCRIPTOR,     /**< \brief ��ȡ HID �������� */
    AM_USBD_EVENT_GET_DEVICE_QUALIFIER_DESCRIPTOR, /**< \brief ��ȡ �豸�������� */
    AM_USBD_EVENT_VENDOR_REQUEST,                  /**< \brief ��Ӧ������ */
    AM_USBD_EVENT_SET_REMOTE_WAKEUP,               /**< \brief ʹ��/��ֹԶ�˻��ѹ��� */
    AM_USBD_EVENT_GET_CONFIGURATION,               /**< \brief ��ȡ��ǰ�������� */
    AM_USBD_EVENT_GET_INTERFACE,                   /**< \brief ��ȡ��ǰ���ýӿ�ֵ */
} am_usbd_event_t;


/**
 * \brief �˵��ʼ���ṹ
 * �ýṹ����Գ�ʼ���˵���Ϣ����Ϊam_usbd_control �Ĳ�������
 */
typedef struct am_usbd_endpoint_init {
    uint8_t  endpoint_address;     /**< \brief �˵��ַ */
    uint8_t  transfer_type;        /**< \brief �˵㴫������ */
    uint16_t max_packet_size;      /**< \brief �˵�������С */
} am_usbd_endpoint_init_t;

/**
 * \brief �˵�״̬�ṹ
 * �ýṹ����Գ�ʼ���˵���Ϣ����Ϊam_usbd_control �Ĳ�������
 */
typedef struct am_usbd_ep_status {
    uint8_t  endpoint_address;     /**< \brief �˵��ַ */
    uint16_t endpoint_status;      /**< \brief �˵�״̬ : ����  or ���� */
} am_usbd_ep_status_t;

typedef struct am_usbd_descriptor {
    uint16_t  desc_wValue;             /* ��8λΪ���������ͣ���8λΪ��������� */
    uint16_t  desc_size;               /* ��������С */
    const uint8_t  *p_desc;            /* ���������� */
}am_usbd_descriptor_t;

#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_H */

/* end of file */
