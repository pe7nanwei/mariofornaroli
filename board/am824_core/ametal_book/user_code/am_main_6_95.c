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
 * \brief �����嵥6.95
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-19  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_hwconf_microport.h"
#include "am_led.h"

int am_main (void)
{
    am_ds1302_handle_t   ds1302_handle = am_microport_ds1302_inst_init();
    uint8_t               data[31];
    int     i;
    for (i = 0; i < 31; i++) {
        data[i] = i;
    }
    am_ds1302_ram_write (ds1302_handle, data, 31, 0);    // ����ʼ��ַ0��ʼд��31�ֽ�����
    
    for (i = 0; i < 31; i++) {
        data[i] = 0;
    }
    am_ds1302_ram_read (ds1302_handle, data, 31, 0);    // ����ʼ��ַ0��ʼ����31�ֽ�����
    for (i = 0; i < 31; i++) {
        if (data[i] != i) {
            am_led_on(0);
        }
    }
    while(1) {
    }
}


/* end of file */

