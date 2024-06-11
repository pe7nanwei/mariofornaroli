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
 * \brief  LED��׼�ӿ�
 * 
 * \par ʹ��ʾ��
 * \code
 * #include "am_led.h"
 *
 * am_led_set(0, AM_TRUE);     // ����LED0
 * am_led_set(0, AM_FALSE);    // Ϩ��LED0
 *
 * am_led_on(1);               // ����LED1
 * am_led_off(1);              // Ϩ��LED1
 *
 * \endcode
 *
 * \internal
 * \par Modification history
 * - 1.01 14-12-01  tee, add the LED to the standard interface
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */

#ifndef __AM_LED_H
#define __AM_LED_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"


/**
 * \addtogroup am_if_led
 * \copydoc am_led.h
 * @{
 */

/**
 * \brief ����LED��״̬
 *
 * \param[in] led_id : LED���, ���ñ���ɾ���ƽ̨����
 * \param[in] state  : AM_TRUE : LED����AM_FALSE : LED��
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �豸������
 */
int am_led_set (int led_id, am_bool_t state);

/**
 * \brief ����LED
 *
 * \param[in] led_id : LED���
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �豸������
 */
int am_led_on(int led_id);

/**
 * \brief Ϩ��LED
 *
 * \param[in] led_id : LED���
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �豸������
 */
int am_led_off(int led_id);

/**
 * \brief ��תָ��LED��״̬
 *
 * \param[in] led_id : LED���
 *
 * \retval  AM_OK     : �����ɹ�
 * \retval -AM_ENODEV : �豸������
 */
int am_led_toggle(int led_id);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LED_H */

/* end of file */
