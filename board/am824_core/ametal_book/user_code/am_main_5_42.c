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
 * \brief �����嵥5.42
 *
 * \note ��������Ҫ�õ�miniport��չ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "digitron2.h"
#include "am_delay.h"
int am_main (void)
{
    int i = 0, sec = 0;                               // ���������0

    digitron2_init();
    digitron2_disp_char_set(0, '0');                   // ��ʾ��ʮλ��0
    digitron2_disp_char_set(1, '0');                   // ��ʾ����λ��0
    while(1) {
        digitron2_disp_scan();                         // ÿ��5ms����ɨ�躯��
        am_mdelay(5);
         i++;
         if (i == 200) {                              // ÿ��ѭ��5ms��ѭ��200�Σ���Ϊ1s
            i = 0;
            sec = (sec + 1) % 60;                     // �������+1
            digitron2_disp_char_set(0,sec / 10 + '0'); // ������ʾ����ʮλ
            digitron2_disp_char_set(1,sec % 10 + '0'); // ������ʾ���ĸ�λ
         }
     }
}

/* end of file */

