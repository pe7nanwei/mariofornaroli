/******************************************************************************
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
 * \brief �����嵥10.20
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "am_temp.h"
#include "am_zm516x.h"
#include "model_temp_monitor.h"
#include "view_zigbee1.h"
#include "view_digitron.h"
#include "view_buzzer.h"
#include "am_lpc82x_inst_init.h"
#include "am_hwconf_lm75.h"
#include "am_hwconf_miniport_view_key.h"

int am_main (void)
{
    model_temp_monitor_t	  model_temp;
    view_zigbee_t         	view_zigbee;
    view_buzzer_t          	view_buzzer;
    view_digitron_t         view_digitron;
    int32_t                	temp_cur;

    am_zm516x_handle_t   	  zm516x_handle = NULL;
	  zm516x_handle           = am_zm516x_inst_init();
	
    am_temp_handle_t     	temp_handle     = am_temp_lm75_inst_init();
    // ��ʼ����������8��ASCII����
    am_miniport_view_key_inst_init();
    am_digitron_disp_decode_set(0, am_digitron_seg8_ascii_decode);
	  
    am_temp_read(temp_handle, &temp_cur);
    // ��ʼ���¿���ģ�ͣ���ʼ����ֵ 10������ֵ40
    model_temp_monitor_init(&model_temp, 10, 40, temp_cur / 1000.0f);
    // ��ͼ��ʼ��
    view_digitron_init(&view_digitron, 0);
	 
    view_zigbee_init1(&view_zigbee, zm516x_handle);
    view_buzzer_init(&view_buzzer);

    model_attach(&(model_temp.isa), &(view_zigbee.isa));
		
    model_attach(&(model_temp.isa), &(view_buzzer.isa));
    model_attach(&(model_temp.isa), &(view_digitron.isa));
		
    while (1) {
        // ÿ��500ms��ȡһ���¶�ֵ
        am_temp_read(temp_handle, &temp_cur);
        model_temp_monitor_cur_set(&model_temp, temp_cur / 1000.0f);

        am_mdelay(500);
    }
}


/* end of file */
