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
 * \brief MicroPort RTC(PCF85063) ���̣�ͨ�� PCF85063 оƬʵ��
 *        RTC�����ӵĹ��ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort RTC ������ӵ� aml166-Core �� MicroPort �ӿڡ�
 *
 * - ʵ������
 *   1. ���ڽ�ÿһ���ʱ����Ϣ��ӡ������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_aml166_core_microport_rtc.c src_aml166_core_microport_rtc
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_microport_rtc
 * \copydoc demo_aml166_core_microport_rtc.c
 */

/** [src_aml166_core_microport_rtc] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief MicroPort RTC ���̣�ͨ����׼�ӿ�ʵ��
 *
 * \param ��
 *
 * \return ��
 */
void demo_aml166_core_microport_rtc_entry (void)
{
    AM_DBG_INFO("demo aml166_core microport rtc!\r\n");

    demo_std_rtc_entry(am_microport_rtc_std_inst_init());
}
/** [src_aml166_core_microport_rtc] */

/* end of file */
