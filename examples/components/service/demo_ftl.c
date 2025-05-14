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
 * \brief FTL��Flash Translation Layer������
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_ftl.c src_ftl
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_ftl
 * \copydoc demo_ftl.c
 */

/** [src_ftl] */
#include "ametal.h"
#include "am_ftl.h"
#include "am_delay.h"
#include "am_vdebug.h"

#define __BUF_SIZE 16 /**< \brief ��������С */

/**
 * \brief �������
 */
void demo_ftl_entry (am_ftl_handle_t ftl_handle, int32_t test_lenth)
{
    uint8_t  buf[__BUF_SIZE] = {0};    /* ���ݻ��� */
    uint16_t i;
    int      ret;

    if (__BUF_SIZE < test_lenth) {
        test_lenth = __BUF_SIZE;
    }

    /* ��䷢�ͻ����� */
    for (i = 0;i < test_lenth; i++) {
        buf[i] = i;
    }

    /* д���� */
    ret = am_ftl_write(ftl_handle, 0, &buf[0]);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_ftl_write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);

    /* ������ */
    ret = am_ftl_read(ftl_handle, 0, &buf[0]);

    if (ret != AM_OK) {
        AM_DBG_INFO("am_ftl_read error(id: %d).\r\n", ret);
        return;
    }

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read FLASH the %2dth data is %2x\r\n", i ,buf[i]);

        /* У��ʧ�� */
        if(buf[i] != i) {
            AM_DBG_INFO("verify failed at index %d.\r\n", i);
            break;
        }
    }

    if (test_lenth == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_ftl] */

/* end of file */
