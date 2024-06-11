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
 * \brief �����ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����ʱ������ 100ms �������жϣ������ж�ʱ��ӡ������Ϣ��
 *
 * \note
 *    1. ���Ա� Demo ������ am_prj_config.h �ڽ� AM_CFG_SOFTIMER_ENABLE ����Ϊ 1��
 *       ͨ���ú��Ѿ�Ĭ������Ϊ 1��
 *
 * \par Դ����
 * \snippet demo_std_softimer.c src_std_softimer
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  nwt, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_softimer
 * \copydoc demo_std_softimer.c
 */

/** [src_std_softimer] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_softimer.h"

/**
 * \brief ��ʱ���ص�����
 */
static void softimer_callback (void *p_arg)
{
    AM_DBG_INFO("softimer irq!\r\n");
}

/**
 * \brief �������
 */
void demo_std_softimer_entry (void)
{
    am_softimer_t softimer;

    am_softimer_init(&softimer, softimer_callback, NULL);
    am_softimer_start(&softimer, 100);                    /* ��ʱʱ�䣺100ms  */

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_softimer] */

/* end of file */
