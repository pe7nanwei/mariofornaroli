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
 * \brief �����嵥5.25
 *
 * \note ��������Ҫ�õ�miniport��չ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_gpio.h"
#include "digitron0.h"
#include "am_lpc82x.h"

static const int g_digitron_com[2] = {PIO0_17,PIO0_23};

static const uint8_t g_segcode_list[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

static const int g_digitron_seg[8]={
    PIO0_8, PIO0_9, PIO0_10, PIO0_11, PIO0_12, PIO0_13, PIO0_14, PIO0_15};

int am_main (void)
{
    int i;

    for (i = 0; i < 2; i++) {
        // ��com�˶�Ӧ��������Ϊ���������ʼ��Ϊ�ߵ�ƽ
        am_gpio_pin_cfg(g_digitron_com[i], AM_GPIO_OUTPUT_INIT_HIGH);
    }
    for (i = 0; i < 8; i++) {
        // ����ѡ�˶�Ӧ��������Ϊ���������ʼ��Ϊ�ߵ�ƽ
        am_gpio_pin_cfg(g_digitron_seg[i], AM_GPIO_OUTPUT_INIT_HIGH);
    }
    digitron_com_sel(0);                         // ѡ��com0�����
    digitron_segcode_set(g_segcode_list[1]);     // ��������1�Ķ���
    while (1) {
    }
}



/* end of file */

