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
 * \brief ��Դ����ӿ�
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_PWR_H
#define __AMHW_ZMF159_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_zlg_pwr.h"

/**
 * \addtogroup amhw_zmf159_if_pwr
 * \copydoc amhw_zmf159_pwr.h
 * @{
 */


/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef amhw_zlg_pwr_t amhw_zmf159_pwr_t;

typedef enum amhw_zmf159_pwr_vos {
    NORMAL_MODE       = 1,            /**< \brief ͨ��ģʽ */
    HEIGH_PROPERTY    = 3             /**< \brief ������ģʽ */
} amhw_zmf159_pwr_vos_t;

/**
 * \brief ��ѹѡ��ʹ��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_pwr_odsw_enable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr |= (1 << 17);
}

/**
 * \brief ��ѹѡ��δʹ��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_pwr_odsw_disable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr &= ~(1 << 17);
}

/**
 * \brief ��ѹʹ��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_pwr_od_enable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr |= (1 << 16);
}

/**
 * \brief ��ѹδʹ��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_pwr_od_disable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr &= ~(1 << 16);
}

/**
 * \brief ��������ѹ������ã�����PLLδʹ��ʱ���ã���PLLʹ�ܺ󣬸�λ��������
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 * \param[in] mode      ������ģʽ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_pwr_vos_set (amhw_zmf159_pwr_t     *p_hw_pwr,
                              amhw_zmf159_pwr_vos_t  mode)
{
    p_hw_pwr->cr |= ((mode & 0x3) << 14);
}

/**
 * \brief ��ѹģʽѡ��׼��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return AM_TRUE  ��׼�����
 *         AM_FALSE ��û��׼�����
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_odswrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 17) & 0x1);
}

/**
 * \brief ��ѹģʽ׼��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return AM_TRUE  ��׼�����
 *         AM_FALSE ��û��׼�����
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_odrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 16) & 0x1);
}

/**
 * \brief ��ѹ���������ѡ��׼��
 *
 * \param[in] p_hw_pwr  �� ָ���Դ���ƼĴ������ָ��
 *
 * \return AM_TRUE  ��׼�����
 *         AM_FALSE ��û��׼�����
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_vosrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 14) & 0x1);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_PWR_H */

/* end of file */
