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
 * \brief bootloader ���̣���demo����Ϊ������Ӧ�ó����޷���Ӧ�ó�������������
 *
 * - ��������
 *   1. LED����˸������ѭ����ӡ��
 *   
 *
 * \note
 *    �̼�����
 *
 *    ����ametal/tools/bootloader/�̼�У��/ �ļ��У�Ŀ¼����һ��bin_chek_sum.bin��ִ���ļ���
 *    �������̱������bin�ļ���������bin_chek_sum.binͬһ��Ŀ¼�£�
 *    �ڸ�Ŀ¼�´�cmd�������������������룺
 *         bin_chek_sum.bin  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-18  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_delay.h"

void demo_zlg217_core_single_application_entry (void)
{
    AM_DBG_INFO("application : am217_core application start up successful!\r\n");

    while(1) {
        AM_DBG_INFO("application : am217_core application running\r\n");
        am_led_toggle(0);
        am_mdelay(1000);
    }
}

/* end of file */
