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
 * \brief ��ʱ�� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_0(TIM2_CH1) ��� 4KHz �� PWM��ռ�ձ�Ϊ 50%��
 *
 * \par Դ����
 * \snippet demo_zmf159_core_hw_tim_pwm.c src_zmf159_core_hw_tim_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_zmf159_core_hw_tim_pwm
 * \copydoc demo_zmf159_core_hw_tim_pwm.c
 */

/** [src_zmf159_core_hw_tim_pwm] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "zmf159_inum.h"
#include "am_zmf159_clk.h"
#include "am_zlg_tim_pwm.h"
#include "demo_zlg_entries.h"

/**
 * \brief �������
 */
void demo_zmf159_core_hw_tim_pwm_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw tim pwm!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP | PIOA_0_SPEED_50MHz);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λ��ʱ�� */
    am_zmf159_clk_reset(CLK_TIM2);

    demo_zlg_hw_tim_pwm_entry(ZMF159_TIM2,
                              AMHW_ZLG_TIM_TYPE1,
                              AM_ZLG_TIM_PWM_CH1,
                              am_clk_rate_get(CLK_TIM2),
                              INUM_TIM2);
}
/** [src_zmf159_core_hw_tim_pwm] */

/* end of file */
