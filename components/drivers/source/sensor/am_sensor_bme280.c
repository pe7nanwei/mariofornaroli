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
 * \brief ������ BME280 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-30  yrz, first implementation.
 * \endinternal
 */

#include "am_sensor_bme280.h"
#include "am_vdebug.h"
#include "am_delay.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define  __BME280_REG_H_LSB         0XFE    /**< \brief ʪ�ȵ��ֽڵ�ַ        */
#define  __BME280_REG_H_MSB         0XFD    /**< \brief ʪ�ȸ��ֽڵ�ַ        */
#define  __BME280_REG_T_XLSB        0XFC    /**< \brief �¶ȵ��ֽڵ�ַ        */   
#define  __BME280_REG_T_LSB         0XFB    /**< \brief �¶ȴε��ֽڵ�ַ      */   
#define  __BME280_REG_T_MSB         0XFA    /**< \brief �¶ȸ��ֽڵ�ַ        */ 
#define  __BME280_REG_P_XLSB        0XF9    /**< \brief ��ѹ���ֽڵ�ַ        */
#define  __BME280_REG_P_LSB         0XF8    /**< \brief ��ѹ�ε��ֽڵ�ַ      */
#define  __BME280_REG_P_MSB         0XF7    /**< \brief ��ѹ���ֽڵ�ַ        */
#define  __BME280_REG_CONFIG        0XF5    /**< \brief ���üĴ�����ַ        */
#define  __BME280_REG_CTRL_MEAS     0XF4    /**< \brief ���Ʋ����Ĵ�����ַ    */
#define  __BME280_REG_STATUS        0XF3    /**< \brief ״̬�Ĵ�����ַ        */
#define  __BME280_REG_CTRL_HUM      0XF2    /**< \brief ����ʪ�Ȳ����Ĵ�����ַ*/
#define  __BME280_REG_RESET         0XE0    /**< \brief ��λ�Ĵ�����ַ        */
#define  __BME280_REG_ID            0XD0    /**< \brief ID�Ĵ�����ַ          */
#define  __BME280_MY_ID             0x60    /**< \brief �豸ID                */
#define  __BME280_CMD_RESET        	0xB6    /**< \brief �豸��λ����          */
                                              
#define  __BME280_REG_DIG_T1	    0x88    /**< \brief �¶�У׼ֵ1��ַ       */
#define  __BME280_REG_DIG_T1_LEN	2       /**< \brief �¶�У׼ֵ1��ַ����   */
#define  __BME280_REG_DIG_T2        0x8A    /**< \brief �¶�У׼ֵ2��ַ       */
#define  __BME280_REG_DIG_T2_LEN    2       /**< \brief �¶�У׼ֵ2��ַ����   */
#define  __BME280_REG_DIG_T3	    0x8C    /**< \brief �¶�У׼ֵ3��ַ       */
#define  __BME280_REG_DIG_T3_LEN    2       /**< \brief �¶�У׼ֵ3��ַ����   */
                                              
#define  __BME280_REG_DIG_P1        0x8E    /**< \brief ѹ��У׼ֵ1��ַ       */
#define  __BME280_REG_DIG_P1_LEN    2       /**< \brief ѹ��У׼ֵ1��ַ����   */
#define  __BME280_REG_DIG_P2	    0x90    /**< \brief ѹ��У׼ֵ2��ַ       */
#define  __BME280_REG_DIG_P2_LEN    2       /**< \brief ѹ��У׼ֵ2��ַ����   */
#define  __BME280_REG_DIG_P3        0x92    /**< \brief ѹ��У׼ֵ3��ַ       */
#define  __BME280_REG_DIG_P3_LEN    2       /**< \brief ѹ��У׼ֵ3��ַ����   */
#define  __BME280_REG_DIG_P4	    0x94    /**< \brief ѹ��У׼ֵ4��ַ       */
#define  __BME280_REG_DIG_P4_LEN    2       /**< \brief ѹ��У׼ֵ4��ַ����   */
#define  __BME280_REG_DIG_P5        0x96    /**< \brief ѹ��У׼ֵ5��ַ       */
#define  __BME280_REG_DIG_P5_LEN    2       /**< \brief ѹ��У׼ֵ5��ַ����   */
#define  __BME280_REG_DIG_P6	    0x98    /**< \brief ѹ��У׼ֵ6��ַ       */
#define  __BME280_REG_DIG_P6_LEN    2       /**< \brief ѹ��У׼ֵ6��ַ����   */
#define  __BME280_REG_DIG_P7        0x9A    /**< \brief ѹ��У׼ֵ7��ַ       */
#define  __BME280_REG_DIG_P7_LEN    2       /**< \brief ѹ��У׼ֵ7��ַ����   */
#define  __BME280_REG_DIG_P8	    0x9C    /**< \brief ѹ��У׼ֵ8��ַ       */
#define  __BME280_REG_DIG_P8_LEN    2       /**< \brief ѹ��У׼ֵ8��ַ����   */
#define  __BME280_REG_DIG_P9        0x9E    /**< \brief ѹ��У׼ֵ9��ַ       */
#define  __BME280_REG_DIG_P9_LEN    2       /**< \brief ѹ��У׼ֵ9��ַ����   */

