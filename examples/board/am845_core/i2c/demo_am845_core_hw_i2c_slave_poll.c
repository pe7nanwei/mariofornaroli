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
 * \brief I2C �ӻ����̣���ѯ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� I2C ������ SCL ���ţ�
 *   2. PIO0_11 �������� I2C ������ SDA ���š�
 *
 * \note
 *    �����̿�������ģ�� EEPROM��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_i2c_slave_poll.c src_am845_core_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-10  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_i2c_slave_poll
 * \copydoc demo_am845_core_hw_i2c_slave_poll.c
 */

/** [src_am845_core_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x.h"
#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_i2c_slave_poll_entry (void)
{
    AM_DBG_INFO("demo am845 I2C slave poll.\r\n");

    am_gpio_pin_cfg(PIO0_10, PIO0_10_I2C0_SCL);
    am_gpio_pin_cfg(PIO0_11, PIO0_11_I2C0_SDA);

    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_I2C0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_I2C0);
    amhw_lpc84x_clk_i2c0_clk_sel_set (AMHW_LPC84X_CLK_DEVICE_FRG0CLK);
  
    demo_lpc_hw_i2c_slave_poll_entry(LPC84X_I2C0);
}
/** [src_am845_core_hw_i2c_slave_poll] */

/* end of file */
