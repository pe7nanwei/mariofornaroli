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
 * \brief bootloader �������ݲ���ͨ�ò����ӿ�
 *
 *   ������Ҫ������BootLoader���ڴ������ݲ����ģ����ڳ����࣬���ݲ�ͬ��������ʽ��������ʵ�ֶ��������
 *   ���磬ʹ��uart���������ݴ��䣬ʹ��i2c���������ݴ��䡣
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
 * - 1.00 18-12-4  yrh, first implementation.
 * \endinternal
 */
#ifndef __AM_BOOT_SERIAL_BYTE_H
#define __AM_BOOT_SERIAL_BYTE_H

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**< \brief ���ջص������������� */
typedef void (*serial_byte_receive_func_t)(uint8_t inchar);

/**
 * \brief �����豸�ֽڴ������������ṹ��
 */
struct am_boot_serial_byte_funcs {
    /**< \brief �������� */
    int (*pfn_serial_byte_send)(void *p_arg, const uint8_t *p_buffer, uint32_t size);

    /**< \brief �������� */
    int (*pfn_serial_byte_receive)(void *p_arg, uint8_t *p_buffer, uint32_t size);

    /**< \brief �û��жϽ��ջص��������� */
    int (*pfn_serial_int_callback_enable)(void *p_arg, serial_byte_receive_func_t callback_fun);
};

/**
 * \brief bootloader �������ݴ��� ��׼����ṹ��
 */
typedef struct am_boot_serial_byte_serv {
    const struct am_boot_serial_byte_funcs *p_funcs;  /**< \brief �������ݴ������������ṹ��ָ�� */
    void                                   *p_drv;    /**< \brief �������ݴ�������������һ������ */
} am_boot_serial_byte_serv_t;

/** \brief bootloader �������ݲ�����׼�������������� */
typedef am_boot_serial_byte_serv_t  *am_boot_serial_handle_t;

/**
 * \brief ͨ�������豸�ӿڷ�����
 *
 * \param[in] handle : �������ݲ�����׼������
 * \param[in] p_buffer : ���͵�����
 * \param[in] size   : �������ݵĳ���
 *
 * \retval ���͵��ֽ���
 */
am_static_inline
int am_boot_serial_byte_send(am_boot_serial_handle_t handle,
                             const uint8_t          *p_buffer,
                             uint32_t                size)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_byte_send) {
        return handle->p_funcs->pfn_serial_byte_send(handle->p_drv,
                                                     p_buffer,
                                                     size);
    }
    return -AM_EINVAL;
}

/**
 * \brief ͨ�������豸�ӿ�������
 *
 * \param[in] handle : �������ݲ�����׼������
 * \param[in] p_buffer : ���յ�����
 * \param[in] size   : �������ݵĳ���
 *
 * \retval �յ����ֽ���
 */
am_static_inline
int am_boot_serial_byte_receive(am_boot_serial_handle_t handle,
                                uint8_t                *p_buffer,
                                uint32_t                size)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_byte_receive) {
        return handle->p_funcs->pfn_serial_byte_receive(handle->p_drv,
                                                        p_buffer,
                                                        size);
    }
    return -AM_EINVAL;
}

/**
 * \brief �����жϽ����û�����Ļص���������
 *
 * �û������Լ���д�Լ��Ļص�������ͨ���ýӿ�ʹ����Ĵ����豸�жϽ��ջص����潫�յ������ݴ����û��ص�������
 *
 * \param[in] handle       : �������ݲ�����׼������
 * \param[in] callback_fun : �û��Ļص�������,serial_byte_receive_func_t��һ������ָ������
 *                           ���жϽ��յ���һ���ֽڣ��û������ڻص��������洦������ֽ�
 *
 * \retval AM_OK    : �ɹ�
 * \retval AM_ERROR : ʧ��
 */
am_static_inline
int am_boot_serial_int_recev_callback_enable(am_boot_serial_handle_t    handle,
                                             serial_byte_receive_func_t callback_fun)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_int_callback_enable) {
        return handle->p_funcs->pfn_serial_int_callback_enable(handle->p_drv,
                                                               callback_fun);
    }
    return -AM_EINVAL;
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_SERIAL_BYTE_H */
/* end of file */
