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
 * \brief ZMF159 TIM ��ʱ�����û������ļ�
 * \sa am_hwconf_zmf159_tim_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "am_zlg_tim_timing.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_tim_timing
 * \copydoc am_hwconf_zmf159_tim_timing.c
 * @{
 */

/*******************************************************************************
 * TIM1 ����
 ******************************************************************************/

/** \brief TIM1 ƽ̨��ʼ�� */
void __zlg_plfm_tim1_timing_init (void)
{

    /* ʹ�ܸ߼���ʱ��1ʱ�� */
    am_clk_enable(CLK_TIM1);

    /* ��λ�߼���ʱ��1 */
    am_zmf159_clk_reset(CLK_TIM1);
}

/** \brief ��� TIM1 ƽ̨��ʼ�� */
void __zlg_plfm_tim1_timing_deinit (void)
{

    /* ��λ�߼���ʱ��1 */
    am_zmf159_clk_reset(CLK_TIM1);

    /* ���ܸ߼���ʱ��1ʱ�� */
    am_clk_disable(CLK_TIM1);
}


/** \brief TIM1 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim1_timing_devinfo = {
    ZMF159_TIM1_BASE,                /**< \brief TIM1�Ĵ�����Ļ���ַ */
    INUM_TIM1_UP,                    /**< \brief TIM1�жϱ�� */
    CLK_TIM1,                        /**< \brief TIM1ʱ��ID */
    AMHW_ZLG_TIM_TYPE0,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim1_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim1_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM1 �豸���� */
am_zlg_tim_timing_dev_t  __g_tim1_timing_dev;

/** \brief ��ʱ��TIM1 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim1_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim1_timing_dev,
                                  &__g_tim1_timing_devinfo);
}

/** \brief TIM1 Timingʵ�����ʼ�� */
void am_zmf159_tim1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM2 ����
 ******************************************************************************/

/** \brief TIM2 ƽ̨��ʼ�� */
void __zlg_plfm_tim2_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��2ʱ�� */
    am_clk_enable(CLK_TIM2);

    /* ��λͨ�ö�ʱ��2 */
    am_zmf159_clk_reset(CLK_TIM2);
}

/** \brief ��� TIM2 ƽ̨��ʼ�� */
void __zlg_plfm_tim2_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��2 */
    am_zmf159_clk_reset(CLK_TIM2);

    /* ����ͨ�ö�ʱ��2ʱ�� */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim2_timing_devinfo = {
    ZMF159_TIM2_BASE,                /**< \brief TIM2�Ĵ�����Ļ���ַ */
    INUM_TIM2,                       /**< \brief TIM2�жϱ�� */
    CLK_TIM2,                        /**< \brief TIM2ʱ��ID */
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim2_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim2_timing_deinit    /**< \brief ƽ̨������ʼ������ */
};

/** \brief TIM2 �豸���� */
am_zlg_tim_timing_dev_t  __g_tim2_timing_dev;

/** \brief TIM2 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim2_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim2_timing_dev,
                                  &__g_tim2_timing_devinfo);
}

/** \brief TIM2 Timingʵ�����ʼ�� */
void am_zmf159_tim2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}


/*******************************************************************************
 * TIM3����
 ******************************************************************************/
/** \brief TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��3ʱ�� */
    am_clk_enable(CLK_TIM3);

    /* ��λͨ�ö�ʱ��3 */
    am_zmf159_clk_reset(CLK_TIM3);
}

