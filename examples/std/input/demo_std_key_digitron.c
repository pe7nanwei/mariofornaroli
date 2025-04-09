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
 * \brief �������̣�ʹ�������ʵʱ��ʾ��ǰ���µİ���
 *
 *  ��Ӧ����Ҫʹ�õ���λ����ܣ�ָ�����������ʾ���������ٰ�����λ����ܡ�ͬʱ��
 *  ʹ�õ�4�������� 4��������Ӧ�İ�������̶�Ϊ��KEY_0��KEY_1��KEY_2��KEY_3��
 *  ���и�����ʱ��Ӧȷ��ϵͳ��4�������������Ƕ�Ӧ�İ�������Ϊ��KEY_0 ~ KEY_4
 * 
 * - ��������
 *   1. ������ں���
 *
 * - ʵ������
 *   1. ����һ����������λ�������ʾ������� 0 ~ 4��
 *   2. ż�����ʱ���������˸���������ʱ������ܲ���˸��
 *
 * \par Դ����
 * \snippet demo_std_key_digitron.c src_std_key_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-03  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_key_digitron
 * \copydoc demo_std_key_digitron.c
 */

/** [src_std_key_digitron] */
#include "ametal.h"
#include "am_input.h"
#include "am_vdebug.h"
#include "am_digitron_disp.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"

static void __digitron_disp_key_code (int id, int code)
{
    am_digitron_disp_char_at(id, 0, '0' + code / 10);     /* ʮλ */
    am_digitron_disp_char_at(id, 1, '0' + code % 10);     /* ��λ */
 
    if ((code & 0x01) == 0) {                           /* ż��ʱ�������˸    */
        am_digitron_disp_blink_set(id, 0, AM_TRUE);
        am_digitron_disp_blink_set(id, 1, AM_TRUE);
    } else {
        am_digitron_disp_blink_set(id, 0, AM_FALSE);
        am_digitron_disp_blink_set(id, 1, AM_FALSE);
    }
}

static void __input_key_proc (void *p_arg, int key_code, int key_state, int keep_time)
{
    int32_t id = *(int32_t *)p_arg;

    AM_DBG_INFO("key_code: %d, key_state :%d, keep_time is %d \r\n",
                                                key_code, key_state, keep_time);

    switch (key_code) {
    case KEY_0:
        __digitron_disp_key_code(id, 0);
        break;

    case KEY_1:
        __digitron_disp_key_code(id, 1);
        break;

    case KEY_2:
        __digitron_disp_key_code(id, 2);
        break;

    case KEY_3:
        __digitron_disp_key_code(id, 3);
        break;

    default :
        break;
    }
}

/**
 * \brief �������
 */
void demo_std_key_digitron_entry (int32_t id)
{
    static am_input_key_handler_t key_handler;
 
    /* ��ʼ��������8��ASCII���� */
    am_digitron_disp_decode_set(id, am_digitron_seg8_ascii_decode);

    /* ��ʼ�ް������£���ʾ -- */
    am_digitron_disp_char_at(id, 0, '-');
    am_digitron_disp_char_at(id, 1, '-');
    
    am_input_key_handler_register(&key_handler, __input_key_proc, &id);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_key_digitron] */

/* end of file */
