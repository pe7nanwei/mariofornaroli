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
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_int.h"
#include "hw/amhw_lpc84x_clk.h"
#include "hw/amhw_lpc84x_syscon.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"
#include "am_lpc84x_boot_flash.h"
#include "am_arm_boot.h"
#include "am_boot_flash.h"
#include "am_boot_mem_flash.h"
#include "lpc84x_regbase.h"
#include "am_boot_firmware_flash.h"
#include "am_lpc84x_clk.h"
#include "am_arm_nvic.h"
#include "am_boot_msg_flag.h"

static am_boot_flash_handle_t flash_handle;
/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_lpc84x_boot_flash_devinfo_t __g_flash_devinfo = {

    {
        /** \brief flash����ʼ��ַ */
        0x0,
        /** \brief flash���ܵĴ�С */
        64 * 1024,
        /** \brief flash������С */
        1024,
        /** \brief flashҳ��С */
        64,
    },

    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_lpc84x_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_lpc84x_boot_flash_inst_init(void)
{
    return am_lpc84x_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}

/*******************************************************************************
 * ��flag��ʽ����Ϣ����
 ******************************************************************************/

static am_boot_msg_flag_devinfo_t __g_boot_msg_flag_info = {
    /** \brief ��������ʼ��ַ */
    0x9C00,
    /** \brief Ӧ������С */
    25 * 1024,
    /** \brief ��־��ŵ�ַ */
    0x3800 - 64,
    /** \brief ��־ռ�õ�ʵ�ʴ�С��һ��Ϊ�ڴ���С��д�뵥Ԫ�����ʹ��flash�ڴ棬��Ϊ��С�Ĳ�����Ԫ*/
    64,

    NULL,
};

am_boot_msg_handle_t am_lpc84x_boot_msg_flag_inst_init()
{
    am_boot_mem_handle_t mem_handle = am_boot_mem_flash_init(flash_handle);
    return am_boot_msg_flag_init(&__g_boot_msg_flag_info,
                                  mem_handle);
}

/*******************************************************************************
 * �̼���flash�ķ�ʽ�洢����
 ******************************************************************************/
static am_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief �̼����ڴ��д�ŵ���ʼ��ַ */
    0x9C00,
    /**< \brief �̼���������ܴ�С */
    25 * 1024,
    /** \brief ������Ź̼���������С , ֵΪ�ڴ�д����С��С�������� */
    64,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

static am_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_lpc84x_boot_firmware_flash_inst_init()
{
    flash_handle = am_lpc84x_boot_flash_inst_init();
    return am_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                        &__g_firmware_flash_devinfo,
                                         flash_handle);
}


/*******************************************************************************
 * ��׼bootloader�û�����
 ******************************************************************************/

/* ������bootloader���õ�����Դ��Ҫ�ӳ�ʼ�����ͷţ��������綨ʱ�������ڵ� */
void __lpc84x_boot_plfm_deinit()
{
    volatile uint32_t i = 1000000;

    uint8_t  channel_nums = 4;
    /* ���ڽ��ʼ�� �����ʼ��ǰ��ҪС�ε���ʱ����֤�Ĵ��������Ѿ����*/
    while(i--){

    }
    /* ���ڽ��ʼ�� */
    amhw_lpc_usart_disable((amhw_lpc_usart_t *)LPC84X_USART0_BASE);
    am_int_disable(INUM_USART0);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_UART0);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_UART0);

    am_gpio_pin_cfg(PIO0_28, PIO0_28_GPIO);
    am_gpio_pin_cfg(PIO1_20, PIO1_20_GPIO);

    /* �����ʱ�����ʼ��*/
    for (i = 0; i < channel_nums; i++) {
        amhw_lpc_mrt_intval_set((amhw_lpc_mrt_t *)LPC84X_MRT_BASE, i, 0, AM_TRUE);

        amhw_lpc_mrt_int_flag_clr((amhw_lpc_mrt_t *)LPC84X_MRT_BASE, i);
        amhw_lpc_mrt_int_pending_clr((amhw_lpc_mrt_t *)LPC84X_MRT_BASE, i);

        amhw_lpc_mrt_int_disable((amhw_lpc_mrt_t *)LPC84X_MRT_BASE, i);
    }

    am_int_disable(INUM_MRT);
    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_MRT);
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_MRT);

    /* ʱ�ӽ��ʼ�� */
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_SWM);
    amhw_lpc84x_swm_fixed_func_disable(LPC84X_SWM,
                                      AMHW_LPC84X_SWM_PIO0_8_XTALIN);
    amhw_lpc84x_swm_fixed_func_disable(LPC84X_SWM,
                                      AMHW_LPC84X_SWM_PIO0_9_XTALOUT);
    /* �л���ʱ��Դ */
    amhw_lpc84x_clk_mainclk_set( AMHW_LPC84X_MAIN_CLK_PLLIN_SRC_MAIN_CLK_PRE_PLL);

    am_arm_nvic_deinit();
    __disable_irq();
}

/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_arm_boot_devinfo_t __g_lpc84x_boot_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x3800,
    /** \brief ram��ʼ��ַ */
    0x10000000,
    /** \brief ram��С */
    16 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    __lpc84x_boot_plfm_deinit,
};

int am_lpc84x_boot_inst_init()
{
    return am_arm_boot_init(&__g_lpc84x_boot_devinfo);
}

/** @} */

/* end of file */
