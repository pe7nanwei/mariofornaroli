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
 * \brief ZM516���߹̼��������̣���demoʵ��zigbee�̼����գ�����ΪB���bootloader��
 * \note
 *    1. ����0��Ҫ��PC���ӣ�ͨ���������ַ��͹̼���������Ϊ115200���������ӹ�ϵ���£�
 * <pre>
 *           PIO0_0   <-->  PC_TX
 *           PIO0_4   <-->  PC_RX
 *
 *    ע�⣺  B������������к�ᴮ�ڴ�ӡ5s����ʱ����Ϣ��
 *            ��Ҫ����5s�ڷ�����������(ͨA�巢�ʹ��������ַ������ܳ���64�ֽ�)����ʱ����̼�
 *            ����״̬����ʱ��ȴ���ʱ10s���ȴ����չ̼������A��û�з��������ַ������
 *            �������B���flash�û��������Ƿ��п�ִ�еĴ��룬���������ת���ô��봦���У�
 *            �����������µȴ��̼���������(��ӡ����ʱ5s��Ϣ)��
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-18  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824zb_bootloader
 * \copydoc demo_am824zb_bootloader.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_boot.h"
#include "am_uart.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "am_lpc82x_inst_init.h"
#include "am_bootconf_lpc824.h"
#include "am_int.h"
#include <string.h>
#include "am_lpc824_boot_firmware_flash.h"

/* �Ƿ�ͨ��Զ�̽��յ������޸ı��ص�ַ */
#define  CHANGE_MY_ADDR             0

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

/** \brief Ӧ�ù̼����ս���״̬ */
#define APP_RECEIVE_END             4
/** @} */


/** \brief ������ʱʱ�䣨�룩 */
#define BOOT_WAITE_TIME             5

/** \brief ��ʱ����ʱʱ�� */
static volatile uint16_t timer = BOOT_WAITE_TIME;

/** \brief bootloader״̬*/
static volatile uint8_t boot_state = BOOT_WAIT_STATE;

/** \brief һ�볬ʱ��־ */
static volatile uint8_t second_flag   = 0;

/**
 * \brief  ������ʱ�ȴ������ʱ���ص�����
 */
static void __startup_wait_timer_handle(void *p_arg)
{
    timer++;
    if(boot_state == BOOT_WAIT_STATE) {
        second_flag = 1;
    } 
}


static void __delay(void)
{
    volatile uint32_t i = 1000000;
    while(i--){
		}
}
static uint8_t __attribute__((aligned(256))) recv_buf[64] = {0};

/**
 * \brief bootloader demo���
 */
