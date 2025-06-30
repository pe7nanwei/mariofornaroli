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
 * \brief �����嵥7.63
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_buzzer.h"
#include "am_led.h"
#include "am_input.h"
#include "am_digitron_disp.h"
#include "am_temp.h"
#include "am_hwconf_lm75.h"
#include "am_hwconf_miniport.h"
#include "string.h"

static uint8_t g_temp_high = 30;            // �¶�����ֵ����ʼΪ30��
static uint8_t g_temp_low  = 25;            // �¶�����ֵ����ʼΪ28��
static uint8_t adj_state   = 0;             // 0-����״̬��1-��������״̬, 2-��������״̬
static uint8_t adj_pos;                     // ��ǰ���ڵ�λ���л�Ϊ����ģʽʱ����ʼΪ���ڸ�λ

static void __digitron_disp_num (int num)
{
    char buf[3];
    am_snprintf(buf, 3, "%2d", num);
    am_digitron_disp_str(0, 0, strlen(buf), buf);
}

static void key_state_process (void)       // ״̬��������KEY0
{
    adj_state = (adj_state + 1) % 3;       // ״̬�л���0 ~ 2
    if (adj_state == 1) {
        // ״̬�л�����������״̬
        am_led_on(0);
        am_led_off(1);
        adj_pos = 1;
        am_digitron_disp_blink_set(0, adj_pos, AM_TRUE);    // ����λ��λ��˸
        __digitron_disp_num(g_temp_high);                   // ��ʾ�¶�����ֵ
    } else if (adj_state == 2) {
        // ״̬�л�����������״̬
        am_led_on(1);
        am_led_off(0);
        am_digitron_disp_blink_set(0, adj_pos, AM_FALSE);   // ��ǰ����λֹͣ��˸
        adj_pos = 1;                                        // ����λ�ָ�Ϊ��λ
        am_digitron_disp_blink_set(0, adj_pos, AM_TRUE);
        __digitron_disp_num(g_temp_low);                    // ��ʾ�¶�����ֵ
    } else {
        // �л�Ϊ����״̬
        am_led_off(0);
        am_led_off(1);
        am_digitron_disp_blink_set(0, adj_pos, AM_FALSE);   // ��ǰ����λֹͣ��˸
        adj_pos = 1;                                        // ����λ�ָ�Ϊ��λ
    }
}

#define VAL_ADJ_TYPE_ADD    1
#define VAL_ADJ_TYPE_SUB    0

static void key_val_process(uint8_t type)                  // ����ֵ���ú�����1-�ӣ�0-����
{
    uint8_t num_single    =     0;                         // ������ֵʱ����ʱ��¼��λ����
    uint8_t num_ten     =     0;                           // ������ֵʱ����ʱ��¼ʮλ����

    if (adj_state == 0)                                    // ����״̬�����������
        return;
    if (adj_state == 1) {
        num_single = g_temp_high % 10;                     // ��������ֵ
        num_ten    = g_temp_high / 10;
    } else if (adj_state == 2){
        num_single = g_temp_low % 10;                      // ��������ֵ
        num_ten    = g_temp_low / 10;
    }
    if (type == VAL_ADJ_TYPE_ADD) {                        // ��1����
        if (adj_pos == 1) {
            num_single = (num_single + 1) % 10;            // ��λ��1��0 ~ 9
        } else {
            num_ten   = (num_ten + 1) % 10;                // ʮλ��1��0 ~ 9
        }
    } else {                                               // ��1����
        if (adj_pos == 1) {
            num_single = (num_single - 1 + 10) % 10;       // ��λ��1��0 ~ 9
        } else {
            num_ten   = (num_ten - 1 + 10) % 10;           // ʮλ��1��0 ~ 9
        }
    }

    if (adj_state == 1) {
        if (num_ten * 10 + num_single >= g_temp_low) {
            g_temp_high = num_ten * 10 + num_single;       // ȷ������Ч������
        } else {
            num_ten    = g_temp_high / 10;                 // ��Ч�����ã�ֵ����
            num_single = g_temp_high % 10;
        }
        __digitron_disp_num(g_temp_high);                  // ��ʾ�¶�����ֵ
    } else if (adj_state == 2) {
        if (num_ten * 10 + num_single <= g_temp_high) {
            g_temp_low = num_ten * 10 + num_single;        // ȷ������Ч������
        }
        __digitron_disp_num(g_temp_low);                   // ��ʾ�¶�����ֵ
    }
}

static void key_pos_process(void)                           // ����λ�л�
{
    if (adj_state != 0) {
        // ��ǰ���ڵ���ģʽ�в������л�����λ
        am_digitron_disp_blink_set(0, adj_pos, AM_FALSE);
        adj_pos = !adj_pos;
        am_digitron_disp_blink_set(0, adj_pos, AM_TRUE);
    }
}

static void key_callback (void *p_arg,int key_code, int key_state, int keep_time)
{
    if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
        switch (key_code) {
        case KEY_0:                       // ����״̬�л�
            key_state_process();
            break;
        case KEY_1:                       // ��ǰ����λ��1
            key_val_process(VAL_ADJ_TYPE_ADD);
            break;
        case KEY_2:                      // �л���ǰ����λ
            key_pos_process();
            break;
        case KEY_3:                      // ��ǰ����λ��1
            key_val_process(VAL_ADJ_TYPE_SUB);
            break;
        default:
            break;
        }
    }
}

int am_main (void)
{
    am_temp_handle_t         temp_handle = am_temp_lm75_inst_init();; // �¶ȴ��������
    am_input_key_handler_t   key_handler;
    int32_t                  temp;

    // ��ʼ����������8��ASCII����
    am_miniport_view_key_inst_init();
    am_digitron_disp_decode_set(0, am_digitron_seg8_ascii_decode);
    am_input_key_handler_register(&key_handler, key_callback, NULL);
    while(1) {
        // �¶ȶ�ȡģ��,����ģʽ�£���ʾ�¶�ֵ��500msִ��һ�Σ�LED��˸
        if (adj_state == 0) {
            am_temp_read(temp_handle, &temp);
            if (temp < 0) {
                temp = -1 * temp;            // �¶�Ϊ��ʱ��Ҳֻ��ʾ�¶���ֵ
            }
            temp = temp / 1000;              //  temp_cur ֻ�����¶���������
            __digitron_disp_num(temp);
            if (temp > g_temp_high || temp < g_temp_low ) {
                am_buzzer_on();
            } else {
                am_buzzer_off();
            }
            am_led_toggle(0);
            am_led_toggle(1);
            am_mdelay(500);
        }
    }
}



/* end of file */

