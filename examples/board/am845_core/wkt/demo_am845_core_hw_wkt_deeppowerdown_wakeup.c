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
 * \brief WKT ��ȵ��绽�����̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ������ȵ���ģʽ��
 *   2. �ȴ� 5s ��WKT ��ʱʱ�䵽��CPU �����ѣ����ͨ�üĴ�������У����ȷ��LED0
 *      ��˸һ�Σ����ͨ�üĴ�������У�����LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO1_3 ���ƣ�
 *    2. ������ȵ���ģʽ��ֻ�� WAKEUP ���ź� WKT ��ʱ���ܻ���оƬ������Ĭ��״̬��
 *       WAKEUP ���Ż���ʹ�ܣ�����һ��ȷ�� WAKEUP �ⲿ��������Դ����֤��Ч�ĸߵ�ƽ
 *       ״̬��������������Ѳ��������۲첻�� WKT ���� CPU���������̽� WAKEUP ����
 *       (PIO0_4)���ѹ��ܽ�ֹ�ˣ����Բ���Ҫ�� PIO0_4 ������
 *    3. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ������ȵ���
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_wkt_deeppowerdown_wakeup.c src_am845_core_hw_wkt_deeppowerdown_wakeup
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-14  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_wkt_deeppowerdown_wakeup
 * \copydoc demo_am845_core_hw_wkt_deeppowerdown_wakeup.c
 */

/** [src_am845_core_hw_wkt_deeppowerdown_wakeup] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_clk.h"
#include "demo_nxp_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_wkt_deeppowerdown_wakeup_entry (void)
{
    am_kprintf("demo am_845core hw wkt deeppowerdown wakeup!\r\n");
    /* ��ʼ�� WKT AHB ʱ�� */
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_WKT);

    /* ��λ WFT */
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_WKT);

    /* �͹���ʱ��Դ */
    amhw_lpc_wkt_clksel_cfg(LPC84X_WKT, AMHW_LPC_WKT_LOW_POWER_CLOCK);

    demo_lpc845_hw_wkt_deeppowerdown_wakeup_entry(LPC84X_PMU,
                                                  LPC84X_WKT,
                                                  INUM_WKT, 
                                                  5000);
}
/** [src_am845_core_hw_wkt_deeppowerdown_wakeup] */

/* end of file */
