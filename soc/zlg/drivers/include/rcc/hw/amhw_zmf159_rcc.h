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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-20  ipk, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_RCC_H
#define __AMHW_ZMF159_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "zmf159_periph_map.h"

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zmf159_if_rcc
 * \copydoc amhw_zmf159_rcc.h
 * @{
 */

/**
 * \brief RCC�Ĵ�����ṹ��
 */
typedef struct amhw_zmf159_rcc {
  __IO uint32_t cr;         /**< \brief ʱ�ӿ��ƼĴ��� */
  __IO uint32_t cfgr;       /**< \brief ʱ�����üĴ��� */
  __IO uint32_t cir;        /**< \brief ʱ���жϼĴ��� */
  __IO uint32_t ahb3rstr;   /**< \brief AHB3���踴λ�Ĵ��� */
  __IO uint32_t ahb2rstr;   /**< \brief AHB2���踴λ�Ĵ��� */
  __IO uint32_t ahb1rstr;   /**< \brief AHB1���踴λ�Ĵ��� */
  __IO uint32_t apb2rstr;   /**< \brief APB2���踴λ�Ĵ��� */
  __IO uint32_t apb1rstr;   /**< \brief APB1���踴λ�Ĵ��� */
  __IO uint32_t ahb3enr;    /**< \brief AHB3����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t ahb2enr;    /**< \brief AHB2����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t ahb1enr;    /**< \brief AHB1����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb2enr;    /**< \brief APB2����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t apb1enr;    /**< \brief APB1����ʱ��ʹ�ܼĴ��� */
  __IO uint32_t bdcr;       /**< \brief ���ݿ��ƼĴ��� */
  __IO uint32_t csr;        /**< \brief ����״̬�Ĵ��� */
  __IO uint32_t syscfg;     /**< \brief ϵͳ���üĴ��� */
} amhw_zmf159_rcc_t;

/**
 * \brief ϵͳʱ��Դ
 */
typedef enum {
    AMHW_ZMF159_SYSCLK_HSI_DIV6,  /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_ZMF159_SYSCLK_HSE,       /**< \brief HSE ��Ϊϵͳʱ�� */
    AMHW_ZMF159_SYSCLK_PLL,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_ZMF159_SYSCLK_LSI,       /**< \brief LSI �����Ϊϵͳʱ�� */
}amhw_zmf159_sys_clk_src;

/**
 * \brief RTCʱ��Դ
 */
typedef enum {
    AMHW_ZMF159_RTCCLK_LSE = 1,       /**< \brief PLL �����Ϊϵͳʱ�� */
    AMHW_ZMF159_RTCCLK_LSI = 2,       /**< \brief HSI ����  6 ��Ƶ��Ϊϵͳʱ�� */
    AMHW_ZMF159_RTCCLK_HSE_DIV128 =3, /**< \brief HSE ��Ϊϵͳʱ�� */
}amhw_zmf159_rtc_clk_src;

/**
 * \brief PLLʱ��Դ
 */
typedef enum {
    AMHW_ZMF159_PLLCLK_HSI_DIV4,  /**< \brief HSI ����  4 ��Ƶ��ΪPLL����ʱ�� */
    AMHW_ZMF159_PLLCLK_HSE,       /**< \brief HSE ��ΪPLL����ʱ�� */
}amhw_zmf159_pll_clk_src;

/**
 * \brief ʱ���жϱ�־
 */
typedef enum {
    AMHW_ZMF159_CLKINT_INDEX_LSI = 0,  /**< \brief LSI��־ */
    AMHW_ZMF159_CLKINT_INDEX_LSE = 1,  /**< \brief LSE��־ */
    AMHW_ZMF159_CLKINT_INDEX_HSI,      /**< \brief HSI��־ */
    AMHW_ZMF159_CLKINT_INDEX_HSE,      /**< \brief HSE��־ */
    AMHW_ZMF159_CLKINT_INDEX_PLL,      /**< \brief PLL��־ */
    AMHW_ZMF159_CLKINT_INDEX_CSSF = 7, /**< \brief CSSF(ʱ�Ӱ�ȫϵͳ�ж�)��־ */
}amhw_zmf159_clk_int_index;

/**
 * \brief AHB1����ö��
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB1_IOPA   = 0,  /**< \brief IOPA */
    AMHW_ZMF159_RCC_AHB1_IOPB   = 1,  /**< \brief IOPB */
    AMHW_ZMF159_RCC_AHB1_IOPC   = 2,  /**< \brief IOPC */
    AMHW_ZMF159_RCC_AHB1_IOPD   = 3,  /**< \brief IOPD */
    AMHW_ZMF159_RCC_AHB1_IOPE   = 4,  /**< \brief IOPE */
    AMHW_ZMF159_RCC_AHB1_SDIO   = 10, /**< \brief SDIO */
    AMHW_ZMF159_RCC_AHB1_CRC    = 12, /**< \brief CRC */
    AMHW_ZMF159_RCC_AHB1_FLASH  = 13, /**< \brief FLASH */
    AMHW_ZMF159_RCC_AHB1_SRAM   = 14, /**< \brief SRAM */
    AMHW_ZMF159_RCC_AHB1_DMA1   = 21, /**< \brief DMA1 */
    AMHW_ZMF159_RCC_AHB1_DMA2   = 22, /**< \brief DMA2 */
}amhw_zmf159_ahb1_peripheral;

