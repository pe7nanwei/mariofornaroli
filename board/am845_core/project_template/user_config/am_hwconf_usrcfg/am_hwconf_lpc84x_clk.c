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
 * \brief LPC84X ʱ���û������ļ�
 * \sa am_hwconf_lpc84x_clk.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  lnk, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc84x_clk.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_swm.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "hw/amhw_lpc84x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_clk
 * \copydoc am_hwconf_lpc84x_clk.c
 * @{
 */

/**
 * \brief PLL ʱ��Դ
 *
 * - �ڲ� IRC��12MHz��: AMHW_LPC84X_CLK_PLLIN_SRC_IRC
 * - �ⲿ����12MHz��: AMHW_LPC84X_CLK_PLLIN_SRC_SYSOSC
 * - �ⲿ��������ʱ��: AMHW_LPC84X_CLK_PLLIN_SRC_CLKIN
 *
 * \note Ĭ��ʹ���ڲ� IRC����Ҫʹ���ⲿ������Ҫ�ڿ������Ϻ��� 12MHz ����
 *       ���޸ĺ�ֵΪ AMHW_LPC84X_CLK_PLLIN_SRC_SYSOSC����ʹ���ⲿ����ʱ�����룬
 *       �� 12MHz ʱ�Ӵ� PIO0_1 ��������
 */
#define __LPC84X_CLK_PLL_SRC     AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_CLK
#define __LPC84X_EXTERNAL_SRC    AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_SYS_OSC_CLK

/**
 * \brief CLK ƽ̨��ʼ��
 */
am_local void __lpc84x_clk_plfm_init (void)
{
    if(__LPC84X_CLK_PLL_SRC == AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_CLK &&
    		__LPC84X_EXTERNAL_SRC ==  AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_SYS_OSC_CLK) {

        /*
         * �ⲿ�����ϵͳ������Ϊʱ��Դ
         */

        /* �� PIO0_8,��PIO0_9 ����Ϊ����ģʽ���������������� */
        amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SWM);

		amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,
						           PIO0_8,
						           AMHW_LPC84X_IOCON_MODE_INACTIVE);
		amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,
						           PIO0_9,
						           AMHW_LPC84X_IOCON_MODE_INACTIVE);

        amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM,
        		                          AMHW_LPC84X_SWM_PIO0_8_XTALIN);
        amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM,
        		                          AMHW_LPC84X_SWM_PIO0_9_XTALOUT);

    } else if (__LPC84X_CLK_PLL_SRC == AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_CLK &&
    		__LPC84X_EXTERNAL_SRC ==  AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_CLK_IN) {

        /*
         * �ⲿ�ܽ�������Ϊʱ��Դ
         */

        /* �� PIO0_1 ����Ϊ����ģʽ���������������� */

        amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_IOCON);

        amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,PIO0_1,
                                   AMHW_LPC84X_IOCON_MODE_INACTIVE);

        /* ʹ�� PIO0_1 ���ؾ���̶����Ź��� CLKIN */

        amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SWM);

        amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM,
                                          AMHW_LPC84X_SWM_PIO0_1_CLKIN);
    } else {

        /*
         * ʹ���ڲ�IRC ��ʱ��Դ
         */
    }
}

/**
 * \brief CLK �豸��Ϣ
 *
 * Ĭ��ʹ���ڲ� fro��24MHz), ���� PLL ��Ƶ���������ʱ�ӣ���ʱ��
 * main_rate = 60 MHz, ϵͳʱ�� system_clk = 30MHz
 *
 * \note ����ͨ���޸� __g_lpc84x_clk_devinfo ������ʱ��Դ��Ƶ�ʣ���ʱ��ʹ�� PLL
 *       ���ʱ���޸� MSEL��PSEL ʵ�֣���ϵͳʱ������ʱ�ӷ�Ƶ��õ���Ĭ�� 2 ��Ƶ
 */
