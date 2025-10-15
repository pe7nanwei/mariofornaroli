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
 * \brief ��ʪ�ȴ����� HTS221 ���̣�ͨ������ģʽʵ��
 *
 * - ʵ������
 *   1. �������õ�Ƶ�ʣ����ж��л�ȡ���ݣ���ͨ�����ڴ�ӡ
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-27  wan, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_hts221.h"
#include "am_delay.h"

/** \brief HTS221��������ID */
const static int __hts221_id[2] = {0, 1};

/* \breif HTS221���������� */
static am_sensor_val_t __hts221_data[2];

/**
 * \brief ͨ��1��ʪ�ȵĻص�����
 */
static void __pfn_humidity (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__hts221_id[0], 1, &__hts221_data[0]);
        am_sensor_val_unit_convert(&__hts221_data[0], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is humidity, value is: %d.%06d rH!\r\n",
                   __hts221_id[0],
                   (__hts221_data[0].val)/1000000,
                   (__hts221_data[0].val)%1000000);
    }
}

/**
 * \brief ͨ��2���¶ȵĻص�����
 */
static void __pfn_temprature (void *p_arg, uint32_t trigger_src)
{
    am_sensor_handle_t handle = (am_sensor_handle_t)p_arg;
    if (trigger_src & AM_SENSOR_TRIGGER_DATA_READY) {
        am_sensor_data_get(handle, &__hts221_id[1], 1, &__hts221_data[1]);
        am_sensor_val_unit_convert(&__hts221_data[1], 1, AM_SENSOR_UNIT_MICRO);
        am_kprintf("The channel %d,type is temprature, value is: %d.%06d  ��!\r\n",
                   __hts221_id[1],
                   (__hts221_data[1].val)/1000000,
                   (__hts221_data[1].val)%1000000);
    }
}

/**
 * \brief �������
 */
void demo_std_hts221_int_entry (am_sensor_handle_t handle)
{
    am_err_t ret = AM_OK;
	
    /* ���øô��������������Ƶ��Ϊ12.5Hz����·ͨ��ͬ���� */
    am_sensor_val_t hts221_rate = {125, AM_SENSOR_UNIT_DECI};

    ret = am_sensor_attr_set(handle,
                             __hts221_id[0],
                             AM_SENSOR_ATTR_SAMPLING_RATE,
                             &hts221_rate);
    if (ret != AM_OK) {
        am_kprintf("sensor_attr_set faild!\r\n");
    }

    /* ʹ����·ͨ�� */
    am_sensor_enable(handle, __hts221_id, 2, __hts221_data);

    /* ����ͨ��0��1�Ĵ����ص����� */
    am_sensor_trigger_cfg(handle,
                          __hts221_id[0],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_humidity,
                          (void*)handle);
    am_sensor_trigger_cfg(handle,
                          __hts221_id[1],
                          AM_SENSOR_TRIGGER_DATA_READY,
                          __pfn_temprature,
                          (void*)handle);

    /* ��ͨ��0��1�Ĵ���ģʽ */
    am_sensor_trigger_on(handle, __hts221_id[0]);
    am_sensor_trigger_on(handle, __hts221_id[1]);

}

/* end of file */
