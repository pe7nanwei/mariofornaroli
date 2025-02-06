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
 * \brief �����嵥4.14
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "digitron0.h"
int am_main (void)
{
    digitron_init();
    while(1) {
        digitron_disp_num(0, 1);             // com0��ʾ1
        am_mdelay(5);                        // ��ʱ5ms
        digitron_disp_num(1, 2);             // com1����ʾ2
        am_mdelay(5);                        // ��ʱ5ms
    }
}



/* end of file */

