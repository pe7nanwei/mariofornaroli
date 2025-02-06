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
 * \brief �����嵥5.45
 *
 * \note ��������Ҫ�õ�miniport��չ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "led.h"
#include "buzzer.h"
#include "key1.h"
#include "am_delay.h"
int am_main(void)
{
    uint8_t key_return;                    // key1_scan()����ֵ����

    key1_init();
    led_init();
    buzzer_init();
    while(1) {
        key_return = key1_scan();          // ����key_return�ķ���ֵ�жϰ����¼��Ĳ���
        if (key_return == 0) {
          // ����ֵΪ0��˵���м����£����������֡�һ��
            buzzer_beep(100);
        } else if (key_return == 1) {
          // ����ֵΪ1��˵�������ͷţ�LED0��ת
            led_toggle(0);
        }
        am_mdelay(10);                    // ÿ��10msɨ��һ�ΰ�������ʱȥ����
    }
}


/* end of file */

