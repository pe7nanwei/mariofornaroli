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
 * \brief USB interfaces for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-26  ipk, first implementation
 * \endinternal
 */
#ifndef __AMHW_ZMF159_USB_H
#define __AMHW_ZMF159_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_types.h"
#include "zmf159_periph_map.h"

/**
 * \addtogroup amhw_zmf159_if_usb
 * \copydoc amhw_zmf159_usb.h
 * @{
 */

/**
 *  \brief USB �Ĵ����ṹ�嶨��
 */
typedef struct amhe_zmf159_usb{
    __I  uint32_t reserve0[3];   /**< \brief ����  */

    __I  uint16_t add_info;      /**< \brief ADD_INFO ƫ�ƣ�0x0c */
    __I  uint16_t reserve1;      /**< \brief ����  */

    __I  uint32_t reserve2[28];  /**< \brief ����  */

    __IO uint16_t int_stat;      /**< \brief �ж�״̬�Ĵ��� ƫ�ƣ�0x80 */
    __I  uint16_t reserve3;      /**< \brief ����  */

    __IO uint16_t int_enb;       /**< \brief �ж�ʹ�ܼĴ��� ƫ�ƣ�0x84 */
    __I  uint16_t reserve4;      /**< \brief ����  */

    __IO uint16_t err_stat;      /**< \brief �����жϼĴ��� ƫ�ƣ�0x88 */
    __I  uint16_t reserve5;      /**< \brief ����  */

    __IO uint16_t stat;          /**< \brief ״̬�Ĵ��� ƫ�ƣ�0x90 */
    __I  uint16_t reserve6;      /**< \brief ����  */

    __IO uint16_t ctl;           /**< \brief ���ƼĴ��� ƫ�ƣ�0x94 */
    __I  uint16_t reserve7;      /**< \brief ����  */

    __IO uint16_t addr;          /**< \brief ��ַ�Ĵ��� ƫ�ƣ�0x98 */
    __I  uint16_t reserve8;      /**< \brief ����  */

    __IO uint16_t bdt_page01;    /**< \brief buffer����ҳ�Ĵ���1 ƫ�ƣ�0x9c */
    __I  uint16_t reserve9;      /**< \brief ����  */

    __IO uint16_t frm_numl;      /**< \brief ������ּĴ��� ƫ�ƣ�0xa0 */
    __I  uint16_t reserve10;     /**< \brief ����  */

    __IO uint16_t frm_numh;      /**< \brief ������ּĴ��� ƫ�ƣ�0xa4 */
    __I  uint16_t reserve11;     /**< \brief ����  */

    __IO uint16_t token;         /**< \brief ָ��Ĵ��� ƫ�ƣ�0xa8 */
    __I  uint16_t reserve12;     /**< \brief ����  */

    __IO uint16_t sof_thld;      /**< \brief SOF�д��� ƫ�ƣ�0xac */
    __I  uint16_t reserve13;     /**< \brief ����  */

    __IO uint16_t bdt_page02;    /**< \brief buffer����ҳ�Ĵ���2 ƫ�ƣ�0xb0 */
    __I  uint16_t reserve14;     /**< \brief ����  */

    __IO uint16_t bdt_page03;    /**< \brief buffer����ҳ�Ĵ���3 ƫ�ƣ�0xb4 */
    __I  uint16_t reserve15;     /**< \brief ����  */

    __I  uint32_t reserve16[2];  /**< \brief ����  */

    struct {
        __IO uint16_t endpt;     /**< \brief �˵���ƼĴ��� ƫ�ƣ�0xc0 ~ 0xfc */
        __I  uint16_t reserve17; /**< \brief ����  */
    } endpt_n[16];

}amhw_zmf159_usb_t;

/**
 * \beief �ж�ʹ��
 */
typedef enum amhw_zmf159_int_enb{
    ZMF159_USB_RST   = 0,
    ZMF159_ERROR,
    ZMF159_SOF_TOK,
    ZMF159_TOK_DNE,
    ZMF159_SLEEP,
    ZMF159_RESUME,
    ZMF159_ATTACH,
    ZMF159_STALL,
} amhw_zmf159_int_enb_t;

//typedef enum amhw_zmf159_dev_stat{
//    ZMF159_MASTER_DEV      = 0,
//    ZMF159_SLAVE_DEV       = 1
//} amhw_zmf159_dev_stat_t;

/**
 * \brief �����ж�ʹ��
 */
am_static_inline
void amhw_zmf159_int_enable (amhw_zmf159_usb_t    *p_hw_usb,
                             amhw_zmf159_int_enb_t flog)
{
    p_hw_usb->int_enb |= (1 << flog);
}

/**
 * \brief �����жϽ���
 */
am_static_inline
void amhw_zmf159_int_disable (amhw_zmf159_usb_t    *p_hw_usb,
                              amhw_zmf159_int_enb_t flog)
{
    p_hw_usb->int_enb &= ~(1 << flog);
}

/**
 * \brief ���ж�״̬
 */
am_static_inline
uint8_t amhw_zmf159_int_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)(p_hw_usb->int_stat & 0xff);
}

/**
 * \brief ��ȡ�ж�������
 */
am_static_inline
uint8_t amhw_zmf159_int_num_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)((p_hw_usb->add_info >> 3) & 0x1f);
}

/**
 * \brief USB ʹ��
 */
am_static_inline
void amhw_zmf159_usb_enable (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl |= (1 << 0);
}

/**
 * \brief USB ����
 */
am_static_inline
void amhw_zmf159_usb_disable (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl &= ~(1 << 0);
}

/**
 * \brief ODD ����
 */
am_static_inline
void amhw_zmf159_odd_rest (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl |= (1 << 1);
}

/**
 * \brief USB-FS �ָ��ź�
 */
am_static_inline
void amhw_zmf159_usb_resume (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl |= (1 << 2);
}

/**
 * \brief ����USBΪ����ģʽ
 */
am_static_inline
void amhw_zmf159_host_mode_enable (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl |= (1 << 3);
}

/**
 * \brief USB ���� ��λ�źţ�������ģʽ�£�
 */
am_static_inline
void amhw_zmf159_usb_reset_start (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl |= (1 << 4);
}

/**
 * \brief USB ������λ�źţ�������ģʽ�£�
 */
am_static_inline
void amhw_zmf159_usb_reset_end (amhw_zmf159_usb_t *p_hw_usb)
{
    p_hw_usb->ctl &= ~(1 << 4);
}

/**
 * \brief USB ��ȡ״̬�Ĵ���
 */
am_static_inline
uint8_t amhw_zmf159_usb_stat_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)(p_hw_usb->stat);
}

/**
 * @}if_amhw_zmf159_usb
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_USB_H */

/* end of file */
