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
 * \brief MiniPort-ZLG72128 �û������ļ�
 * \sa am_hwconf_miniport_zlg72128.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "lpc82x_pin.h"
#include "am_zlg600.h"

static uint8_t g_zlg600_uart_txbuf[128];
static uint8_t g_zlg600_uart_rxbuf[128];

static const am_zlg600_uart_dev_info_t __g_zlg600_uart_devinfo = {
  	g_zlg600_uart_rxbuf,       				// ���ڴ��ڽ��յĻ�����
 	  g_zlg600_uart_txbuf,       				// ���ڴ��ڷ��͵Ļ�����
  	128,                       				// �������ݻ������Ĵ�С
  	128,                        			// �������ݻ������Ĵ�С
  	AM_ZLG600_BAUDRATE_115200,  			// ��ZLG600Aͨ�ŵĲ���������Ϊ115200
 	  AM_ZLG600_MODE_AUTO_CHECK, 		    // ����ģʽʹ�õ��Զ����ģʽ
  	0x59,  								            // Ĭ�ϵ�ַ
};

static am_zlg600_uart_dev_t  __g_zlg600_uart_dev;

am_zlg600_handle_t am_zlg600_uart_inst_init(void)
{
    am_uart_handle_t uart_handle = am_lpc82x_usart1_inst_init();
    return am_zlg600_uart_old_init(&__g_zlg600_uart_dev, uart_handle, &__g_zlg600_uart_devinfo);
}
/* end of file */
