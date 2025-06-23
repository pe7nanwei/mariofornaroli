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
 * \brief �����嵥7.40
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "app_key_code_led_show.h" 

int am_main (void)
{
    am_miniport_key_inst_init();   // MiniPort-ZLG72128ʵ����ʼ��
    app_key_code_led_show();       // ʹ��LED0��LED1�԰���������ж�������ʾ
    while (1) {
    }
}



/* end of file */

