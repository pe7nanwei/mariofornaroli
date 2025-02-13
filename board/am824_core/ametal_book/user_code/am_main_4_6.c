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
 * \brief �����嵥4.6
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
#include "led.h"

int am_main (void)
{
    led_init();                 // �弯��ʼ����Ϩ��LED�� 
    while (1) {
        led_toggle(0);          // ��תI/O��ƽ,�ı�LED0״̬
        am_mdelay(200);         // ��ʱ200ms
    }
}


/* end of file */
