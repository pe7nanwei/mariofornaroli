/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ����ģ���Զ����������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��Ƭ���ֱ���ͨ�� 4800��9600��19200��38400��57600��115200��230400��
 *      460800��1000000����ZLG52810��
 *
 *   2. ������ӳɹ������ڴ�ӡ�ᵱǰ�Ĳ�����, MCU���Ὣ���յ�����Ϣ�ش��������Լ�BLEģ��
 *
 *   3. �������ʧ�ܣ�LED0 �� 100 ms �ļ������˸��
 *
 * \par Դ����
 * \snippet demo_zlg52810_baudrate.c src_zlg52810_baudrate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-08  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zlg52810_baudrate
 * \copydoc demo_zlg52810_baudrate.c
 */

/** [src_zlg52810_baudrate] */
#include "ametal.h"
#include "am_zlg52810.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "am_led.h"
#include "string.h"
#include "demo_components_entries.h"

/**
 * \brief ����˸ LED0
 */
static void flash_led (void)
{
    while (1) {
        am_led_on(0);
        am_mdelay(100);
        am_led_off(0);
        am_mdelay(100);
    }
}

/**
 * \brief �������
 */
void demo_zlg52810_baudrate_entry (am_zlg52810_handle_t zlg52810_handle)
{
    uint8_t   temp[50] = {0};
    int32_t   i                       = 0;
    uint32_t  zlg52810_baudrate       = 20;
    uint32_t  zlg52810_baudrate_tab[] = {4800, 9600, 19200, 38400, 57600,
                                         115200, 230400, 460800, 1000000};

    /* ��������ģ�� */
    for (i = 0; i < AM_NELEMENTS(zlg52810_baudrate_tab); i++) {

        /* ������ ZLG52810 ͨ�ŵĴ��ڵĲ����� */
        am_uart_ioctl(zlg52810_handle->uart_handle,
                      AM_UART_BAUD_SET,
                      (void *)zlg52810_baudrate_tab[i]);

        /* ���Ի�ȡ ZLG52810 �Ĳ����� */
        am_zlg52810_ioctl(zlg52810_handle,
                         AM_ZLG52810_BAUD_GET,
                         (void *)&zlg52810_baudrate);


        if (i == zlg52810_baudrate) {
            AM_DBG_INFO("ZLG52810 BAUDRATE: %d\r\n", zlg52810_baudrate_tab[i]);
            sprintf((char *)temp, "ZLG52810 BAUDRATE: %d", (int)zlg52810_baudrate_tab[i]);
            am_mdelay(100);
            am_zlg52810_send(zlg52810_handle,
            (const uint8_t *)temp,
                             strlen((const char *)temp));
            break;
        }
    }

    if (i == AM_NELEMENTS(zlg52810_baudrate_tab)) {
        AM_DBG_INFO("AM_ZLG52810_BAUD_GET failed\r\n");
        flash_led();
    }

    while (1) {
        uint8_t count = 1;
        uint8_t i     = 0;
        count = am_zlg52810_recv(zlg52810_handle, temp, count);
        am_zlg52810_send(zlg52810_handle, (const uint8_t *)temp, count);
        for(i = 0; i < count; i++){
            am_kprintf("%c", temp[i]);
        }
        am_mdelay(50);
    }
}

/** [src_zlg52810_baudrate] */

/* end of file */
