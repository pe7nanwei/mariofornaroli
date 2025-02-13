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
 * \brief �����嵥5.70 
 *
 * \note ��������Ҫ�õ�miniport��չ��,������LED��Ч��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_spi.h"
#include "am_lpc82x_inst_init.h"
#include "am_lpc82x.h" 
int am_main(void)
{
    am_spi_handle_t  spi1_handle  = am_lpc82x_spi1_dma_inst_init(); 
    am_spi_device_t  hc595_dev;                // ������HC595�����Ĵӻ��豸
    uint8_t          tx_buf[1] = {0x55};       // �ٶ�����һ��8λ����0x55

    // ��ʼ��һ����74HC595��Ӧ��SPI�ӻ�ʵ��
    am_spi_mkdev(
        &hc595_dev,                    // ���ݴӻ��豸��ַ
        spi1_handle,                // SPI0�������
        8,                             // ���ݿ��Ϊ8-bit
        AM_SPI_MODE_3,                 // ѡ��ģʽ3
        3000000,                       // ���Ƶ��3MHz
        PIO0_14,                       // Ƭѡ����PIO0_1 4
        NULL);                         // ���Զ���Ƭѡ���ƺ���NULL
        am_spi_setup(&hc595_dev);      // ����SPI���豸
        am_spi_write_then_write(&hc595_dev,    // ���ݴӻ��豸
        tx_buf,                        // �������ݻ�����0������
        1,                             // ����1������
        NULL,                          // �������ݻ�����1������
        0);                            // �����ݣ��򳤶�Ϊ0
    while(1) {
    }
}


/* end of file */