/**
 * \brief AHB2����ö��
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB2_USBFS   = 7,  /**< \brief USBFS */
}amhw_zmf159_ahb2_peripheral;

/**
 * \brief AHB3����ö��
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB3_FSMC   = 0,  /**< \brief FSMC */
}amhw_zmf159_ahb3_peripheral;

/**
 * \brief APB2����ö��
 */
typedef enum {
    AMHW_ZMF159_RCC_APB2_TIM1   = 0,  /**< \brief TIM1 */
    AMHW_ZMF159_RCC_APB2_TIM8   = 1,  /**< \brief TIM8 */
    AMHW_ZMF159_RCC_APB2_UART1  = 4,  /**< \brief UART1 */
    AMHW_ZMF159_RCC_APB2_UART6  = 5,  /**< \brief UART6 */
    AMHW_ZMF159_RCC_APB2_ADC1   = 8,  /**< \brief ADC1 */
    AMHW_ZMF159_RCC_APB2_SPI1   = 12, /**< \brief SPI1 */
    AMHW_ZMF159_RCC_APB2_SYSCFG = 14, /**< \brief SYSCFG */
    AMHW_ZMF159_RCC_APB2_COMP   = 15, /**< \brief COMP */
}amhw_zmf159_apb2_peripheral;

/**
 * \brief APB1����ö��
 */
