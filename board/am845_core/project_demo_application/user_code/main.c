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
 * \brief LPC84X bootloader ���ڲ��Ե�Ӧ�ó��򹤳�
 *
 * - �������裺
 *   �ο�AMmetal-AM845-Core-bootloader�����ֲ�
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
#include "am_fm175xx.h"
#include "demo_am845_core_entries.h"

#include "am_lpc84x.h"
#include "am_uart.h"
#include "am_lpc84x_inst_init.h"
/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void) 
{
      demo_am845_core_application_entry();

    while(1) {

    }
}

/* end of file */
