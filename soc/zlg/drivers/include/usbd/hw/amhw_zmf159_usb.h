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
    __IO uint32_t per_id;        //0x00
    __IO uint32_t id_comp;
    __IO uint32_t rev;
    __I  uint32_t add_info;      /**< \brief ADD_INFO ƫ�ƣ�0x0c */
    __IO uint32_t otg_int_stat;  //0x10
    __IO uint32_t otg_int_en;    //0x14
    __IO uint32_t otg_status;    //0x18
    __IO uint32_t otg_ctrl;      //0x1c
    __I  uint32_t reserve0[24];  /**< \brief ����  */
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
    __I  uint32_t reserve1[2];   /**< \brief ����  */
    __IO uint32_t ep_ctl[16];    /**< \brief �˵���ƼĴ��� ƫ�ƣ�0xc0 ~ 0xfc */

}amhw_zmf159_usb_t;

typedef struct amhw_zmf159_bdt_data {
    __IO uint32_t format;
    __IO uint32_t adress;
} amhw_zmf159_bdt_data_t;

typedef struct amhw_zmf159_usb_bdt {
    amhw_zmf159_bdt_data_t rx_buf[2];
    amhw_zmf159_bdt_data_t tx_buf[2];
} amhw_zmf159_usb_bdt_t;

/**
 * \beief �жϱ�־
 */
#define  ZMF159_USB_INT_STAT_RST       (0x01)
#define  ZMF159_USB_INT_STAT_ERROR     (0x02)
#define  ZMF159_USB_INT_STAT_SOF_TOK   (0x04)
#define  ZMF159_USB_INT_STAT_TOK_DNE   (0x08)
#define  ZMF159_USB_INT_STAT_SLEEP     (0x10)
#define  ZMF159_USB_INT_STAT_RESUME    (0x20)
#define  ZMF159_USB_INT_STAT_ATTACH    (0x40)
#define  ZMF159_USB_INT_STAT_STALL     (0x80)

/**
 * \beief CTRL�Ĵ�������
 */
typedef enum amhw_zmf159_ctrl{
    ZMF159_USB_EN   = 0,
    ZMF159_USB_ODD_RST,
    ZMF159_USB_RESUME,
    ZMF159_USB_HOST_MODE_EN,
    ZMF159_USB_RESET,
    ZMF159_USB_TXD_SUSPEND_TOKBSY,
    ZMF159_USB_SE0,
    ZMF159_USB_SIE_RCV
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
 * \brief ��ȡ��������ַ
 */
am_static_inline
uint32_t amhw_zmf159_bdt_page_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint32_t)(p_hw_usb->bdt_page03 << 24) |
                     (p_hw_usb->bdt_page02 << 16) |
                     ((p_hw_usb->bdt_page01 >> 1) << 9);
}

/**
 * \brief ����USB��ַ
 */
am_static_inline
void amhw_zmf159_addr_set (amhw_zmf159_usb_t *p_hw_usb,
                           uint8_t            usb_addr)
{
//	am_kprintf("addr is %x \r\n", usb_addr);
    p_hw_usb->addr |= usb_addr ;
}

/**
 * \brief USB ctrl����
 */
am_static_inline
void amhw_zmf159_ctrl_set (amhw_zmf159_usb_t *p_hw_usb,
                           amhw_zmf159_ctrl_t ctrl)
{
    p_hw_usb->ctl |= 1 << ctrl;
}

/**
 * \brief USB ctrl����
 */
am_static_inline
void amhw_zmf159_ctrl_reset (amhw_zmf159_usb_t *p_hw_usb,
                             amhw_zmf159_ctrl_t ctrl)
{
    p_hw_usb->ctl &= ~(1 << ctrl);
}

/**
 * \brief �˵���ƼĴ�������
 */
am_static_inline
void amhw_zmf159_ep_ctrl_set (amhw_zmf159_usb_t *p_hw_usb,
                              uint8_t            epx,
                              uint8_t            dat)
{
    p_hw_usb->ep_ctl[epx] = dat;
}

/**
 * \brief �˵���������
 */
am_static_inline
void amhw_zmf159_ep_class_set (amhw_zmf159_usb_t *p_hw_usb,
                               uint8_t            epx,
                               uint8_t            dat)
{
    p_hw_usb->ep_ctl[epx] = dat << 2;
}

/**
 * \brief ����˵�HALT״̬ dat = 0 ����� dat= 1,����
 */
am_static_inline
void amhw_zmf159_ep_halt_set (amhw_zmf159_usb_t *p_hw_usb,
                              uint8_t            epx,
							  uint8_t            dat)
{
	if (dat == 0) {
        p_hw_usb->ep_ctl[epx] &= ~(1 << 1);  // �����
	} else if (dat == 1){
		p_hw_usb->ep_ctl[epx] |= (1 << 1);   // ����
	}
}


/**
 * \brief ����˵�HALT״̬
 */
am_static_inline
void amhw_zmf159_ep_enable (amhw_zmf159_usb_t *p_hw_usb,
                            uint8_t            epx)
{
    p_hw_usb->ep_ctl[epx] = 1 << 0;
}


/**
 * \brief ���ö˵�״̬
 */
am_static_inline
void amhw_zmf159_ep_stat_set (amhw_zmf159_usb_t *p_hw_usb,
                              uint8_t            epx,
                              am_bool_t          stat)
{
    p_hw_usb->ep_ctl[epx] &= ~((uint32_t)(stat & 0x01) << 1);
    p_hw_usb->ep_ctl[epx] |= (uint32_t)(stat & 0x01) << 1;
}

/**
 * \brief ��ȡ�˵�״̬
 */
am_static_inline
am_bool_t amhw_zmf159_ep_stat_get (amhw_zmf159_usb_t *p_hw_usb,
                                   uint8_t            epx)
{
    return (am_bool_t)((p_hw_usb->ep_ctl[epx] >> 1) & 0x01);
}

/**
 * \brief �����ж�ʹ��
 */
am_static_inline
void amhw_zmf159_usb_int_enable (amhw_zmf159_usb_t *p_hw_usb,
                                 uint32_t           flog)
{
    p_hw_usb->int_enb |= flog;
}

/**
 * \brief �����жϽ���
 */
am_static_inline
void amhw_zmf159_usb_int_disable (amhw_zmf159_usb_t *p_hw_usb,
                              uint32_t           flog)
{
    p_hw_usb->int_enb &= ~flog;
}

/**
 * \brief ���ж�״̬
 */
am_static_inline
uint8_t amhw_zmf159_usb_int_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)(p_hw_usb->int_stat & 0xff);
}

/**
 * \brief ����Ӧ�ж�
 */
am_static_inline
void amhw_zmf159_usb_int_clear (amhw_zmf159_usb_t *p_hw_usb,
                                uint32_t           flag)
{
    p_hw_usb->int_stat = flag;
}

/**
 * \brief ��USB״̬
 */
am_static_inline
uint8_t amhw_zmf159_usb_stat_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)(p_hw_usb->stat & 0xff);
}

/**
 * \brief ��ȡ�ж�������
 */
am_static_inline
uint8_t amhw_zmf159_usb_int_num_get (amhw_zmf159_usb_t *p_hw_usb)
{
    return (uint8_t)((p_hw_usb->add_info >> 3) & 0x1f);
}

/**
 * @}if_amhw_zmf159_usb
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_USB_H */

/* end of file */
