/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ʱ��ѡ��Ϳ��ƽӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-01-01  bzq, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC84X_CLK_H
#define __AMHW_LPC84X_CLK_H

#include "ametal.h"
#include "lpc84x_periph_map.h"
#include "hw/amhw_lpc84x_syscon.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc84x_if_clk
 * \copydoc amhw_lpc84x_clk.h
 * @{
 */

/**
 * \name Ƶ��ֵ����
 *
 * ���ʹ�����ⲿ�ܽţ�PIO0_22����Ϊʱ������ܽţ�����Ҫ��
 * AMHW_LPC84X_CLK_FREQ_CLKIN ����Ϊ��ȷ��Ƶ��ֵ.
 *
 * @{
 */

/** \brief �ڲ�FROƵ��         */
#define AMHW_LPC84X_CLK_FREQ_IRC      24000000UL
/** \brief �ⲿ�ܽŵ�����Ƶ��  */
#define AMHW_LPC84X_CLK_FREQ_CLKIN    12000000UL
/** \brief ���Ź���Ϊʱ��Դ������Ƶ��  */
#define AMHW_LPC84X_WDT_FREQ_CLKIN    12000000UL
/** \brief �ⲿ����Ƶ��        */
#define AMHW_LPC84X_CLK_FREQ_XTAL     12000000UL

/** @} */

/** \brief Integer divide API routines */
typedef struct {
  int quot;      /** \brief  Quotient */
  int rem;       /** \brief  Remainder */
} IDIV_RETURN_T;

typedef struct {
  unsigned quot; /** \brief Quotient */
  unsigned rem;  /** \brief  Reminder */
} UIDIV_RETURN_T;

typedef struct {
    /** \brief  Signed integer division */
    int (*sidiv)(int numerator, int denominator);

    /** \brief  Unsigned integer division */
    unsigned (*uidiv)(unsigned numerator, unsigned denominator);

    /** \brief  Signed integer division with remainder */
    IDIV_RETURN_T (*sidivmod)(int numerator, int denominator);

    /** \brief  Unsigned integer division with remainder */
    UIDIV_RETURN_T (*uidivmod)(unsigned numerator, unsigned denominator);
} ROM_DIV_API_T;


#define ROM_DRIVER_BASE (0x0F001FF8UL)

#define LPC_PWRD_API    ((PWRD_API_T *   ) ((*(LPC_ROM_API_T * *) (ROM_DRIVER_BASE))->pPWRD))

/** \brief  Power APIs */
typedef struct _PWRD {
    void (*set_pll)(unsigned int cmd[], unsigned int resp[]);
    void (*set_power)(unsigned int cmd[], unsigned int resp[]);
    void (*set_fro_frequency)(unsigned frequency);
    void (*power_mode_configure)(unsigned int power_mode, unsigned int peripheral_ctrl);
    void (*set_aclkgate)(unsigned aclkgate);
    unsigned (*get_aclkgate)(void);
} PWRD_API_T;

/** \brief
 *   The master structure that defines the table of
 *   all ROM APIs on the device (a.k.a ROM Driver table)
 */
typedef struct _ROM_API {
	/** \brief  Offsets 0, 4, 8 */
    const unsigned int  reserved3[3];

    /** \brief  Offset 0xC. Power APIs function table base address */
    const PWRD_API_T    *pPWRD;

    /** \brief  Offset 0x10. Integer division routines function table base address */
    const ROM_DIV_API_T *divApiBase;

     /** \brief  Offsets 0x14 - 0x2C */
    const unsigned int  reserved7[7];
} LPC_ROM_API_T;

/**
 * \brief ϵͳ������ʱ�ӱ��
 */
typedef enum amhw_lpc84x_clk_periph {
    AMHW_LPC84X_CLK_SYS = 0,           /**< \brief System ʱ��         */
    AMHW_LPC84X_CLK_ROM,               /**< \brief ROM ʱ��            */
    AMHW_LPC84X_CLK_SRAM0_1,           /**< \brief SRAM0 SRAM1 ʱ��    */
    AMHW_LPC84X_CLK_FLASH = 4,         /**< \brief FLASH ʱ��          */
    AMHW_LPC84X_CLK_I2C0,              /**< \brief I2C0ʱ��            */
    AMHW_LPC84X_CLK_GPIO0,              /**< \brief GPIO0 ʱ��           */
    AMHW_LPC84X_CLK_SWM,               /**< \brief SWM ʱ��            */
    AMHW_LPC84X_CLK_SCT,               /**< \brief SCT ʱ��            */
    AMHW_LPC84X_CLK_WKT,               /**< \brief WKT ʱ��            */
    AMHW_LPC84X_CLK_MRT,               /**< \brief MRTʱ��             */
    AMHW_LPC84X_CLK_SPI0,              /**< \brief SPI0 ʱ��           */
    AMHW_LPC84X_CLK_SPI1,              /**< \brief SPI1 ʱ��           */
    AMHW_LPC84X_CLK_CRC,               /**< \brief CRC ʱ��            */
    AMHW_LPC84X_CLK_UART0,             /**< \brief UART0 ʱ��          */
    AMHW_LPC84X_CLK_UART1,             /**< \brief UART1 ʱ��          */
    AMHW_LPC84X_CLK_UART2,             /**< \brief UART2 ʱ��          */
    AMHW_LPC84X_CLK_WWDT,              /**< \brief WWDT ʱ��           */
    AMHW_LPC84X_CLK_IOCON,             /**< \brief IOCON ʱ��          */
    AMHW_LPC84X_CLK_ACMP,              /**< \brief ACMP ʱ��           */
	AMHW_LPC84X_CLK_GPIO1,             /**< \brief GPIO1 ʱ��           */
    AMHW_LPC84X_CLK_I2C1,              /**< \brief I2C1 ʱ��           */
    AMHW_LPC84X_CLK_I2C2,              /**< \brief I2C2 ʱ��           */
    AMHW_LPC84X_CLK_I2C3,              /**< \brief I2C3 ʱ��           */
    AMHW_LPC84X_CLK_ADC,               /**< \brief ADC ʱ��            */
	AMHW_LPC84X_CLK_CTIMER0,           /**< \brief CTIMER0 ʱ��   */
    AMHW_LPC84X_CLK_MTB ,              /**< \brief MTB ʱ��            */
	AMHW_LPC84X_CLK_DAC0,              /**< \brief ADC0 ʱ��            */
	AMHW_LPC84X_CLK_GPIO_INT,          /**< \brief GPIO_INT ʱ��            */
    AMHW_LPC84X_CLK_DMA,               /**< \brief DMA ʱ��            */
	AMHW_LPC84X_CLK_UART3,             /**< \brief UART3 ʱ��          */
	AMHW_LPC84X_CLK_UART4,             /**< \brief UART4 ʱ��          */
	AMHW_LPC84X_CLK_CAPT,              /**< \brief CAPT ʱ��          */
	AMHW_LPC84X_CLK_DAC1,              /**< \brief DAC1 ʱ��          */
} amhw_lpc84x_clk_periph_t;

/**
 * \brief PLL ����ʱ��Դ
 */
typedef enum amhw_lpc84x_pllinclk_src {
    AMHW_LPC84X_CLK_PLLIN_SRC_FRO = 0,      /**< \brief �ڲ�FRO   */
    AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_CLK, /**< \brief �ⲿʱ��        */
	AMHW_LPC84X_CLK_PLLIN_SRC_WTD_CLK,      /**< \brief ���Ź�ʱ��        */
    AMHW_LPC84X_CLK_PLLIN_SRC_FRO_DIV       /**< \brief �ڲ�FRO��Ƶʱ��  */
} amhw_lpc84x_pllinclk_src_t;

/**
 * \brief FRO ����ʱ��Դ
 */
typedef enum amhw_lpc84x_fro_src {
    AMHW_LPC84X_CLK_FRO_18000000 = 0,      /**< \brief �ڲ�FRO 1800000HZ   */
	AMHW_LPC84X_CLK_FRO_30000000,          /**< \brief �ڲ�FRO 3000000HZ        */
	AMHW_LPC84X_CLK_FRO_24000000,          /**< \brief �ڲ�FRO 2400000HZ         */
} amhw_lpc84x_fro_src_t;


/**                                                                    
 * \brief �ⲿʱ��Դ
 */                                                                    
typedef enum amhw_lpc84x_clk_exeternal_src {
    AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_SYS_OSC_CLK = 0, /**< \brief �ⲿ������ΪPLLʱ��   */
    AMHW_LPC84X_EXTERNAL_CLK_PLLIN_SRC_CLK_IN,          /**< \brief ����������Ϊʱ��       */
} amhw_lpc84x_clk_exeternal_src_t;

/**
 * \brief ��ʱ��Դ
 */
typedef enum amhw_lpc84x_clk_main_src {
    AMHW_LPC84X_MAIN_CLK_PLLIN_SRC_MAIN_CLK_PRE_PLL = 0, /**< \brief ����PLLʱ��    */
    AMHW_LPC84X_CLK_PLLIN_SRC_EXTERNAL_SYS_PLL,          /**< \brief PLL���ʱ��       */
} amhw_lpc84x_clk_main_src_t;


/**                                                                    
 * \brief CLKOUT ���ŵ�ʱ��Դ                                          
 */                                                                    
typedef enum amhw_lpc84x_clk_clkout_src {
    AMHW_LPC84X_CLK_CLKOUT_SRC_IRC = 0,  /**< \brief �ڲ�IRC    */
    AMHW_LPC84X_CLK_CLKOUT_SRC_SYSOSC,   /**< \brief ϵͳ����      */
    AMHW_LPC84X_CLK_CLKOUT_SRC_WDTOSC,   /**< \brief ���Ź�����   */
    AMHW_LPC84X_CLK_CLKOUT_SRC_MAINCLK   /**< \brief ��ʱ��              */
} amhw_lpc84x_clk_clkout_src_t;

/**
 * \brief IOCON ʱ�ӷ�Ƶѡ��
 */ 
typedef enum amhw_lpc84x_clk_iocon_div_t {
    AMHW_LPC84X_CLK_IOCON_CLKDIV0 = 0,   /**< \brief IOCON ʱ�ӷ�Ƶ��0 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV1,       /**< \brief IOCON ʱ�ӷ�Ƶ��1 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV2,       /**< \brief IOCON ʱ�ӷ�Ƶ��2 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV3,       /**< \brief IOCON ʱ�ӷ�Ƶ��3 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV4,       /**< \brief IOCON ʱ�ӷ�Ƶ��4 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV5,       /**< \brief IOCON ʱ�ӷ�Ƶ��5 */
    AMHW_LPC84X_CLK_IOCON_CLKDIV6,       /**< \brief IOCON ʱ�ӷ�Ƶ��6 */
} amhw_lpc84x_clk_iocon_div_t;

/**
 * \brief ADC ʱ��Դѡ��
 */
typedef enum amhw_lpc84x_adc_src {
    AMHW_LPC84X_CLK_ADC_FRO = 0,          /**< \brief �ڲ�FRO   */
	AMHW_LPC84X_CLK_ADC_SYS_PLL0_CLK,     /**< \brief PLLʱ��        */
} amhw_lpc84x_adc_src_t;

/**
 * \brief UART SPI I2C ʱ��Դѡ��
 */
typedef enum amhw_lpc84x_dev_src {
    AMHW_LPC84X_CLK_DEVICE_FRO = 0,      /**< \brief �ڲ�FRO   */
    AMHW_LPC84X_CLK_DEVICE_MAIN_CLK,     /**< \brief ��ʱ��        */
	AMHW_LPC84X_CLK_DEVICE_FRG0CLK,      /**< \brief FRG0ʱ��        */
    AMHW_LPC84X_CLK_DEVICE_FRG1CLK,      /**< \brief FRG1ʱ��  */
	AMHW_LPC84X_CLK_DEVICE_FRO_DIV,      /**< \brief �ڲ�FRO��Ƶʱ��  */
} amhw_lpc84x_dev_src_t;

/**
 * \brief frg ʱ��Դѡ��
 */
typedef enum amhw_lpc84x_frg_src {
    AMHW_LPC84X_CLK_FRG_FRO = 0,      /**< \brief �ڲ�FRO   */
    AMHW_LPC84X_CLK_FRG_MAIN_CLK,     /**< \brief �ⲿʱ��        */
	AMHW_LPC84X_CLK_FRG_SYS_PLL0_CLK, /**< \brief PLLʱ��        */
} amhw_lpc84x_frg_src_t;

/**
 * \brief sct ʱ��Դѡ��
 */
typedef enum amhw_lpc84x_sct_src {
    AMHW_LPC84X_CLK_SCT_FRO = 0,      /**< \brief �ڲ�FRO   */
    AMHW_LPC84X_CLK_SCT_MAIN_CLK,     /**< \brief ��ʱ��        */
	AMHW_LPC84X_CLK_SCT_SYS_PLL0_CLK, /**< \brief PLLʱ��       */
} amhw_lpc84x_sct_src_t;

/**
 * \brief CLKOUT ���ŵ�ʱ��Դ
 */
typedef enum amhw_lpc84x_outclk_src {
    AMHW_LPC84X_CLKOUT_SRC_FRO = 0,        /**< \brief �ڲ�FRO   */
    AMHW_LPC84X_CLKOUT_SRC_MAIN,           /**< \brief ��ʱ��        */
    AMHW_LPC84X_CLKOUT_SRC_SYS_LPP0_CLK,   /**< \brief PLLʱ��       */
    AMHW_LPC84X_CLKOUT_SRC_FRO_DIV,        /**< \brief �ڲ�FRO��Ƶʱ��   */
	AMHW_LPC84X_CLKOUT_SRC_FRO_WDT_OSC_CLK,/**< \brief ���Ź�ʱ��   */
} amhw_lpc84x_outclk_src_t;



/**
 * \brief �õ��ڲ�FROʱ��Ƶ��
 *
 * \return �ڲ�ʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc84x_clk_fro_rate_get (void)
{
    return AMHW_LPC84X_CLK_FREQ_IRC;
}

/**
 * \brief �õ��ⲿXTALʱ��Ƶ��
 *
 * \return �ⲿXTALʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc84x_clk_xtal_rate_get (void)
{
    return AMHW_LPC84X_CLK_FREQ_XTAL;
}

/**
 * \brief �õ��ⲿ�ܽ�����ʱ��Ƶ��
 *
 * \return �ⲿ�ܽ�����ʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_lpc84x_clk_clkin_rate_get (void)
{
    return AMHW_LPC84X_CLK_FREQ_CLKIN;
}


/**
 * \brief �õ�WDT������ʱ��Ƶ��
 *
 * \return  WDT������ʱ��Ƶ�ʣ���λ��Hz��
 *
 * \note ���Ƶ�ʾ���������40%�����
 */
uint32_t amhw_lpc84x_clk_wdt_rate_get (void);

/**
 * \brief PLL ���ƼĴ�������
 *
 * \param[in] msel : ������Ƶ����ֵ
 * \param[in] psel : �󱳷�Ƶ����ֵ
 *
 * \return ��
 * \note  M = msel + 1
 *        P = 2^(psel)
 *        PLLOUT = M * PLLIN;
 *        FCCO = 2 * P * PLLOUT;
 *        PLLIN��������Ƶ��10MHz��25MHz������M��ֵʹ��PLLOUT���Ƶ�ʵ���100MHz,
 *        ����P��ֵʹFCCOƵ����156MHz��320MHz
 */
am_static_inline
void amhw_lpc84x_clk_pllctrl_set (uint8_t msel, uint8_t psel)
{
    LPC84X_SYSCON->syspllctrl = AM_SBF(psel, 5) | msel;
}

/**
 * \brief �ⲿʱ��Դѡ��
 *
 * \param[in] src : �ⲿʱ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lpc84x_external_clk_src_set (amhw_lpc84x_pllinclk_src_t src)
{
    LPC84X_SYSCON->extclksel = (uint32_t)src;
}


/**
 * \brief PLLʱ��Դѡ��
 *
 * \param[in] src : PLLʱ��Դ
 * 
 * \return ��
 *
 */
am_static_inline
void amhw_lpc84x_clk_pll_src_set (amhw_lpc84x_pllinclk_src_t src)
{
    LPC84X_SYSCON->syspllclksel = (uint32_t)src;
    
    /* ����PLLʱ�� */
    LPC84X_SYSCON->syspllclkuen = 0x00;
    LPC84X_SYSCON->syspllclkuen = 0x01;
}    

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 *
 * \param[in] clk : ָ���Ĵ�ʹ�ܵ�ϵͳ������ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_clk_periph_enable (amhw_lpc84x_clk_periph_t clk)
{
	if (clk <= 31) {
		AM_BIT_SET(LPC84X_SYSCON->sysahbclkctrl0, clk);
	} else {
		AM_BIT_SET(LPC84X_SYSCON->sysahbclkctrl1, clk - 32);
	}

}

/**
 * \brief ����ָ����ϵͳ������ʱ��
 *
 * \param[in] clk : ָ���Ĵ����ܵ�ϵͳ������ʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_clk_periph_disable (amhw_lpc84x_clk_periph_t clk)
{
	if (clk >= 31) {
		AM_BIT_CLR(LPC84X_SYSCON->sysahbclkctrl0, clk);
	} else {
		AM_BIT_CLR(LPC84X_SYSCON->sysahbclkctrl1, clk - 32);
	}
}

/**
 * \brief ��ȡϵͳPLL���ʱ��Ƶ��
 *
 * \return PLL���ʱ��Ƶ��
 */
uint32_t amhw_lpc84x_clk_pllout_rate_get (void);

/**
 * \brief ��ȡϵͳPLL����ʱ��Ƶ��
 *
 * \return PLL����ʱ��Ƶ��
 */
uint32_t amhw_lpc84x_clk_pllin_rate_get (void);

/**
 * \brief �ж�PLL�Ƿ�����
 *
 * \return AM_TRUE  ����
 *          AM_FALSE δ����
 */
am_static_inline
am_bool_t amhw_lpc84x_clk_pll_locked_chk (void)
{
    return (am_bool_t)(LPC84X_SYSCON->syspllstat & 0x01);
}

/**
 * \brief ϵͳ������·����ʹ��/����
 *
 * \param[in] bypass : ��·ϵͳ����  AM_FALSE-����,TURE-ʹ��
 * \param[in] highfr : ����Ƶ�ʷ�Χ  AM_FALSE: 1-20MHz TRUE:15-25MHz
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_clk_pll_bypass_set (am_bool_t bypass, am_bool_t highfr)
{
    if (bypass) {
        AM_BIT_SET(LPC84X_SYSCON->sysoscctrl, 0);
    } else {
        AM_BIT_CLR(LPC84X_SYSCON->sysoscctrl, 0);
    }
    
    if (highfr) {
        AM_BIT_SET(LPC84X_SYSCON->sysoscctrl, 1);
    } else {
        AM_BIT_CLR(LPC84X_SYSCON->sysoscctrl, 1);
    }
}

/**
 * \brief ���� main ʱ��Դ
 *
 * \param[in] src : mainʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_clk_main_src_set (amhw_lpc84x_clk_main_src_t src)
{
    LPC84X_SYSCON->mainclkpllsel = (uint32_t)src;
    
    /* ����mainʱ�� */
    LPC84X_SYSCON->mainclkplluen = 0x00;
    LPC84X_SYSCON->mainclkplluen = 0x01;
}


