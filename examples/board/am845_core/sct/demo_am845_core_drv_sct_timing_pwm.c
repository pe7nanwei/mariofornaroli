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
 * \brief SCT 32 λ PWM ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_23(SCT_OUT0) ��� 500Hz �� PWM��ռ�ձ�Ϊ 25%��
 *   2. LED0 ״̬��תƵ��Ϊ 500Hz��
 *
 * \note
 *    1. �������£��¼� 0 ÿ 2000000ns ����� IO ͨ�� 0 �øߣ��������жϣ��������ڣ�
 *       �¼� 1 ÿ 500000ns��ռ���� 25%������� IO ͨ�� 0 ���㣬����ռ�ձȣ�
 *    2. �������£�ÿ�����¼� 0 ʱ���¼� 1 Ҳ��ͬʱ��������ʱ�����¼���������� IO
 *       ͨ�� 0���Ҳ�����ƽ��ͻ����ʱ��Ҫ�ƶ������ͻ�İ취������ָ�����������ϴ�
 *       ��ƽ���䣻
 *    3. ���� SCT Ĭ����Ϊ������������ʹ�ò��Ա� Demo ǰ��Ҫ�� am_prj_config.h ��
 *       �� AM_CFG_BUZZER_ENABLE ����Ϊ 0����ʹ�÷�������
 *
 * \par Դ����
 * \snippet demo_am845_core_drv_sct_timing_pwm.c src_am845_core_drv_sct_timing_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-03  hgo, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_drv_sct_timing_pwm
 * \copydoc demo_am845_core_drv_sct_timing_pwm.c
 */

/** [src_am845_core_drv_sct_timing_pwm] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x_inst_init.h"
#include "demo_nxp_entries.h"
#include "lpc84x_pin.h"

/**
 * \brief �������
 */
void demo_am845_core_drv_sct_timing_pwm_entry (void)
{
    am_lpc_sct_handle_t lpc84x_sct_handle = NULL;

    AM_DBG_INFO("demo am845_core sct pwm service\r\n");
    AM_DBG_INFO("The PIO0_23(SCT_OUT0) PWM: freq is 500Hz, "
                "The duty ratio is 25%% \r\n");

    lpc84x_sct_handle = am_lpc84x_sct0_inst_init();

    /* �� PIO0_23 ������ SCT �����ͨ�� 0 */
    am_gpio_pin_cfg(PIO0_23, PIO_FUNC_SCT_OUT0);

    /* ���� SCT ״̬Ϊ 0 */
    am_lpc_sct_state_set(lpc84x_sct_handle, 0);

    demo_lpc_drv_sct_timing_pwm_entry(lpc84x_sct_handle);

}
/** [src_am845_core_drv_sct_timing_pwm] */

/* end of file */
