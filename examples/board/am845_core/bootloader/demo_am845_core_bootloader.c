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
 * \brief bootloader ���̣���demo����Ϊbootloader��
 *
 * - �������裺
 *   �ο�AMmetal-AM845-Core-bootloader�����ֲ�
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_bootloader
 * \copydoc demo_am845_core_bootloader.c
 */

#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_lpc84x.h"
#include "lpc84x_pin.h"
#include "am_boot.h"
#include "am_uart.h"
#include "am_softimer.h"
#include "am_boot_firmware.h"
#include "am_lpc84x_inst_init.h"
#include "am_bootconf_lpc845.h"
#include "am_int.h"

/** \brief 0:����bootloader��1:˫��bootloader */
#define AM_DOUBLE_BOOT              1

/** \brief �������ݽ��ջ����С */
#define UART_CALLBACK_BUF_SIZE      4096

#define RECEIVE_BUF_SIZE            64

/** \brief ������ʱʱ��(��)*/
#define BOOT_WAITE_TIME             5

/** \brief ���ڲ����� */
#define UART_BAUD                   9600

/**
 * \name bootloader״̬
 * @{
 */
/** \brief ������ʱ�ȴ�״̬ */
#define BOOT_WAIT_STATE             0

/** \brief bootloader����״̬ */
#define BOOT_STARTUP_STATE          1

/** \brief Ӧ������״̬ */
#define APP_STARTUP_STATE           2

/** \brief Ӧ�ù̼�����״̬ */
#define APP_RECEIVE_STATE           3
/** @} */

static volatile uint32_t write_offset = 0, read_offset = 0;

/** \brief bootloader������ʱ�����ʱ���ṹ�� */
static am_softimer_t timeout_timer;

/** \brief ��ʱ����ʱʱ�� */
//static uint8_t timer            = BOOT_WAITE_TIME;

/** \brief bootloader״̬*/
//static uint8_t boot_state       = BOOT_WAIT_STATE;

/** \brief һЩ���õı�־�ͳ�ʼֵ */
static volatile uint8_t second_timeout = 0, firmware_timeout = 0, timer = BOOT_WAITE_TIME, boot_state = BOOT_WAIT_STATE;


/** \brief �����жϻص����ݽ��ջ��� */
static uint8_t  uart_callback_buffer[UART_CALLBACK_BUF_SIZE] = {0};

static void __delay(void)
{
    volatile int i = 1000000;
    while(i--);
}

/**
 * \brief �����жϽ��ջص�����
 */
static void __uart_callback(void *p_arg, char inchar)
{
    if(boot_state == BOOT_WAIT_STATE) {
        timer = BOOT_WAITE_TIME;
        boot_state = BOOT_STARTUP_STATE;
    }

    if(boot_state == APP_RECEIVE_STATE)
    {
        uart_callback_buffer[write_offset++] = (uint8_t)inchar;
        write_offset &= UART_CALLBACK_BUF_SIZE - 1;
    }
}
/**
 * \brief ��ʱ���ص�����
 */
static void __timer_handle(void *p_arg)
{
    if(boot_state == BOOT_WAIT_STATE) {
        if(timer != 0) {
            timer--;
            if(timer == 0) {
                am_softimer_stop(&timeout_timer);
                timer = BOOT_WAITE_TIME;
                boot_state = APP_STARTUP_STATE;
                return;
            }
        second_timeout = 1;
      }
    }
    if (boot_state == APP_RECEIVE_STATE) {
        firmware_timeout = 1;
    }
}

/**
 * \brief  �Ӵ��ڽ��ջ�����������
 */
static int __read_data(uint8_t *p_buffer, uint32_t byte_count)
{
    uint32_t current_bytes_read = 0;
    am_softimer_start(&timeout_timer, 15000);
    while (current_bytes_read != byte_count) {
        if(firmware_timeout == 1) {
            firmware_timeout = 0;
            am_softimer_stop(&timeout_timer);
            return AM_ERROR;
        }

        if(read_offset != write_offset) {
            p_buffer[current_bytes_read++] = uart_callback_buffer[read_offset++];
            read_offset &= UART_CALLBACK_BUF_SIZE - 1;
        }
    }
    firmware_timeout = 0;
    am_softimer_stop(&timeout_timer);
    return AM_OK;
}

/**
 * \brief bootloader demo���
 */
