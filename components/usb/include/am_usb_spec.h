/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_SPEC_H
#define __AM_USB_SPEC_H

#include "am_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* USB speed */
#define AM_USB_SPEED_FULL (0x00U)
#define AM_USB_SPEED_LOW  (0x01U)
#define AM_USB_SPEED_HIGH (0x02U)

/* USB �˵�����
 * @{
 */
#define AM_USB_ENDPOINT_CONTROL                      (0x00U)
#define AM_USB_ENDPOINT_ISOCHRONOUS                  (0x01U)
#define AM_USB_ENDPOINT_BULK                         (0x02U)
#define AM_USB_ENDPOINT_INTERRUPT                    (0x03U)
/*}@*/

/* USB���䷽�� */
#define AM_USB_OUT   (0U)
#define AM_USB_IN    (1U)

/* USB ������������ */
#define AM_USB_DESC_LENGTH_DEVICE              (0x12U)
#define AM_USB_DESC_LENGTH_CONFIGURE           (0x09U)
#define AM_USB_DESC_LENGTH_INTERFACE           (0x09U)
#define AM_USB_DESC_LENGTH_HID                 (0x09U)
#define AM_USB_DESC_LENGTH_ENDPOINT            (0x07U)
#define AM_USB_DESC_LENGTH_ALL(x)        \
		(AM_USB_DESC_LENGTH_CONFIGURE +  \
		 AM_USB_DESC_LENGTH_INTERFACE +  \
		 (x * AM_USB_DESC_LENGTH_ENDPOINT))

#define AM_USB_DESC_LENGTH_DEVICE_QUALITIER    (0x0AU)

/* USB ���������� */
#define AM_USB_DESC_TYPE_DEVICE                (0x01U)        /* �豸������. */
#define AM_USB_DESC_TYPE_CONFIGURE             (0x02U)        /* ������������. */
#define AM_USB_DESC_TYPE_STRING                (0x03U)        /* �ַ���������. */
#define AM_USB_DESC_TYPE_INTERFACE             (0x04U)        /* �ӿ������� */
#define AM_USB_DESC_TYPE_ENDPOINT              (0x05U)        /* �˵�������.  */
#define AM_USB_DESC_TYPE_DEVICE_QUALITIER      (0x06U)
#define AM_USB_DESC_TYPE_OTHER_SPEED_CONFIG    (0x07U)
#define AM_USB_DESC_TYPE_INTERFAACE_POWER      (0x08U)
#define AM_USB_DESC_TYPE_OTG                   (0x09U)
#define AM_USB_DESC_TYPE_INTERFACE_ASSOC       (0x0BU)

#define AM_USB_DESC_TYPE_HID                   (0x21U)     /* �˻��ӿ���������. */
#define AM_USB_DESC_TYPE_HID_REPORT            (0x22U)     /* ���������� */
#define AM_USB_DESC_TYPE_HID_PHY               (0x23U)     /* ʵ�������� */

/* USB ��׼�������� */
#define AM_USB_REQ_TYPE_DIR_MASK                 (0x80U)
#define AM_USB_REQ_TYPE_DIR_SHIFT                (7U)
#define AM_USB_REQ_TYPE_DIR_OUT                  (0x00U)
#define AM_USB_REQ_TYPE_DIR_IN                   (0x80U)

#define AM_USB_REQ_TYPE_MASK                     (0x60U)
#define AM_USB_REQ_TYPE_SHIFT                    (5U)
#define AM_USB_REQ_TYPE_STANDARD                 (0U)
#define AM_USB_REQ_TYPE_CLASS                    (0x20U)
#define AM_USB_REQ_TYPE_VENDOR                   (0x40U)

#define AM_USB_REQ_TYPE_RECIPIENT_MASK           (0x1FU)
#define AM_USB_REQ_TYPE_RECIPIENT_SHIFT          (0U)
#define AM_USB_REQ_TYPE_RECIPIENT_DEVICE         (0x00U)
#define AM_USB_REQ_TYPE_RECIPIENT_INTERFACE      (0x01U)
#define AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT       (0x02U)
#define AM_USB_REQ_TYPE_RECIPIENT_OTHER          (0x03U)

