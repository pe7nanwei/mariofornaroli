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
 * \brief ZMF159 TIM���ڲ����ܵ��û������ļ�
 * \sa am_hwconf_zmf159_tim_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_zlg_tim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zmf159_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_tim_cap
 * \copydoc am_hwconf_zmf159_tim_cap.c
 * @{
 */
 
/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim1_cap_init (void)
{

    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zmf159_clk_reset(CLK_TIM1);
}

/** \brief ���TIM1ƽ̨��ʼ�� */
void __zlg_plfm_tim1_cap_deinit (void)
{

    /* ��λ�߼���ʱ��1 */
    am_zmf159_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim1_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_8,  PIOA_8_TIM1_CH1  | PIOA_8_INPUT_FLOAT,  PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_9,  PIOA_9_TIM1_CH2  | PIOA_9_INPUT_FLOAT,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},

    /** \brief ͨ��3 */
    {PIOA_10, PIOA_10_TIM1_CH3 | PIOA_10_INPUT_FLOAT, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},

    /** \brief ͨ��4 */
    {PIOA_11, PIOA_11_TIM1_CH4 | PIOA_11_INPUT_FLOAT, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT}
};

/** \brief TIM1���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim1_cap_devinfo = {
    ZMF159_TIM1_BASE,               /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_CC,                   /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                       /**< \brief TIM1ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim1_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE0,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim1_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim1_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM1���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim1_cap_dev;

/** \brief tim1 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim1_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim1_cap_dev,
                                  &__g_tim1_cap_devinfo);
}

/** \brief tim1 capʵ�����ʼ�� */
void am_zmf159_tim1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim2_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zmf159_clk_reset(CLK_TIM2);
}

/** \brief ���TIM2ƽ̨��ʼ�� */
void __zlg_plfm_tim2_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��2 */
    am_zmf159_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim2_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_INPUT_FLOAT, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_1, PIOA_1_TIM2_CH2     | PIOB_1_INPUT_FLOAT, PIOA_1_GPIO | PIOA_1_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_2, PIOA_2_TIM2_CH3     | PIOB_2_INPUT_FLOAT, PIOA_2_GPIO | PIOA_2_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOA_3, PIOA_3_TIM2_CH4     | PIOB_3_INPUT_FLOAT, PIOA_3_GPIO | PIOA_3_INPUT_FLOAT},
};

/** \brief TIM2���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim2_cap_devinfo = {
    ZMF159_TIM2_BASE,               /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                      /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                       /**< \brief TIM2ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim2_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim2_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim2_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM2���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim2_cap_dev;

/** \brief tim2 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim2_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim2_cap_dev,
                                  &__g_tim2_cap_devinfo);
}

/** \brief tim2 capʵ�����ʼ�� */
void am_zmf159_tim2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM3 ����
 ******************************************************************************/

/** \brief TIM3���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim3_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zmf159_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��3 */
    am_zmf159_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim3_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOB_4,  PIOB_4_TIM3_CH1 | PIOB_4_INPUT_FLOAT, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},

    /** \brief ͨ��2 */
    {PIOB_5,  PIOB_5_TIM3_CH2 | PIOB_5_INPUT_FLOAT, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},

    /** \brief ͨ��3 */
    {PIOB_0,  PIOB_0_TIM3_CH3 | PIOB_0_INPUT_FLOAT, PIOB_0_GPIO | PIOB_0_INPUT_FLOAT},

    /** \brief ͨ��4 */
    {PIOB_1,  PIOB_1_TIM3_CH4 | PIOB_1_INPUT_FLOAT, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
};

/** \brief TIM3���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim3_cap_devinfo = {
    ZMF159_TIM3_BASE,               /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                      /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                       /**< \brief TIM3ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim3_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim3_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim3_cap_deinit      /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM3���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim3_cap_dev;

/** \brief tim3 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim3_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim3_cap_dev,
                                  &__g_tim3_cap_devinfo);
}

/** \brief tim3 capʵ�����ʼ�� */
void am_zmf159_tim3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM4 ����
 ******************************************************************************/

/** \brief TIM4���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim4_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��4ʱ�� */
    am_clk_enable(CLK_TIM4);

    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4ƽ̨��ʼ�� */
void __zlg_plfm_tim4_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);

    /* ����ͨ�ö�ʱ��4ʱ�� */
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim4_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOB_6,  PIOB_6_TIM4_CH1 | PIOB_6_INPUT_FLOAT, PIOB_6_GPIO | PIOB_6_INPUT_FLOAT},
    /** \brief ͨ��2 */
    {PIOB_7,  PIOB_7_TIM4_CH2 | PIOB_7_INPUT_FLOAT, PIOB_7_GPIO | PIOB_7_INPUT_FLOAT},
    /** \brief ͨ��3 */
    {PIOB_8,  PIOB_8_TIM4_CH3 | PIOB_8_INPUT_FLOAT, PIOB_8_GPIO | PIOB_8_INPUT_FLOAT},
    /** \brief ͨ��4 */
    {PIOB_9,  PIOB_9_TIM4_CH4 | PIOB_9_INPUT_FLOAT, PIOB_9_GPIO | PIOB_9_INPUT_FLOAT},
};

