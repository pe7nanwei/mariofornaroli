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
 * \brief ��ʱ����׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-07  hgo, del am_timer_connect().
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_TIMER_H
#define __AM_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup am_if_timer
 * \copydoc am_timer.h
 * @{
 */

/**
 * \name ��ʱ������
 *  
 *  - ��8λ����ʱ��λ������32λ��ʱ�������8λֵΪ32
 *  - 8 ~ 15 λ��ʾ��ʱ��ͨ����
 *  - ������ʱ�����Խ�ռһλ���ӵ�16λ��ʼ�� AM_TIMER_FEATURE(0) ~ AM_TIMER_FEATURE(15)
 * @{
 */
 
/** \brief ����������ʱ�����Զ���         */
#define AM_TIMER_FEATURE(feature_id)           ((uint32_t)(1u << (feature_id)))

/** \brief ��ʱ�����Բ����ж�             */
#define AM_TIMER_CAN_INTERRUPT                  AM_TIMER_FEATURE(0)

/** \brief ��ʱ�����Զ�ȡ��ǰ��������ֵ   */
#define AM_TIMER_INTERMEDIATE_COUNT             AM_TIMER_FEATURE(1)

/** \brief ��ʱ�����ܱ�ֹͣ               */
#define AM_TIMER_CANNOT_DISABLE                 AM_TIMER_FEATURE(2)

/** \brief ��ʱ���ڶ�ȡ����ֵʱ��ֹͣ     */
#define AM_TIMER_STOP_WHILE_READ                AM_TIMER_FEATURE(3)

/** \brief ��ʱ��֧���Զ���װ�ؼ���ֵ     */
#define AM_TIMER_AUTO_RELOAD                    AM_TIMER_FEATURE(4)

/** \brief ��ʱ���������У����ܸı䷭תֵ */
#define AM_TIMER_CANNOT_MODIFY_ROLLOVER         AM_TIMER_FEATURE(5)
 
/** 
 * \brief ��ʱ����Ԥ��Ƶֵ֧��1�����ֵ֮�������ֵ
 * 
 * - ����ʱ��֧�ָ����ԣ���ʱ����Ϣ�е� prescaler (am_timer_info_t)��ʾ֧�ֵ�
 *   ���Ԥ��Ƶֵ�����磬prescaler��ֵΪ 256����ʾ֧�� 1 ~ 256 ����Ԥ��Ƶֵ��
 *
 * - ����ʱ����֧�ָ����ԣ���ʱ����Ϣ�е� prescaler ��ʾ����֧����ЩԤ��Ƶֵ��
 *   ����Nλ��N�ķ�Χ�� 0 ~ 31��Ϊ 1�����ʾ֧��Ԥ��Ƶֵ��2 �� N�η������磬
 *   prescaler��ֵΪ0xF��bit0��1��2��3��ֵΪ1����֧�ֵķ�Ƶֵ�У�1(2^0)��2(2^1)��
 *   4(2^2)��8(2^3)
 *
 * - �ر�أ��� prescaler ��ֵΪ0����ʾ��ʱ����֧��Ԥ��Ƶ�����������Ӧ�� prescaler
 *   ����Ϊ 0x01��
 */
#define AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX  AM_TIMER_FEATURE(6)

/** @} */ 


/** 
 * \brief ��ʱ����Ϣ�ṹ��
 */
typedef struct am_timer_info {

    uint8_t   counter_width;               /**< \brief ��ʱ��λ��             */
    uint8_t   chan_num;                    /**< \brief ��ʱ��ͨ����           */
    uint16_t  features;                    /**< \brief ��ʱ������             */
 
    /** 
     * \brief Ԥ��Ƶ����Ϣ
     *
     * ��ֵ��ʾԤ��Ƶ��֧�ֵ�Ԥ��Ƶֵ����ֵ�ĺ����붨ʱ����Ԥ��Ƶ��������أ�
     * ��������ԵĽ��� #AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX
     */
    uint32_t   prescaler; 
    
} am_timer_info_t;


/**
 * \brief ��ʱ�����������ṹ��
 */
struct am_timer_drv_funcs {

    /**
     * \brief ��ȡ��ʱ��������Ϣ
     *
     * ����Ϣ�Ƕ�ʱ���Ĺ������ԣ��������ڲ���ɶ��壬�ú������Է���ָ��ó�����
     * Ϣ��ָ�룬�Ա��û�ʹ�á�
     */
    const am_timer_info_t * (*pfn_info_get) (void *p_drv);
    
    /**
     * \brief ��ȡ��ʱ��������ʱ��Ƶ�ʣ����ж�ʱ��ͨ������һ������Ƶ�ʣ�
     *
     * ����ʱ��Ƶ����ʱ�����á�����Ӳ������أ���Ƶ�ʲ��Ƕ�ʱ���ļ�ʱƵ�ʣ���ʱ
     * ����ʵ�ʼ�ʱƵ�ʿ�����ͨ��һ��Ԥ��Ƶ����Ƶ���Ƶ�ʡ�
     */
    int (*pfn_clkin_freq_get) (void *p_drv, uint32_t *p_freq);
    
    /**
     * \brief ���ö�ʱ����Ԥ��Ƶֵ
     *
     * ����ʱ����֧��Ԥ��Ƶ���� �ú�������Ϊ NULL��
     */
    int (*pfn_prescale_set) (void *p_drv, uint8_t chan, uint32_t prescale);

    /**
     * \brief ��ȡ��ʱ����ǰʹ�õ�Ԥ��Ƶֵ
     *
     * ʹ������Ƶ�ʳ��Ը�Ԥ��Ƶֵ�����ɵõ���ʱ���ļ���Ƶ��
     */
    int (*pfn_prescale_get) (void *p_drv, uint8_t chan, uint32_t *p_prescale);

    /**
     * \brief ��ȡ��ǰ��ʱ������ֵ
     *
     * ����ʱ����λ��������32λ����  p_count Ϊ  uint32_t* ����
     * ����ʱ����λ������32λ����  p_count Ϊ  uint64_t* ����
     */
    int (*pfn_count_get) (void *p_drv, uint8_t chan, void *p_count);

    /** 
     * \brief ��ȡ��ʱ����תֵ
     * 
     * ����ʱ����λ��������32λ����  p_count Ϊ  uint32_t* ����
     * ����ʱ����λ������32λ����  p_count Ϊ  uint64_t* ����
     */
    int (*pfn_rollover_get) (void *p_drv, uint8_t chan, void *p_rollover);
 
    /** 
     * \brief ʹ�ܶ�ʱ����ͬʱ�趨��ʱcountֵ
     *
     * ����ʱ����λ��������32λ����  p_count Ϊ  uint32_t* ����
     * ����ʱ����λ������32λ����  p_count Ϊ  uint64_t* ����
     *
     * ��������0��ʼ�������ﵽ��ֵʱ�������û��趨�Ļص����������ص�������Ч��
     * ͬʱ����������ֵ�ص�0���¿�ʼ������
     */
    int (*pfn_enable) (void *p_drv, uint8_t chan, void *p_count);

    /** \brief ���ܶ�ʱ��                         */
    int (*pfn_disable) (void *p_drv, uint8_t chan);

    /** \brief ���ûص�������ÿ��һ����ʱ�������ʱ���� */
    int (*pfn_callback_set)(void    *p_drv,
                            uint8_t  chan,
                            void   (*pfn_callback)(void *),
                            void    *p_arg);
};

/** 
 * \brief ��ʱ������
 */
typedef struct am_timer_serv {

    /** \brief ��ʱ�����������ṹ��ָ�� */
    struct am_timer_drv_funcs *p_funcs; 
    
    /** \brief �������������ĵ�һ������ */
    void                      *p_drv;   
} am_timer_serv_t;

/** \brief ��ʱ����׼�������������Ͷ��� */
typedef am_timer_serv_t *am_timer_handle_t;

/** 
 * \brief ��ȡ��ʱ����Ϣ
 * \param[in]  handle : ��ʱ����׼����������
 * \return ָ��ʱ����Ϣ������ָ�룬��ΪNULL�����ʾ��Ϣ��ȡʧ��
 */
am_static_inline
const am_timer_info_t * am_timer_info_get (am_timer_handle_t handle)
{
    return handle->p_funcs->pfn_info_get(handle->p_drv);
}

/**
 * \brief ��ȡ��ǰ��ʱ��������ʱ��Ƶ�ʣ����ж�ʱ��ͨ������һ������Ƶ�ʣ�
 *
 * ��ʱ��������Ƶ�ʲ��Ƕ�ʱ���ļ���Ƶ�ʣ�ʵ�ʶ�ʱ������Ƶ�����ɸ�Ƶ�ʷ�Ƶ�Ľ����
 * ֧�ֵķ�Ƶֵ������ԣ�#AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX �������������Ƶ
 * ֵ����ͨ��  am_timer_prescale_set() �ӿ����á�
 *
 * \param[in]  handle : ��ʱ����׼����������
 * \param[out] p_freq : ��ȡ��ʱ������Ƶ�ʵ�ָ��
 *
 * \return ��
 */
am_static_inline
int am_timer_clkin_freq_get (am_timer_handle_t handle, uint32_t *p_freq)
{
    return handle->p_funcs->pfn_clkin_freq_get(handle->p_drv, p_freq);
}

/** 
 * \brief ���ö�ʱ����Ԥ��Ƶֵ
 *
 * \param[in] handle   : ��ʱ����׼����������
 * \param[in] chan     : ��ʱ��ͨ��
 * \param[in] prescale : Ԥ��Ƶֵ
 *
 * \retval  AM_OK      : ���óɹ�
 * \retval -AM_EINVAL  : ����ʧ��, ��������
 * \retval -AM_ENOTSUP : ����ʧ�ܣ���֧�ֵ�Ԥ��Ƶֵ��֧�ֵ�Ԥ��Ƶֵ�����ʱ����Ϣ
 */
am_static_inline
int am_timer_prescale_set (am_timer_handle_t handle, 
                           uint8_t           chan, 
                           uint32_t          prescale)
{
    return handle->p_funcs->pfn_prescale_set(handle->p_drv, chan, prescale); 
}

/** 
 * \brief ���ö�ʱ����Ԥ��Ƶֵ
 *
 * \param[in] handle   : ��ʱ����׼����������
 * \param[in] chan     : ��ʱ��ͨ��
 * \param[in] prescale : Ԥ��Ƶֵ
 *
 * \retval  AM_OK      : ���óɹ�
 * \retval -AM_EINVAL  : ����ʧ��, ��������
 * \retval -AM_ENOTSUP : ����ʧ�ܣ���֧�ֵ�Ԥ��Ƶֵ��֧�ֵ�Ԥ��Ƶֵ�����ʱ����Ϣ
 */
am_static_inline
int am_timer_prescale_get (am_timer_handle_t   handle,
                           uint8_t             chan,
                           uint32_t           *p_prescale)
{
    return handle->p_funcs->pfn_prescale_get(handle->p_drv, chan, p_prescale);
}

/**
 * \brief ��ȡ��ʱ����ǰ�ļ���Ƶ��
 *
 * \param[in]  handle  : ��ʱ����׼����������
 * \param[in]  chan    : ��ʱ��ͨ��
 * \param[out] p_freq  : ���ڻ�ȡ��ʱ����ǰ����Ƶ�ʵ�ָ��
 *
 * \retval  AM_OK      : ��ȡ��ʱ����ǰ����ֵ�ɹ�
 * \retval -AM_EINVAL  : ��ȡʧ��, ��������
 */
int am_timer_count_freq_get (am_timer_handle_t handle,
                             uint8_t           chan,
                             uint32_t         *p_freq);

/** 
 * \brief ��ȡ��ʱ����ǰ�ļ���ֵ
 * 
 * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
 *
 * \param[in]  handle  : ��ʱ����׼����������
 * \param[in]  chan    : ��ʱ��ͨ��
 * \param[out] p_count : ���ڻ�ȡ��ʱ����ǰ����ֵ��ָ��
 *
 * \retval  AM_OK      : ��ȡ��ʱ����ǰ����ֵ�ɹ�
 * \retval -AM_EINVAL  : ��ȡʧ��, ��������
 */
am_static_inline
int am_timer_count_get (am_timer_handle_t handle, 
                        uint8_t           chan, 
                        uint32_t         *p_count)
{
    return handle->p_funcs->pfn_count_get(handle->p_drv, chan, (void*)p_count);
}

/** 
 * \brief ��ȡ��ʱ����תֵ
 *
 * \param[in]  handle     : ��ʱ����׼����������
 * \param[in]  chan       : ��ʱ��ͨ��
 * \param[out] p_rollover : ���ڻ�ȡ��ʱ����תֵ��ָ��
 *
 * \retval  AM_OK         : ��ȡ��ʱ����תֵ�ɹ�
 * \retval -AM_EINVAL     : ��ȡʧ��, ��������
 */
am_static_inline
int am_timer_rollover_get (am_timer_handle_t  handle, 
                           uint8_t            chan, 
                           uint32_t          *p_rollover)
{
    return handle->p_funcs->pfn_rollover_get(handle->p_drv,
                                             chan,
                                            (void *)p_rollover);
}

/** 
 * \brief ���ܶ�ʱ����ֹͣ��ʱ��
 *
 * \param[in] handle  : ��ʱ����׼����������
 * \param[in] chan    : ��ʱ��ͨ��
 *
 * \retval  AM_OK     : ���ܶ�ʱ���ɹ�
 * \retval -AM_EINVAL : ����ʧ��, ��������
 */
am_static_inline
int am_timer_disable (am_timer_handle_t handle, uint8_t chan)
{
    return handle->p_funcs->pfn_disable(handle->p_drv, chan);
}

/** 
 * \brief ʹ�ܶ�ʱ����ͬʱ�趨��ʱcountֵ 
 *
 * \param[in] handle : ��ʱ����׼����������
 * \param[in] chan   : ��ʱ��ͨ��
 * \param[in] count  : ��ʱcountֵ 
 *
 * \retval  AM_OK     : ʹ�ܳɹ�
 * \retval -AM_EINVAL : ʧ��, ��������
 *
 * \note ��ʱ������ֵ�ﵽ�趨�Ķ�ʱcountֵʱ��������жϡ�ͬʱ����λ����ֵ
 *       Ϊ0�������ż�����ʱ��
 */
am_static_inline
int am_timer_enable (am_timer_handle_t handle, uint8_t chan, uint32_t count)
{
     return handle->p_funcs->pfn_enable(handle->p_drv, chan, (void *)(&count));
}

/** 
 * \brief ���ûص�������ÿ��һ����ʱ�������ʱ����
 *
 * \param[in] handle       : ��ʱ����׼����������
 * \param[in] chan         : ��ʱ��ͨ��
 * \param[in] pfn_callback : �ص�����
 * \param[in] p_arg        : �ص��������û�����
 *
 * \retval  AM_OK     : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ��, ��������
 *
 */
am_static_inline
int am_timer_callback_set (am_timer_handle_t  handle, 
                           uint8_t            chan,
                           void             (*pfn_callback)(void *),
                           void              *p_arg)
{
    return handle->p_funcs->pfn_callback_set(handle->p_drv,
                                             chan,
                                             pfn_callback,
                                             p_arg);
}

/** 
 * \brief ��ȡ33 ~ 64λ��ʱ���ĵ�ǰ����ֵ
 *
 * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
 *
 * \param[in]  handle  : ��ʱ����׼����������
 * \param[in]  chan    : ��ʱ��ͨ��
 * \param[out] p_count : ���ڻ�ȡ��ʱ����ǰ����ֵ��ָ��
 *
 * \retval  AM_OK      : ��ȡ���ĵ�ǰ��ʱ������ֵ
 * \retval -AM_EINVAL  : ��ȡʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú�����ȡ��ʱ���ĵ�ǰ����ֵ
 */
am_static_inline
int am_timer_count_get64 (am_timer_handle_t  handle, 
                          uint8_t            chan,
                          uint64_t          *p_count)
{
    return handle->p_funcs->pfn_count_get(handle->p_drv, chan, (void *)p_count);
}

/** 
 * \brief ��ȡ33 ~ 64λ��ʱ���ķ�תֵ
 *
 * \param[in]  handle     : ��ʱ����׼����������
 * \param[in]  chan       : ��ʱ��ͨ��
 * \param[out] p_rollover : ���ڻ�ȡ��ʱ����תֵ��ָ��
 *
 * \retval  AM_OK         : ��ȡ��תֵ�ɹ�
 * \retval -AM_EINVAL     : ��ȡ��תֵʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú�����ȡ��תֵ
 */
am_static_inline
int am_timer_rollover_get64 (am_timer_handle_t  handle, 
                             uint8_t            chan,
                             uint64_t          *p_rollover)
{
    return handle->p_funcs->pfn_rollover_get(handle->p_drv,
                                             chan,
                                            (void *)p_rollover);
}

/** 
 * \brief ʹ��33��64λ��ʱ���������ö�ʱcountֵ
 *
 * \param[in] handle : ��ʱ����׼����������
 * \param[in] chan   : ��ʱ��ͨ��
 * \param[in] count  : ��ʱ��countֵ
 *
 * \retval  AM_OK     : ʹ�ܳɹ�
 * \retval -AM_EINVAL : ʹ��ʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú���ʹ�ܶ�ʱ��
 */
am_static_inline
int am_timer_enable64 (am_timer_handle_t handle, uint8_t chan, uint64_t count)
{
    return handle->p_funcs->pfn_enable(handle->p_drv, chan, (void *)(&count));
}

/** 
 * \brief ʹ�ܶ�ʱ����ֱ���趨��ʱʱ��
 *
 * һ������£��û���Ҫʹ��һ����ʱʱ�䣬��Ҫ��������Ƶ�ʺͶ�ʱ��λ���������Ԥ
 * ��Ƶֵ�Ͷ�ʱ count ֵ��Ȼ��ʹ�� am_timer_prescale_set() ����Ԥ��Ƶֵ�����ʹ
 * �� am_timer_enable() �� am_timer_enable64() ���ö�ʱcountֵ��ʹ�ܶ�ʱ����
 * 
 * �ֶ�������Ҫ���Ƕ�ʱ������Ƶ�ʡ���ʱ��λ������ʱ�����ԣ����ֶ�ʱ�����ܲ�֧��
 * ��ֻ֧�ּ���Ԥ��Ƶֵ������Ϊ���������ڴˣ��û�����ֱ��ʹ�øú�������ָ����ʱ
 * ��ֵ����λ��us��ʹ�ܶ�ʱ����ϵͳ���Զ����ݶ�ʱ��λ������ʱ�����Ե����úö�ʱ
 * ����
 *
 * ��ʱʱ����ܴ���ƫ�ʵ�ʶ�ʱʱ������� ����Ƶ�� �� ��תֵ �õ�����תֵ����
 * ����Ƶ�ʵĵ������ɡ�
 *
 * ���ڶ�ʱʱ�䵽������жϣ���ˣ������齫��ʱ�����õù��̣�����Ӧ�ڼ���us������
 * ���õ� ms ����
 *
 * \param[in] handle : ��ʱ����׼����������
 * \param[in] chan   : ��ʱ��ͨ��
 * \param[in] nus    : ���õĶ�ʱʱ�䣨��λ��us��
 *
 * \retval  AM_OK     : ʹ�ܳɹ�
 * \retval -AM_EINVAL : ʧ��, ��������
 * \retval -AM_NOTSUP ����֧�ָö�ʱʱ�䣬ʱ��̫������ʱ��λ��������
 */
int am_timer_enable_us (am_timer_handle_t handle, uint8_t chan, uint32_t nus);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_TIMER_H */

/* end of file */
