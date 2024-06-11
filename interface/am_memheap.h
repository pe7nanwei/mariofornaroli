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
 * \brief �ѹ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 16-10-27  tee, copy from amorks
 * \endinternal
 */

#ifndef __AM_MEMHEAP_H
#define __AM_MEMHEAP_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup am_if_memheap
 * \copydoc am_memheap.h
 * @{
 */

/**
 * \brief memory item on the memory heap
 */
typedef struct am_memheap_item
{
    uint32_t                magic;           /**< magic number for memheap */
    struct am_memheap      *pool_ptr;        /**< point of pool            */

    struct am_memheap_item *next;            /**< next memheap item        */
    struct am_memheap_item *prev;            /**< prev memheap item        */

    struct am_memheap_item *next_free;       /**< next free memheap item   */
    struct am_memheap_item *prev_free;       /**< prev free memheap item   */
} am_memheap_item_t;

/**
 * \brief memory heap
 */
typedef struct am_memheap
{
    const char             *name;               /**< pool name */
    void                   *start_addr;         /**< pool start address and size */

    uint32_t                pool_size;          /**< pool size */
    uint32_t                available_size;     /**< available size */
    uint32_t                max_used_size;      /**< maximum allocated size */

    struct am_memheap_item *block_list;         /**< used block list */

    struct am_memheap_item *free_list;          /**< free block list */
    struct am_memheap_item  free_header;        /**< free block list header */
 
} am_memheap_t;

/**
 * \brief ��ʼ��һ���ѹ�����
 *
 * \param[in] memheap    ��ָ�����ʼ���Ķѹ�����
 * \param[in] name       : �ѹ�����������
 * \param[in] start_addr : �öѹ����������ڴ�ռ����ʼ��ַ
 * \param[in] size       : �öѹ����������ڴ�ռ�Ĵ�С���ֽ�����
 *
 * \retval AM_OK : ��ʼ���ɹ�
 * \retval  < 0  : ��ʼ��ʧ��
 */
am_err_t am_memheap_init(struct am_memheap *memheap,
                         const char        *name,
                         void              *start_addr,
                         uint32_t           size);
 
/**
 * \brief �Ӷ��з���ռ�
 *
 * \param[in] heap   ��ָ��ѹ�����
 * \param[in] size   : ����ռ�Ĵ�С
 *
 * \return ����ռ���׵�ַ��NULL��������ʧ��
 */
void *am_memheap_alloc(struct am_memheap *heap, uint32_t size);

/**
 * \brief ��ȡ����ռ�Ĵ�С
 *
 * \param[in] heap   ��ָ��ѹ�����
 * \param[in] ptr    : ����ռ���׵�ַ
 *
 * \return ����ռ�Ĵ�С���ֽ�����
 */
size_t am_memheap_memsize(struct am_memheap *heap, void *ptr);

/**
 * \brief ��̬�ڴ�������ı��ѷ���ռ�Ĵ�С
 *
 * \param[in] heap    ��ָ��ѹ�����
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
void *am_memheap_realloc(struct am_memheap *heap, void *ptr, size_t newsize);

/**
 * \brief �ͷŶ�̬����Ķ��ڴ�
 * \param[in] ptr : ����Ŀռ���׵�ַ
 * \return ��
 */
void am_memheap_free(void *ptr);

/** @}  am_if_memheap */

#ifdef __cplusplus
}
#endif	/* __cplusplus 	*/

#endif /* __AM_MEMHEAP_H    */

/* end of file */
