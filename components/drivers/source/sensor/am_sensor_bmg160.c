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
 * \brief ������ BMG160 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-11  wk, first implementation.
 * \endinternal
 */
 
#include "am_sensor_bmg160.h"
#include "am_gpio.h"
#include "am_vdebug.h"

/*******************************************************************************
 * �궨��
 ******************************************************************************/
#define __BMG160_CHIP_ID        (0x00)  /**< \brief �豸ID��ַ */
#define __BMG160_MY_ID          (0x0F)  /**< \brief �豸ID */
#define __BMG160_RATE_X_LSB     (0x02)  /**< \brief ����Xͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_RATE_X_MSB     (0x03)  /**< \brief ����Xͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_RATE_Y_LSB     (0x04)  /**< \brief ����Yͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_RATE_Y_MSB     (0x05)  /**< \brief ����Yͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_RATE_Z_LSB     (0x06)  /**< \brief ����Zͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_RATE_Z_MSB     (0x07)  /**< \brief ����Zͨ�������ʶ���ֵ�������Чλ */
#define __BMG160_TEMP           (0x08)  /**< \brief ������ǰоƬ�¶� */
#define __BMG160_INT_STATUS_0   (0x09)  /**< \brief �����ж�״̬λ */
#define __BMG160_INT_STATUS_1   (0x0A)  /**< \brief �����ж�״̬λ */
#define __BMG160_INT_STATUS_2   (0x0B)  /**< \brief �����κ��˶��ж�״̬λ */
#define __BMG160_INT_STATUS_3   (0x0C)  /**< \brief �����������ж�״̬λ */

#define __BMG160_FIFO_STATUS    (0x0E)  /**< \brief ����FIFO״̬��־ */
#define __BMG160_RANGE          (0x0F)  /**< \brief ����BMG160֧��5�ֲ�ͬ�Ľ����ʲ�����Χ */
#define __BMG160_BW             (0x10)  /**< \brief �üĴ�������ѡ�����������˲������� */
#define __BMG160_LPM1           (0x11)  /**< \brief ѡ������Դģʽ */
#define __BMG160_LPM2           (0x12)  /**< \brief �����ϵ���ⲿ�������������� */
#define __BMG160_RATE_HBW       (0x13)  /**< \brief ���������ݲɼ������������ʽ */
#define __BMG160_BGW_SOFTRESET  (0x14)	/**< \brief �����û������Ĵ�������λ */ 
#define __BMG160_INT_EN_0       (0x15)  /**< \brief ����������Щ�ж� */
#define __BMG160_INT_EN_1       (0x16)  /**< \brief �����ж��������� */
#define __BMG160_INT_MAP_0      (0x17)  /**< \brief ������Щ�ж��ź�ӳ�䵽INT1���� */
#define __BMG160_INT_MAP_1      (0x18)  /**< \brief ������Щ�ж��ź�ӳ�䵽INT1���ź�INT2���� */
#define __BMG160_INT_MAP_2      (0x19)  /**< \brief ������Щ�ж��ź�ӳ�䵽INT2���� */
#define __BMG160_INTR_ZERO_ADDR (0x1A)  /**< \brief ���ƾ��п�ѡ����Դ����Щ�жϵ�����Դ����  */
#define __BMG160_INTR_ONE_ADDR  (0x1B)  /**< \brief ���ƿ���ƫ�Ʋ���������Դ������κ��˶���ֵ  */
#define __BMG160_INTR_TWO_ADDR  (0x1C)  /**< \brief  */
#define __BMG160_INTR_4_ADDR    (0x1E)  /**< \brief  */

#define __BMG160_INT_RST_LATCH  (0x21)  /**< \brief �����жϸ�λλ���ж�ģʽѡ�� */
#define __BMG160_High_Th_x      (0x22)  /**< \brief ����x��ĸ�������ֵ�͸������ͺ����� */
#define __BMG160_High_Dur_x     (0x23)  /**< \brief ����x��ĸ����ʳ���ʱ������ */
#define __BMG160_High_Th_y      (0x24)  /**< \brief ����y��ĸ�������ֵ�͸������ͺ����� */
#define __BMG160_High_Dur_y     (0x25)  /**< \brief ����y��ĸ����ʳ���ʱ������ */
#define __BMG160_High_Th_z      (0x26)  /**< \brief ����z��ĸ�������ֵ�͸������ͺ����� */
#define __BMG160_High_Dur_z     (0x27)  /**< \brief ����z��ĸ����ʳ���ʱ������ */
                              
