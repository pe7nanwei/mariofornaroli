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
 * \brief lpc824 bootloader �û������ļ�
 * \sa am_bootconf_lpc824_firmware_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#include "am_lpc824_boot_firmware_flash.h"
#include "am_boot_firmware.h"
#include "am_lpc824_boot_flash.h"
#include "am_lpc824_boot.h"

/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_lpc824_boot_flash_devinfo_t __g_flash_devinfo = {
    /** \brief flash����ʼ��ַ */
    0,
    /** \brief flash���ܵĴ�С */
    32 * 1024,
    /** \brief flash������С */
    1024,
    /** \brief flash������ */
    32,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_lpc824_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_lpc824_boot_flash_inst_init(void)
{
    return am_lpc824_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}
/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_lpc824_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼���flash�д�ŵ���ʼ��ַ */
    0x3800,
    /** \brief ������Ź̼���������С��Ҳ��flash��Сд����ֽ�������󲻿ɳ���1024 */
    64,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_lpc824_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_lpc824_boot_firmware_flash(am_boot_flash_handle_t flash_handle)
{
    return am_lpc824_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                               &__g_firmware_flash_devinfo,
                                                flash_handle);
}


/*******************************************************************************
 * ��׼bootloader�ӿ�����
 ******************************************************************************/
/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_lpc824_boot_devinfo_t __g_lpc824_boot_devinfo = {
    /** \brief Ӧ�ô�����ʼ��ַ*/
    0x3800,
    /**< \brief ������־�Ĵ�ŵ�ַ*/
    0x7C00,
    /** \brief flash��ʼ��ַ*/
    0,
    /** \brief flash��С */
    32 * 1024,
    /** \brief ram��ʼ��ַ */
    0x10000000,
    /** \brief ram��С */
    8 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

/**
 * < \brief bootloader��׼�豸ʵ��
 */
static am_lpc824_boot_dev_t __g_lpc824_boot_dev;

int am_lpc824_std_boot_inst_init(am_boot_flash_handle_t flash_handle)
{
    return am_lpc824_boot_init(&__g_lpc824_boot_dev, &__g_lpc824_boot_devinfo, flash_handle);
}
