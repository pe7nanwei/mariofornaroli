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
 * \brief �����嵥7.55
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_hwconf_miniport.h"
#include "app_digitron_count_down.h"

int am_main (void)
{
    am_miniport_view_595_inst_init();      // MiniPort-View����ܣ�HC595������룩ʵ����ʼ��
    app_digitron_count_down(0);            // ʹ����ʾ�����Ϊ0�������
    while (1) {
    }
}


/* end of file */

