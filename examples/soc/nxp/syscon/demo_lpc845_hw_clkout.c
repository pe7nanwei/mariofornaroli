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
 * \brief ʱ��Ƶ��������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ "The CLKOUT  rate is  xxx Hz\r\n"��xxx Ϊ��ǰƵ�ʣ�
 *   2. PIO0_27 ���ţ�Ĭ������ CLKOUT ��������������ǰʱ��Ƶ�� 2.5MHz��
 *   3. LED0 �� 0.2s ��ʱ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_clkout.c src_lpc824_hw_clkout
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_clkout
 * \copydoc demo_lpc824_hw_clkout.c
 */

/** [src_lpc824_hw_clkout] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_clk.h"


/** \brief ʱ��Դ���� */
#define __CLKOUT_SRC  AMHW_LPC84X_CLKOUT_SRC_MAIN

/** \brief ʱ�ӷ�Ƶ�������� */
#define __CLKOUT_DIV  10

/** \brief ʱ�ӷ�Ƶ�������� */
#define __RETE        2

#define __DIV         2

/**
 * \brief �������
 */
void demo_lpc845_hw_clkout_entry (void)
{
    /* �����ڲ� IRC */
    am_kprintf("demo am845 hw clkout!\r\n");

    /* Configure the SWM for clock out */
    am_gpio_pin_cfg(16, PIO_FUNC_CLKOUT);

    amhw_lpc84x_outclk_div_set(__CLKOUT_DIV);

    amhw_lpc84x_outclk_src_set(__CLKOUT_SRC);

    if(__CLKOUT_SRC == AMHW_LPC84X_CLKOUT_SRC_FRO_WDT_OSC_CLK) {
        amhw_lpc84x_clk_wdtoscc_cfg(__RETE, __DIV);
		amhw_lpc84x_syscon_powerup(AMHW_LPC84X_SYSCON_PD_WDT_OSC);
    }

    AM_DBG_INFO("The CLKOUT  rate is  %8d Hz\r\n",
    		amhw_lpc84x_outclk_clkrate_get() / __CLKOUT_DIV);

    AM_FOREVER {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}
/** [src_lpc824_hw_clkout] */

/* end of file */
