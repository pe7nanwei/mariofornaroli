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
 * \brief DAC��ģת�����̣�ͨ��HW�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ����PIOE_30ΪDACģ�����
 *   2. ��ʾ�����ɼ���ģת���������PE30���ź����
 *   3. ʾ������ʾPIOE_30��ģ��������ڴ��Ϊ7������Ҳ���
 *
 *
 * \par Դ����
 * \snippet demo_lpc_hw_dac_buf_int.c src_lpc_hw_dac_buf_int
 *
 * \internal
 * \par Modification History
 * - 1.00 16-09-26  mkr, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_lpc_if_hw_dac_buf_int
 * \copydoc demo_lpc_hw_dac_buf_int.c
 */

 /** [src_lpc_hw_dac_buf_int] */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_int.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"
#include <am_lpc84x_dac.h>
#include <hw/amhw_lpc84x_dac.h>

#define  __BUFLEN  (sizeof(waveform)/4)

#define  FREQ      891

#if (SINE == 0)
static const uint32_t waveform[] = {0x0000, 0x1111, 0x2222, 0x3333,
                                    0x4444, 0x5555, 0x6666, 0x7777,
                                    0x8888, 0x9999, 0xAAAA, 0xBBBB,
                                    0xCCCC, 0xDDDD, 0xEEEE, 0xFFFF,
                                    0xFFFF, 0xEEEE, 0xDDDD, 0xCCCC,
                                    0xBBBB, 0xAAAA, 0x9999, 0x8888,
                                    0x7777, 0x6666, 0x5555, 0x4444,
                                    0x3333, 0x2222, 0x1111, 0x0000};
#else
static const uint32_t waveform[] = {32768, 39160, 45307, 50972,
                                    55938, 60013, 63041, 64905,
                                    65535, 64905, 63041, 60013,
                                    55938, 50972, 45307, 39160,
                                    32768, 26375, 20228, 14563,
                                     9597,  5522,  2494,   630,
                                        0,   630,  2494,  5522,
                                     9597, 14563, 20228, 26375};
#endif

/**
 * \brief DAC �жϷ�����
 */
static void __lpc_dac_int (void *p_arg)
{
	static uint32_t windex = 0;
    amhw_lpc_dac_t *p_hw_dac = (amhw_lpc_dac_t *)p_arg;
	p_hw_dac->cr = waveform[windex++];

	if (windex == __BUFLEN) {
	    windex = 0;
	}

}

/**
 * \brief DAC �ж�������Ҳ��źţ�HW��ʵ��
 * \return ��
 */
void demo_lpc_hw_dac_buf_int_entry (amhw_lpc_dac_t *p_hw_dac,
                                    int             inum)
{

    /* DAC���ݻ�������ʼ�� */
    extern int am_int_connect (int inum, am_pfnvoid_t pfn_isr, void *p_arg);
    extern int am_int_enable (int inum);

    /* DAC��ʼ�� */
	amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_DAC0);
	amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_DAC0);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SWM);
    amhw_lpc84x_swm_fixed_func_enable(LPC84X_SWM,
    		                          AMHW_LPC84X_SWM_PIO0_17_DACOUT0);
    amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,
                               PIO0_17,
                               AMHW_LPC84X_IOCON_MODE_INACTIVE);
    amhw_lpc84x_iocon_dac_mode_set(LPC84X_IOCON,
                                   PIO0_17,
								   AMHW_LPC84X_IOCON_DAC_MODE_ENABLE);

    amhw_lpc84x_dac_cntval_set (p_hw_dac, FREQ);
    amhw_lpc84x_syscon_powerup(AMHW_LPC84X_SYSCON_PD_DAC0);

    /* DAC�ж����Ӻ��� */
    am_int_connect(inum, __lpc_dac_int, p_hw_dac);

    /* ʹ��DAC��� */
    amhw_lpc84x_dac_dblbuf_set(p_hw_dac, AMHW_LPC84x_DAC_DBLBUF_EN);
    amhw_lpc84x_dac_cnt_set(p_hw_dac, AMHW_LPC84x_DAC_CNT_EN);
    amhw_lpc84x_dac_dma_int_req_set(p_hw_dac, AMHW_LPC84x_DAC_DMA_EN);
    am_int_enable(inum);

    while (1) {
        am_mdelay(2);
    }
}

/** [src_lpc_hw_dac_buf_int] */

/* end of file */