/** \brief TIM4���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim4_cap_devinfo = {
    ZMF159_TIM4_BASE,               /**< \brief TIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                      /**< \brief TIM4�жϱ�� */
    CLK_TIM4,                       /**< \brief TIM4ʱ��ID */
    4,                              /**< \brief 4������ͨ�� */
    &__g_tim4_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE2,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim4_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim4_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM4���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim4_cap_dev;

/** \brief tim4 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim4_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim4_cap_dev,
                               &__g_tim4_cap_devinfo);
}

/** \brief tim4 capʵ�����ʼ�� */
void am_zmf159_tim4_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM5 ����
 ******************************************************************************/

/** \brief TIM5���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim5_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��5ʱ�� */
    am_clk_enable(CLK_TIM5);

    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);
}

/** \brief ���TIM5ƽ̨��ʼ�� */
void __zlg_plfm_tim5_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);

    /* ����ͨ�ö�ʱ��5ʱ�� */
    am_clk_disable(CLK_TIM5);
}

/** \brief TIM5���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim5_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOA_0,  PIOA_0_TIM5_CH1 | PIOA_0_INPUT_FLOAT, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},
};

/** \brief TIM5���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim5_cap_devinfo = {
    ZMF159_TIM5_BASE,               /**< \brief TIM5�Ĵ�����Ļ���ַ */
    INUM_TIM5,                      /**< \brief TIM5�жϱ�� */
    CLK_TIM5,                       /**< \brief TIM5ʱ��ID */
    1,                              /**< \brief 1������ͨ�� */
    &__g_tim5_cap_ioinfo_list[0],   /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE2,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim5_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim5_cap_deinit      /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM5���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim5_cap_dev;

/** \brief tim5 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim5_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim5_cap_dev,
                               &__g_tim5_cap_devinfo);
}

/** \brief tim5 capʵ�����ʼ�� */
void am_zmf159_tim5_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}


/*******************************************************************************
 * TIM8 ����
 ******************************************************************************/

/** \brief TIM8���ڲ����ܵ�ƽ̨��ʼ�� */
void __zlg_plfm_tim8_cap_init (void)
{

    /* ʹ��ͨ�ö�ʱ��8ʱ�� */
    am_clk_enable(CLK_TIM8);

    /* ��λͨ�ö�ʱ��8 */
    am_zmf159_clk_reset(CLK_TIM8);
}

/** \brief ���TIM8ƽ̨��ʼ�� */
void __zlg_plfm_tim8_cap_deinit (void)
{

    /* ��λͨ�ö�ʱ��8 */
    am_zmf159_clk_reset(CLK_TIM8);

    /* ����ͨ�ö�ʱ��8ʱ�� */
    am_clk_disable(CLK_TIM8);
}

/** \brief TIM8���ڲ����ܵ�����������Ϣ�б� */
am_zlg_tim_cap_ioinfo_t __g_tim8_cap_ioinfo_list[] = {

    /** \brief ͨ��1 */
    {PIOC_6, PIOC_6_TIM8_CH1 | PIOC_6_INPUT_FLOAT, PIOC_6_GPIO | PIOC_6_INPUT_FLOAT},
};

/** \brief TIM8���ڲ����ܵ��豸��Ϣ */
const am_zlg_tim_cap_devinfo_t  __g_tim8_cap_devinfo = {
    ZMF159_TIM8_BASE,               /**< \brief TIM8�Ĵ�����Ļ���ַ */
    INUM_TIM8_CC,                      /**< \brief TIM8�жϱ�� */
    CLK_TIM8,                       /**< \brief TIM8ʱ��ID */
    1,                              /**< \brief 1������ͨ�� */
    &__g_tim8_cap_ioinfo_list[0],  /**< \brief ����������Ϣ�б� */
    AMHW_ZLG_TIM_TYPE3,             /**< \brief ��ʱ������ */
    __zlg_plfm_tim8_cap_init,       /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim8_cap_deinit      /**< \brief ƽ̨���ʼ������ */

};

/** \brief TIM8���ڲ����ܵ��豸���� */
am_zlg_tim_cap_dev_t  __g_tim8_cap_dev;

/** \brief tim8 capʵ����ʼ�������cap��׼������ */
am_cap_handle_t am_zmf159_tim8_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim8_cap_dev,
                               &__g_tim8_cap_devinfo);
}

/** \brief tim7 capʵ�����ʼ�� */
void am_zmf159_tim8_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}


/**
 * @}
 */

/* end of file */
