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
 * \brief ������ϵͳͨ�ñ�׼�ӿ�
 *
 *    ��ǰ���������豸�ӿڡ�
 *
 *    todo: �������ͨ�ýӿڴ�������ꡢ���̡�ҡ�ˡ������豸��
 *
 * \par ��ʾ��
 * \code
 *
 * #include "am_input.h"
 *
 * (1) ���������������ϱ������¼�����������ʵ�֣��û�������ģ��� ���磺
 *
 *      - ��⵽ KEY_1 �����£�am_event_input_key_pressed(KEY_1);
 *      - ��⵽ KEY_1 ���ͷţ�am_event_input_key_released(KEY_1);
 *
 * (2) Ӧ�ó�����ʹ�ûص������������¼�
 *
 * static void __input_key_proc (
 *      void *p_arg, int key_code, int key_state, int keep_time)
 * {
 *      if (key_code == KEY_1) {
 *           if (key_state == AM_INPUT_KEY_STATE_PRESSED) {
 *               am_led_on(0);
 *
 *               if (keep_time >= 3000) {           // ��������ʱ��ﵽ 3s
 *                   // ����3s�Ĵ������磬�ػ���
 *               }
 *
 *           } else if (key_state == AM_INPUT_KEY_STATE_RELEASED){
 *               am_led_off(0);
 *           }
 *      }
 * }
 *
 * int am_main (void)
 * {
 *     static am_input_key_handler_t key_handler;
 *
 *     am_input_key_handler_register(&key_handler, __input_key_proc, NULL);
 * }
 *
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 17-05-15  tee, first implementation.
 * \endinternal
 */


#ifndef __AM_INPUT_H
#define __AM_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_input
 * \copydoc am_input.h
 * @{
 */
#include "am_common.h"
#include "am_event.h"
#include "am_input_code.h"

/**
 * \name ������״̬
 * @{
 */

#define  AM_INPUT_KEY_STATE_PRESSED    0       /**< \brief ��������  */
#define  AM_INPUT_KEY_STATE_RELEASED   1       /**< \brief �����ͷ�  */

/** @} */

/**
 * \brief �����ص���������
 *
 * \param[in] p_arg      : �û����ݣ�ע��ʱ�趨���û�����
 * \param[in] key_code   : ��������
 * \param[in] key_state  : ����״̬��AM_INPUT_KEY_STATE_PRESSED
 * \param[in] keep_time  : ״̬����ʱ�䣬���ڰ���������ʱ�䵥λΪ��ms��
 *
 * \note ״̬����ʱ�����ڰ��������������״ΰ��£��¼�ΪAM_INPUT_KEY_STATE_PRESSED
 * keep_timeΪ0��������һֱ���֣�������һ����Ƶ���ϱ� AM_INPUT_KEY_STATE_PRESSED
 * �¼���keep_time ��ʾ�������±��ֵ�ʱ�䡣�ر�أ�����������֧�ֳ�������
 * keep_time ʼ��Ϊ -1��
 */
typedef void (*am_input_key_cb_t) (void     *p_arg,
                                   int       key_code,
                                   int       key_state,
                                   int       keep_time);

/**
 * \brief ����������
 */
typedef struct am_input_key_handler {
    am_event_handler_t    ev_handler;            /**< \brief ͨ���¼�������  */
    am_input_key_cb_t     pfn_cb;                /**< \brief �ص�����  */
    void                 *p_usr_data;            /**< \brief �ص������û����� */
} am_input_key_handler_t;

/**
 * \brief ע��һ������������
 *
 * ���������»��ͷ�ʱ���������  pfn_cb ָ��Ļص�����
 *
 * \param[in] p_handler ��  ����������
 * \param[in] pfn_cb    ��  ��������ص�����
 * \param[in] p_arg     : ��������ص������û�����
 *
 * \retval   AM_OK      ע��ɹ�
 * \retval  -AM_EINVAL  ��������
 */
int am_input_key_handler_register (am_input_key_handler_t  *p_handler,
                                   am_input_key_cb_t        pfn_cb,
                                   void                    *p_arg);

/**
 * \brief ע��һ������������
 *
 * \param[in] p_handler ��  ����������
 *
 * \retval   AM_OK      ע��ɹ�
 * \retval  -AM_ENODEV  ע��ʧ�ܣ����������������ڣ���δע�ᣩ
 * \retval  -AM_EINVAL  ��������
 */
int am_input_key_handler_unregister (am_input_key_handler_t *p_handler);


/** @} am_if_input */

#ifdef __cplusplus
}
#endif

#endif /* __AM_INPUT_H */

/* end of file */
