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
 * \brief HC32 RTC �û������ļ�
 * \sa am_hwconf_hc32_rtc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-10-17  zp, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_hc32.h"
#include "am_clk.h"
#include "am_hc32_rtc.h"
#include "hw/amhw_hc32_rcc.h"
#include "am_hc32l13x_inst_init.h"
#include "hc32_periph_map.h"
#include "hc32_clk.h"

/**
 * \addtogroup am_if_src_hwconf_hc32_rtc
 * \copydoc am_hwconf_hc32_rtc.c
 * @{
 */

/** \brief RTC ƽ̨��ʼ�� */
void __hc32_plfm_rtc_init()
{
    am_clk_enable(CLK_RTC);

    am_gpio_pin_cfg(PIOB_14, PIOB_14_RTC_1HZ | PIOB_14_OUT_PP);
}

/** ��� RTC ƽ̨��ʼ�� */
void __hc32_plfm_rtc_deinit(void)
{
    am_clk_disable(CLK_RTC);

    am_gpio_pin_cfg(PIOB_14, PIOB_14_GPIO | PIOB_14_INPUT_PU);
}

/** \brief RTC�豸��Ϣ */
const struct am_hc32_rtc_devinfo __g_rtc_devinfo = {

    /** \brief RTC�豸����ַ */
    HC32_RTC_BASE,

    /** \brief RTC�豸ʱ��Դ */
    AMHW_HC32_RTC_CLK_SRC_XTL_32768Hz,

    /**< \brief RTC �жϺ� */
    INUM_RTC,

    {
        AM_TRUE,                      /* �Ƿ�ʹ��1Hz�������
                                       * AM_TRUE �� ʹ�� �����Ķ������������õ�ע�ͣ�
                                       * AM_FALSE�� ���ܣ���������������Ч��
                                       */
        -92.554,                      /* ����ֵ��-274.6 ~ 212.6��ppm����Χ�����ر�*/
        AM_TRUE,                      /* ��ppm���ڷ�Χ��ʱ������������������£���
                                       * ѡ���Ƿ�������ʱ����Ϊ����ʱ��
                                       *
                                       * AM_TRUE �� ��������ʱ����Ϊ����ʱ��
                                       * AM_FALSE�� �رո���ʱ����Ϊ����ʱ��
                                       */
        AMHW_HC32_RTCCLK_ADJUST_24M,/* ����ʱ�Ӳ���ʱ��ѡ�� ����PCLKƵ�ʱ���һ����ͬ  */
    },

    /** \brief ƽ̨��ʼ������ */
    __hc32_plfm_rtc_init,

    /** \brief ƽ̨ȥ��ʼ������ */
    __hc32_plfm_rtc_deinit
};

/** \brief RTC�豸 */
am_hc32_rtc_dev_t __g_rtc_dev;

/** \brief rtc ʵ����ʼ�������rtc��׼������ */
am_rtc_handle_t am_hc32_rtc_inst_init (void)
{
    return am_hc32_rtc_init(&__g_rtc_dev, &__g_rtc_devinfo);
}

/**
 * \brief rtc ʵ�����ʼ��
 * \param[in] handle : rtc���ֵ
 */
void am_hc32_rtc_inst_deinit (am_rtc_handle_t handle)
{
    am_hc32_rtc_deinit(handle);
}

/**
 * @}
 */

/** end of file */
