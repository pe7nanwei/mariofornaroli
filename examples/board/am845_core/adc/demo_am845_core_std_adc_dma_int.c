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
 * \brief ADC DMA ���̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_7(ADC ͨ�� 0) ����ģ�������ѹ��
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *    PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_adc_dma_int.c src_am845_core_std_adc_dma_int
 *
 * \internal
 * \par Modification History
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_adc_dma_int
 * \copydoc demo_am845_core_std_adc_dma_int.c
 */

/** [src_am845_core_std_adc_dma_int] */
#include "ametal.h"
#include "am_adc.h"
#include "am_vdebug.h"
#include "am_lpc84x_inst_init.h"
#include "demo_nxp_entries.h"

/** \brief ͨ�� */
#define __ADC_CHAN         0
/**
 * \brief �������
 */
void demo_am845_core_std_adc_dma_int_entry (void)
{
    am_adc_handle_t adc_handle = NULL;

    am_kprintf("demo am845_core std adc int!\r\n");
  
    adc_handle = am_lpc84x_adc0_dma_inst_init();
    
    /* ͨ���Ͳ������� */
    demo_lpc_std_adc_dma_int_entry (adc_handle, __ADC_CHAN, 10000);
}
/** [src_am845_core_std_adc_dma_int] */

/* end of file */
