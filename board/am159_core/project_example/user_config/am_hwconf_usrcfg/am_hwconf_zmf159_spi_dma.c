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
 * \brief ZMF159 SPI �û������ļ�
 * \sa am_hwconf_zlg116_spi_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 15-10-23  ari, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_zlg_spi_dma.h"
#include "am_gpio.h"
#include "hw/amhw_zlg_spi.h"
#include "am_clk.h"
#include "zmf159_dma_chan.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_spi_dma
 * \copydoc am_hwconf_zmf159_spi_dma.c
 * @{
 */

/** \brief SPI1 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi1_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_3, PIOB_3_SPI1_SCK | PIOB_3_AF_PP);
    am_gpio_pin_cfg(PIOB_4, PIOB_4_SPI1_MISO | PIOB_4_INPUT_PU);
    am_gpio_pin_cfg(PIOB_5, PIOB_5_SPI1_MOSI | PIOB_5_AF_PP);
//    am_gpio_pin_cfg(PIOA_15, PIOA_15_SPI1_NSS | PIOA_15_AF_PP);

    am_clk_enable(CLK_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi1_dma_deinit (void)
{

    /* �ͷ�����Ϊ����ģʽ */
    am_gpio_pin_cfg(PIOB_3, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_4, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_5, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct am_zlg_spi_dma_devinfo  __g_spi1_dma_devinfo = {
    ZMF159_SPI1_BASE,               /**< \brief SPI1�Ĵ���ָ�� */
    CLK_SPI1,                       /**< \brief ʱ��ID�� */
    INUM_SPI1,                      /**< \brief SPI1�жϺ� */
    0,                              /**< \brief SPI1���ñ�ʶ */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    __zmf159_plfm_spi1_dma_init,    /**< \brief SPI1ƽ̨��ʼ������ */
    __zmf159_plfm_spi1_dma_deinit   /**< \brief SPI1ƽ̨���ʼ������ */
};

/** \brief SPI1 �豸ʵ�� */
static am_zlg_spi_dma_dev_t __g_spi1_dma_dev;

/** \brief SPI1 ʵ����ʼ�������SPI��׼������ */
am_spi_handle_t am_zmf159_spi1_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi1_dma_dev, &__g_spi1_dma_devinfo);
}

/** \brief SPI1 ʵ�����ʼ�� */
void am_zmf159_spi1_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI2 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi2_dma_init (void)
{
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK | PIOB_13_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_AF_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI  | PIOB_15_AF_PP);

    am_clk_enable(CLK_SPI2);
}

/** \brief ��� SPI2 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi2_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOB_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_14, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOB_15, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI2 �豸��Ϣ
 */
static const struct am_zlg_spi_dma_devinfo  __g_spi2_dma_devinfo = {
    ZMF159_SPI2_BASE,                /**< \brief SPI2 �Ĵ���ָ�� */
    CLK_SPI2,                        /**< \brief ʱ�� ID �� */
    INUM_SPI2,                       /**< \brief SPI2�жϺ� */
    0,                               /**< \brief SPI2 ���ñ�ʶ */

    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    __zmf159_plfm_spi2_dma_init,     /**< \brief SPI2 ƽ̨��ʼ������ */
    __zmf159_plfm_spi2_dma_deinit    /**< \brief SPI2 ƽ̨���ʼ������ */
};

/** \brief SPI2 �豸ʵ�� */
static am_zlg_spi_dma_dev_t __g_spi2_dma_dev;

/** \brief SPI2 ʵ����ʼ������� SPI ��׼������ */
am_spi_handle_t am_zmf159_spi2_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi2_dma_dev, &__g_spi2_dma_devinfo);
}

/** \brief SPI2 ʵ�����ʼ�� */
void am_zlg_spi2_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI3 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi3_dma_init (void)
{
    am_gpio_pin_cfg(PIOD_4, PIOD_4_SPI3_SCK  | PIOD_4_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOD_5, PIOD_5_SPI3_MISO | PIOD_5_AF_PP);
    am_gpio_pin_cfg(PIOD_6, PIOD_6_SPI3_MOSI | PIOD_6_AF_PP);

    am_clk_enable(CLK_SPI3);
}

/** \brief ��� SPI3 ƽ̨��ʼ�� */
static void __zmf159_plfm_spi3_dma_deinit (void)
{
    am_gpio_pin_cfg(PIOD_4, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_5, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOD_6, AM_GPIO_INPUT);

    am_clk_disable(CLK_SPI3);
}

/**
 * \brief SPI3 �豸��Ϣ
 */
static const struct am_zlg_spi_dma_devinfo  __g_spi3_dma_devinfo = {
    ZMF159_SPI3_BASE,                /**< \brief SPI3 �Ĵ���ָ�� */
    CLK_SPI3,                        /**< \brief ʱ�� ID �� */
    INUM_SPI3,                       /**< \brief SPI3�жϺ� */
    0,                               /**< \brief SPI3 ���ñ�ʶ */

    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    __zmf159_plfm_spi3_dma_init,     /**< \brief SPI3 ƽ̨��ʼ������ */
    __zmf159_plfm_spi3_dma_deinit    /**< \brief SPI3 ƽ̨���ʼ������ */
};

/** \brief SPI3 �豸ʵ�� */
static am_zlg_spi_dma_dev_t __g_spi3_dma_dev;

/** \brief SPI3 ʵ����ʼ������� SPI ��׼������ */
am_spi_handle_t am_zmf159_spi3_dma_inst_init (void)
{
    return am_zlg_spi_dma_init(&__g_spi3_dma_dev, &__g_spi3_dma_devinfo);
}

/** \brief SPI2 ʵ�����ʼ�� */
void am_zlg_spi3_dma_inst_deinit (am_spi_handle_t handle)
{
    am_zlg_spi_dma_deinit(handle);
}


/**
 * @}
 */

/* end of file */
