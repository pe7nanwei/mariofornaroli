#ifndef __TABLE_H
#define __TABLE_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _table_t;
typedef struct _table_t table_t;

typedef void* table_key_t;
typedef void* table_value_t;
typedef const void* table_const_key_t;
typedef const void* table_const_value_t;
typedef int (*table_visit_func_t)(void* ctx, table_const_key_t key, table_const_value_t value);

typedef int (*table_get_t)(table_t* table, table_const_key_t key, table_value_t value);
typedef int (*table_set_t)(table_t* table, table_const_key_t key, table_const_value_t value);
typedef int (*table_remove_t)(table_t* table, table_const_key_t key);
typedef int (*table_reset_t)(table_t* table);
typedef int (*table_close_t)(table_t* table);

/* KV ���ݿ�Ľӿ�*/
struct _table_t {
    table_get_t     get;
    table_set_t     set;
    table_remove_t  remove;
    table_reset_t   reset;
};

/**
 * \brief ��ȡKey/Value��
 *
 * \param[in] table  �� ���ݿ����
 * \param[in] key    �� ��
 * \param[out] value �� ֵ���ɵ����߷��䲻С��value_size��Ϊ0ʱ����ֵΪNULL���Ŀռ䡣
 *
 * \retval TRUE  �ɹ�
 * \retval FALSE ʧ��
 */
am_static_inline
int table_get (table_t* table, table_const_key_t key, table_value_t value)
{
	if ((table == NULL) || (table->get == NULL)) {
		return -AM_EINVAL;
	}
    return table->get(table, key, value);
}

/**
 * \brief ����Key/Value��
 *
 * \param[in] table      �� ���ݿ����
 * \param[in] key        �� ��
 * \param[in] value      �� ֵ
 *
 * \retval TRUE  �ɹ�
 * \retval FALSE ʧ��
 */
am_static_inline
int table_set (table_t* table, table_const_key_t key, table_const_key_t value)
{
	if ((table == NULL) || (table->set == NULL)) {
		return -AM_EINVAL;
	}
    return table->set(table, key, value);
}

/**
* \brief ɾ��ָ����Key��
*
* \param[in] table      �� ���ݿ����
* \param[in] key        �� ��
*
* \retval TRUE  �ɹ�
* \retval FALSE ʧ��
*/
am_static_inline
int table_remove(table_t* table, table_const_key_t key)
{
	if ((table == NULL) || (table->remove == NULL)) {
		return -AM_EINVAL;
	}
    return table->remove(table, key);
}

/**
* \brief ���ȫ����¼
*
* \param[in] table      �� ���ݿ����
* \param[in] key        �� ��
*
* \retval TRUE  �ɹ�
* \retval FALSE ʧ��
*/
am_static_inline
int table_reset(table_t* table)
{
	if ((table == NULL) || (table->reset == NULL)) {
		return -AM_EINVAL;
	}
    return table->reset(table);
}

#ifdef __cplusplus
}
#endif

#endif  // __TABLE_H

