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
 * \brief USART �����������̣�DMA ��ʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ "DMA tx transfer start:"��
 *   2. ������� "aAbBcCdD...",�� 256 ���ֽڣ�
 *   3. DMA ������ɺ󴮿ڴ�ӡ "DMA transfer done!"��
 *
 * \note
 *    1. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_18 �������� PC ���ڵ� TXD��
 *       PIO0_19 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_usart_tx_dma.c src_am845_core_hw_usart_tx_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-15  bob, first implementation
 * \endinternal
 */

 /**
 * \addtogroup demo_if_am845_core_hw_usart_tx_dma
 * \copydoc demo_am845_core_hw_usart_tx_dma.c
 */

/** [src_am845_core_hw_usart_tx_dma] */
#include "ametal.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc84x_clk.h"
#include "am_vdebug.h"
#include "demo_nxp_entries.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \brief ��������Ƶ�����ã���������Ƶ�ʱ���С��ϵͳʱ��Ƶ����ӦΪ�����ʵ���������
 *
 * Ϊ�����ò�����Ϊ 115200�������ô��ڻ�������Ƶ��Ϊ��
 * 11059200Hz(11059200 = 115200 * 96)��
 * ���ڻ�������Ƶ������Ϊ 11.059200MHz�����������������ʵ����� (9600,4800,115200)
 *
 * \note  USART0\1\2 ����һ����������Ƶ��,��Ҫ���׸Ķ�
 */
#define  __LPC84X_UASART_BASE_RATE  11059200

/** \brief ������ */
#define __USART_BAUDRATE      115200

/**
 * \brief �������
 */
void demo_am845_core_hw_usart_tx_dma_entry (void)
{
    am_kprintf("demo am845 hw usart tx dma!\r\n");
  
	amhw_lpc84x_clk_uart0_clk_sel_set(AMHW_LPC84X_CLK_DEVICE_FRG0CLK);

    /* ʹ�ܴ��� 0 ʱ�Ӳ���λ */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_UART0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_UART0);

    /* �������Ÿ��� */
    am_gpio_pin_cfg(PIO1_0, PIO_FUNC_U0_TXD);
    am_gpio_pin_cfg(PIO1_2, PIO_FUNC_U0_RXD);
    /* USART ��ʼ�� */
    demo_lpc845_hw_usart_tx_dma_entry(LPC84X_USART0,
    		amhw_lpc84x_clk_periph_freq_get(LPC84X_USART0),
            __USART_BAUDRATE,
            DMA_CHAN_USART0_TX_REQ);
}
/** [src_am845_core_hw_usart_tx_dma] */

/* end of file */
