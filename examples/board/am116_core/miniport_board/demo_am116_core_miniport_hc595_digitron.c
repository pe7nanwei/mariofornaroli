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
 * \brief MiniPort-View + MiniPort-595 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������
 *   1. �Ƚ� MiniPort-595 ����ֱ���� AM116-Core �� MiniPort �����ӣ�
 *   2. �� MiniPort-View ������ MiniPort-595 �ӿ������ӡ�
 *
 * - ʵ������
 *   1. ���Կ�����ֵ 0 ~ 59 �����������
 *   2. ����С�� 30 ʱ����λ��˸������ 30 ʱʮλ��˸��
 *
 * \par Դ����
 * \snippet demo_am116_core_miniport_hc595_digitron.c src_am116_core_miniport_hc595_digitron
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_am116_core_miniport_hc595_digitron
 * \copydoc demo_am116_core_miniport_hc595_digitron.c
 */

/** [src_am116_core_miniport_hc595_digitron] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zlg116_inst_init.h"
#include "demo_std_entries.h"
#include "demo_am116_core_entries.h"

/**
 * \brief �������
 */
void demo_am116_core_miniport_hc595_digitron_entry (void)
{
    AM_DBG_INFO("demo am116_core miniport hc595 digitron!\r\n");

    am_miniport_view_595_inst_init();

    demo_std_digitron_60s_counting_entry(0);
}
/** [src_am116_core_miniport_hc595_digitron] */

/* end of file */
