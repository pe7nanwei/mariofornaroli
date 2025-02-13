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
 * \brief �����嵥4.20
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
    int sec = 0;                                 // ���������0
    int i   = 0;
    int j   = 0;
    digitron1_init();                            // ��ʼ����ʱ����ʵ���Զ�ɨ����ʾ
    digitron1_disp_num_set(0, 0);                // ��ʾ����ʮλ��0
    digitron1_disp_num_set(1, 0);                // ��ʾ���ĸ�λ��0
    while(1) {
        for (i = 0; i < 2; i++) {
            digitron1_disp_num_set(1, sec % 10); // ��λ��ʾ
            for (j = 0; j < 50; j++) {           // ɨ��50�Σ���ʱ250ms
                     digitron1_disp_scan();
                     am_mdelay(5);
            }
            digitron1_disp_code_set(1, 0xFF);    // ��250ms��λϨ��
            for (j = 0; j < 50; j++) {           // ɨ��50�Σ���ʱ250ms
                     digitron1_disp_scan();
                     am_mdelay(5);
            }
        }
        sec = (sec + 1) % 60;                    // �������+1
        digitron1_disp_num_set(0, sec / 10);     // ������ʾ����ʮλ
        digitron1_disp_num_set(1, sec % 10);     // ������ʾ���ĸ�λ
    }
}


/* end of file */

