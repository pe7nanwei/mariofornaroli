/*******************************************************************************
*                                 AMetal
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief KL16 SPI0 �û������ļ�
 * \sa am_hwconf_kl26_spi0_poll.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-23  sdy, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_kl26.h"
#include "am_kl26_spi_poll.h"
#include "am_gpio.h"
#include "hw/amhw_fsl_spi.h"
#include "hw/amhw_kl26_sim.h"

/**
 * \addtogroup am_if_src_hwconf_kl26_spi0_poll
 * \copydoc am_hwconf_kl26_spi0_poll.c
 * @{
 */

/** \brief SPI0 ƽ̨��ʼ�� */
static void __kl26_plfm_spi0_poll_init (void)
{
    am_gpio_pin_cfg(PIOE_17, PIOE_17_SPI0_SCK  | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOE_18, PIOE_18_SPI0_MOSI | AM_GPIO_PULLUP);
    am_gpio_pin_cfg(PIOE_19, PIOE_19_SPI0_MISO | AM_GPIO_PULLUP);

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_SPI0);
}

/** \brief ���SPI0 ƽ̨��ʼ�� */
static void __kl26_plfm_spi0_poll_deinit (void)
{
    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOE_17, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOE_18, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOE_19, AM_GPIO_INPUT);

    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_SPI0);
}

/**
 * \brief SPI0 �豸��Ϣ
 */
const  struct am_kl26_spi_poll_devinfo  __g_spi0_poll_devinfo = {
    KL26_SPI0_BASE,                    /**< \brief SPI0�Ĵ���ָ��   */
    AM_KL26_SPI_POLL_CFG_WIAT_EN,      /**< \brief SPI ���ñ�ʶ    */
    __kl26_plfm_spi0_poll_init,        /**< \brief SPI0ƽ̨��ʼ������ */
    __kl26_plfm_spi0_poll_deinit       /**< \brief SPI0ƽ̨���ʼ������ */
};

/** \brief SPI0 �豸ʵ�� */
static am_kl26_spi_poll_dev_t __g_spi0_poll_dev;

/** \brief SPI0 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_kl26_spi0_poll_inst_init (void)
{
    return am_kl26_spi_poll_init(&__g_spi0_poll_dev, &__g_spi0_poll_devinfo);
}

/** \brief SPI0 ʵ�����ʼ�� */
void am_kl26_spi0_poll_inst_deinit (am_spi_handle_t handle)
{
    am_kl26_spi_poll_deinit(handle);
}

/**
 * @}
 */

/* end of file */
