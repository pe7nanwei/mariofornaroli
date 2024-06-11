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
 * - �������裺
 *   1. ʹ��Ӧ���ж������ϲ����½��ء�
 *
 * - ʵ������
 *   1. �жϲ���ʱ���Դ������ "the gpio interrupt happen!"��
 *
 * \par Դ����
 * \snippet demo_std_gpio_trigger.c src_std_gpio_trigger
 *
 * \internal
 * \par Modification History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_gpio_trigger
 * \copydoc demo_std_gpio_trigger.c
 */

/** [src_std_gpio_trigger] */
#include "ametal.h"
#include "am_gpio.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**
 * \brief �����жϷ�����
 */
static void __gpio_isr (void *p_arg)
{
    int arg = (int)p_arg;

    if (arg == 0) {
        AM_DBG_INFO("the gpio interrupt happen!\r\n");
    }
}

/**
 * \brief �������
 */
void demo_std_gpio_trigger_entry (int pin)
{

    /* ���������жϷ����� */
    am_gpio_trigger_connect(pin, __gpio_isr, (void *)0);

    /* ���������жϴ�����ʽ */
    am_gpio_trigger_cfg(pin, AM_GPIO_TRIGGER_FALL);

    /* ʹ�����Ŵ����ж� */
    am_gpio_trigger_on(pin);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_gpio_trigger] */

/* end of file */
