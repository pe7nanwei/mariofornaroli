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

/** \brief ����2ƽ̨��ʼ�� */
static void __kl26_plfm_uart2_init (void)
{
    /* ���ų�ʼ��      PIOD_4_UART2_RX  PIOD_5_UART2_TX     */
     am_gpio_pin_cfg(PIOD_4, PIOD_4_UART2_RX);
     am_gpio_pin_cfg(PIOD_5, PIOD_5_UART2_TX);

     /* ����UART2ʱ��                  */
     amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_UART2);
}

/** \brief �������2 ƽ̨��ʼ�� */
static void __kl26_plfm_uart2_deinit (void)
{
    /* �ر�UART2ʱ��                  */
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_UART2);

    am_gpio_pin_cfg(PIOD_4, PIOD_4_GPIO);
    am_gpio_pin_cfg(PIOD_5, PIOD_5_GPIO);
}

/** \brief ����2 �豸��Ϣ */
static const am_fsl_uart_devinfo_t __g_uart2_devinfo = {

    KL26_UART2,                      /**< \brief ����2             */
    INUM_UART2,                      /**< \brief ����2���жϱ��.     */
    AM_FSL_UART_VER1,                /**< \brief ���������İ汾��.     */
    CLK_UART2,                       /**< \brief ����2��ʱ�Ӻ�.       */
    AMHW_FSL_UART_C1_M_8BIT      |   /**< \brief 8λ����.           */
    AMHW_FSL_UART_C1_PARITY_NO   |   /**< \brief �޼���.            */
    AMHW_FSL_UART_BDH_SBNS_STOP_1,   /**< \brief 1��ֹͣλ .         */

    115200,                          /**< \brief ���õĲ�����.        */

    0,                               /**< \brief �������ж�.          */

    NULL,                            /**< \brief USART2��ʹ��RS485   */
    __kl26_plfm_uart2_init,          /**< \brief USART2��ƽ̨��ʼ��.   */
    __kl26_plfm_uart2_deinit,        /**< \brief USART2��ƽ̨ȥ��ʼ��.  */
};
#define DMA_BUFFER_SIZE     64                        /**< \brief DMA��������С     */
#define DATA_BUFFER_SIZE    64                        /**< \brief ���ڽ��ջ�������С     */

/** \brief   DMA���λ��������壬��Ҫ�����豸��Ϣ����Ĵ�С���ж���  */
static char __dma_buffer_2[DMA_BUFFER_SIZE] __attribute__((aligned(DMA_BUFFER_SIZE)));
static char __rec_buffer_2[DATA_BUFFER_SIZE];

/** \brief   DMA UART�豸��Ϣ���� */
static const  am_kl26_uart_dma_devinfo_t  __g_uart2_dma_devinfo = {
    &__g_uart2_devinfo,
    KL26_DMA,
    DMA_CHAN_2,
    __dma_buffer_2,
    __rec_buffer_2,
    KL26_DMA_BUFFER_64_BYTES,        /**< \briefDMA���λ������Ĵ�С    */
    DMA_BUFFER_SIZE,
    DATA_BUFFER_SIZE
};

static am_kl26_uart_dma_dev_t  __g_uart2_dma_dev;   /**< \brief ���崮��2 �豸.*/

/** \brief DMA UART0ʵ����ʼ�������uart2��׼������ */
am_uart_handle_t am_kl26_uart2_dma_inst_init (void)
{
    return (am_uart_handle_t)am_uart_dma_init(&__g_uart2_dma_dev, &__g_uart2_dma_devinfo);
}

/** \brief DMA UART2ʵ�����ʼ�� */
void am_kl26_uart2_dma_inst_deinit (am_uart_handle_t handle)
{
    am_uart_dma_deinit((am_fsl_uart_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */



