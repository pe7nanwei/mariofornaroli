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
 * \brief SYSTICK ���������� Timer ��׼�ӿ�
 *
 * \note ʹ�� SYSTICK ����� Timer ��׼�ӿڣ��Ͳ���ʹ�ñ�׼��ʱ�ӿ�
 *       am_mdelay()��am_udelay()
 * \internal
 * \par Modification History
 * - 1.02 15-12-14  hgo, fix potential bug caused by incorrect p_arg on callback
 * - 1.00 15-09-22  win, first implementation.
 * \endinternal
 */

/*******************************************************************************
  includes
*******************************************************************************/
#include "am_arm_systick.h"
#include "hw/amhw_arm_systick.h"
#include "am_clk.h"

/*******************************************************************************
  ��������
*******************************************************************************/
static const am_timer_info_t * __systick_info_get (void *p_drv);

static int __systick_clkin_freq_get (void *p_drv, uint32_t *p_freq);
static int __systick_prescale_set (void *p_drv, uint8_t chan, uint32_t prescale);
static int __systick_prescale_get (void *p_drv, uint8_t chan, uint32_t *p_prescale);
static int __systick_count_get (void *p_drv, uint8_t chan, void *p_count);
static int __systick_rollover_get (void *p_drv,uint8_t chan,void *p_rollover);
static int __systick_disable (void *p_drv, uint8_t chan);
static int __systick_enable (void *p_drv, uint8_t chan, void *p_count);

static int __systick_callback_set (void    *p_drv,
                                   uint8_t  chan,
                                   void   (*pfn_callback)(void *),
                                   void    *p_arg);

/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

/* ��ʱ����Ϣ */
static const am_timer_info_t __g_systick_info = {
    24,                                                   /* 24λ��ʱ��       */
    1,                                                    /* ��ͨ��           */
    AM_TIMER_CAN_INTERRUPT      |                         /* ���Բ����ж�     */
    AM_TIMER_AUTO_RELOAD        |                         /* ֧���Զ�����     */
    AM_TIMER_INTERMEDIATE_COUNT,                          /* ��ǰ������ֵ�ɶ� */
    0                                                     /* ��֧��ʱ��Ԥ��Ƶ */
};

/* SYSTICK ��������  */
static const struct am_timer_drv_funcs __g_systick_drv_funcs = {
    __systick_info_get,
    __systick_clkin_freq_get,
    __systick_prescale_set,
    __systick_prescale_get,
    __systick_count_get,
    __systick_rollover_get,
    __systick_enable,
    __systick_disable,
    __systick_callback_set,
};

/*
 * ���ǵ� SYSTICK �жϴ������޷����ݲ�����ʹ��һ��ȫ�ֱ���ָ�룬
 * ���� SYSTICK �豸�ṹ���ַ
 */
static am_arm_systick_dev_t *__gp_systick_dev;

/*******************************************************************************
  �жϴ���
*******************************************************************************/

/**
 * \brief SYSTICK �жϴ�����
 *
 * \return ��
 */
void SysTick_Handler (void)
{
    if (__gp_systick_dev->pfn_callback != NULL) {
        __gp_systick_dev->pfn_callback(__gp_systick_dev->p_arg);
    }
}

/*******************************************************************************
  ��׼��ʱ������ʵ��
*******************************************************************************/

/* ��ȡ SYSTICK ��Ϣ */
static const am_timer_info_t * __systick_info_get (void *p_drv)
{
    return &__g_systick_info;
}