#define __BMG160_SoC            (0x31)  /**< \brief ��������ƫ��ȡ������ */
#define __BMG160_A_FOC          (0x32)  /**< \brief ��������ƫ��ȡ������ */
#define __BMG160_TRIM_NVM_CTRL  (0x33)  /**< \brief �������οɱ�̷���ʧ�Դ洢����NVM���Ŀ������� */
#define __BMG160_BGW_SPI3_WDT   (0x34)  /**< \brief �������ֽӿڵ����� */
                              
#define __BMG160_OFC1           (0x36)  /**< \brief ����ƫ�Ʋ���ֵ */
#define __BMG160_OFC2           (0x37)  /**< \brief ����Xͨ����ƫ�Ʋ���ֵ */
#define __BMG160_OFC3           (0x38)  /**< \brief ����Yͨ����ƫ�Ʋ���ֵ */
#define __BMG160_OFC4           (0x39)  /**< \brief ����Zͨ����ƫ�Ʋ���ֵ */
#define __BMG160_TRIM_GP0       (0x3A)  /**< \brief ��������NVM���ݵ�ͨ�����ݼĴ��� */
#define __BMG160_TRIM_GP1       (0x3B)  /**< \brief ��������NVM���ݵ�ͨ�����ݼĴ��� */
#define __BMG160_BIST           (0x3C)  /**< \brief ���������Բ⣨BIST������ */
#define __BMG160_FIFO_CONFIG_0  (0x3D)  /**< \brief ����FIFOwatermark���� */
#define __BMG160_FIFO_CONFIG_1  (0x3E)  /**< \brief ����FIFO�������� */
#define __BMG160_FIFO_DATA      (0x3F)  /**< \brief FIFO���ݶ����Ĵ��� */

/** \brief ������int8ת��Ϊһ��int16_t���� */
#define __BMG160_UINT8_TO_UINT16(buff) \
                       (int16_t)(((uint16_t)(buff[1]) << 8) \
                               | ((uint16_t)(buff[0])))
                                                          
/** \brief X����ٶȲ��� */ 
#define __BMG160_X_START       (0x2<<0)  
/** \brief Y����ٶȲ��� */ 
#define __BMG160_Y_START       (0x2<<2)                   
/** \brief Z����ٶȲ��� */ 
#define __BMG160_Z_START       (0x2<<5)                                  
                               
 
#define BMG160_ODR_100 (100)
#define BMG160_ODR_200 (200)
#define BMG160_ODR_400 (400)
#define BMG160_ODR_1000 (1000)
#define BMG160_ODR_2000 (2000)

