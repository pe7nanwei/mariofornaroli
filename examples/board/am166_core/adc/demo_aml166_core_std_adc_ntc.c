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
 * \brief ADC ���ð��ӵ���������(NTC)��������¶����̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� J6 ����ñ��ʹ�� ADC_IN8��PIOB_0������ R9 �ĵ�ѹ��
 *   2. �� J14 �� KEY �� RES �̽���һ��ʹ�ð��� RES ����ͨ���ʵ��衣
 *
 * - ʵ������
 *   1. ��������¶�ֵ��
 *   2. ���� RES ��������һ�������������¶�ֵ���ߡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \warning �뾡��ʹ�ö��� 5V ��Դ�����ӹ��磬��Ϊ���ȵ����ǹ��ʵ��裬��ֵ��С������
 *          ��ͨ���緽ʽ�� USB ���磬���������Դ��ѹ������Ӱ������������ֵ�жϣ�����
 *          Ӱ���¶�ֵ�Ĳ�����
 *
 * \par Դ����
 * \snippet demo_aml166_core_std_adc_ntc.c src_aml166_core_std_adc_ntc
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-10  hgo, modified
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_std_adc_ntc
 * \copydoc demo_aml166_core_std_adc_ntc.c
 */

/** [src_aml166_core_std_adc_ntc] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/* \brief �������  */
void demo_aml166_core_std_adc_ntc_entry (void)
{
    AM_DBG_INFO("demo aml166_core std adc ntc!\r\n");

    /* NTC�¶Ȳɼ�ʹ�õ���ADCͨ�� 8 ��PIOB_0���� ��ѹ����Ϊ 2000ŷķ */
    demo_std_adc_ntc_entry(am_zlg116_adc_inst_init(),  8, 2000);
}
/** [src_aml166_core_std_adc_ntc] */

/* end of file */
