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
 * \brief �����嵥6.1105
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-19  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg72128.h"
#include "am_delay.h"
#include "am_hwconf_zlg72128.h"

struct key_event_info {                        // �����¼���Ϣ�ṹ�����Ͷ���
    am_bool_t    key_event;                    // �Ƿ��а����¼�
    uint8_t      key_val;                      // ��ͨ������ֵ
    uint8_t      repeat_cnt;                   // ��ͨ�����ظ�����
    uint8_t      funkey_val;                   // ���ܼ���ֵ
};
struct key_event_info g_key_event_info;        // �ṹ����������Ա��水����Ϣ

// �Զ��尴������ص�����
static void zlg72128_key_callback(void      *p_arg,      // �û�������ע��ص�����ʱָ��
                                  uint8_t    key_val,    // ��ͨ������ֵ
                                  uint8_t    repeat_cnt, // ����������
                                  uint8_t    funkey_val) // ���ܼ���ֵ
{                                                        
    if (g_key_event_info.key_event == AM_FALSE)  {       // �ް����¼�����������µļ�ֵ
        g_key_event_info.key_val     =  key_val;
        g_key_event_info.repeat_cnt  =  repeat_cnt;
        g_key_event_info.funkey_val  =  funkey_val;
        g_key_event_info.key_event   =  AM_TRUE ;
    }
}


static void digitron_test_process (am_zlg72128_handle_t handle)
{
    am_zlg72128_digitron_disp_test(handle);    // ��������
    am_mdelay(3000);                           // ��ʱ3s,ʹ�ܲ��������3s
    am_zlg72128_digitron_disp_reset(handle);   // ��λ�������ʾ
}

static void normal_key_test_process (am_zlg72128_handle_t   handle, // ZLG72128�������
                                     uint8_t               key_val) // ��ͨ����ֵ
{
    // �����1��ʾʮλ��ʮλΪ0ʱ����ʾ����ʾ�ո񣩣�����ʾС���㣬����˸
    if (g_key_event_info.key_val / 10 != 0) {
        am_zlg72128_digitron_disp_num(handle, 1,key_val / 10, AM_FALSE,AM_FALSE );
    } else {
        am_zlg72128_digitron_disp_char(handle, 1, ' ',AM_FALSE,AM_FALSE );
    }
    // �������0��ʾ��λ������ʾС���㣬����˸
    am_zlg72128_digitron_disp_num(handle, 0, key_val % 10, AM_FALSE,AM_FALSE );   
}

static void combination_key_process(am_zlg72128_handle_t   handle,       // ZLG72128�������
                                    uint8_t                key_val,      // ��ͨ����ֵ
                                    uint8_t                funckey_val)  // ���ܼ���ֵ
{
    static uint16_t flash = 0x0000;               // ��ʼʱ������δ������˸
    if ((funckey_val & (1 << 0)) == 0) {          // F0 ����
        switch (key_val) {
           case 1:                // ѭ�����ƶ�  
                 am_zlg72128_digitron_shift(
                     handle,
                     AM_ZLG72128_DIGITRON_SHIFT_LEFT,
                     AM_TRUE, 
                     1);
           break;
         case 2:                // ѭ�����ƶ�
             am_zlg72128_digitron_shift(
                 handle, 
                 AM_ZLG72128_DIGITRON_SHIFT_RIGHT,
                 AM_TRUE, 
                 1);
             break;
         case 3:                // ��/�ر���˸
           flash = ~flash;      // ȡ��������Ϊ��˸״̬�ı�
           am_zlg72128_digitron_flash_ctrl(handle, flash);
            break;
         default:
           break;
        }
    }
}

int am_main (void)
{
    am_zlg72128_handle_t zlg72128_handle = am_zlg72128_inst_init();
    am_zlg72128_key_cb_set(zlg72128_handle, zlg72128_key_callback, NULL);// ע�ᰴ���ص�����
    digitron_test_process(zlg72128_handle);                              // �������ʾ����
    while (1) {
        if (g_key_event_info.key_event == AM_TRUE) {
                 // ����ͨ�������£��������Գ���
            if ((g_key_event_info.funkey_val == 0xFF) && (g_key_event_info.key_val != 0)) {
                normal_key_test_process(zlg72128_handle, g_key_event_info.key_val);
            }
              // ��ϼ�����
            if ((g_key_event_info.funkey_val != 0xFF) && (g_key_event_info.key_val != 0)) {
                combination_key_process(
                    zlg72128_handle, g_key_event_info.key_val, g_key_event_info.funkey_val);
            }
            g_key_event_info.key_event = AM_FALSE;
        }
    }
}



/* end of file */

