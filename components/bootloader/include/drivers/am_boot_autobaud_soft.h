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
 * \brief �Զ������ʷ��񣬿���ʵ����δ֪�����ʵĴ����豸�Զ�ƥ�䲨����(���ʵ��)
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  ipk, first implementation
 * \endinternal
 */

#ifndef __AM_AUTO_BAUDRATE_SOFT_H__
#define __AM_AUTO_BAUDRATE_SOFT_H__

#include "am_cap.h"
#include "am_uart.h"
#include "am_timer.h"
#include "am_softimer.h"
#include "am_boot_autobaud.h"
/**
 * \brief �Զ��������豸��Ϣ
 */
typedef struct am_boot_autobaud_soft_devinfo {

    uint8_t  cap_chanel;               /**< \brief CAP����ͨ�� */
    uint8_t  timer_width;              /**< \brief TIMER��ʱ��λ�� */

    uint16_t timer_out;                /**< \brief ����һ�����ݵĳ�ʱʱ�䣬��λms*/
    uint32_t cap_trigger;              /**< \brief CAP������ط�ʽѡ��ѡ�� */

    void     (*pfn_plfm_init)(void);   /**< \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_deinit)(void); /**< \brief ƽ̨���ʼ������ */
} am_boot_autobaud_soft_devinfo_t;

/**
 * \brief �Զ��������豸�ṹ��
 */
typedef struct am_boot_atuobaud_soft_dev {
    /** \brief �Զ������ʻ�ȡ��׼���� */
    am_boot_autobaud_serv_t autobaud_serv;

    /** \brief CAP������*/
    am_cap_handle_t         cap_handle;

    /** \brief softimer�����ʱ���ṹ��*/
    am_softimer_t           softimer;

    /** \brief ��������*/
    int                     cap_pin;

    /** \brief �����жϱ�־*/
    volatile am_bool_t      cap_flag;


    /** \brief ���ڽ�������*/
    uint16_t                uart_data;

    /** \brief �������ݵ�˫���ؼ���*/
    uint32_t                data_edge;

    /** \brief �������ݵ�������*/
    uint32_t                data_pulses;

    /** \brief �������ݳ�ʱʱ�����*/
    uint16_t                time_out_ms;

    /** \brief �������ݵ�������*/
    uint32_t                data_pulse_width[32];

    /** \brief �Զ��������豸��Ϣ*/
    am_boot_autobaud_soft_devinfo_t  *p_devinfo;

} am_boot_autobaud_soft_dev_t;


/**
 * \brief �Զ������ʳ�ʼ������
 *
 * \param[in] p_dev        : ָ���Զ������ʷ����ָ��
 * \param[in] p_devinfo    : ָ���Զ������ʷ�����Ϣ������ָ��
 * \param[in] cap_handle   : CAP�����׼������
 * \param[in] uart_handle  : UART���ڱ�׼������
 *
 * \return �Զ������ʷ���������
 */
am_boot_autobaud_handle_t am_boot_autobaud_soft_init (
    am_boot_autobaud_soft_dev_t     *p_dev,
    am_boot_autobaud_soft_devinfo_t *p_devinfo,
    am_cap_handle_t                  cap_handle,
    int                              cap_pin);

/**
 * \brief �Զ������ʽ��ʼ������
 *
 * \param[in] handle        : �Զ������ʷ�����
 *
 * \return ��
 */
void am_boot_autobaud_soft_deinit (am_boot_autobaud_handle_t handle);


#endif

/* end of file */
