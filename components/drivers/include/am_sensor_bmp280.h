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
 * \brief ѹ���¶ȴ����� BMP280 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 18-11-28  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_BMP280_H
#define __AM_SENSOR_BMP280_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/*
 * \brief ������BMP280�ṩ������ͨ��ID����
 */
#define AM_BMP280_CHAN_1      0             /* BMP280 ��ͨ��1��ѹ��������ͨ�� */
#define AM_BMP280_CHAN_2      1             /* BMP280 ��ͨ��2���¶ȴ�����ͨ�� */

/**
 * \brief ������ BMP280 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_bmp280_devinfo {

    /**
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַΪ 0x76 �� 0x77
     */
    uint8_t i2c_addr;

} am_sensor_bmp280_devinfo_t;

/**
 * \brief BMP280 ʪ�Ⱥ��¶�У׼ֵ����
 */
typedef struct am_bmp280_calibration_data {
	uint16_t  dig_t1;
	int16_t   dig_t2;
	int16_t   dig_t3;
	uint16_t  dig_p1;
	int16_t   dig_p2;
	int16_t   dig_p3;
	int16_t   dig_p4;
	int16_t   dig_p5;
	int16_t   dig_p6;
	int16_t   dig_p7;
	int16_t   dig_p8;
	int16_t   dig_p9;
	int32_t   t_fine;
} am_bmp280_calibration_data_t;

/**
 * \breif ������ BMP280 �豸�ṹ�嶨��
 */
typedef struct am_sensor_bmp280_dev {
    am_sensor_serv_t                  bmp280_dev; /*< \breif ��������׼���� */
    am_i2c_device_t                   i2c_dev;    /*< \brief i2c�豸ʵ�� */
    am_bmp280_calibration_data_t      cal_val;    /*< \brief ����У׼ֵ */
    uint8_t                           trigger;    /*< \brief ��¼��־λ */
    am_sensor_val_t                   data[2];    /*< \brief �ڲ����ݻ��� */

    /** \brief �豸��Ϣ */
    const am_sensor_bmp280_devinfo_t *dev_info;

} am_sensor_bmp280_dev_t;

/**
 * \brief ������ BMP280 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���BMP280�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���BMP280�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_bmp280_init (
        am_sensor_bmp280_dev_t           *p_dev,
        const am_sensor_bmp280_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ BMP280 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_bmp280_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_bmp280_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_BMP280_H */

/* end of file */
