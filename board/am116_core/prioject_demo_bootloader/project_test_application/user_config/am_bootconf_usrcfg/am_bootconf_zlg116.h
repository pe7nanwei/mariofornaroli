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
 * \brief ZLG116 kboot KinetisFlashTool �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

#include "am_boot_firmware.h"
#include "am_boot_flash.h"

am_boot_flash_handle_t am_zlg116_boot_flash_inst_init(void);

am_boot_firmware_handle_t am_zlg116_boot_firmware_flash(am_boot_flash_handle_t flash_handle);
/**
 * \brief bootloader ��׼ʵ����ʼ��
 *
 *
 * \return ��Ϊ AM_OK��������ʼ���ɹ�
 */
int am_zlg116_std_boot_inst_init(am_boot_flash_handle_t flash_handle);