typedef enum {
    AMHW_ZMF159_RCC_APB1_TIM2   = 0,   /**< \brief TIM2��ʱ�� */
    AMHW_ZMF159_RCC_APB1_TIM3   = 1,   /**< \brief TIM3��ʱ�� */
    AMHW_ZMF159_RCC_APB1_TIM4   = 2,   /**< \brief TIM4��ʱ�� */
    AMHW_ZMF159_RCC_APB1_TIM5   = 3,   /**< \brief TIM5��ʱ�� */
    AMHW_ZMF159_RCC_APB1_TIM6   = 4,   /**< \brief TIM6��ʱ�� */
    AMHW_ZMF159_RCC_APB1_TIM7   = 5,   /**< \brief TIM7��ʱ�� */
    AMHW_ZMF159_RCC_APB1_WWDG   = 11,  /**< \brief WWDG���ڿ��Ź� */
    AMHW_ZMF159_RCC_APB1_SPI2   = 14,  /**< \brief SPI2 */
    AMHW_ZMF159_RCC_APB1_SPI3   = 15,  /**< \brief SPI3 */
    AMHW_ZMF159_RCC_APB1_UART2  = 17,  /**< \brief UART2 */
    AMHW_ZMF159_RCC_APB1_UART3  = 18,  /**< \brief UART3 */
    AMHW_ZMF159_RCC_APB1_UART4  = 19,  /**< \brief UART4 */
    AMHW_ZMF159_RCC_APB1_UART5  = 20,  /**< \brief UART5 */
    AMHW_ZMF159_RCC_APB1_I2C1   = 21,  /**< \brief I2C1 */
    AMHW_ZMF159_RCC_APB1_I2C2   = 22,  /**< \brief I2C2 */
    AMHW_ZMF159_RCC_APB1_CRS    = 24,  /**< \brief CRS */
    AMHW_ZMF159_RCC_APB1_CAN    = 25,  /**< \brief CAN */
    AMHW_ZMF159_RCC_APB1_BKP    = 27,  /**< \brief BKP */
    AMHW_ZMF159_RCC_APB1_PWR    = 28,  /**< \brief ��Դ�ӿ� */
    AMHW_ZMF159_RCC_APB1_UART7  = 30,  /**< \brief UART7 */
    AMHW_ZMF159_RCC_APB1_UART8  = 31,  /**< \brief UART8 */
}amhw_zmf159_apb1_peripheral;

/**
 * \brief ��λ��־
 */
#define    AMHW_ZMF159_RCC_CSR_PINRSTF    (1ul << 26) /**< \brief NRST�ܽŸ�λ��־ */
#define    AMHW_ZMF159_RCC_CSR_PORRSTF    (1ul << 27) /**< \brief �ϵ�/���縴λ��־ */
#define    AMHW_ZMF159_RCC_CSR_SFTRSTF    (1ul << 28) /**< \brief �����λ��־ */
#define    AMHW_ZMF159_RCC_CSR_IWDGRSTF   (1ul << 29) /**< \brief �������Ź���λ��־ */
#define    AMHW_ZMF159_RCC_CSR_WWDGRSTF   (1ul << 30) /**< \brief ���ڿ��Ź���λ��־ */
#define    AMHW_ZMF159_RCC_CSR_LPWRRSTF   (1ul << 31) /**< \brief �͹��Ĺ���λ��־ */


/**
 * \brief ϵͳ���üĴ���ö��
 */
typedef enum{
    AMHW_ZMF159_RCC_SYSCFG_0  =0,
    AMHW_ZMF159_RCC_SYSCFG_1  =1,
}amhw_zmf159_syscfg_peripheral;

/**
 * \brief USBʱ��Դѡ��
 */
typedef enum{
    AMHW_ZMF159_RCC_USB_PLL_48M  =0,
    AMHW_ZMF159_RCC_USB_HSI_48M  =1,
}amhw_zmf159_usb_clk_t;

