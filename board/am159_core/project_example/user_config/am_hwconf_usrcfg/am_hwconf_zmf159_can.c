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

/** \brief CANƽ̨��ʼ�� */
static void __zmf159_plfm_can_init (void)
{
    am_gpio_pin_cfg(PIOB_8, PIOB_8_CAN1_RX | PIOB_8_INPUT_FLOAT | PIOB_8_SPEED_50MHz);
    am_gpio_pin_cfg(PIOB_9, PIOB_9_CAN1_TX | PIOB_9_AF_PP | PIOB_9_SPEED_50MHz);

    am_clk_enable(CLK_CAN);
    am_clk_enable(CLK_SYSCFG);
}

/** \brief ���CANƽ̨��ʼ�� */
static void __zmf159_plfm_can_deinit (void)
{
    am_clk_disable (CLK_CAN);
}

static am_zmf159_can_intcb_info_t    __g_can_intcb_info[MAX];

/** \brief �豸��Ϣ */
static const am_zmf159_can_devinfo_t __g_can_devinfo = {

    ZMF159_CAN_BASE,                 /**< \brief CAN */
    INUM_CAN_RX1,                    /**< \brief CAN���жϱ�� */
	AMHW_ZMF159_CAN_PELI_CAN,        /**< \brief CANģʽ���� */
    __g_can_intcb_info,              /**< \brief �ص���Ϣ */
    MAX,                             /**< \brief �ص���Ϣ�ڴ��С*/
    __zmf159_plfm_can_init,          /**< \brief CAN1��ƽ̨��ʼ�� */
    __zmf159_plfm_can_deinit,        /**< \brief CAN1��ƽ̨ȥ��ʼ�� */

};

/**< \brief �豸ʵ�� */
static am_zmf159_can_dev_t  __g_can_dev;

/** \brief CANʵ����ʼ�������CAN��׼������ */
am_can_handle_t am_zmf159_can_inst_init (void)
{
    return am_zmf159_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief CANʵ�����ʼ�� */
void am_zmf159_can_inst_deinit (am_can_handle_t handle)
{
    am_zmf159_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */
