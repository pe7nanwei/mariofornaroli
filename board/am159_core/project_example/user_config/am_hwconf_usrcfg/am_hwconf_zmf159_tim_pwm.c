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
 * \sa am_hwconf_zmf159_tim_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-24  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_gpio.h"
#include "am_zlg_tim_pwm.h"
#include "am_clk.h"
#include "am_zmf159_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_tim_pwm
 * \copydoc am_hwconf_zmf159_tim_pwm.c
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
    am_zmf159_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
static void __zlg_plfm_tim1_pwm_deinit (void)
{
    /* ��λ�߼���ʱ��1 */
    am_zmf159_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim1_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOA_8, PIOA_8_TIM1_CH1 | PIOA_8_AF_PP, PIOA_8_GPIO | PIOA_8_INPUT_FLOAT},
    /** \brief ͨ��1������������ */
    {AM_ZLG_TIM_PWM_CH1N, PIOB_13, PIOB_13_TIM1_CH1N | PIOB_13_AF_PP, PIOB_13_GPIO | PIOB_13_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, PIOA_9, PIOA_9_TIM1_CH2  | PIOA_9_AF_PP,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},
    /** \brief ͨ��2������������ */
    {AM_ZLG_TIM_PWM_CH2N, PIOB_14, PIOB_14_TIM1_CH2N | PIOB_14_AF_PP, PIOB_14_GPIO | PIOB_14_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_ZLG_TIM_PWM_CH3, PIOA_10, PIOA_10_TIM1_CH3 | PIOA_10_AF_PP, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},
    /** \brief ͨ��3������������ */
    {AM_ZLG_TIM_PWM_CH3N, PIOB_1, PIOB_1_TIM1_CH3N | PIOB_1_AF_PP, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_ZLG_TIM_PWM_CH4, PIOA_11, PIOA_11_TIM1_CH4 | PIOA_11_AF_PP, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT},
};

/** \brief TIM1����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim1_pwm_devinfo = {
    ZMF159_TIM1_BASE,                          /**< \brief TIM1�Ĵ�����Ļ���ַ    */
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
am_pwm_handle_t am_zmf159_tim1_pwm_inst_init (void)
{
    if (__g_tim1_pwm_handle == NULL) {
        __g_tim1_pwm_handle = am_zlg_tim_pwm_init(&__g_tim1_pwm_dev,
                                                  &__g_tim1_pwm_devinfo);
    }
    
    return __g_tim1_pwm_handle;
}

/** \brief tim1 pwm ʵ�����ʼ�� */
void am_zmf159_tim1_pwm_inst_deinit (am_pwm_handle_t handle)
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
    am_zmf159_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
static void __zlg_plfm_tim2_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��2 */
    am_zmf159_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim2_pwm_chaninfo_list[] = {
        /** \brief ͨ��1�������� */
        {AM_ZLG_TIM_PWM_CH1, PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_AF_PP, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},
        /** \brief ͨ��2�������� */
        {AM_ZLG_TIM_PWM_CH2, PIOA_1, PIOA_1_TIM2_CH2 | PIOA_1_AF_PP, PIOA_1_GPIO | PIOA_1_INPUT_FLOAT},
        /** \brief ͨ��3�������� */
        {AM_ZLG_TIM_PWM_CH3, PIOA_2, PIOA_2_TIM2_CH3 | PIOA_2_AF_PP, PIOA_2_GPIO | PIOA_2_INPUT_FLOAT},
        /** \brief ͨ��4�������� */
        {AM_ZLG_TIM_PWM_CH4, PIOA_3, PIOA_3_TIM2_CH4 | PIOA_3_AF_PP, PIOA_3_GPIO | PIOA_3_INPUT_FLOAT},
};

/** \brief TIM2����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim2_pwm_devinfo = {
    ZMF159_TIM2_BASE,                          /**< \brief TIM2�Ĵ�����Ļ���ַ    */
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
am_pwm_handle_t am_zmf159_tim2_pwm_inst_init (void)
{
    if (__g_tim2_pwm_handle == NULL) {
        __g_tim2_pwm_handle = am_zlg_tim_pwm_init(&__g_tim2_pwm_dev,
                                                  &__g_tim2_pwm_devinfo);
    }
    
    return __g_tim2_pwm_handle;
}

/** \brief tim2 pwmʵ�����ʼ�� */
void am_zmf159_tim2_pwm_inst_deinit (am_pwm_handle_t handle)
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
    am_zmf159_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim3_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��3 */
    am_zmf159_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim3_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOB_4,  PIOB_4_TIM3_CH1 | PIOB_4_AF_PP, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},
    /** \brief ͨ��2�������� */
    {AM_ZLG_TIM_PWM_CH2, PIOB_5,  PIOB_5_TIM3_CH2 | PIOB_5_AF_PP, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},
    /** \brief ͨ��3�������� */
    {AM_ZLG_TIM_PWM_CH3, PIOB_0,  PIOB_0_TIM3_CH3 | PIOB_0_AF_PP, PIOB_0_GPIO | PIOB_0_INPUT_FLOAT},
    /** \brief ͨ��4�������� */
    {AM_ZLG_TIM_PWM_CH4, PIOB_1,  PIOB_1_TIM3_CH4 | PIOB_1_AF_PP, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
};

/** \brief TIM3����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim3_pwm_devinfo = {
    ZMF159_TIM3_BASE,                          /**< \brief TIM3�Ĵ�����Ļ���ַ    */
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
am_pwm_handle_t am_zmf159_tim3_pwm_inst_init (void)
{
    if (__g_tim3_pwm_handle == NULL) {
        __g_tim3_pwm_handle = am_zlg_tim_pwm_init(&__g_tim3_pwm_dev,
                                                  &__g_tim3_pwm_devinfo);
    }
    return __g_tim3_pwm_handle;
}

/** \brief tim3 pwm ʵ�����ʼ�� */
void am_zmf159_tim3_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim3_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim3_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM4����
 ******************************************************************************/

/** \brief TIM4����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim4_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��4ʱ�� */
    am_clk_enable(CLK_TIM4);

    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim4_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);

    /* ����ͨ�ö�ʱ��4ʱ�� */
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim4_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOB_6,  PIOB_6_TIM4_CH1 | PIOB_6_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM4����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim4_pwm_devinfo = {
    ZMF159_TIM4_BASE,                          /**< \brief TIM4�Ĵ�����Ļ���ַ   */
    CLK_TIM4,                                  /**< \brief TIM4ʱ��ID             */
    AM_NELEMENTS(__g_tim4_pwm_chaninfo_list) , /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim4_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE2,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim4_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim4_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM4����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim4_pwm_dev;
static am_pwm_handle_t       __g_tim4_pwm_handle = NULL;

/** \brief tim4 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zmf159_tim4_pwm_inst_init (void)
{
    if (__g_tim4_pwm_handle == NULL) {
        __g_tim4_pwm_handle = am_zlg_tim_pwm_init(&__g_tim4_pwm_dev,
                                                   &__g_tim4_pwm_devinfo);
    }
    return __g_tim4_pwm_handle;
}

/** \brief tim4 pwmʵ�����ʼ�� */
void am_zmf159_tim4_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim4_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim4_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM5����
 ******************************************************************************/

/** \brief TIM5����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim5_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��5ʱ�� */
    am_clk_enable(CLK_TIM5);

    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);
}

/** \brief ���TIM5 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim5_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);

    /* ����ͨ�ö�ʱ��5ʱ�� */
    am_clk_disable(CLK_TIM5);
}

/** \brief TIM5����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim5_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOA_0,  PIOA_0_TIM5_CH1 | PIOA_0_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM5����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim5_pwm_devinfo = {
    ZMF159_TIM4_BASE,                          /**< \brief TIM5�Ĵ�����Ļ���ַ   */
    CLK_TIM5,                                  /**< \brief TIM5ʱ��ID             */
    AM_NELEMENTS(__g_tim5_pwm_chaninfo_list) , /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim5_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE2,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim5_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim5_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM5����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim5_pwm_dev;
static am_pwm_handle_t       __g_tim5_pwm_handle = NULL;

