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
 * \brief ѹ����ʪ�ȴ����� BME280 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡѹǿ��ʪ�Ⱥ��¶ȵ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_bme280.c src_std_bme280
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-30  yrz, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_bme280
 * \copydoc demo_std_bme280.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_bme280.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_bme280_entry (am_sensor_handle_t handle)
{
    /* bme280�ṩ������ͨ��ID�о� */
    const int id[3] = {AM_BME280_CHAN_1, AM_BME280_CHAN_2, AM_BME280_CHAN_3};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[3];

    /*
     * �г�����ͨ����ѹ����ʪ�Ⱥ��¶ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"pressure", "temperature", "humidity"};
    const char *data_unit_string[] = {"Pa", "��", "%rH"};

    am_sensor_enable(handle, id, 3, data);

    while(1) {
        am_sensor_data_get(handle, id, 3, data);

        if (AM_SENSOR_VAL_IS_VALID(data[0])) { /* ��ͨ��������Ч����������ʹ�� */
            am_kprintf("The %s is : %d %s.\r\n", data_name_string[0],
                                                 (data[0].val),
                                                 data_unit_string[0]);
        } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
            am_kprintf("The %s get failed!\r\n", data_name_string[0]);
        }
        
        if (AM_SENSOR_VAL_IS_VALID(data[1])) { /* ��ͨ��������Ч����������ʹ�� */
            /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
            am_sensor_val_unit_convert(&data[1], 1, AM_SENSOR_UNIT_MICRO);
            am_kprintf("The %s is : %d.%06d %s.\r\n", data_name_string[1],
                                                      (data[1].val)/1000000,
                                                      (data[1].val)%1000000,
                                                      data_unit_string[1]);
        } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
            am_kprintf("The %s get failed!\r\n", data_name_string[1]);
        }  

        if (AM_SENSOR_VAL_IS_VALID(data[2])) { /* ��ͨ��������Ч����������ʹ�� */
            /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
            am_sensor_val_unit_convert(&data[2], 1, AM_SENSOR_UNIT_MICRO);
            am_kprintf("The %s is : %d.%06d %s.\r\n", data_name_string[2],
                                                      (data[2].val)/1000000,
                                                      (data[2].val)%1000000,
                                                      data_unit_string[2]);
        } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
            am_kprintf("The %s get failed!\r\n", data_name_string[2]);
        }          
        am_mdelay(1000);
    }
}

/* end of file */
