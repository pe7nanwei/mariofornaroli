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
 * \brief �����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Դ��ڴ�ӡ�����¼���
 *
 * \note
<<<<<<< HEAD
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO1_3 ���ƣ�
=======
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO1_8 ���ƣ�
>>>>>>> c30fd2a269cc42c5f6c688e5b171a7fb5b8e6b85
 *    2. ʹ�ð�����Ҫ�� J14 ����ñ�� KEY �� PIO1_11 �̽ӣ��ұ����� am_prj_config.h
 *       �ڽ� AM_CFG_KEY_GPIO_ENABLE ����Ϊ 1�����ú��Ѿ�Ĭ������Ϊ 1�� �û�������
 *       �����ã�
 *    3. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_key_input_event.c src_am845_core_std_key_input_event
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-8  hbt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_key_input_event
 * \copydoc demo_am845_core_std_key_input_event.c
 */

/** [src_am845_core_std_key_input_event] */
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_key_input_event_entry (void)
{
    AM_DBG_INFO("demo am845 std input event!\r\n");

    demo_std_key_entry();
}
/** [src_am845_core_std_key_input_event] */

/* end of file */
