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
 * \brief �̼����ձ�׼�豸ʵ�֣�uart������
 *
 * \internal
 * \par modification history:
 * - 1.00 18-11-30  yrh, first implementation.
 * \endinternal
 */

#ifndef __AM_BOOT_FIRMWARE_RECV_UART_H
#define __AM_BOOT_FIRMWARE_RECV_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_boot_flash.h"
#include "am_boot_firmware.h"
#include "am_boot_firmware_recv.h"
/**
 * \brief �̼����յ��豸�����ڴ���ʵ�֣�
 */
typedef struct am_boot_firwa_recv_uart_dev {
    /**< \brief ��׼�Ĺ̼����շ���  */
    am_boot_firwa_recv_serv_t        isa;
    /**< \brief �̼���ŵı�׼����������  */
    am_boot_firmware_handle_t        firmware_handle;
    /**< \brief ���ڵı�׼����������  */
    am_uart_handle_t                 uart_handle;
} am_boot_firwa_recv_uart_dev_t;

/**
 * \brief �̼������豸��ʼ�������ڴ���ʵ�֣�
 */
am_boot_firwa_recv_handle_t am_boot_firwa_recv_uart_init(
    am_boot_firmware_handle_t firmware_handle, am_uart_handle_t uart_handle);


#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_FIRMWARE_RECV_UART_H */

/* end of file */
