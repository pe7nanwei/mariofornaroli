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
 * \brief ��ѯģʽ�º��̸е�������ͨ�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ��������:
 *       1. ��J11��J13������ñ���ӣ�
 *       2. ���������������ӡ�
 *
 * - ʵ������:
 *       �Ӵӻ��������ӻ���Ϣ�򴮿ڴ�ӡ��
 *
 * \par Դ����
 * \snippet demo_amks16z_core_hw_i2c_master_poll.c src_amks16z_core_hw_i2c_master_poll
 * 
 * \internal
 * \par History
 * - 1.00 19-0`-22  bzq, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_amks16z_core_if_hw_i2c_master_poll
 * \copydoc demo_amks16z_core_hw_i2c_master_poll.c
 */
 
/** [src_amks16z_core_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_kl26_clk.h"
#include "am_gpio.h"
#include "hw/amhw_kl26_sim.h"
#include "demo_fsl_entrys.h"
#include "../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../soc/freescale/kl26/kl26_pin.h"
#include "demo_amks16z_core_all_entries.h"






/**
 * \brief ���Ժ������
 */
void demo_amks16z_core_hw_i2c_master_smoke_poll_entry (void)
{

//	demo_std_i2c_master_entry(am_kl26_i2c0_inst_init());

    uint32_t i2c_clk;

    AM_DBG_INFO("demo amks16z_core hw i2c master poll!\r\n");

    /**
     * PIOC_10 ~ I2C1_SCL, PIOC_11 ~ I2C1_SDA;
     */

    am_gpio_pin_cfg(PIOE_25, PIOE_25_I2C0_SDA | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOE_24, PIOE_24_I2C0_SCL | AM_GPIO_PULLUP);

//    am_gpio_pin_cfg(PIOB_1, PIOB_1_I2C0_SDA);
//    am_gpio_pin_cfg(PIOB_0, PIOB_0_I2C0_SCL);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2C0);

    i2c_clk = am_kl26_clk_periph_rate_get(KL26_I2C0);

    demo_fsl_hw_i2c_master_smoke_poll_entry(KL26_I2C0, i2c_clk);
}

/** [src_amks16z_core_hw_i2c_master_poll] */

/* end of file */
