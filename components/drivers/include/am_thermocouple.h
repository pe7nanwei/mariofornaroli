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
 * \brief FM175XX�ײ�������ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-23  sky, first implementation.
 * - 1.01 17-10-31  sdq, make some changes.
 * \endinternal
 */

#ifndef __AM_THERMOCOUPLE_H
#define __AM_THERMOCOUPLE_H

#include "am_spi.h"
#include "am_types.h"
#include "am_softimer.h"
#include <stdint.h>


/*******************************************************************************
 �ȵ�ż���Ͷ���
*******************************************************************************/
#define THERMOCOUPLIE_J        0     /**< \brief J���ȵ�ż */
#define THERMOCOUPLIE_K        1     /**< \brief K���ȵ�ż */
#define THERMOCOUPLIE_T        2     /**< \brief T���ȵ�ż */
#define THERMOCOUPLIE_N        3     /**< \brief N���ȵ�ż */
#define THERMOCOUPLIE_R        4     /**< \brief R���ȵ�ż */


/**< \brief �ȵ�ż��ѹֵת�¶Ⱥ������� */
typedef am_err_t (*pf__n_v_to_temperature_t) (double ,double *);
/**< \brief �ȵ�ż�¶�ת��ѹ���� */
typedef am_err_t (*pf__n_temperature_to_v_t) (double ,double *);
/**
 * \brief  �ȵ�ż���㹫ʽ��ʼ��
 *
 */
void am_thermocouplie_init(void);
/**
 * \brief  �ȵ�ż�����ѹת�¶�
 * \param[in] type   : �ȵ�ż����
 * \param[in] voltage   : ��ѹ
 * \param[out] p_temperature   :�¶�
 */
void am_thermocouplie_v2t(uint8_t            type,
                          double             voltage,
                          double            *p_temperature);
/**
 * \brief  �ȵ�ż�����¶�ת��ѹ
 * \param[in] type   : �ȵ�ż����
 * \param[in] temperature   : �¶�
 * \param[out] p_voltage   : ��ѹ
 */
void am_thermocouplie_t2v(uint8_t            type,
                          double             temperature,
                          double            *p_voltage );

#endif
