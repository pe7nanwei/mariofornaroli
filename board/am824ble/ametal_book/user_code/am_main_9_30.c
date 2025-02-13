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
 * \brief �����嵥9.30
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg9021.h"
#include "am_delay.h"
#include "am_hwconf_zlg9021.h"

int am_main (void)
{
    uint8_t  buf[10];
      am_zlg9021_handle_t  zlg9021_handle = am_zlg9021_inst_init();
        am_zlg9021_ioctl(zlg9021_handle, AM_ZLG9021_RESET, NULL);         // ��λZLG9021
        
        am_zlg9021_ioctl(zlg9021_handle, AM_ZLG9021_TIMEOUT, (void*)100); // ���ó�ʱʱ��100ms
        
    while(1) {
        int len = am_zlg9021_recv(zlg9021_handle, buf, 10);
        if (len > 0) {                                                    // �ɹ����յ�����Ϊlen ���ֽڵ�����
            am_zlg9021_send(zlg9021_handle, buf, len);
       }
            am_mdelay(100);
    }
}
 
/* end of file */
