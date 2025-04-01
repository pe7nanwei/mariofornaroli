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
 * \brief �������̣�4��������
 *
 * ������չʾ�� 4�������İ������ͷŴ�������ӡ��Ϣ��Ϊ����ʾ������4��������Ӧ��
 * ��������̶�Ϊ��KEY_0��KEY_1��KEY_2��KEY_3�����и�����ʱ��Ӧȷ��ϵͳ��4��������
 * �����Ƕ�Ӧ�İ�������Ϊ��KEY_0 ~ KEY_4
 *
 * - ��������
 *   1. ������ں���
 *
 * - ʵ������
 *   1. ���°���ʱ�����Դ��ڴ�ӡ��ǰ������Ϣ��
 *
 * \par Դ����
 * \snippet demo_std_4key.c src_std_4key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_4key
 * \copydoc demo_std_4key.c
 */

/** [src_std_4key] */
#include "ametal.h"
#include "am_delay.h"
#include "am_input.h"
#include "am_vdebug.h"
#include "am_event_input_key.h"
#include "am_event_category_input.h"

static void __input_key_proc (void *p_arg, int key_code, int key_state, int keep_time)
{
    switch (key_code) {

    case KEY_0:
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
            AM_DBG_INFO("key0 Press! Keep_time is %d\r\n", keep_time);
        } else if (key_state == AM_INPUT_KEY_STATE_RELEASED){
            AM_DBG_INFO("key0 Released! \r\n");
        }

        break;

    case KEY_1:
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
            AM_DBG_INFO("key1 Press! Keep_time is %d\r\n", keep_time);
        } else if (key_state == AM_INPUT_KEY_STATE_RELEASED){
            AM_DBG_INFO("key1 Released! \r\n");
        }

        break;

    case KEY_2:
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
            AM_DBG_INFO("key2 Press! Keep_time is %d\r\n", keep_time);
        } else if (key_state == AM_INPUT_KEY_STATE_RELEASED){
            AM_DBG_INFO("key2 Released! \r\n");
        }

        break;

    case KEY_3:
        if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
            AM_DBG_INFO("key3 Press! Keep_time is %d\r\n", keep_time);
        } else if (key_state == AM_INPUT_KEY_STATE_RELEASED){
            AM_DBG_INFO("key3 Released! \r\n");
        }

        break;

    default :
        break;
    }
 }

/**
 * \brief �������
 */
void demo_std_4key_entry (void)
{
    static am_input_key_handler_t key_handler;

    am_input_key_handler_register(&key_handler, __input_key_proc, NULL);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_4key] */

/* end of file */
