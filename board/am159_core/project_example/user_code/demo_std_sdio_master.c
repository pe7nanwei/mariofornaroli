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
 * \brief SDIO �������� EEPROM �豸���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���� EEPROM �� SDIO ���ŵ���Ӧ���š�
 *
 * - ʵ������
 *   1. д���ݵ� EEPROM��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_std_sdio_master_async.c src_std_sdio_master_async
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_sdio_master_async
 * \copydoc demo_std_sdio_master_async.c
 */

/** [src_std_sdio_master_async] */
#include "ametal.h"
#include "am_sdio.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_sdcard.h"

extern am_sdcard_handle_t am_sdcard_inst_init (void);

uint8_t            wr_buf[512 * 5] = {0}; /* д���ݻ��涨�� */
uint8_t            rd_buf[512 * 2] = {0}; /* �����ݻ��涨�� */

/**
 * \brief �������
 */
void demo_std_sdio_master_entry ()
{
    int                i;
    am_err_t           ret;
    am_sdcard_handle_t sdcard_handle;
    uint32_t           count = 0;

    for ( i = 0; i < sizeof(wr_buf); i++) {
        wr_buf[i] = i;
    }

    sdcard_handle = am_sdcard_inst_init();

    am_mdelay(100);

    if (sdcard_handle == NULL) {
        am_kprintf( "sd card init failed\r\n");
        while(1);
    }

    am_kprintf( "sd card init successful\r\n");

    ret = am_sdcard_blocks_erase(sdcard_handle, 200, 6);
    if (ret != AM_OK) {
        am_kprintf( "sdcard block erase failed\r\n");
    }

    ret = am_sdcard_blocks_write(sdcard_handle, wr_buf, 200, 4);
    if (ret != AM_OK) {
        am_kprintf( "sdcard single block write failed\r\n");
    }

    while(1) {

        ret = am_sdcard_blocks_read(sdcard_handle,
                                    rd_buf,
                                    200 + count,
                                    1);

        if (ret == AM_OK) {
            for(i = 0; i < 512 * 2; i++) {
                am_kprintf( "%02x ", rd_buf[i]);
//                if ((wr_buf[i] != rd_buf[i]) && (count == 0)) {
//                    am_kprintf( "\r\n error \r\n");
//                    while(1);
//                }
            }
            am_kprintf( "\r\n\r\n");
        }
        count++;
    }

}
/** [src_std_sdio_master_async] */

/* end of file */
