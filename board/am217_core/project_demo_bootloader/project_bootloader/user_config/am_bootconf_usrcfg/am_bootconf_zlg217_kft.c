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
 * \brief ZLG217 kboot KinetisFlashTool �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */


/**
 * \addtogroup am_if_src_bootconf_zlg217_kft
 * \copydoc am_bootconf_zlg217_kft.c
 * @{
 */

#include "am_arm_boot.h"
#include "am_boot_kft.h"
#include "ametal.h"
#include "am_gpio.h"
#include "am_zlg217.h"
#include "am_zlg217_inst_init.h"
#include "am_boot_serial_uart.h"
#include "am_zlg_boot_flash.h"
#include "am_boot.h"
#include "am_boot_autobaud_soft.h"
#include "am_boot_flash.h"
#include "am_zlg_tim_cap.h"
#include "am_zlg_flash.h"
#include "zlg217_regbase.h"
#include "am_int.h"
#include "am_zlg217_clk.h"
#include "am_arm_nvic.h"

/**
 * \name �Զ������ʼ��궨��
 * @{
 */

/** \brief ��Ҫ�õ��Ķ�ʱ��λ�� */
#define     TIMER_WIDTH           16
static am_cap_handle_t   cap_handle;
/** @} */

/*******************************************************************************
 * �Զ������ʼ������
 ******************************************************************************/

/** \brief �Զ������ʵ�ƽ̨��ʼ�� */
void __zlg217_plfm_autobaud_init (void)
{
    amhw_zlg_tim_prescale_set((amhw_zlg_tim_t *)ZLG217_TIM2_BASE, (uint16_t)8);
}

/** \brief �Զ������ʵ�ƽ̨���ʼ��  */
void __zlg217_plfm_autobaud_deinit (void)
{
    am_zlg217_tim1_cap_inst_deinit (cap_handle);
}

/** \brief �Զ������ʵ��豸��Ϣʵ�� */
static am_boot_autobaud_soft_devinfo_t __g_zlg217_boot_autobaud_devinfo = {

    2,                            /**< \brief CAP����ͨ���� */
    TIMER_WIDTH,                  /**< \brief TIMER��ʱ��λ�� */
    10,                           /**< \brief ����һ�����ݵĳ�ʱʱ��(ms)*/
    AM_CAP_TRIGGER_FALL,          /**< \brief CAP���񴥷���ʽ */
    __zlg217_plfm_autobaud_init,  /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_autobaud_deinit,/**< \brief ƽ̨���ʼ������ */
};

/** \brief �Զ������ʹ��ܵ��豸ʵ�� */
am_boot_autobaud_soft_dev_t  __g_zlg217_boot_autobaud_dev;

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_boot_autobaud_handle_t am_zlg217_boot_autobaud_inst_init (void)
{
    cap_handle = am_zlg217_tim1_cap_inst_init();

    am_zlg_tim_cap_dev_t *p_cap_dev = (am_zlg_tim_cap_dev_t *)cap_handle;
    int cap_pin =
        p_cap_dev->p_devinfo->p_ioinfo[__g_zlg217_boot_autobaud_devinfo.cap_chanel].gpio;

    return am_boot_autobaud_soft_init(&__g_zlg217_boot_autobaud_dev,
                                      &__g_zlg217_boot_autobaud_devinfo,
                                       cap_handle,
                                       cap_pin);
}

/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_zlg_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x08000000,
        /** \brief flash���ܵĴ�С */
        128 * 1024,
        /** \brief flash������С */
        1024,
        /** \brief flashҳ��С */
        4,
    },
    /** \brief flash�Ĵ����Ļ���ַ */
    ZLG217_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_zlg_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_zlg217_boot_kft_flash_inst_init(void)
{
    return am_zlg_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * ��׼bootloader�ӿ�����
 ******************************************************************************/

static void __zlg217_boot_kft_plfm_deinit()
{
    volatile uint32_t i = 1000000;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){

    }
    am_clk_disable(CLK_UART1);
    am_gpio_pin_cfg(PIOA_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIOA_10,AM_GPIO_INPUT);

    amhw_zlg_uart_disable((amhw_zlg_uart_t *)ZLG217_UART1_BASE);
    am_int_disable(INUM_UART1);

    /* ��ʱ�����ʼ��  */
    amhw_zlg_tim_int_disable(ZLG217_TIM4, AMHW_ZLG_TIM_UIE);
    amhw_zlg_tim_disable(ZLG217_TIM4);
    am_int_disable(INUM_TIM4);
    am_zlg217_clk_reset(CLK_TIM4);
    am_clk_disable(CLK_TIM4);

    am_arm_nvic_deinit();
    __disable_irq();
}

/**
 *  \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_zlg217_boot_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x08007000,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram������ַ */
    20 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __zlg217_boot_kft_plfm_deinit,
};

/**
 *  \brief bootloader��׼�豸ʵ��
 */
int am_zlg217_boot_kft_inst_init()
{
    return am_arm_boot_init(&__g_zlg217_boot_devinfo);
}

/** @} */

/* end of file */
