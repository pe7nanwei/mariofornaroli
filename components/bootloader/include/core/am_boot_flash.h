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
 * \brief bootloader flash������׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 18-11-13  yrh, first implementation.
 * \endinternal
 */

#ifndef __AM_BOOT_FLASH_H
#define __AM_BOOT_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

typedef struct am_boot_flash_info {
    /**< \brief flash��ʼ��ַ */
    uint32_t  flash_start_addr;

    /**< \brief flash�Ĵ�С */
    uint32_t  flash_size;

    /**< \brief flash������С */
    uint32_t  flash_sector_size;

    /**< \brief flashҳ��С */
    uint32_t  flash_page_size;

}am_boot_flash_info_t;

struct am_boot_flash_drv_funcs {
    /**< \brief flash������� */
    int  (*pfn_flash_erase_region) (void     *p_drv,
                                    uint32_t  start_addr,
                                    uint32_t  length);

    /**< \brief flashд */
    int  (*pfn_flash_program) (void      *p_drv,
                               uint32_t   dst_addr,
                               void      *p_src,
                               uint32_t   size);

    /**< \brief ��ȡflash����Ϣ */
    void (*pfn_flash_info_get) (void     *p_drv,am_boot_flash_info_t  **p_info );

    /**< \brief ��������flash */
    int (*pfn_flash_erase_all)(void      *p_drv);
};

typedef struct am_boot_flash_serv {
    /**< \brief flash�������������ṹ��ָ�� */
    struct am_boot_flash_drv_funcs *p_funcs;

    /**< \brief flash�������������ĵ�һ������ */
    void                           *p_drv;
}am_boot_flash_serv_t;

/**< \brief flash��׼�������������Ͷ��� */
typedef am_boot_flash_serv_t *am_boot_flash_handle_t;

/**
 * \brief flash�������
 *
 * ע�⣺��������ĳ���С��flash�Ĳ�����С��С�������ղ�����С��С����
 *
 * \param[in] start_addr : ��ʼ��ַ
 * \param[in] length     : ��������
 *
 * \retval AM_OK    �����ɹ�
 * \retval AM_ERROR ����Ĳ�������
 * \retval >0       ����������
 */
am_static_inline
int am_boot_flash_erase_region(am_boot_flash_handle_t handle,
                               uint32_t               start_addr,
                               uint32_t               length)
{
    return handle->p_funcs->pfn_flash_erase_region(handle->p_drv,
                                                   start_addr,
                                                   length);
}
/**
 * \brief flash���
 *
 * \param[in] dst_addr : Ŀ���ַ
 * \param[in] p_src    : ����Դ��ַ
 * \param[in] size     : д������ݵĴ�С
 *
 * \retval AM_OK    д��ɹ�
 * \retval AM_ERROR ����Ĳ�������
 * \retval >0       ����������
 */
am_static_inline
int am_boot_flash_program(am_boot_flash_handle_t handle,
                          uint32_t               dst_addr,
                          void                  *p_src,
                          uint32_t               size)
{
    return handle->p_funcs->pfn_flash_program(handle->p_drv,
                                              dst_addr,
                                              p_src,
                                              size);
}

/**
 * \brief ��ȡflash����Ϣ
 *
 * \param[in] p_info : ��Ż�ȡ�����Ϣ
 * \retval ��
 */
am_static_inline
void am_boot_flash_info_get(am_boot_flash_handle_t  handle,
                            am_boot_flash_info_t  **pp_info)
{
    if(handle != NULL &&
       handle->p_funcs != NULL &&
       handle->p_funcs->pfn_flash_info_get != NULL) {
        handle->p_funcs->pfn_flash_info_get(handle->p_drv, pp_info);
    } 
}

/**
 * \brief ��������flash
 *
 * \retval AM_OK    : �ɹ�
 * \retval AM_ERROR : ʧ��
 *
 */
am_static_inline
int am_boot_flash_erase_all(am_boot_flash_handle_t handle)
{
    if(handle != NULL &&
       handle->p_funcs != NULL &&
       handle->p_funcs->pfn_flash_erase_all != NULL) {
        return handle->p_funcs->pfn_flash_erase_all(handle->p_drv);
    }
    return AM_ERROR;
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_FLASH_H */

/* end of file */
