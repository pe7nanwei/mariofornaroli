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
 * \brief LED ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� LED1 �� 0.5s ��ʱ������˸��
 *
 * \note
 *    1. LED0/LED1 ��Ҫ�̽� J9/J10 ����ñ�����ֱܷ� PIO0_20/PIO0_21 ���ƣ�
 *    2. ���Ա����̱����� am_prj_config.h �ڽ� AM_CFG_LED_ENABLE ����Ϊ 1�����ú�
 *       �Ѿ�Ĭ������Ϊ 1�� �û������ٴ����á�
 *
 * \par Դ����
 * \snippet demo_am845_core_std_led.c src_am845_core_std_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_led
 * \copydoc demo_am845_core_std_led.c
 */

/** [src_am845_core_std_led] */
#include "ametal.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_adc.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "demo_std_entries.h"
#include "hw/amhw_lpc84x_dac.h"
#define __MV_OUT                 1000

extern void demo_std_dac_entry (am_dac_handle_t dac0_handle,
                                uint8_t         channel,
                                uint32_t        mv_out);

/**
 * \brief �������
 */
void demo_am845_core_std_dac_entry (void)
{
    am_kprintf("demo am845_core std adc!\r\n");

      /* DACʵ����ʼ��������ȡDAC���ֵ */
    am_dac_handle_t dac0_handle = (am_dac_handle_t)am_lpc84x_dac0_inst_init();

    demo_std_dac_entry (dac0_handle, AMHW_LPC_DAC0_CHAN_0,__MV_OUT);
}
/** [src_am845_core_std_led] */

/* end of file */