/**
 * \brief �õ� main ʱ��Դ
 *
 * \return main ʱ��Դ
 */
am_static_inline
amhw_lpc84x_clk_main_src_t amhw_lpc84x_clk_main_src_get (void)
{
    return (amhw_lpc84x_clk_main_src_t)(LPC84X_SYSCON->mainclkpllsel);
}

/**
 * \brief �õ� main ʱ��Դ
 *
 * \return main ʱ��Դ
 */
am_static_inline
amhw_lpc84x_outclk_src_t amhw_lpc84x_outclk_src_get (void)
{
    return (amhw_lpc84x_outclk_src_t)(LPC84X_SYSCON->clkoutsel);
}
/**
 * \brief �ⲿʱ�����ѡ��
 *
 * \param[in] src : ������ⲿ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lpc84x_outclk_src_set (amhw_lpc84x_outclk_src_t src)
{
    LPC84X_SYSCON->clkoutsel = (uint32_t)src;
}

/**
 * \brief �ⲿʱ�����ѡ��
 *
 * \param[in] src : ������ⲿ
 *
 * \return ��
 *
 */
am_static_inline
void amhw_lpc84x_outclk_div_set ( uint32_t div)
{
    LPC84X_SYSCON->clkoutdiv = (uint32_t)div;
}