/**
 * \brief �ڲ�����ʱ��ʹ��
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zmf159_rcc_hsion_enable (void)
{
    ZMF159_RCC->cr |= 1ul;
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 8MHzʱ��û�о���
 * \retval FALSE : �ڲ� 8MHzʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_hsirdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ��(HSE ����)ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_hseon_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 16);
}

/**
 * \brief �ⲿ����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ⲿʱ��û�о���
 * \retval FALSE : �ⲿʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_hserdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & (1ul << 17)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_hsebyp_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 18);
}

/**
 * \brief ʱ�Ӱ�ȫϵͳʹ��
 *
 * \details ����ⲿ 8-24MHz����������ʱ�Ӽ����������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ccson_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 19);
}

/**
 * \brief PLL��Ƶϵ������
 *
 * \param[in]  div ����Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_plldm_set (uint8_t div)
{
    ZMF159_RCC->cr = ((div & 0x7ul) << 20) |
                            (ZMF159_RCC->cr & ~(0x7ul << 20));
}

/**
 * \brief PLL��Ƶϵ������
 *
 * \param[in]  mul ����Ƶֵ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_plldn_set (uint8_t mul)
{

    ZMF159_RCC->cr = ((mul & 0x3ful) << 26) |
                            (ZMF159_RCC->cr & ~(0x3ful << 26));
}

/**
 * \brief PLL ʹ��
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_pll_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 24);
}

/**
 * \brief PLL ����
 *
 * \details �����������ֹͣģʽʱ����λ��Ӳ�����㡣
 *          �� PLL ʱ�ӱ�������ѡ��Ҫ��Ϊϵͳʱ��ʱ,
 *          ��λ���ܱ����㡣
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_pll_disable (void)
{
    ZMF159_RCC->cr &= ~(1ul << 24);
}

/**
 * \brief PLL ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : PLL δ����
 * \retval FALSE : PLL ����
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_pllrdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & (1ul << 25)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ϵͳʱ���л�
 *
 * \param[in]  src ��ϵͳʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_sys_clk_set (amhw_zmf159_sys_clk_src src)
{

    ZMF159_RCC->cfgr = ((src & 0x3ul) << 0) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 0));
}

/**
 * \brief ��ǰϵͳʱ�ӻ�ȡ
 *
 * \return ��ǰϵͳʱ��Դ
 */
am_static_inline
amhw_zmf159_sys_clk_src amhw_zmf159_rcc_sys_clk_get (void)
{

    return (amhw_zmf159_sys_clk_src)((ZMF159_RCC->cfgr >> 2ul) & 0x3ul);
}

/**
 * \brief ����AHB1 Ԥ��Ƶ
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-7 �� ����Ƶ
 *       - 8   �� 2��Ƶ
 *       - 9   �� 4��Ƶ
 *       - 10  �� 8��Ƶ
 *       - 11  �� 16��Ƶ
 *       - 12  �� 64��Ƶ
 *       - 13  �� 128��Ƶ
 *       - 14  �� 256��Ƶ
 *       - 15  �� 512��Ƶ
 *
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0xful) << 4) |
                              (ZMF159_RCC->cfgr & ~(0xful << 4));
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB1��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb1_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x7ul) << 8) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 8));
}

/**
 * \brief ��ȡ ���� APB1 Ԥ��Ƶ��APB1��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_zmf159_rcc_apb1_div_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 8) & 0x7ul);
}

/**
 * \brief ���� ���� APB Ԥ��Ƶ��APB2��
 *
 * \param[in]  div ��Ԥ��Ƶֵ
 *
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb2_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x7ul) << 11) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 11));
}

/**
 * \brief ��ȡ ���� APB Ԥ��Ƶ��APB2��
 *
 * \return Ԥ��Ƶֵ
 *       - 0-3 �� ����Ƶ
 *       - 4   �� 2��Ƶ
 *       - 5   �� 4��Ƶ
 *       - 6   �� 8��Ƶ
 *       - 7   �� 16��Ƶ
 */
am_static_inline
uint8_t amhw_zmf159_rcc_apb2_div_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 11) & 0x7ul);
}

/**
 * \brief STOP ģʽ������ʱ�ӿ���λ
 *
 * \param[in]  statusֵ ��AM_TRUE�� ��STOPģʽ�£�Ӳ�������Զ��ر�PLL��HSI��HSE
 *                               ��PLL_LDO���û�����ͨ������RCC_CR�Ĵ������ر���Ӧʱ��
 *
 *                      AM_FALSE����STOPģʽ�£�Ӳ�������Զ��ر�PLL��HSI��HSE��PLL_LDO
 *
 * \return ��
 */
am_static_inline
void amhw_amf159_rcc_ckoff_sft_set (am_bool_t status)
{
    ZMF159_RCC->cfgr |= AM_SBF(status, 14);
}

