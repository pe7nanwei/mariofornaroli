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
 * \brief �����嵥6.70
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
    am_pcf85063_handle_t pcf85063_handle = am_microport_rtc_inst_init();
    uint8_t              data            = 0x00;
    
    am_pcf85063_ram_write (pcf85063_handle,  0x55);  // д������0x55
    am_pcf85063_ram_read (pcf85063_handle,  &data);  // ��ȡ����
    
    if (data != 0x55) {   // �����ݲ�Ϊ0x55�������д���������LED0
        am_led_on(0);
    }
    while(1) {
    }
}


/* end of file */

