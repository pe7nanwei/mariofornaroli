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
 * \brief ��ʱ��ͨ���Ƚ�ƥ�����ŷ�ת���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIOA_4 ������ 10Hz ��Ƶ�ʽ��з�ת��
 *
 * \note
 *    ���� TIM14 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã�ʹ�ñ� Demo ֮ǰ������
 *    am_prj_config.h �ڽ� AM_CFG_KEY_GPIO_ENABLE��AM_CFG_SOFTIMER_ENABLE
 *    �� AM_CFG_SYSTEM_TICK_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_am116_core_hw_tim_cmp_toggle.c src_am116_core_hw_tim_cmp_toggle
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-22  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_hw_tim_cmp_toggle
 * \copydoc demo_am116_core_hw_tim_cmp_toggle.c
 */

/** [src_am116_core_hw_tim_cmp_toggle] */
#include "ametal.h"
#include "am_clk.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zlg116.h"
#include "am_zlg116_clk.h"
#include "demo_zlg_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_hw_tim_cmp_toggle_entry (void)
{
    AM_DBG_INFO("demo am116_core hw tim cmp toggle!\r\n");

    /* ��ʼ������ */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_TIM14_CH1 | PIOA_4_AF_PP);

    /* ʹ�ܶ�ʱ��ʱ�� */
    am_clk_enable(CLK_TIM14);

    /* ��λ��ʱ�� */
    am_zlg116_clk_reset(CLK_TIM14);

    demo_zlg_hw_tim_cmp_toggle_entry(ZLG116_TIM14,
                                     AMHW_ZLG_TIM_TYPE2,
                                     0,
                                     am_clk_rate_get(CLK_TIM14),
                                     INUM_TIM14);
}
/** [src_am116_core_hw_tim_cmp_toggle] */

/* end of file */
