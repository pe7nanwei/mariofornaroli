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
 * \brief ZLG GPIO �������ò�������
 *
 * \note: �������Ź��ܵ�ʱ��һ��Ҫͬʱ�������ŵ�ģʽ����������ģʽ������ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __ZMF159_PIN_H
#define __ZMF159_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zmf159_gpio_util.h"

 /**
 * \addtogroup zmf159_if_pin
 * \copydoc zmf159_pin.h
 * @{
 */

/**
 * \name ZMF159 GPIO ���ű��
 * \anchor grp_gpio_pin_number
 * @{
 */

#define PIOA            0         /**< \brief �˿�A������ʼ�� */
#define PIOA_0          0         /**< \brief PIOA_0 ���ź� */
#define PIOA_1          1         /**< \brief PIOA_1 ���ź� */
#define PIOA_2          2         /**< \brief PIOA_2 ���ź� */
#define PIOA_3          3         /**< \brief PIOA_3 ���ź� */
#define PIOA_4          4         /**< \brief PIOA_4 ���ź� */
#define PIOA_5          5         /**< \brief PIOA_5 ���ź� */
#define PIOA_6          6         /**< \brief PIOA_6 ���ź� */
#define PIOA_7          7         /**< \brief PIOA_7 ���ź� */
#define PIOA_8          8         /**< \brief PIOA_8 ���ź� */
#define PIOA_9          9         /**< \brief PIOA_9 ���ź� */
#define PIOA_10         10        /**< \brief PIOA_10 ���ź� */
#define PIOA_11         11        /**< \brief PIOA_11 ���ź� */
#define PIOA_12         12        /**< \brief PIOA_13 ���ź� */
#define PIOA_13         13        /**< \brief PIOA_13 ���ź� */
#define PIOA_14         14        /**< \brief PIOA_14 ���ź� */
#define PIOA_15         15        /**< \brief PIOA_15 ���ź� */

#define PIOB            16        /**< \brief �˿�B������ʼ�� */
#define PIOB_0          16        /**< \brief PIOB_0 ���ź� */
#define PIOB_1          17        /**< \brief PIOB_1 ���ź� */
#define PIOB_2          18        /**< \brief PIOB_2 ���ź� */
#define PIOB_3          19        /**< \brief PIOB_3 ���ź� */
#define PIOB_4          20        /**< \brief PIOB_4 ���ź� */
#define PIOB_5          21        /**< \brief PIOB_5 ���ź� */
#define PIOB_6          22        /**< \brief PIOB_6 ���ź� */
#define PIOB_7          23        /**< \brief PIOB_7 ���ź� */
#define PIOB_8          24        /**< \brief PIOB_8 ���ź� */
#define PIOB_9          25        /**< \brief PIOB_9 ���ź� */
#define PIOB_10         26        /**< \brief PIOB_10���ź� */
#define PIOB_11         27        /**< \brief PIOB_11���ź� */
#define PIOB_12         28        /**< \brief PIOB_12���ź� */
#define PIOB_13         29        /**< \brief PIOB_13���ź� */
#define PIOB_14         30        /**< \brief PIOB_14���ź� */
#define PIOB_15         31        /**< \brief PIOB_15���ź� */

#define PIOC            32        /**< \brief �˿�C������ʼ�� */
#define PIOC_0          32        /**< \brief PIOC_0 ���ź� */
#define PIOC_1          33        /**< \brief PIOC_1 ���ź� */
#define PIOC_2          34        /**< \brief PIOC_2 ���ź� */
#define PIOC_3          35        /**< \brief PIOC_3 ���ź� */
#define PIOC_4          36        /**< \brief PIOC_4 ���ź� */
#define PIOC_5          37        /**< \brief PIOC_5 ���ź� */
#define PIOC_6          38        /**< \brief PIOC_6 ���ź� */
#define PIOC_7          39        /**< \brief PIOC_7 ���ź� */
#define PIOC_8          40        /**< \brief PIOC_8 ���ź� */
#define PIOC_9          41        /**< \brief PIOC_9 ���ź� */
#define PIOC_10         42        /**< \brief PIOC_10���ź� */
#define PIOC_11         43        /**< \brief PIOC_11���ź� */
#define PIOC_12         44        /**< \brief PIOC_12���ź� */
#define PIOC_13         45        /**< \brief PIOC_13���ź� */
#define PIOC_14         46        /**< \brief PIOC_14���ź� */
#define PIOC_15         47        /**< \brief PIOC_15���ź� */

