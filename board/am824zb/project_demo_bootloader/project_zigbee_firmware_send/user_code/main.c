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
 * \brief AM824ZB bootloader �̼����͹���
 *
 *  ʹ�÷�ʽ�ɲο�ametal/documents/am24zb/Ŀ¼�µ�ametal_am824zb_bootloader�����ֲ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_lpc82x.h"

extern void demo_zigbee_firmware_send_entry();

/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void)
{
	  demo_zigbee_firmware_send_entry();

    while(1) {
    }
}

/* end of file */