/* USB ��׼���� */
#define AM_USB_REQ_STANDARD_GET_STATUS           (0x00U)
#define AM_USB_REQ_STANDARD_CLEAR_FEATURE        (0x01U)
#define AM_USB_REQ_STANDARD_SET_FEATURE          (0x03U)
#define AM_USB_REQ_STANDARD_SET_ADDRESS          (0x05U)
#define AM_USB_REQ_STANDARD_GET_DESCRIPTOR       (0x06U)
#define AM_USB_REQ_STANDARD_SET_DESCRIPTOR       (0x07U)
#define AM_USB_REQ_STANDARD_GET_CONFIGURATION    (0x08U)
#define AM_USB_REQ_STANDARD_SET_CONFIGURATION    (0x09U)
#define AM_USB_REQ_STANDARD_GET_INTERFACE        (0x0AU)
#define AM_USB_REQ_STANDARD_SET_INTERFACE        (0x0BU)
#define AM_USB_REQ_STANDARD_SYNCH_FRAME          (0x0CU)

/* USB ��׼�������û�������� */
#define AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT        (0U)
#define AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP (1U)
#define AM_USB_REQ_STA_FEATURE_DEVICE_TEST_MODE     (2U)

/* USB �������������� */
#define AM_USB_DESC_CONFIG_ATTR_D7_MASK                 (0x80U)
#define AM_USB_DESC_CONFIG_ATTR_D7_SHIFT                (7U)

#define AM_USB_DESC_CONFIG_ATTR_SELF_POWERED_MASK       (0x40U)
#define AM_USB_DESC_CONFIG_ATTR_SELF_POWERED_SHIFT      (6U)

#define AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_MASK      (0x20U)
#define AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_SHIFT     (5U)

