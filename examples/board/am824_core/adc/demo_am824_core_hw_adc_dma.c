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
 *   1. �̽� J12 ����ñ��ʹ�òο���ѹΪ 2.5V��
 *   2. PIO0_7(ADC ͨ�� 0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADC ת����� 100 �Σ����ڴ�ӡ�� 100 ��������ѹֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am824_core_hw_adc_dma.c src_am824_core_hw_adc_dma
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_core_hw_adc_dma
 * \copydoc demo_am824_core_hw_adc_dma.c
 */

/** [src_am824_core_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am824_core_hw_adc_dma_entry (void)
{
    am_kprintf("demo am824_core hw adc dma!\r\n");

    /* ƽ̨��ʼ�� */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_ADC0);
    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_ADC0);
	
    /* ����ͨ����ʹ��ͨ�� 0����������Ϊ����ģʽ INACTIVE */
    am_gpio_pin_cfg(PIO0_7, PIO0_7_ADC_0 | PIO0_7_INACTIVE);

    demo_lpc824_hw_adc_dma_entry(LPC82X_ADC0, 0, 2500);
}
/** [src_am824_hw_adc_dma] */

/* end of file */