/**
 * \brief �õ� main ʱ��Ƶ��
 *
 * \return  main ʱ��Ƶ�ʣ���λ:Hz��
 */
uint32_t amhw_lpc84x_clk_main_clkrate_get (void);

/**
 * \brief �õ� outclkʱ��Ƶ��
 */
uint32_t amhw_lpc84x_outclk_clkrate_get (void);

/**
 * \brief ���� CLKOUT ʱ��Դ�ͷ�Ƶֵ
 *
 * \param[in] src : CLKOUT��ʱ��Դ
 * \param[in] div : ��CLKOUTʱ��Դ�ķ�Ƶ
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ������CLKOUT�������������ЧֵΪ1~255. 
 *       ����CLKOUT�ܽ������ʱ��Ƶ��ΪCLKOUTʱ��Դ��Ƶ�ʳ��Է�Ƶϵ����
 */
void amhw_lpc84x_clk_clkout_config (amhw_lpc84x_clk_clkout_src_t src,
                                    uint32_t                     div);

/**
 * \name  WDTOSC��ѡƵ�ʶ���
 * \anchor grp_amhw_lpc84x_clk_wdtosc_rate
 *  @{
 */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_0_6MHZ     1   /**< \brief 0.6MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_1_05MHZ    2   /**< \brief 1.05MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_1_4MHZ     3   /**< \brief 1.4MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_1_75MHZ    4   /**< \brief 1.75MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_2_1MHZ     5   /**< \brief 2.1MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_2_4MHZ     6   /**< \brief 2.4MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_2_7MHZ     7   /**< \brief 2.7MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_3_0MHZ     8   /**< \brief 3.0MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_3_25MHZ    9   /**< \brief 3.25MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_3_5MHZ     10  /**< \brief 3.5MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_3_75MHZ    11  /**< \brief 3.75MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_4_0MHZ     12  /**< \brief 4.0MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_4_2MHZ     13  /**< \brief 4.2MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_4_4MHZ     14  /**< \brief 4.4MHz */