#define PIOD            48        /**< \brief �˿�D������ʼ�� */
#define PIOD_0          48        /**< \brief PIOD_0 ���ź� */
#define PIOD_1          49        /**< \brief PIOD_1 ���ź� */
#define PIOD_2          50        /**< \brief PIOD_2 ���ź� */
#define PIOD_3          51        /**< \brief PIOD_3 ���ź� */
#define PIOD_4          52        /**< \brief PIOD_4 ���ź� */
#define PIOD_5          53        /**< \brief PIOD_5 ���ź� */
#define PIOD_6          54        /**< \brief PIOD_6 ���ź� */
#define PIOD_7          55        /**< \brief PIOD_7 ���ź� */
#define PIOD_8          56        /**< \brief PIOD_8 ���ź� */
#define PIOD_9          57        /**< \brief PIOD_9 ���ź� */
#define PIOD_10         58        /**< \brief PIOD_10���ź� */
#define PIOD_11         59        /**< \brief PIOD_11���ź� */
#define PIOD_12         60        /**< \brief PIOD_12���ź� */
#define PIOD_13         61        /**< \brief PIOD_13���ź� */
#define PIOD_14         62        /**< \brief PIOD_14���ź� */
#define PIOD_15         63        /**< \brief PIOD_15���ź� */

#define PIOE            64        /**< \brief �˿�E������ʼ�� */
#define PIOE_0          64        /**< \brief PIOE_0 ���ź� */
#define PIOE_1          65        /**< \brief PIOE_1 ���ź� */
#define PIOE_2          66        /**< \brief PIOE_2 ���ź� */
#define PIOE_3          67        /**< \brief PIOE_3 ���ź� */
#define PIOE_4          68        /**< \brief PIOE_4 ���ź� */
#define PIOE_5          69        /**< \brief PIOE_5 ���ź� */
#define PIOE_6          70        /**< \brief PIOE_6 ���ź� */
#define PIOE_7          71        /**< \brief PIOE_7 ���ź� */
#define PIOE_8          72        /**< \brief PIOE_8 ���ź� */
#define PIOE_9          73        /**< \brief PIOE_9 ���ź� */
#define PIOE_10         74        /**< \brief PIOE_10���ź� */
#define PIOE_11         75        /**< \brief PIOE_11���ź� */
#define PIOE_12         76        /**< \brief PIOE_12���ź� */
#define PIOE_13         77        /**< \brief PIOE_13���ź� */
#define PIOE_14         78        /**< \brief PIOE_14���ź� */
#define PIOE_15         79        /**< \brief PIOE_15���ź� */

/**
 * \brief ������ĿΪ72
 */
#define PIN_NUM         80

/**
 * \brief ֧��ͬʱ������������ж�����16
 */
#define PIN_INT_MAX     16

/** @} */

/**
 * \name ZMF159 ���Ŷ���,����������SWCK��SWIO֮�⣬�������Ÿ�λʱ��Ĭ��ΪGPIO����(��������)
 * @{
 */

/******************************************************************************/

/**
 * \name PIOA_0���Ÿ��ù���
 * @{
 */
