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
 * \brief SPI ���������������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI ������ SPI �ӻ������������ӡ�
 *
 * - ʵ������
 *   1. ������ÿ 500 ����ͨ�� SPI����ӻ����� "nihao" �ַ�����
 *   2. �ӻ����յ��ַ�����ͨ�����ڽ��ַ�����ӡ�������� LED0 ��˸��
 *
 * \note
 *    1. ��������Ҫ�� demo_am845_hw_spi_slave.c һͬ���ԣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_spi_master.c src_am845_core_hw_spi_master
 *
 * \internal
 * \par History
 * - 1.01 15-11-26  sky, modified
 * - 1.00 15-07-15  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_spi_master
 * \copydoc demo_am845_core_hw_spi_master.c
 */

/** [src_am845_core_hw_spi_master] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_spi_master_entry (void)
{
    uint32_t clk = 0;
  
    am_kprintf("demo845 hw spi master!\r\n");
  
    /* SPI0 �������� */
    am_gpio_pin_cfg(PIO0_10, PIO_FUNC_SPI0_SSEL0);
    am_gpio_pin_cfg(PIO0_17, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_18, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_19, PIO_FUNC_SPI0_MISO);

    /* ʹ�� SPI0 ʱ�� */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SPI0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SPI0);
    amhw_lpc84x_clk_spi0_clk_sel_set (AMHW_LPC84X_CLK_DEVICE_FRG0CLK);
  
    clk = amhw_lpc84x_clk_periph_freq_get(LPC84X_SPI0);
  
    demo_lpc_hw_spi_master_entry(LPC84X_SPI0, clk);
}
/** [src_am845_core_hw_spi_master] */

/* end of file */
