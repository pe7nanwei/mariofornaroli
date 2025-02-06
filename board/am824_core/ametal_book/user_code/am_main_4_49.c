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
 * \brief �����嵥4.49
 *
 * \note ��������Ҫ�õ�miniport��չ��
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "hc595.h"
#include "am_delay.h"

int am_main(void)
{
    uint8_t data = 0x01;                      // ��ʼ��bit0Ϊ1����ʾ����LED0

    hc595_init();
    while(1) {
        hc595_send_data(~data);               // dataȡ������LED
        am_mdelay(100);
        data <<= 1;
        if (data == 0) {                      // 8��ѭ�����������´�0x01��ʼ
            data = 0x01;
        }
    }
}



/* end of file */

