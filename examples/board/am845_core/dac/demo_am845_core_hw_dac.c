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
 *    1. LED0/LED1 ��Ҫ�̽� J9/J10 ����ñ�����ֱܷ� PIO1_8/PIO1_10 ���ƣ�
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
#include "am_lpc84x.h"
#include "am_lpc84x_dac.h"
#include "demo_nxp_entries.h"

extern void demo_lpc_hw_dac_buf_int_entry (amhw_lpc_dac_t *p_hw_dac,
                                           int             inum);

/**
 * \brief �������
 */
void demo_am845_core_hw_dac_entry (void)
{
    am_kprintf("demo am845_core hw dac!\r\n");
  
    demo_lpc_hw_dac_buf_int_entry (LPC84X_DAC0, INUM_DAC0);
}
/** [src_am845_core_std_led] */

/* end of file */
