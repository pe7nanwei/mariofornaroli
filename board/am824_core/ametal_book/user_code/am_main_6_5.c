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
 * \brief �����嵥6.5
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-18  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_lpc82x_inst_init.h"
#include "am_ep24cxx.h"
#include "am_hwconf_microport.h"

int app_test_ep24cxx (am_ep24cxx_handle_t handle)
{
    int  i;
    uint8_t data[20];

    for (i = 0; i < 20; i++)                        // �������
        data[i] = i;
    am_ep24cxx_write(handle, 0, &data[0], 20);      // ��0��ַ��ʼ������д��20�ֽ�����
    for (i = 0; i < 20; i++)                        // ��������
        data[i] = 0;
    am_ep24cxx_read(handle, 0, &data[0], 20);       // ��0��ַ��ʼ����������20�ֽ�����
    for (i = 0; i < 20; i++) {                      // �Ƚ�����
        if (data[i] != i)        return AM_ERROR;
    }
    return AM_OK;
}

int am_main (void)
{
    am_ep24cxx_handle_t fm24c02_handle = am_microport_eeprom_inst_init();
    if (app_test_ep24cxx(fm24c02_handle) != AM_OK) {
        am_led_on(0);        while(1);
    }
    while (1) {
        am_led_toggle(0);        am_mdelay(100);
    }
}


/* end of file */

