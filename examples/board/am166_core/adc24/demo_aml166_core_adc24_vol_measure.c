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
 * - ʵ������
 *   1. ���Ӻô��ڣ�����������ѹ�����Ӧ��ͨ����
 *   2. ���ڽ����ӡ����ѹֵ
 *
 * \par Դ����
 * \snippet demo_aml166_core_cs1239_vol_measure.c src_aml166_core_cs1239_vol_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_cs1239_vol_measure
 * \copydoc demo_aml166_core_cs1239_vol_measure.c
 */

/** [src_aml166_core_cs1239_vol_measure] */
#include <am_aml166_inst_init.h>
#include "string.h"
#include "am_adc24.h"
#include "am_zlg_flash.h"
#include "am_hwconf_aml166_adc24.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief CS1239�̶���ѹ��������
 */
void demo_aml166_core_adc24_vol_measure (void)
{
    float para[16];
    am_adc24_handle_t handle = am_aml166_adc24_inst_init();
    /* ��ȡflash�е�ѹУ׼ϵ�� */
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)((FLASH_BLOCK_NUM * 1024)), 4 * 16);
    dome_adc24_vol_measure_entry(handle, para, AM_ADC24_PGA_1);
}

/** [src_aml166_core_cs1239_vol_measure] */

/* end of file */