am_local am_lpc84x_clk_devinfo_t __g_lpc84x_clk_devinfo = {

	/** \brief fro ʱ��ѡ��  */
	AMHW_LPC84X_CLK_FRO_24000000,

    /*
     * �ⲿ ʱ��Դ
     * ʹ��io����ʱ�ӻ��Ǿ�������ʱ��
     * ��PLLΪѡ���ⲿʱ��Դ���������Ч
     */
	AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_SYS_OSC_CLK,

    /*
     * PLL ʱ��Դ
     * �ڲ� IFRO��Ĭ��24MHz��: AMHW_LPC84X_CLK_PLLIN_SRC_FRO
     * �ⲿʱ��(ѡ���ⲿʱ��ΪPLL����Դ����ѡ����ⲿ ʱ��Դ��Ч): AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_CLK
     *  ���Ź�����: AMHW_LPC84X_CLK_PLLIN_SRC_WTD_CLK
     * �ڲ� IFRO_DIV��Ĭ��12MHz����AMHW_LPC84X_CLK_PLLIN_SRC_WTD_CLK
     */
	AMHW_LPC84X_CLK_PLLIN_SRC_FRO_DIV,

    /*
     * PLL ���ƼĴ��� MSEL��ʹ FCLKOUT �ڷ�Χ 100MHz ��
     * FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 5 = 60 MHz
     */
    4,

    /*
     * PLL ���ƼĴ��� PSEL��ʹ FCCO �ڷ�Χ 156MHz - 320MHz
     * FCCO = FCLKOUT * 2 * 2^(PSEL) = 60MHz * 2 * 2 = 240MHz
     */
    1,

    /*
     * ��ʱ��Դѡ��
     * - Ĭ�ϲ�����PLLʱ��: AMHW_LPC84X_MAIN_CLK_PLLIN_SRC_MAIN_CLK_PRE_PLL
     * - ����PLLʱ�� ��AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_SYS_PLL
     */
	AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_SYS_PLL,

    /*
     * ��ʱ��Դͨ����Ƶ����Ϊϵͳʱ�ӣ���Ƶֵ���� 1- 255 ֮�����ֵ
     * system_clk = main_clk / div = 60MHz / 2 = 30 MHz
     */
    2,

    /*
     * WDTOSC Ƶ�ʷ�Ƶϵ�������� 2 - 64 ֮���ż��
     * ����ʱ��Դѡ���Ź�����ʱ����Ҫ���� WDTOSC Ƶ�ʷ�Ƶϵ����Ƶ��ѡ��
     * ����ΪĬ��ֵ 4.6MHz��2 ��Ƶ��ʱ��Ƶ�� 2.3MHz
     */
    2,

    /*
     * WDTOSC Ƶ��ѡ��
     * wdtosc_freq = 600000UL Hz
     */
	AMHW_LPC84X_CLK_WDTOSC_RATE_4_6MHZ,

    /*
     * FRG0 ʱ��ԴƵ��ѡ��
     * - FRO��AMHW_LPC84X_CLK_FRG_FRO
     * - ��ʱ�ӣ�AMHW_LPC84X_CLK_FRG_MAIN_CLK
     * - PLL���ʱ�ӣ� AMHW_LPC84X_CLK_FRG_SYS_PLL0_CLK
     */
	AMHW_LPC84X_CLK_FRG_MAIN_CLK,

    /*
     * FRG1 ʱ��ԴƵ��ѡ��
     * - FRO��AMHW_LPC84X_CLK_FRG_FRO
     * - ��ʱ�ӣ�AMHW_LPC84X_CLK_FRG_MAIN_CLK
     * - PLL���ʱ�ӣ� AMHW_LPC84X_CLK_FRG_SYS_PLL0_CLK
     */
	AMHW_LPC84X_CLK_FRG_MAIN_CLK,

    /* ƽ̨��ʼ������ */
    __lpc84x_clk_plfm_init,

    /* ��ƽ̨���ʼ������ */
    NULL
};

/** \brief CLK �豸ʵ�� */
am_local am_lpc84x_clk_dev_t __g_lpc84x_clk_dev;

/**
 * \brief CLK ʵ����ʼ��
 */
int am_lpc84x_clk_inst_init (void)
{

    return am_lpc84x_clk_init(&__g_lpc84x_clk_dev, &__g_lpc84x_clk_devinfo);
}

/**
 * @}
 */

/* end of file */
