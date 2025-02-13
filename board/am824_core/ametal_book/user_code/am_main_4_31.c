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
 * \brief �����嵥4.31
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
#include "am_softimer.h"
static am_softimer_t timer_sec;
static void timer_sec_callback (void *p_arg)
{
    static int sec = 0;                           // ���������0

    sec = (sec + 1) % 60;                         // �������+1
    digitron1_disp_num_set(0,sec / 10);            // ������ʾ����ʮλ
    digitron1_disp_num_set(1,sec % 10);            // ������ʾ���ĸ�λ
}

int am_main (void)
{
    digitron1_init_with_softimer ();
    am_softimer_init(&timer_sec, timer_sec_callback, NULL);    // ��ʼ����ʱ��
    am_softimer_start(&timer_sec,1000);                        // ������ʱ������ʱʱ��Ϊ1s
    digitron1_disp_num_set(0,0);                   // ��ʾ����ʮλ��0
    digitron1_disp_num_set(1,0);                   // ��ʾ���ĸ�λ��0
    while(1) {
    }
}



/* end of file */