/** \brief ���TIM3ƽ̨��ʼ�� */
void __zlg_plfm_tim3_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��3 */
    am_zmf159_clk_reset(CLK_TIM3);

    /* ����ͨ�ö�ʱ��3ʱ�� */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3 �豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim3_timing_devinfo = {
    ZMF159_TIM3_BASE,                /**< \brief TIM3�Ĵ�����Ļ���ַ */
    INUM_TIM3,                       /**< \brief TIM3�жϱ�� */
    CLK_TIM3,                        /**< \brief TIM3ʱ��ID */
    AMHW_ZLG_TIM_TYPE1,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim3_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim3_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM3�豸���� */
am_zlg_tim_timing_dev_t  __g_tim3_timing_dev;

/** \brief TIM3 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim3_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim3_timing_dev,
                                  &__g_tim3_timing_devinfo);
}

/** \brief TIM3 Timingʵ�����ʼ�� */
void am_zmf159_tim3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM4����
 ******************************************************************************/
/** \brief TIM4ƽ̨��ʼ�� */
void __zlg_plfm_tim4_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��4ʱ�� */
    am_clk_enable(CLK_TIM4);

    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);
}

/** \brief ���TIM4ƽ̨��ʼ�� */
void __zlg_plfm_tim4_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��4 */
    am_zmf159_clk_reset(CLK_TIM4);

    /* ����ͨ�ö�ʱ��4ʱ�� */
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim4_timing_devinfo = {
    ZMF159_TIM4_BASE,                 /**< \brief TIM4�Ĵ�����Ļ���ַ */
    INUM_TIM4,                        /**< \brief TIM4�жϱ�� */
    CLK_TIM4,                         /**< \brief TIM4ʱ��ID */
    AMHW_ZLG_TIM_TYPE1,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim4_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim4_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM4�豸���� */
am_zlg_tim_timing_dev_t  __g_tim4_timing_dev;

/** \brief TIM4 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim4_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim4_timing_dev,
                                  &__g_tim4_timing_devinfo);
}

/** \brief TIM4 Timingʵ�����ʼ�� */
void am_zmf159_tim4_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM5����
 ******************************************************************************/
/** \brief TIM5ƽ̨��ʼ�� */
void __zlg_plfm_tim5_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��5ʱ�� */
    am_clk_enable(CLK_TIM5);

    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);
}

/** \brief ���TIM5ƽ̨��ʼ�� */
void __zlg_plfm_tim5_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��5 */
    am_zmf159_clk_reset(CLK_TIM5);

    /* ����ͨ�ö�ʱ��5ʱ�� */
    am_clk_disable(CLK_TIM5);
}

/** \brief TIM5�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim5_timing_devinfo = {
    ZMF159_TIM5_BASE,                 /**< \brief TIM5�Ĵ�����Ļ���ַ */
    INUM_TIM5,                        /**< \brief TIM5�жϱ�� */
    CLK_TIM5,                         /**< \brief TIM5ʱ��ID */
    AMHW_ZLG_TIM_TYPE1,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim5_timing_init,      /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim5_timing_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM5�豸���� */
am_zlg_tim_timing_dev_t  __g_tim5_timing_dev;

/** \brief TIM5 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim5_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim5_timing_dev,
                                  &__g_tim5_timing_devinfo);
}

/** \brief TIM5 Timingʵ�����ʼ�� */
void am_zmf159_tim5_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM6����
 ******************************************************************************/

/** \brief TIM6ƽ̨��ʼ�� */
void __zlg_plfm_tim6_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��6ʱ�� */
    am_clk_enable(CLK_TIM6);

    /* ��λͨ�ö�ʱ��6 */
    am_zmf159_clk_reset(CLK_TIM6);
}

/** \brief ���TIM6ƽ̨��ʼ�� */
void __zlg_plfm_tim6_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��6 */
    am_zmf159_clk_reset(CLK_TIM6);

    /* ����ͨ�ö�ʱ��6ʱ�� */
    am_clk_disable(CLK_TIM6);
}

/** \brief TIM6�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim6_timing_devinfo = {
    ZMF159_TIM6_BASE,                 /**< \brief TIM6�Ĵ�����Ļ���ַ */
    INUM_TIM6,                        /**< \brief TIM6�жϱ�� */
    CLK_TIM6,                         /**< \brief TIM6ʱ��ID */
    AMHW_ZLG_TIM_TYPE3,               /**< \brief ��ʱ������ */
    __zlg_plfm_tim6_timing_init,      /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim6_timing_deinit     /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM6�豸���� */
