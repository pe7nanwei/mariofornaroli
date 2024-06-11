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
 * \brief �����������ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "am_buzzer.h"
 * \endcode
 *
 * \par ʹ��ʾ��
 * \code
 * #include "am_buzzer.h"
 *
 * am_buzzer_on();      // ����������
 * am_buzzer_off();     // �رշ���������
 * am_buzzer_beep(100); // ����������100����
 *
 * \endcode
 *
 * \internal
 * \par Modification history
 * - 1.01 14-12-09  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_BUZZER_H
#define __AM_BUZZER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"
    
/**
 * \addtogroup am_if_buzzer
 * \copydoc am_buzzer.h
 * @{
 */

/**
 * \brief �򿪷���������ʼ���У�
 *
 * \retval  AM_OK     : �򿪳ɹ�
 * \retval -AM_ENODEV : �����ڷ������豸
 */ 
int am_buzzer_on(void);

/**
 * \brief �رշ�����
 *
 * \retval  AM_OK     : �رճɹ�
 * \retval -AM_ENODEV : �����ڷ������豸
 */ 
int am_buzzer_off(void);

/**
 * \brief ����������ָ��ʱ�䣨ʱ�䵥λ�����룩�����н����󷵻�
 *
 * \param[in] ms : ����ʱ��
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �����ڷ������豸
 */ 
int am_buzzer_beep(uint32_t ms);

/**
 * \brief ����������ָ��ʱ�䣨ʱ�䵥λ�����룩����������������
 *
 * \param[in] ms : ����ʱ��
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �����ڷ������豸
 */
int am_buzzer_beep_async (uint32_t ms);
 
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_BUZZER_H */

/* end of file */
