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
 * \brief ϵͳ�δ������ʱ���û������ļ�
 * \sa am_hwconf_system_tick_softimer.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-20  pea, first implementation
 * \endinternal
 */

#include "am_lpc84x.h"
#include "ametal.h"
#include "am_timer.h"
#include "am_system.h"
#include "am_softimer.h"
#include "am_arm_nvic.h"
#include "am_lpc84x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_system_tick_softimer
 * \copydoc am_hwconf_system_tick_softimer.c
 * @{
 */

/*******************************************************************************
  Local struct type define
*******************************************************************************/
struct __prescale_and_count_cal_ctx {
    uint32_t   desired_ticks;           /* Ŀ�� ticks                         */
    uint32_t   count_max;               /* ��ʱ����� count ֵ                */
    uint32_t   error;                   /* ��ǰԤ��Ƶ�ͼ���ֵ����Ӧ�����ֵ   */
    uint32_t   count;                   /* ��ǰ������: count ֵ             */
    uint32_t   prescale;                /* ��ǰ������: Ԥ��Ƶֵ             */
    am_bool_t  update;                  /* �Ƿ���¹�Ԥ��Ƶֵ                 */
};


/** \brief ϵͳ�δ��Ƶ�ʣ�Ĭ�� 1KHz */
#define __SYSTEM_TICK_RATE      1000

/** \brief ʹ�õĶ�ʱ�����жϺ� */
#define __TIMER_INUM            INUM_MRT

/** \brief ʹ�ö�ʱ��ͨ�� 0 */
#define __TIMER_CHAN            0

/**
 * \brief ��ʱ���ص����������ڲ���ϵͳ�δ�
 */
am_local void __system_tick_callback (void *p_arg)
{
    am_system_module_tick();    /* ����ϵͳ�δ� */
}

/**
 * \brief ��ʱ���ص����������ڲ���ϵͳ�δ����������ʱ��
 */
am_local void __system_tick_softimer_callback (void *p_arg)
{
    am_system_module_tick();      /* ����ϵͳ�δ� */
    am_softimer_module_tick();    /* ���������ʱ�� */
}

/**
 * \brief ϵͳ�δ�ʵ����ʼ������ʹ�������ʱ����
 */
am_timer_handle_t am_system_tick_inst_init (void)
{
    am_timer_handle_t handle;
    //am_timer_info_t   hwtimer_info;

    handle = am_lpc84x_mrt_inst_init();

    if (NULL != handle) {
        uint32_t clk_freq;

        am_timer_count_freq_get(handle, 0, &clk_freq);
      

        /* ����ʱ�����ж����ȼ�����Ϊ��� */
        am_arm_nvic_priority_set(__TIMER_INUM, 0x03, 0x03);

        am_timer_callback_set(handle,
                              __TIMER_CHAN,
                              __system_tick_callback,
                              NULL);

        //am_timer_info_get(handle, &hwtimer_info);

        am_system_module_init(__SYSTEM_TICK_RATE);

        am_timer_enable(handle,
                        __TIMER_CHAN,
                        clk_freq / __SYSTEM_TICK_RATE);
    }

    return handle;
}


static void __error_check_with_new_prescale (
    struct __prescale_and_count_cal_ctx *p_ctx, uint32_t prescale_new)
{
    uint32_t count = p_ctx->desired_ticks / prescale_new;
    uint32_t error;

    /* ���� count ֵ���� count_max */
    if (count > p_ctx->count_max) {
        count = p_ctx->count_max;
    }

    error = p_ctx->desired_ticks - count * prescale_new;

    if (p_ctx->error > error) {        /* ���ָ�С�������ֵ */
        p_ctx->error    = error;
        p_ctx->count    = count;
        p_ctx->prescale = prescale_new;
        p_ctx->update   = AM_TRUE;
    }
}


/******************************************************************************/
static int __prescale_and_count_cal (const am_timer_info_t *p_info,
                                     uint32_t               ticks,
                                     uint32_t              *p_prescale,
                                     uint32_t              *p_count)
{
    struct __prescale_and_count_cal_ctx  ctx;

    uint32_t prescale_max;
    uint32_t prescale_min;
    uint32_t prescale;

    uint32_t count_max;

    count_max = ( (uint32_t)1ull << (p_info->counter_width) ) - 1;

    /* �����Ƶ */
    if (ticks <= count_max) {

         *p_prescale = 1;
         *p_count    = ticks;

         return AM_OK;
    }

    /* ��Ҫ��Ƶ������֧���κη�Ƶֵ */
    if (p_info->prescaler == 0) {
        return -AM_ENOTSUP;
    }

    prescale_min = ticks / count_max;        /* ���� Ticks ����С��Ƶ  */

    ctx.count_max     = count_max;
    ctx.desired_ticks = ticks;
    ctx.error         = ticks;              /* ��ʼ����Ϊ������      */
    ctx.count         = count_max;
    ctx.prescale      = 1;
    ctx.update        = AM_FALSE;

    if (p_info->features & AM_TIMER_SUPPORT_ALL_PRESCALE_1_TO_MAX) {

        prescale_max = p_info->prescaler;

        if (prescale_max < prescale_min) {   /* �޷����� */
            return -AM_ENOTSUP;
        }

        /* �������з�Ƶֵ��Ѱ����ѷ�Ƶֵ�������С��*/
        for (prescale = prescale_min; prescale <= prescale_max; prescale++) {
            __error_check_with_new_prescale(&ctx, prescale);
            if (ctx.error == 0) {
                break;
            }
        }

    } else {

        for (prescale = 1; prescale != 0; prescale <<= 1) {

            /* ֧�ָ÷�Ƶ�� ��������СֵҪ��  */
            if ((prescale & p_info->prescaler) && (prescale >= prescale_min)) {
                __error_check_with_new_prescale(&ctx, prescale);
                if (ctx.error == 0) {
                    break;
                }
            }
        }
    }

    if (ctx.update) {

         *p_prescale = ctx.prescale;
         *p_count    = ctx.count;

        return AM_OK;
    }

    return -AM_ENOTSUP;
}


/******************************************************************************/
static int __timer_enable_us (am_timer_handle_t handle, uint8_t chan, uint32_t nus)
{
    uint32_t               clkin;
    uint32_t               prescale;
    uint32_t               ticks;
    uint32_t               count;
    const am_timer_info_t *p_info;

    if (handle == NULL) {
        return -AM_EINVAL;
    }

    p_info = am_timer_info_get(handle);

    am_timer_clkin_freq_get(handle, &clkin);

    /* ����������Ƶ���£�Ӧ�ü�¼��count ֵ */
    ticks = nus *  (clkin / 1000000);

    if (__prescale_and_count_cal(p_info, ticks, &prescale, &count) != AM_OK) {
        return -AM_ENOTSUP;
    }

    am_timer_prescale_set(handle, chan, prescale);

    if (p_info->counter_width <= 32) {
        am_timer_enable(handle, chan, count);
    } else {
        am_timer_enable64(handle, chan, count);
    }

    return AM_OK;
}
/**
 * \brief ϵͳ�δ�ʵ����ʼ����ʹ�������ʱ����
 */
am_timer_handle_t am_system_tick_softimer_inst_init (void)
{
    am_timer_handle_t handle;
   // am_timer_info_t   hwtimer_info;

    handle = am_lpc84x_mrt_inst_init();
    //handle = am_arm_systick_inst_init();
    if (NULL != handle) {

        /* ��ʼ�������ʱ�� */
        am_softimer_module_init(__SYSTEM_TICK_RATE);

        /* ����ʱ�����ж����ȼ�����Ϊ��� */
        am_arm_nvic_priority_set(__TIMER_INUM, 0x03, 0x03);

        am_timer_callback_set(handle,
                              __TIMER_CHAN,
                              __system_tick_softimer_callback,
                              NULL);

        //am_timer_info_get(handle, &hwtimer_info);

        am_system_module_init(__SYSTEM_TICK_RATE);

        __timer_enable_us(handle,
                          __TIMER_CHAN,
                          1000000 / __SYSTEM_TICK_RATE);
  }

    return handle;
}

/**
 * @}
 */

/* end of file */
