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
 * \brief PT100�¶�ת���㷨
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-29  tee, first implementation.
 * \endinternal
 */

#ifndef __PT100_TO_TEMPERATURE_H
#define __PT100_TO_TEMPERATURE_H

/**
 * \brief ����PT100�ĵ������ֵ����λ�����������¶�ֵ����λ���棩
 * \param[in] : PT100�Ĳ������裬��λ����
 * \return �¶�ֵ
 */
float pt100_to_temperature(float pt100);

#endif

/* end of file */

