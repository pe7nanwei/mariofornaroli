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
 * \brief ���Եļ�ʵ��
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_assert.h
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history
 * - 1.00 16-10-27  tee, first implementation
 * \endinternal
 */

#ifndef __AM_ASSERT_H
#define __AM_ASSERT_H

/*lint ++flb */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_assert
 * \copydoc am_assert.h
 * @{
 */

#ifdef AM_DEBUG

/* help macro */
#define _AM_VTOS(n)     #n          /* Convert n to string */
#define _AM_SVAL(m)     _AM_VTOS(m) /* Get string value of macro m */

/**
 * \brief ����һ�����ʽ
 *
 * �����ʽΪ��ʱ����겻���κ����飬Ϊ��ʱ�����am_assert_msg()���������Ϣ��
 * ������Ϣ��ʽΪ��
 * �ļ������кţ����ʽ
 * \hideinitializer
 */
#define am_assert(e) \
    ((e) ? (void)0 : am_assert_msg(__FILE__":"_AM_SVAL(__LINE__)":("#e")\n"))

extern void am_assert_msg (const char *msg);

#else

/**
 * \brief ����һ�����ʽ
 *
 * �����ʽΪ��ʱ����겻���κ����飬Ϊ��ʱ�����am_assert_msg()���������Ϣ��
 * ������Ϣ��ʽΪ��
 * �ļ������кţ����ʽ
 * \hideinitializer
 */
#define am_assert(e)    ((void)0)
#endif

#ifdef __cplusplus
}
#endif

/** @}  am_if_assert */

#endif /* __AM_ASSERT_H */

/* end of file */
