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
 * \brief ZMF159 CAN �û������ļ�
 * \sa am_hwconf_zmf159_can.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "zmf159_periph_map.h"
#include "am_zmf159.h"
#include "zmf159_inum.h"
#include "am_gpio.h"
#include "am_zmf159_can.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_adc
 * \copydoc am_hwconf_zmf159_adc.c
 * @{
 */

#define MAX     10

/** \brief ADCƽ̨��ʼ�� */
static void __zmf159_plfm_can_init (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_CAN1_RX);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_CAN1_TX);
    am_clk_enable(CLK_CAN);
}

/** \brief ���ADCƽ̨��ʼ�� */
static void __zmf159_plfm_can_deinit (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_CAN1_RX);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_CAN1_TX);
    am_clk_disable (CLK_CAN);
}

static am_zmf159_can_intcb_info_t    __g_can_intcb_info[MAX];

/** \brief �豸��Ϣ */
static const am_zmf159_can_devinfo_t __g_can_devinfo = {

    ZMF159_CAN_BASE,                 /**< \brief ADC */
    INUM_CAN_RX1,                    /**< \brief ADC���жϱ�� */
    AMHW_ZMF159_CAN_BASIC_CAN,       /**< \brief ADCʱ�Ӻ� */
    __g_can_intcb_info,              /**< \brief �ο���ѹ */
    MAX,                             /**< \brief ת������ */

    __zmf159_plfm_can_init,          /**< \brief ADC1��ƽ̨��ʼ�� */
    __zmf159_plfm_can_deinit,        /**< \brief ADC1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_zmf159_can_dev_t  __g_can_dev;

/** \brief ADCʵ����ʼ�������ADC��׼������ */
am_can_handle_t am_zmf159_can_inst_init (void)
{
    return am_zmf159_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief ADCʵ�����ʼ�� */
void am_zmf159_can_inst_deinit (am_can_handle_t handle)
{
    am_zmf159_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */
