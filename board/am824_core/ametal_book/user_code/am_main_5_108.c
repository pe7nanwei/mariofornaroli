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
 * \brief �����嵥5.108
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "am_uart.h"

static uint8_t     g_buf0[10] = {0};
static uint8_t     g_buf1[10] = {0};
static int         g_rx_index = 0;
static int         g_tx_index = -1;
static int         g_rx_cnt = 0;
static int         g_tx_cnt = 0;

static int __uart_txchar_get (void *p_arg, char *p_outchar)
{
    if (g_tx_index == -1)        return -AM_EEMPTY;
    if (g_tx_cnt == 10) {      // ��ǰ�������е����ݷ������
        g_tx_cnt = 0;
        return -AM_EEMPTY;
    }
    if (g_tx_index == 0) {
        *p_outchar = g_buf0[g_tx_cnt++];
    } else {
        *p_outchar = g_buf1[g_tx_cnt++];
    }
    return AM_OK;
}

static int __uart_rxchar_put (void *p_arg, char inchar)
{
    if (g_rx_index == 0) {                   // �����ݴ�ŵ�������0
        g_buf0[g_rx_cnt++] = inchar;
    } else {                                 // �����ݴ�ŵ�������1
        g_buf1[g_rx_cnt++] = inchar;
    }
    if (g_rx_cnt == 10) {                    // ���������������ͻ������е�����
        g_rx_cnt   = 0;
        g_tx_index = g_rx_index;             // ���͸û������е�����
        g_rx_index = !g_rx_index;            // �����������ݴ�ŵ�����һ����������
        am_uart_tx_startup(p_arg);           // �������ڷ���
    }
    return AM_OK;
}

int am_main (void)
{
    am_uart_handle_t uart_handle = am_lpc82x_usart0_inst_init();
    am_uart_callback_set(
        uart_handle, AM_UART_CALLBACK_TXCHAR_GET, __uart_txchar_get, uart_handle);
    am_uart_callback_set(
        uart_handle, AM_UART_CALLBACK_RXCHAR_PUT, __uart_rxchar_put, uart_handle);
    // ����Ϊ�ж�ģʽ
    am_uart_ioctl(uart_handle,AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    while(1) {
    }
}


/* end of file */

