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
 * \brief PMU ˯��ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ�鲽�裺
 *   1. �öŰ��߽� PIO0_23 �� GND ���ӣ��ѵ�ƽ���͡�
*
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ����˯��ģʽ��
 *   2. �� PIO0_23 �� GND �����ӶϿ�ʱ��CPU �����ѣ�LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ���� MRT Ĭ����Ϊϵͳ�δ�ʹ�ã�ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_SOFTIMER_ENABLE�� AM_CFG_SYSTEM_TICK_ENABLE �Լ�
 *       AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0����ʹ�������ʱ����ϵͳ��ડ����ض���������
 *       ��ֹ����˯��ģʽ�� MRT ��ʱ���жϻ��ѣ�
 *    2. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ����˯��
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_pmu_sleep.c src_lpc824_hw_pmu_sleep
 *
 * \internal
 * \par Modification history
 * - 1.02 19-04-17  ipk, modified
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-21  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_sleep
 * \copydoc demo_lpc824_hw_pmu_sleep.c
 */

/** [src_lpc824_hw_pmu_sleep] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "am_lpc82x.h"

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/
volatile uint8_t __g_sleep_wkt_flag = 0; /**< \brief �жϱ�־���� */

/**
 * \brief �����жϷ�����
 */
am_local void __sleep_pint_isr (void *p_arg)
{

    /* ����жϱ�־ */
    amhw_lpc82x_pint_edge_dec_clr(LPC82X_PINT, AMHW_LPC82X_PINT_CHAN_0);

    /* �ı��жϱ�־���� */
    __g_sleep_wkt_flag = 1;
}

/**
 * \brief PMU ˯��ģʽ ��ʼ��
 */
void demo_lpc824_hw_pmu_sleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                     int                 pin)
{

    /* LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);
  
    /* �򿪿��Ź�������Դ */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* PIO0_23 �ж�ʹ���ж�ͨ�� 0 */
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_0, pin);

    /* ����Ϊ˫���ش��� */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_BOTH_EDGES);

    /* PIN0 ��Ϊ����Դ */
    amhw_lpc82x_syscon_wakeup_enable(AMHW_LPC82X_SYSCON_STARTER_PINT0);

    /* �����жϷ����� */
    am_int_connect(INUM_PIN_INT0, __sleep_pint_isr, (void *)0);

    /* ʹ�������ж� */
    am_int_enable(INUM_PIN_INT0);
  
    /* ����Ϊ˯��ģʽ */
    amhw_lpc82x_lowpower_mode_set(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_NORMAL);

    /* ����˯��ģʽ */
    __WFI();

    AM_FOREVER {

        /* ��˯��ģʽ���Ѻ�LED0 ������˸ */
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}
/** [src_lpc824_hw_pmu_sleep] */

/* end of file */
