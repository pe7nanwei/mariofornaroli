/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ���ڹ�ϣ���΢�����ݿ�
 *
 *
 * \internal
 * \par modification history:
 * - 1.00 18-05-02  tee, first implementation
 * \endinternal
 */

#ifndef __HASH_KV_H
#define __HASH_KV_H

#include "types_def.h"
#include "stdint.h"
#include "stdio.h"
#include "raw_posix.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ��¼��󳤶ȣ�key_size + value_size + sizeof(hash_kv_addr_t)*/
#define MAX_RECORD_SIZE  128

 

typedef uint32_t hash_kv_addr_t;
typedef int (*hash_kv_func_t)(const void *p_key);
typedef int (*hash_func_t)(const void* data, size_t len);	
typedef int (*compare_func_t)(const void* a, const void* b, size_t len);
typedef am_bool_t (*visit_func_t)(void* ctx, const void* data);

/* �����ļ���ϣ������ݿ�*/
typedef struct _db_micro_hash_kv_t {
    FILE                       *fp;                  // �ļ����
    const char                 *p_file_name;         // �ļ���
    hash_kv_func_t              pfn_hash;            // ��ϣ����
    uint32_t                    dirty;               // �����޸ļ�����
    uint16_t                    size;                // ��ϣ��Ĵ�С��ֱ��Ӱ�����ܣ�һ������ΪԤ������¼����1/4��1����
    uint16_t                    key_size;            // ���ĳ���
    uint16_t                    value_size;          // ֵ�ĳ���
    hash_kv_addr_t              free_record_head;    // ����վ����ı�ͷ
} hash_kv_t;

/**
 * \brief ��ʼ���ļ���ϣ��ֻ�г�ʼ��֮�󣬲��ܵ�������������
 *
 * \param[in] kv         �� ���ݿ����
 * \param[in] size       �� ��ϣ��Ĵ�С��ֱ��Ӱ�����ܣ�һ������ΪԤ������¼����1/4��1����
 * \param[in] key_size   �� ���ĳ��� 
 * \param[in] value_size �� ֵ�ĳ��� 
 * \param[in] hash       �� ��ϣ����
 * \param[in] file_name  �����Դ洢 ��ϣ���ݿ������Ϣ���ļ���
 *
 * \retval AW_OK  �ɹ�
 */
int hash_kv_init (hash_kv_t      *p_db,
                  uint16_t        size,
                  uint16_t        key_size,
                  uint16_t        value_size,
                  hash_kv_func_t  pfn_hash,
                  const char     *file_name);

/**
 * \brief ���һ����¼������ Key ��  Value��
 *
 * \param[in] p_db     �� ���ݿ����
 * \param[in] key        �� ��
 * \param[in] value      �� ֵ
 *
 * \retval AW_OK  �ɹ�
 *
 * \note ����ʱ��Ӧ�ñ�֤��ǰ�ؼ��ֵļ�¼������
 */
int hash_kv_add (hash_kv_t  *p_db,
                 const void *key,
                 const void *value);

/**
 * \brief ��ȡKey/Value��
 *
 * \param[in]  p_db    �� ���ݿ����
 * \param[in]  key       �� ��
 * \param[out] value     �� ֵ���ɵ����߷��䲻С��value_size�Ŀռ䡣
 *
 * \retval AW_OK  �ɹ�
 * \retval ����ֵ   ʧ��
 */
int hash_kv_search (hash_kv_t     *p_db,
                    const void    *p_key,
                    void          *p_value);
/**
 * \brief ɾ��ָ����  Key �ļ�¼
 *
 * \param[in] kv         �� ���ݿ����
 * \param[in] key        �� ��
 *
 * \retval AW_OK  �ɹ�
 * \retval ����ֵ   ʧ��
 */
int hash_kv_del (hash_kv_t   *p_db,
                             const void              *p_key);

/**
 * \brief ��λ���ݿ⣬��ɾ����������
 *
 * \param[in] p_db �� ���ݿ����
 *
 * \retval AW_OK  �ɹ�
 * \retval ����ֵ   ʧ��
 */
int hash_kv_reset (hash_kv_t *p_db);

/**
 * \brief ������ݿ����޸ģ�ͬ�������豸��
 *
 * \param[in] p_db  �� ���ݿ����
 *
 * \retval AW_OK  �ɹ�
 * \retval ����ֵ   ʧ��
 */
int hash_kv_flush (hash_kv_t *p_db);

/**
 * \brief ���ʼ�����رճ�ʼ��ʱ�򿪵��ļ����ͷ������Դ
 *
 * \param[in] p_db �� ���ݿ����
 *
 * \retval AW_OK  �ɹ�
 * \retval ����ֵ   ʧ��
 */
int hash_kv_deinit (hash_kv_t *p_db);


#ifdef __cplusplus
}
#endif

#endif /* HASH_KV_H */

/* end of file */

