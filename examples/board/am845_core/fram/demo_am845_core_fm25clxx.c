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
 * \brief F-RAM ���̣�ͨ����׼�ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ����д���ݵ� F-RAM��
 *   2. ������ F-RAM ��ȡ���ݣ���ͨ�����ڴ�ӡ����
 *   3. ���ڴ�ӡ�����Խ����
 *
 * \internal
 * \par Modification history
 * - 1.00  19-06-06  zjr, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_std_gpio
 * \copydoc demo_am845_core_std_gpio.c
 */

/** [src_am845_core_std_gpio] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_lpc84x_inst_init.h"
#include "demo_components_entries.h"


/**
 * \brief �������
 */
void demo_am845_core_fm25clxx_entry (void)
{
    AM_DBG_INFO("demo am845_core fm25clxx!\r\n");

    demo_fm25clxx_entry(am_fm25clxx_inst_init(), 8);
}
/** [src_am845_core_std_gpio] */

/* end of file */
