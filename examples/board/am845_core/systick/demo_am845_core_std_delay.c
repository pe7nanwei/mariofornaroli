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
 * \brief Systick ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �� 10Hz ��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_am845_core_std_delay.c src_am845_core_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_delay
 * \copydoc demo_am845_core_std_delay.c
 */

/** [src_am845_core_std_delay] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_std_entries.h"

/**
 * \brief �������
 */
void demo_am845_core_std_delay_entry (void)
{
    AM_DBG_INFO("demo am845 std delay!\r\n");
    demo_std_delay_entry(LED0);
}
/** [src_am845_core_std_delay] */

/* end of file */
