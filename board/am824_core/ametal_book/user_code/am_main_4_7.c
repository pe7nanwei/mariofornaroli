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
 * \brief �����嵥4.7
 *
 * \note ��������Ҫ�õ�miniport��չ��,��Ҫ��led.h�ļ�����USE_MINIPORT_LED��Ϊ1
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_delay.h"
#include "led.h"

int am_main (void)
{
    int i = 0;

    led_init();               // �弶��ʼ�� 
    while(1) {
        led_on(i);            // ����LED��i��
        am_mdelay(100);       // ��ʱ100ms 
        led_off(i);           // Ϩ��LED��i�� 
        i++;                  // ָ����һ��LED         
        if(i == 8) {          // LEDѭ��һ�κ�i = 8  
            i = 0;            // ����i��ʼ��Ϊ0        
        }
    }
}

/* end of file */
