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
 * \brief ���������Ǵ����� BMG160 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡX��Y��Z����Ľ��ٶ�ֵ
 *
 * \par Դ����
 * \snippet demo_std_bmg160.c src_std_bmg160
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-11  wk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_bmg160
 * \copydoc demo_std_bmg160.c
 */
 
#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_bmg160.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_bmg160_entry (am_sensor_handle_t handle)
{

    /* BMG160�ṩ������ͨ��ID�о� */
    const int       id[3] = {AM_BMG160_CHAN_1, AM_BMG160_CHAN_2, AM_BMG160_CHAN_3};

    /* ��������ͨ�����ݵĻ��� */
    am_sensor_val_t data[3];

    int             i; 
    
    /*
     * �г�����ͨ����X��Y��Z����ٶȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"x_axis_angular_velocity", 
                                      "y_axis_angular_velocity",
                                      "z_axis_angular_velocity"};
    const char *data_unit_string[] = {"rad/s", "rad/s", "rad/s"};

    am_sensor_enable(handle, id, 3, data);
    
    while(1) {
        am_sensor_data_get(handle, id, 3, data);
        for(i=0; i<3; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* ��ͨ��������Ч����������ʹ�� */
                /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
                am_sensor_val_unit_convert(&data[i], 1, AM_SENSOR_UNIT_MICRO);
                am_kprintf("The %s is : %d.%06d %s.\r\n", data_name_string[i],
                                                         (data[i].val)/1000000,
                                                         (data[i].val)%1000000,
                                                          data_unit_string[i]);
            } else {       /* ��ͨ��������Ч�����ݻ�ȡʧ�� */
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        am_mdelay(1000);
    }
}

/* end of file */
