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
 * \brief �����嵥4.55
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "buzzer.h"
#include "led.h"
#include "matrixkey.h"
#include "digitron1.h"
#include "lm75.h"
#include "am_delay.h"
static uint8_t g_temp_high  = 30;          // �¶�����ֵ����ʼΪ30��
static uint8_t g_temp_low   = 28;          // �¶�����ֵ����ʼΪ28��
static uint8_t adj_state    = 0;           // 0-����״̬��1-��������״̬, 2-��������״̬
static uint8_t adj_pos;                    // ��ǰ���ڵ�λ���л�Ϊ����ģʽʱ����ʼΪ���ڸ�λ

static void key_state_process (void)       // ״̬��������KEY0
{
    adj_state = (adj_state + 1) % 3;       // ״̬�л���0 ~ 2
    if (adj_state == 1) {
        // ״̬�л�����������״̬
        led_on(0);        led_off(1);
        adj_pos = 1;
        digitron1_disp_blink_set(adj_pos,AM_TRUE);     // ����λ��λ��˸
        digitron1_disp_num_set(0, g_temp_high / 10);   // ��ʾ�¶�����ֵʮλ
        digitron1_disp_num_set(1, g_temp_high % 10);   // ��ʾ�¶�����ֵ��λ
    } else if (adj_state == 2) {
        // ״̬�л�����������״̬
        led_on(1);        led_off(0);
        digitron1_disp_blink_set(adj_pos, AM_FALSE);   // ��ǰ����λֹͣ��˸
        adj_pos = 1;                                  // ����λ�ָ�Ϊ��λ
        digitron1_disp_blink_set(adj_pos, AM_TRUE);
        digitron1_disp_num_set(0,g_temp_low / 10);
        digitron1_disp_num_set(1,g_temp_low % 10);
    } else {
        // �л�Ϊ����״̬
        led_off(0);        led_off(1);    
        digitron1_disp_blink_set(adj_pos, AM_FALSE);  // ��ǰ����λֹͣ��˸
        adj_pos = 1;                                 // ����λ�ָ�Ϊ��λ
    }
}

#define VAL_ADJ_TYPE_ADD        1
#define VAL_ADJ_TYPE_SUB        0

static void key_val_process(uint8_t type)            // ����ֵ���ú�����1-�ӣ�0-����
{                                                   
    uint8_t num_single;                              // ������ֵʱ����ʱ��¼��λ����
    uint8_t num_ten;                                 // ������ֵʱ����ʱ��¼ʮλ����

    if (adj_state == 0)                              // ����״̬�����������
        return;
    if (adj_state == 1) {
        num_single = g_temp_high % 10;               // ��������ֵ
        num_ten   = g_temp_high / 10;
    } else if (adj_state == 2){
        num_single = g_temp_low % 10;                // ��������ֵ
        num_ten   = g_temp_low / 10;
    }
    if (type == 1) {                                 // ��1����
        if (adj_pos == 1) {
            num_single = (num_single + 1) % 10;      // ��λ��1��0 ~ 9
        } else {
            num_ten   = (num_ten + 1) % 10;          // ʮλ��1��0 ~ 9
        }
        } else {                                     // ��1����
        if (adj_pos == 1) {
            num_single = (num_single - 1 + 10) % 10; // ��λ��1��0 ~ 9
        } else {
            num_ten   = (num_ten - 1 + 10) % 10;     // ʮλ��1��0 ~ 9
        }
    }
    if (adj_state == 1) {
        if (num_ten * 10 + num_single >= g_temp_low) {
            g_temp_high = num_ten * 10 + num_single;    // ȷ������Ч������
        } else {
            num_ten   = g_temp_high / 10;               // ��Ч�����ã�ֵ����
            num_single = g_temp_high % 10; 
        }
    } else if (adj_state == 2){
        if (num_ten * 10 + num_single <= g_temp_high) {
            g_temp_low = num_ten * 10 + num_single;     // ȷ������Ч������
        } else {
            num_ten   = g_temp_low / 10;                // ��Ч�����ã�ֵ����
            num_single = g_temp_low % 10;
        }
    }
    digitron1_disp_num_set(0, num_ten);                  // ������ʾ����ʮλ
    digitron1_disp_num_set(1, num_single);               // ������ʾ���ĸ�λ
}

static void key_pos_process(void)                       // ����λ�л�
{
    if (adj_state != 0) {
        // ��ǰ���ڵ���ģʽ�в������л�����λ
        digitron1_disp_blink_set(adj_pos, AM_FALSE);
        adj_pos = !adj_pos;
        digitron1_disp_blink_set(adj_pos, AM_TRUE);
    }
}

static void key_process (uint8_t code)
{
    switch (code) {
    case 0: 
        key_state_process();                          // ����״̬�л�
        break;
        case 1:                                       // ��ǰ����λ��1
        key_val_process(VAL_ADJ_TYPE_ADD);
        break;
        case 2:                                       // �л���ǰ����λ
        key_pos_process();
        break;
    case 3:                                           // ��ǰ����λ��1
        key_val_process(VAL_ADJ_TYPE_SUB);
        break;
        default:
        break;
    }
}

int am_main(void)
{
    uint8_t key_code;
    int16_t temp;                                     // �����¶�ֵ
    int i = 0;
    // �����GPIO��������ܣ���ֻҪ��digitron_init()��digitron_disp_scan()�滻��Ӧ�ĺ�������
    buzzer_init();
    led_init();
    matrixkey_init();
    digitron1_hc595_init();                            // digitron_init();
    lm75_init();
    while(1) {
        // �¶ȶ�ȡģ��,����ģʽ�£���ʾ�¶�ֵ��500msִ��һ��
            if (adj_state == 0) {
                temp = lm75_read();
                if (temp < 0) {
                temp = -1 * temp;                     // �¶�Ϊ��ʱ��Ҳֻ��ʾ�¶���ֵ
                }
                temp = temp >> 8;                     //  tempֻ�����¶���������
                digitron1_disp_num_set(0, temp / 10);
                digitron1_disp_num_set(1, temp % 10);
                if (temp > g_temp_high || temp < g_temp_low) {
                buzzer_on();
                } else {
                buzzer_off();
                }
            }
            for (i = 0; i < 100; i++) {
            // �������ÿ��5msɨ��һ�Σ�100�μ�Ϊ500ms
            key_code = matrixkey_scan_with_digitron(digitron1_hc595_disp_scan);
            if (key_code != 0xFF) {
                if ((key_code & 0x80) == 0) {      // ��������ʱ�����������֡�һ��
                    buzzer_beep_async(100);        // �첽��ʽ
                    key_process(key_code);         // �а����¼�����
                }
            }
						// ������̺������ÿ��5msɨ��һ�� 100 �� ��Ϊ 500ms
            if ((adj_state == 0) && (((i + 1) % 50) == 0)) {
                led_toggle(0);    led_toggle(1);
            }
            am_mdelay(5);
        }
    }
}




/* end of file */

