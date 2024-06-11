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
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �������� 0.5s ��ʱ�������С�
 *
 * \note
 *    ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_BUZZER_ENABLE ����Ϊ 1��
 *    ͨ���ú��Ѿ�Ĭ������Ϊ 1��
 *
 * \par Դ����
 * \snippet demo_std_buzzer.c src_std_buzzer
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-20  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_buzzer
 * \copydoc demo_std_buzzer.c
 */

/** [src_std_buzzer] */
#include "ametal.h"
#include "am_delay.h"
#include "am_buzzer.h"

/**
 * \brief �������
 */
void demo_std_buzzer_entry (void)
{
    am_buzzer_on();
    am_mdelay(500);
    am_buzzer_off();
    am_mdelay(500);

    AM_FOREVER {

        am_buzzer_beep(500);  /* ���������� 0.5s */
        am_mdelay(500);
    }
}
/** [src_std_buzzer] */

/* end of file */
