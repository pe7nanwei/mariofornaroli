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
 * \brief �����嵥4.15
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
    int i        = 0;
    int num      = 0;

    digitron_init();                       // �弶��ʼ��
    while(1) {
        digitron_segcode_set (0xFF);       // ��Ӱ--Ϩ��ȫ�������
        digitron_disp_num(0, num / 10);    // com0��ʾnum��ʮλ
        am_mdelay(5);                      // ��ʱ5ms
        digitron_segcode_set (0xFF);       // ��Ӱ--Ϩ��ȫ�������
        digitron_disp_num(1, num % 10);    // com1��ʾnum�ĸ�λ
        am_mdelay(5);
        i++;
        if (i == 100) {                    // ѭ��100�μ�����ʱ��ﵽ1s
            i = 0;
            num = (num + 1) % 60;          // num��ֵ��0 ~ 59ѭ��
        }
    }
}


/* end of file */

