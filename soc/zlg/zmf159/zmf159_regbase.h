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
 * \brief ZMF159 оƬ����Ĵ�����ַ����
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-20  ipk, first implementation
 * \endinternal
 */

#ifndef __ZMF159_REGBASE_H
#define __ZMF159_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zmf159_if_regbase
 * \copydoc zmf159_regbase.h
 * @{
 */

/**
 * \name �����ڴ�ӳ���ַ����
 * @{
 */

/** \brief GPIO����ַ */
#define ZMF159_GPIO_BASE              (0x48000000UL)

/** \brief GPIOA����ַ */
#define ZMF159_GPIOA_BASE             (0x48000000UL)

/** \brief GPIOB����ַ */
#define ZMF159_GPIOB_BASE             (0x48000400UL)

/** \brief GPIOC����ַ */
#define ZMF159_GPIOC_BASE             (0x48000800UL)

/** \brief GPIOD����ַ */
#define ZMF159_GPIOD_BASE             (0x48000C00UL)

/** \brief GPIOE����ַ */
#define ZMF159_GPIOE_BASE             (0x48001000UL)

/** \brief �߼����ƶ�ʱ��1����ַ */
#define ZMF159_TIM1_BASE              (0x40012C00UL)

/** \brief ͨ�ö�ʱ��2����ַ */
#define ZMF159_TIM2_BASE              (0x40000000UL)

/** \brief ͨ�ö�ʱ��3����ַ */
#define ZMF159_TIM3_BASE              (0x40000400UL)

/** \brief ͨ�ö�ʱ��4����ַ */
#define ZMF159_TIM4_BASE              (0x40000800UL)

/** \brief ͨ�ö�ʱ��5����ַ */
#define ZMF159_TIM5_BASE              (0x40000C00UL)

/** \brief ͨ�ö�ʱ��6����ַ */
#define ZMF159_TIM6_BASE              (0x40001000UL)

/** \brief ͨ�ö�ʱ��7����ַ */
#define ZMF159_TIM7_BASE              (0x40001400UL)

/** \brief �߼����ƶ�ʱ��8����ַ */
#define ZMF159_TIM8_BASE              (0x40013400UL)

/** \brief RTC����ַ */
#define ZMF159_RTC_BASE               (0x40002800UL)

/** \brief ���ݿ���BKP����ַ */
#define ZMF159_BKP_BASE               (0x40002824UL)

/** \brief ��Դ����PWR����ַ */
#define ZMF159_PWR_BASE               (0x40007000UL)

/** \brief UART1 ����ַ */
#define ZMF159_UART1_BASE             (0x40013800UL)

/** \brief UART2 ����ַ */
#define ZMF159_UART2_BASE             (0x40004400UL)

/** \brief UART3 ����ַ */
#define ZMF159_UART3_BASE             (0x40004800UL)

/** \brief UART4 ����ַ */
#define ZMF159_UART4_BASE             (0x40004C00UL)

/** \brief UART5 ����ַ */
#define ZMF159_UART5_BASE             (0x40005000UL)

/** \brief UART6 ����ַ */
#define ZMF159_UART6_BASE             (0x40013C00UL)

/** \brief UART7 ����ַ */
#define ZMF159_UART7_BASE             (0x40007800UL)

/** \brief UART8 ����ַ */
#define ZMF159_UART8_BASE             (0x40007C00UL)

/** \brief ADC1 ����ַ */
#define ZMF159_ADC1_BASE              (0x40012400UL)

/** \brief DMA1 ����ַ */
#define ZMF159_DMA1_BASE              (0x40020000UL)

/** \brief DMA2 ����ַ */
#define ZMF159_DMA2_BASE              (0x40020400UL)

/** \brief RCC����������ַ */
#define ZMF159_RCC_BASE               (0x40021000UL)

/** \brief SPI1����������ַ */
#define ZMF159_SPI1_BASE              (0x40013000UL)

/** \brief SPI2����������ַ */
#define ZMF159_SPI2_BASE              (0x40003800UL)

/** \brief SPI3����������ַ */
#define ZMF159_SPI3_BASE              (0x40003C00UL)

/** \brief I2C1����ַ */
#define ZMF159_I2C1_BASE              (0x40005400UL)

/** \brief I2C2����ַ */
#define ZMF159_I2C2_BASE              (0x40005800UL)

/** \brief IWDG����������ַ */
#define ZMF159_IWDG_BASE              (0x40003000UL)

/** \brief WWDG����������ַ */
#define ZMF159_WWDG_BASE              (0x40002C00UL)

/** \brief CAN����������ַ */
#define ZMF159_CAN_BASE               (0x40006400UL)

/** \brief USB����������ַ */
#define ZMF159_USB_BASE               (0x50000000UL)

/** \brief �ⲿ�ж�(�¼�)������EXTI����ַ */
#define ZMF159_EXTI_BASE              (0x40010400UL)

/** \brief FLASH �ӿڻ���ַ */
#define ZMF159_FLASH_BASE             (0x40022000UL)

/** \brief SRAM1����ַ */
#define ZMF159_SRAM1_BASE             (0x20004000UL)

/** \brief SRAM2����ַ */
#define ZMF159_SRAM2_BASE             (0x20000000UL)

/** \brief SYS FLASH ����ַ */
#define ZMF159_SYS_FLASH_BASE         (0x1FFFF400UL)

/** \brief Main FLASH ����ַ */
#define ZMF159_MAIN_FLASH_BASE        (0x08000000UL)

/** \brief CRC����ַ */
#define ZMF159_CRC_BASE               (0x40023000UL)

/** \brief SYSCFG����ַ */
#define ZMF159_SYSCFG_BASE            (0x40010000UL)

/** \brief SYSTICK����ַ */
#define ZMF159_SYSTICK                (0xE000E010UL)

/** @} */

/**
 * @} zmf159_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZMF159_REGBASE_H */

/* end of file */
