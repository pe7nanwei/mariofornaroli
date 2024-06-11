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
 * \brief ��ʱ��׼�ӿ����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ָ���� LED �� 10Hz ��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_std_delay.c src_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_delay
 * \copydoc demo_std_delay.c
 */

/** [src_std_delay] */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"

/**
 * \brief �������
 */
void demo_std_delay_entry (int led_id)
{
    /* ��ʱ 1000us */
    am_udelay(1000);

    AM_FOREVER {
        am_led_toggle(led_id);

        /* ��ʱ 100ms */
        am_mdelay(100);
    }
}
/** [src_std_delay] */

/* end of file */
