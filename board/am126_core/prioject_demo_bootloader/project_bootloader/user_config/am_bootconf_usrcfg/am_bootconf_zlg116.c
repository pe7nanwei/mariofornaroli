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
 * \brief ZLG116 bootloader �û������ļ�
 * \sa am_bootconf_zlg116_firmware_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#include "am_zlg116_boot_firmware_flash.h"
#include "am_boot_firmware.h"
#include "am_zlg116_boot_flash.h"
#include "zlg116_regbase.h"
#include "am_zlg116_boot.h"

/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_zlg116_boot_flash_devinfo_t __g_flash_devinfo = {
    /** \brief flash����ʼ��ַ */
    0x08000000,
    /** \brief flash���ܵĴ�С */
    64 * 1024,
    /** \brief flash������С */
    1024,
    /** \brief flash������ */
    64,
    /** \brief flash�Ĵ����Ļ���ַ */
    ZLG116_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_zlg116_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_zlg116_boot_flash_inst_init(void)
{
    return am_zlg116_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}
/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_zlg116_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼���flash�д�ŵ���ʼ��ַ */
    0x08003C00,
    /** \brief ������Ź̼���������С��Ҳ��flash��Сд����ֽ�������󲻿ɳ���1024 */
    4,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_zlg116_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_zlg116_boot_firmware_flash(am_boot_flash_handle_t flash_handle)
{
    return am_zlg116_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                               &__g_firmware_flash_devinfo,
                                                flash_handle);
}


/*******************************************************************************
 * ��׼bootloader�ӿ�����
 ******************************************************************************/
/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_zlg116_boot_devinfo_t __g_zlg116_boot_devinfo = {
    /** \brief Ӧ�ô�����ʼ��ַ*/
    0X08003C00,
    /** \brief ��������ʼ��ַ*/
    0x08009C00,
    /**< \brief ������־�Ĵ�ŵ�ַ*/
    0X0800FC00,
    /**< \brief Ӧ�ô���ռ�õ�����������������ռ�õ���������ͬ*/
    24,
    /** \brief flash��ʼ��ַ*/
    0x08000000,
    /** \brief flash��С */
    64 * 1024,
    /** \brief ram��ʼ��ַ */
    0x20000000,
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
static am_zlg116_boot_dev_t __g_zlg116_boot_dev;

int am_zlg116_std_boot_inst_init(am_boot_flash_handle_t flash_handle)
{
    return am_zlg116_boot_init(&__g_zlg116_boot_dev, &__g_zlg116_boot_devinfo, flash_handle);
}
