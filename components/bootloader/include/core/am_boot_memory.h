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
 * \brief bootloader memory ����ͨ�ò����ӿ�
 *
 *   ������Ҫ������BootLoader�����ڴ�����ģ����ڳ����࣬���ݲ�ͬ��������ʽ��������ʵ�ֶ��������
 *   ���磬ʹ��flash�������ڴ������ʹ��ram�����ڴ������
 *
 *
 * \par ʹ��ʾ��
 * \code
 *
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 18-11-30  yrh, first implementation.
 * \endinternal
 */


#ifndef __AM_BOOT_MEMORY_H
#define __AM_BOOT_MEMORY_H

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif



/**
 * \brief bootloader memory ���������ṹ��
 */
struct am_boot_mem_drv_funcs {

    /** \brief �ڴ������ */
    int (*pfn_read) (void *p_drv, uint32_t address, uint32_t length, uint8_t *p_buffer);

    /** \brief �ڴ�д���� */
    int (*pfn_write) (void *p_drv, uint32_t address, uint32_t length, uint8_t *p_buffer);

    /** \brief �ڴ��������  */
    int (*pfn_erase) (void *p_drv, uint32_t address, uint32_t length);
};

/**
 * \brief bootloader memory ��׼����ṹ��
 */
typedef struct am_boot_mem_serv {
    const struct am_boot_mem_drv_funcs *p_funcs;  /**< \brief �豸���������ṹ��ָ��    */
    void                               *p_drv;    /**< \brief �豸����������һ������ */
} am_boot_mem_serv_t;

/** \brief bootloader memory ��׼�������������Ͷ��� */
typedef am_boot_mem_serv_t  *am_boot_mem_handle_t;

/**
 * \brief �ڴ�д
 *
 * \param[in] handle   : �ڴ������׼������
 * \param[in] address  : д��ĵ�ַ
 * \param[in] length   : д��ĳ���
 * \param[in] p_buffer : д�������
 *
 * \retval AM_OK : д��ɹ�
 */
am_static_inline
int am_boot_mem_read(am_boot_mem_handle_t handle,
                     uint32_t             address,
                     uint32_t             length,
                     uint8_t             *p_buffer)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_read) {
        return handle->p_funcs->pfn_read(handle->p_drv, address, length, p_buffer);
    }
    return -AM_EINVAL;
}

/**
 * \brief �ڴ�д
 *
 * \param[in] handle   : �ڴ������׼������
 * \param[in] address  : �ڴ���ĵ�ַ
 * \param[in] length   : �����ĳ���
 * \param[in] p_buffer : �������ݴ�ŵ�λ��
 *
 * \retval AM_OK : д��ɹ�
 */
am_static_inline
int am_boot_mem_write(am_boot_mem_handle_t handle,
                      uint32_t             address,
                      uint32_t             length,
                      uint8_t             *p_buffer)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_write) {
           return handle->p_funcs->pfn_write(handle->p_drv, address, length, p_buffer);
    }
    return -AM_EINVAL;
}

/**
 * \brief �ڴ�д
 *
 * \param[in] handle   : �ڴ������׼������
 * \param[in] address  : ��������ʼ��ַ
 * \param[in] length   : �����ĳ���
 *
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_boot_mem_erase(am_boot_mem_handle_t handle,
                      uint32_t             address,
                      uint32_t             length)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_erase) {
           return handle->p_funcs->pfn_erase(handle->p_drv, address, length);
    }
    return -AM_EINVAL;
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_MEMORY_H */
