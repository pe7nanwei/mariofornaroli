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
 * \brief bootloader �̼����յĽӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-5-23  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_FIRMWARE_RECV_H
#define __AM_BOOT_FIRMWARE_RECV_H

#include "am_common.h"

/**
 * \brief bootloader �̼��������������ṹ��
 */
struct am_boot_firwa_recv_drv_funcs {

    /** \brief �̼����ղ��� */
    int (*pfn_firwa_recv) (void *p_drv);
};

/**
 * \brief bootloader �̼����ձ�׼����ṹ��
 */
typedef struct am_boot_firwa_recv_serv {
    /**< \brief �豸���������ṹ��ָ�� */
    const struct am_boot_firwa_recv_drv_funcs *p_funcs;

    /**< \brief �豸����������һ������ */
    void                                     *p_drv;
} am_boot_firwa_recv_serv_t;

/** \brief bootloader �̼����ձ�׼�������������Ͷ��� */
typedef am_boot_firwa_recv_serv_t  *am_boot_firwa_recv_handle_t;

/**
 * \brief �̼�����
 *
 * \retval AM_OK    ���ճɹ�
 * \retval AM_ERROR ����ʧ��
 */
am_static_inline
int am_boot_firmware_recv(am_boot_firwa_recv_handle_t handle)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_firwa_recv) {
        return handle->p_funcs->pfn_firwa_recv(handle->p_drv);
    }
    return -AM_EINVAL;
}
/* end of file */

#endif /* __AM_BOOT_FIRMWARE_RECV_H */

