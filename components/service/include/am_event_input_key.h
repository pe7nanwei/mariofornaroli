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
 * \brief ���������¼�
 *
 * \internal
 * \par Modification history
 * - 1.00 16-08-23  tee, first implementation.
 * \endinternal
 */
#ifndef __AM_EVENT_INPUT_KEY_H
#define __AM_EVENT_INPUT_KEY_H

#include "am_common.h"
#include "am_event.h"
#include "am_softimer.h"

#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * \brief ���ڰ����������û����������˽����Ա���������ڴ����
 */
typedef struct am_event_input_key_long_press {
    am_softimer_t timer;         /**< \brief �����ʱ�������ڰ���������ʱ     */
    int           key_code;      /**< \brief ��ǰ�����İ������룬-1Ϊ��Чֵ   */
    int           keep_time;     /**< \brief ������ʱ                         */
} am_event_input_key_long_press_t;

/**
 * \brief �����������ϵͳ�����Ϣ
 */
typedef struct am_event_input_key_info {

    /**
     * \brief �����೤ʱ���ʼ�ϱ����������¼�
     *
     * ���磬��Ҫ����1s��ʼ�ϱ������¼������ֵΪ 1000
     */
    int  key_long_press_time_start_ms;

    /**
     * \biref �ﵽ����ʱ���ÿ��һ����ʱ���ϱ�һ�γ����¼�
     *
     * ���磬�����������ã�
     *  - key_long_press_time_start_ms  Ϊ 1000
     *  - key_long_press_time_period_ms Ϊ 200
     *
     *  ���ʾ��������ס1s���ϱ�һ�γ����¼����Ժ�ÿ��200ms���ϱ�һ�γ����¼�
     */
    int  key_long_press_time_period_ms;

    /**
     * \brief ͬʱ�����İ���������
     *
     *  - ������֧�ְ������������ֵΪ0
     *  - ����֧�ְ������������ֵΪͬһʱ�̳�����������������ͨ��Ϊ1��
     *
     * һ������£�ͬһʱ��ֻ�᳤������������һ�㲻��ͬʱ�������������
     * ����֧��ͬʱ������������������Ϊ����������ʱ�����Ҫ���ڴ�ռ䡣
     *
     * \note ���ﲢ��֧�ֳ����İ�������������ͬʱ������������������
     */
    int  key_long_press_max_num;

    /**
     * \brief ���������ر����棬�����СΪ�� key_long_press_max_num
     *
     * �û�����趨�壬�����ڴ���䣬�����û��Գ�Ա��ֵ
     *
     * �� key_long_press_max_num Ϊ 0������֧�ֳ��������ֵΪNULL��
     */
    am_event_input_key_long_press_t *p_buf;

} am_event_input_key_info_t;

/**
 * \brief �����������ϵͳ��ʼ��
 *
 * \return ��
 *
 * \note ���������� "�����¼������" һ�����࣬�ڳ�ʼ�������������ģ��ǰ��Ӧȷ
 * ���Ѿ�ʹ�� am_event_category_input_init() ��������������¼��������ĳ�ʼ����
 */
void am_event_input_key_init (const am_event_input_key_info_t *p_info);


/**
 * \brief �ϱ����������¼����ײ㰴���������ã�������ͨ������
 *
 * ��ͨ�����ڰ������»��ͷ�ʱ����Ӧ�ϱ��¼���AMetal�ϲ㽫�ڽ��յ���������
 * �¼�ʱ����������������ʱ����ʹ���˸ù��ܣ����ڰ����ͷ�ǰ��������Ӧ��
 * ���ϱ������¼���
 *
 * ���������������ð��������������ͷţ����������ͷ��¼���������������Ӧ�ڰ�����
 * ��ʱ���� am_event_input_key_released() ������
 *
 * \param[in] key_code   : ��������
 *
 * \return ��׼�����
 */
int am_event_input_key_pressed  (int key_code);

/**
 * \brief �ϱ������ͷ��¼����ײ㰴���������ã�������ͨ������
 *
 * ��ͨ�����ڰ������»��ͷ�ʱ����Ӧ�ϱ��¼���AMetal�ϲ㽫�ڽ��յ���������
 * �¼�ʱ����������������ʱ����ʹ���˸ù��ܣ����ڰ����ͷ�ǰ��������Ӧ��
 * ���ϱ������¼���
 *
 * �ú�������ָ֪ͨ���������ͷţ��ϲ�Ӧֹͣ�ð����ĳ�����ʱ��
 *
 * \param[in] key_code   : ��������
 *
 * \return ��׼�����
 */
int am_event_input_key_released (int key_code);

/**
 * \brief �ϱ����������¼����ײ㰴���������ã��������ⰴ����������������ʱ��
 *
 * ����һЩ���ⰴ��/���̣���Ҫ����Ӽ���ģ��ʱ����ZLG72128���̣������ܲ�����
 * AMetal�ϲ���г�����ʱ����Ҫ�����������
 *
 * 1.����ģ�����ֻ���ϱ����������¼��������ϱ������ͷ��¼��������ھ��󲿷�Ӧ�ã�
 *   ���ܲ����İ������ͷţ��� �ް����ͷţ��޷��Գ�������׼ȷ��ʱ��
 *
 * 2. ����������֧�ֳ���ʱ����ZLG72128���̡�PS/2���̣�������������ʱ���䱾��ᶨ
 * ���ϱ������¼�����ʱ��AMetal�ϲ������ٶԳ������κζ��⴦��Ӧ�ò�ͬ������ʹ
 * �ó������ܣ�ֻ����������ʱ���ɾ������ģ����ɵģ�����AMetal�ϲ���롣
 *
 * \param[in] key_code  : ��������
 * \param[in] keep_time : ��������ʱ�䣨��λ��ms����������ģ�鱾��֧�ֳ������ܣ�
 * ���ֵΪ����ģ�鱾��ļ�ʱ�����0Ϊ�״ΰ��£���������ģ�鱾��֧�ֳ������ܣ�
 * ���ֵΪ-1��
 *
 * \return ��׼�����
 */
int am_event_input_key_pressed_without_timing (int key_code, int keep_time);


#ifdef __cplusplus
}
#endif

#endif /* __AM_EVENT_INPUT_KEY_H */
