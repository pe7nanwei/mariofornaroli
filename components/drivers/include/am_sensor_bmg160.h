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
 * \brief ���������Ǵ����� BMG160 ͷ�ļ�
 *
 * \internal
 * \par modification history
 * - 1.00 18-12-11  wk, first implementation.
 * \endinternal
 */
 
#ifndef __AM_SENSOR_BMG160_H
#define __AM_SENSOR_BMG160_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_i2c.h"
#include "am_sensor.h"
#include "am_isr_defer.h"
    
/*
 * \brief ������BMG160�ṩ������ͨ��ID����
 */
#define AM_BMG160_CHAN_1      0             /* BMG160 ��ͨ��1��X��ͨ�� */
#define AM_BMG160_CHAN_2      1             /* BMG160 ��ͨ��2��Y��ͨ�� */
#define AM_BMG160_CHAN_3      2             /* BMG160 ��ͨ��3��Z��ͨ�� */    

/**
 * \brief ������ BMG160 �豸��Ϣ�ṹ��
 */
typedef struct am_sensor_bmg160_devinfo {

    /**
     * \brief ����׼��������������
     */
    int     trigger_pin;

    /*
     * \brief I2C 7λ �豸��ַ
     *
     * ���豸7λ��ַ�̶�Ϊ 0x68
     */
    uint8_t i2c_addr;

} am_sensor_bmg160_devinfo_t;

/****************************** У׼ֵ������************************************/

/**
 * \breif ������ BMG160 �豸�ṹ�嶨��
 */
typedef struct am_sensor_bmg160_dev {
    
    am_sensor_serv_t               bmg160_dev;   /**< \breif ��������׼����   */
    am_i2c_device_t                i2c_dev;      /**< \brief i2c�豸ʵ��      */
    void                          *p_arg[3];     /**< \brief �����ص��������� */
    uint8_t                        flags[3];     /**< \brief ������־λ       */
    am_isr_defer_job_t             g_myjob;      /**< \brief �ж���ʱ�������� */
    am_sensor_val_t                sam_rate;     /**< \brief ����Ƶ��         */    
    uint8_t                        trigger;      /**< \brief ��¼��־λ       */
    am_sensor_val_t                data[3];      /**< \brief �ڲ����ݻ���     */
    /** \brief ����׼�����������ص����� */
    am_sensor_trigger_cb_t            pfn_trigger_cb[3];

    /** \brief �豸��Ϣ */
    const am_sensor_bmg160_devinfo_t *dev_info;

} am_sensor_bmg160_dev_t;

/**
 * \brief ������ BMG160 ��ʼ��
 *
 * \param[in] p_dev     : ָ�򴫸���BMG160�豸��ָ��
 * \param[in] p_devinfo : ָ�򴫸���BMG160�豸��Ϣ��ָ��
 * \param[in] handle    : IIC��׼������
 *
 * \return ��������׼�������������Ϊ NULL��������ʼ��ʧ��
 */
am_sensor_handle_t am_sensor_bmg160_init (
        am_sensor_bmg160_dev_t           *p_dev,
        const am_sensor_bmg160_devinfo_t *p_devinfo,
        am_i2c_handle_t                   handle);

/**
 * \brief ������ BMG160 ȥ��ʼ��
 *
 * \param[in] handle : am_sensor_bmg160_init()��ʼ��������õĴ�������׼������
 *
 * \return ��
 */
am_err_t am_sensor_bmg160_deinit (am_sensor_handle_t handle);
    
#ifdef __cplusplus
}
#endif

#endif /* __AM_SENSOR_BMG160_H */

/* end of file */
