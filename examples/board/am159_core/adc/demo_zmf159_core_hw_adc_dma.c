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
 * \brief ADC INT ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOA_4 (ADC ͨ�� 4) ����ģ�����롣
 *   2. PIOA_5 (ADC ͨ�� 5) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    1. ʹ�� ADC ģ�鹦�ܣ����뱣֤ ADC ģ���ϵ磻
 *    2. ��Ҫ��֤��Ӧͨ�����ŵĳ�ʼ��ע�ʹ򿪣�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    4. ���û��û���Ҫ���ADC��ѯ��ȡͨ������Ŀ�����߱����ȡͨ����˳��ֻ���޸�
 *       adc_chan[]�����е�ͨ��ֵ���ɣ�ע����Ҫ��ͨ�����ŵĳ�ʼ��ע�ʹ򿪡�
 *
 * \par Դ����
 * \snippet demo_zmf159_hw_adc_dma.c src_zmf159_hw_adc_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_adc_dma
 * \copydoc demo_zmf159_hw_adc_dma.c
 */

/** [src_zmf159_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "zmf159_dma_chan.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

#define  __ADC1_DMA_CHAN1         DMA1_CHAN_1 /* ADC��ӦDMA1ͨ��1 */

/**
 * \brief �������
 */
void demo_zmf159_core_hw_adc_dma_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw adc dma!\r\n");

    int adc_chan[] = {4, 5};

    /* ����Ӳ��������ǰ�Ļ������� ���������ţ�ʹ��ʱ�ӵ� */
//    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN | PIOA_0_ADC_IN0); /* ADC1ͨ��0 */
//    am_gpio_pin_cfg(PIOA_1, PIOA_1_AIN | PIOA_1_ADC_IN1); /* ADC1ͨ��1 */
//    am_gpio_pin_cfg(PIOA_2, PIOA_2_AIN | PIOA_2_ADC_IN2); /* ADC1ͨ��2 */
//    am_gpio_pin_cfg(PIOA_3, PIOA_3_AIN | PIOA_3_ADC_IN3); /* ADC1ͨ��3 */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN | PIOA_4_ADC_IN4); /* ADC1ͨ��4 */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_AIN | PIOA_5_ADC_IN5); /* ADC1ͨ��5 */
//    am_gpio_pin_cfg(PIOA_6, PIOA_6_AIN | PIOA_6_ADC_IN6); /* ADC1ͨ��6 */
//    am_gpio_pin_cfg(PIOA_7, PIOA_7_AIN | PIOA_7_ADC_IN7); /* ADC1ͨ��7 */


    am_clk_enable(CLK_ADC1);

    demo_zlg_hw_adc_dma_entry(ZMF159_ADC1,
                              adc_chan,
                              sizeof(adc_chan)/sizeof(adc_chan[0]),
                              __ADC1_DMA_CHAN1);
}
/** [src_zmf159_hw_adc_dma] */

/* end of file */
