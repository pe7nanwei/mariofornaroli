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
 * \brief lpc845 kboot KinetisFlashTool �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */

#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "am_boot_msg_flag.h"
/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_lpc84x_boot_flash_inst_init(void);

/**
 * \brief bootloader ��׼ʵ����ʼ��
 *
 *
 * \return ��Ϊ AM_OK��������ʼ���ɹ�
 */
int am_lpc84x_boot_inst_init(void);

/**
 * \brief bootloader �̼���� ʵ����ʼ��
 */
am_boot_firmware_handle_t am_lpc84x_boot_firmware_flash_inst_init(void);

/**
 * \brief bootloader ͨ����־������Ϣ  ʵ����ʼ��
 */
am_boot_msg_handle_t am_lpc84x_boot_msg_flag_inst_init(void);

/*end of file*/
