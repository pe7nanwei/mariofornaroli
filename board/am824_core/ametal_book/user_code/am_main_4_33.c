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
 * \brief �����嵥4.33
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "digitron1.h"
#include "buzzer.h"
#include "am_softimer.h"

static am_softimer_t timer_sec;
static void timer_sec_callback (void *p_arg)
{
    static int sec = 0;                            // ���������0
    buzzer_beep(100);                              // ����100ms�����֡�һ��
    sec = (sec + 1) % 60;                          // �������+1
    digitron1_disp_num_set(0, sec / 10);           // �������������ʮλ
    digitron1_disp_num_set(1, sec % 10);           // ������������ĸ�λ
}

int am_main (void)
{
    buzzer_init();
    digitron1_init_with_softimer();
    am_softimer_init(&timer_sec, timer_sec_callback, NULL); // ��ʼ����ʱ��
    am_softimer_start(&timer_sec, 1000);                    // ������ʱ������ʱʱ��Ϊ1s
    digitron1_disp_num_set(0, 0);                           // ���������ʮλ��0
    digitron1_disp_num_set(1, 0);                           // ��������ĸ�λ��0
    while(1) {
    }
}




/* end of file */

