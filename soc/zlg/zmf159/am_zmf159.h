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
 * \brief ZMF159 оƬ�������ͷ�ļ�����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AM_ZMF159_H
#define __AM_ZMF159_H

#ifdef __cplusplus
extern "C" {
#endif

/** \brief оƬ���Ŷ��� */
#include "zmf159_pin.h"

/** \brief оƬ�жϱ�Ŷ��� */
#include "zmf159_inum.h"

/** \brief оƬ����Ĵ�����ַ���� */
#include "zmf159_regbase.h"

/** \brief оƬ����ӳ�� */
#include "zmf159_periph_map.h"

/** \brief ʱ��ID���� */
#include "zmf159_clk.h"

/** \brief DMAͨ���Ŷ��� */
//#include "zlg217_dma_chan.h"

/**
 * \name Cortex-M3 �ں˴���������������
 * @{
 */
#ifndef AM_CORTEX_M3
#define AM_CORTEX_M3             1
#endif

#if defined AM_CORTEX_M3

#define __MPU_PRESENT            0  /**< \brief M3 ���� MPU */
#define __NVIC_PRIO_BITS         4  /**< \brief M3 ��Ϊ 4 */
#define __Vendor_SysTickConfig   0  /**< \brief ����Ϊ 1 �������� SysTick */

#include "core_cm3.h"

#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZMF159_H */

/* end of file */
