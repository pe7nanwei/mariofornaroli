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
 * \brief ģ��Ƚ������̣���ѹ���ݣ���ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_14 ����ģ������ 3��
 *   2. PIO0_6 ��ѹ��Ϊ���ݵ�ѹ��Դ����ʵ��� 3.3V ��ѹ���� VDDCMP = 3.3V��
 *
 * - ʵ������
 *   1. ���� 3 ���� 1703mV ʱ�����ڻ�����ȽϽ�� "result: PIO0_14_ACMP_I3 > PIO0_6_ACMP_LAD(1703mV)"��
 *   1. ���� 3 С�� 1703mV ʱ�����ڻ�����ȽϽ�� "result: PIO0_14_ACMP_I3 < PIO0_6_ACMP_LAD(1703mV)"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_14 �������� PC ���ڵ� TXD��
 *    PIO0_23 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_acmp_lad.c src_am845_core_hw_acmp_lad
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-21  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_acmp_lad
 * \copydoc demo_am845_core_hw_acmp_lad.c
 */

/** [src_am845_core_hw_acmp_lad] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_acmp.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"
#include "demo_nxp_entries.h"

/**
 * \brief ACMP ƽ̨��ʼ������
 */
am_local void __plfm_acmp_init()
{
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_ACMP);
    amhw_lpc84x_syscon_powerup(AMHW_LPC84X_SYSCON_PD_ACMP);

    /* ʹ�ܹܽ�  PIO0_14 Ϊ�Ƚ������� 3 ���ܣ��Ƚ������� 3 �ܽŹ̶�Ϊ PIO0_14�� */
    am_gpio_pin_cfg (PIO0_14, PIO0_14_ACMP_I3);

    /* ʹ�ܹܽ�  PIO0_6 Ϊ�Ƚ������ݵ�ѹ���ܣ��Ƚ������ݵ�ѹ�ܽŹ̶�Ϊ PIO0_6�� */
    am_gpio_pin_cfg (PIO0_6, PIO0_6_VDDCMP);

    /* ʹ�ܹܽ� PIO0_18 Ϊ�Ƚ���������� */
    am_gpio_pin_cfg (PIO0_18, PIO_FUNC_ACMP_O);
}

/**
 * \brief �������
 */
void demo_am845_core_hw_acmp_lad_entry (void)
{

    am_kprintf("demo am845_core hw acmp lad!\r\n");

    /* ƽ̨��ʼ�� */
    __plfm_acmp_init();
    
    demo_lpc845_hw_acmp_lad_entry(LPC84X_ACMP, PIO0_18);
}
/** [src_am845_core_hw_acmp_lad] */

/* end of file */
