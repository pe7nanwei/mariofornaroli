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
 * \brief  ALARM_CLK ��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-09  vir, first implementation.
 * \endinternal
 */
#ifndef __AM_ALARM_CLK_H
#define __AM_ALARM_CLK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup am_if_alarm_clk
 * \copydoc am_alarm_clk.h
 * @{
 */

/**
 * \name ����ʱ�������ȡֵ
 * \anchor grp_alarm_clk_week
 *
 * \note  ���Ҫ���������������������� ������   �� tm_wday ��ֵΪ ��
 *        AM_ALARM_CLK_WEDNESDAY | AM_ALARM_CLK_SUNDAY
 * @{
 */

#define AM_ALARM_CLK_SUNDAY    0X01    /**< \brief ������ */
#define AM_ALARM_CLK_MONDAY    0X02    /**< \brief ����һ */
#define AM_ALARM_CLK_TUESDAY   0X04    /**< \brief ���ڶ� */
#define AM_ALARM_CLK_WEDNESDAY 0X08    /**< \brief ������ */
#define AM_ALARM_CLK_THURSDAY  0X10    /**< \brief ������ */
#define AM_ALARM_CLK_FRIDAY    0X20    /**< \brief ������ */
#define AM_ALARM_CLK_SATURDAY  0X40    /**< \brief ������ */
#define AM_ALARM_CLK_WORKDAY   0X3E    /**< \brief �����գ�����һ ~ ������ */
#define AM_ALARM_CLK_EVERYDAY  0X7F    /**< \brief ÿһ��  */

 /** @} */

/**
 * \brief ����ʱ��ṹ��
 *
 * \note ʱ����24Сʱ��
 */
typedef struct am_alarm_clk_tm {
    int min;      /**< \brief ��    ֵ��Χ�� [0, 59]  */
    int hour;     /**< \brief Сʱ  ֵ��Χ��[0, 23]  */
    int wdays;    /**< \brief����   ֵ��ο�  \ref grp_alarm_clk_week */
} am_alarm_clk_tm_t;

/**
 * \brief ALARM_CLK ��������
 */
struct am_alarm_clk_drv_funcs {

    /** \brief ��������ʱ�� */
    int (*pfn_alarm_clk_time_set)(void *p_drv, am_alarm_clk_tm_t *p_tm);

    /** \brief �������ӻص����� */
    int (*pfn_alarm_clk_callback_set)(void          *p_drv,
                                      am_pfnvoid_t   pfn_callback,
                                      void          *p_arg);
    /** \brief ��������  */
    int (*pfn_alarm_clk_on)(void *p_drv);

    /** \brief �ر�����  */
    int (*pfn_alarm_clk_off)(void *p_drv);

};


/**
 * \brief ALARM_CLK ��׼����
 */
typedef struct am_alarm_clk_serv {

    /** \brief RTC�������� */
    struct am_alarm_clk_drv_funcs *p_funcs;

    /** \brief ����������һ����ڲ��� */
    void                      *p_drv;
} am_alarm_clk_serv_t;

/** \brief ALARM_CLK ��׼�������������� */
typedef am_alarm_clk_serv_t *am_alarm_clk_handle_t;


/**
 * \brief ��������ʱ��
 *
 * \param[in] handle : ALARM_CLK ��׼����������
 * \param[in] p_tm   : Ҫ���õ�ʱ��
 *
 * \return    AM_OK    : ���óɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_alarm_clk_time_set (am_alarm_clk_handle_t handle, am_alarm_clk_tm_t *p_tm)
{
    return handle->p_funcs->pfn_alarm_clk_time_set(handle->p_drv, p_tm);
}

/**
 * \brief ��������ʱ��
 *
 * \param[in] handle         : ALARM_CLK ��׼����������
 * \param[in] pfn_callback   : �����жϵĻص�����
 * \param[in] p_arg          : �ص������Ĳ���
 *
 * \return    AM_OK    : ���óɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_alarm_clk_callback_set (am_alarm_clk_handle_t handle,
                               am_pfnvoid_t          pfn_callback,
                               void                 *p_arg)
{
    return handle->p_funcs->pfn_alarm_clk_callback_set(handle->p_drv, pfn_callback, p_arg);
}

/**
 * \brief ��������
 *
 * \param[in]  handle  : ALARM_CLK��׼����������
 *
 * \return   AM_OK     : ��ȡʱ��ɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_alarm_clk_on (am_alarm_clk_handle_t handle)
{
    return handle->p_funcs->pfn_alarm_clk_on(handle->p_drv);
}

/**
 * \brief �ر�����
 *
 * \param[in]  handle  : ALARM_CLK��׼����������
 *
 * \return   AM_OK     : ��ȡʱ��ɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_alarm_clk_off (am_alarm_clk_handle_t handle)
{
    return handle->p_funcs->pfn_alarm_clk_off(handle->p_drv);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ALARM_CLK_H */

/* end of file */