#define  __BME280_REG_DIG_H1        0xA1    /**< \brief ʪ��У׼ֵ1��ַ       */
#define  __BME280_REG_DIG_H2_LSB    0xE1    /**< \brief ʪ��У׼ֵ2���ֽڵ�ַ */
#define  __BME280_REG_DIG_H2_MSB    0xE2    /**< \brief ʪ��У׼ֵ2���ֽڵ�ַ */
#define  __BME280_REG_DIG_H3        0xE3    /**< \brief ʪ��У׼ֵ3��ַ       */
#define  __BME280_REG_DIG_H4_LSB    0xE5    /**< \brief ʪ��У׼ֵ4���ֽڵ�ַ */
#define  __BME280_REG_DIG_H4_MSB    0xE4    /**< \brief ʪ��У׼ֵ4���ֽڵ�ַ */
#define  __BME280_REG_DIG_H5_LSB    0xE5    /**< \brief ʪ��У׼ֵ5���ֽڵ�ַ */
#define  __BME280_REG_DIG_H5_MSB    0xE6    /**< \brief ʪ��У׼ֵ5���ֽڵ�ַ */
#define  __BME280_REG_DIG_H6        0xE7    /**< \brief ʪ��У׼ֵ6��ַ       */


/** \brief ��ȡDATA״̬λ */
#define __BME280_GET_DATA_STATUS(reg)   (((reg) >> 3) & 0x1)

/** \brief ������int8ת��Ϊһ��int16���� */
#define __BME280_UINT8_TO_UINT16(buff) ((int16_t)((buff[1] << 8) | buff[0]))

/** \brief ������int8ת��Ϊһ��20bit���� */
#define __BME280_UINT8_TO_UINT32(buff) \
                       (int32_t)(((int32_t)(buff[0]) << 12) \
                               | ((int32_t)(buff[1]) << 4)  \
                               | ((int32_t)(buff[2]) >> 4))
/** \brief ����У׼ֵt1��t2��t3���������t���¶�ʵ��ֵ ������10^6�� */ 
#define __BME280_GET_TEM_VALUE(t, t1, t2, t3) \
                (((((((double)t) / 16384.0 - ((double) t1) / 1024.0) * \
                  ((double) t2)) + (((((double)t) / 131072.0 - ((double) t1) / \
                  8192.0) * (((double)t) / 131072.0 - ((double) t1) / \
                  8192.0)) * ((double) t3))) * 1000000) / 5120)
/** \brief ����У׼ֵt1��t2��t3�������ѹУ׼�Ĳ���t_define */ 
#define __BME280_GET_T_DEFINE(t, t1, t2, t3) \
                (((((double)t) / 16384.0 - ((double) t1) / 1024.0) * \
                  ((double) t2)) + (((((double)t) / 131072.0 - ((double) t1) / \
                  8192.0) * (((double)t) / 131072.0 - ((double) t1) / \
                  8192.0)) * ((double) t3)))
 
/** \brief ģ�鹤�� */
#define __BME280_NORMAL                   (0x3<<0)
/** \brief ģ��˯�� */
#define __BME280_SLEEP                    (~(0x3<<0))
/** \brief ��ʪ�Ȳ��� */ 
#define __BME280_HUM_START                (0x2<<0)
/** \brief �ر�ʪ�Ȳ��� */ 
#define __BME280_HUM_CLOSE                (~(0x2<<0))  
/** \brief ��ѹǿ���� */ 
#define __BME280_PRESS_START              (0x2<<2)
/** \brief �ر�ѹǿ���� */ 
#define __BME280_PRESS_CLOSE              (~(0x2<<2))
/** \brief ���¶Ȳ��� */ 
#define __BME280_TEMP_START               (0x2<<5)
/** \brief �ر��¶Ȳ��� */ 
#define __BME280_TEMP_CLOSE               (~(0x2<<5))
/*******************************************************************************
 * ���غ�������
 ******************************************************************************/
