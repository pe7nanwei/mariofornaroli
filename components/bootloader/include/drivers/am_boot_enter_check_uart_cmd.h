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
 * \brief ����Ӧ�ó����⣨����ָ������ʵ�֣�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-5-23  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_ENTER_CHECK_UART_H
#define __AM_BOOT_ENTER_CHECK_UART_H

#include "am_common.h"
#include "am_uart.h"
#include "am_boot_enter_check.h"

/**
 * \brief ����Ӧ�ô������豸����������������
 */
typedef struct am_boot_enter_check_uart_cmd_dev {
    /**< \brief ��׼�Ľ���Ӧ�ó��������  */
    am_boot_enter_check_serv_t enter_check_serv;
    /**< \brief ���ڱ�׼����������  */
    am_uart_handle_t           uart_handle;
}am_boot_enter_check_uart_cmd_dev_t;

/**
 * \brief ����Ӧ�ô������豸��ʼ������������������
 */
am_boot_enter_check_handle_t am_boot_enter_check_uart_cmd_init(am_uart_handle_t uart_handle);

#endif /* __AM_BOOT_ENTER_CHECK_UART_H */
