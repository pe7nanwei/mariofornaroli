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
 * \brief adc24 �û������ļ�
 * \sa am_hwconf_adc24.c
 *
 * \internal
 * \par Modification history
 * - 1.01 18-09-07  cml, correction frequency of communication with adc24
 * - 1.00 18-06-11  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_gpio.h"
#include "am_adc24.h"
#include "am_zlg116.h"

/**
 * \addtogroup am_if_src_hwconf_adc24
 * \copydoc am_hwconf_adc24.c
 * @{
 */

/** \brief adc24 �豸��Ϣ */
am_local am_const am_adc24_devinfo_t __g_adc24_devinfo = {
    2500,                           /* ADC �ο���ѹ����λ��mV����2.5V���� 5V */
    5000,                           /* ��ʱʱ�䣬��λΪ���� */
};

/** \brief adc24 �豸ʵ�� */
am_local am_adc24_dev_t __g_adc24_dev;
/**
 * \brief adc24 ʵ����ʼ��
 */
am_adc24_handle_t am_aml166_adc24_inst_init (void)
{
    return am_adc24_init(&__g_adc24_dev, &__g_adc24_devinfo);;
}

/**
 * \brief adc24 ʵ�����ʼ��
 */
void am_aml166_adc24_inst_deinit (am_adc24_handle_t handle)
{
    am_adc24_deinit(handle);
}

/**
 * @}
 */

/* end of file */
