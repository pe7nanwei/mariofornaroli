/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief PT100��ֵ�¶�ת��
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-29  tee, first implementation.
 * \endinternal
 */

#include <stdio.h>
#include "am_pt100_to_temperature.h"
#include "am_pt100_temp_res_table.h"
 
/* PT100�ĵ������ֵ�����¶�ֵ */
float pt100_to_temperature (float pt100)
{
    const unsigned int table_size = sizeof(g_pt100_table) / sizeof(g_pt100_table[0]);
    
    unsigned int   pt100_x100 = 0;
    unsigned int   index      = 0;
    int            dif        = 0;
    float          dec        = 0;
 
    int low, high, mid;                          /* ���ڶ��ַ�����            */
 
    pt100_x100 = (unsigned int)(pt100 * 100);    /* ��ֵ����100������������� */

    /* �ж��Ƿ񳬳���Χ */
    if (pt100_x100 < g_pt100_table[0]) {
        return -200.0f;
    } else if (pt100_x100 >= g_pt100_table[table_size - 1]) {
        return 850.0f;
    }
    
    dec = pt100 * 100 - pt100_x100;
 
    low  = 0;
    high = table_size - 1;
 
    while ((high - low) != 1) {                /* ֱ���¶ȷ�Χ��СΪ1��  */

        mid = (low + high) / 2;

        if (pt100_x100 < g_pt100_table[mid]) {
            high = mid;
        } else if (pt100_x100 > g_pt100_table[mid]) {
            low  = mid;
        } else {
            index = mid;
            dif    = 0;
            break;
        }
    }
    
    if ((high - low) == 1) {
        
        index = low;
        dif   = pt100_x100 - g_pt100_table[low];
    }

    /* ���ֱ���Ϊ1�ȣ�������������ı��� */
    dec = 1.0f * (dif + dec) / (g_pt100_table[index + 1] - g_pt100_table[index]);

    /* ��ʼ�¶�Ϊ -200 */
    return index + dec - 200.0f;
}

/* end of file */
