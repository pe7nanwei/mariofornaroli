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
 * \brief SPI �ػ����̣�DMA ��ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� SPI �� MOSI(PIO0_18) �� MISO(PIO0_19)��
 *   2. ���� KEY������һ�δ��䡣
 *
 * - ʵ������
 *   1. ��������һ�δ��䣬��У�鷢�͵���������յ������Ƿ�һ�£�
 *   2. ���°����󣬷���һ�δ��䣬��ͨ�����ڴ�ӡ���͵���������յ����ݡ�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_spi_master_dma.c src_am_am845_core_std_spi_master_dma
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_spi_master_dma
 * \copydoc demo_am845_core_std_spi_master_dma.c
 */

/** [src_am_am845_core_std_spi_master_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_spi_master_dma_entry (void)
{
    AM_DBG_INFO("demo am845_core std spi master dma!\r\n");
  
    demo_std_spi_master_entry(am_lpc84x_spi0_dma_inst_init(), PIO0_10);
}
/** [src_am_am845_core_std_spi_master_dma] */

/* end of file */
