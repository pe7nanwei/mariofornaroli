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
 * \brief bootloader��׼�ӿ�ʵ�֣�arm������
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_ARM_BOOT_H
#define __AM_ARM_BOOT_H

#include "am_boot.h"
#include "am_boot_flash.h"

typedef struct am_arm_boot_devinfo {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    uint32_t  app_reg_sta_addr;

    /**< \brief ram��ʼ��ַ */
    uint32_t  ram_start_addr;

    /**< \brief ram�Ĵ�С */
    uint32_t  ram_size;

    /**< \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /**< \brief ƽ̨ȥ��ʼ������ */
    void    (*pfn_plfm_deinit)(void);
}am_arm_boot_devinfo_t;

typedef struct am_arm_boot_dev {
    am_boot_serv_t         boot_serv;
    am_arm_boot_devinfo_t *p_devinfo;
}am_arm_boot_dev_t;

/**
 * \brief ��ʼ��BootLoader������BootLoader��׼����������
 *
 * \param[in] p_devinfo : ָ��BootLoader�豸��Ϣ������ָ��
 *
 * \return BootLoader��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
int am_arm_boot_init(am_arm_boot_devinfo_t *p_devinfo);


#endif /* __AM_ARM_BOOT_H */
