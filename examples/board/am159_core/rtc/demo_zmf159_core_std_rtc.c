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
 * \brief RTC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����õ�ʱ�䣬�Ժ�ÿ���ӡһ��ʱ�䡣
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zmf159_std_rtc.c src_zmf159_std_rtc
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-30  lqy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_std_rtc
 * \copydoc demo_zmf159_std_rtc.c
 */

/** [src_zmf159_std_rtc] */

#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "am_zmf159_inst_init.h"

/**
 * \brief �������
 */
void demo_zmf159_core_std_rtc_entry (void)
{
    AM_DBG_INFO("demo am159_core rtc entry!\r\n");

    demo_std_rtc_entry(am_zmf159_rtc_inst_init());
}
/** [src_zmf159_std_rtc] */

/* end of file */
