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
 * \brief �����嵥 9.77
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-26  ipk, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_input.h"
#include "am_zm516x.h"
#include "model_bool.h"
#include "view_led.h"
#include "view_zigbee.h"
#include "am_lpc82x_inst_init.h"

static model_bool_t __g_model_bool;      //����һ��������ģ��ʵ��

static void __input_key_proc (void *p_arg, int key_code, int key_state)
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
    view_led_t              view_led0;     	//����һ��LED��ͼʵ��
    view_zigbee_t           view_zigbee;   	//����һ��zigbee��ͼʵ��
    am_input_key_handler_t  key_handler;   	//����һ������������
    am_zm516x_handle_t      zm516x_handle = am_zm516x_inst_init();		

    //ע�ᰴ���¼�
    am_input_key_handler_register(&key_handler, __input_key_proc, (void *)NULL);
    //��ʼ��ģ�ͣ�value�ĳ�ʼֵΪ AM_FAKSE
    model_bool_init(&__g_model_bool, AM_FALSE);
    //��ʼ����ͼʵʵ��
    view_led_init(&view_led0, 0);
    view_zigbee_init(&view_zigbee, zm516x_handle);
    //�����ͼ
    model_attach(&(__g_model_bool.isa), &(view_led0.isa));
    model_attach(&(__g_model_bool.isa), &(view_zigbee.isa));
    while (1) {
    }
}
/* end of file */
