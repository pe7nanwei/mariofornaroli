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
 * \brief 74HC595ͨ�ò����ӿ�
 *
 *        ������������һ��74HC595оƬ, ���ڳ�����. ���ݲ�ͬ��������ʽ, ������ʵ�ֶ�
 *    ��Ĳ���, ����, ʹ��GPIO����74HC595, ʹ��SPI����74HC595.
 *
 *  74HC595���ż��䶨��
 *
 *               -------------
 *               | O         |
 *          Q1 --|1        16|-- VCC
 *          Q2 --|2        15|-- Q0
 *          Q3 --|3        14|-- SDI    (DATA Pin)
 *          Q4 --|4   595  13|-- OE     (OE Pin)
 *          Q5 --|5        12|-- RCK    (LOCK Pin)
 *          Q6 --|6        11|-- SCK    (CLOCK Pin)
 *          Q7 --|7        10|-- SCLR
 *         GND --|8         9|-- Q7'
 *               |           |
 *               -------------
 *
 *       Q0 ~ Q7 :  �����������.
 *        GND(8) :  ��.
 *        Q7'(9) :  ������������(���뵽��һ��������74HC595).
 *      SCLR(10) :  ��SCLR�ǵ͵�ƽʱ, ����λ�Ĵ����е��������.
 *       SCK(11) :  ��λ�Ĵ�����������ʱ���ź�, ��λ������SCK��������.
 *       RCK(12) :  ����Ĵ�������ʱ���ź�.
 *        OE(13) :  ���ʹ��, �͵�ƽ��Ч.
 *       SDI(14) :  ������������.
 *           VCC :  2 ~ 5v.
 *
 * \par ʹ��ʾ��
 * \code
 *
 *  int am_main (void)
 *  {
 *      uint8_t buf[2] = {0x02, 0x06};
 *
 *      // ��þ������ͬƽ̨�е�ʵ����ʼ��������(am_hc595_inst_init)���ܴ��ڲ�ͬ
 *      am_hc595_handle_t handle = am_hc595_inst_init();
 *
 *      // ��������0x02��0x06�� ��������HC595����
 *      am_hc595_send(handle, buf, 2);
 *
 *      // ...
 *  }
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-23  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HC595_H
#define __AM_HC595_H

#include "am_common.h"
#include "am_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_hc595
 * \copydoc am_hc595.h
 * @{
 */

/**
 * \brief HC595���������ṹ��
 */
struct am_hc595_drv_funcs {

    /** \brief ʹ��HC595��� */
    int (*pfn_hc595_enable) (void *p_cookie);

    /** \brief ����HC595�����Ĭ�ϣ�������ָ���״̬�� */
    int (*pfn_hc595_disable) (void *p_cookie);

    /** \brief HC595���ݷ���  */
    int (*pfn_send) (void *p_cookie, const void *p_data, size_t nbytes);
};

/**
 * \brief HC595 ��׼����ṹ��
 */
typedef struct am_hc595_dev {
    const struct am_hc595_drv_funcs *p_funcs;  /**< \brief �豸��������     */
    void                            *p_cookie; /**< \brief �豸������������ */
} am_hc595_dev_t;

/** \brief HC595 ��׼�������������� */
typedef am_hc595_dev_t *am_hc595_handle_t;

/**
 * \brief ʹ��HC595���
 * \param[in] handle : HC595��׼������
 * \return ��׼�����
 */
am_static_inline
int am_hc595_enable (am_hc595_handle_t handle)
{
    if (handle && handle->p_funcs && handle->p_funcs->pfn_hc595_enable) {
        return handle->p_funcs->pfn_hc595_enable(handle->p_cookie);
    }
    return -AM_EINVAL;
}

/**
 * \brief ����HC595�����Ĭ�ϣ�������ָ���״̬��
 * \param[in] handle : HC595��׼������
 * \return ��׼�����
 */
am_static_inline
int am_hc595_disable (am_hc595_handle_t handle)
{
    if (handle && handle->p_funcs && handle->p_funcs->pfn_hc595_disable) {
        return handle->p_funcs->pfn_hc595_disable(handle->p_cookie);
    }
    return -AM_EINVAL;
}

/**
 * \brief HC595���ݷ���
 *
 * \param[in] handle : HC595��׼������
 * \param[in] p_data : �����͵����ݻ���
 * \param[in] nbytes : �����ֽ���
 *
 * \return ��׼�����
 */
am_static_inline
int am_hc595_send (am_hc595_handle_t handle, const void *p_data, size_t nbytes)
{
    if (handle && handle->p_funcs && handle->p_funcs->pfn_send) {
        return handle->p_funcs->pfn_send(handle->p_cookie, p_data, nbytes);
    }
    return -AM_EINVAL;
}

/** @} am_if_hc595 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC595_H */
