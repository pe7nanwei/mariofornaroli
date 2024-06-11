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
 * \brief �ڴ�����׼�ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ���
 * \code
 * #include "am_mem.h"
 * \endcode
 * �������ṩ�˶�̬�ڴ����Ľӿ�
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 16-10-27  tee, first implementation
 * \endinternal
 */

#ifndef __AM_MEM_H
#define __AM_MEM_H

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

#include "am_memheap.h"

/**
 * \addtogroup am_if_mem
 * \copydoc am_mem.h
 * @{
 */

/**
 * \brief ����һ������align�ֽڶ�����ڴ�ռ�
 *
 * \param[in] size    ������ռ�Ĵ�С
 * \param[in] align   : ָ������ռ������ֽ������׵�ַ������align�ֽڶ��룩
 *
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 */
void *am_mem_align(size_t size, size_t align);

/**
 * \brief ����һ���ڴ�ռ�
 * \param[in] size ������ռ�Ĵ�С
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 */
void *am_mem_alloc(size_t size);

/**
 * \brief ����һ���ڴ�ռ䣨�ڴ�ռ�ᱻ��ʼ��Ϊ0��
 *
 * \param[in] nelem ��Ԫ�ظ���
 * \param[in] size  : һ��Ԫ�صĴ�С�������ڴ�ռ�Ĵ�С��Ϊ  nelem * size
 *
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 *
 * \note ������ڴ�ռ�ᱻ��ʼ��Ϊ0
 */
void *am_mem_calloc(size_t nelem, size_t size);

/**
 * \brief �ͷ��ѷ�����ڴ�ռ�
 * \param[in] ptr ���ѷ�����ڴ�ռ���׵�ַ
 * \return ��
 */
void am_mem_free(void *ptr);

/**
 * \brief ��ȡ����ռ�Ĵ�С
 * \param[in] ptr    : ����ռ���׵�ַ
 * \return ����ռ�Ĵ�С���ֽ�����
 */
size_t am_mem_size(void *ptr);

/**
 * \brief ��̬�ڴ�������ı��ѷ���ռ�Ĵ�С
 *
 * \param[in] ptr     : �ѷ���ռ���׵�ַ
 * \param[in] newsize : ���·���Ŀռ�Ĵ�С
 *
 * \return ���·���ռ���׵�ַ��NULL��������ʧ��
 *
 * \note �������жϵ�ǰ��ָ���Ƿ����㹻�������ռ䣬����У����� ptr ָ���ַ��
 * �ռ䣬ֱ�ӽ�ptr��ֵ���ء�����ռ䲻�����Ȱ���new_sizeָ���Ĵ�С����ռ䣬��
 * ԭ�����ݴ�ͷ��β�������·�����ڴ����򣬶����ͷ�ԭ��ptr��ָ�ڴ�����ԭ��
 * ָ���Զ��ͷţ�����Ҫ am_memheap_free()����ͬʱ�����·�����ڴ�������׵�ַ��
 */
void *am_mem_realloc(void *ptr, size_t newsize);

/** @}  am_if_mem */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif	/* __AM_MEM_H */

/* end of file */