#define BMG160_ODR_100_REG (0x07)
#define BMG160_ODR_200_REG (0x06)
#define BMG160_ODR_400_REG (0x03)
#define BMG160_ODR_1000_REG (0x02)
#define BMG160_ODR_2000_REG (0x01)



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
am_local am_const struct am_sensor_drv_funcs __g_sensor_bmg160_funcs = {
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
 * \brief BMG160 д����
 */
am_local am_err_t __bmg160_write (am_sensor_bmg160_dev_t *p_this,
                                  uint32_t                subaddr,
                                  uint8_t                *p_buf,
                                  uint32_t                nbytes)
{
    return am_i2c_write(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/**
 * \brief BMG160 ������
 */
am_local am_err_t __bmg160_read (am_sensor_bmg160_dev_t *p_this,
                                 uint32_t                subaddr,
                                 uint8_t                *p_buf,
                                 uint32_t                nbytes)
{
    return am_i2c_read(&p_this->i2c_dev, subaddr, p_buf, nbytes);
}

/** \breif �жϻص����� */
am_local void __bmg160_alarm_callback (void *p_arg)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_arg;

    am_isr_defer_job_add(&p_this->g_myjob);   /*< \brief ����ж��ӳٴ������� */
}

/** \breif �ж��ӳٺ��� */
am_local void __am_pfnvoid_t (void *p_arg)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_arg;

    uint8_t current_data[6] = {0};
    int16_t x_axis_data   = 0;
    int16_t y_axis_data   = 0;
    int16_t z_axis_data   = 0;

    /** \brief ��ȡX��Y��Z����ٶ�ֵ */
    __bmg160_read(p_this, __BMG160_RATE_X_LSB, current_data, 6);

    /* ��ȡX����ٶ� */
    x_axis_data = __BMG160_UINT8_TO_UINT16(current_data);
    p_this->data[0].val = x_axis_data;
    p_this->data[0].unit = AM_SENSOR_UNIT_MICRO;

    /* ��ȡY����ٶ� */
    y_axis_data = __BMG160_UINT8_TO_UINT16((current_data+2));
    p_this->data[1].val = y_axis_data;
    p_this->data[1].unit = AM_SENSOR_UNIT_MICRO;

    /* ��ȡZ����ٶ� */
    z_axis_data = __BMG160_UINT8_TO_UINT16((current_data+4));
    p_this->data[2].val = z_axis_data;
    p_this->data[2].unit = AM_SENSOR_UNIT_MICRO;

    if (p_this->pfn_trigger_cb[0] &&
            (p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY)) {
        p_this->pfn_trigger_cb[0](p_this->p_arg[0],
                                  AM_SENSOR_TRIGGER_DATA_READY);
    }

    if (p_this->pfn_trigger_cb[1] &&
            (p_this->flags[1] & AM_SENSOR_TRIGGER_DATA_READY)) {
        p_this->pfn_trigger_cb[1](p_this->p_arg[1],
                                  AM_SENSOR_TRIGGER_DATA_READY);
    }
     
    if (p_this->pfn_trigger_cb[2] &&
            (p_this->flags[2] & AM_SENSOR_TRIGGER_DATA_READY)) {
        p_this->pfn_trigger_cb[2](p_this->p_arg[2],
                                  AM_SENSOR_TRIGGER_DATA_READY);
    }
}

/*
 * \brief ����ѡ��
 */
am_local am_err_t  __reg_attr_set (am_sensor_bmg160_dev_t *p_this, uint8_t rate)
{
   
     am_err_t ret = AM_OK;

     uint8_t rate_cfg = 0;

     ret = __bmg160_read(p_this, __BMG160_BW, &rate_cfg, 1);
     if (ret != AM_OK) {
         return ret;
     }

     switch (rate) {
     case 0:
         rate_cfg |= BMG160_ODR_100_REG;
         break;
     case 1:
         rate_cfg |= BMG160_ODR_200_REG;
         break;
     case 2:
         rate_cfg |= BMG160_ODR_400_REG;
         break;
     case 3:
         rate_cfg |= BMG160_ODR_1000_REG;
         break;
     case 4:
         rate_cfg |= BMG160_ODR_2000_REG;
         break;
     default:
         break;
     }

     return __bmg160_write(p_this, __BMG160_BW, &rate_cfg, 1);
}

/** \brief ��ȡ�ô�����ĳһͨ�������� */
am_local am_err_t __pfn_type_get (void *p_drv, int id)
{
    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if ((id == AM_BMG160_CHAN_1)
     || (id == AM_BMG160_CHAN_2)
     || (id == AM_BMG160_CHAN_3)) {
        return AM_SENSOR_TYPE_GYROSCOPE;
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
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;
    
    am_err_t ret        = AM_OK;

    uint8_t reg_data[6] = {0};
    int16_t x_axis_data = 0;
    int16_t y_axis_data = 0;
    int16_t z_axis_data = 0;
    
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
     /* ��Ϊ1�������������׼�����������ص�������ʹ�� */
    if (num == 1) {
        cur_id = p_ids[0];
        /* ��������׼������������ʽ����ֱ�Ӹ�ֵ */
        if ((AM_BIT_GET(p_this->trigger, 2)) &&
                ((p_this->flags[0] & AM_SENSOR_TRIGGER_DATA_READY) ||
                 (p_this->flags[1] & AM_SENSOR_TRIGGER_DATA_READY))) {
            p_buf[0].val = p_this->data[cur_id].val;
            p_buf[0].unit= p_this->data[cur_id].unit;
            return AM_OK;
        }
    }
    /** \brief ��ȡ�ɶ�״ֵ̬(�޴˲���) */

    for (i = 0; i < num; i++) {

        cur_id = p_ids[i];

        if (cur_id == 0) {
            
            /** \brief ��ȡX����ٶ����� */
            ret = __bmg160_read(p_this, __BMG160_RATE_X_LSB, reg_data, 2);
            if (ret != AM_OK) {
                return ret;
            }
            x_axis_data = __BMG160_UINT8_TO_UINT16(reg_data);
            p_buf[i].val  = x_axis_data ;         /*< \brief X����ٶ����� */
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
        } else if (cur_id == 1) {
            /** \brief ��ȡY����ٶ����� */
            ret = __bmg160_read(p_this, __BMG160_RATE_Y_LSB, reg_data+2, 2);
            if (ret != AM_OK) {
                return ret;
            }
            y_axis_data = __BMG160_UINT8_TO_UINT16((reg_data+2));
            p_buf[i].val  = y_axis_data ;         /*< \brief Y����ٶ����� */
            p_buf[i].unit = AM_SENSOR_UNIT_MICRO; /*< \brief ��λĬ��Ϊ-6:10^(-6)*/
        } else if (cur_id == 2) {
            /** \brief ��ȡZ����ٶ����� */
            ret = __bmg160_read(p_this, __BMG160_RATE_Z_LSB, reg_data+4, 2);
            if (ret != AM_OK) {
                return ret;
            }
            z_axis_data = __BMG160_UINT8_TO_UINT16((reg_data+4));
            p_buf[i].val  = z_axis_data ;         /*< \brief Z����ٶ����� */
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
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    
   uint8_t int_en_1 = 0;
    
    am_err_t ret = -AM_ENODEV;
    am_err_t curent_ret = AM_OK;
    
        if (p_drv == NULL) {
        return -AM_EINVAL;
    }
    
    
    for (i = 0; i < num; i++) {
        cur_id = p_ids[i];
        if (cur_id == 0 || cur_id == 1 || cur_id == 2) {
            if (p_result != NULL) {
                p_result[i].val = AM_OK;
            }
            ret = AM_OK;
        } else {
            if (p_result != NULL) {
                p_result[i].val = -AM_ENODEV;
            }
            curent_ret = -AM_ENODEV;
        }
    }
    if (ret != AM_OK) {    /**< \breif �������û�иô�������ͨ�����룬���˳� */
        return curent_ret;
    }
        if (ret == AM_OK) {
        AM_BIT_SET(p_this->trigger, 7);
        AM_BIT_SET(p_this->trigger, 6);
        AM_BIT_SET(p_this->trigger, 5);
        AM_BIT_SET(p_this->trigger, 4);
    }
        
    ret = __bmg160_read(p_this, __BMG160_INT_EN_1, &int_en_1, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }

    int_en_1 |= 0x0F;
    ret = __bmg160_write(p_this, __BMG160_INT_EN_1, &int_en_1, 1);
    if (ret != AM_OK) {
        curent_ret = ret;
    }
 
     return curent_ret;
}

/** \brief ���ܴ�����ͨ�� */
am_local am_err_t __pfn_disable (void            *p_drv,
                                 const int       *p_ids,
                                 int              num,
                                 am_sensor_val_t *p_result)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    int i = 0;
    int cur_id = 0;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

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

//        ret = __bmg160_read(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg, 1);
//        if (ret != AM_OK){
//            cur_ret = ret;
//        }

//        /** \brief �رո�ͨ�� */
//        ctrl_reg &= __HTS221_CLOSE;
//        ret = __bmg160_write(p_this, __HTS221_REG_CTRL_REG1, &ctrl_reg, 1);
        if (ret != AM_OK){
            cur_ret = ret;
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 7);
        }
    }

    return cur_ret;
}
 
/** \brief ���ô�����ͨ�����ԣ�attributes�� */
am_local am_err_t __pfn_attr_set (void                  *p_drv,
                                  int                    id,
                                  int                    attr,
                                  const am_sensor_val_t *p_val)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    am_sensor_val_t sensor_val = {0, 0};

    am_sensor_val_t __sampling_rate = {0, 0};

    uint16_t rate = 0;

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }
    
    if ((id != AM_BMG160_CHAN_1)
     && (id != AM_BMG160_CHAN_2)
     && (id != AM_BMG160_CHAN_3)) {
        return -AM_ENODEV;
    }

    switch (attr) {
      /* �޸�Ƶ�� */
      case AM_SENSOR_ATTR_SAMPLING_RATE:

        if (sensor_val.val < 0 || sensor_val.val > 2000) {
            return -AM_ENOTSUP;
        }

        sensor_val.unit = p_val->unit;
        sensor_val.val  = p_val->val;
        am_sensor_val_unit_convert(&sensor_val, 1, AM_SENSOR_UNIT_BASE);

        if (sensor_val.val == 100) {
            rate = 100;
            __sampling_rate.val = 100;
        } else if (sensor_val.val > 100 && sensor_val.val < 400) {
            rate = 200;
            __sampling_rate.val = 200;
        } else if (sensor_val.val > 200 && sensor_val.val < 1000) {
            rate = 400;
            __sampling_rate.val = 400;
        } else if (sensor_val.val > 400 && sensor_val.val < 2000) {
            rate = 1000;
            __sampling_rate.val = 1000;
        } else if (sensor_val.val > 1000 && sensor_val.val <= 2000) {
            rate = 2000;
            __sampling_rate.val = 2000;
            __sampling_rate.unit = AM_SENSOR_UNIT_BASE;
        }

        ret = __reg_attr_set(p_this, rate);
        if (ret != AM_OK) {
            cur_ret = ret;
        } else {
            p_this->sam_rate.val  = __sampling_rate.val;
            p_this->sam_rate.unit = __sampling_rate.unit;
        }

        break;

    default:
        cur_ret = -AM_ENOTSUP;
        break;
    }

    return cur_ret;    
}
 
