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
 * \brief UART �жϷ������̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "HW example---UART test in interrupt mode:"��
 *   2. ����������յ����ַ���
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zmf159_hw_uart_int.c src_zmf159_hw_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 17-01-20  ari, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_zmf159_hw_uart_int
 * \copydoc demo_zmf159_hw_uart_int.c
 */

/** [src_zmf159_hw_uart_int] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_zmf159.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "demo_zlg_entries.h"

static void __zmf159_uart_pins_init (void)
{
    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_9,  PIOA_9_UART1_TX | PIOA_9_AF_PP );
    am_gpio_pin_cfg(PIOA_10, PIOA_10_UART1_RX| PIOA_10_INPUT_FLOAT);
}

/**
 * \brief �������
 */
void demo_zmf159_core_hw_uart_int_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw uart int!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    /* ʹ��ʱ�� */
    am_clk_enable(CLK_UART1);

    demo_zlg_hw_uart_int_entry(ZMF159_UART1,
                               __zmf159_uart_pins_init,
                               am_clk_rate_get(CLK_UART1),
                               ZMF159_UART1_BASE,
                               INUM_UART1);
}
/** [src_zmf159_hw_uart_int] */

/* end of file */
