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
 * \brief ѹ���¶ȴ����� LPS22HB ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������õ�Ƶ�ʣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-04  yrz, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_lps22hb.h"
#include "am_delay.h"

/** \brief LPS22HB��������ID */
const static int __lps22hb_id[2] = {AM_LPS22HB_CHAN_1, AM_LPS22HB_CHAN_2};

/* \breif LPS22HB���������� */
static am_sensor_val_t __lps22hb_data[2];

/**
 * \brief ͨ��1��ʪ�ȵĻص�����
 */
static void __pfn_pressure (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__lps22hb_id[0], 1, &__lps22hb_data[0]);
        am_sensor_val_unit_convert(&__lps22hb_data[0], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is pressure, value is: %d Pa!\r\n",
                   __lps22hb_id[0],
                   __lps22hb_data[0].val);
    }
}

/**
 * \brief ͨ��2���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__lps22hb_id[1], 1, &__lps22hb_data[1]);
        am_sensor_val_unit_convert(&__lps22hb_data[1], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is temprature, value is: %d.%06d  ��!\r\n",
                   __lps22hb_id[1],
                   (__lps22hb_data[1].val)/1000000,
                   (__lps22hb_data[1].val)%1000000);
    }
}

/**
 * \brief �������
 */
void demo_std_lps22hb_int_entry (am_sensor_handle_t handle)
{
    /* ���øô��������������Ƶ��Ϊ10Hz����·ͨ��ͬ���� */
    am_sensor_val_t lps22hb_rate = {10, AM_SENSOR_UNIT_BASE};
    
    am_err_t ret = AM_OK;

    ret = am_sensor_attr_set(handle,
                             __lps22hb_id[0],
                             AM_SENSOR_ATTR_SAMPLING_RATE,
                             &lps22hb_rate);
    if (ret != AM_OK) {
        am_kprintf("sensor_attr_set faild!\r\n");
    }

    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __lps22hb_id, 2, __lps22hb_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __lps22hb_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_pressure,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __lps22hb_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __lps22hb_id[0]);
    am_sensor_trigger_on(handle, __lps22hb_id[1]);
}

/* end of file */
