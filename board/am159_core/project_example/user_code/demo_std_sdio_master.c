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
    int len = 0;
    uint8_t            rd_buf[512] = {0}; /* �����ݻ��涨�� */
    am_err_t           ret;
    am_sdcard_handle_t sdcard_handle;

    for ( i = 0; i < sizeof(wr_buf); i++) {
        wr_buf[i] = 0xaa;
    }

    sdcard_handle = am_sdcard_inst_init();

//    len = am_sdcard_write(sdcard_handle, wr_buf, 0x00 , 1);

    len = am_sdcard_read(sdcard_handle, rd_buf, 0x00, 1);

    for(i = 0; i < len; i++) {
        am_kprintf( "%2x ", rd_buf[i]);
    }

    am_mdelay(10);
    while(1) {

        //am_sdcard_erase(sdcard_handle, 0x00, 0x1);
        len = am_sdcard_read(sdcard_handle, rd_buf, 0x4000 , 1);

        am_kprintf( "len = %d \r\n", len);

        for(i = 0; i < len; i++) {
            am_kprintf( "%2x ", rd_buf[i]);
        }

        am_kprintf( "\r\n");
    }

}
/** [src_std_sdio_master_async] */

/* end of file */
