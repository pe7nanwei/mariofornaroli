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
 * \brief ZLG217 kboot KinetisFlashTool �û������ļ�
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
#include "am_boot_autobaud.h"
/**
 * \brief bootloader kboot KinetisFlashTool ʵ����ʼ��
 *
 * \return ��Ϊ AM_OK��������ʼ���ɹ�
 */
int am_zlg217_boot_kft_inst_init( am_boot_flash_handle_t flash_handle);

/** \brief bootloader��׼�ӿ�ʵ����ʼ��������Զ������ʷ����� */
int am_zlg217_std_boot_inst_init(am_boot_flash_handle_t flash_handle);

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_zlg217_boot_flash_inst_init(void);

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_boot_autobaud_handle_t am_zlg217_boot_autobaud_inst_init (void);

/** \brief �Զ�������ʵ�����ʼ�� */
void am_zlg217_boot_autobaud_inst_deinit (am_boot_autobaud_handle_t handle);