/******************************************************************************/
static int __systick_clkin_freq_get (void *p_drv, uint32_t *p_freq)
{
    am_arm_systick_dev_t *p_dev = (am_arm_systick_dev_t *)p_drv;

    if ((p_dev == NULL) || (p_freq == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ��ǰϵͳʱ��Ƶ�ʣ�systick ʹ�õ���ϵͳʱ�� */
    *p_freq = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    return AM_OK;
}

/******************************************************************************/
static int __systick_prescale_set (void *p_drv, uint8_t chan, uint32_t prescale)
{
    if (prescale == 1) {
        return AM_OK;
    }

    return -AM_ENOTSUP;
}

/******************************************************************************/
static int __systick_prescale_get (void *p_drv, uint8_t chan, uint32_t *p_prescale)
{
    am_arm_systick_dev_t *p_dev = (am_arm_systick_dev_t *)p_drv;

    if (p_dev == NULL || p_prescale == NULL || chan != 0) {
        return -AM_EINVAL;
    }

    /* �޷�Ƶ������Ƶֵʼ��Ϊ1  */
    *p_prescale = 1;

    return AM_OK;
}

/******************************************************************************/
static int __systick_count_get (void *p_drv, uint8_t chan, void *p_count)
{
    am_arm_systick_dev_t *p_dev        = (am_arm_systick_dev_t *)p_drv;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if (p_dev == NULL || p_count == NULL || chan != 0) {
        return -AM_EINVAL;
    }

    p_hw_systick = (amhw_arm_systick_t *)p_dev->p_devinfo->systick_regbase;

    *((uint32_t *)p_count) = amhw_arm_systick_reload_val_get(p_hw_systick) - \
                             amhw_arm_systick_val_get(p_hw_systick);

    return AM_OK;
}

/******************************************************************************/
static int __systick_rollover_get (void     *p_drv,
                                   uint8_t   chan,
                                   void     *p_rollover)
{
    am_arm_systick_dev_t *p_dev        = (am_arm_systick_dev_t *)p_drv;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if (p_drv == NULL || p_rollover == NULL || chan != 0) {
        return -AM_EINVAL;
    }

    p_hw_systick = (amhw_arm_systick_t   *) p_dev->p_devinfo->systick_regbase;

    *((uint32_t *)p_rollover) = amhw_arm_systick_reload_val_get(p_hw_systick);

    return AM_OK;
}

/******************************************************************************/
static int __systick_disable (void *p_drv, uint8_t chan)
{
    am_arm_systick_dev_t *p_dev        = NULL;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if (p_drv == NULL || chan != 0) {
        return -AM_EINVAL;
    }

    p_dev        = (am_arm_systick_dev_t *)p_drv;
    p_hw_systick = (amhw_arm_systick_t   *)p_dev->p_devinfo->systick_regbase;

    amhw_arm_systick_int_disable(p_hw_systick);
    amhw_arm_systick_disable(p_hw_systick);

    return AM_OK;
}

/******************************************************************************/
static int __systick_enable (void     *p_drv,
                             uint8_t   chan,
                             void     *p_count)
{
    am_arm_systick_dev_t *p_dev        = NULL;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if ((p_drv == NULL) || (chan != 0) || (p_count == NULL)) {
        return -AM_EINVAL;
    }

    p_dev        = (am_arm_systick_dev_t *)p_drv;
    p_hw_systick = (amhw_arm_systick_t   *)p_dev->p_devinfo->systick_regbase;

    /* �������ض�ʱ�Ĵ����е���ֵ */
    amhw_arm_systick_reload_val_set(p_hw_systick, *((uint32_t *)p_count));

    /* �����ǰ��ʱ�������е���ֵ */
    amhw_arm_systick_val_set(p_hw_systick, 0x0);

    if (p_dev->pfn_callback == NULL) {
        amhw_arm_systick_int_disable(p_hw_systick);
    } else {
        amhw_arm_systick_int_enable(p_hw_systick);
    }

    /* ʹ�� SYSTICK */
    amhw_arm_systick_enable(p_hw_systick);

    return AM_OK;
}

/******************************************************************************/
static int __systick_callback_set (void    *p_drv,
                                   uint8_t  chan,
                                   void   (*pfn_callback)(void *),
                                   void    *p_arg)
{
    am_arm_systick_dev_t *p_dev        = NULL;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if (p_drv == NULL || chan != 0) {
        return -AM_EINVAL;
    }

    p_dev        = (am_arm_systick_dev_t *)p_drv;
    p_hw_systick = (amhw_arm_systick_t   *)p_dev->p_devinfo->systick_regbase;

    if (pfn_callback == NULL) {
        amhw_arm_systick_int_disable(p_hw_systick);
    } else {
        p_dev->p_arg        = p_arg;
        p_dev->pfn_callback = pfn_callback;
        
        amhw_arm_systick_int_enable(p_hw_systick);
    }

    return AM_OK;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

am_timer_handle_t  am_arm_systick_init (am_arm_systick_dev_t           *p_dev,
                                        const am_arm_systick_devinfo_t *p_devinfo)
{
    amhw_arm_systick_t *p_hw_systick = NULL;

    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_hw_systick              = (amhw_arm_systick_t *)p_devinfo->systick_regbase;
    p_dev->p_devinfo          = p_devinfo;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_systick_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev;
    p_dev->pfn_callback       = NULL;
    p_dev->p_arg              = NULL;

    __gp_systick_dev          = p_dev;

    /* ���ö�ʱ��ʱ��Ƶ�� */
    if ((p_devinfo->clk_freq_src != AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM) &&
        (p_devinfo->clk_freq_src != AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF)) {
        return NULL;
    } else {
        amhw_arm_systick_config(p_hw_systick, p_devinfo->clk_freq_src);
    }

    return &(p_dev->timer_serv);
}

/******************************************************************************/
void am_arm_systick_deinit (am_timer_handle_t handle)
{
    am_arm_systick_dev_t *p_dev        = NULL;
    amhw_arm_systick_t   *p_hw_systick = NULL;

    if (handle == NULL) {
        return ;
    }

    p_dev = (am_arm_systick_dev_t *)handle;
    
    p_hw_systick = (amhw_arm_systick_t *)p_dev->p_devinfo->systick_regbase;

    p_dev->timer_serv.p_funcs = NULL;
    p_dev->timer_serv.p_drv   = NULL;
    p_dev->pfn_callback       = NULL;
    p_dev->p_arg              = NULL;

    amhw_arm_systick_int_disable(p_hw_systick);
    amhw_arm_systick_disable(p_hw_systick);
}