#define PIOA_0_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_0_TIM5_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM5_CH1_ETR */
#define PIOA_0_TIM8_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1_ETR */
#define PIOA_0_UART2_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOA_0_UART4_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_TX */
#define PIOA_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_0���Ÿ���ʱ����ģʽ
 * @{
 */
#define PIOA_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */
/** @} */

/**
 * \name PIOA_0������Ӧ����
 * @{
 */
#define PIOA_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */
/** @} */

/******************************************************************************/

/**
 * \name PIOA_1���Ÿ��ù���
 * @{
 */


#define PIOA_1_TIM2_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH2 */
#define PIOA_1_TIM5_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH2 */
#define PIOA_1_UART2_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_RTS */
#define PIOA_1_UART4_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_RX */
#define PIOA_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_1������Ӧ����
 * @{
 */

#define PIOA_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_2���Ÿ��ù���
 * @{
 */

#define PIOA_2_TIM2_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH3 */
#define PIOA_2_TIM5_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM5_CH3 */
#define PIOA_2_UART2_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_TX */
#define PIOA_2_CPT2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT2_OUT */
#define PIOA_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_2������Ӧ����
 * @{
 */

#define PIOA_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_3���Ÿ��ù���
 * @{
 */

#define PIOA_3_TIM2_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH4 */
#define PIOA_3_TIM5_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH4 */
#define PIOA_3_UART2_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_RX */
#define PIOA_3_ADC_IN3        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN3 */
#define PIOA_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_3������Ӧ����
 * @{
 */

#define PIOA_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_4���Ÿ��ù���
 * @{
 */

#define PIOA_4_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)    /**< \brief SPI1_NSS */
#define PIOA_4_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)    /**< \brief SPI3_NSS */
#define PIOA_4_UART5_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)    /**< \brief UART5_TX */
#define PIOA_4_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0D)    /**< \brief SPI1_MOSI */
#define PIOA_4_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0E)    /**< \brief SPI1_MISO */
#define PIOA_4_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief SPI1_SCK */
#define PIOA_4_ADC_IN4        AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief ADC_IN4 */
#define PIOA_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_4������Ӧ����
 * @{
 */

#define PIOA_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_5���Ÿ��ù���
 * @{
 */

#define PIOA_5_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_5_TIM8_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM2_CH1N */
#define PIOA_5_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOA_5_UART5_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_RX */
#define PIOA_5_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_NSS */
#define PIOA_5_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_MOSI */
#define PIOA_5_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MISO */
#define PIOA_5_ADC_IN5        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN5 */
#define PIOA_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_5������Ӧ����
 * @{
 */

#define PIOA_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_6���Ÿ��ù���
 * @{
 */

#define PIOA_6_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_BKIN */
#define PIOA_6_TIM3_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOA_6_TIM8_KIN       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM3_CH3 */
#define PIOA_6_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MISO */
#define PIOA_6_CPT1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT1_OUT */
#define PIOA_6_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_SCK */
#define PIOA_6_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_NSS */
#define PIOA_6_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MOSI */
#define PIOA_6_ADC_IN6        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN6 */
#define PIOA_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_6������Ӧ����
 * @{
 */

#define PIOA_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_7���Ÿ��ù���
 * @{
 */

#define PIOA_7_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1N */
#define PIOA_7_TIM3_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH2 */
#define PIOA_7_TIM8_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOA_7_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOA_7_CRS_SYNC       AM_ZMF159_GPIO_FUNC_CODE(0x0A)   /**< \brief CPT1_OUT */
#define PIOA_7_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_SCK */
#define PIOA_7_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_NSS */
#define PIOA_7_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MOSI */
#define PIOA_7_ADC_IN7        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN7 */
#define PIOA_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_7���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_7������Ӧ����
 * @{
 */

#define PIOA_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_8���Ÿ��ù���
 * @{
 */

#define PIOA_8_MCO1           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief MCO */
#define PIOA_8_TIM1_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1 */
#define PIOA_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_8������Ӧ����
 * @{
 */

#define PIOA_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_9���Ÿ��ù���
 * @{
 */


#define PIOA_9_TIM1_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH2 */
#define PIOA_9_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOA_9_UART1_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_TX */
#define PIOA_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_9������Ӧ����
 * @{
 */

#define PIOA_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_10���Ÿ��ù���
 * @{
 */

#define PIOA_10_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3 */
#define PIOA_10_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief I2C_SDA */
#define PIOA_10_UART1_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RX */
#define PIOA_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_10������Ӧ����
 * @{
 */

#define PIOA_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_11���Ÿ��ù���
 * @{
 */

#define PIOA_11_TIM1_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH4 */
#define PIOA_11_UART1_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_CTS */
#define PIOA_11_CAP1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART1_CTS */
#define PIOA_11_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief UART1_CTS */
#define PIOA_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_11������Ӧ����
 * @{
 */

#define PIOA_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_12���Ÿ��ù���
 * @{
 */

#define PIOA_12_TIM1_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_ETR */
#define PIOA_12_UART1_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RTS */
#define PIOA_12_CAP2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CAP2_OUT */
#define PIOA_12_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOA_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */

#define PIOA_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_12������Ӧ����
 * @{
 */

#define PIOA_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_13���Ÿ��ù���
 * @{
 */

#define PIOA_13_SWDIO          AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SWDIO */
#define PIOA_13_USB_VBUS_ON    AM_ZMF159_GPIO_FUNC_CODE(0x0A)   /**< \brief USB_VBUS_ON */
#define PIOA_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_13������Ӧ����
 * @{
 */

#define PIOA_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_14���Ÿ��ù���
 * @{
 */

#define PIOA_14_SWDCLK         AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SWDCLK */
#define PIOA_14_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief UART2_TX */
#define PIOA_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_14������Ӧ����
 * @{
 */

#define PIOA_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_15���Ÿ��ù���
 * @{
 */

#define PIOA_15_JTDI           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief JTD1 */
#define PIOA_15_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_15_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief UART2_RX */
#define PIOA_15_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_NSS */
#define PIOA_15_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_NSS */
#define PIOA_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOA_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOA_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOA_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOA_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOA_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOA_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOA_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOA_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOA_15������Ӧ����
 * @{
 */

#define PIOA_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOA_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOA_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_0���Ÿ��ù���
 * @{
 */

#define PIOB_0_TIM1_CH2N       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_0_TIM3_CH3        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOB_0_TIM8_CH2N       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_0_UART6_TX        AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOB_0_ADC_IN8         AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN8 */
#define PIOB_0_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_0������Ӧ����
 * @{
 */

#define PIOB_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_1���Ÿ��ù���
 * @{
 */

#define PIOB_1_TIM1_CH3N       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_1_TIM3_CH4        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOB_1_TIM8_CH3N       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_1_UART6_RX        AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_RX */
#define PIOB_1_ADC_IN9         AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN9 */
#define PIOB_1_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_1_AIN           AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_1_INPUT_FLOAT   AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_1_INPUT_PD      AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_1_INPUT_PU      AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_1_OUT_PP        AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_1_OUT_OD        AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_1_AF_PP         AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_1_AF_OD         AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_1������Ӧ����
 * @{
 */

#define PIOB_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_2���Ÿ��ù���
 * @{
 */

#define PIOB_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_2������Ӧ����
 * @{
 */

#define PIOB_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_3���Ÿ��ù���
 * @{
 */
#define PIOB_3_JTDO           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief JTD0 */
#define PIOB_3_TRACESWO       AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_SCK */
#define PIOB_3_TIM2_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1 */
#define PIOB_3_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOB_3_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI1_SCK */
#define PIOB_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOB_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_3������Ӧ����
 * @{
 */

#define PIOB_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_4���Ÿ��ù���
 * @{
 */
#define PIOB_4_NJRST          AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief NJTRST */
#define PIOB_4_TIM3_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOB_4_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MISO */
#define PIOB_4_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI1_MISO */
#define PIOB_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_4������Ӧ����
 * @{
 */

#define PIOB_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_5���Ÿ��ù���
 * @{
 */

#define PIOB_5_TIM3_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH2 */
#define PIOB_5_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOB_5_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_MOSI */
#define PIOB_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)  /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_5������Ӧ����
 * @{
 */

#define PIOB_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_6���Ÿ��ù���
 * @{
 */

#define PIOB_6_TIM4_CH1      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1N */
#define PIOB_6_I2C1_SCL      AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_6_UART1_TX      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_TX */
#define PIOB_6_UART7_TX      AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOB_6_GPIO          AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */


/** @} */

/**
 * \name PIOB_6���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_6������Ӧ����
 * @{
 */

#define PIOB_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_7���Ÿ��ù���
 * @{
 */

#define PIOB_7_TIM4_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH2 */
#define PIOB_7_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_7_UART1_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RX */
#define PIOB_7_UART7_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_RX */
#define PIOB_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_7�ܽŸ���ʱ���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ(Ĭ��) */
#define PIOB_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_7������Ӧ����
 * @{
 */

#define PIOB_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_8���Ÿ��ù���
 * @{
 */
#define PIOB_8_TIM4_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH3 */
#define PIOB_8_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_8_CPT1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief I2C_SCL */
#define PIOB_8_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief I2C_SCL */
#define PIOB_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_8������Ӧ����
 * @{
 */

#define PIOB_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_9���Ÿ��ù���
 * @{
 */

#define PIOB_9_TIM4_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH4 */
#define PIOB_9_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_9_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOB_9_CPT2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT2_OUT */
#define PIOB_9_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOB_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_9������Ӧ����
 * @{
 */

#define PIOB_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_10���Ÿ��ù���
 * @{
 */

#define PIOB_10_TIM2_CH3      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH3 */
#define PIOB_10_I2C2_SCL      AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_10_SPI2_SCK      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_10_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX */
#define PIOB_10_GPIO          AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_10���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_10������Ӧ����
 * @{
 */

#define PIOB_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_11���Ÿ��ù���
 * @{
 */

#define PIOB_11_TIM2_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH4 */
#define PIOB_11_I2C2_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_11_UART_RX        AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief I2C_SDA */
#define PIOB_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_11���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_11������Ӧ����
 * @{
 */

#define PIOB_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_12���Ÿ��ù���
 * @{
 */

#define PIOB_12_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_BKIN */
#define PIOB_12_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOB_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_12���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ�*/
#define PIOB_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_12������Ӧ����
 *
 * @{
 */

#define PIOB_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_13���Ÿ��ù���
 * @{
 */

#define PIOB_13_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH1N */
#define PIOB_13_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_13_UART3_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief I2C_SCL */
#define PIOB_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_13������Ӧ����
 * @{
 */

#define PIOB_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_14���Ÿ��ù���
 * @{
 */

#define PIOB_14_TIM1_CH2N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_14_TIM8_CH2N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_14_SPI2_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_14_UART_RTS       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART_RTS */
#define PIOB_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_14������Ӧ����
 * @{
 */

#define PIOB_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_15���Ÿ��ù���
 * @{
 */

#define PIOB_15_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3N */
#define PIOB_15_TIM8_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH3N */
#define PIOB_15_SPI2_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MOSI */
#define PIOB_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOB_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOB_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOB_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOB_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOB_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOB_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOB_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOB_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOB_15������Ӧ����
 * @{
 */

#define PIOB_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz�����Ӧ���� */
#define PIOB_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOB_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_0���Ÿ��ù���
 * @{
 */
#define PIOC_0_I2C1_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOC_0_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_0������Ӧ����
 * @{
 */

#define PIOC_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_1���Ÿ��ù���
 * @{
 */
#define PIOC_1_I2C1_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SDA */
#define PIOC_1_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_13������Ӧ����
 * @{
 */

#define PIOC_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_2���Ÿ��ù���
 * @{
 */
#define PIOC_2_I2C2_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SCL */
#define PIOC_2_SPI2_MISO        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_SCL */
#define PIOC_2_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_2������Ӧ����
 * @{
 */

#define PIOC_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_3���Ÿ��ù���
 * @{
 */
#define PIOC_3_I2C2_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SDA */
#define PIOC_3_SPI2_MOSI        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_3_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_3������Ӧ����
 * @{
 */

#define PIOC_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_4���Ÿ��ù���
 * @{
 */
#define PIOC_4_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_4���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_4������Ӧ����
 * @{
 */

#define PIOC_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/** @} */

/******************************************************************************/


/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */
#define PIOC_5_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_6���Ÿ��ù���
 * @{
 */

#define PIOC_6_TIM3_CH1         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_6_TIM8_CH1         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_6_I2C1_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_6_UART6_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOC_6_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */

#define PIOC_7_TIM3_CH2         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_7_TIM8_CH2         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_7_I2C1_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_7_UART6_RX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_RX */
#define PIOC_7_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */
#define PIOC_8_TIM3_CH3         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOC_8_TIM8_CH3         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH3 */
#define PIOC_8_I2C2_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOC_8_SDIO_D0          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D0 */
#define PIOC_8_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_9���Ÿ��ù���
 * @{
 */

#define PIOC_9_MCO2             AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief MCO2 */
#define PIOC_9_TIM3_CH4         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_9_TIM8_CH4         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_9_I2C2_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_9_SDIO_D1          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D1 */
#define PIOC_9_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_9������Ӧ����
 * @{
 */

#define PIOC_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_10���Ÿ��ù���
 * @{
 */

#define PIOC_10_SPI3_SCK         AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_SCK */
#define PIOC_10_UART3_TX         AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX */
#define PIOC_10_UART4_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_TX */
#define PIOC_10_SDIO_D2          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D2 */
#define PIOC_10_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */

#define PIOC_11_SPI3_MISO        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_11_UART3_RX         AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief UART3_RT */
#define PIOC_11_UART4_RX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_RX */
#define PIOC_11_SDIO_D3          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D3 */
#define PIOC_11_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5���Ÿ��ù���
 * @{
 */

#define PIOC_12_SPI3_MOSI        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_12_UART5_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_TX */
#define PIOC_12_SDIO_CK          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_CK */
#define PIOC_12_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_5������Ӧ����
 * @{
 */

#define PIOC_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_13���Ÿ��ù���
 * @{
 */
#define PIOC_13_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_13������Ӧ����
 * @{
 */

#define PIOC_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_14���Ÿ��ù���
 * @{
 */
#define PIOC_14_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_14���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_14������Ӧ����
 * @{
 */

#define PIOC_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_15���Ÿ��ù���
 * @{
 */
#define PIOC_15_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOC_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOC_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOC_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOC_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOC_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOC_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOC_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOC_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOC_15������Ӧ����
 * @{
 */

#define PIOC_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOC_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOC_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_0���Ÿ��ù���
 * @{
 */
#define PIOD_0_UART8_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_TX */
#define PIOD_0_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_RX */
#define PIOD_0_FMC_DA         AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief CAN1_RX */
#define PIOD_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_0������Ӧ����
 * @{
 */

#define PIOD_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_1���Ÿ��ù���
 * @{
 */

#define PIOD_1_UART8_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_RX */
#define PIOD_1_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOD_1_FMC_DA3        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA3 */
#define PIOD_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_1������Ӧ����
 * @{
 */

#define PIOD_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_2���Ÿ��ù���
 * @{
 */

#define PIOD_2_TIM3_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_ETR */
#define PIOD_2_UART5_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_RX */
#define PIOD_2_SDIO_CMD       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_CMD */
#define PIOD_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_2���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_2������Ӧ����
 * @{
 */

#define PIOD_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_3_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_3_UART2_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_3_FMC_CLK        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_CLK */
#define PIOD_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_4_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_4_UART2_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_4_FMC_NOE        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NOE */
#define PIOD_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_5_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_5_UART2_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_5_FMC_NWE        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NWE */
#define PIOD_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_6_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_6_UART2_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_6_FMC_NWAIT      AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NWAIT */
#define PIOD_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_7_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI3_NSS */
#define PIOD_7_FMC_NE1        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NE1 */
#define PIOD_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_8_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX*/
#define PIOD_8_FMC_DA13       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA13 */
#define PIOD_8_UART3_RX       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief UART3_RX */
#define PIOD_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_9���Ÿ��ù���
 * @{
 */

#define PIOD_9_UART3_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_RX */
#define PIOD_9_FMC_DA14       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA14 */
#define PIOD_9_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief UART3_TX */
#define PIOD_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_9���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_9������Ӧ����
 * @{
 */

#define PIOD_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_10���Ÿ��ù���
 * @{
 */

#define PIOD_10_FMC_DA15       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA15 */
#define PIOD_10_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief I2C1_SCL */
#define PIOD_10_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief I2C1_SDA */
#define PIOD_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_11_UART3_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_CTS */
#define PIOD_11_FMC_A16        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A16 */
#define PIOD_11_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief I2C1_SDA */
#define PIOD_11_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief I2C1_SCL */
#define PIOD_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_11������Ӧ����
 * @{
 */

#define PIOD_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_12���Ÿ��ù���
 * @{
 */

#define PIOD_12_TIM4_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1 */
#define PIOD_12_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI2_SCK */
#define PIOD_12_UART3_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_RTS */
#define PIOD_12_FMC_A17        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_12_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_NSS */
#define PIOD_12_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_MOSI */
#define PIOD_12_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_MISO */
#define PIOD_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_13_TIM4_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1 */
#define PIOD_13_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI2_SCK */
#define PIOD_13_FMC_A18        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_13_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_SCK */
#define PIOD_13_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_NSS */
#define PIOD_13_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_MOSI */
#define PIOD_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3���Ÿ��ù���
 * @{
 */

#define PIOD_14_TIM4_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH3 */
#define PIOD_14_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_SCK */
#define PIOD_14_FMC_DA0        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_14_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_MISO */
#define PIOD_14_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_SCK */
#define PIOD_14_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_NSS */
#define PIOD_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOD_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_15���Ÿ��ù���
 * @{
 */

#define PIOD_15_TIM4_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH4 */
#define PIOD_15_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_NSS */
#define PIOD_15_FMC_DA1        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA1 */
#define PIOD_15_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_MOSI */
#define PIOD_15_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_MISO */
#define PIOD_15_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_SCK */
#define PIOD_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_15���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOD_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOD_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOD_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOD_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOD_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOD_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOD_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOD_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_15������Ӧ����
 * @{
 */

#define PIOD_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOD_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOD_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_0_TIM4_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_ETR */
#define PIOE_0_UART8_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_RX */
#define PIOE_0_FMC_NBL0       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NBL0 */
#define PIOE_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOE_0������Ӧ����
 * @{
 */

#define PIOE_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_1���Ÿ��ù���
 * @{
 */
#define PIOE_1_UART8_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_TX */
#define PIOE_1_FMC_NBL1       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NBL1 */
#define PIOE_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_1���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOE_1������Ӧ����
 * @{
 */

#define PIOE_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_2���Ÿ��ù���
 * @{
 */

#define PIOE_2_TRACECLK       AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACECLK */
#define PIOE_2_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOE_2_FMC_A23        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A23 */
#define PIOE_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_3_TRACED0        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED0 */
#define PIOE_3_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_3_FMC_A19         AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A19 */
#define PIOE_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_4���Ÿ��ù���
 * @{
 */

#define PIOE_4_TRACED1        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TRACED1 */
#define PIOE_4_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_4_FMC_A20        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A20 */
#define PIOE_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_5_TRACED2        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED1 */
#define PIOE_5_I2C2_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SCL */
#define PIOE_5_SPI2_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MISO */
#define PIOE_5_FMC_A21        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A21 */
#define PIOE_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_6_TRACED3        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED3 */
#define PIOE_6_I2C2_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SDA */
#define PIOE_6_SPI2_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MOSI */
#define PIOE_6_FMC_A22        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A22 */
#define PIOE_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_7_TIM1_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM4_CH4 */
#define PIOE_7_UART7_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_RX */
#define PIOE_7_FMC_DA4        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA4 */
#define PIOE_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_8_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1N */
#define PIOE_8_UART7_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_TX */
#define PIOE_8_FMC_DA5        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA5 */
#define PIOE_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_9_TIM1_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1 */
#define PIOE_9_FMC_DA6        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA6 */
#define PIOE_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_10_FMC_DA7        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA7 */
#define PIOE_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_11_TIM1_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2 */
#define PIOE_11_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_NSS */
#define PIOE_11_FMC_DA8        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA8 */
#define PIOE_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_12_TIM1_CH3N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3N */
#define PIOE_12_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOE_12_FMC_DA9        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA9 */
#define PIOE_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_13_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3 */
#define PIOE_13_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_13_FMC_DA10       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA10 */
#define PIOE_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_14_TIM1_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH4 */
#define PIOE_14_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOE_14_FMC_DA11       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA11 */
#define PIOE_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0���Ÿ��ù���
 * @{
 */

#define PIOE_15_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_BKIN */
#define PIOE_15_FMC_DA12       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA12 */
#define PIOE_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0���Ÿ���ʱ����ģʽ
 * @{
 */

#define PIOE_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief ģ��ģʽ */
#define PIOE_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief ���븡��ģʽ��Ĭ�ϣ� */
#define PIOE_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief ��������ģʽ */
#define PIOE_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief ��������ģʽ */
#define PIOE_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief ͨ���������ģʽ */
#define PIOE_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief ͨ�ÿ�©���ģʽ */
#define PIOE_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief �����������ģʽ */
#define PIOE_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief ���ÿ�©���ģʽ */

/** @} */

/**
 * \name PIOD_3������Ӧ����
 * @{
 */

#define PIOE_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz�����Ӧ���� */
#define PIOE_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz�����Ӧ���� */
#define PIOE_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz�����Ӧ���� */

/** @} */

/******************************************************************************/

/**
 * @}
 */

/**
 * @}if_zmf159_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_PIN_H */

/* end of file */
