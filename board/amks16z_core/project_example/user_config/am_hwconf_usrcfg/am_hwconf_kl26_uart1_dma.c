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
 * \brief kl26 UART0 �û������ļ�
 * \sa am_kl26_hwconfig_uart0.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-14  htf, first implementation.
 * \endinternal
 */

#include "am_gpio.h"
#include "am_fsl_uart.h"
#include "hw/amhw_fsl_uart.h"
#include "hw/amhw_kl26_sim.h"
#include "kl26_dmamux_chan.h"
#include "am_kl26_uart_dma.h"
#include "am_kl26_inst_init.h"

#include "../../../../../soc/freescale/kl26/kl26_clk.h"
#include "../../../../../soc/freescale/kl26/kl26_inum.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"

/**
 * \addtogroup am_kl26_if_hwconfig_src_uart0
 * \copydoc am_kl26_hwconfig_uart0.c
 * @{
 */

/** \brief ����0ƽ̨��ʼ�� */
/** \brief ����1ƽ̨��ʼ�� */
static void __kl26_plfm_uart1_init (void)
{
    /* ���ų�ʼ��      PIOC_3_UART1_RX  PIOC_4_UART1_TX   */
    am_gpio_pin_cfg(PIOC_3, PIOC_3_UART1_RX);
    am_gpio_pin_cfg(PIOC_4, PIOC_4_UART1_TX);

    /* ����UART1ʱ��                  */
    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART1);
}

/** \brief �������1ƽ̨��ʼ�� */
static void __kl26_plfm_uart1_deinit (void)
{
     /* �ر�UART1ʱ��                  */
     amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_UART1);

     am_gpio_pin_cfg(PIOC_3, PIOC_3_GPIO);
     am_gpio_pin_cfg(PIOC_4, PIOC_4_GPIO);
}

/** \brief ����1�豸��Ϣ */
static const am_fsl_uart_devinfo_t __g_uart1_devinfo = {

    KL26_UART1,                      /**< \brief ����1            */
    INUM_UART1,                      /**< \brief ����1���жϱ��.    */
    AM_FSL_UART_VER1,                /**< \brief ���������İ汾��.     */
    CLK_UART1,                       /**< \brief ����1��ʱ�Ӻ�.     */
    AMHW_FSL_UART_C1_M_8BIT      |  /**< \brief 8λ����.          */
    AMHW_FSL_UART_C1_PARITY_NO   |  /**< \brief �޼���.           */
    AMHW_FSL_UART_BDH_SBNS_STOP_1,  /**< \brief 1��ֹͣλ.         */

    115200,                          /**< \brief ���õĲ�����.       */

    0,                               /**< \brief �������ж�.         */

    NULL,                            /**< \brief USART1��ʹ��RS485  */
    __kl26_plfm_uart1_init,          /**< \brief USART1��ƽ̨��ʼ��.  */
    __kl26_plfm_uart1_deinit,        /**< \brief USART1��ƽ̨ȥ��ʼ��. */
};
#define DMA_BUFFER_SIZE     64                        /**< \brief DMA��������С     */
#define DATA_BUFFER_SIZE    64                        /**< \brief ���ڽ��ջ�������С     */

/** \brief   DMA���λ��������壬��Ҫ�����豸��Ϣ����Ĵ�С���ж���  */
static char __dma_buffer_1[DMA_BUFFER_SIZE] __attribute__((aligned(DMA_BUFFER_SIZE)));
static char __rec_buffer_1[DATA_BUFFER_SIZE];

/** \brief   DMA UART�豸��Ϣ���� */
static const  am_kl26_uart_dma_devinfo_t  __g_uart1_dma_devinfo = {
    &__g_uart1_devinfo,
    KL26_DMA,
    DMA_CHAN_1,
    __dma_buffer_1,
    __rec_buffer_1,
    KL26_DMA_BUFFER_64_BYTES,        /**< \briefDMA���λ������Ĵ�С    */
    DMA_BUFFER_SIZE,
    DATA_BUFFER_SIZE
};

static am_kl26_uart_dma_dev_t  __g_uart1_dma_dev;   /**< \brief ���崮��0 �豸.*/

/** \brief UART0ʵ����ʼ�������uart0��׼������ */
am_uart_handle_t am_kl26_uart1_dma_inst_init (void)
{
    return (am_uart_handle_t)am_uart_dma_init(&__g_uart1_dma_dev, &__g_uart1_dma_devinfo);
}

/** \brief UART0ʵ�����ʼ�� */
void am_kl26_uart1_dma_inst_deinit (am_uart_handle_t handle)
{
    am_uart_dma_deinit((am_fsl_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */



