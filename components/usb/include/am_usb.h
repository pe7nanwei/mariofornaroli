/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_H
#define __AM_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_usb_osa.h"
#include "am_usb_misc.h"
/*!
 * @addtogroup usb_drv
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** \brief ����USBЭ��ջ���汾�� */
#define AM_USB_STACK_VERSION_MAJOR  (1U)
/** \brief ����USBЭ��ջ���汾�� */
#define AM_USB_STACK_VERSION_MINOR  (1U)
/** \brief ����USBЭ��ջ�޸��汾�� */
#define AM_USB_STACK_VERSION_BUGFIX (0U)

#define AM_USB_VERSION              0x0110

/** \brief USB Э��ջ�汾������ */
#define AM_USB_MAKE_VERSION(major, minor, bugfix) \
                     (((major) << 16) | ((minor) << 8) | (bugfix))

/** \brief USB������ */
typedef enum am_usb_status {
    AM_USB_STATUS_SUCCESS = 0x00U,              /**< \brief Success */
    AM_USB_STATUS_ERROR,                        /**< \brief Failed */

    AM_USB_STATUS_BUSY,                         /**< \brief æ״̬ */
    AM_USB_STATUS_INVALID_HANDLE,               /**< \brief handle ���� */
    AM_USB_STATUS_INVALID_PARAMETER,            /**< \brief �������� */
    AM_USB_STATUS_INVALID_REQUEST,              /**< \brief ��Ӧ���� */
    AM_USB_STATUS_CONTROLLER_NOT_FOUND,         /**< \brief ���ƽӿ��޷��ҵ� */
    AM_USB_STATUS_INVALID_CONTROLLER_INTERFACE, /**< \brief �Ƿ��ӿ� */

    AM_USB_STATUS_NOT_SUPPORTED,                /**< \brief ��֧�� */
    AM_USB_STATUS_RETRY,                        /**< \brief ���� */
    AM_USB_STATUS_TRANSFER_STALL,               /**< \brief �˿����� */
    AM_USB_STATUS_TRANSFER_FAILED,              /**< \brief ����ʧ�� */
    AM_USB_STATUS_ALLOC_FAIL,                   /**< \brief ����ʧ�� */
    AM_USB_STATUS_LACK_SWAP_BUFFER,             /**< \brief Insufficient swap buffer for KHCI */
    AM_USB_STATUS_TRANSFER_CANCEL,              /**< \brief ����ȡ�� */
    AM_USB_STATUS_BAND_WIDTH_FAIL,              /**< \brief �������ʧ�� */
    AM_USB_STATUS_MSD_STATUS_FAIL,              /**< \brief For MSD, the CSW status means fail */
} am_usb_status_t;

/** \brief USB host handle type define */
typedef void *am_usbh_handle_t;

/** \brief USB device handle type define. */
typedef void *am_usbd_handle_t;

/** \brief USB OTG handle type define */
typedef void *am_usb_otg_handle;

/**
* \brief USBЭ��汾����
*/
typedef struct am_usb_version {
    uint8_t major;  /**< \brief ���汾�� */
    uint8_t minor;  /**< \brief ���汾�� */
    uint8_t bugfix; /**< \brief �޸��汾�� */
} am_usb_version_t;

/*! @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_H */
