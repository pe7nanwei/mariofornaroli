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
 * \snippet demo_am845_core_hw_gpio_int.c src_am845_core_hw_gpio_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_gpio_int
 * \copydoc demo_am845_core_hw_gpio_int.c
 */

/** [src_am845_core_hw_gpio_int] */
#include "ametal.h"
#include "hw/amhw_lpc84x_syscon.h"
#include "am_vdebug.h"
#include "am_int.h"
#include "hw/amhw_lpc84x_gpio.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "demo_nxp_entries.h"
#include "lpc84x_inum.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO1_8

/** \brief �������� */
#define __KEY_PIN  PIO1_11

/**
 * \brief �������
 */
void demo_am845_core_hw_gpio_int_entry (void)
{

    am_kprintf("demo am845 hw gpio int!\r\n");

    /* ���� LED ���ŷ���Ϊ��� */
    amhw_lpc84x_gpio_pin_dir_output(LPC84X_GPIO, __LED0_PIN);

    /* ���� KEY ���ŷ���Ϊ���� */
    amhw_lpc84x_gpio_pin_dir_input(LPC84X_GPIO, __KEY_PIN);

    /* ���� KEY ����Ϊ���� */
    amhw_lpc84x_iocon_mode_set(LPC84X_IOCON, __KEY_PIN,
                               AMHW_LPC84X_IOCON_MODE_PULLUP);

    /* ����Ϊ�½��ش��� */
    amhw_lpc82x_pint_trigger_set(LPC84X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_FALL);

    demo_lpc845_hw_gpio_int_entry(__KEY_PIN,
                                  __LED0_PIN,
                                  AMHW_LPC82X_PINT_CHAN_0,
                                  INUM_PIN_INT0);

}
/** [src_am845_core_hw_gpio_int] */

/* end of file */
