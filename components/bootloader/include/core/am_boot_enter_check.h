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
 * \brief ����Ӧ�ó������׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-5-23  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_ENTER_CHECK_H
#define __AM_BOOT_ENTER_CHECK_H

#include "am_common.h"

/**
 * \brief bootloader ����Ӧ�ó��������������ṹ��
 */
struct am_boot_enter_check_drv_funcs {

    /** \brief Ӧ�ó�������� */
    am_bool_t (*pfn_startup_check) (void *p_drv);
};

/**
 * \brief Ӧ�ó���������׼����ṹ��
 */
typedef struct am_boot_enter_check_serv {
    /**< \brief �豸���������ṹ��ָ�� */
    const struct am_boot_enter_check_drv_funcs *p_funcs;

    /**< \brief �豸����������һ������ */
    void                                       *p_drv;
} am_boot_enter_check_serv_t;

/** \brief ����Ӧ�ó������׼�������������Ͷ��� */
typedef am_boot_enter_check_serv_t  *am_boot_enter_check_handle_t;

/**
 * \brief ����Ӧ�ó�����
 *
 * \retval AM_TRUE  ����Ӧ�ô���
 * \retval AM_FALSE ����BootLoader
 */
am_static_inline
am_bool_t am_boot_enter_check(am_boot_enter_check_handle_t handle)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_startup_check) {
        return handle->p_funcs->pfn_startup_check(handle->p_drv);
    }
    return AM_FALSE;
}

#endif /* __AM_BOOT_ENTER_CHECK_H */