void demo_am824zb_bootloader_entry (void)
{
    am_boot_firmware_verify_info_t firmware_head;
    am_boot_firmware_handle_t      firmware_handle;
	  am_zm516x_cfg_info_t           zm516x_cfg_info;

    am_zm516x_handle_t zm516x_handle = am_zm516x_inst_init();  
  
	/** \brief bootloader������ʱ�����ʱ���ṹ�� */
    am_softimer_t        startup_wait_timer;
	
    int      ret;
	  uint32_t count   = 0; 
		
    /* ��ȡ ZigBee ģ���������Ϣ���������D1�� */
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
		    am_kprintf("zm516x_cfg_info_get fiald\r\n");
		}

	  zm516x_cfg_info.chan         = 20;
    zm516x_cfg_info.serial_rate  = 3; /* ������9600 */
		
		zm516x_cfg_info.dst_addr[0]  = 0x00;
	  zm516x_cfg_info.dst_addr[1]  = 0x00;
		
		zm516x_cfg_info.panid[0]     = 0x10;
		zm516x_cfg_info.panid[1]     = 0x01;
		
	  zm516x_cfg_info.my_addr[0]   = 0x20;
	  zm516x_cfg_info.my_addr[1]   = 0x02;
		
    /* �޸� ZigBee ģ���������Ϣ���������D6�������óɹ��踴λ */
    if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
				am_kprintf("zm516x_cfg_info_set fiald\r\n");
		}
		
    /* ʹ ZigBee ģ�鸴λ���������D9�� */
    am_zm516x_reset(zm516x_handle);
    __delay();
		
		am_uart_ioctl(zm516x_handle->uart_handle->handle, 
		              AM_UART_BAUD_SET, 
		              (void *)9600);
		
    /* bootloader flash��ʼ��  */
    am_boot_flash_handle_t flash_handle = am_lpc824_boot_flash_inst_init();
    /* �̼���ű�׼�ӿڳ�ʼ��  */
    firmware_handle = am_lpc824_boot_firmware_flash(flash_handle);
	
      /* bootloader ��׼�ӿڳ�ʼ��  */
    am_lpc824_std_boot_inst_init(flash_handle);
	
    am_uart_handle_t uart_handle = am_lpc82x_usart0_inst_init();
    am_debug_init(uart_handle, 115200);
		
    /* ������ʱ�ص���ʱ����ʼ��  */
    am_softimer_init(&startup_wait_timer, __startup_wait_timer_handle, &startup_wait_timer);
		
		am_softimer_start(&startup_wait_timer, 1000);
		
		am_kprintf("Device will enter application, if don't input anything after %ds\r\n",timer);
		
		timer = 0;
		/* ��ʱ�ȴ�������û������ݷ������ͽ���bootloader��������ת��Ӧ�ó��� */
		while(boot_state == BOOT_WAIT_STATE) {
			
		    /* �����յ����ݣ����л���Bootloader״̬ */
		    ret = am_zm516x_receive(zm516x_handle, (uint8_t *)&recv_buf, sizeof(recv_buf));
				if (ret > 0) {
					boot_state = BOOT_STARTUP_STATE;
					break;
			  }
			
			  /* ����ʱ�� ������û������� */
				if (timer > BOOT_WAITE_TIME){
					boot_state = APP_STARTUP_STATE;
					break;
				}
			
				/* ÿ���ӡһ�� */
				if(timer < BOOT_WAITE_TIME && second_flag == 1){
			      am_kprintf("Device will enter application, if don't input anything after %ds\r\n", BOOT_WAITE_TIME - timer);	
					  second_flag = 0;
				}
		 }
		
    while(1) {
		    am_kprintf("bootloader : running...\r\n");

		    /* �������̼�����״̬ */
		    if (boot_state == BOOT_STARTUP_STATE) {
			 
			 	    /* ׼���̼���� */
            am_boot_firmware_store_start(firmware_handle, 18 * 1024);
			      am_kprintf("bootloader : firmware transmission is ready\r\n");

			      timer = 0;
				    while(am_zm516x_receive(zm516x_handle, &firmware_head, sizeof(firmware_head)) != 8) {
					      if (timer > 10) {
							      continue;
						    }
				    }
					 
				    timer = 0;
			 
				    while(boot_state == BOOT_STARTUP_STATE) {		
						    ret = am_zm516x_receive(zm516x_handle, recv_buf, sizeof(recv_buf));					  
						    if (ret > 0) {
						        /* �̼����  ��ÿ�δ���ֽ� */ 
							      am_boot_firmware_store_bytes(firmware_handle, recv_buf, sizeof(recv_buf));

							      timer = 0;
							      count += ret;
						    }
								
						    if (timer > 2) {
								    if (count > 0) {
									      boot_state = APP_RECEIVE_END;
								    }							
								    break;
						    }					
				    }
        }
		  
        /* ����̼����ս��� */
			  if (boot_state == APP_RECEIVE_END) {
				    /* �̼���Ž���  */
            am_boot_firmware_store_final(firmware_handle);

			      /* ��ӡ���յ����ݴ�С����ȥ2�ֽڵ�my_addr ����8�ֽ�ͷ*/
            am_kprintf("bootloader : firmware receive successful\r\n");
				
            /* �̼�У��  */
            ret = am_boot_firmware_verify(firmware_handle, &firmware_head);
            if(ret != AM_OK) {
                am_kprintf("bootloader : firmware verify error, bootloader will restart!\r\n");
					      count = 0;
					      boot_state = BOOT_STARTUP_STATE;
                continue;
            }
				    boot_state = APP_STARTUP_STATE;
								
#if CHANGE_MY_ADDR				
				/* ��ȡ ZigBee ģ���������Ϣ���������D1�� */
        am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info);
				
				zm516x_cfg_info.my_addr[0] = recv_buf[1];
				zm516x_cfg_info.my_addr[1] = recv_buf[0];
				
				    /* �޸� ZigBee ģ���������Ϣ���������D6�������óɹ��踴λ */
				if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
					am_kprintf("addr set error!!!\r\n");
				}
	
				/* ʹ ZigBee ģ�鸴λ���������D9�� */
				am_zm516x_reset(zm516x_handle);
				am_mdelay(10);
				
				am_zm516x_send(zm516x_handle, "recvOK", sizeof("recvOK"));
#endif		
        }
		
        if(am_boot_app_is_ready() && boot_state == APP_STARTUP_STATE) {
            //am_kprintf("bootloader : go to application...\r\n");

            __delay();
            am_lpc82x_usart0_inst_deinit(uart_handle);
            /* ��ת��Ӧ�ó���  */
            if(AM_OK != am_boot_go_application()){
					      count = 0;
							  boot_state = BOOT_STARTUP_STATE;
                continue;
            }
        }
	
    }
}

/* end of file */
