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
    __I  uint32_t add_info;      /**< \brief ADD_INFO ƫ�ƣ�0x0c */
    __I  uint32_t reserve2[28];  /**< \brief ����  */
    __IO uint32_t int_stat;      /**< \brief �ж�״̬�Ĵ��� ƫ�ƣ�0x80 */
    __IO uint32_t int_enb;       /**< \brief �ж�ʹ�ܼĴ��� ƫ�ƣ�0x84 */
    __IO uint32_t err_stat;      /**< \brief �����жϼĴ��� ƫ�ƣ�0x88 */
    __IO uint32_t err_enb;       /**< \brief �����жϼĴ��� ƫ�ƣ�0x8C */
    __IO uint32_t stat;          /**< \brief ״̬�Ĵ��� ƫ�ƣ�0x90 */
    __IO uint32_t ctl;           /**< \brief ���ƼĴ��� ƫ�ƣ�0x94 */
    __IO uint32_t addr;          /**< \brief ��ַ�Ĵ��� ƫ�ƣ�0x98 */
    __IO uint32_t bdt_page01;    /**< \brief buffer����ҳ�Ĵ���1 ƫ�ƣ�0x9c */
    __IO uint32_t frm_numl;      /**< \brief ������ּĴ��� ƫ�ƣ�0xa0 */
    __IO uint32_t frm_numh;      /**< \brief ������ּĴ��� ƫ�ƣ�0xa4 */
    __IO uint32_t token;         /**< \brief ָ��Ĵ��� ƫ�ƣ�0xa8 */
    __IO uint32_t sof_thld;      /**< \brief SOF�д��� ƫ�ƣ�0xac */
    __IO uint32_t bdt_page02;    /**< \brief buffer����ҳ�Ĵ���2 ƫ�ƣ�0xb0 */
    __IO uint32_t bdt_page03;    /**< \brief buffer����ҳ�Ĵ���3 ƫ�ƣ�0xb4 */
    __I  uint32_t reserve17[2];  /**< \brief ����  */
    __IO uint32_t endpt[16];     /**< \brief �˵���ƼĴ��� ƫ�ƣ�0xc0 ~ 0xfc */

}amhw_zmf159_usb_t;

typedef struct amhw_zmf159_bdt_data {
    __IO uint32_t format;
    __IO uint32_t address;
} amhw_zmf159_bdt_data_t;

typedef struct amhw_zmf159_usb_bdt {
    amhw_zmf159_bdt_data_t rx_buf[2];
    amhw_zmf159_bdt_data_t tx_buf[2];
} amhw_zmf159_usb_bdt_t;

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

/**
 * \beief CTRL�Ĵ�������
 */
typedef enum amhw_zmf159_ctrl{
    ZMF159_USB_EN   = 0,
    ZMF159_ODD_RST,
    ZMF159_RESUME,
    ZMF159_TOK_DNE,
    ZMF159_SLEEP,
    ZMF159_RESUME,
    ZMF159_ATTACH,
    ZMF159_STALL,
} amhw_zmf159_ctrl_t;

/**
 * \brief ������������ַ
 */
am_static_inline
void amhw_zmf159_bdt_page_set (amhw_zmf159_usb_t *p_hw_usb,
                               uint32_t           addr)
{
    p_hw_usb->bdt_page03 = (addr >> 24) & 0xff;
    p_hw_usb->bdt_page02 = (addr >> 16) & 0xff;
    p_hw_usb->bdt_page01 = ((addr >> 9) & 0xff) << 1;
}

/**
 * \brief ����USB��ַ
 */
am_static_inline
void amhw_zmf159_addr_set (amhw_zmf159_usb_t *p_hw_usb,
                           uint8_t            usb_addr)
{
    p_hw_usb->addr = (p_hw_usb->addr & ~0xef) | (usb_addr & 0xef);
}

/**
 * \brief USB ctrl����
 */
am_static_inline
void amhw_zmf159_ctrl_set (amhw_zmf159_usb_t *p_hw_usb,
                           amhw_zmf159_ctrl_t ctrl,
                           am_bool_t          flag)
{
    (flag) ? (p_hw_usb->ctl |= (1 << ctrl)) : (p_hw_usb->ctl &= ~(1 << ctrl));
}

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
 * \brief USB ��ȡ��ǰBDT���µĶ˵�
 */
am_static_inline
uint8_t amhw_zmf159_usb_bdt_ep_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)((p_hw_usb->stat >> 4) & 0x0f);
}


/**
 * @}if_amhw_zmf159_usb
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_USB_H */

/* end of file */
