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
 * \brief ģ��Ƚ������̣��ж�ģʽ����ͨ�� HW ��ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_1 ����ģ������ 2��
 *   2. PIO0_14 ����ģ������ 3��
 *
 * - ʵ������
 *   1. ������ 2 ������ 3 �ȽϽ�������仯��ʱ��������ʾ�ַ���
 *   2. ���� 2 �������� 3 ʱ�����ڻ�����ȽϽ�� "result: PIO0_1_ACMP_I2 > PIO0_14_ACMP_I3"��
 *   3. ���� 2 С������ 3 ʱ�����ڻ�����ȽϽ�� "result: PIO0_1_ACMP_I2 < PIO0_14_ACMP_I3"��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *S
 * \par Դ����
 * \snippet demo_lpc824_hw_acmp_int.c src_lpc824_hw_acmp_int
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-05  hgo, modified
 * - 1.00 15-07-21  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_acmp_int
 * \copydoc demo_lpc824_hw_acmp_int.c
 */

/** [src_lpc824_hw_acmp_int] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "hw/amhw_lpc82x_acmp.h"


/** \brief ACMP �жϱ�־ */
am_local volatile am_bool_t __g_complete_flag = AM_FALSE;


/**
 * \brief ACMP �жϷ�����,���ȽϽ�������仯ʱ������ж�
 */
am_local void __acmp_irq_handler (void *p_arg)
{
  amhw_lpc82x_acmp_t *p_hw_acmp = (amhw_lpc82x_acmp_t *)p_arg;
    __g_complete_flag = AM_TRUE;
    amhw_lpc82x_acmp_int_clr(p_hw_acmp);
}


void demo_lpc824_hw_acmp_int_entry(amhw_lpc82x_acmp_t *p_hw_acmp, 
                                   uint32_t            flags, 
                                   int                 inum, 
                                   int                 pin)
{
    amhw_lpc82x_acmp_config(p_hw_acmp, flags);

    /* ���� ADC �жϷ���������ʹ���ж� */
    am_int_connect(inum, __acmp_irq_handler, (void *)p_hw_acmp);
    am_int_enable (inum);

    AM_FOREVER {

        while ( AM_FALSE == __g_complete_flag);

        if (am_gpio_get(pin)) {
            AM_DBG_INFO("result: PIO0_1_ACMP_I2 > PIO0_14_ACMP_I3\r\n");
        } else {
            AM_DBG_INFO("result: PIO0_1_ACMP_I2 < PIO0_14_ACMP_I3\r\n");
        }

        __g_complete_flag =  AM_FALSE;
    }
}
/** [src_lpc824_hw_acmp_int] */

/* end of file */

