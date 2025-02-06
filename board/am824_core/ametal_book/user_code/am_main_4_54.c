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
 * \brief �����嵥4.54
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
#include "lm75.h"
#include "am_delay.h"
int am_main(void)
{
    int16_t temp;                                       // �����¶�ֵ
    int i = 0;

    digitron1_hc595_init();
    lm75_init();
    while(1) {
        temp = lm75_read();                             // ��ȡ�¶�ֵ
        if (temp < 0)
            temp = -1 * temp;                        // �¶�Ϊ��ʱ��Ҳֻ��ʾ�¶���ֵ
        digitron1_disp_num_set(0, (temp >> 8) / 10); // ��ʾ�¶��������ֵ�ʮλ
        digitron1_disp_num_set(1, (temp >> 8) % 10); // ��ʾ�¶�С�����ֵ�ʮλ
        for (i = 0; i < 100; i++) {
            // ѭ��100�Σ���ʱ500ms,ʹ�¶�ֵ��500ms��ʱ��������
            digitron1_hc595_disp_scan();
            am_mdelay(5);
        }
    }
}



/* end of file */

