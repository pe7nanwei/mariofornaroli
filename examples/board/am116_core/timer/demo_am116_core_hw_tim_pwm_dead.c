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
 * \brief ��ʱ��������ʱ��Ļ��� PWM ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_8(TIM1_CH1) �� PIOA_7(TIM1_CH1N) ������� PWM��Ƶ��Ϊ 100KHz��
 *      ռ�ձ�Ϊ 40%������ʱ��Ϊ 100ns��
 *
 * \par Դ����
 * \snippet demo_am116_core_hw_tim_pwm_dead.c src_am116_core_hw_tim_pwm_dead
 *
 * \internal
 * \par Modification history
 * - 1.00 18-06-06  pea, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_am116_core_hw_tim_pwm_dead
 * \copydoc demo_am116_core_hw_tim_pwm_dead.c
 */

/** [src_am116_core_hw_tim_pwm_dead] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "am_zlg116_clk.h"
#include "am_zlg_tim_pwm.h"
#include "demo_zlg_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_hw_tim_pwm_dead_entry (void)
{
    AM_DBG_INFO("demo am116_core hw tim pwm dead!\r\n");

    /* �������Ź��� */
    am_gpio_pin_cfg(PIOA_7, PIOA_7_TIM1_CH1N | PIOA_7_AF_PP);
    am_gpio_pin_cfg(PIOA_8, PIOA_8_TIM1_CH1 | PIOA_8_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ��ʱ�� */
    am_zlg116_clk_reset(CLK_TIM1);

    demo_zlg_hw_tim_pwm_dead_entry(ZLG116_TIM1,
                                   AMHW_ZLG_TIM_TYPE0,
                                   AM_ZLG_TIM_PWM_CH1,
                                   am_clk_rate_get(CLK_TIM1));
}
/** [src_am116_core_hw_tim_pwm_dead] */

/* end of file */
