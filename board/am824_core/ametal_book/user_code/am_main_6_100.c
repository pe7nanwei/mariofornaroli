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
 * \brief �����嵥6.100
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-19  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_zlg72128.h"
#include "am_hwconf_zlg72128.h"

// �Զ��尴������ص�����
static void __key_callback (void *p_arg,uint8_t key_val,uint8_t repeat_cnt,uint8_t funkey_val)
{
    if (key_val == AM_ZLG72128_KEY_1_1) {        // ��1�е�1����������
            // ���ܼ�F0����
        if (AM_ZLG72128_FUNKEY_CHECK(funkey_val, AM_ZLG72128_FUNKEY_0)) {
            am_led_toggle(1);
        } else {                                // ���ܼ�F0δ����
            am_led_toggle(0);
        }
    }
}

int am_main (void)
{
    am_zlg72128_handle_t zlg72128_handle = am_zlg72128_inst_init();
    am_zlg72128_key_cb_set(zlg72128_handle, __key_callback, NULL);                    
    // _key_callbackע��Ļص��������ص������ĵ�һ��������ʹ�ã�����ΪNULL
    while (1){
    }
}



/* end of file */

