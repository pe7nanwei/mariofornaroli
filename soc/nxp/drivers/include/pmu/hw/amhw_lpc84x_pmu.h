/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC84X PMU Ӳ�������ӿ�����
 * 
 * 1. ����ģʽ���ƣ�
 * 2. �͹����������ƣ�
 * 3. ���ͨ�ñ��ݼĴ���������ȵ���ģʽ�±������ݣ�
 * 4. ���¶ȷ�Χ(-40��~ 105��)��Vdd��ѹֵ��Χ(1.8V~3.35V)��������������
 * ע�⣺
 *     ��ȵ���ģʽ������������ܹ���(�����ֲ�˵��)��
 *         - �¶�С�ڵ���25�ȣ�Vdd��ѹֵ����3.4V
 *         - �¶ȴ���25�ȣ�Vdd��ѹֵ����3.35V
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-01  sky, modified.
 * - 1.00 15-07-13  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC84X_PMU_H
#define __AMHW_LPC84X_PMU_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** 
 * \addtogroup amhw_lpc84x_if_pmu
 * \copydoc amhw_lpc84x_pmu.h
 * @{
 */

#include "hw/amhw_lpc82x_pmu.h"

/**
 * \brief �͹���ģʽ����
 *
 * \param[in] p_hw_pmu : ָ��PMU��Դ���ƼĴ������ָ��
 * \param[in] mode     : ��Ҫ���õ�ģʽ
 *
 * \return AM_ERROR    : ����ʧ��
 *         AM_OK       : ���óɹ�
 */
int amhw_lpc84x_lowpower_mode_set (amhw_lpc82x_pmu_t       *p_hw_pmu,
                                   amhw_lpc82x_pmu_pm_src_t mode);


/**
 * @} amhw_lpc82x_if_pmu
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC84X_PMU_H */

/* end of file */