/* USB �˵����� */
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK             (0x80U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_SHIFT            (7U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_OUT              (0U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_IN               (0x80U)

#define AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK          (0x0FU)
#define AM_USB_DESC_ENDPOINT_ADDR_NUMBER_SHFIT         (0U)

#define AM_USB_DESC_ENDPOINT_ATTR_TYPE_MASK            (0x03U)
#define AM_USB_DESC_ENDPOINT_ATTR_NUMBER_SHFIT         (0U)

#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_MASK       (0x0CU)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_SHFIT      (2U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_NSYNC      (0x00U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_ASYNC      (0x04U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_ADAPT      (0x08U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_SYNC       (0x0CU)

#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_MASK           (0x30U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_SHFIT          (4U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_DATA           (0x00U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_FEEDBACK       (0x10U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_IFEEDBACK_DATA (0x20U)

#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MASK              (0x07FFu)
#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MULT_TRANS_MASK   (0x1800u)
#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MULT_TRANS_SHFIT  (11U)

/* Set up ���ṹ */
typedef struct am_usb_setup {
    uint8_t  bm_request_type;        /**<\brief �������� */
    uint8_t  b_request;              /**<\brief �������*/
    uint16_t w_value;                /**<\brief ��ǰ����Ĳ���*/
    uint16_t w_index;                /**<\brief �ӿڻ��߶˵�����*/
    uint16_t w_length;               /**<\brief ���ݹ�������Ҫ������ֽ���*/
} am_usb_setup_t;

typedef struct am_usb_descriptor_dev {
    uint8_t b_length;                /**<\brief �������ֽ��� */
    uint8_t b_descriptor_type;       /**<\brief ����������  */
    uint8_t bcd_usb[2];              /**<\brief USB�汾��(BCD��) */
    uint8_t b_device_class;          /**<\brief �豸�� ��*/
    uint8_t b_device_sub_class;      /**<\brief �豸������ */
    uint8_t b_device_protocol;       /**<\brief �豸Э���� */
    uint8_t bmax_packet_size0;       /**<\brief �˵�0������С */
    uint8_t id_vendor[2];            /**<\brief ���̱�ʶ����USB-IF��֯��ֵ�� */
    uint8_t id_product[2];           /**<\brief ��Ʒ��� */
    uint8_t bcd_device[2];           /**<\brief �豸�汾�� */
    uint8_t i_manufacturer;          /**<\brief ������Ϣ�ַ�������������ֵ */
    uint8_t i_product;               /**<\brief ��Ʒ��Ϣ�ַ�������������ֵ */
    uint8_t i_serial_number;         /**<\brief ������Ϣ�ַ�������������ֵ�豸���к���Ϣ������ֵ */
    uint8_t b_num_configurations;    /**<\brief ������������Ŀ */
} am_usb_descriptor_dev_t;

typedef struct am_usb_descriptor_config {
    uint8_t b_length;                /**<\brief ����������ĳ��� */
    uint8_t b_descriptor_type;       /**<\brief �������������� */
    uint8_t w_total_length[2];       /**<\brief ������Ϣ���ܳ� */
    uint8_t b_num_interfaces;        /**<\brief ����֧�ֵĽӿ� */
    uint8_t b_configuration_value;   /**<\brief ����ֵ */
    uint8_t i_configuration;         /**<\brief ������ֵ���ַ������� */
    uint8_t bm_attributes;           /**<\brief �������� */
    uint8_t b_max_power;             /**<\brief ���õ�����2mAΪһ����λ�� */
} am_usb_descriptor_config_t;

typedef struct am_usb_descriptor_interface {
    uint8_t b_length;                /**< \brief �ӿ����������ֽڴ�С */
    uint8_t b_descriptor_type;       /**< \brief �ӿ������������ͱ�� */
    uint8_t b_interface_number;      /**< \brief �ӿڱ�� */
    uint8_t b_alternate_setting;     /**< \brief �ӿ��������ı�� */
    uint8_t b_num_endpoints;         /**< \brief �˵������������˵�0�� */
    uint8_t b_interface_class;       /**< \brief �ӿ��� */
    uint8_t b_interface_sub_class;   /**< \brief �ӿ����� */
    uint8_t b_interface_protocol;    /**< \brief �ӿ�Э�� */
    uint8_t i_interface;             /**< \brief �ýӿڵ��ַ�������ֵ */
} am_usb_descriptor_interface_t;


typedef struct am_usb_hid_descriptor
{
    uint8_t b_length;                /**< \brief HID��������С */
    uint8_t b_descriptor_type;       /**< \brief ����������*/
    uint8_t bcd_hid[2];              /**< \brief HID�汾��*/
    uint8_t b_country_code;          /**< \brief ��ʾ����Ӳ���Ĺ��Ҵ���*/
    uint8_t b_num_descriptors;       /**< \brief ����������(������һ����������������)*/
    uint8_t b_hid_descriptor_type;   /**< \brief ��������������*/
    uint8_t w_descriptor_length[2];  /**< \brief �����������ܴ�С*/
} am_usb_hid_descriptor_t;

typedef struct am_usb_descriptor_endpoint {
    uint8_t b_length;                /**<\brief �˵��������ֽ�����С */
    uint8_t b_descriptor_type;       /**<\brief �˵������������ͱ��*/
    uint8_t b_endpoint_address;      /**<\brief �˵��ַ���䷽��*/
    uint8_t bm_attributes;           /**<\brief �˵㴫������*/
    uint8_t wmax_packet_size[2];     /**<\brief �˵����Ĵ������С*/

    /**
     * \brief �ö˵㱻�����ķ�������
     * �����˸ö˵㱻�������ʵ����ڣ�����ֵ������������Ϳ��ƴ���������塣����ͬ�����䣬��ֵ����Ϊ 1��
     * �� 1ms Ϊ��׼��ͬ��֡���ڡ������жϴ��䣬��ֵΪ1~255���� 1ms~255ms
     */
    uint8_t b_interval;
} am_usb_descriptor_endpoint_t;

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_SPEC_H */
