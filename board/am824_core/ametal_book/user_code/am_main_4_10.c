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
 * \brief �����嵥4.10
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_board.h"
#include "buzzer.h"

/**
 * \brief AMetal Ӧ�ó������
 */
int am_main (void)
{
    buzzer_init();         // ��������ʼ����Ĭ��Ϊ1KHzƵ��
    while (1) {               
        buzzer_on();       // �򿪷����� 
        am_mdelay(1000);    // ��ʱ100ms 
        buzzer_off();      // �رշ����� 
        am_mdelay(1000);    // ��ʱ100ms 
    }
}

/* end of file */

