#ifndef BLOCK_DEV_H
#define BLOCK_DEV_H

#include "types_def.h"

BEGIN_C_DECLS

//���豸����Ĵ�С��һ��ѡ��256����������
#ifndef BLOCK_SIZE
#define BLOCK_SIZE 256
#endif//BLOCK_SIZE

typedef unsigned short block_num_t;

struct _block_dev_t;
typedef struct _block_dev_t block_dev_t;

typedef block_num_t (*block_dev_get_block_nr_t)(block_dev_t* dev);
typedef am_bool_t (*block_dev_read_block_t)(block_dev_t* dev, block_num_t block_num, void* buff);
typedef am_bool_t (*block_dev_write_block_t)(block_dev_t* dev, block_num_t block_num, const void* buff);
typedef void   (*block_dev_close_t)(block_dev_t* dev);


/*
* ���豸�Ľӿڡ�
*/

struct _block_dev_t {
	block_dev_get_block_nr_t   get_block_nr;
	block_dev_write_block_t    write_block;
	block_dev_read_block_t     read_block;
	block_dev_close_t          close;
};

/**
* \brief ��ȡ���豸���ܹ��Ŀ�����
*
* \param[in] dev      �� ���豸����
*
* \retval ���豸���ܹ��Ŀ���
*/
am_static_inline block_num_t block_dev_get_block_nr(block_dev_t* dev) {
	return_value_if_fail(dev != NULL && dev->get_block_nr != NULL, 0);

	return dev->get_block_nr(dev);
}

/**
* \brief �ӿ��豸�ж�ȡָ��������ݡ�
*
* \param[in] dev        �� ���豸����
* \param[in] block_num  �� ���
* \param[out] buff      �� �������ݵ�buff���������ṩ��С��BLOCK_SIZE��С�Ŀռ䡣
*
* \retval TRUE  �ɹ�
* \retval FALSE ʧ��
*/
am_static_inline am_bool_t block_dev_read_block(block_dev_t* dev, block_num_t block_num, void* buff) {
	return_value_if_fail(dev != NULL && dev->read_block != NULL 
			&& block_num < block_dev_get_block_nr(dev), FALSE);

	return dev->read_block(dev, block_num, buff);
}

/**
* \brief ����豸��д��ָ��������ݡ�
*
* \param[in] dev        �� ���豸����
* \param[in] block_num  �� ���
* \param[in] buff       �� ��д�����ݵ�buff����С��С��BLOCK_SIZE��
*
* \retval TRUE  �ɹ�
* \retval FALSE ʧ��
*/
am_static_inline am_bool_t block_dev_write_block(block_dev_t* dev, block_num_t block_num, const void* buff) {
	return_value_if_fail(dev != NULL && dev->write_block != NULL 
			&& block_num < block_dev_get_block_nr(dev), FALSE);

	return dev->write_block(dev, block_num, buff);
}

/**
* \brief �رտ��豸���ͷ������Դ��
*
* \param[in] dev        �� ���豸����
*
* \retval ��
*/
am_static_inline void block_dev_close(block_dev_t* dev) {
	return_if_fail(dev != NULL && dev->close != NULL);

	dev->close(dev);
}

END_C_DECLS

#endif//BLOCK_DEV_H

