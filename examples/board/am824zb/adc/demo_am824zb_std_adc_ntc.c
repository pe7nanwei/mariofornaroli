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
 * \brief ADC ���ð����������� (NTC) �����¶Ȳ������̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J6 ����ñ��ʹ�� ADC0_2��PIO0_14��������������ĵ�ѹ��
 *   2. ��am_hwconf_lpc82x_adc0_int.c�ļ��еĵ�48��ȡ��ע�ͣ���ADC��ͨ��2��
 *
 * - ʵ������
 *   1. ��������¶�ֵ��
 *   2. ���� RES ��������һ�������������¶�ֵ���ߡ�
 *
 * \note
 *    1. ������Ҫ�� J14 ����ñ�� KEY �� RES �̽Ӳ���ʹ�ã�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *       PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \warning �뾡��ʹ�ö��� 5V ��Դ�����ӹ��磬��Ϊ���ȵ����ǹ��ʵ��裬��ֵ��С
 *          ��������ͨ���緽ʽ�� USB ���磬���������Դ��ѹ������Ӱ��������
 *          ����ֵ�жϣ�����Ӱ���¶�ֵ�Ĳ�����
 *
 * \par Դ����
 * \snippet demo_am824_std_adc_ntc.c src_am824_std_adc_ntc
 *
 * \internal
 * \par Modification History
 * - 1.02 18-12-21  ipk, modified
 * - 1.01 15-12-10  hgo, modified
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824_std_adc_ntc
 * \copydoc demo_am824_std_adc_ntc.c
 */

/** [src_am824_std_adc_ntc] */
#include "ametal.h"
#include "am_adc.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc82x_inst_init.h"
#include "demo_std_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/** \brief NTC �¶Ȳɼ�ʹ�õ��� ADC ͨ�� 2 */
#define __ADC_CHAN    2

/**
 * \brief �������
 */
void demo_am824zb_std_adc_ntc_entry (void)
{
    AM_DBG_INFO("demo am824_core std adc ntc!\r\n");
  
    demo_std_adc_ntc_entry(am_lpc82x_adc0_int_inst_init(),  __ADC_CHAN, 2000);

}
/** [src_am824_std_adc_ntc] */

/* end of file */
