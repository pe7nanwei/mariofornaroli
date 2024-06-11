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
 * \brief Micro LIB
 *
 * ��ʹ��ǰ��������"Project->Options for Target xxx->Target"�й�ѡ"Use MicroLIB"
 * ���ڴ����ӿ�ֻ����Micro LIB��ametalϵͳ�ӿ�֮��ѡ��һ��ʹ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-17  pea, first implementation.
 * \endinternal
 */

#ifndef __AM_BSP_MICROLIB_H
#define __AM_BSP_MICROLIB_H

#include "am_uart.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Micro LIB��ʼ��
 *
 * \param[in] uart_handle UART����
 *
 * \return AM_OK
 */
int am_bsp_microlib_init (am_uart_handle_t uart_handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_BSP_MICROLIB_H */

/* end of file */
