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
 * \brief FLASH ���̣�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. �����������ڴ�ӡ"erase error!"��
 *   2. д��������ڴ�ӡ"program error!"��
 *   3. д��ɹ������ڴ�ӡ 55 ������(1024/4)�� 32bit ʮ���������ݡ�
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIOA_10 �������� PC ���ڵ� TXD��
 *    PIOA_9 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_zlg237_drv_flash.c src_zlg237_drv_flash
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  ari, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg237_drv_flash
 * \copydoc demo_zlg237_drv_flash.c
 */

/** [src_zlg237_drv_flash] */
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_zlg237_flash.h"
#include "am_zlg237.h"
#include "demo_zlg_entries.h"
#include "demo_am237_core_entries.h"

#define FLASH_PAGE           50    /**< \brief ҳ�� */

void __zlg237_drv_flash_entry (amhw_zlg237_flash_t *p_hw_flash, uint8_t page_num)
{
    int             i;
    uint32_t        status;         /* FLASH ����ִ��״̬ */
    static uint32_t data[1024 / 4]; /* Ҫд�� FLASH ������ */
    static uint32_t temp[1024 / 4]; /* �� FLASH �ж��������� */

    /* ���ݳ�ʼ�� */
    for (i = 0; i < 1024 / 4; i++) {
        data[i] = i;
    }

    /* FLASH ��ʼ�� */
    am_zlg237_flash_init(p_hw_flash);

    /* �������� */
    status = am_zlg237_flash_page_erase(p_hw_flash, page_num * 1024);

    /* ������������ ����ͣ�ڴ˴� */
    if (0 != status) {
        AM_DBG_INFO("erase error!\r\n");

        AM_FOREVER;
    }

    /* ��������д������ */
    status = am_zlg237_flash_sector_program(p_hw_flash,
                                            page_num * 1024,
                                            data,
                                            1024 / 4);

    /* ����д���������ͣ�ڴ˴� */
    if ((1024 / 4) != status) {
        AM_DBG_INFO("program error!\r\n");

        AM_FOREVER;
    }

    /* ��������ȡ���� */
    for (i = 0; i < 1024 / 4; i++) {
        temp[i] = *(uint32_t *)((i * 4) + (page_num * 1024));

        /* У�����ݣ�У��ʧ�ܣ�����ͣ�ڴ˴� */
        if (temp[i] != data[i]) {
            AM_DBG_INFO("verify error!\r\n");
            AM_FOREVER;
        }
    }

    AM_DBG_INFO("\r\nflash test success!\r\n");

    AM_FOREVER {
        ; /* VOID */
    }
}

/**
 * \brief �������
 */
void demo_zlg237_core_drv_flash_entry (void)
{
    AM_DBG_INFO("demo am237_core drv flash!\r\n");

    __zlg237_drv_flash_entry(ZLG237_FLASH, FLASH_PAGE);
}

/** [src_zlg237_drv_flash] */

/* end of file */