/** \brief ��ȡ������ͨ������ */
am_local am_err_t __pfn_attr_get (void            *p_drv,
                                  int              id,
                                  int              attr,
                                  am_sensor_val_t *p_val)
{
   am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    am_err_t ret = AM_OK;

    if ((id != AM_BMG160_CHAN_1)
     && (id != AM_BMG160_CHAN_2)
     && (id != AM_BMG160_CHAN_2)) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (attr) {

    /* ��ȡ����Ƶ�� */
    case AM_SENSOR_ATTR_SAMPLING_RATE:

        p_val->val  = p_this->sam_rate.val;
        p_val->unit = p_this->sam_rate.unit;
        break;

    default:
        ret = -AM_ENOTSUP;
        break;

    }

    return ret;
}


/** \brief ���ô�����һ��ͨ����������һ�������ص����� */
am_local am_err_t __pfn_trigger_cfg (void                   *p_drv,
                                     int                     id,
                                     uint32_t                flags,
                                     am_sensor_trigger_cb_t  pfn_cb,
                                     void                   *p_arg)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    switch (flags) {
    case AM_SENSOR_TRIGGER_DATA_READY:
        break;
    default:
        return -AM_ENOTSUP;
    }

    p_this->pfn_trigger_cb[id] = pfn_cb;
    p_this->p_arg[id]          = p_arg;
    p_this->flags[id]          = flags;

    return AM_OK;
}

