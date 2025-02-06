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
 * \brief �����嵥4.26
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
#include "digitron1.h"

int am_main (void)
{
    int sec     = 0;                                 // ���������0
    int i       = 0;

    digitron1_init();
    digitron1_disp_num_set(0, 0);                    // ��ʾ����ʮλ��0
    digitron1_disp_num_set(1, 0);                    // ��ʾ���ĸ�λ��0
    digitron1_disp_blink_set(1, AM_TRUE);            // com1�����������λ����˸
    while(1) {
        digitron1_disp_scan();                       // ÿ��5ms���ö�̬ɨ�躯��
        am_mdelay(5);
        i++;
        if (i == 200) {                              // ѭ��200�μ�����ʱ��ﵽ1s
            i = 0;
            sec = (sec + 1) % 60;                    // �������+1
            digitron1_disp_num_set(0, sec / 10);     // ������ʾ����ʮλ
            digitron1_disp_num_set(1, sec % 10);     // ������ʾ���ĸ�λ
        }
    }
}



/* end of file */