/**
 * \brief USB 48Mʱ��Դѡ��
 *
 * \return ��
 */
am_static_inline
void amhw_amf159_rcc_clk48msel_set (amhw_zmf159_usb_clk_t flog)
{
    ZMF159_RCC->cfgr |= AM_SBF(flog, 15);
}

/**
 * \brief PLL����ʱ��ѡ��
 *
 * \param[in]  src ��PLL����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_pll_clk_set (amhw_zmf159_pll_clk_src src)
{

    ZMF159_RCC->cfgr = ((src & 0x3ul) << 16) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 16));
}

/**
 * \brief ��ǰPLL����ʱ�ӻ�ȡ
 *
 * \return ��ǰPLL����ʱ��Դ
 */
am_static_inline
amhw_zmf159_pll_clk_src amhw_zmf159_rcc_pll_clk_get (void)
{

    return (amhw_zmf159_pll_clk_src)((ZMF159_RCC->cfgr >> 16ul) & 0x3ul);
}

/**
 * \brief ѡ�� HSE ��Ƶ����Ϊ PLL ����
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� ����Ƶ
 *      - 1  �� 2��Ƶ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_hseforpll_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x1ul) << 17) |
                              (ZMF159_RCC->cfgr & ~(0x1ul << 17));
}

/**
 * \brief ѡ�� USB Ԥ��Ƶ
 *
 * \param[in]  div ����Ƶֵ
 *
 *      - 0  �� PLL ʱ��ֱ����Ϊ USB ʱ��
 *      - 1  �� PLL ʱ��2 ��Ƶ��Ϊ USBʱ��
 *      - 2  �� PLL ʱ��3 ��Ƶ��Ϊ USBʱ��
 *      - 3  �� PLL ʱ��4 ��Ƶ��Ϊ USBʱ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_pllforusb_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x3ul) << 22) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 22));
}

/**
 * \brief USB Ԥ��Ƶ��ȡ
 *
 * \retval  0  �� PLL ʱ��ֱ����Ϊ USB ʱ��
 * \retval  1  �� PLL ʱ��2 ��Ƶ��Ϊ USBʱ��
 * \retval  2  �� PLL ʱ��3 ��Ƶ��Ϊ USBʱ��
 * \retval  3  �� PLL ʱ��4 ��Ƶ��Ϊ USBʱ��
 */
am_static_inline
uint8_t amhw_zmf159_rcc_pllforusb_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 22ul) & 0x3ul);
}

/**
 * \brief ΢������ʱ�����ѡ��
 *
 * \details 1.��ʱ��������������л� MCO ʱ��Դʱ���ܻᱻ�ض�,
 *          2.��ϵͳʱ����Ϊ����� MCO �ܽ�ʱ���뱣֤���ʱ��Ƶ
 *            �ʲ����� 50MHz��IO�����Ƶ�ʣ�
 *
 * \param[in]  src ��ʱ��Դ
 *
 *      - 0-1 �� û��ʱ�����
 *      - 2   �� LSI ʱ�����
 *      - 3   �� ����
 *      - 4   �� ϵͳʱ�ӣ�SYSCLK�����
 *      - 5   �� HSI ʱ�����
 *      - 6   �� HSE ʱ�����
 *      - 7   �� PLL ʱ��2 ��Ƶ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_mco_src_set (uint8_t src)
{

    ZMF159_RCC->cfgr = ((src & 0x7ul) << 24ul) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 24ul));
}

/**
 * \brief �����ж�ʹ��
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_clkint_enable (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir |= ((index & 0x1ful) << 8);
}

/**
 * \brief �����жϽ���
 *
 * \param[in]  index ��������־
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_clkint_disable (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir &= ~((index & 0x1ful) << 8);
}

/**
 * \brief ��ȡ�жϱ�־
 *
 * \return �жϱ�־
 */
