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
 * \brief PMU ���˯��ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ�鲽�裺
 *   1. �öŰ��߽� PIO0_23 �� GND ���ӣ��ѵ�ƽ���͡�
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ�������˯��ģʽ��
 *   2. �� PIO0_23 �� GND �����ӶϿ�ʱ��CPU �����ѣ�LED0 ������˸��
 *
 * \note
 *    1. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ�������˯��
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_am845_core_hw_pmu_deepsleep.c src_am845_core_hw_pmu_deepsleep
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-20  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_hw_pmu_deepsleep
 * \copydoc demo_am845_core_hw_pmu_deepsleep.c
 */

/** [src_am845_core_hw_pmu_deepsleep] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "demo_nxp_entries.h"
#include "lpc84x_periph_map.h"
#include "lpc84x_pin.h"

/**
 * \brief �������
 */
void demo_am845_core_hw_pmu_deepsleep_entry (void)
{

    am_kprintf("demo am845_core hw pmu deepsleep!\r\n");
    /* ��ʱһ�룬�����´����س��� */
    am_mdelay(1000);

    /* ���� PIO0_23 ����Ϊ���� */
    amhw_lpc84x_gpio_pin_dir_input(LPC84X_GPIO, PIO0_23);

    /* ���� PIO0_23 ���� */
    amhw_lpc84x_iocon_mode_set(LPC84X_IOCON,
                               PIO0_23,
                               AMHW_LPC84X_IOCON_MODE_PULLUP);

    /* LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    /* �������˯��ģʽ */
    demo_lpc845_hw_pmu_deepsleep_entry(LPC84X_PMU, PIO0_23);
   
}
/** [src_am845_core_hw_pmu_deepsleep] */

/* end of file */
