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
 * \brief ����Ŵ����� MMC5883MA ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ÿ��һ�룬ͨ�����ڴ�ӡX��Y��Z����ĴŸ�Ӧǿ��ֵ
 *
 * \par Դ����
 * \snippet demo_std_mmc5883ma.c src_std_mmc5883ma
 *
 * \internal
 * \par Modification history
 * - 1.00  18-12-12  wk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_mmc5883ma
 * \copydoc demo_std_mmc5883ma.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_sensor.h"
#include "am_sensor_mmc5883ma.h"
#include "am_delay.h"

/**
 * \brief �������
 */
void demo_std_mmc5883ma_entry (am_sensor_handle_t handle)
{  
    
    /* MMC5883MA�ṩ������ͨ��ID�о� */
    const int id[3] = {AM_MMC5883MA_CHAN_1, AM_MMC5883MA_CHAN_2, AM_MMC5883MA_CHAN_3};
    
    /* ����3��ͨ�����ݵĻ��� */
    am_sensor_val_t data[3];

    int             i;

    /*
     * �г�����ͨ����X,Y,Z��Ÿ�Ӧǿ�ȣ����ݵ����ֺ͵�λ�ַ��������ڴ�ӡ
     */
    const char *data_name_string[] = {"x_axis_data", "y_axis_data", "z_axis_data"};
    const char *data_unit_string[] = {"Gs","Gs","Gs"};

    am_sensor_enable(handle, id, 3, data); 
    	
    while (1) {
        am_sensor_data_get(handle, id, 3, data);
        for(i=0; i<3; i++) {
            if (AM_SENSOR_VAL_IS_VALID(data[i])) { /* ��ͨ��������Ч����������ʹ�� */
                /* ��λת��Ϊ AM_SENSOR_UNIT_MICRO���Դ�ӡ��ʾ6λС�� */
                am_sensor_val_unit_convert(&data[i], 1, AM_SENSOR_UNIT_MICRO);
                am_kprintf("The %s is : %d.%06d %s.\r\n", data_name_string[i],
                                                          (data[i].val)/1000000,
                                                          (data[i].val)%1000000,
                                                          data_unit_string[i]);
            } else {       //��ͨ��������Ч�����ݻ�ȡʧ��
                am_kprintf("The %s get failed!\r\n", data_name_string[i]);
            }
        }
        am_mdelay(1000);
    }
}
                
/* end of file */
