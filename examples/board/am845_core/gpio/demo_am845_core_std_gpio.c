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
 * \brief GPIO ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ʹ��������Ϊ�͵�ƽ��
 *
 * - ʵ������
 *   2. ��������Ϊ�͵�ƽʱ���������״̬��ת��
 *
 * \par Դ����
 * \snippet demo_std_gpio.c src_std_gpio
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-15  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_gpio
 * \copydoc demo_am845_core_std_gpio.c
 */

/** [src_am845_core_std_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_lpc84x_gpio.h"
#include "demo_std_entries.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO1_8

/** \brief �������� */
#define __KEY_PIN  PIO1_11

/**
 * \brief �������
 */
void demo_am845_core_std_gpio_entry (void)
{

    AM_DBG_INFO("demo am845_core std gpio!\r\n");

    demo_std_gpio_entry(__KEY_PIN, __LED0_PIN);
}
/** [src_am845_core_std_gpio] */

/* end of file */
