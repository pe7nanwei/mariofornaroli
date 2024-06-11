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
 * \brief UART ���λ�������ʽ�½��շ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������� "UART interrupt mode(Add ring buffer) test:"��
 *   2. ����������յ����ַ�����
 *
 * \note�� ������Դ���ʹ���뱾������ͬ����Ӧ�ں�������ʹ�õ�����Ϣ�������
 *       ���磺AM_DBG_INFO()��
 *
 * \par Դ����
 * \snippet demo_std_uart_ringbuf.c src_std_uart_ringbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 17-05-4  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_uart_ringbuf
 * \copydoc demo_std_uart_ringbuf.c
 */

/** [src_std_uart_ringbuf] */
#include "ametal.h"
#include "am_uart.h"
#include "am_uart_rngbuf.h"

/*******************************************************************************
  �궨��
*******************************************************************************/
#define UART_RX_BUF_SIZE  128  /**< \brief ���ջ��λ�������С��Ӧ��Ϊ2^n  */
#define UART_TX_BUF_SIZE  128  /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ2^n  */

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/** \brief UART ���ջ��λ�����  */
static uint8_t __uart_rxbuf[UART_RX_BUF_SIZE];

/** \brief UART ���ͻ��λ�����  */
static uint8_t __uart_txbuf[UART_TX_BUF_SIZE];

/** \brief ��ʼ����ʾ�ַ�  */
static const uint8_t __ch[] = {"UART interrupt mode(Add ring buffer) test:\r\n"};

/** \brief ���ڻ������豸 */
static am_uart_rngbuf_dev_t __g_uart_ringbuf_dev;

/**
 * \brief �������
 */
void demo_std_uart_ringbuf_entry (am_uart_handle_t uart_handle)
{
    uint8_t                 uart1_buf[5];   /* ���ݻ����� */
    am_uart_rngbuf_handle_t handle = NULL;  /* ���ڻ��λ����������� */

    /* UART ��ʼ��Ϊ���λ�����ģʽ */
    handle = am_uart_rngbuf_init(&__g_uart_ringbuf_dev,
                                  uart_handle,
                                  __uart_rxbuf,
                                  UART_RX_BUF_SIZE,
                                  __uart_txbuf,
                                  UART_TX_BUF_SIZE);

    am_uart_rngbuf_send(handle, __ch, sizeof(__ch));

    while (1) {

        /* �ӽ��ջ�����ȡ��һ�����ݵ� buf���������� */
        am_uart_rngbuf_receive(handle, uart1_buf, 1);

        /* �� buf ��һ�����ݷ��뻷�λ��������������� */
        am_uart_rngbuf_send(handle, uart1_buf, 1);
    }
}
/** [src_std_uart_ringbuf] */

/* end of file */
