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

#define __BUF_SIZE 8 /** \brief ��������С */

/**
 * \brief SDIO ������ɻص�����
 */
static void __sdio_msg_callback (void *p_arg)
{
    AM_DBG_INFO("SDIO async transfer complete!\r\n");
}

extern am_sdcard_handle_t am_sdcard_inst_init (void);

/**
 * \brief �������
 */
void demo_std_sdio_master_entry ()
{
    uint8_t            wr_buf[512] = {0}; /* д���ݻ��涨�� */
    int                i;
    int                len = 0;
    uint8_t            rd_buf[512] = {0}; /* �����ݻ��涨�� */
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

//    len = am_sdcard_write(sdcard_handle, wr_buf, 0x80000 , 1);

    len = am_sdcard_read(sdcard_handle, rd_buf, 0x00, 1);

    for(i = 0; i < len; i++) {
        am_kprintf( "%02x ", rd_buf[i]);
    }
    am_kprintf( "\r\n");

//    am_sdcard_erase(sdcard_handle, 0x40000, 1);

    am_mdelay(10);
    while(1) {

        len = am_sdcard_read(sdcard_handle,
                            rd_buf,
                            0x00,
                            1);

//        len = am_sdcard_read(sdcard_handle,
//                            rd_buf,
//                            0x80000 + (count * sdcard_handle->sdcard_info.card_block_size),
//                            1);

        am_kprintf( "len = %d \r\n", len);

        for(i = 0; i < len; i++) {
            am_kprintf( "%02x ", rd_buf[i]);
        }

        am_kprintf( "\r\n");

        count++;
    }

}
/** [src_std_sdio_master_async] */

/* end of file */
