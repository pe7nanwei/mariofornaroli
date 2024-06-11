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
 * \brief HC595 ������̣�Ϊ���ڹ۲����󣬽��齫HC595��8��������ӵ�LED��
 *
 * - ʵ������
 *   1. ��ˮ������
 *
 * \par Դ����
 * \snippet demo_std_hc595_led.c src_std_hc595_led
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_hc595_led
 * \copydoc demo_std_hc595_led.c
 */

/** [src_std_hc595_led] */
#include "ametal.h"
#include "am_hc595.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_std_hc595_led_entry (am_hc595_handle_t hc595_handle)
{
    uint8_t buf = 0;
    int     i   = 0;

    while(1) {
        buf = ~(1ul << i);
        am_hc595_send(hc595_handle, &buf, 1); /* ������ǰλ�� LED �� ���͵�ƽ������*/
        am_mdelay(150);                       /* ��ʱ 150ms */
        buf = 0xFF;
        am_hc595_send(hc595_handle, &buf, 1); /* Ϩ��ǰλ�� LED �ƣ��ߵ�ƽϨ�� */

        i = (i + 1) % 8;                      /* �л�����һλ�� */
    }
}
/** [src_std_hc595_led] */

/* end of file */
