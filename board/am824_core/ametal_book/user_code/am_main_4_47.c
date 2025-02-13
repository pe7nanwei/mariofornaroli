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
 * \brief �����嵥4.47
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "matrixkey.h"
#include "digitron1.h"
#include "am_delay.h"

static uint8_t g_disp_num = 0;

static void key_process (uint8_t code)
{
    static uint8_t adj_state = 0;                           // ����״̬Ϊ0������״̬Ϊ1
    static uint8_t adj_pos;                                 // ��˸λ����ʼ��ʱ��λ��˸
    uint8_t        num_single;                              // ��λ������
    uint8_t        num_ten;                                 // ʮλ������

    switch (code) {
    case 0:  
            adj_state = !adj_state;                         // ״̬��ת
            if (adj_state == 1) {                           // �л�������״̬
                digitron1_disp_blink_set(1, AM_TRUE);       // ��λ��˸
            } else {                                        // �л�������״̬
                digitron1_disp_blink_set(adj_pos, AM_FALSE);// ֹͣ��˸
                adj_pos = 1;
            }
           break;
    case 1:                                                 // ��˸λ��1
            if (adj_state == 1) {    
                num_single = g_disp_num % 10;
                num_ten   = g_disp_num / 10;
                if (adj_pos == 1) {
                    num_single = (num_single + 1) % 10;     // ��λ��1��0 ~ 9
                } else {
                    num_ten   = (num_ten + 1) % 10;         // ʮλ��1��0 ~ 9
                }
                g_disp_num = num_ten * 10 + num_single;
                digitron1_disp_num_set(0,num_ten);          // ������ʾ����ʮλ
                digitron1_disp_num_set(1,num_single);       // ������ʾ���ĸ�λ
        }
        break;
    case 2:                                                // �л�����λ
        if (adj_state == 1) {
                digitron1_disp_blink_set(adj_pos, AM_FALSE);
                adj_pos = !adj_pos;
                digitron1_disp_blink_set(adj_pos, AM_TRUE);
            }
            break;
    case 3:                                                  // ��˸λ��1
            num_single = g_disp_num % 10;
            num_ten   = g_disp_num / 10;
            if (adj_state == 1) {
                if (adj_pos == 1) {
                    num_single = (num_single - 1 + 10) % 10; // ��λ��1��0 ~ 9
                } else {                                     
                    num_ten   = (num_ten - 1 + 10) % 10;     // ʮλ��1��0 ~ 9
                }
            }
            g_disp_num = num_ten * 10 + num_single;
            digitron1_disp_num_set(0,num_ten);                // ������ʾ����ʮλ
            digitron1_disp_num_set(1,num_single);             // ������ʾ���ĸ�λ
            break;
    default:
            break;
    }
}

int am_main(void)
{
    uint8_t key_return;

    matrixkey_init();
    digitron1_init();
    digitron1_disp_num_set(0,g_disp_num / 10);                 // ������ʾ����ʮλ
    digitron1_disp_num_set(1,g_disp_num % 10);                 // ������ʾ���ĸ�λ
    while(1) {
        key_return = matrixkey_scan_with_digitron(digitron1_disp_scan);

        if (key_return!= 0xFF) {
            // �а����¼�����
            key_process(key_return);
        }
				am_mdelay(5);
    } 
}


/* end of file */

