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
 * \brief I2C ��ѯģʽ�²��� EEPROM ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIOC_8 �������� EEPROM �� SCL ���ţ�
 *   2. PIOC_9 �������� EEPROM �� SDA ���š�
 *
 * - ʵ������
 *   1. �� EEPROM �豸д�� 8�ֽڣ�С�ڻ����һҳ�����ݣ�
 *   2. ��ȡ EEPROM �е�����ͨ�����ڴ�ӡ������
 *   3. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED0 �� 200ms �����˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIOC_9 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    3. ��ǰ I2C �� SCL ����ʹ�õ��� PIOB_6��SDA ����ʹ�õ��� PIOB_7��
 *       �ɸ���ʵ������������š�
 *
 * \par Դ����
 * \snippet demo_zmf159_hw_i2c_master_poll.c src_zmf159_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 17-09-5  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_i2c_master_poll
 * \copydoc demo_zmf159_hw_i2c_master_poll.c
 */

/** [src_zmf159_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "amhw_zmf159_rcc.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

#define I2C_MASTER    (amhw_zlg_i2c_t *)ZMF159_I2C2_BASE   /**< \brief I2C����������ͨ���Ŷ��� */

/**
 * \brief �������
 */
void demo_zmf159_core_hw_i2c_master_poll_entry (void)
{

    am_kprintf("demo zmf159_core hw i2c master poll!\r\n");

    /**
     * PIOC_8 ~ I2C2_SCL, PIOC_9 ~ I2C2_SDA
     */
    am_gpio_pin_cfg(PIOC_8, PIOC_8_I2C2_SCL | PIOC_8_AF_OD | PIOC_8_SPEED_20MHz);
    am_gpio_pin_cfg(PIOC_9, PIOC_9_I2C2_SDA | PIOC_9_AF_OD | PIOC_9_SPEED_20MHz);

    am_clk_enable(CLK_I2C2);
    am_zmf159_clk_reset(CLK_I2C2);

    demo_zlg_hw_i2c_master_poll_entry(I2C_MASTER, am_clk_rate_get(CLK_APB1));

}
/** [src_zmf159_hw_i2c_master_poll] */

/* end of file */
