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
 * \brief bootloader �̼��洢�Ľӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-16  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_FIRMWARE_H
#define __AM_BOOT_FIRMWARE_H

#include "ametal.h"
/**
 * \brief bootloader���չ̼�ͷ������
 */
typedef struct am_boot_firmware_verify_info {
    /** \brief �̼���־ */
    uint32_t flag;

    /** \brief �̼����� */
    uint32_t len;

    /** \brief �̼�У���� */
    uint32_t verify_value;

} am_boot_firmware_verify_info_t;

struct am_boot_firmware_drv_funcs {
    /**< \brief �̼��洢��ʼ��������*/
    int (*pfn_store_start)(void *p_drv);

    /**< \brief �̼��洢��������*/
    int (*pfn_store_bytes)(void *p_drv, uint8_t *p_data, uint32_t size);

    /**< \brief �̼��洢������������*/
    int (*pfn_store_final)(void *p_drv);

    /**< \brief �̼�У��*/
    int (*pfn_verify)(void *p_drv, am_boot_firmware_verify_info_t *p_verify_info);

};

/**< \brief �̼��洢��׼���� */
typedef struct am_boot_firmware_serv {
    /**< \brief ��׼�������������ṹ��ָ�� */
    struct am_boot_firmware_drv_funcs *pfn_funcs;

    /**< \brief ���������ĵ�һ������ */
    void                              *p_drv;
} am_boot_firmware_serv_t;

/**< \brief �̼��洢��׼���������������Ͷ��� */
typedef am_boot_firmware_serv_t *am_boot_firmware_handle_t;

/**
 * \brief �̼��洢�Ŀ�ʼ����
 *
 *
 * \retval AM_ENOMEM   �̼������ڴ��С
 * \retval AM_EFAULT   �̼���ŵĵ�ַ����1.��ַ���󣬲��������Ĵ洢��Χ��2.�����������׵�ַ��
 * \retval AM_EINVAL   ����Ĳ������Ϸ�
 * \retval AM_OK       �ɹ�
 */
am_static_inline
int am_boot_firmware_store_start(am_boot_firmware_handle_t  handle)
{
    return handle->pfn_funcs->pfn_store_start(handle->p_drv);
}

/**
 * \brief �̼����ݴ洢
 *
 * am_boot_firmware_store_bytes��������ִ����Ҫһ����ʱ�䣬����ʱע��̼������ʱ�䣬��ֹ���ݴ��䶪ʧ��
 *
 * \param[in] p_data        : ����Ĺ̼����׵�ַ
 * \param[in] firmware_size : ����Ĺ̼�����
 *
 * \retval AM_EINVAL   ������Ч
 * \retval AM_ENOMEM   �ռ䣨�ڴ棩����
 * \retval AM_ERROR    ������д��ʧ��
 * \retval AM_OK       �ɹ�
 */
am_static_inline
int am_boot_firmware_store_bytes(am_boot_firmware_handle_t handle,
                                 uint8_t                  *p_data,
                                 uint32_t                  size)
{
    return handle->pfn_funcs->pfn_store_bytes(handle->p_drv, p_data, size);
}

/**
 * \brief �̼��洢�Ľ���
 *
 * \retval AM_ERROR ����
 * \retval AM_OK    �ɹ�
 */
am_static_inline
int am_boot_firmware_store_final(am_boot_firmware_handle_t handle)
{
    return handle->pfn_funcs->pfn_store_final(handle->p_drv);
}

/**
 * \brief �̼�У��
 *
 * У�鴫��Ĺ̼��Ƿ���ȷ
 *
 * \param[in] handle        : �������
 * \param[in] p_verify_info : У����Ϣ�Ľṹ�壬�����̼����Ⱥ�У����
 *
 * \retval AM_ERROR ����
 * \retval AM_OK    �ɹ�
 */
am_static_inline
int am_boot_firmware_verify(am_boot_firmware_handle_t handle, am_boot_firmware_verify_info_t *p_verify_info)
{
    return handle->pfn_funcs->pfn_verify(handle->p_drv, p_verify_info);
}


#endif /* __AM_BOOT_FIRMWARE_H */

/* end of file */
