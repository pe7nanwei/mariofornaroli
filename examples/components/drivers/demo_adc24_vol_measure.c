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
 *   1. ���Ӻô��ڣ�����������ѹ�����Ӧ��ͨ����
 *   2. ѡ���Ӧ�����汶���������ѹ*����ӦС�ڻ�׼��ѹ
 *   3. ���ڽ����ӡ����ѹֵ
 *   4. ���ڳ����������л���ѹֵ  ֱ��������Ӧ�����ּ��ɡ�
 *
 * \par Դ����
 * \snippet dome_adc24_adjust_vol_entry.c src_dome_adc24_adjust_vol_entry
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-28  htf, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_adc24_adjust_vol_entry
 * \copydoc dome_adc24_adjust_vol_entry.c
 */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_adc24.h"

/**
 * \brief ADC24��ѹ��������
 */
void dome_adc24_vol_measure_entry(am_adc24_handle_t  handle,
                                  float             *p_para,
                                  uint8_t            gpa_index)
{
    
	  am_adc24_gain_set(handle, 1 << gpa_index);

    am_adc24_mux_set(handle, ADC24_INPS_AIN3 | ADC24_INNS_AIN2);

    while(1){
        uint8_t i = 0;
        int32_t adc_val[10];
        double vol = 0;;
        am_adc_read(&handle->adc_serve, 0, (void *)adc_val, AM_NELEMENTS(adc_val));

        for(i = 0 ; i < AM_NELEMENTS(adc_val); i++){
            vol += adc_val[i] / AM_NELEMENTS(adc_val);
        }

        vol = (double)((double)(vol  / 8388607.0) * handle->p_devinfo->vref);
        vol = p_para[gpa_index * 2] * vol + p_para[gpa_index * 2 + 1];
        vol *= 10000;
        vol /= (1 << gpa_index);
        if(vol > 0){
            am_kprintf("Voltage is %d.%04d\r\n", (int32_t)vol/10000, (int32_t)vol%10000);
        }else {
            vol *= -1;
            am_kprintf("Voltage is  -%d.%04d\r\n", (int32_t)vol/10000, (int32_t)vol%10000);
        }
    }
}
