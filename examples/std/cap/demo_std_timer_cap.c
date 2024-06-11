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
 * \brief ��ʱ��ʵ�ֲ����ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� PWM ������ӵ������������š�
 *
 * - ʵ������
 *   1. ���Դ���������񵽵� PWM �źŵ����ں�Ƶ�ʡ�
 *
 * \par Դ����
 * \snippet demo_std_timer_cap.c src_std_timer_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 16-04-22  nwt, first implementation
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_timer_cap
 * \copydoc demo_std_timer_cap.c
 */

/** [src_std_timer_cap] */
#include "ametal.h"
#include "am_cap.h"
#include "am_vdebug.h"

static volatile am_bool_t __g_flag    = AM_FALSE;    /**< \brief �����־ */
static volatile uint32_t  __g_time_ns = 0;           /**< \brief �������ֵ */

/**
 * \brief ����ص�����
 */
static void __cap_callback (void *p_arg, unsigned int cap_val)
{
    static uint32_t  s_count    = 0;
    static am_bool_t s_first    = AM_TRUE;
    am_cap_handle_t  cap_handle = (am_cap_handle_t)p_arg;

    if (__g_flag == AM_FALSE) {

        if (s_first == AM_TRUE) {
            s_count = cap_val;
            s_first  = AM_FALSE;
        } else {

            /* ��ʱ��TIM����32λ������ʱ, �������ʱ���ݴ��� */
            if(s_count < cap_val) {
               am_cap_count_to_time(cap_handle,
                                    0,
                                    s_count,
                                    cap_val,
                                    (unsigned int *)&__g_time_ns);
            }

            s_first = AM_TRUE;

            /* �ñ�־Ϊ�棬����������� */
            __g_flag = AM_TRUE;
        }
    }
}

/**
 * \brief �������
 */
void demo_std_timer_cap_entry (am_cap_handle_t cap_handle, int cap_chan)
{
    uint32_t freq = 0;

    /* ������������ */
    am_cap_config(cap_handle,
                  cap_chan,
                  AM_CAP_TRIGGER_RISE,
                  __cap_callback,
                  (void *)cap_handle);
    am_cap_enable(cap_handle, cap_chan);

    while (1) {
        if (__g_flag == AM_TRUE) {
            freq = 1000000000 / __g_time_ns;

            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n",
                         __g_time_ns,
                         freq);

            __g_flag = AM_FALSE;
        }
    }
}
/** [src_std_timer_cap] */

/* end of file */