#define AMHW_LPC84X_CLK_WDTOSC_RATE_4_6MHZ     15  /**< \brief 4.6MHz */

/** @} */

/**
 * \brief WDTOSC ���ƼĴ�������
 *
 * \param[in] rate : ѡ���Ź��������Ƶ��, 
 *                   �μ� \ref grp_amhw_lpc84x_clk_wdtosc_rate
 * \param[in] div  : ΪFclkanaѡ���Ƶϵ��, 2 - 64֮���ż��
 *
 * \return ��
 * 
 * \note  ���Ź�����Ƶ���ڸ�λ����Ҫ��������
 */
am_static_inline
void amhw_lpc84x_clk_wdtoscc_cfg (uint8_t rate,
                                  uint8_t div)
{                                          
    LPC84X_SYSCON->wdtoscctrl = AM_SBF((uint8_t) (rate), 5) |
                                     ((div >> 1) - 1);
}

/**
 * \brief ����ϵͳʱ�ӷ�Ƶֵ
 *
 * \param[in] div : ϵͳʱ�ӷ�Ƶֵ
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ������ϵͳʱ�ӣ�������ЧֵΪ1~255.
 *       ϵͳʱ��Ƶ��Ϊ��ʱ��Ƶ�ʳ��Ըô����õ�ϵͳʱ�ӷ�Ƶֵ��
 */
