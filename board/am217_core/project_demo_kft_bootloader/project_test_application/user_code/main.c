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
 * \brief ZLG217 bootloader��Ӧ�ó��򹤳�
 *
 * - �������裺
 *    �ο� {sdk}\ametal\documents\ZLG217 Ŀ¼�� am217_core_kft_bootloader �����ֲᡣ
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

/**
 * \brief �������
 */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "demo_am217_core_entries.h"
#include "zlg217_pin.h"
#include "am_zlg217_inst_init.h"

int am_main (void)
{
    AM_DBG_INFO("application : Start up successful!\r\n");

    demo_zlg217_core_boot_kft_application_entry();

    while (1) {

    }
}

/* end of file */
