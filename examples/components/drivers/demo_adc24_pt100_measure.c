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
 * \brief ADC24�����̶���ѹ��ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���Ӻô��ڣ���PT100�������RTDC��RTDB֮�䣬���̽�RTDA��
 *   2. ���ڽ����ӡ��PT100��ֵ�Լ��¶�ֵ
 *
 * \par Դ����
 * \snippet dome_adc24_pt100_measure.c src_dome_adc24_pt100_measure
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_dome_adc24_pt100_measure
 * \copydoc dome_adc24_pt100_measure.c
 */
#include "ametal.h"
#include "am_adc24.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_pt100_to_temperature.h"

/**
 * \brief ��ȡPT100�ȵ�����ֵ
 */
float am_adc24_thermistor_res_data_get(am_adc24_handle_t  handle)
{
    uint8_t  i;
    float  r_data = 0;
    int32_t   vol_rtdb_c = 0, vol_rtda_c = 0, vol_res = 0;
    int32_t  adc_val[4];
    am_adc_handle_t adc_handle = &handle->adc_serve;
    //����ͨ��ΪADC_2 ADC_4    RTDB---RTDC
    am_adc24_mux_set(handle, ADC24_INPS_AIN(2) | ADC24_INNS_AIN(3));
    am_adc_read(adc_handle, 0, (uint32_t *)adc_val, AM_NELEMENTS(adc_val));
    for(i = 0; i < AM_NELEMENTS(adc_val); i++){
        vol_rtdb_c += adc_val[i];
    }
    vol_rtdb_c /= AM_NELEMENTS(adc_val);

    /*  ����ͨ��ΪADC_3 ADC_4     RTDA---RTDC */
    am_adc24_mux_set(handle, ADC24_INPS_AIN(3) | ADC24_INNS_AIN(3));
    am_adc_read(adc_handle, 0, (uint32_t *)adc_val, AM_NELEMENTS(adc_val));

    for(i = 0; i < AM_NELEMENTS(adc_val); i++){
        vol_rtda_c += adc_val[i];
    }
    vol_rtda_c /= AM_NELEMENTS(adc_val);

    vol_res = vol_rtdb_c * 2 - vol_rtda_c ;

    /* ���õ�ѹУ׼ϵ��  */
    r_data = (float)((float)(vol_res / 8388607.0) * 1999.36);

    return r_data;
}
/**
 * \brief ����AML166�弶���PT100�ȵ������ֵ�Լ���Ӧ��ת���¶�
 */
void demo_adc24_pt100_measure_entry(am_adc24_handle_t  handle,
                                    float             *p_para)
{
    float  r_data = 0, temperature = 0;

    while(1){
        /* ����PT100���汶�� */
        am_adc24_gain_set(handle, 1);

        r_data = am_adc24_thermistor_res_data_get(handle);
        /* ����У׼ϵ��  */
        r_data = p_para[0] * r_data + p_para[1];

        /* PT100����ת�¶�  */
        temperature = pt100_to_temperature(r_data);

        if(temperature < 0){
            temperature *= -1;
            am_kprintf("Tem = -%d.%03d��\r\n",
               ((int32_t)(temperature * 1000) / 1000) ,
               ((int32_t)(temperature * 1000) % 1000));
        }else{
            am_kprintf("Tem = %d.%03d��\r\n\r\n",
               ((int32_t)(temperature * 1000) / 1000) ,
               ((int32_t)(temperature * 1000) % 1000));
        }
        am_mdelay(200);
    }
}
