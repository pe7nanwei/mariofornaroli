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
 * \brief �����嵥6.30
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-18  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_mx25xx.h"
#include "app_test_mtd.h"
#include "am_hwconf_microport.h"

int am_main (void)
{
    am_mtd_handle_t mtd_handle = am_microport_flash_mtd_inst_init(); 
    if (app_test_mtd(mtd_handle) != AM_OK) {
        am_led_on(0);
        while(1);
    }
    while(1) {
        am_led_toggle(0);
        am_mdelay(200);
    }
}


/* end of file */

