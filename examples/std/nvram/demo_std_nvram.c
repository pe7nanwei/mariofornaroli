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
 * \brief  NVRAM �ӿ�����
 *
 *  ����ʹ�õĴ洢������ __g_nvram_segs[] �б��ж��壨am_nvram_cfg.c �ļ��У�
 *
 * - ʵ������
 *   1. ���Դ��ڴ�ӡ�����Խ����
 *
 * \par Դ����
 * \snippet demo_std_nvram.c src_std_nvram
 *
 * \internal
 * \par Modification history
 * - 1.00  17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_nvram
 * \copydoc demo_std_nvram.c
 */

/** [src_std_nvram] */
#include "ametal.h"
#include "am_nvram.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_ep24cxx.h"

#define __BUF_SIZE 16 /**< \brief ��������С */

/**
 * \brief �������
 */
void demo_std_nvram_entry (char *p_nvram_name, int32_t nvram_unit, int32_t test_lenth)
{
    uint8_t  wr_buf[__BUF_SIZE] = {0}; /* д���ݻ��涨�� */
    uint8_t  rd_buf[__BUF_SIZE] = {0}; /* �����ݻ��涨�� */
    uint16_t i;
    int      ret;

    if (__BUF_SIZE < test_lenth) {
        test_lenth = __BUF_SIZE;
    }

    /* ��䷢�ͻ����� */
    for (i = 0;i < test_lenth; i++) {
        wr_buf[i] = i;
    }

    /* д���� */
    ret = am_nvram_set(p_nvram_name,
                       nvram_unit,
                      &wr_buf[0],
                       0,
                       test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("nvram write error(id: %d).\r\n", ret);
        return;
    }
    am_mdelay(5);

    /* ������ */
    ret = am_nvram_get(p_nvram_name,
                       nvram_unit,
                      &rd_buf[0],
                       0,
                       test_lenth);

    if (ret != AM_OK) {
        AM_DBG_INFO("nvram read error(id: %d).\r\n", ret);
        return;
    }

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0; i < test_lenth; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is 0x%02x\r\n", i ,rd_buf[i]);

        /* У��ʧ�� */
        if(wr_buf[i] != rd_buf[i]) {
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
/** [src_std_nvram] */

/* end of file */
