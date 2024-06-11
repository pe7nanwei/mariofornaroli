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
 * \brief ʱ���׼����
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_time.h
 *
 * \par ʹ��ʾ��
 * \code
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 13-09-06  zen, first implementation
 * \endinternal
 */

#ifndef __AM_TIME_H
#define __AM_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "time.h"

/**
 * \addtogroup am_if_time
 * \copydoc am_time.h
 * @{
 */

/** \brief ����ʱ�䣬��1970 �� 1 �� 1 �� 0 ʱ 0 �� 0 �� ���������� */
typedef time_t am_time_t;

/** \brief ��ȷ����ʱ�䣬����������ʾ������ʱ�� */
typedef struct am_timespec {
    am_time_t       tv_sec;   /**< \brief �����   */
    unsigned long   tv_nsec;  /**< \brief ������� */
} am_timespec_t;

/**
 * \brief ϸ��ʱ��, ���ṹ���� <time.h> �е� struct tm ����, ��ʹ�� <time.h> ��
 * �ĸ��������������� (ʹ��ǿ��ת�� (struct tm *)xx )
 */
typedef struct am_tm {
    int tm_sec;     /**< \brief seconds after the minute     - [0, 59]  */
    int tm_min;     /**< \brief minutes after the hour       - [0, 59]  */
    int tm_hour;    /**< \brief hours after midnight         - [0, 23]  */
    int tm_mday;    /**< \brief day of the month             - [1, 31]  */
    int tm_mon;     /**< \brief months since January         - [0, 11]  */
    int tm_year;    /**< \brief years since 1900                        */
    int tm_wday;    /**< \brief days since Sunday            - [0, 6]   */
    int tm_yday;    /**< \brief days since January 1         - [0, 365] */
    int tm_isdst;   /**< \brief Daylight Saving Time flag               */
} am_tm_t;

/**
 * \brief ��ȡ��ǰ����ʱ�� (�� <time.h> �� time() ��Ϊ��ͬ)
 *
 * \note ��ʹ�� am_time_to_tm() ������ʱ��ת��Ϊϸ��ʱ��
 *
 * \param[out] p_time   ����ΪNULL, �򷵻�����ʱ��
 *
 * \return ��ǰ����ʱ��
 *
 * \par ʾ��
 * \code
 * #include "am_time.h"
 *
 * am_time_t time;      // ����ʱ��
 * am_tm_t   tm;        // ϸ��ʱ��
 *
 * time = am_time(NULL);                            // �õ�����ʱ��
 * printf("%s\n", ctime(const time_t *)&time);      // ��ӡ����ʱ��
 *
 * am_time_to_tm(time, &tm);                        // ������ʱ��ת��Ϊϸ��ʱ��
 * printf("%s\n", asctime(const struct tm *)&tm);   // ��ӡϸ��ʱ��
 * \endcode
 */
am_time_t am_time(am_time_t *p_time);

/**
 * \brief ��ȡ��ǰ����ʱ�� (�롢�����ʾ)
 *
 * ��� am_time(), am_tm_get(), �������ܶ��ȡһ������ֵ��
 *
 * \note ��ʹ�� am_tm_get() ֱ�ӻ�ȡ��ǰʱ���ϸ�ֱ�ʾ��ʽ
 *
 * \param[out] p_tv  ʱ��ֵ
 *
 * \retval AM_OK    �ɹ�
 * \retval -AM_EINVAL  ��������
 *
 * \par ʾ��
 * \code
 * #include "am_time.h"
 *
 * am_timespec_t timespec;      // ����ʱ��
 *
 * am_timespec_get(&timespec);                            // �õ�����ʱ��
 * printf("%s", ctime((const time_t *)&timespec.tv_sec)); // ��ӡ����ʱ��
 * printf(" %d ms \n", timespec.tv_nsec / 1000000);       // ��ӡ����
 * \endcode
 * \sa am_time() am_timespec_set()
 */
int am_timespec_get(am_timespec_t *p_tv);

/**
 * \brief ���õ�ǰ����ʱ��
 *
 * \note ��ʹ�� am_tm_set() ��ϸ�ֱ�ʾ��ʽ�����õ�ǰʱ��
 *
 * \param[in] p_tv Ҫ���õ�ʱ��
 *
 * \retval AM_OK    �ɹ�
 * \retval -AM_EINVAL  ��������
 *
 * \par ʾ��
 * \code
 * #include "am_time.h"
 *
 * am_tm_t       tm;            // ϸ��ʱ��
 * am_timespec_t timespec;      // ����ʱ��
 *
 * tm.tm_sec    = 6;
 * tm.tm_min    = 6;
 * tm.tm_hour   = 6;
 * tm.tm_mday   = 6;
 * tm.tm_mon    = 6 - 1;        // ʵ���·�Ҫ��1
 * tm.tm_year   = 2013 - 1900;  // ��1900������
 * tm.tm_isdst  = -1;           // ����ʱ������
 *
 * am_tm_to_time(&tm, &timespec.tv_sec);    // ת��Ϊ����ʱ��
 * timespec.tv_nsec = 0;                    // ���벿����0
 *
 * am_timespec_set(&timespec);              // ��������ʱ��
 *
 * \endcode

 * \sa am_time() am_timespec_Get()
 */
