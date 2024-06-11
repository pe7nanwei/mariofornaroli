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
 * \brief ����ͨ�ö�ʱ��ʵ�ֵ���ʱ����
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-22  pea, first implementation
 * \endinternal
 */
#ifndef __AM_BSP_DELAY_TIMER_H
#define __AM_BSP_DELAY_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"

/**
 * \brief ��ʱ������ʼ��
 *
 * ��ʱͨ����ȡ��ǰcountֵʵ�֣�����Զ�ʱ���������κθı䣬��ˣ�������ʱ�Ķ�ʱ
 * ��ͨ�����������������ܣ����磬���ڿ��� 1KHz �������Զ�ʱ�жϣ�����ϵͳ���ġ�
 *
 * ����ʱ�׶β���ر��жϣ���ˣ�����ʱ�ڼ�������жϣ��жϻ�����ִ�У��ҿ���
 * ������ʱʱ���ӳ���
 */
void am_bsp_delay_timer_init (am_timer_handle_t timer_handle, uint8_t chan);

#ifdef __cplusplus
}
#endif

#endif /* __AM_BSP_DELAY_TIMER_H */

/* end of file */
