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
 * \brief I2C �ӻ����̣��жϷ�ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_10 �������� I2C ������ SCL ���ţ�
 *   2. PIO0_11 �������� I2C ������ SDA ���š�
 *
 * - ʵ������
 *   1. �ӻ���������д��ַ�����ݵ��ӻ�����ͨ�����ڴ�ӡ������
 *   2. �ӻ������������������ݣ���ͨ�����ڴ�ӡ����
 *   3. LED0 �� 200ms ʱ������˸��
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_i2c_slave_int.c src_am845_core_hw_i2c_slave_int
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-13  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_i2c_slave_int
 * \copydoc demo_am845_core_hw_i2c_slave_int.c
 */

/** [src_am845_core_hw_i2c_slave_int] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x.h"
#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_i2c_slave_int_entry (void)
{

    AM_DBG_INFO("demo am845 I2C slave int mode.\r\n");

    am_gpio_pin_cfg(PIO0_10, PIO0_10_I2C0_SCL);
    am_gpio_pin_cfg(PIO0_11, PIO0_11_I2C0_SDA);

    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_I2C0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_I2C0);
    amhw_lpc84x_clk_i2c0_clk_sel_set (AMHW_LPC84X_CLK_DEVICE_FRG0CLK);

    demo_lpc_hw_i2c_slave_int_entry(LPC84X_I2C0, INUM_I2C0);

}
/** [src_am845_core_hw_i2c_slave_int] */

/* end of file */
