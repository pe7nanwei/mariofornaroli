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
 * \brief GPIO �����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO1_11 �ĵ�ƽ�ɸߵ�ƽ�ı�Ϊ�͵�ƽ������ KEY/RES ���£�ʱ��LED0 ״̬�ı䡣
 *
 * \par Դ����
 * \snippet demo_am845_core_std_gpio_int.c src_am845_core_std_gpio_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_gpio_int
 * \copydoc demo_am845_core_std_gpio_int.c
 */

/** [src_am845_core_std_gpio_int] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "demo_std_entries.h"

/** \brief �������� */
#define __KEY_PIN  PIO1_11

/**
 * \brief �������
 */
void demo_am845_core_std_gpio_int_entry (void)
{
    AM_DBG_INFO("demo am845_core std gpio trigger!\r\n");

    demo_std_gpio_trigger_entry(__KEY_PIN);
}
/** [src_am845_core_std_gpio_int] */

/* end of file */
