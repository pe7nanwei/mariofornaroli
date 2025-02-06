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
 * \brief �����嵥7.17
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_hc595.h"
#include "am_delay.h"
#include "am_hwconf_miniport.h"

int am_main(void)
{
    am_hc595_handle_t  hc595_handle = am_miniport_595_inst_init();
    uint8_t             data        = 0x01;        // ��ʼ��bit0Ϊ1����ʾ����LED0
    while(1) {
       uint8_t temp = ~data;                       // dataȡ������LED
       am_hc595_send(hc595_handle, &temp, 1);
       am_mdelay(100);
       data <<= 1;
       if (data == 0) {                            // 8��ѭ�����������´�0x01��ʼ
           data = 0x01;
       }
   }
}

/* end of file */

