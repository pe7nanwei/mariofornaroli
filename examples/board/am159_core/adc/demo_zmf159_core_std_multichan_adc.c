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
 * \brief ��ͨ��ADC�ɼ� ���̣�ͨ����׼�ӿ�ʵ��
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
 *    2. ��Ҫ��֤am_hwconf_zmf159_adc.c�ļ��еĶ�Ӧͨ�����ŵĳ�ʼ��ע�ʹ򿪣�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    4. ���û��û���Ҫ���ADC��ѯ��ȡͨ������Ŀ�����߱����ȡͨ����˳��ֻ���޸�
 *       adc_chan[]�����е�ͨ��ֵ���ɣ�ע����Ҫ��am_hwconf_zmf159_adc.c
 *       �ļ��н�ͨ�����ŵĳ�ʼ��ע�ʹ򿪡�
 *
 * \par Դ����
 * \snippet demo_zmf159_core_std_multichan_adc.c src_zmf159_core_std_multichan_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-29  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_core_std_multichan_adc
 * \copydoc demo_zmf159_core_std_multichan_adc.c
 */

/** [src_zmf159_core_std_multichan_adc] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_zmf159_inst_init.h"
#include "demo_std_entries.h"
#include "demo_zmf159_core_entries.h"

/**
 * \brief �������
 */
void demo_zmf159_core_std_multichan_adc_entry (void)
{
    /* ADCͨ��4,5 */
    int adc_chan[] = {4, 5};

    AM_DBG_INFO("demo zmf159_core std adc int!\r\n");

    demo_std_multichan_adc_entry(am_zmf159_adc1_inst_init(),
                                 adc_chan,
                                 sizeof(adc_chan) / sizeof(adc_chan[0]));

}
/** [src_zmf159_core_std_multichan_adc] */

/* end of file */
