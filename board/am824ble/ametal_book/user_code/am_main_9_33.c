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
 * \brief �����嵥9.33
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_hwconf_zlg9021.h"
#include "app_ble_led_control.h"

int am_main (void)
{
    am_zlg9021_handle_t  zlg9021_handle = am_zlg9021_inst_init();
	  app_ble_led_control(zlg9021_handle);
    while (1) {
	  }
}



/* end of file */
