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
 * \brief bootloader��Ϣ��ͨ����־����������
 *
 * \internal
 * \par modification history:
 * - 1.00 18-11-30  yrh, first implementation.
 * \endinternal
 */

#ifndef __AM_BOOT_MSG_FLAG_H
#define __AM_BOOT_MSG_FLAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_boot_msg.h"
#include "am_boot_memory.h"



/**
 * \brief ��Ϣ�豸��Ϣ����־ʵ�֣�
 */
typedef struct am_boot_msg_flag_devinfo {
    /**< \brief �̼���������ʼ��ַ  */
    uint32_t  upt_sta_addr;
    /** \brief Ӧ������С */
    uint32_t  app_area_size;
    /** \brief ��־�����ʼ��ַ */
    uint32_t  flag_addr;
    /** \brief ��־ռ�õ�ʵ�ʴ�С��һ��Ϊ�ڴ���С��д�뵥Ԫ�����ʹ��flash�ڴ棬��Ϊ��С�Ĳ�����Ԫ*/
    uint32_t  flag_occupy_size;
    /** \brief �̼���������Ҫ�ӹ̼��ı�������������Ӧ�ó����ִ����*/
    int     (*pfn_firwa_cpy)(uint32_t dst_addr, uint32_t src_addr);
}am_boot_msg_flag_devinfo_t;

/**
 * \brief ͨ����־������Ϣ���豸
 */
typedef struct am_boot_msg_flag_dev {
    am_boot_msg_serv_t            isa;          /**< \brief ��׼����Ϣ����  */
    am_boot_msg_flag_devinfo_t   *p_devinfo;    /**< \brief �豸��Ϣ�ṹ�� */
    am_boot_mem_handle_t          mem_handle;   /**< \brief memory�ı�׼����������  */
    uint32_t                      app_sta_addr; /**< \brief Ӧ�ó����ڴ��ŵ���ʼ��ַ  */
} am_boot_msg_flag_dev_t;


/**
 * \brief ��Ϣ�豸��ʼ������־ʵ�֣�
 *
 * \return flash ��׼����������
 */
am_boot_msg_handle_t am_boot_msg_flag_init(am_boot_msg_flag_devinfo_t *p_devinfo,
                                           am_boot_mem_handle_t        mem_handle);


#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_MSG_FLAG_H */

/* end of file */
