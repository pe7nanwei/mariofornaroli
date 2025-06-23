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
 * \brief �����嵥7.31
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_input.h"
#include "am_led.h"

static am_input_key_handler_t g_key_handler;    // �¼�������ʵ�����壬ȫ�ֱ�����ȷ��һֱ��Ч

// ʹ�ð����������ܣ�ʹ�øù��ܽ�ע�Ϳ�ʼ�������溯��ע��
//static void __input_key_proc(void *p_arg, int key_code, int key_state, int keep_time)
//{
//    if (key_code == KEY_KP0) {
//        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {        //  �м�����
//            am_led_on(0);
//        }else if (key_state == AM_INPUT_KEY_STATE_RELEASED){  // �����ͷ�
//            am_led_off(0);
//        }
//    }
//}


// ʹ�ð����������ܣ�ʹ�øù��ܽ�ע�Ϳ�ʼ�������溯��ע��
static void __input_key_proc(void *p_arg, int key_code, int key_state, int keep_time) 
{
    if (key_code == KEY_KP0) {
        if ((key_state == AM_INPUT_KEY_STATE_PRESSED) && (keep_time == 3000)) {
            am_led_toggle(0); 					// ����3s,  LED0״̬��ת
        }
    }
} 


int am_main (void)
{
    // ���ﰴ���ص���������ѡ�񰴼���ͬ�Ĺ���(�������ܻ��߳�������,ֻ��Ҫ�޸�)
    am_input_key_handler_register(&g_key_handler, __input_key_proc, (void *)100);
    while (1) {
    }
}



/* end of file */