/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id);

/** \brief ��ȡ������ͨ���������� */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf);

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result);

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result);

/** \brief ���ô�����ͨ������ */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val);

/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val);

/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg);

/** \brief �򿪴��� */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id);

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id);

/** \brief ��������׼���� */
am_local am_const struct am_sensor_drv_funcs __g_sensor_bme280_funcs = {
        __pfn_type_get,
        __pfn_data_get,
        __pfn_enable,
        __pfn_disable,
        __pfn_attr_set,
        __pfn_attr_get,
        __pfn_trigger_cfg,
        __pfn_trigger_on,
        __pfn_trigger_off
};
/*******************************************************************************
  Local functions
*******************************************************************************/
/**
 * \brief BME280 д����
 */
am_local am_err_t __bme280_write (am_sensor_bme280_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief BME280 ������
 */
am_local am_err_t __bme280_read (am_sensor_bme280_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief ��ȡѹ��У׼ֵ
 */
am_local am_err_t __bme280_get_press_cal (am_sensor_bme280_dev_t *p_this)
{
    uint8_t buff[2] = {0};

    am_err_t ret = AM_OK;

    /**
     * \brief ����Ϊ��ȡѹ��У׼��9������
     */
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P1,
                        buff,
                        __BME280_REG_DIG_P1_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p1 = __BME280_UINT8_TO_UINT16(buff);

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P2,
                        buff,
                        __BME280_REG_DIG_P2_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p2 = __BME280_UINT8_TO_UINT16(buff);  

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P3,
                        buff,
                        __BME280_REG_DIG_P3_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p3 = __BME280_UINT8_TO_UINT16(buff);     
 
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P4,
                        buff,
                        __BME280_REG_DIG_P4_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p4 = __BME280_UINT8_TO_UINT16(buff); 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P5,
                        buff,
                        __BME280_REG_DIG_P5_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p5 = __BME280_UINT8_TO_UINT16(buff); 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P6,
                        buff,
                        __BME280_REG_DIG_P6_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p6 = __BME280_UINT8_TO_UINT16(buff);
    
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P7,
                        buff,
                        __BME280_REG_DIG_P7_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p7 = __BME280_UINT8_TO_UINT16(buff);    
    
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P8,
                        buff,
                        __BME280_REG_DIG_P8_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p8 = __BME280_UINT8_TO_UINT16(buff);  

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_P9,
                        buff,
                        __BME280_REG_DIG_P9_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_p9 = __BME280_UINT8_TO_UINT16(buff);
    
    return ret;
}

/**
 * \brief ��ȡ�¶�У׼ֵ
 */
am_local am_err_t __bme280_get_tem_cal (am_sensor_bme280_dev_t *p_this)
{
    uint8_t buff[2] = {0};
    
    am_err_t ret = AM_OK;

    /**
     * \brief ����Ϊ��ȡ�¶�У׼��3������
     */
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_T1,
                        buff,
                        __BME280_REG_DIG_T1_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t1 = __BME280_UINT8_TO_UINT16(buff);

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_T2,
                        buff,
                        __BME280_REG_DIG_T2_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t2 = __BME280_UINT8_TO_UINT16(buff); 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_T3,
                        buff,
                        __BME280_REG_DIG_T3_LEN);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_t3 = __BME280_UINT8_TO_UINT16(buff);    
    
    return ret;
}

/**
 * \brief ��ȡʪ��У׼ֵ
 */
am_local am_err_t __bme280_get_hum_cal (am_sensor_bme280_dev_t *p_this)
{
    uint8_t buff[2] = {0};
    
    am_err_t ret = AM_OK;

    /**
     * \brief ����Ϊ��ȡ�¶�У׼��6������
     */
    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H1,
                        buff,
                        1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h1 = buff[0];

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H2_LSB,
                        buff,
                        2);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h2 = __BME280_UINT8_TO_UINT16(buff); 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H3,
                        buff,
                        1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h3 = buff[0]; 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H4_MSB,
                        buff,
                        2);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h4 = (int16_t)((buff[0] << 4) | (buff[1] & 0x0f)); 

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H5_LSB,
                        buff,
                        2);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h5 = (int16_t)((buff[1] << 4) | ((buff[0] & 0xf0) >> 4));     

    ret = __bme280_read(p_this,
                        __BME280_REG_DIG_H6,
                        buff,
                        1);
    if (ret != AM_OK) {
        return ret;
    }
    p_this->cal_val.dig_h6 = buff[0];     
    
    return ret;
}

