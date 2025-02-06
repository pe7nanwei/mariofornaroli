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
 * \brief �����嵥4.52
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
#include "am_delay.h"
int am_main (void)
{
    int i       = 0;
    int sec     = 0;                                  // ���������0

    digitron1_hc595_init();                            // �弶��ʼ��
    digitron1_disp_num_set(0, 0);                      // ���������ʮλ��0
    digitron1_disp_num_set(1, 0);                      // ��������ĸ�λ��0
    while(1) {
        digitron1_hc595_disp_scan();                   // ÿ��5ms���ö�̬ɨ�躯��
        am_mdelay(5);
        i ++;
        if (i == 200) {                               // ѭ��200�Σ���ʱ1s
            i = 0;
            sec = (sec + 1) % 60;                     // �������+1
            digitron1_disp_num_set(0,sec / 10);        // �������������ʮλ
            digitron1_disp_num_set(1,sec % 10);        // ������������ĸ�λ
        }
    }
}


/* end of file */

