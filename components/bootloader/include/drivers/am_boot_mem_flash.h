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
 * \brief bootloader �ڴ������flash������
 *
 * \internal
 * \par modification history:
 * - 1.00 18-11-30  yrh, first implementation.
 * \endinternal
 */

#ifndef __AM_BOOT_FLASH_MEMORY_H
#define __AM_BOOT_FLASH_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_boot_memory.h"
#include "am_boot_flash.h"

/**
 * \brief �ڴ�����豸��flashʵ�֣�
 */
typedef struct am_boot_mem_flash_dev {
    am_boot_mem_serv_t            isa;          /**< \brief ��׼�� memory ����  */
    am_boot_flash_handle_t        flash_handle; /**< \brief flash�ı�׼����������  */
} am_boot_mem_flash_dev_t;

/**
 * \brief �ڴ�����豸��ʼ����flashʵ�֣�
 *
 * \return flash ��׼����������
 */
am_boot_mem_handle_t am_boot_mem_flash_init(am_boot_flash_handle_t flash_handle);


#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_FLASH_MEMORY_H */

/* end of file */