am_static_inline
void amhw_lpc84x_clk_system_clkdiv_set (uint8_t div)
{
    LPC84X_SYSCON->sysahbclkdiv = div;
}

/**
 * \brief �õ�ϵͳʱ�ӷ�Ƶֵ
 *
 * \return ϵͳʱ�ӷ�Ƶֵ
 */
am_static_inline
uint8_t amhw_lpc84x_clk_system_clkdiv_get (void)
{
    return LPC84X_SYSCON->sysahbclkdiv & 0xFF;
}

/**
 * \brief �õ�ϵͳʱ��Ƶ��
 *
 * \return ϵͳʱ��Ƶ��
 */
uint32_t amhw_lpc84x_clk_system_clkrate_get (void);

/**
 * \brief ����ʱ�ӷ�Ƶ
 *
 * \param[in] div : ��Ƶ��ֵ�趨
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ�����ܴ���ʱ�ӣ�������ЧֵΪ1~255.
 *       ����ʱ��Ƶ��Ϊ��ʱ��Ƶ�ʳ��Ըô����õĴ���ʱ�ӷ�Ƶֵ��
 */
am_static_inline
void amhw_lpc84x_syscon_uartclkdiv_set(uint8_t div)
{
    LPC84X_SYSCON->frg0div = div;
}

