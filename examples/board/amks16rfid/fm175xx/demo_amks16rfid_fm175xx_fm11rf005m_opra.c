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
 * \brief fm175xx��FM11R005M���Ϳ����в���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��FM11R005M���Ϳ��������߸�Ӧ����
 *
 * - ʵ������
 *   1. ���ڽ����ӡFM11R005M����UID
 *   2. ���ڽ����ӡд�������
 *
 * \par Դ����
 * \snippet demo_amks16rfid_dr_fm11rf005m_opra.c src_amks16rfid_dr_fm11rf005m_opra
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16rfid_dr_fm11rf005m_opra
 * \copydoc demo_amks16rfid_dr_fm11rf005m_opra.c
 */

/** [src_amks16rfid_dr_fm11rf005m_opra] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"

/**
 * \brief FM11RF005M����������
 */
void demo_amks16rfid_dr_fm11rf005m_operate (void)
{
    am_fm175xx_handle_t handle = am_fm175xx_inst_init();

    demo_fm175xx_fm11rf005m_operate(handle);
}

/** [src_amks16rfid_dr_fm11rf005m_opra] */

/* end of file */
