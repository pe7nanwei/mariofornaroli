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
 * \brief UART ���λ��������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "UART interrupt mode(Add ring buffer) test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *       PIOA_9 �������� PC ���ڵ� RXD��
 *    2. ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()����
 *
 * \par Դ����
 * \snippet demo_zmf159_std_uart_ringbuf.c src_zmf159_std_uart_ringbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-18  ari, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_std_uart_ringbuf
 * \copydoc demo_zmf159_std_uart_ringbuf.c
 */

/** [src_zmf159_std_uart_ringbuf] */
#include <demo_zmf159_core_entries.h>
#include "ametal.h"
#include "am_zmf159_inst_init.h"
#include "demo_std_entries.h"
#include "am_vdebug.h"
/**
 * \brief �������
 */
void demo_zmf159_core_std_uart_ringbuf_entry (void)
{
    AM_DBG_INFO("demo zmf159_core std uart ringbuf!\r\n");

     /* �ȴ������������ */
    am_mdelay(100);

    demo_std_uart_ringbuf_entry(am_zmf159_uart1_inst_init());
}
/** [src_zmf159_std_uart_ringbuf] */

/* end of file */