/** \brief ������ѹ */
am_local int32_t __bme280_press_cal (am_sensor_bme280_dev_t *p_this,
                                     int32_t                 press)
{
    int32_t var1 = 0;
    int32_t var2 = 0;
    int32_t  t_fine = 0;

    /* У׼����ָ�� */
    am_bme280_calibration_data_t *p_cal = &(p_this->cal_val);
    
    t_fine = p_cal->t_fine; 
  
    /* ת����ʵ����ѹֵ */             
    var1 = ((double)t_fine / 2.0) - 64000.0; 
    var2 = var1 * var1 * ((double)p_cal->dig_p6) / 32768.0;
    var2 = var2 + var1 * ((double)p_cal->dig_p5) * 2.0;
    var2 = (var2 / 4.0) + (((double)p_cal->dig_p4) * 65536.0);
    var1 = (((double)p_cal->dig_p3) * var1 * var1 / 524288.0
         + ((double)p_cal->dig_p2) * var1) / 524288.0;
    var1 = (1.0 + var1 / 32768.0) * ((double)p_cal->dig_p1);
    press = 1048576.0 - (double)press;
    press = (press - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = ((double)p_cal->dig_p9) * press * press / 2147483648.0;
    var2 = press * ((double)p_cal->dig_p8) / 32768.0;
    press = press + (var1 + var2 + ((double)p_cal->dig_p7)) / 16.0;
    
    return  press;             
}

/** \brief ����ʪ�� */
am_local int32_t __bme280_hum_cal (am_sensor_bme280_dev_t *p_this,
                                   int32_t                 hum)
{
    int32_t var1    = 0;
    int32_t var2    = 0;
    int32_t t_fine  = 0;

    /* У׼����ָ�� */
    am_bme280_calibration_data_t *p_cal = &(p_this->cal_val);
    
    t_fine = p_cal->t_fine;
    
    /* ת����ʪ��ֵ */
    var1 = (t_fine - (int32_t)(76800));
    var1 = (((((hum << 14) - (((int32_t)p_cal->dig_h4) << 20)
         - (((int32_t)p_cal->dig_h5) * var1)) + ((int32_t)16384)) >> 15)
         * (((((((var1 * ((int32_t)p_cal->dig_h6)) >> 10) 
         * (((var1 * ((int32_t)p_cal->dig_h3)) >> 11) 
         + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) 
         * ((int32_t)p_cal->dig_h2) + 8192) >> 14));
    
    var1 = (var1 - (((((var1 >> 15) * (var1 >> 15)) >> 7) 
         * ((int32_t)p_cal->dig_h1)) >> 4)); 
    var2 = (uint32_t)(var1 >> 12);
    
    hum  = (uint64_t)(var2) * 1000000 / 1024;
    return  hum;    
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (id == AM_BME280_CHAN_1) {
        return AM_SENSOR_TYPE_PRESS;
    } else if (id == AM_BME280_CHAN_2) {
        return AM_SENSOR_TYPE_TEMPERATURE;
    } else if (id == AM_BME280_CHAN_3) {
        return AM_SENSOR_TYPE_HUMIDITY;
    } else {
        return -AM_ENODEV;
    }
}

/** \brief ��ȡ������ͨ���������� */
am_local am_err_t __pfn_data_get (void            *p_drv,
                                  const int       *p_ids,
                                  int              num,
                                  am_sensor_val_t *p_buf)
{
    am_sensor_bme280_dev_t* p_this = (am_sensor_bme280_dev_t*)p_drv;

    am_bme280_calibration_data_t *p_cal = &p_this->cal_val;

    am_err_t ret        = AM_OK;
    uint8_t status_val  = 0;
    uint8_t reg_data[3] = {0};
    int32_t tem_data    = 0;

    int cur_id = 0;
    int i = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (AM_BIT_GET(p_this->trigger, 7) != 1) {
        return -AM_EPERM;
    }

    for (i = 0; i < num; i++) {
        p_buf[i].unit = AM_SENSOR_UNIT_INVALID;
    }

    /** \brief ��ȡ�ɶ�״ֵ̬ */
    do {
        ret = __bme280_read(p_this, __BME280_REG_STATUS, &status_val, 1);
        if (ret != AM_OK) {
            return ret;
        }
    } while (__BME280_GET_DATA_STATUS(status_val) != 0x1);

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {
            
            /** \brief ��ȡ�¶ȼĴ���ֵ */
            ret = __bme280_read(p_this, __BME280_REG_T_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BME280_UINT8_TO_UINT32(reg_data);
           
            /** \brief �����¶�ֵ������ѹУ׼���� */
            p_cal->t_fine = __BME280_GET_T_DEFINE(tem_data,
                                                  p_cal->dig_t1,
                                                  p_cal->dig_t2,
                                                  p_cal->dig_t3);
            /** \brief ��ȡѹ��ֵ */
            ret = __bme280_read(p_this, __BME280_REG_P_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BME280_UINT8_TO_UINT32(reg_data);

            /** \brief ѹ�� */
            p_buf[i].val = __bme280_press_cal(p_this, tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_BASE; /*< \brief ��λĬ��Ϊ0:10^(0)*/

        } else if (cur_id == 1) {

            /** \brief ��ȡ�¶� */
            ret = __bme280_read(p_this, __BME280_REG_T_MSB, reg_data, 3);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = __BME280_UINT8_TO_UINT32(reg_data);
           
            /** \brief �¶� */
            p_buf[i].val = __BME280_GET_TEM_VALUE(tem_data,
                                                  p_cal->dig_t1,
                                                  p_cal->dig_t2,
                                                  p_cal->dig_t3); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        } else if (cur_id == 2) {

            /** \brief ��ȡʪ�� */
            ret = __bme280_read(p_this, __BME280_REG_H_MSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            tem_data = (uint16_t)(reg_data[0] << 8 | reg_data[1]);
           
            
            p_buf[i].val = __bme280_hum_cal(p_this, tem_data); 
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/

        } else {
            return -AM_ENODEV;  /*< \brief ���˴�ͨ�������ڸô�������ֱ�ӷ��� */
        }
    }
    
    return ret;
}

/** \brief ʹ�ܴ�����ͨ�� */
am_local am_err_t __pfn_enable (void            *p_drv,
                                const int       *p_ids,
                                int              num,
                                am_sensor_val_t *p_result)
{
    am_sensor_bme280_dev_t* p_this = (am_sensor_bme280_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    uint8_t ctrl_meas = 0;
    uint8_t ctrl_hum  = 0;
    
    am_err_t ret = -AM_ENODEV;
    am_err_t cur_ret = AM_OK;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            AM_BIT_SET(p_this->trigger, 6);           
            ret = AM_OK;

        } else if (cur_id == 1) {
 
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            AM_BIT_SET(p_this->trigger, 5);           
            ret = AM_OK;

        } else if (cur_id == 2) {
 
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            AM_BIT_SET(p_this->trigger, 4);           
            ret = AM_OK;

        } else {
            if (p_result != NULL) {
                p_result[i].val = -AM_ENODEV;
            }
            cur_ret = -AM_ENODEV;
        }
    }

    if (ret != AM_OK) {    /**< \breif �������û�иô�������ͨ�����룬���˳� */
        return cur_ret;
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 1)
            || (AM_BIT_GET(p_this->trigger, 5) == 1)
            || (AM_BIT_GET(p_this->trigger, 4) == 1)) {  
        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief ���빤��ģʽ */
        ctrl_meas |= __BME280_NORMAL;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    }  

    if (AM_BIT_GET(p_this->trigger, 4) == 1) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
        
        /** \brief ʹ�ܸ�ͨ�� */
        ctrl_hum |= __BME280_HUM_START;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }    
    }

    if (AM_BIT_GET(p_this->trigger, 5) == 1) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief ʹ�ܸ�ͨ�� */
        ctrl_meas |= __BME280_TEMP_START;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    } 
    
    if (AM_BIT_GET(p_this->trigger, 6) == 1) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /** \brief ʹ�ܸ�ͨ�� */
        ctrl_meas |= __BME280_PRESS_START;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
    } 

    if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
    }

    return cur_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_bme280_dev_t* p_this = (am_sensor_bme280_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t ctrl_meas = 0;
    uint8_t ctrl_hum  = 0;
    
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {

            AM_BIT_CLR(p_this->trigger, 6);
            ret = AM_OK;

        } else if (cur_id == 1) {

            AM_BIT_CLR(p_this->trigger, 5);
            ret = AM_OK;

        } else if (cur_id == 2) {

            AM_BIT_CLR(p_this->trigger, 4);
            ret = AM_OK;

        } else {
            ret = -AM_ENODEV;
        }

        if (p_result != NULL) {
            p_result[i].val = ret;
        }
    }

    if ((AM_BIT_GET(p_this->trigger, 6) == 0)
            && (AM_BIT_GET(p_this->trigger, 5) == 0)
            && (AM_BIT_GET(p_this->trigger, 4) == 0)) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
        
        /** \brief �رո�ͨ�� */
        ctrl_hum &= __BME280_HUM_CLOSE;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        } 

        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief ����˯��ģʽ���ر�ͨ�� */
        ctrl_meas &= __BME280_SLEEP & __BME280_PRESS_CLOSE & __BME280_TEMP_CLOSE;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 7);
        }
    }
            
    if (AM_BIT_GET(p_this->trigger, 6) == 0) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief �رո�ͨ�� */
        ctrl_meas &= __BME280_PRESS_CLOSE;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }
    }

    if (AM_BIT_GET(p_this->trigger, 5) == 0) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        /** \brief �رո�ͨ�� */
        ctrl_meas &= __BME280_TEMP_CLOSE;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_MEAS, &ctrl_meas, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }
    }  

    if (AM_BIT_GET(p_this->trigger, 4) == 0) {

        ret = __bme280_read(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
        
        /** \brief �رո�ͨ�� */
        ctrl_hum &= __BME280_HUM_CLOSE;
        ret = __bme280_write(p_this, __BME280_REG_CTRL_HUM, &ctrl_hum, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }
    }  
    
    return cur_ret;
}

