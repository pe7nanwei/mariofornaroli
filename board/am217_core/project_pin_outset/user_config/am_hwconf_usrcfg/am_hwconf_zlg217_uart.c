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
 * \brief ZLG217 UART �û������ļ�
 * \sa am_zlg217l_hwconfig_uart.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-10  ari, first implementation
 * \endinternal
 */

#include "am_gpio.h"
#include "am_zlg_uart.h"
#include "amhw_zlg_uart.h"
#include "am_clk.h"
#include "am_zlg217.h"
#include "amhw_zlg217_gpio.h"
#include "zlg217_periph_map.h"
#include "amhw_zlg217_rcc.h"
#include "zlg217_pin.h"

/**
 * \addtogroup am_if_src_hwconf_zlg217_uart
 * \copydoc am_hwconf_zlg217_uart.c
 * @{
 */

/** \brief ����1ƽ̨��ʼ�� */
static void __zlg217_plfm_uart1_init (void)
{
    am_gpio_pin_cfg(__UART1_TX, __GPIO_UART1_TX);
    am_gpio_pin_cfg(__UART1_RX, __GPIO_UART1_RX);
}

/** \brief �������1ƽ̨��ʼ�� */
static void __zlg217_plfm_uart1_deinit (void)
{
    am_clk_disable(CLK_UART1);

    am_gpio_pin_cfg(__UART1_RX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__UART1_TX, AM_GPIO_INPUT);
}

/** \brief ����1�豸��Ϣ */
static const am_zlg_uart_devinfo_t __g_uart1_devinfo = {

    ZLG217_UART1_BASE,            /**< \brief ����1 */
    INUM_UART1,                   /**< \brief ����1���жϱ�� */
    CLK_UART1,                    /**< \brief ����1��ʱ�� */

    AMHW_ZLG_UART_DATA_8BIT |  /**< \brief 8λ���� */
    AMHW_ZLG_UART_PARITY_NO |  /**< \brief �޼��� */
    AMHW_ZLG_UART_STOP_1BIT,   /**< \brief 1��ֹͣλ */

    115200,                       /**< \brief ���õĲ����� */

    0,                            /**< \brief �������ж� */

    NULL,                         /**< \brief UART1ʹ��RS485 */
    __zlg217_plfm_uart1_init,     /**< \brief UART1��ƽ̨��ʼ�� */
    __zlg217_plfm_uart1_deinit,   /**< \brief UART1��ƽ̨ȥ��ʼ�� */
};

/**< \brief ���崮��1 �豸 */
static am_zlg_uart_dev_t  __g_uart1_dev;

/** \brief ����2ƽ̨��ʼ�� */
static void __zlg217_plfm_uart2_init (void)
{
    am_gpio_pin_cfg(__UART2_TX, __GPIO_UART2_TX);
    am_gpio_pin_cfg(__UART2_RX, __GPIO_UART2_RX);
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __zlg217_plfm_uart2_deinit (void)
{

    /* �ر�UART2ʱ�� */
    am_clk_disable(CLK_UART2);

    am_gpio_pin_cfg(__UART2_TX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__UART2_RX, AM_GPIO_INPUT);
}

/** \brief ����2 �豸��Ϣ */
static const am_zlg_uart_devinfo_t __g_uart2_devinfo = {

    ZLG217_UART2_BASE,              /**< \brief ����2 */
    INUM_UART2,                     /**< \brief ����2���жϱ�� */
    CLK_UART2,                      /**< \brief ����2��ʱ�� */

    AMHW_ZLG_UART_DATA_8BIT |    /**< \brief 8λ���� */
    AMHW_ZLG_UART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_ZLG_UART_STOP_1BIT,     /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief UART2ʹ��RS485 */
    __zlg217_plfm_uart2_init,       /**< \brief UART2��ƽ̨��ʼ�� */
    __zlg217_plfm_uart2_deinit,     /**< \brief UART2��ƽ̨ȥ��ʼ�� */
};

/**< \brief ���崮��2�豸 */
static am_zlg_uart_dev_t  __g_uart2_dev;

/** \brief ����3ƽ̨��ʼ�� */
static void __zlg217_plfm_uart3_init (void)
{
    am_gpio_pin_cfg(__UART3_TX, __GPIO_UART3_TX);
    am_gpio_pin_cfg(__UART3_RX, __GPIO_UART3_RX);
}

/** \brief �������3 ƽ̨��ʼ�� */
static void __zlg217_plfm_uart3_deinit (void)
{
    am_clk_disable(CLK_UART3);

    am_gpio_pin_cfg(__UART3_TX, AM_GPIO_INPUT);
    am_gpio_pin_cfg(__UART3_RX, AM_GPIO_INPUT);
}

/** \brief ����3 �豸��Ϣ */
static const am_zlg_uart_devinfo_t __g_uart3_devinfo = {

    ZLG217_UART3_BASE,              /**< \brief ����3 */
    INUM_UART3,                     /**< \brief ����2���жϱ�� */
    CLK_UART3,                      /**< \brief ����2��ʱ�� */

    AMHW_ZLG_UART_DATA_8BIT |    /**< \brief 8λ���� */
    AMHW_ZLG_UART_PARITY_NO |    /**< \brief �޼��� */
    AMHW_ZLG_UART_STOP_1BIT,     /**< \brief 1��ֹͣλ */

    115200,                         /**< \brief ���õĲ����� */

    0,                              /**< \brief �������ж� */

    NULL,                           /**< \brief UART3ʹ��RS485 */
    __zlg217_plfm_uart3_init,       /**< \brief UART3��ƽ̨��ʼ�� */
    __zlg217_plfm_uart3_deinit,     /**< \brief UART3��ƽ̨ȥ��ʼ�� */
};

/**< \brief ���崮��2�豸 */
static am_zlg_uart_dev_t  __g_uart3_dev;

/** \brief UART1ʵ����ʼ�������uart1��׼������ */
am_uart_handle_t am_zlg217_uart1_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart1_dev, &__g_uart1_devinfo);
}

/** \brief UART1ʵ�����ʼ�� */
void am_zlg217_uart1_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/** \brief UART2ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_zlg217_uart2_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart2_dev, &__g_uart2_devinfo);
}

/** \brief UART2ʵ�����ʼ�� */
void am_zlg217_uart2_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/** \brief UART3ʵ����ʼ�������uart3��׼������ */
am_uart_handle_t am_zlg217_uart3_inst_init (void)
{
    return am_zlg_uart_init(&__g_uart3_dev, &__g_uart3_devinfo);
}

/** \brief UART3ʵ�����ʼ�� */
void am_zlg217_uart3_inst_deinit (am_uart_handle_t handle)
{
    am_zlg_uart_deinit((am_zlg_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
