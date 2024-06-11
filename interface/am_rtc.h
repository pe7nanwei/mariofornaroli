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
 * \brief  RTC ��׼�ӿ�
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-07-29  win, modify note.
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AM_RTC_H
#define __AM_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"
#include "am_time.h"
    
/** 
 * \addtogroup am_if_rtc
 * \copydoc am_rtc.h
 * @{
 */

/** 
 * \brief RTC��������
 */
struct am_rtc_drv_funcs {
     
    /** \brief ���õ�ǰ��ϸ��ʱ�� */
    int (*pfn_rtc_time_set)(void *p_drv, am_tm_t *p_tm);
    
    /** \brief ��ȡ��ǰ��ϸ��ʱ�� */
    int (*pfn_rtc_time_get)(void *p_drv, am_tm_t *p_tm);

};


/** 
 * \brief RTC��׼����
 */
typedef struct am_rtc_serv {

    /** \brief RTC�������� */
    struct am_rtc_drv_funcs *p_funcs; 
    
    /** \brief ����������һ����ڲ��� */
    void                    *p_drv;
} am_rtc_serv_t;

/** \brief RTC��׼�������������� */
typedef am_rtc_serv_t *am_rtc_handle_t;

/**
 * \brief ���õ�ǰ��ϸ��ʱ��
 *
 * \param[in] handle : RTC��׼����������
 * \param[in] p_tm   : Ҫ���õ�ʱ��
 *
 * \return    AM_OK    : ���óɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_rtc_time_set (am_rtc_handle_t handle, am_tm_t *p_tm)
{
    return handle->p_funcs->pfn_rtc_time_set(handle->p_drv, p_tm);
}

/**
 * \brief ��ȡ��ǰ��ϸ��ʱ��
 *
 * \param[in]  handle  : RTC��׼����������
 * \param[out] p_tm    : ��ȡ��ʱ��
 *
 * \return   AM_OK     : ��ȡʱ��ɹ�
 * \retval  -AM_EINVAL : ��������
 */
am_static_inline
int am_rtc_time_get (am_rtc_handle_t handle, am_tm_t *p_tm)
{
    return handle->p_funcs->pfn_rtc_time_get(handle->p_drv, p_tm);
}
    
/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_RTC_H */

/* end of file */
