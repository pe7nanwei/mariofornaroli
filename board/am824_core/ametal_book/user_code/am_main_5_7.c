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
 * \brief �����嵥5.7
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_gpio.h"
#include "am_lpc82x.h"
int am_main (void)
{
    // ����GPIOΪ���ģʽ������ʼ��Ϊ�ߵ�ƽ
    am_gpio_pin_cfg(PIO0_20, AM_GPIO_OUTPUT_INIT_HIGH);
    am_gpio_set(PIO0_20, 0);                        // ����͵�ƽ������LED
    while (1) {
    }
}


/* end of file */

