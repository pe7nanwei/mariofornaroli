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
 * \brief  BootLoader��Ϣ��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-5-23  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_MSG_H
#define __AM_BOOT_MSG_H

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \brief ˫���û�������Ч */
#define AM_BOOTLOADER_FLAG_APP     (0x12345678)
/** \brief ˫������������Ч */
#define AM_BOOTLOADER_FLAG_UPDATE  (0x87654321)
/** \brief ˫���޴��� */
#define AM_BOOTLOADER_FLAG_NO      (0xFFFFFFFF)
/**
 * \brief bootloader ��Ϣ���������ṹ��
 */
struct am_boot_msg_drv_funcs {
    /** \brief ��Ϣ���� */
    int (*pfn_msg_dispose) (void *p_drv);

    /** \brief ������Ϣ���� */
    int (*pfn_msg_set) (void *p_drv, void *par);
};

/**
 * \brief bootloader ��Ϣ��׼����ṹ��
 */
typedef struct am_boot_msg_serv {
    const struct am_boot_msg_drv_funcs *p_funcs;  /**< \brief �豸���������ṹ��ָ��    */
    void                               *p_drv;    /**< \brief �豸����������һ������ */
} am_boot_msg_serv_t;

/** \brief bootloader ��Ϣ��׼�������������Ͷ��� */
typedef am_boot_msg_serv_t * am_boot_msg_handle_t;



/**
 * \brief ����Ӧ�ó�����BootLoader���ݵ���Ϣ
 *
 * \param[in] handle : ��Ϣ������׼������
 * \param[in] par    : ������Ϣ������
 *
 * \retval AM_OK    : �ɹ�
 * \retval AM_ERROR : ʧ��
 */
am_static_inline
int am_boot_msg_set(am_boot_msg_handle_t handle, void *par)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_msg_set) {
           return handle->p_funcs->pfn_msg_set(handle->p_drv, par);
    }
    return -AM_EINVAL;
}

/**
 * \brief ����Ϣ����Ӧ�Ļ�Ӧ����
 *
 * \param[in] handle : ��Ϣ������׼������
 *
 * \retval AM_OK    : ����ɹ�
 * \retval AM_ERROR : ����ʧ��
 */
am_static_inline
int am_boot_msg_dispose(am_boot_msg_handle_t handle)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_msg_dispose) {
           return handle->p_funcs->pfn_msg_dispose(handle->p_drv);
    }
    return -AM_EINVAL;
}
#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_MSG_H */
