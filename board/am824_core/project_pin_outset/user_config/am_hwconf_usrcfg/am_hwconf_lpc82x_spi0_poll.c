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
 * \brief LPC82X SPI (��ѯ��ʽ) �û������ļ�
 * \sa am_hwconf_lpc82x_spi0_poll.c
 *
 * \pollernal
 * \par Modification history
 * - 1.02 19-01-21  htf, first implementation
 * \endpollernal
 */

#include "ametal.h"
#include "am_lpc82x.h"
#include "am_lpc_spi_poll.h"
#include "am_lpc82x_spi_dma.h"
#include "hw/amhw_lpc82x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_spi0_poll
 * \copydoc am_hwconf_lpc82x_spi0_poll.c
 * @{
 */

/**
 * \brief SPI0 ƽ̨��ʼ��
 */
am_local void __lpc82x_spi0_poll_plfm_init (void)
{
    am_gpio_pin_cfg(PIO0_15, PIO_FUNC_SPI0_SCK);
    am_gpio_pin_cfg(PIO0_12, PIO_FUNC_SPI0_MOSI);
    am_gpio_pin_cfg(PIO0_13, PIO_FUNC_SPI0_MISO);

    /* CS_Pin ���û����� STD ����ʱ���д��룬�˴��������� */

    amhw_lpc82x_clk_periph_enable(AMHW_LPC82X_CLK_SPI0);
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI0);
}

/**
 * \brief SPI0 ƽ̨���ʼ��
 */
am_local void __lpc82x_spi0_poll_plfm_deinit (void)
{
    amhw_lpc82x_syscon_periph_reset(AMHW_LPC82X_RESET_SPI0);
    amhw_lpc82x_clk_periph_disable(AMHW_LPC82X_CLK_SPI0);

    am_gpio_pin_cfg(PIO0_15, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_12, AM_GPIO_PULLUP | AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_13, AM_GPIO_PULLUP | AM_GPIO_INPUT);
}

/** \brief SPI0 (��ѯ��ʽ) �豸��Ϣ */
am_local am_const struct am_lpc_spi_poll_devinfo __g_lpc82x_spi0_poll_devinfo = {
    LPC82X_SPI0_BASE,                /* SPI0 �Ĵ��������ַ */
    INUM_SPI0,                       /* SPI0 �жϺ� */
    CLK_SPI0,                        /* SPI0 ʱ�Ӻ� */
    __lpc82x_spi0_poll_plfm_init,     /* ƽ̨��ʼ������ */
    __lpc82x_spi0_poll_plfm_deinit    /* ƽ̨���ʼ������ */
};

/** \brief SPI0 (�жϷ�ʽ) �豸ʵ�� */
am_local am_lpc_spi_poll_dev_t __g_lpc82x_spi0_poll_dev;

/**
 * \brief SP0I (��ѯ��ʽ) ʵ����ʼ��
 */
am_spi_handle_t am_lpc82x_spi0_poll_inst_init (void)
{
    return am_lpc_spi_poll_init(&__g_lpc82x_spi0_poll_dev,
                               &__g_lpc82x_spi0_poll_devinfo);
}

/**
 * \brief SPI0 (��ѯ��ʽ) ʵ�����ʼ��
 */
void am_lpc82x_spi0_poll_inst_deinit (am_spi_handle_t handle)
{
    am_lpc_spi_poll_deinit(handle);
}

/**
 * @}
 */

/* end of file */
