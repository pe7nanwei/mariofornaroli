/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB DEVICE����
 *
 * \internal
 * \par Modification History
 * - 1.00 19-03-07  adw, first implementation.
 * \endinternal
 */

#ifndef __AM_ZMF159_USBD_H_
#define __AM_ZMF159_USBD_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "am_usb_dci.h"
#include "amhw_zmf159_usb.h"

#define  AM_ZMF159MAX_EP_NUM      7



/**
 * \brief
 */
typedef struct am_zmf159_usbd_devinfo{
    uint32_t usb_regbase;          /**< \brief usb ����ַ*/

    int inum;                      /**< \brief �жϺ� */

    void (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������  */

    void (*pfn_plfm_deinit)(void); /**< \brief ƽ̨ȥ��ʼ������ */

    const am_usbd_devinfo_t *p_devinfo;

}am_zmf159_usbd_devinfo_t;


typedef struct am_zmf159_usbd_dev am_zmf159_usbd_dev_t;

/**
 * \brief zlg USBD device structure
 */
struct am_zmf159_usbd_dev {
    /**< \brief Device handle used to identify the device object belongs to */
    am_usbd_dev_t  device;

    /**< \brief �ж�״̬
     *          D7��STALL
     *          D6��ATTACH �����ж�
     *          D5�����߻���y
     *          D4��SLEEP
     *          D3��TOK_DNE
     *          D2��SOF
     *          D1: �����ж�
     *          D0�����߸�λ����
     */
    uint8_t int_stat;


    // ҳ��ַ
    amhw_zmf159_usb_bdt_t *p_usb_bdt;

    uint8_t     int_ep;    // �ж϶˵��

//    // device info
//    uint8_t Current_Feature;
//    uint8_t Current_Configuration;   /* Selected configuration */
//    uint8_t Current_Interface;       /* Selected interface of current configuration */
//    uint8_t Current_AlternateSetting;/* Selected Alternate Setting of current
//                                       interface*/
//    // ep info
//    uint16_t  Usb_wLength;
//    uint16_t  Usb_wOffset;
//    uint16_t  PacketSize;
//    uint8_t   *(*CopyData)(uint16_t Length);

    // ֧�����˵���
    uint8_t max_ep_num;


//    /**< \brief �豸��Ϣ�ṹָ�� */
    const am_zmf159_usbd_devinfo_t         *p_info;
};



///*******************************************************************************
//   �ⲿ��������
//*******************************************************************************/


am_usbd_dev_t *am_zmf159_usbd_init (am_zmf159_usbd_dev_t           *p_dev,
                                      const am_zmf159_usbd_devinfo_t *p_info);

void am_zmf159_usbd_deinit (const am_zmf159_usbd_devinfo_t *p_info);

/**
 * @} mm32_if_usbd
 */

#ifdef __cplusplus
}
#endif







#endif /* __AM_ZMF159_USBD_H_ */

/* end of file */
