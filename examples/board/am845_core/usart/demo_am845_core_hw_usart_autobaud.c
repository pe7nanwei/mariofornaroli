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
 * \brief USART �Զ�ƥ�䲨�������̣�ͨ��Ӳ����ӿ�ʵ��
 *
 * - �������裺
 *   1. ����λ�����յ� "please set a new baudrate and then input '5'"ʱ���ı�
 *      ��λ���Ĳ�����Ϊ 4800 �� 9600,Ȼ�������ַ� 'a' �� '5'��
 *
 * - ʵ������
 *   1. �Զ�������ƥ��ɹ��󣬴��ڴ�ӡ "The usart baudrate is xxx"���������룻
 *   2. ����������յ����ַ�����
 *
 * \note
 *    1. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_14 �������� PC ���ڵ� TXD��
 *       PIO0_23 �������� PC ���ڵ� RXD��
 *    2. ����ԭ��MCU Ӳ��ͨ������ RXD ���Ž�������ʱ���������½���֮���ʱ��
 *       ����Զ����㲨���ʣ�����Ҫ����λ�����͵����ݣ�'a' �� '5'����
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_usart_autobaud.c src_am845_core_hw_usart_autobaud
 *
 * \internal
 * \par Modification History
 * - 1.00 15-07-03  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_usart_autobaud
 * \copydoc demo_am845_core_hw_usart_autobaud.c
 */

 /** [src_am845_core_hw_usart_autobaud] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_usart_autobaud_entry (void)
{
    am_kprintf("demo am845 hw usart autobaud!\r\n");
    demo_lpc845_hw_usart_autobaud_entry(LPC84X_USART0,
        amhw_lpc84x_clk_periph_freq_get(LPC84X_USART0));
}
/** [src_am845_core_hw_usart_autobaud] */

/* end of file */
