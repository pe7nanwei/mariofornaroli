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
 * \brief ZMF159 GPIO �û������ļ���
 * \sa am_hwconf_zmf159_gpio.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-12  zcb, first implementation
 * \endinternal
 */

#include "am_zmf159.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zmf159_clk.h"
#include "am_zmf159_gpio.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_gpio
 * \copydoc am_hwconf_zmf159_gpio.c
 * @{
 */

/** \brief GPIOƽ̨��ʼ�� */
void __zmf159_plfm_gpio_init (void)
{
    am_clk_enable(CLK_IOPA);
    am_clk_enable(CLK_IOPB);
    am_clk_enable(CLK_IOPC);
    am_clk_enable(CLK_IOPD);
    am_clk_enable(CLK_IOPE);

    /* ϵͳ����ʱ��ʹ��(�ȼ���AFIOʱ��) */
    am_clk_enable(CLK_SYSCFG);

    am_zmf159_clk_reset(CLK_IOPA);
    am_zmf159_clk_reset(CLK_IOPB);
    am_zmf159_clk_reset(CLK_IOPC);
    am_zmf159_clk_reset(CLK_IOPD);
    am_zmf159_clk_reset(CLK_IOPE);

    am_zmf159_clk_reset(CLK_SYSCFG);
}

/** \brief GPIOƽ̨���ʼ�� */
void __zmf159_plfm_gpio_deinit (void)
{
    am_zmf159_clk_reset(CLK_IOPA);
    am_zmf159_clk_reset(CLK_IOPB);
    am_zmf159_clk_reset(CLK_IOPC);
    am_zmf159_clk_reset(CLK_IOPD);
    am_zmf159_clk_reset(CLK_IOPE);

    am_zmf159_clk_reset(CLK_SYSCFG);

    am_clk_disable(CLK_IOPA);
    am_clk_disable(CLK_IOPB);
    am_clk_disable(CLK_IOPC);
    am_clk_disable(CLK_IOPD);
    am_clk_disable(CLK_IOPE);

    /* ϵͳ����ʱ�ӽ���(�ȼ���AFIOʱ��) */
    am_clk_disable(CLK_SYSCFG);
}

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct am_zmf159_gpio_trigger_info __g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t __g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const am_zmf159_gpio_devinfo_t __g_gpio_devinfo = {
    ZMF159_GPIO_BASE,            /**< \brief GPIO�������Ĵ������ַ */
    ZMF159_EXTI_BASE,            /**< \brief EXTI�������Ĵ������ַ */
    ZMF159_SYSCFG_BASE,          /**< \brief AFIO�������Ĵ������ַ */

    {
        INUM_EXTI0,
        INUM_EXTI1,
        INUM_EXTI2,
        INUM_EXTI3,
        INUM_EXTI4,
        INUM_EXTI9_5,
        INUM_EXTI15_10,
    },

    PIN_NUM,                       /**< \brief GPIO PIN���� */
    PIN_INT_MAX,                   /**< \brief GPIOʹ�õ�����ⲿ�ж��߱��+1 */

    &__g_gpio_infomap[0],          /**< \brief GPIO �����ⲿ�¼���Ϣ */
    &__g_gpio_triginfos[0],        /**< \brief GPIO PIN������Ϣ */

    __zmf159_plfm_gpio_init,       /**< \brief GPIO ƽ̨��ʼ�� */
    __zmf159_plfm_gpio_deinit      /**< \brief GPIO ƽ̨ȥ��ʼ�� */
};

/** \brief GPIO�豸ʵ�� */
am_zmf159_gpio_dev_t __g_gpio_dev;

/** \brief GPIO ʵ����ʼ�� */
int am_zmf159_gpio_inst_init (void)
{
    return am_zmf159_gpio_init(&__g_gpio_dev, &__g_gpio_devinfo);
}

/** \brief GPIO ʵ�����ʼ�� */
void am_zmf159_gpio_inst_deinit (void)
{
    am_zmf159_gpio_deinit();
}

/**
 * @}
 */

/* end of file */
