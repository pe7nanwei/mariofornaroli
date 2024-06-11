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
 * \brief CPU ϵͳ�δ�ʱ��(SYSTICK) �����ӿ�
 *
 * 1. �򵥵�24λ�ݼ���ʱ����
 * 2. ʹ��ר�õ��쳣�����š�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-18  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_ARM_SYSTICK_H
#define __AMHW_ARM_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_arm_if_systick
 * \copydoc amhw_arm_systick.h
 * @{
 */

/**
 * \brief SYSTICK �Ĵ�����ṹ��
 */
typedef struct amhw_arm_systick {
    __IO uint32_t ctrl;       /**< \brief SysTick ���ƺ�״̬�Ĵ��� */
    __IO uint32_t load;       /**< \brief SysTick ��װ��ֵ�Ĵ��� */
    __IO uint32_t val;        /**< \brief SysTick ��ǰ��ʱ��ֵ�Ĵ��� */
    __I  uint32_t calib;      /**< \brief SysTick У׼�Ĵ��� */
} amhw_arm_systick_t;

#ifndef AMHW_ARM_SYSTICK
#define AMHW_ARM_SYSTICK  ((amhw_arm_systick_t *)0xE000E010UL)    /**< SCB  SysTick����ַ */
#endif


/**
 * \name Systick���ƼĴ����ĺ궨��
 * @{
 */

/** \brief Systick���ֵ */
#define AMHW_ARM_SYSTICK_INVAL_MAX                     (0xFFFFFFUL)

/** \brief Systickʹ�� */
#define AMHW_ARM_SYSTICK_CONFIG_ENABLE                 (1 << 0)

/** \brief Systick�ж�ʹ�� */
#define AMHW_ARM_SYSTICK_CONFIG_TICKINT                (1 << 1)

/** \brief Systickʱ��ԴΪϵͳʱ�� */
#define AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM          (1 << 2)

/** \brief Systickʱ��Դ��Ϊϵͳʱ�ӵ�1/2 */
#define AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM_HALF     (0 << 2)

/**
 * \brief Systickʱ��ԴΪSystickʱ�ӷ�Ƶ�������ʱ��
 */
#define AMHW_ARM_SYSTICK_CONFIG_CLKSRC_MAINCLK_BY_DIV  (0 << 2)

/** @} */

/**
 * \brief ʹ��Systick����ʼ���¼�����
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_arm_systick_enable (amhw_arm_systick_t *p_hw_systick)
{
    p_hw_systick->ctrl |= AMHW_ARM_SYSTICK_CONFIG_ENABLE;
}

/**
 * \brief ����Systick��ֹͣ���¼�����
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_arm_systick_disable (amhw_arm_systick_t *p_hw_systick)
{
    p_hw_systick->ctrl &= ~AMHW_ARM_SYSTICK_CONFIG_ENABLE;
}

/**
 * \brief ʹ��Systick�ж�
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_arm_systick_int_enable (amhw_arm_systick_t *p_hw_systick)
{
    p_hw_systick->ctrl |= AMHW_ARM_SYSTICK_CONFIG_TICKINT;
}

/**
 * \brief ����Systick�ж�
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_arm_systick_int_disable (amhw_arm_systick_t *p_hw_systick)
{
    p_hw_systick->ctrl &= ~AMHW_ARM_SYSTICK_CONFIG_TICKINT;
}

/**
 * \brief ���Systick����ֵ�Ƿ�ݼ���0
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \retval AM_TRUE  : Systick����ֵ�ݼ���0
 * \retval AM_FALSE : Systick����ֵδ�ݼ���0
 */
am_static_inline
am_bool_t amhw_arm_systick_flag_check (amhw_arm_systick_t *p_hw_systick)
{
    return (am_bool_t)((p_hw_systick->ctrl & (1 << 16)) != 0);
}

/**
 * \brief ����Systick
 *
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \param[in] flags        : ���������е�����ֵ�����ж����Ļ�ֵ
 *                            - AMHW_ARM_SYSTICK_CONFIG_ENABLE
 *                            - AMHW_ARM_SYSTICK_CONFIG_TICKINT
 *                            - AMHW_ARM_SYSTICK_CONFIG_CLKSRC_SYSTEM
 *                            - AMHW_ARM_SYSTICK_CONFIG_CLKSRC_MAINCLK_BY_DIV
 * \return ��
 */
am_static_inline
void amhw_arm_systick_config (amhw_arm_systick_t *p_hw_systick, uint32_t flags)
{
    p_hw_systick->ctrl = flags;
}

/**
 * \brief ����Systick���Զ���װ��ֵ
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \param[in] value        : �Զ���װ��ֵ(���Ϊ0xFFFFFF)
 * \return ��
 */
am_static_inline
void amhw_arm_systick_reload_val_set (amhw_arm_systick_t *p_hw_systick, uint32_t value)
{
    p_hw_systick->load = value & 0xFFFFFF;
}

/**
 * \brief ��ȡSystick���Զ���װ��ֵ
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return �Զ�װ��ֵ
 */
am_static_inline
uint32_t amhw_arm_systick_reload_val_get (amhw_arm_systick_t *p_hw_systick)
{
    return ((p_hw_systick->load) & 0xFFFFFF);
}

/**
 * \brief ����Systick��ǰ�ļ���ֵ
 *
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \param[in] value        : Systick��ǰ�ļ���ֵ
 *
 * \return ��
 *
 * \note д�κ�ֵ��������Systick��ǰ�ļ���ֵ����������ƼĴ����е�COUNTFLAG��־��
 */
am_static_inline
void amhw_arm_systick_val_set (amhw_arm_systick_t *p_hw_systick, uint32_t value)
{
    p_hw_systick->val = value & 0xFFFFFF;
}

/**
 * \brief ��ȡSystick��ǰ�ļ���ֵ
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return Systick��ǰ�ļ���ֵ
 */
am_static_inline
uint32_t amhw_arm_systick_val_get (amhw_arm_systick_t *p_hw_systick)
{
    return (p_hw_systick->val & 0xFFFFFF);
}

/**
 * \brief ��ȡSystick��У׼ֵ
 * \param[in] p_hw_systick : ָ��Systick�Ĵ������ָ��
 * \return Systick��У׼ֵ
 */
am_static_inline
uint32_t amhw_arm_systick_calib_val_get (amhw_arm_systick_t *p_hw_systick)
{
    return p_hw_systick->calib;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_ARM_SYSTICK_H */

/*end of file */