/** \brief �򿪴��� */
am_local am_err_t __pfn_trigger_on (void *p_drv, int id)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t reg_data = 0;

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    if (p_this->trigger & 0x4) {
        return AM_OK;
    }

    ret = __bmg160_read(p_this, __BMG160_INT_EN_0, &reg_data, 1);
    if ( ret != AM_OK) {
        cur_ret = ret;
    }

    if (cur_ret == AM_OK && id == 0) {
        AM_BIT_SET(p_this->trigger, 0);
        AM_BIT_SET(p_this->trigger, 2);
    }
    if (cur_ret == AM_OK && id == 1) {
        AM_BIT_SET(p_this->trigger, 1);
        AM_BIT_SET(p_this->trigger, 2);
    }

    return cur_ret;
}

/** \brief �رմ��� */
am_local am_err_t __pfn_trigger_off (void *p_drv, int id)
{
    am_sensor_bmg160_dev_t* p_this = (am_sensor_bmg160_dev_t*)p_drv;

    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t reg_data = 0;

    am_sensor_val_t p_val = {0, 0};

    if (id != 0 && id != 1) {
        return -AM_ENODEV;
    }

    if (p_drv == NULL) {
        return -AM_EINVAL;
    }

    p_this->pfn_trigger_cb[id] = NULL;
    p_this->p_arg[id]          = NULL;
    p_this->flags[id]          = 0;

    AM_BIT_CLR(p_this->trigger, id);

    if ((p_this->trigger & 0x3) == 0) {

        ret = __bmg160_read(p_this, __BMG160_INT_EN_0, &reg_data, 1);
        if (ret != AM_OK) {
            cur_ret = ret;
        }
        ret = __pfn_attr_set(p_drv, id, AM_SENSOR_ATTR_SAMPLING_RATE, &p_val);
        if (ret != AM_OK) {
            cur_ret = ret;
        }

        if ((p_this->dev_info->trigger_pin != -1) && (cur_ret == AM_OK)) {
            ret = am_gpio_trigger_off(p_this->dev_info->trigger_pin);
            if (ret != AM_OK) {
                cur_ret = ret;
            }
        }

        if (cur_ret == AM_OK) {
            AM_BIT_CLR(p_this->trigger, 2);
        }
    }

    return cur_ret;
}

