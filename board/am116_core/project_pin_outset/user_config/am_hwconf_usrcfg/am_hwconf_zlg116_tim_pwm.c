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
 * \brief TIM����PWM��� �û������ļ�
 * \sa am_hwconf_zlg116_tim_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-24  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg116.h"
#include "am_gpio.h"
#include "am_zlg_tim_pwm.h"
#include "am_clk.h"
#include "am_zlg116_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zlg116_tim_pwm
 * \copydoc am_hwconf_zlg116_tim_pwm.c
 * @{
 */

/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim1_pwm_init (void)
{
    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
static void __zlg_plfm_tim1_pwm_deinit (void)
{
    /* ��λ�߼���ʱ��1 */
    am_zlg116_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, __TIM1_CH1_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��1������������ */
    {AM_ZLG_TIM_PWM_CH1N, __TIM1_CH1N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, __TIM1_CH2_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��2������������ */
    {AM_ZLG_TIM_PWM_CH2N, __TIM1_CH2N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��3�������� */
    {AM_ZLG_TIM_PWM_CH3, __TIM1_CH3_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��3������������ */
    {AM_ZLG_TIM_PWM_CH3N, __TIM1_CH3N_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
    /** \brief ͨ��4�������� */
    {AM_ZLG_TIM_PWM_CH4, __TIM1_CH4_GPIO, __GPIO_TIM1, __PIO_GPIO_TIM},
};

/** \brief TIM1����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    ZLG116_TIM1_BASE,                          /**< \brief TIM1�Ĵ�����Ļ���ַ    */
    CLK_TIM1,                                  /**< \brief TIM1ʱ��ID              */
    AM_NELEMENTS(__g_tim1_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim1_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE0,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim1_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim1_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM1����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim1_pwm_dev;
static am_pwm_handle_t       __g_tim1_pwm_handle = NULL;

/** \brief tim1 pwm ʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zlg116_tim1_pwm_inst_init (void)
{
    if (__g_tim1_pwm_handle == NULL) {
        __g_tim1_pwm_handle = am_zlg_tim_pwm_init(&__g_tim1_pwm_dev,
                                                  &__g_tim1_pwm_devinfo);
    }
    
    return __g_tim1_pwm_handle;
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_zlg116_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim1_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim1_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim2_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
static void __zlg_plfm_tim2_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��2 */
    am_zlg116_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {
        /** \brief ͨ��1�������� */
        {AM_ZLG_TIM_PWM_CH1, __TIM2_CH1_ETR_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief ͨ��2�������� */
        {AM_ZLG_TIM_PWM_CH2, __TIM2_CH2_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief ͨ��3�������� */
        {AM_ZLG_TIM_PWM_CH3, __TIM2_CH3_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
        /** \brief ͨ��4�������� */
        {AM_ZLG_TIM_PWM_CH4, __TIM2_CH4_GPIO, __GPIO_TIM2, __PIO_GPIO_TIM},
};

/** \brief TIM2����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    ZLG116_TIM2_BASE,                          /**< \brief TIM2�Ĵ�����Ļ���ַ    */
    CLK_TIM2,                                  /**< \brief TIM2ʱ��ID              */
    AM_NELEMENTS(__g_tim2_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim2_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim2_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim2_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM2 ����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim2_pwm_dev;
static am_pwm_handle_t       __g_tim2_pwm_handle = NULL;

/** \brief tim2 pwmʵ����ʼ�������pwm��׼������ */
am_pwm_handle_t am_zlg116_tim2_pwm_inst_init (void)
{
    if (__g_tim2_pwm_handle == NULL) {
        __g_tim2_pwm_handle = am_zlg_tim_pwm_init(&__g_tim2_pwm_dev,
                                                  &__g_tim2_pwm_devinfo);
    }
    
    return __g_tim2_pwm_handle;
}

/** \brief tim2 pwmʵ�����ʼ�� */
void am_zlg116_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim2_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim2_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM3 ����
 ******************************************************************************/

/** \brief TIM3����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim3_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim3_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��3 */
    am_zlg116_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, __TIM3_CH1_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, __TIM3_CH2_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief ͨ��3�������� */
    {AM_ZLG_TIM_PWM_CH3, __TIM3_CH3_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
    /** \brief ͨ��4�������� */
    {AM_ZLG_TIM_PWM_CH4, __TIM3_CH4_GPIO,  __GPIO_TIM3, __PIO_GPIO_TIM},
};

/** \brief TIM3����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    ZLG116_TIM3_BASE,                          /**< \brief TIM3�Ĵ�����Ļ���ַ    */
    CLK_TIM3,                                  /**< \brief TIM3ʱ��ID              */
    AM_NELEMENTS(__g_tim3_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                    /**< \brief PWM���ģʽ2            */
    0,                                         /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim3_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE1,                        /**< \brief ��ʱ������              */
    __zlg_plfm_tim3_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim3_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM3����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim3_pwm_dev;
static am_pwm_handle_t       __g_tim3_pwm_handle = NULL;

/** \brief tim3 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg116_tim3_pwm_inst_init (void)
{
    if (__g_tim3_pwm_handle == NULL) {
        __g_tim3_pwm_handle = am_zlg_tim_pwm_init(&__g_tim3_pwm_dev,
                                                  &__g_tim3_pwm_devinfo);
    }
    return __g_tim3_pwm_handle;
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_zlg116_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim3_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim3_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM14����
 ******************************************************************************/

/** \brief TIM14����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim14_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��14ʱ�� */
    am_clk_enable(CLK_TIM14);

    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);
}

/** \brief ���TIM14 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim14_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��14 */
    am_zlg116_clk_reset(CLK_TIM14);

    /* ����ͨ�ö�ʱ��14ʱ�� */
    am_clk_disable(CLK_TIM14);
}

/** \brief TIM14����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim14_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, __TIM14_CH1_GPIO,  __GPIO_TIM14, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM14����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim14_pwm_devinfo = {
    ZLG116_TIM14_BASE,                          /**< \brief TIM14�Ĵ�����Ļ���ַ   */
    CLK_TIM14,                                  /**< \brief TIM14ʱ��ID             */
    AM_NELEMENTS(__g_tim14_pwm_chaninfo_list) , /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim14_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE2,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim14_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim14_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM14����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim14_pwm_dev;
static am_pwm_handle_t       __g_tim14_pwm_handle = NULL;

/** \brief tim14 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg116_tim14_pwm_inst_init (void)
{
    if (__g_tim14_pwm_handle == NULL) {
        __g_tim14_pwm_handle = am_zlg_tim_pwm_init(&__g_tim14_pwm_dev,
                                                   &__g_tim14_pwm_devinfo);
    }
    return __g_tim14_pwm_handle;
}

/** \brief tim14 pwmʵ�����ʼ�� */
void am_zlg116_tim14_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim14_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim14_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM16����
 ******************************************************************************/

/** \brief TIM16����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim16_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��16ʱ�� */
    am_clk_enable(CLK_TIM16);

    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);

}

/** \brief ���TIM16 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim16_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��16 */
    am_zlg116_clk_reset(CLK_TIM16);

    /* ����ͨ�ö�ʱ��16ʱ�� */
    am_clk_disable(CLK_TIM16);
}


/** \brief TIM16����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim16_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, __TIM16_CH1_GPIO, __GPIO_TIM16_CH1, AM_GPIO_INPUT | AM_GPIO_FLOAT},
    /** \brief ͨ��1������������ */
    {AM_ZLG_TIM_PWM_CH1N, __TIM16_CH1N_GPIO, __GPIO_TIM16_CH1N, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM16����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim16_pwm_devinfo = {
    ZLG116_TIM16_BASE,                          /**< \brief TIM16�Ĵ�����Ļ���ַ   */
    CLK_TIM16,                                  /**< \brief TIM16ʱ��ID             */
    AM_NELEMENTS(__g_tim16_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim16_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE3,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim16_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim16_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM16����PWM�豸���� */
static am_zlg_tim_pwm_dev_t __g_tim16_pwm_dev;
static am_pwm_handle_t      __g_tim16_pwm_handle = NULL;

/** \brief tim16 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg116_tim16_pwm_inst_init (void)
{
    if (__g_tim16_pwm_handle == NULL) {
        __g_tim16_pwm_handle = am_zlg_tim_pwm_init(&__g_tim16_pwm_dev,
                                                   &__g_tim16_pwm_devinfo);
    }

    return __g_tim16_pwm_handle;
}

/** \brief tim16 pwmʵ�����ʼ�� */
void am_zlg116_tim16_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim16_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim16_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM17����
 ******************************************************************************/

/** \brief TIM17����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim17_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��17ʱ�� */
    am_clk_enable(CLK_TIM17);

    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);
}

/** \brief ���TIM17 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim17_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��17 */
    am_zlg116_clk_reset(CLK_TIM17);

    /* ����ͨ�ö�ʱ��17ʱ�� */
    am_clk_disable(CLK_TIM17);
}

/** \brief TIM17����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim17_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOA_7,  PIOA_7_TIM17_CH1 | PIOA_7_AF_PP, PIOA_7_GPIO | PIOA_7_INPUT_FLOAT},
    /** \brief ͨ��1������������ */
    {AM_ZLG_TIM_PWM_CH1N, PIOB_7, PIOB_7_TIM17_CH1N | PIOB_7_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM17����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim17_pwm_devinfo = {
    ZLG116_TIM17_BASE,                          /**< \brief TIM17�Ĵ�����Ļ���ַ   */
    CLK_TIM17,                                  /**< \brief TIM17ʱ��ID             */
    AM_NELEMENTS(__g_tim17_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim17_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE3,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim17_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim17_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM17����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim17_pwm_dev;
static am_pwm_handle_t       __g_tim17_pwm_handle = NULL;

/** \brief tim17 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zlg116_tim17_pwm_inst_init (void)
{
    if (__g_tim17_pwm_handle == NULL) {
        __g_tim17_pwm_handle = am_zlg_tim_pwm_init(&__g_tim17_pwm_dev,
                                                   &__g_tim17_pwm_devinfo);
    }
    return __g_tim17_pwm_handle;
}

/** \brief tim17 pwmʵ�����ʼ�� */
void am_zlg116_tim17_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim17_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim17_pwm_handle = NULL;
    }
}

/**
 * @}
 */

/* end of file */
