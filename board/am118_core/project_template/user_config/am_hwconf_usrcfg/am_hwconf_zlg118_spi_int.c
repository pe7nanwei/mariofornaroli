/*******************************************************************************

                                AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG118 SPI INT 用户配置文件
 * \sa am_hwconf_zlg118_spi.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-09-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg118_spi_int.h"
#include "am_gpio.h"
#include "hw/amhw_zlg118_spi.h"
#include "am_clk.h"
#include "am_zlg118.h"
#include "zlg118_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg118_spi_int
 * \copydoc am_hwconf_zlg118_spi_int.c
 * @{
 */
/** \brief SPI0 平台初始化 */
static void __zlg118_plfm_spi0_int_init (void)
{
    am_gpio_pin_cfg(PIOB_3,  PIOB_3_SPI0_SCK   | PIOB_3_OUT_PP);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_SPI0_MOSI | PIOA_12_OUT_PP);
    am_gpio_pin_cfg(PIOA_11, PIOA_11_SPI0_MISO | PIOA_11_INPUT_PU);

    am_clk_enable(CLK_SPI0);
}

/** \brief 解除SPI0 平台初始化 */
static void __zlg118_plfm_spi0_int_deinit (void)
{
    /* 释放引脚为输入模式 */
    am_gpio_pin_cfg(PIOB_3,  PIOB_3_INPUT_PU);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_INPUT_PU);
    am_gpio_pin_cfg(PIOA_11, PIOA_11_INPUT_PU);

    am_clk_disable(CLK_SPI0);
}

/** \brief SPI0 设备信息 */
const  struct am_zlg118_spi_int_devinfo  __g_spi0_int_devinfo = {
    ZLG118_SPI0_BASE,                        /**< \brief SPI0寄存器指针 */
    CLK_SPI0,                                /**< \brief 时钟ID号 */
    INUM_SPI0,                               /**< \brief SPI0中断号 */
    PIOA_12_SPI0_MOSI | PIOA_12_OUT_PP,     /**< \brief SPI0配置标识 */
    PIOA_12,                                /**< \brief MOSI引脚号 */
    __zlg118_plfm_spi0_int_init,             /**< \brief SPI0平台初始化函数 */
    __zlg118_plfm_spi0_int_deinit            /**< \brief SPI0平台解初始化函数 */
};

/** \brief SPI0 设备实例 */
static am_zlg118_spi_int_dev_t __g_spi0_int_dev;

/** \brief SPI0 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg118_spi0_int_inst_init (void)
{
    return am_zlg118_spi_int_init(&__g_spi0_int_dev, &__g_spi0_int_devinfo);
}

/** \brief SPI0 实例解初始化 */
void am_zlg118_spi0_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg118_spi_int_deinit(handle);
}

/** \brief SPI1 平台初始化 */
static void __zlg118_plfm_spi1_int_init (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_SPI1_SCK  | PIOB_10_OUT_PP);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_SPI1_MISO  | PIOC_2_INPUT_PU);

    am_clk_enable(CLK_SPI1);
}

/** \brief 解除SPI1 平台初始化 */
static void __zlg118_plfm_spi1_int_deinit (void)
{
    am_gpio_pin_cfg(PIOB_10, PIOB_10_INPUT_PU);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_INPUT_PU);
    am_gpio_pin_cfg(PIOC_2,  PIOC_2_INPUT_PU);

    am_clk_disable(CLK_SPI1);
}

/** \brief SPI1 设备信息 */
const  struct am_zlg118_spi_int_devinfo  __g_spi1_int_devinfo = {
    ZLG118_SPI1_BASE,                        /**< \brief SPI1寄存器指针 */
    CLK_SPI1,                                /**< \brief 时钟ID号 */
    INUM_SPI1,                               /**< \brief SPI1中断号 */
    PIOB_15_SPI1_MOSI | PIOB_15_OUT_PP,      /**< \brief SPI1配置标识 */
    PIOB_15,                                 /**< \brief MOSI引脚号 */
    __zlg118_plfm_spi1_int_init,             /**< \brief SPI1平台初始化函数 */
    __zlg118_plfm_spi1_int_deinit            /**< \brief SPI1平台解初始化函数 */
};

/** \brief SPI1 设备实例 */
static am_zlg118_spi_int_dev_t __g_spi1_int_dev;

/** \brief SPI1 实例初始化，获得SPI标准服务句柄 */
am_spi_handle_t am_zlg118_spi1_int_inst_init (void)
{
    return am_zlg118_spi_int_init(&__g_spi1_int_dev, &__g_spi1_int_devinfo);
}

/** \brief SPI1 实例解初始化 */
void am_zlg118_spi1_int_inst_deinit (am_spi_handle_t handle)
{
    am_zlg118_spi_int_deinit(handle);
}

/**
 * @}
 */

/* end of file */