/**
 * \brief ��ȡADC��������Ƶ��
 * \return ��
 */
uint32_t amhw_lpc84x_clk_adc_baseclkrate_get (void);

/**
 * \brief ��ȡSCT��������Ƶ��
 * \return ��
 */
uint32_t amhw_lpc84x_clk_sct_baseclkrate_get (void);

/**
 * \brief ��ȡ����I2C��SPI��������Ƶ��
 *
 * \return ���ڻ�������Ƶ��ֵ
 */
uint32_t amhw_lpc84x_clk_usart_i2c_spi_baseclkrate_get (int id);


/**
 * \brief ����UART0ʱ������Դ
 */
void amhw_lpc84x_clk_uart0_clk_sel_set (uint32_t uart_clk_sel);

/**
 * \brief ����UART1ʱ������Դ
 */
void amhw_lpc84x_clk_uart1_clk_sel_set (uint32_t uart_clk_sel);

/**
 * \brief ����UART2ʱ������Դ
 */
void amhw_lpc84x_clk_uart2_clk_sel_set (uint32_t uart_clk_sel);
/**
 * \brief ����UART3ʱ������Դ
 */
void amhw_lpc84x_clk_uart3_clk_sel_set (uint32_t uart_clk_sel);

/**
 * \brief ����UART4ʱ������Դ
 */