void demo_am845_core_bootloader_entry (void)
{
    am_boot_firmware_verify_info_t firmware_head;
    am_boot_firmware_handle_t      firmware_handle;
    int ret = -1, i, count;
    /* bootloader flash��ʼ��  */
    am_boot_flash_handle_t flash_handle = am_lpc845_boot_flash_inst_init();
    /* bootloader ��׼�ӿڳ�ʼ��  */
    am_lpc845_std_boot_inst_init(flash_handle);

    am_uart_handle_t uart_handle = am_lpc84x_usart0_inst_init ();
    am_debug_init(uart_handle, UART_BAUD);

    /* ʹ�ܴ����ж�ģʽ  */
    am_uart_ioctl(uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    /* ע�ᷢ�ͻص�����  */
    am_uart_callback_set(uart_handle, AM_UART_CALLBACK_RXCHAR_PUT, __uart_callback, NULL);
    /* ������ʱ�ص���ʱ����ʼ��  */
    am_softimer_init(&timeout_timer, __timer_handle, NULL);
    am_kprintf("Device will enter application, if don't input anything after %ds\r\n",timer);
    am_softimer_start(&timeout_timer, 1000);

    /* ��ʱ�ȴ�������û������ݷ������ͽ���bootloader��������ת��Ӧ�ó��� */
    while(boot_state == BOOT_WAIT_STATE) {
        if(second_timeout == 1) {
            am_kprintf("Device will enter application, if don't input anything after %ds\r\n",timer);
            second_timeout = 0;
        }
    }
    am_softimer_stop(&timeout_timer);

#if AM_DOUBLE_BOOT
    /* �û��������͹�����ʾҪ����bootloader����������������bootloader������־Ϊ˫����Ч�����½��ܹ̼�  */
    if( boot_state == BOOT_STARTUP_STATE) {
        am_boot_update_flag_set(AM_BOOTLOADER_FLAG_NO);
    }
#endif

    /* ����ʱ�ȴ��ڼ�û���û����룬��ת��Ӧ�ó������Ӧ�ó���û׼���ã�ֱ�ӽ���bootloader��������  */
    if(boot_state == APP_STARTUP_STATE && am_boot_app_is_ready()) {
        __delay();
        am_lpc84x_usart0_inst_deinit(uart_handle);
        am_lpc84x_clk_inst_deinit();
        am_boot_go_application();
    }

    am_kprintf("bootloader : running......\r\n");
    while(1) {
        am_kprintf("bootloader : update init\r\n");
        /* �̼���ű�׼�ӿڳ�ʼ��  */
        firmware_handle = am_lpc845_boot_firmware_flash(flash_handle);
        /* ��ʼ�̼����  */
#if AM_DOUBLE_BOOT
        am_boot_firmware_store_start(firmware_handle, 26 * 1024);
#else
        am_boot_firmware_store_start(firmware_handle, 49 * 1024);
#endif
        /* �л�Ϊ�̼�����״̬  */
        boot_state = APP_RECEIVE_STATE;
        am_kprintf("bootloader : firmware transmission is ready\r\n");

        /* �Ӵ������ݻ������ж�ȡ�̼���ͷ����Ϣ  */
        if(AM_OK != __read_data((uint8_t *)&firmware_head, sizeof(firmware_head))) {
            am_kprintf("bootloader : firmware transmission is timeout, bootloader will restart!\r\n");
            continue;
        }

        count = firmware_head.len / RECEIVE_BUF_SIZE;
        uint8_t buf_t[RECEIVE_BUF_SIZE] = {0};
        am_kprintf("bootloader : receiving firmware ...\r\n");
        for(i = 0; i < count; i++) {

            ret = __read_data((uint8_t *)buf_t, sizeof(buf_t));


            if(AM_OK != ret) {
                am_kprintf("bootloader : firmware transmission is timeout, bootloader will restart!\r\n");
                break;
            }
            /* �̼����   */
            ret = am_boot_firmware_store_bytes(firmware_handle, (uint8_t *)buf_t, sizeof(buf_t));
            if(ret != AM_OK) {
                am_kprintf("bootloader : firmware store is error, bootloader will restart!\r\n");
                break;
            }
        }
        if(AM_OK != ret) {
            continue;
        }

        if (firmware_head.len & (RECEIVE_BUF_SIZE - 1)) {
            if(AM_OK != __read_data((uint8_t *)buf_t, firmware_head.len & (RECEIVE_BUF_SIZE - 1))) {

                am_kprintf("bootloader : firmware transmission is error, bootloader will restart!\r\n");
                continue;
            }

            if(AM_OK != am_boot_firmware_store_bytes (firmware_handle,
                                                     (uint8_t *)buf_t,
                                                     firmware_head.len & (RECEIVE_BUF_SIZE - 1))) {
                am_kprintf("bootloader : firmware store is error, bootloader will restart!\r\n");
                continue;
            }
        }
        /* �̼���Ž���  */
        am_boot_firmware_store_final(firmware_handle);
        am_kprintf("bootloader : firmware receive successful\r\n");
        /* �̼�У��  */
        ret = am_boot_firmware_verify(firmware_handle, &firmware_head);
        if(ret != AM_OK) {
            am_kprintf("bootloader : firmware verify error, bootloader will restart!\r\n");
            continue;
        } else {
            am_kprintf("bootloader : firmware verify successful\r\n");
        }

#if  AM_DOUBLE_BOOT
        /* ���� bootloader ��������־ΪӦ�ó�����Ч  */
        ret = am_boot_update_flag_set(AM_BOOTLOADER_FLAG_APP);
        if(ret != AM_OK) {
            am_kprintf("bootloader : set update flag fail\r\n");
            continue;
        }
#endif

        if(am_boot_app_is_ready()) {
            am_kprintf("bootloader : go to application...\r\n");
            __delay();
            am_lpc84x_usart0_inst_deinit(uart_handle);
            am_lpc84x_clk_inst_deinit();
            /* ��ת��Ӧ�ó���  */
            if(AM_OK != am_boot_go_application()){
                continue;
            }
        }
    }
}

/* end of file */
