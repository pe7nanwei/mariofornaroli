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
 * \brief
 *
 * - ʵ������
 *   1. ���Ӻô��ڣ���PT100�������RTDC��RTDB֮�䣬���̽�RTDA��
 *   2. ���ڽ����ӡ��PT100�����¶�ֵ
 *
 * \par Դ����
 * \snippet demo_aml166_core_cs1239_pt100_measure.c src_aml166_core_cs1239_pt100_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_cs1239_pt100_measure
 * \copydoc demo_aml166_core_cs1239_pt100_measure.c
 */

/** [src_aml166_core_cs1239_pt100_measure] */
#include <am_aml166_inst_init.h>
#include "string.h"
#include "am_adc24.h"
#include "am_hwconf_aml166_adc24.h"
#include "am_zlg_flash.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief CS1239 PT100��������
 */
void demo_aml166_core_adc24_pt100_measure (void)
{
    float para[2];
    am_adc24_handle_t  handle = am_aml166_adc24_inst_init();
    /* ��flash�л�ȡPT100���������ϵ�� */
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)PT100_PARA_SAVE_ADDRESS, 4 * 2);
    /* ��flash��δ����ϵ�� */
    if(para[0] > 1.1 || para[0] < 0.9) para[0] = 1;
    if(para[0] > 0.15 || para[0] < -0.15)para[0] = 0;
    demo_adc24_pt100_measure_entry(handle, para);
}

/** [src_aml166_core_cs1239_pt100_measure] */

/* end of file */
