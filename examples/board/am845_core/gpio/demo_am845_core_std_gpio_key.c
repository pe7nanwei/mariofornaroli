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
 * \brief GPIO �������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��һ�ΰ��� LED0 ��Ϩ���ٰ�һ�ΰ��� LED0 ��������˷�����
 *
 * \par Դ����
 * \snippet demo_am845_core_std_gpio_key.c src_am845_core_std_gpio_key
 *
 * \internal
 * \par Modification history
 * - 1.00 15-11-25  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_gpio_key
 * \copydoc demo_am845_core_std_gpio_key.c
 */

/** [src_am845_core_std_gpio_key] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_lpc84x_gpio.h"
#include "demo_nxp_entries.h"

/** \brief �������� */
#define __KEY_PIN  PIO1_11

/**
 * \brief �������
 */
void demo_am845_core_std_gpio_key_entry (void)
{
    AM_DBG_INFO("demo am845_core std gpio key!\r\n");

    demo_lpc_std_gpio_key_entry(__KEY_PIN);
}
/** [src_am845_core_std_gpio_key] */

/* end of file */
