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
 * \brief TIM17 ��ʱ�� TIMING ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��������ʱ���������Ϣ
 *   2. ��ʱ���ڵ���(Ĭ��Ϊ 2Hz)�����Դ��ڻ���� The timing frq is 2Hz;
 *
 * \note
 *    16 λ��ʱ����ʱ����ֵ��Ϊ 65536 �ı�������ʱ����һЩƫ�
*
 * \par Դ����
 * \snippet demo_am116_core_std_tim17_timing.c src_am116_core_std_tim17_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_am116_core_std_tim17_timing
 * \copydoc demo_am116_core_std_tim17_timing.c
 */

/** [src_am116_core_std_tim17_timing] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg116_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_std_tim17_timing_entry (void)
{
    AM_DBG_INFO("demo am116_core std tim17 timing!\r\n");

    demo_std_timer_timing_entry(am_zlg116_tim17_timing_inst_init(), 0);
}
/** [src_am116_core_std_tim17_timing] */

/* end of file */
