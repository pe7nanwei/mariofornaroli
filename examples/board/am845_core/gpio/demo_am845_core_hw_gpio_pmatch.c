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
 * \brief GPIO ģʽƥ��������ʾ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. �߼����ʽΪ:(/IN0) * IN1 + (/IN3) + (/IN4��*(/IN5)
 *      ���������κ�һ�����㴥���жϣ�
 *          - IN0 Ϊ�͵�ƽ�� IN1 ��Ϊ�ߵ�ƽ��
 *          - IN3 Ϊ�͵�ƽ
 *          - IN4 Ϊ�͵�ƽ�� IN5 �������½����¼�
 *   2. �ж�ͨ�������Ŷ�Ӧ��ϵ��
 *          - IN0 - PIO0_14
 *          - IN1 - PIO0_15
 *          - IN3 - PIO0_16
 *          - IN4 - PIO0_17
 *          - IN5 - PIO0_18
 *
 * - ʵ������
 *   1. �жϱ�����ʱ��LED0 ״̬��ת�����ڴ�ӡ "gpio pmatch count %d\r\n"��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO1_8 ���ƣ�
 *    2. ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO1_2 �������� PC ���ڵ� TXD��
 *       PIO1_0 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_am845_hw_gpio_pmatch.c src_am845_hw_gpio_pmatch
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-24  mem, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_hw_gpio_pmatch
 * \copydoc demo_am845_hw_gpio_pmatch.c
 */

/** [src_am845_hw_gpio_pmatch] */
#include "ametal.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_gpio.h"
#include "lpc84x_periph_map.h"
#include "demo_nxp_entries.h"
#include "lpc84x_pin.h"

/** \brief LED0 ���� */
#define __LED0_PIN  PIO1_8

/**
 * \brief �������
 */
void demo_am845_core_hw_gpio_pmatch_entry (void)
{
    am_kprintf("demo am845 hw gpio pmatch!\r\n");

    /* ���� LED0 ���ŷ���Ϊ��� */
    amhw_lpc84x_gpio_pin_dir_output(LPC84X_GPIO, __LED0_PIN);

    demo_lpc845_hw_gpio_pmatch_entry(__LED0_PIN);

}
/** [src_am845_hw_gpio_pmatch] */

/* end of file */
