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
 * \brief RS485 ���̣�ʹ��UART��׼�ӿڣ�
 *
 * - ʵ������
 *   1. �������"RS485 Test:"��
 *   2. ����������յ����ַ�����
 *
 *   RS485Ϊ��˫��ͨ�ţ���˴�˫�����붨��ú��ʵķ���ʵ�ʣ������ͻ��������
 *   ��Ϊһ�ּ򵥵ķ��������Ϊ�յ�һ���ַ��ͻط�һ���ַ�����ˣ����Ͷ�ֻ�ܵ�
 *   �������ַ��ķ��ͣ�������һ���ַ�����յ��ش����ַ��ٴ�����һ���ַ���
 *
 * \par Դ����
 * \snippet demo_std_uart_rs485.c src_std_uart_rs485
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_uart_rs485
 * \copydoc demo_std_uart_rs485.c
 */

/** [src_std_uart_rs485] */
#include "ametal.h"
#include "am_uart.h"

/**
 * \brief �������
 */
void demo_std_uart_rs485_entry (am_uart_handle_t uart_handle)
{
    uint8_t  rcv_tmp;           /* ���������ݴ��� */
    int      rcv_cnt;

    /**
     * ʹ�� 485 ģʽ�����Զ����Ʒ�������
     */
    am_uart_ioctl(uart_handle, AM_UART_RS485_SET, (void *)AM_TRUE);
    am_uart_ioctl(uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_POLL);

    am_uart_poll_send(uart_handle, (const uint8_t *)"\r\n RS485 Test:\r\n",
                                   sizeof("\r\n RS485 Test:\r\n") - 1);
    while (1) {

        /* �����ַ� */
        rcv_cnt = am_uart_poll_receive(uart_handle, &rcv_tmp, 1);
        if (rcv_cnt) {
            am_uart_poll_send(uart_handle, &rcv_tmp, 1);
        }
    }
}
/** [src_std_uart_rs485] */

/* end of file */
