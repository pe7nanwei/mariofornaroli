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
 * \brief AM824ZB booltoader ����Ӧ�ù���
 *
 *  ʹ�÷�ʽ�ɲο�ametal/documents/am24zb/Ŀ¼�µ�ametal_am824zb_bootloader�����ֲ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"
#include "demo_am824zb_entries.h"
/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void)
{
    AM_DBG_INFO("application ��application Start up successful!\r\n");
    while(1) {
        am_mdelay(1000);
        am_led_toggle(0);
    }
}

/* end of file */
