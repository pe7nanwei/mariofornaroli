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
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸��
 *   2. PIO0_17 ���ŵ������ƽ״̬�� 8KHz ��Ƶ�ʱ任������ 4KHz �Ĳ��Ρ�
 *
 * \note
 *    1. ���� MRT Ĭ����Ϊϵͳ1�δ�ʹ�ã�ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_SOFTIMER_ENABLE�� AM_CFG_SYSTEM_TICK_ENABLE �Լ�
 *       AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0����ʹ�������ʱ����ϵͳ��ડ����ض���������
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_mrt.c src_am845_core_hw_mrt
 *
 * \internal
 * \par History
 *
 * - 1.01 15-12-02  mem ,modified
 * - 1.00 15-07-15  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_mrt
 * \copydoc demo_am845_core_hw_mrt.c
 */

/** [src_am845_core_hw_mrt] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_mrt_entry (void)
{
    am_kprintf("demo am845_core hw mrt!\r\n");
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_MRT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_MRT);

    am_gpio_pin_cfg(PIO0_17, AM_GPIO_OUTPUT_INIT_HIGH);

    demo_lpc845_hw_mrt_entry(LPC84X_MRT, INUM_MRT);
}
/** [src_am845_core_hw_mrt] */

/* end of file */
