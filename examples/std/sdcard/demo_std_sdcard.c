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
 * \brief SD������д����
 *
 * - �������裺
 *   1. ��SD�����뿨��
 *
 * - ʵ������
 *   1. ����SD��ָ���飻
 *   2. д������ݣ�
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ��������ȡ��������д������ݲ�һ�£����ӡ"sd card test error"��ֹͣ��
 *
 * - ע�⣺
 *   1. ���д�demo���ܻ��ƻ�SD��ԭ�е��ļ�ϵͳ��ע�ⱸ�ݱ���SD����ԭ������Ҫ�ļ�
 *
 * \par Դ����
 * \snippet demo_std_sdcard.c src_std_sdcard
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-14  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_sdcard
 * \copydoc demo_std_sdcard.c
 */

/** [src_std_std_sdcard] */
#include "ametal.h"
#include "am_sdio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_sdcard.h"

#define __READ_BLOCKS  2       /* �����ݿ���� */
#define __WRITE_BLOCKS 6       /* д���ݿ���� */
#define __ERASE_BLOCKS 10      /* �������ݿ���� */

#define __BLOCK_SIZE   512     /* ���ݿ��С */

static uint8_t __g_wr_buf[__BLOCK_SIZE * __WRITE_BLOCKS] = {0}; /* д���ݻ��涨�� */
static uint8_t __g_rd_buf[__BLOCK_SIZE * __READ_BLOCKS]  = {0}; /* �����ݻ��涨�� */
/**
 * \brief �������
 */
void demo_std_sdcard_entry (am_sdcard_handle_t handle)
{
    uint16_t           i;
    am_err_t           ret;
    uint32_t           count = 0;

    if (handle == NULL) {
        am_kprintf( "sd card init failed\r\n");
        while(1);
    }

    /* д���ݻ��渳��ֵ */
    for (i = 0; i < sizeof(__g_wr_buf); i++) {
        __g_wr_buf[i] = i;
    }

    /* ����ָ���� */
    ret = am_sdcard_blocks_erase(handle, 1000, __ERASE_BLOCKS);
    if (ret != AM_OK) {
        am_kprintf( "sdcard blocks erase failed\r\n");
    }

    /* ָ����д������ */
    ret = am_sdcard_blocks_write(handle, __g_wr_buf, 1000, __WRITE_BLOCKS);
    if (ret != AM_OK) {
        am_kprintf( "sdcard blocks write failed\r\n");
    }

    count = 0;
    while(1) {

        /* ָ�����ȡ���� */
        ret = am_sdcard_blocks_read(handle,
                                    __g_rd_buf,
                                    1000 + count,
                                    __READ_BLOCKS);

        if (ret == AM_OK) {
            for(i = 0; i < __BLOCK_SIZE * __READ_BLOCKS; i++) {

                am_kprintf("%02x ", __g_rd_buf[i]);

            }
            am_kprintf( "\r\n\r\n");
        }
        count += __READ_BLOCKS;

        am_mdelay(1000);
    }

}
/** [src_demo_std_sdcard] */

/* end of file */
