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
 * \brief SPI �ػ����̣��жϷ�ʽ����ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �̽� SPI �� MOSI(PIO0_18) �� MISO(PIO0_19)��
 *
 * - ʵ������
 *   1. ��������һ�δ��䣬��У�鷢�͵���������յ������Ƿ�һ�£�
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_spi_master_int.c src_am845_core_std_spi_master_int
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_spi_master_int
 * \copydoc demo_am845_core_std_spi_master_int.c
 */

/** [src_am845_core_std_spi_master_int] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_spi_master_int_entry (void)
{
    am_kprintf("demo am845 std spi master int!\r\n");
  
    am_spi_handle_t spi_handle = am_lpc84x_spi0_int_inst_init();
    demo_std_spi_master_entry(spi_handle, PIO0_10);
}
/** [src_am845_core_std_spi_master_int] */

/* end of file */
