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
 * \brief GPIO ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��� 0.5s��LED0 ��˸ 5 �Σ�
 *   2. ֮��LED0 �� 0.2s �ļ��һֱ��˸��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_gpio.c src_am845_core_hw_gpio
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_gpio
 * \copydoc demo_am845_core_hw_gpio.c
 */

/** [src_am845_core_hw_gpio] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_gpio.h"
#include "demo_nxp_entries.h"
#include "lpc84x_periph_map.h"
#include "lpc84x_pin.h"
/** \brief LED0 ���� */
#define __LED_PIN  PIO1_8

extern void demo_lpc845_hw_gpio_entry (amhw_lpc84x_gpio_t *p_hw_gpio,
                                       int                 pin);

/**
 * \brief �������
 */
void demo_am845_core_hw_gpio_entry (void)
{
  
    am_kprintf("demo am845_core hw gpio!\r\n");
  
    /* �������ŷ���Ϊ��� */
    amhw_lpc84x_gpio_pin_dir_output(LPC84X_GPIO, __LED_PIN);

    demo_lpc845_hw_gpio_entry(LPC84X_GPIO, __LED_PIN);
}
/** [src_am845_core_hw_gpio] */

/* end of file */