int am_timespec_set(am_timespec_t *p_tv);

/**
 * \brief ��ȡ��ǰʱ�� (ϸ����ʽ��ʾ)
 *
 * \note ��ʹ�� am_tm_get() ֱ�ӻ�ȡ��ǰʱ���ϸ�ֱ�ʾ��ʽ
 *
 * \param[out] p_tm  ʱ��ֵ
 *
 * \retval AM_OK    �ɹ�
 * \retval -AM_EINVAL  ��������
 *
 * \par ʾ��
 * \code
 * #include "am_time.h"
 * am_tm_t tm;          // ϸ��ʱ��
 *
 * am_tm_get(&tm);      // �õ���ǰʱ��
 * printf("%s", asctime((const struct tm *)&tm)); // ��ӡʱ��
 *
 * printf("%d-%d-%d %d:%d:%d wday:%d yday:%d\n",
 *        tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
 *        tm.tm_hour, tm.tm_min, tm.tm_sec,
 *        tm.tm_wday, tm.tm_yday);              // ��ӡʱ��
 *
 * \endcode
 * \sa am_time() am_tm_set()
 */
int am_tm_get (am_tm_t *p_tm);

/**
 * \brief ���õ�ǰʱ��(ϸ����ʽ��ʾ)
 *
 * \param[in] p_tm Ҫ���õ�ʱ��
 *
 * \retval AM_OK    �ɹ�
 * \retval -AM_EINVAL  ��������
 *
 * \par ʾ��
 * \code
 * #include "am_time.h"
 *
 * am_tm_t       tm;            // ϸ��ʱ��
 *
 * tm.tm_sec    = 6;
 * tm.tm_min    = 6;
 * tm.tm_hour   = 6;
 * tm.tm_mday   = 6;
 * tm.tm_mon    = 6 - 1;        // ʵ���·�Ҫ��1
 * tm.tm_year   = 2013 - 1900;  // ��1900������
 * tm.tm_isdst  = -1;           // ����ʱ������
 *
 * am_tm_set(&tm);              // ��������ʱ��
 *
 * \endcode
 *
 * \sa am_time() am_timespec_Get()
 */
int am_tm_set (am_tm_t *p_tm);

/**
 * \brief ��ϸ��ʱ����ʽת��Ϊ����ʱ����ʽ
 *
 * \param[in,out] p_tm    ϸ��ʱ��, ��Ա tm_wday, tm_yday �ڵ��ú󱻸���;
 *                        ������ʱ��Ч, tm_isdst Ϊ��, ����Ч��Ϊ0, ����Ϣ������
 *                        ��Ϊ��
 * \param[out]    p_time  ����ʱ��
 *
 * \retval AM_OK       �ɹ�
 * \retval -AM_EINVAL  ��������
 * \retval -EBADF      ϸ��ʱ�����, ϸ��ʱ�����Чֵ��ο� am_tm_t
 */
int am_tm_to_time (am_tm_t *p_tm, am_time_t *p_time);

/**
 * \brief ������ʱ����ʽת��Ϊϸ��ʱ����ʽ
 *
 * \attention ��������������
 *
 * \param[in]   p_time  ����ʱ��
 * \param[out]  p_tm    ϸ��ʱ��
 *
 * \retval AM_OK       �ɹ�
 * \retval -AM_EINVAL  ��������
 */
int am_time_to_tm (am_time_t *p_time, am_tm_t *p_tm);

/**
 * \brief ϵͳʱ���ʼ��
 *
 * \param[in] rtc_handle        : ������RTCʵʱʱ�Ӿ��
 * \param[in] update_sysclk_ns  : ʹ��ϵͳʱ�Ӹ��µ�ʱ��������λ�����룩
 * \param[in] update_rtc_s      : ʹ��RTC���µ�ʱ��������λ�����룩
 *
 * \retval AM_OK       �ɹ�
 * \retval -AM_EINVAL  ��������
 */
int am_time_init (void           *rtc_handle,
                  unsigned int    update_sysclk_ns,
                  unsigned int    update_rtc_s);

/**
 * \brief ����RTC����ϵͳʱ��
 */
int am_time_update (void);

/** @} am_if_time */

#ifdef __cplusplus
}
#endif

#endif /* __AM_TIME_H */

/* end of file */