void amhw_lpc84x_clk_uart4_clk_sel_set (uint32_t uart_clk_sel);

/**
 * \brief ����i2c0ʱ������Դ
 */
void amhw_lpc84x_clk_i2c0_clk_sel_set (uint32_t i2c_clk_sel);

/**
 * \brief ����i2c1ʱ������Դ
 */
void amhw_lpc84x_clk_i2c1_clk_sel_set (uint32_t i2c_clk_sel);

/**
 * \brief ����i2c2ʱ������Դ
 */
void amhw_lpc84x_clk_i2c2_clk_sel_set (uint32_t i2c_clk_sel);

/**
 * \brief ����UART0ʱ������Դ
 */
void amhw_lpc84x_clk_i2c3_clk_sel_set (uint32_t i2c_clk_sel);

/**
 * \brief ����spi0ʱ������Դ
 */
void amhw_lpc84x_clk_spi0_clk_sel_set (uint32_t spi_clk_sel);

/**
 * \brief ����UART0ʱ������Դ
 */
void amhw_lpc84x_clk_spi1_clk_sel_set (uint32_t spi_clk_sel);

/**
 * \brief ����capʱ������Դ
 */
void amhw_lpc84x_clk_cap_clk_sel_set (uint32_t cap_clk_sel);

/**
 * \brief ����sctʱ������Դ
 */
void amhw_lpc84x_sct_clk_sel_set (uint32_t sct_clk_sel, uint8_t sct_clk_div);

/**
 * \brief ����adcʱ������Դ
 */
