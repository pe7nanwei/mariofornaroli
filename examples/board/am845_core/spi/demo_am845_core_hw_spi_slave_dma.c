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
 * \brief SPI �ӻ������������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI �ӿں�����Դ��Ӧ�� SPI �ӿ�����������
 *
 * - ʵ������
 *   1. ���յ����ݣ�ͨ�����ڴ�ӡ������
 *
 * \note
 *    1. ����Դ��ѡ�� demo_am845_core_std_spi_master_dma.c �ĳ���
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *    3. ���� PIO0_12 ���ͻᵼ�µ�Ƭ����λʱ���� ISP ģʽ������ PIO0_12 Ӧ
 *       ��Ƭ����λ�������ӡ�
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_spi_slave_dma.c src_am845_core_hw_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.01 15-11-27  sky, modified
 * - 1.00 15-07-16  aii, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_spi_slave_dma
 * \copydoc demo_am845_core_hw_spi_slave_dma.c
 */

/** [src_am845_core_hw_spi_slave_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_spi_slave_dma_entry (void)
{

    /* SPI0 �������� */
    am_gpio_pin_cfg(PIO0_10, PIO_FUNC_SPI0_SSEL0);
    am_gpio_pin_cfg(PIO0_17, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_18, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_19, PIO_FUNC_SPI0_MISO);

    /* ʹ�� SPI0 ʱ�� */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_SPI0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_SPI0);

        /* DMA ƽ̨��ʼ�� */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_DMA);
  
    demo_lpc824_hw_spi_slave_dma_entry(LPC84X_SPI0,
                                       DMA_CHAN_SPI0_RX_REQ);
}
/** [src_am845_core_hw_spi_slave_dma] */

/* end of file */