am_static_inline
amhw_zmf159_clk_int_index amhw_zmf159_rcc_clkint_flag_read (void)
{

    return (amhw_zmf159_clk_int_index)(ZMF159_RCC->cir & 0x9ful);
}

/**
 * \brief ����жϱ�־
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_clkint_flag_clear (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir |= ((index & 0x9ful) << 16);
}

/**
 * \brief ��λAHB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_reset (amhw_zmf159_ahb1_peripheral reset)
{

    ZMF159_RCC->ahb1rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAHB1����
 *
 * \param[in]  reset ����Ҫֹͣ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_reset_stop (amhw_zmf159_ahb1_peripheral reset)
{

    ZMF159_RCC->ahb1rstr &= ~(1ul << reset);
}

/**
 * \brief ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb2_reset (amhw_zmf159_apb2_peripheral reset)
{

    ZMF159_RCC->apb2rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB2����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb2_reset_stop (amhw_zmf159_apb2_peripheral reset)
{

    ZMF159_RCC->apb2rstr &= ~(1ul << reset);
}

/**
 * \brief ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb1_reset (amhw_zmf159_apb1_peripheral reset)
{

    ZMF159_RCC->apb1rstr |= (1ul << reset);
}

/**
 * \brief ֹͣ��λAPB1����
 *
 * \param[in]  reset ����Ҫ��λ������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb1_reset_stop (amhw_zmf159_apb1_peripheral reset)
{

    ZMF159_RCC->apb1rstr &= ~(1ul << reset);
}

/**
 * \brief ʹ��APB1����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb1_enable (amhw_zmf159_apb1_peripheral peri)
{

    ZMF159_RCC->apb1enr |= (1ul << peri);
}

/**
 * \brief ����APB1����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb1_disable (amhw_zmf159_apb1_peripheral peri)
{

    ZMF159_RCC->apb1enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��APB2����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb2_enable (amhw_zmf159_apb2_peripheral peri)
{

    ZMF159_RCC->apb2enr |= (1ul << peri);
}

/**
 * \brief ����APB2����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_apb2_disable (amhw_zmf159_apb2_peripheral peri)
{

    ZMF159_RCC->apb2enr &= ~(1ul << peri);
}

/**
 * \brief ʹ��AHB1����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_enable (amhw_zmf159_ahb1_peripheral peri)
{

    ZMF159_RCC->ahb1enr |= (1 << peri);
}

/**
 * \brief ����AHB1����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_disable (amhw_zmf159_ahb1_peripheral peri)
{

    ZMF159_RCC->ahb1enr &= ~(1 << peri);
}

/**
 * \brief ʹ��AHB2����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb2_enable (amhw_zmf159_ahb2_peripheral peri)
{

    ZMF159_RCC->ahb2enr |= (1 << peri);
}

/**
 * \brief ����AHB2����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb2_disable (amhw_zmf159_ahb2_peripheral peri)
{

    ZMF159_RCC->ahb2enr &= ~(1 << peri);
}

/**
 * \brief ʹ��AHB3����
 *
 * \param[in]  peri ����Ҫʹ�ܵ�����
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_ahb3_enable (amhw_zmf159_ahb3_peripheral peri)
{

    ZMF159_RCC->ahb3enr |= (1 << peri);
}

/**
 * \brief ����AHB3����
 *
 * \param[in]  peri ����Ҫ���ܵ�����
 *
 * \return ��
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb3_disable (amhw_zmf159_ahb3_peripheral peri)
{

    ZMF159_RCC->ahb3enr &= ~(1 << peri);
}

/**
 * \brief ʹ��LSI
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_lsi_enable (void)
{

    ZMF159_RCC->csr |= (1ul << 0);
}

/**
 * \brief ����LSI
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_lsi_disable (void)
{

    ZMF159_RCC->csr &= ~(1ul << 0);
}

/**
 * \brief �ڲ�����ʱ�Ӿ�����־��ȡ
 *
 * \retval TRUE  : �ڲ� 40kHz ����ʱ�Ӿ���
 * \retval FALSE : �ڲ� 40kHz ����ʱ��δ����
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_lsirdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->csr & (1ul << 1)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief ��ȡ��λ��־
 *
 * \return ��λ��־
 */
