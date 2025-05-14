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
 * \brief WDT ��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. feed_time_ms ���� time_out_ms��оƬ��λ��
 *   2. feed_time_ms С�� time_out_ms�������������С�
 *
 * \par Դ����
 * \snippet demo_std_wdt.c src_std_wdt
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-26  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_wdt
 * \copydoc demo_std_wdt.c
 */

/** [src_std_wdt] */
#include "ametal.h"
#include "am_wdt.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_std_wdt_entry (am_wdt_handle_t handle,
                         uint32_t        time_out_ms,
                         uint32_t        feed_time_ms)
{
    am_wdt_info_t info;

    AM_DBG_INFO("The chip Reset by External Reset Pin or WDT \r\n");

    am_wdt_info_get(handle, &info);

    AM_DBG_INFO("The WDT support min time is %d ms\r\n", info.min_timeout_ms);
    AM_DBG_INFO("The WDT support max time is %d ms\r\n", info.max_timeout_ms);

    am_wdt_enable(handle, time_out_ms);

    while (1) {

        /* ι������ */
        am_wdt_feed(handle);

        /* ��ʱ������ʱ����ι��ʱ��ʱ,��������Ź��¼���MCU ��λ */
        am_mdelay(feed_time_ms);

    }
}
/** [src_std_wdt] */

/* end of file */
