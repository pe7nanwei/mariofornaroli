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
 * \brief ѹ���¶ȴ����� LPS22HB ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 18-12-03  yrz, first implementation.
 * \endinternal
 */

#ifndef __AM_SENSOR_LPS22HB_H
#define __AM_SENSOR_LPS22HB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"

/**
 * \brief ������LPS22HB�ṩ������ͨ��ID����
 */
#define AM_LPS22HB_CHAN_1      0           /* LPS22HB ��ͨ��1��ѹ��������ͨ�� */
#define AM_LPS22HB_CHAN_2      1           /* LPS22HB ��ͨ��2���¶ȴ�����ͨ�� */

/**
 * \brief ������ LPS22HB �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_lps22hb_devinfo {
    
    /**
     * \brief ����׼��������������
     */
    int     trigger_pin;
    
    /**
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַΪ 0x5C �� 0x5D
     */
    uint8_t i2c_addr;

} am_sensor_lps22hb_devinfo_t;

/**
 * \breif ������ LPS22HB �豸�ṹ�嶨��
 */
typedef struct am_sensor_lps22hb_dev {
    am_sensor_serv_t               lps22hb_dev;  /**< \breif ��������׼����   */
    am_i2c_device_t                i2c_dev;      /**< \brief i2c�豸ʵ��      */
    void                          *p_arg[2];     /**< \brief �����ص��������� */
    uint8_t                        flags[2];     /**< \brief ������־λ       */
    am_isr_defer_job_t             g_myjob;      /**< \brief �ж���ʱ�������� */
    am_sensor_val_t                sam_rate;     /**< \brief ����Ƶ��         */    
    uint8_t                        trigger;      /**< \brief ��¼��־λ       */
    am_sensor_val_t                data[2];      /**< \brief �ڲ����ݻ���     */
    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t         pfn_trigger_cb[2];
    
    /** \brief �豸��Ϣ */
    const am_sensor_lps22hb_devinfo_t *dev_info;

} am_sensor_lps22hb_dev_t;

/**
 * \brief ������ LPS22HB ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���LPS22HB�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���LPS22HB�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_lps22hb_init (
        am_sensor_lps22hb_dev_t           *p_dev,
        const am_sensor_lps22hb_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ LPS22HB ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_lps22hb_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_lps22hb_deinit (am_sensor_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_LPS22HB_H */

/* end of file */