am_static_inline
uint32_t amhw_zmf159_rcc_reset_flag (void)
{

    return (uint32_t)(ZMF159_RCC->csr & 0xfc000000);
}

/**
 * \brief �����λ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_reset_flag_clear (void)
{

    ZMF159_RCC->csr |= (1ul << 24);
}
/**
 * \brief �ⲿ��������ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lseon_enable (void)
{

    ZMF159_RCC->bdcr |= (1ul << 0);
}
/**
 * \brief �ⲿ������������
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lseon_disable (void)
{
    ZMF159_RCC->bdcr &= ~(1ul << 0);
}
/**
 * \brief �ⲿ��������������־��ȡ
 *
 * \retval TRUE  : �ڲ� 32MHzʱ��û�о���
 * \retval FALSE : �ڲ� 32MHzʱ�Ӿ���
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_bdcr_lserdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->bdcr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lsebyp_set (uint32_t lsebyp)
{
    ZMF159_RCC->bdcr |= (lsebyp << 2);
}
/**
 * \brief �ⲿ����ʱ����·״̬
 *
 * \retval TRUE  : LSE ʱ�ӱ���·
 * \retval FALSE : LSE ʱ��δ����·
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_bdcr_lsebyp_get (void)
{
    return (am_bool_t)((ZMF159_RCC->bdcr & 0x4ul) ? AM_TRUE : AM_FALSE);
}
/**
 * \brief RTC����ʱ��ѡ��
 *
 * \param[in]  src ��RTC����ʱ��Դ
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_clk_set (amhw_zmf159_rtc_clk_src src)
{

    ZMF159_RCC->bdcr = ((src & 0x3ul) << 8) |
                              (ZMF159_RCC->bdcr & ~(0x3ul << 8));
}

/**
 * \brief RTC����ʱ�ӻ�ȡ
 *
 * \retval  rtcʱ��Դ��ȡ
 */
am_static_inline
amhw_zmf159_rtc_clk_src amhw_zmf159_rcc_bdcr_rtc_clk_get (void)
{
    return (amhw_zmf159_rtc_clk_src)((ZMF159_RCC->bdcr >> 8) & 0x3ul);
}

/**
 * \brief RTCʱ��ʹ��
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_enable (void)
{

    ZMF159_RCC->bdcr |= (1ul << 15);
}
/**
 * \brief RTCʱ�ӽ���
 *
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_disable (void)
{

    ZMF159_RCC->bdcr &= ~(1ul << 15);
}

/**
 * \brief �����������λ
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_bdrst_reset (void)
{

    ZMF159_RCC->bdcr |= (1ul << 16);
}
/**
 * \brief �����������λ����
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_bdrst_reset_end (void)
{

    ZMF159_RCC->bdcr &= ~(1ul << 16);
}
/**
 * \brief ϵͳ���üĴ���flash����
 *
 * \param[in] flag flashҳ����ʱ�����Ĵ�С 1��1K�ֽ� 0��512�ֽ�
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_syscfg_erasure (uint32_t flag)
{

    ZMF159_RCC->syscfg &= (flag << 1);
}
/**
 * \brief ϵͳ���üĴ���flash���
 *
 * \param[in] flag flashҳ����ʱ�Ƿ��� 1����� 0�������
 * \return ��
 */
am_static_inline
void amhw_zmf159_rcc_syscfg_checkout (uint32_t flag)
{

    ZMF159_RCC->syscfg &= (flag << 0);
}

/**
 * @}
 */
/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __ZMF159_RCC_H */

#endif

/* end of file */
