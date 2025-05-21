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
 * \brief I2C �������� EEPROM �豸���̣�ͨ���첽��׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���� EEPROM �� I2C ���ŵ���Ӧ���š�
 *
 * - ʵ������
 *   1. д���ݵ� EEPROM��
 *   2. �����ղ�д������ݣ�
 *   3. ���Դ��ڴ�ӡ���Խ����
 *
 * \par Դ����
 * \snippet demo_std_i2c_master_async.c src_std_i2c_master_async
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_i2c_master_async
 * \copydoc demo_std_i2c_master_async.c
 */

/** [src_std_i2c_master_async] */
#include "ametal.h"
#include "am_i2c.h"
#include "am_delay.h"
#include "am_vdebug.h"

#define __BUF_SIZE 8 /** \brief ��������С */

/**
 * \brief I2C ������ɻص�����
 */
void __i2c_msg_callback (void *p_arg)
{
    AM_DBG_INFO("I2C async transfer complete!\r\n");
}

/**
 * \brief �������
 */
void demo_std_i2c_master_async_entry (am_i2c_handle_t handle,
                                      uint32_t        eeprom_addr,
                                      uint32_t        test_len)
{
    uint8_t           i;
    uint8_t           sub_addr;
    uint8_t           wr_buf[__BUF_SIZE] = {0}; /* д���ݻ��涨�� */
    uint8_t           rd_buf[__BUF_SIZE] = {0}; /* �����ݻ��涨�� */
    am_err_t          ret;
    am_i2c_message_t  msg;
    am_i2c_transfer_t trans[4];

    if (__BUF_SIZE < test_len) {
        test_len = __BUF_SIZE;
    }

    /**
     * ���촫��ṹ��
     * �� 1 �����䷢�ʹӻ��ӵ�ַ
     * �� 2 ������� wr_buf �������ݵ� EEPROM
     * �� 3 �����䷢�ʹӻ��ӵ�ַ
     * �� 4 ������� EEPROM ��ȡ���ݵ� rd_buf
     */
    sub_addr = 0x00;
    am_i2c_mktrans(&trans[0],
                    eeprom_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_WR,
                   &sub_addr,
                    1);

    /* ��䷢�ͻ����� */
    for (i = 0;i < test_len; i++) {
        wr_buf[i] = (i + 6);
    }

    am_i2c_mktrans(&trans[1],
                    eeprom_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE |
                    AM_I2C_M_WR | AM_I2C_M_NOSTART,
                   &wr_buf[0],
                    test_len);

    /* ������Ϣ */
    am_i2c_mkmsg(&msg, &trans[0], 2, __i2c_msg_callback, NULL);

    /* �����첽��Ϣ���� */
    ret = am_i2c_msg_start(handle, &msg);
    if (ret != AM_OK) {
        AM_DBG_INFO("am_i2c_msg_start error(id: %d).\r\n", ret);
        return;
    }

    /* ��ʱһС��ʱ�䣬�����ݴ���������ٽ�������У�� */
    am_mdelay(100);

    am_i2c_mktrans(&trans[2],
                    eeprom_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_WR,
                   &sub_addr,
                    1);

    am_i2c_mktrans(&trans[3],
                    eeprom_addr,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_RD,
                   &rd_buf[0],
                    test_len);

    /* ������Ϣ */
    am_i2c_mkmsg(&msg, &trans[2], 2, __i2c_msg_callback, NULL);

    /* �����첽��Ϣ���� */
    ret = am_i2c_msg_start(handle, &msg);
    if (ret != AM_OK) {
        AM_DBG_INFO("am_i2c_msg_start error(id: %d).\r\n", ret);
        return;
    }

    /* ��ʱһС��ʱ�䣬�����ݴ���������ٽ�������У�� */
    am_mdelay(100);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < test_len; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is 0x%02x\r\n", i ,rd_buf[i]);

        /* У��ʧ�� */
        if(wr_buf[i] != rd_buf[i]) {
            AM_DBG_INFO("verify failed at index %d.\r\n", i);
            break;
        }
    }

    if (test_len == i) {
        AM_DBG_INFO("verify success!\r\n");
    }

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_i2c_master_async] */

/* end of file */
