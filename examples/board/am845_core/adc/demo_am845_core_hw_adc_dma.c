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
 * \brief ADC ���̣�ת���������ͨ�� DMA ���䣬ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   2. PIO0_7(ADC ͨ�� 0) ����ģ�������ѹ��
 *
 * - ʵ������
 *   1. ADC ת����� 100 �Σ����ڴ�ӡ�� 100 ��������ѹֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *    PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_adc_dma.c src_am845_core_hw_adc_dma
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_adc_dma
 * \copydoc demo_am845_core_hw_adc_dma.c
 */

/** [src_am845_core_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x_clk.h"
#include "hw/amhw_lpc84x_clk.h"
#include "am_lpc84x_adc_dma.h"
#include "demo_nxp_entries.h"

extern void demo_lpc845_hw_adc_dma_entry(amhw_lpc84x_adc_t *p_hw_adc,
                                         int                ch,
                                         uint32_t           vref_mv);

/**
 * \brief �������
 */
void demo_am845_core_hw_adc_dma_entry (void)
{
    am_kprintf("demo am845_core hw adc dma!\r\n");

    /* ƽ̨��ʼ�� */
    amhw_lpc84x_syscon_powerup(AMHW_LPC84X_SYSCON_PD_ADC0);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_ADC);

    /* ����ͨ����ʹ��ͨ�� 0����������Ϊ����ģʽ INACTIVE */
    am_gpio_pin_cfg(PIO0_7, PIO0_7_ADC_0 | PIO0_7_INACTIVE);

    demo_lpc845_hw_adc_dma_entry(LPC84X_ADC0, 0, 2500);
}
/** [src_am845_core_hw_adc_dma] */

/* end of file */
