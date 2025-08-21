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
 * \brief ��ʪ�ȴ����� HTS221 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 18-11-26  wan, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_HTS221_H
#define __AM_SENSOR_HTS221_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/*
 * \brief ������HTS221�ṩ������ͨ��ID����
 */
#define AM_HTS221_CHAN_1      0             /* HTS221 ��ͨ��1��ʪ�ȴ�����ͨ�� */
#define AM_HTS221_CHAN_2      1             /* HTS221 ��ͨ��2���¶ȴ�����ͨ�� */

/**
 * \brief ������ HTS221 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_hts221_devinfo {

    /**
     * \brief ����׼��������������
     */
    int     trigger_pin;

    /*
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַ�̶�Ϊ 0x5f
     */
    uint8_t i2c_addr;

} am_sensor_hts221_devinfo_t;

/**
 * \brief HTS221 ʪ�Ⱥ��¶�У׼ֵ����
 */
typedef struct am_hts221_calibration_data {
    int16_t   x0;
    int8_t    y0;
    int16_t   x1;
    int8_t    y1;
} am_hts221_calibration_data_t;

/**
 * \breif ������ HTS221 �豸�ṹ�嶨��
 */
typedef struct am_sensor_hts221_dev {
    am_sensor_serv_t                  hts221_dev; /*< \breif ��������׼���� */
    am_i2c_device_t                   i2c_dev;    /*< \brief i2c�豸ʵ�� */
    am_hts221_calibration_data_t      cal_val[2]; /*< \brief ������ʪ��У׼ֵ */
    void                             *p_arg[2];   /*< \brief �����ص��������� */
    uint8_t                           flags[2];   /*< \brief ������־λ */
    am_isr_defer_job_t                g_myjob;    /*< \brief �ж���ʱ�������� */
    am_sensor_val_t                   sam_rate;   /*< \brief ����Ƶ�� */
    uint8_t                           trigger;    /*< \brief ��¼��־λ */
    am_sensor_val_t                   data[2];    /*< \brief �ڲ����ݻ��� */

    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t            pfn_trigger_cb[2];

    /** \brief �豸��Ϣ */
    const am_sensor_hts221_devinfo_t *dev_info;

} am_sensor_hts221_dev_t;

/**
 * \brief ������ HTS221 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���HTS221�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���HTS221�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_hts221_init (
        am_sensor_hts221_dev_t           *p_dev,
        const am_sensor_hts221_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ HTS221 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_hts221_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_hts221_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_HTS221_H */

/* end of file */