/** \brief tim14 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zmf159_tim5_pwm_inst_init (void)
{
    if (__g_tim4_pwm_handle == NULL) {
        __g_tim4_pwm_handle = am_zlg_tim_pwm_init(&__g_tim5_pwm_dev,
                                                  &__g_tim5_pwm_devinfo);
    }
    return __g_tim5_pwm_handle;
}

/** \brief tim5 pwmʵ�����ʼ�� */
void am_zmf159_tim5_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim4_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim5_pwm_handle = NULL;
    }
}

/*******************************************************************************
 * TIM8����
 ******************************************************************************/

/** \brief TIM8����PWM��� ƽ̨��ʼ�� */
static void __zlg_plfm_tim8_pwm_init (void)
{
    /* ʹ��ͨ�ö�ʱ��8ʱ�� */
    am_clk_enable(CLK_TIM8);

    /* ��λͨ�ö�ʱ��8 */
    am_zmf159_clk_reset(CLK_TIM8);
}

/** \brief ���TIM8 PWMƽ̨��ʼ�� */
static void __zlg_plfm_tim8_pwm_deinit (void)
{
    /* ��λͨ�ö�ʱ��8 */
    am_zmf159_clk_reset(CLK_TIM8);

    /* ����ͨ�ö�ʱ��8ʱ�� */
    am_clk_disable(CLK_TIM8);
}

/** \brief TIM8����PWM���ܵ�ͨ��������Ϣ�б� */
static am_zlg_tim_pwm_chaninfo_t __g_tim8_pwm_chaninfo_list[] = {
    /** \brief ͨ��1�������� */
    {AM_ZLG_TIM_PWM_CH1, PIOC_6,  PIOC_6_TIM8_CH1 | PIOC_6_AF_PP, PIOC_6_GPIO | PIOC_6_INPUT_FLOAT},
    /** \brief ͨ��1������������ */
    {AM_ZLG_TIM_PWM_CH1N, PIOA_5, PIOA_5_TIM8_CH1N | PIOA_5_AF_PP, AM_GPIO_INPUT | AM_GPIO_FLOAT},
};

/** \brief TIM8����PWM�豸��Ϣ */
static const am_zlg_tim_pwm_devinfo_t  __g_tim8_pwm_devinfo = {
    ZMF159_TIM8_BASE,                          /**< \brief TIM8�Ĵ�����Ļ���ַ   */
    CLK_TIM8,                                  /**< \brief TIM8ʱ��ID             */
    AM_NELEMENTS(__g_tim8_pwm_chaninfo_list),  /**< \brief �������ͨ������        */
    AMHW_ZLG_TIM_PWM_MODE2,                     /**< \brief PWM���ģʽ2            */
    0,                                          /**< \brief PWM����ߵ�ƽ��Ч       */
    &__g_tim8_pwm_chaninfo_list[0],            /**< \brief ͨ��������Ϣ�б�        */
    AMHW_ZLG_TIM_TYPE0,                         /**< \brief ��ʱ������              */
    __zlg_plfm_tim8_pwm_init,                  /**< \brief ƽ̨��ʼ������          */
    __zlg_plfm_tim8_pwm_deinit                 /**< \brief ƽ̨���ʼ������        */
};

/** \brief TIM8����PWM�豸���� */
static am_zlg_tim_pwm_dev_t  __g_tim8_pwm_dev;
static am_pwm_handle_t       __g_tim8_pwm_handle = NULL;

/** \brief tim8 pwmʵ����ʼ�������PWM��׼������ */
am_pwm_handle_t am_zmf159_tim8_pwm_inst_init (void)
{
    if (__g_tim8_pwm_handle == NULL) {
        __g_tim8_pwm_handle = am_zlg_tim_pwm_init(&__g_tim8_pwm_dev,
                                                   &__g_tim8_pwm_devinfo);
    }
    return __g_tim8_pwm_handle;
}

/** \brief tim8 pwmʵ�����ʼ�� */
void am_zmf159_tim8_pwm_inst_deinit (am_pwm_handle_t handle)
{
    if (__g_tim8_pwm_handle == handle) {
        am_zlg_tim_pwm_deinit(handle);
        __g_tim8_pwm_handle = NULL;
    }
}

/**
 * @}
 */

/* end of file */
