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
 * \brief �����嵥4.1
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"

/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void)
{
    while(1) {
        am_led_toggle(0);           			// ��תLED0��״̬
        am_mdelay(500);             			// ��ʱ500ms
	    }
}

/* end of file */

