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
 * \brief ZML166���İ� 24λadc���ȵ�ż�¶�
 *
 * - �������裺
 *   1. ���Ӻ��趨���ȵ�ż֮�󣬴򿪴��� PA9 PA10��
 *
 * - ʵ������
 *   1. ���ڽ����ӡ�����¶ȡ�
 *
 * \par Դ����
 * \snippet demo_aml166_core_cs1239_thermistor_measure.c src_aml166_core_cs1239_thermistor_measure
 *
 * \internal
 * \par Modification history
 * - 1.00 19-01-17  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_aml166_core_cs1239_thermistor_measure
 * \copydoc demo_aml166_core_cs1239_thermistor_measure.c
 */

/** [src_aml166_core_cs1239_thermistor_measure] */

#include <am_aml166_inst_init.h>
#include "am_adc24.h"
#include "string.h"
#include "am_hwconf_aml166_adc24.h"
#include "am_zlg_flash.h"
#include "am_thermocouple.h"
#include "zlg116_periph_map.h"
#include "demo_components_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief �ȵ�ż��������
 */
void demo_aml166_core_adc24_thermocouple_measure (void)
{

    float para[16];
    am_adc24_handle_t  handle      = am_aml166_adc24_inst_init();

    /* �ȵ�ż�����Լ���ѹУ׼������ʼ�� */
    am_thermocouplie_init();
    am_zlg_flash_init(ZLG116_FLASH);
    memcpy((void *)para, (uint32_t *)((FLASH_BLOCK_NUM * 1024)), 4 * 16);

    dome_adc24_thermocouple_measure_entry(handle,
                                          para,
                                          THERMOCOUPLIE_K);
}

/** [src_aml166_core_cs1239_thermistor_measure] */

/* end of file */
