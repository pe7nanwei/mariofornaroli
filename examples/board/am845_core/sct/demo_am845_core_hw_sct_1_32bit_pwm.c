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
 * \brief SCT 32 λ PWM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 4kHz �� PWM��ռ�ձ�Ϊ 50%��
 *   2. PIO0_27(SCT_OUT4) ��� 4kHz �� PWM��ռ�ձ�Ϊ 25%��
 *   3. LED0 �� 0.2s ��ʱ������˸��
 *
 * \note
 *    1. SCT ʹ�� 32 λ��������ֻ�ܲ���һ������� PWM������ PWM ���ʹ��ͬһƵ�ʣ�
 *       �����������ƥ��ֵΪ 0xFFFFFFFF��
 *    2. SCT ʹ�� 16 λ�����������Բ��� 2 ������� PWM��ÿһ�� PWM �����ʹ��ͬһ
 *       Ƶ�ʣ������������ƥ��ֵΪ 0xFFFF��
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_sct_1_32bit_pwm.c src_am845_core_hw_sct_1_32bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-19  hgo, modified
 * - 1.00 15-07-13  oce, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_sct_1_32bit_pwm
 * \copydoc demo_am845_core_hw_sct_1_32bit_pwm.c
 */

/** [src_am845_core_hw_sct_1_32bit_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_sct_1_32bit_pwm_entry (void)
{
    uint32_t frq = 0;
  
    AM_DBG_INFO("demo am845_core 1_32bit hw pwm\r\n");

    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SCT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SCT);

    /* PIO0_23 ������ SCT �����ͨ�� 0��PIO0_27 ������ SCT �����ͨ�� 4 */
    am_gpio_pin_cfg(PIO0_23, PIO_FUNC_SCT_OUT0);
    am_gpio_pin_cfg(PIO0_27, PIO_FUNC_SCT_OUT4);

    AM_DBG_INFO("The demo for SCT output PWM:\r\n");
    AM_DBG_INFO("The PIO0_23(SCT_OUT0) PWM: freq is 4kHz, "
                "The duty ratio is 50%% \r\n");
    AM_DBG_INFO("The PIO0_27(SCT_OUT4) PWM: freq is 4kHz, "
                "The duty ratio is 25%% \r\n");

    frq = amhw_lpc84x_clk_system_clkrate_get();
    demo_lpc_hw_sct_1_32bit_pwm_entry(LPC84X_SCT0, frq);

}
/** [src_am845_core_hw_sct_1_32bit_pwm] */

/* end of file */