/*******************************************************************************
  Public functions
*******************************************************************************/
/**
 * \brief ������ BMG160 ��ʼ��
 */
am_sensor_handle_t am_sensor_bmg160_init (
        am_sensor_bmg160_dev_t           *p_dev,
        const am_sensor_bmg160_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle)
{
    am_err_t ret = AM_OK;
    am_err_t cur_ret = AM_OK;

    uint8_t bmg160_id = 0;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    am_i2c_mkdev(&p_dev->i2c_dev,
                 handle,
                 p_devinfo->i2c_addr,
                 AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    p_dev->bmg160_dev.p_drv   = p_dev;
    p_dev->bmg160_dev.p_funcs = &__g_sensor_bmg160_funcs;
    p_dev->dev_info           = p_devinfo;
    p_dev->pfn_trigger_cb[0]  = NULL;
    p_dev->pfn_trigger_cb[1]  = NULL;
    p_dev->pfn_trigger_cb[2]  = NULL;
    p_dev->p_arg[0]           = NULL;
    p_dev->p_arg[1]           = NULL;
    p_dev->p_arg[2]           = NULL;
    p_dev->flags[0]           = 0;
    p_dev->flags[1]           = 0;
    p_dev->flags[2]           = 0;
    p_dev->sam_rate.val       = 0;
    p_dev->sam_rate.unit      = 0;
    p_dev->trigger            = 0;
    p_dev->data[0].val        = 0;
    p_dev->data[0].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[1].val        = 0;
    p_dev->data[1].unit       = AM_SENSOR_UNIT_INVALID;
    p_dev->data[2].val        = 0;
    p_dev->data[2].unit       = AM_SENSOR_UNIT_INVALID;

    if (p_devinfo->trigger_pin != -1) {
        am_gpio_trigger_connect(p_devinfo->trigger_pin,
                                __bmg160_alarm_callback,
                                (void*)p_dev);
        am_gpio_trigger_cfg(p_devinfo->trigger_pin, AM_GPIO_TRIGGER_RISE);
    }

    am_isr_defer_job_init(&p_dev->g_myjob, __am_pfnvoid_t, p_dev, 1);

    ret = __bmg160_read(p_dev, __BMG160_CHIP_ID, &bmg160_id, 1);
    if (ret != AM_OK || bmg160_id != __BMG160_MY_ID) {
        cur_ret = ret;
    } else {


    }

    if (cur_ret != AM_OK) {
        am_kprintf("\r\nSensor BMG160 Init is ERROR! \r\n");
        return NULL;
    }

    return &(p_dev->bmg160_dev);
}

/**
 * \brief ������ BMG160 ���ʼ��
 */
am_err_t am_sensor_bmg160_deinit (am_sensor_handle_t handle)
{
    am_sensor_bmg160_dev_t *p_dev = handle->p_drv;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_dev->bmg160_dev.p_drv   = NULL;
    p_dev->bmg160_dev.p_funcs = NULL;
    p_dev->dev_info           = NULL;

    return AM_OK;
}

/* end of file */
