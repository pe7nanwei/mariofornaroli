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
 * \brief �����嵥 9.73
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-26  ipk, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_led.h"
#include "am_input.h"
#include "model_bool.h"
#include "view_led.h"

static model_bool_t __g_model_bool;      			// ����һ��������ģ��ʵ��
static void __input_key_proc (void *p_arg, int key_code, int key_state, int keep_time)
{
	    am_bool_t value;
	
	    if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
	        if (model_bool_get(&__g_model_bool, &value) == 0) {
	            model_bool_set(&__g_model_bool, !value);
	        }
	    }
}
	
int am_main (void)
{
    view_led_t              view_led0;     		//����һ��LED��ͼʵ��
    am_input_key_handler_t  key_handler;   	  //����һ������������

    //ע�ᰴ���¼�
    am_input_key_handler_register(&key_handler, __input_key_proc, (void *)NULL);
    //��ʼ��ģ��,value�ĳ�ʼֵΪAM_FALSE
    model_bool_init(&__g_model_bool, AM_TRUE);
    //��ʼ����ͼʵ��
    view_led_init(&view_led0, 0);
    //�����ͼ
    model_attach(&(__g_model_bool.isa), &(view_led0.isa));
    while (1) {
    }
}
/* end of file */
