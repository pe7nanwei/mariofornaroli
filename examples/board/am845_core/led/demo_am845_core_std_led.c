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
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� LED1 �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. ���Ա����̱����� am_prj_config.h �ڽ� AM_CFG_LED_ENABLE ����Ϊ 1�����ú�
 *       �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_am845_core_std_led.c src_am845_core_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_led
 * \copydoc demo_am845_core_std_led.c
 */

/** [src_am845_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_led_entry (void)
{
    am_kprintf("demo am845_core std led!\r\n");
  
    demo_std_led_entry(LED0);
}
/** [src_am845_core_std_led] */

/* end of file */
