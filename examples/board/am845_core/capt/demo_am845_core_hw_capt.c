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
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� LED1 �� 0.5s ��ʱ������˸��
 *
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_capt.c src_am845_core_hw_capt
 *
 * - �������裺
 *   1. PIO0_31  ���ӵ��ݴ������� CAPTX0��
 *   2. PIO1_0   ���ӵ��ݴ������� CAPTX1��
 *   3. PIO1_1   ���ӵ��ݴ������� CAPTX2��
 *   3. PIO0_30  ����ģ��Ƚ�ACMP��
 *
 * * - ʵ������
 *   1. ���ִ���ACMP�� ��CAPTX0ʱ����ӡX0�Ĵ�������ֵΪ4095��yestouch��ʼ������notouchֹͣ������
 *   1. ���ִ���ACMP�� ��CAPTX1ʱ����ӡX1�Ĵ�������ֵΪ4095��yestouch��ʼ������notouchֹͣ������
 *   1. ���ִ���ACMP�� ��CAPTX2ʱ����ӡX2�Ĵ�������ֵΪ4095��yestouch��ʼ������notouchֹͣ������
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-27  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_capt
 * \copydoc demo_am845_core_hw_capt.c
 */

/** [src_am845_core_hw_capt] */
#include "ametal.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "lpc84x_periph_map.h"
#include "lpc84x_pin.h"

extern void demo_lpc84x_hw_capt_entry (amhw_lpc84x_capt_t *p_hw_capt,
                                       amhw_lpc84x_acmp_t *p_hw_acmp);

/**
 * \brief �������
 */
void demo_am845_core_hw_capt_entry (void)
{
    am_kprintf("demo am845_core hw capt!\r\n");
  
    am_gpio_pin_cfg(PIO0_31, PIO0_31_CAPT_X0 | PIO0_31_INACTIVE);
    am_gpio_pin_cfg(PIO1_0, PIO1_0_CAPT_X1 | PIO1_0_INACTIVE);
    am_gpio_pin_cfg(PIO1_1, PIO1_1_CAPT_X2 | PIO1_1_INACTIVE);

    amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM, AMHW_LPC84X_SWM_PIO0_31_CAPT_X0);
    amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM, AMHW_LPC84X_SWM_PIO1_0_CAPT_X1);
    amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM, AMHW_LPC84X_SWM_PIO1_1_CAPT_X2);

    demo_lpc84x_hw_capt_entry(LPC84X_CAPT, LPC84X_ACMP);
}
/** [src_am845_core_std_led] */

/* end of file */
