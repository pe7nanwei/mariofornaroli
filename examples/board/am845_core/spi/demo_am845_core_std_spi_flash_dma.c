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
 * \brief SPI ��д FLASH(MX25L3206E) ���̣�DMA ��ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� SPI0 �� SPI FLASH �����������ӡ�
 *
 * - ʵ������
 *   1. д�����ݵ� SPI FLASH ����ȡ��������У�飬������ȡ��������ͨ�����������
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_14 �������� PC ���ڵ� TXD��
 *    PIO0_23 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_spi_flash_dma.c src_am845_core_std_spi_flash_dma
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_spi_flash_dma
 * \copydoc demo_am845_core_std_spi_flash_dma.c
 */

/** [src_am845_core_std_spi_flash_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_spi_flash_dma_entry (void)
{

    AM_DBG_INFO("demo am845_core std spi flash dma!\r\n");

    demo_std_spi_flash_entry(am_lpc84x_spi0_dma_inst_init(), PIO0_10, 0, 256);
}
/** [src_am845_core_std_spi_flash_dma] */

/* end of file */