void amhw_lpc84x_clk_adc_sel_set (uint32_t adc_clk_sel, uint8_t adc_clk_div);
/**
 * \brief ���ô��ڻ�������Ƶ��
 *
 * \param[in] rate : �����Ĵ��ڻ�������Ƶ������ֵ������С��ϵͳʱ��Ƶ�ʣ�
 *
 * \retval   AM_OK     : �����ɹ�
 * \retval  -AM_EINVAL : ��Ч����
 *
 * \note ʵ�ʵĴ��ڻ�������Ƶ��ֵ������������ֵ����ƫ��
 */
int amhw_lpc84x_clk_frg0_baseclkrate_set (uint32_t rate);

/**
 * \brief ���ô��ڻ�������Ƶ��
 *
 * \param[in] rate : �����Ĵ��ڻ�������Ƶ������ֵ������С��ϵͳʱ��Ƶ�ʣ�
 *
 * \retval   AM_OK     : �����ɹ�
 * \retval  -AM_EINVAL : ��Ч����
 *
 * \note ʵ�ʵĴ��ڻ�������Ƶ��ֵ������������ֵ����ƫ��
 */
int amhw_lpc84x_clk_frg1_baseclkrate_set (uint32_t rate);

/**
 * \brief ���� IOCON ʱ�ӷ�Ƶ
 *
 * \param[in] divider : ��Ҫ���õ�IOCON��Ƶ��
 * \param[in] div     : ��Ƶֵ
 *
 * \return ��
 * \note ���÷�Ƶֵ0ʹ�رգ�������Ƶֵ0-255
 */
am_static_inline
void amhw_lpc84x_clk_iocon_div_set (amhw_lpc84x_clk_iocon_div_t divider,
                                    uint8_t                     div)
{
    int t_divider = AMHW_LPC84X_CLK_IOCON_CLKDIV6 - divider;

    LPC84X_SYSCON->ioconclkdiv[t_divider] = div;
}

/**
 * \brief ��ȡIOCON ʱ��Ƶ��
 *
 * \param[in] divider : ��Ҫ��ȡ��IOCON��Ƶ��
 *
 * \return ��ӦIOCON�����˲���Ƶ��
 */
am_static_inline
uint32_t 
amhw_lpc84x_clk_iocon_rate_get (amhw_lpc84x_clk_iocon_div_t divider)
{
    int32_t div = LPC84X_SYSCON->ioconclkdiv[divider] & 0xFF;

    return (div == 0)? (0) : (amhw_lpc84x_clk_main_clkrate_get() / div);
}

/**
 * \brief ������ʱ��
 *
 * \param[in] main_sel : ѡ���ʱ��Դ
 *
 * \return ��ӦIOCON�����˲���Ƶ��
 */
am_static_inline
void amhw_lpc84x_clk_mainclk_set(uint8_t main_sel)
{
    LPC84X_SYSCON->mainclkpllsel     = main_sel;
    LPC84X_SYSCON->mainclkplluen     = 0;
    LPC84X_SYSCON->mainclkplluen     = 1;
}

/**
 * \brief ����froʱ��
 *
 * \param[in] sel : ѡ��Ŀ���ʱ��Դ
 *
 * \return
 */
am_static_inline
void amhw_lpc84x_clk_fro_set(uint32_t fro_sel)
{
	uint32_t temp;
	temp = LPC84X_SYSCON->frooscctrl;
	temp &= ~( fro_sel);
	temp |=   (fro_sel);

	LPC84X_SYSCON->frooscctrl = temp;
	LPC84X_SYSCON->frodirectclkuen = 0;
	LPC84X_SYSCON->frodirectclkuen = 1;
}

/**
 * \brief ������ʱ�ӷ�Ƶֵ
 *
 * \param[in] div : ʱ��Դ��Ƶֵ
 *
 * \return ��ӦIOCON�����˲���Ƶ��
 */
am_static_inline
void amhw_lpc84x_clk_main_div_set(uint8_t div)
{
	LPC84X_SYSCON->sysahbclkdiv =  div;
}

/**
 * \brief �õ����������Ƶ��
 *
 * \param[in] p_periph : ָ������ļĴ������ָ��
 *
 * \return ���������Ƶ��
 *
 */
uint32_t amhw_lpc84x_clk_periph_freq_get (void *p_periph);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_LPC84X_CLK_H */

/* end of file */