am_zlg_tim_timing_dev_t  __g_tim6_timing_dev;

/** \brief ��ʱ��TIM6 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim6_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim6_timing_dev,
                                  &__g_tim6_timing_devinfo);
}

/** \brief TIM6 Timingʵ�����ʼ�� */
void am_zmf159_tim6_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM7����
 ******************************************************************************/

/** \brief TIM7ƽ̨��ʼ�� */
void __zlg_plfm_tim7_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��7ʱ�� */
    am_clk_enable(CLK_TIM7);

    /* ��λͨ�ö�ʱ��7 */
    am_zmf159_clk_reset(CLK_TIM7);
}

/** \brief ���TIM7ƽ̨��ʼ�� */
void __zlg_plfm_tim7_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��7 */
    am_zmf159_clk_reset(CLK_TIM7);

    /* ����ͨ�ö�ʱ��7ʱ�� */
    am_clk_disable(CLK_TIM7);
}

/** \brief TIM7�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim7_timing_devinfo = {
    ZMF159_TIM7_BASE,                /**< \brief TIM7�Ĵ�����Ļ���ַ */
    INUM_TIM7,                       /**< \brief TIM7�жϱ�� */
    CLK_TIM7,                        /**< \brief TIM7ʱ��ID */
    AMHW_ZLG_TIM_TYPE3,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim7_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim7_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM7�豸���� */
am_zlg_tim_timing_dev_t  __g_tim7_timing_dev;

/** \brief ��ʱ��TIM7 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim7_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim7_timing_dev,
                                     &__g_tim7_timing_devinfo);
}

/** \brief TIM7 Timingʵ�����ʼ�� */
void am_zmf159_tim7_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM8����
 ******************************************************************************/

/** \brief TIM8ƽ̨��ʼ�� */
void __zlg_plfm_tim8_timing_init (void)
{

    /* ʹ��ͨ�ö�ʱ��8ʱ�� */
    am_clk_enable(CLK_TIM8);

    /* ��λͨ�ö�ʱ��8 */
    am_zmf159_clk_reset(CLK_TIM8);
}

/** \brief ���TIM8ƽ̨��ʼ�� */
void __zlg_plfm_tim8_timing_deinit (void)
{

    /* ��λͨ�ö�ʱ��7 */
    am_zmf159_clk_reset(CLK_TIM8);

    /* ����ͨ�ö�ʱ��8ʱ�� */
    am_clk_disable(CLK_TIM8);
}

/** \brief TIM8�豸��Ϣ */
const am_zlg_tim_timing_devinfo_t  __g_tim8_timing_devinfo = {
    ZMF159_TIM8_BASE,                /**< \brief TIM8�Ĵ�����Ļ���ַ */
    INUM_TIM8_UP,                    /**< \brief TIM8�жϱ�� */
    CLK_TIM8,                        /**< \brief TIM8ʱ��ID */
    AMHW_ZLG_TIM_TYPE0,              /**< \brief ��ʱ������ */
    __zlg_plfm_tim7_timing_init,     /**< \brief ƽ̨��ʼ������ */
    __zlg_plfm_tim7_timing_deinit    /**< \brief ƽ̨���ʼ������ */
};

/** \brief TIM8�豸���� */
am_zlg_tim_timing_dev_t  __g_tim8_timing_dev;

/** \brief ��ʱ��TIM8 Timingʵ����ʼ�������Timer��׼������ */
am_timer_handle_t am_zmf159_tim8_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim8_timing_dev,
                                  &__g_tim8_timing_devinfo);
}

/** \brief TIM8 Timingʵ�����ʼ�� */
void am_zmf159_tim8_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