/** \brief ���ô�����ͨ������ */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val)
{
    return -AM_ENOTSUP;
}

/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val)
{
    return -AM_ENOTSUP;
}

/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg)
{
    return -AM_ENOTSUP;
}

/** \brief �򿪴��� */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id)
{
    return -AM_ENOTSUP;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    return -AM_ENOTSUP;
}
/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ BME280 ��ʼ��
 */
am_sensor_handle_t am_sensor_bme280_init (
        am_sensor_bme280_dev_t           *p_dev,
        const am_sensor_bme280_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;
    
    uint8_t reset     = __BME280_CMD_RESET;
    uint8_t bme280_id = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->bme280_dev.p_drv   = p_dev;
    p_dev->bme280_dev.p_funcs = &__g_sensor_bme280_funcs;
    p_dev->dev_info           = p_devinfo;

    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val        = 0;
    p_dev->data[1].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[2].val        = 0;
    p_dev->data[2].unit       = AM_SENSOR_UNIT_INVALID;    

    /* ��λBME280 */
    ret = __bme280_write(p_dev, __BME280_REG_RESET, &reset, 1); 
    if (ret != AM_OK) {
        cur_ret = ret;
    }
    /* �ȴ���λ��� */
    am_mdelay(50);
    
    /* ��ȡID */
    ret = __bme280_read(p_dev, __BME280_REG_ID, &bme280_id, 1);
    if (ret != AM_OK || bme280_id != __BME280_MY_ID) {
        cur_ret = ret;
    } else {

        /* ��ȡѹ��У׼ֵ */
        ret = __bme280_get_press_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        /* ��ȡ�¶�У׼ֵ */
        ret = __bme280_get_tem_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
        
        /* ��ȡʪ��У׼ֵ */
        ret = __bme280_get_hum_cal(p_dev);
        if (ret != AM_OK) {
            cur_ret = ret;
        } 
    }
    
    if (cur_ret != AM_OK) {
        am_kprintf("\r\nSensor bme280 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->bme280_dev);
}

/**
 * \brief ������ BME280 ȥ��ʼ��
 */
am_err_t am_sensor_bme280_deinit (am_sensor_handle_t handle)
{
    am_sensor_bme280_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->bme280_dev.p_drv   = NULL;
    p_dev->bme280_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}



/* end of file */
