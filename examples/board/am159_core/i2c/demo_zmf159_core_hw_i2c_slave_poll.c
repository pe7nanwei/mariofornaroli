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
 * \brief I2C �ӻ�����(�����̿�������ģ�� EEPROM)��ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_8 �������� I2C ������ SCL ���ţ�
 *   2. PIOC_9 �������� I2C ������ SDA ���š�
 *
 * \note
 *    ��ǰ I2C �� SCL ����ʹ�õ��� PIOC_8��SDA ����ʹ�õ��� PIOC_9��
 *    �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zmf159_hw_i2c_slave_poll.c src_zmf159_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_i2c_slave_poll
 * \copydoc demo_zmf159_hw_i2c_slave_poll.c
 */

/** [src_zmf159_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "amhw_zlg_i2c.h"
#include "amhw_zmf159_rcc.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

/**
 * \brief �������
 */
void demo_zmf159_core_hw_i2c_slave_poll_entry (void)
{
    am_kprintf("demo zmf159_core hw i2c slave poll!\r\n");

    /**
     * PIOC_8 ~ I2C2_SCL, PIOC_9 ~ I2C2_SDA
     */
    am_gpio_pin_cfg(PIOC_8, PIOC_8_I2C2_SCL | PIOC_8_AF_OD | PIOC_8_SPEED_20MHz);
    am_gpio_pin_cfg(PIOC_9, PIOC_9_I2C2_SDA | PIOC_9_AF_OD | PIOC_9_SPEED_20MHz);

    am_clk_enable(CLK_I2C2);
    am_zmf159_clk_reset(CLK_I2C2);

    demo_zlg_hw_i2c_slave_poll_entry(ZMF159_I2C2);
}
/** [src_zmf159_hw_i2c_slave_poll] */

/* end of file */
