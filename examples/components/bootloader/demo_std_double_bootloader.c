/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2019 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief bootloader ˫��bootloader ͨ�����ڴ��䣬�������ַ��͹̼�������
 *
 *
 * \par Դ����
 * \snippet demo_std_double_bootloader.c src_std_double_bootloader
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-04 yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_double_bootloader
 * \copydoc demo_std_double_bootloader.c
 */

/** [src_std_double_bootloader] */
#include "am_boot_msg_flag.h"
#include "am_boot_firmware_recv.h"
#include "am_boot_firmware.h"
#include "am_boot_enter_check.h"
#include "am_boot.h"
#include "am_vdebug.h"

void demo_std_double_bootloader_entry(am_boot_firwa_recv_handle_t  firwa_recv_handle,
                                      am_boot_enter_check_handle_t enter_check_handle,
                                      am_boot_msg_handle_t         msg_handle)
{
    int ret;
    /* �Ƿ����Ӧ�ó�����  */
    if(am_boot_enter_check(enter_check_handle)) {
        /* ��Ϣ���� */
        ret = am_boot_msg_dispose(msg_handle);
        if(ret == AM_OK) {
            /* �ж�Ӧ�ó����Ƿ���Ч */
            if(am_boot_app_is_ready()) {
                /* ��ת��Ӧ�ó��� */
                am_boot_go_application();
            }
        }
    }

    while(1) {
        /* �̼����� */
        ret = am_boot_firmware_recv(firwa_recv_handle);
        if(ret == AM_OK) {
            /* �̼����ճɹ������ñ�־ΪӦ�ó�����������Ч */
            am_boot_msg_set(msg_handle, (void *)AM_BOOTLOADER_FLAG_APP);
            break;
        } else {
            /* ����̼�����ʧ�ܣ����½��չ̼� */
            am_kprintf("boot : firmware receive fail,restart receive firmware\r\n");
        }
    }

    if(am_boot_app_is_ready()) {
        am_boot_go_application();
    }
}
/** [src_std_double_bootloader] */

/* end of file */
