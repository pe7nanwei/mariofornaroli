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
 * \brief ZSN60x�����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-04-22  htf, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_i2c.h"
#include "zsn60x.h"
#include "zlg116_pin.h"
#include "am_zsn60x.h"
#include "am_uart_rngbuf.h"
#include "zsn60x_platform.h"
#include "am_zlg116_inst_init.h"
#include "am_hwconf_zsn60x_i2c.h"

/**< \brief ZSN60x(UARTģʽ) �豸ʵ�� */
static   zsn60x_uart_dev_t          __g_zsn60x_uart_dev;

/**< \brief ZSN60x(UARTģʽ) �豸��Ϣ */
static const zsn60x_uart_devinfo_t  __g_uart_info = {
     0xb2,
    {
        -1,
        PIOA_12,
        am_zlg116_uart2_inst_init,
        am_zlg116_uart2_inst_deinit,
        9600,
    }
};
/** \brief ZSN60x ʵ����ʼ�������ZSN60x��׼������(UARTģʽ) */
zsn60x_handle_t  am_zsn60x_uart_inst_init (void)
{
    return zsn60x_uart_init(&__g_zsn60x_uart_dev, &__g_uart_info);
}
