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
 * \brief IWDG�����ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  sdy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_IWDG_H
#define __AMHW_ZMF159_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_zlg_iwdg.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zmf159_if_iwdg
 * \copydoc amhw_zmf159_iwdg.h
 * @{
 */

/**
 * \brief IWDG�Ĵ�����ṹ��
 */
typedef struct amhw_zmf159_iwdg {
    amhw_zlg_iwdg_t zlg_reg;
    __IO uint32_t   ctrl;
} amhw_zmf159_iwdg_t;

typedef enum amhw_zmf159_iwdg_ctrl {
    ZMF159_IWDG_REST  = 0,         /*< \brief IWDG����������λ  */
    ZMF159_IWDG_IRQ   = 1,         /*< \brief IWDG���������ж�  */
} amhw_zmf159_iwdg_ctrl_t;

/**
 * \brief IWDG�������ѡ��
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 * \param[in] flag      : �������ѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_iwdg_overflow_set (amhw_zmf159_iwdg_t      *p_hw_iwdg,
                                    amhw_zmf159_iwdg_ctrl_t  flag)
{
    p_hw_iwdg->ctrl |= (flag << 0);
}

/**
 * \brief IWDG����ж�
 *
 * \param[in] p_hw_iwdg : ָ��IWDG�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_iwdg_irq_clear (amhw_zmf159_iwdg_t *p_hw_iwdg)
{
    p_hw_iwdg->ctrl |= (1 << 1);
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __AMHW_ZMF159 _IWDG_H */

#endif

/* end of file */
