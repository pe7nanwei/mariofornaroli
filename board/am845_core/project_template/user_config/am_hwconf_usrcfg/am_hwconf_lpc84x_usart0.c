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
 * \brief LPC84X USART0 �û������ļ�
 * \sa am_hwconf_lpc84x_usart0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc_usart.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_usart0
 * \copydoc am_hwconf_lpc84x_usart0.c
 * @{
 */

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note USART0/1/2/3/4 SPI0/1 I2C0/1/2/3 ���ܹ���һ����������Ƶ�ʣ���Ҫ����Ķ�
 */
#ifndef  __LPC84X_FRG0_BASE_RATE
#define  __LPC84X_FRG0_BASE_RATE  11059200
#endif

/**
 * \brief USART0 ƽ̨��ʼ��
 */
am_local void __lpc84x_usart0_plfm_init (void)
{

	amhw_lpc84x_clk_uart0_clk_sel_set(AMHW_LPC84X_CLK_DEVICE_FRG0CLK);

    /* ���ô��ڻ���ʱ�� */
    amhw_lpc84x_clk_frg0_baseclkrate_set(__LPC84X_FRG0_BASE_RATE);

    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_UART0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_UART0);
    am_gpio_pin_cfg(PIO0_14, PIO_FUNC_U0_TXD);
    am_gpio_pin_cfg(PIO0_23, PIO_FUNC_U0_RXD);

}

/**
 * \brief USART0 ƽ̨���ʼ��
 */
am_local void __lpc84x_usart0_plfm_deinit (void)
{
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_UART0);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_UART0);

    am_gpio_pin_cfg(PIO0_19, PIO0_19_GPIO);
    am_gpio_pin_cfg(PIO0_18, PIO0_18_GPIO);
}

/** \brief USART0 �豸��Ϣ */
am_local am_const am_lpc_usart_devinfo_t __g_lpc84x_usart0_devinfo = {
    LPC84X_USART0_BASE,             /* USART0 �Ĵ��������ַ */
    INUM_USART0,                    /* USART0 �жϺ� */
    CLK_UART0,                      /* USART0 ʱ�Ӻ� */
    __lpc84x_usart0_plfm_init,      /* ƽ̨��ʼ������ */
    __lpc84x_usart0_plfm_deinit,    /* ƽ̨���ʼ������ */
    NULL                            /* �� RS485 ������ƺ��� */
};

/** \brief USART0 �豸ʵ�� */
am_local am_lpc_usart_dev_t __g_lpc84x_usart0_dev;

/**
 * \brief USART0 ʵ����ʼ��
 */
am_uart_handle_t am_lpc84x_usart0_inst_init (void)
{
    return am_lpc_usart_init(&__g_lpc84x_usart0_dev,
                             &__g_lpc84x_usart0_devinfo);
}

/**
 * \brief USART0 ʵ�����ʼ��
 */
void am_lpc84x_usart0_inst_deinit (am_uart_handle_t handle)
{
    am_lpc_usart_deinit(handle);
}

/**
 * @}
 */

/* end of file */
