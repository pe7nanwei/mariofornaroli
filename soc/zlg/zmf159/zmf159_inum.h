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
 * \brief ZMF159 �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-21  ipk, first implementation
 * \endinternal
 */

#ifndef __ZMF159_INUM_H
#define __ZMF159_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \addtogroup zmf159_if_inum
 * \copydoc zmf159_inum.h
 * @{
 */

/**
 * \name ZMF159 CPU �жϺ�
 * @{
 */

#define INUM_WWDG_IWDG            0    /**< \brief ���Ź��ж� */
#define INUM_PVD                  1    /**< \brief ��Դ��ѹ����ж� */
#define INUM_TAMPER               2    /**< \brief �������ж� */
#define INUM_RTC                  3    /**< \brief ʵʱʱ�ӣ�RTC��ȫ���ж� */
#define INUM_FLASH                4    /**< \brief ����ȫ���ж� */
#define INUM_RCC                  5    /**< \brief ��λ��ʱ�ӿ��ƣ�RCC���ж� */

#define INUM_EXTI0                6    /**< \brief EXTI��0�ж� */
#define INUM_EXTI1                7    /**< \brief EXTI��1�ж� */
#define INUM_EXTI2                8    /**< \brief EXTI��2�ж� */
#define INUM_EXTI3                9    /**< \brief EXTI��3�ж� */
#define INUM_EXTI4                10   /**< \brief EXTI��4�ж� */

#define INUM_DMA1_1               11   /**< \brief DMA1ͨ��1ȫ���ж� */
#define INUM_DMA1_2               12   /**< \brief DMA1ͨ��2ȫ���ж� */
#define INUM_DMA1_3               13   /**< \brief DMA1ͨ��3ȫ���ж� */
#define INUM_DMA1_4               14   /**< \brief DMA1ͨ��4ȫ���ж� */
#define INUM_DMA1_5               15   /**< \brief DMA1ͨ��5ȫ���ж� */
#define INUM_DMA1_6               16   /**< \brief DMA1ͨ��6ȫ���ж� */
#define INUM_DMA1_7               17   /**< \brief DMA1ͨ��7ȫ���ж� */

#define INUM_ADC1_2               18   /**< \brief ADC1��ADC2��ȫ���ж� */
#define INUM_FlASH_CACHE          19   /**< \brief FlashCache�ж� */

#define INUM_CAN_RX1              21   /**< \brief CAN����1�ж� */

#define INUM_EXTI9_5              23   /**< \brief EXTI��[9��5]�ж� */
#define INUM_TIM1_BRK             24   /**< \brief TIM1ɲ���ж� */
#define INUM_TIM1_UP              25   /**< \brief TIM1�����ж� */
#define INUM_TIM1_TRG_COM         26   /**< \brief TIM1������ͨ���ж� */
#define INUM_TIM1_CC              27   /**< \brief TIM1����Ƚ��ж� */
#define INUM_TIM2                 28   /**< \brief TIM2ȫ���ж� */
#define INUM_TIM3                 29   /**< \brief TIM3ȫ���ж� */
#define INUM_TIM4                 30   /**< \brief TIM14ȫ���ж� */

#define INUM_I2C1_EV              31   /**< \brief I2C1�¼��ж� */

#define INUM_I2C2_EV              33   /**< \brief I2C2�¼��ж� */

#define INUM_SPI1                 35   /**< \brief SPI1ȫ���ж� */
#define INUM_SPI2                 36   /**< \brief SPI2ȫ���ж� */

#define INUM_UART1                37   /**< \brief UART1ȫ���ж� */
#define INUM_UART2                38   /**< \brief UART2ȫ���ж� */
#define INUM_UART3                39   /**< \brief UART3ȫ���ж� */

#define INUM_EXTI15_10            40   /**< \brief EXTI��[15��10]�ж� */
#define INUM_RTC_ALARM            41   /**< \brief ����EXTI17��RTC�����ж� */
#define INUM_USB_WK               42   /**< \brief ����EXTI18�Ĵ�USB���������ж� */

#define INUM_TIM8_BRK             43   /**< \brief TIM8ɲ���ж� */
#define INUM_TIM8_UP              44   /**< \brief TIM8�����ж� */
#define INUM_TIM8_TRG_COM         45   /**< \brief TIM8 �����������ж� */
#define INUM_TIM8_CC              46   /**< \brief TIM8����Ƚ��ж� */

#define INUM_SDIO                 49   /**< \brief SDIOȫ���ж� */
#define INUM_TIM5                 50   /**< \brief TIM5ȫ���ж� */
#define INUM_SPI3                 51   /**< \brief SPI3ȫ���ж� */
#define INUM_UART4                52   /**< \brief UART4ȫ���ж� */
#define INUM_UART5                53   /**< \brief UART5ȫ���ж� */
#define INUM_TIM6                 54   /**< \brief TIM6ȫ���ж� */
#define INUM_TIM7                 55   /**< \brief TIM7ȫ���ж� */
#define INUM_DMA2_1               56   /**< \brief DMA2ͨ��1ȫ���ж� */
#define INUM_DMA2_2               57   /**< \brief DMA2ͨ��2ȫ���ж� */
#define INUM_DMA2_3               58   /**< \brief DMA2ͨ��3ȫ���ж� */
#define INUM_DMA2_4               59   /**< \brief DMA2ͨ��4ȫ���ж� */
#define INUM_DMA2_5               60   /**< \brief DMA2ͨ��5ȫ���ж� */

#define INUM_COMP1_2              64   /**< \brief ����EXTI�ıȽ���1/2�ж� */

#define INUM_USB_FS               67   /**< \brief USB_FSȫ���ж� */

#define INUM_UART6                71   /**< \brief UART6ȫ���ж� */

#define INUM_UART7                82   /**< \brief UART7ȫ���ж� */
#define INUM_UART8                83   /**< \brief UART8ȫ���ж� */

/** @} */

/**
 * \brief ����жϺ�Ϊ�� INUM_UART6
 */
#define INUM_INTERNAL_MAX        INUM_UART6

/** \brief ��С�жϺ�: INUM_WWDT */
#define INUM_INTERNAL_MIN        INUM_WWDG_IWDG

/**
 * \brief ���ж���Ϊ��(INUM_INTERNAL_MAX - INUM_INTERNAL_MIN + 1),
 *
 */
#define INUM_INTERNAL_COUNT     (INUM_INTERNAL_MAX - INUM_INTERNAL_MIN + 1)


/**
 * \cond
 * �жϺŶ��壬Ϊ core_cm3.h�ļ�����
 */
typedef enum {

    /* ----------------------  Cortex-M3���쳣��  ------------------- */

    /** \brief 2  ���������ж�, ���ܱ�ֹͣ����ռ */
    NonMaskableInt_IRQn      = -14,

    /** \brief 3  Ӳ�������ж� */
    HardFault_IRQn           = -13,

    /** \brief 11  ϵͳ�������ͨ��SVCָ�� */
    SVCall_IRQn              =  -5,

    /** \brief 14  ϵͳ�Ĺ������� */
    PendSV_IRQn              =  -2,

    /** \brief 15  ϵͳ�δ�ʱ�� */
    SysTick_IRQn             =  -1,

    /******  ZMF159 Specific Interrupt Numbers *******************************************************/
    WWDG_IWDG_IRQn            =0,         /**< \brief ���Ź���ʱ���ж� */
    PVD_IRQn                  =1,         /**< \brief ��Դ��ѹ����ж� */
    TAMPER_IRQn               =2,         /**< \brief �������ж� */
    RTC_IRQn                  =3,         /**< \brief ʵʱʱ�ӣ�RTC��ȫ���ж� */
    FLASH_IRQn                =4,         /**< \brief ����ȫ���ж� */
    RCC_IRQn                  =5,         /**< \brief ��λ��ʱ�ӿ��ƣ�RCC���ж� */
    EXTI0_IRQn                =6,         /**< \brief EXTI��0�ж� */
    EXTI1_IRQn                =7,         /**< \brief EXTI��1�ж� */
    EXTI2_IRQn                =8,         /**< \brief EXTI��2�ж� */
    EXTI3_IRQn                =9,         /**< \brief EXTI��3�ж� */
    EXTI4_IRQn                =10,        /**< \brief EXTI��4�ж� */
    DMA1_1_IRQn               =11,        /**< \brief DMA1ͨ��1ȫ���ж� */
    DMA1_2_IRQn               =12,        /**< \brief DMA1ͨ��2ȫ���ж� */
    DMA1_3_IRQn               =13,        /**< \brief DMA1ͨ��3ȫ���ж� */
    DMA1_4_IRQn               =14,        /**< \brief DMA1ͨ��4ȫ���ж� */
    DMA1_5_IRQn               =15,        /**< \brief DMA1ͨ��5ȫ���ж� */
    DMA1_6_IRQn               =16,        /**< \brief DMA1ͨ��6ȫ���ж� */
    DMA1_7_IRQn               =17,        /**< \brief DMA1ͨ��7ȫ���ж� */
    ADC1_2_IRQn               =18,        /**< \brief ADC1��ȫ���ж� */
    FlASH_CACHE_IRQn          =19,        /**< \brief FlASH_CACHE�ж� */
    Reserved0                 =20,        /**< \brief RESERVED */
    CAN_RX1_IRQn              =21,        /**< \brief CAN����1�ж� */
    Reserved1                 =22,        /**< \brief RESERVED */
    EXTI9_5_IRQn              =23,        /**< \brief EXTI��[9��5]�ж� */
    TIM1_BRK_IRQn             =24,        /**< \brief TIM1�Ͽ��ж� */
    TIM1_UP_IRQn              =25,        /**< \brief TIM1�����ж� */
    TIM1_TRG_COM_IRQn         =26,        /**< \brief TIM1������ͨ���ж� */
    TIM1_CC_IRQn              =27,        /**< \brief TIM1����Ƚ��ж� */
    TIM2_IRQn                 =28,        /**< \brief TIM2ȫ���ж� */
    TIM3_IRQn                 =29,        /**< \brief TIM3ȫ���ж� */
    TIM4_IRQn                 =30,        /**< \brief TIM14ȫ���ж� */
    I2C1_EV_IRQn              =31,        /**< \brief I2C1�¼��ж� */
    Reserved2                 =32,        /**< \brief RESERVED */
    I2C2_EV_IRQn              =33,        /**< \brief I2C1�¼��ж� */
    Reserved3                 =34,        /**< \brief RESERVED */
    SPI1_IRQn                 =35,        /**< \brief SPI1ȫ���ж� */
    SPI2_IRQn                 =36,        /**< \brief SPI2ȫ���ж� */
    UART1_IRQn                =37,        /**< \brief UART1ȫ���ж� */
    UART2_IRQn                =38,        /**< \brief UART2ȫ���ж� */
    UART3_IRQn                =39,        /**< \brief UART3ȫ���ж� */
    EXTI15_10_IRQn            =40,        /**< \brief EXTI��[15��10]�ж� */
    RTCAlarm_IRQn             =41,        /**< \brief ����EXTI17��RTC�����ж� */
    USB_WK_IRQn               =42,        /**< \brief ����EXTI18�Ĵ�USB���������ж� */
    TIM8_BRK_IRQn             =43,        /**< \brief TIM8ɲ���ж� */
    TIM8_UP_IRQn              =44,        /**< \brief TIM8�����ж� */
    TIM8_TRG_COM_IRQn         =45,        /**< \brief TIM8 �����������ж� */
    TIM8_CC_IRQn              =46,        /**< \brief TIM8����Ƚ��ж� */
    Reserved4                 =47,        /**< \brief RESERVED */
    Reserved5                 =48,        /**< \brief RESERVED */
    SDIO_IRQn                 =49,        /**< \brief SDIOȫ���ж� */
    TIM5_IRQn                 =50,        /**< \brief TIM5ȫ���ж� */
    SPI3_IRQn                 =51,        /**< \brief SPI3ȫ���ж� */
    UART4_IRQn                =52,        /**< \brief UART4ȫ���ж� */
    UART5_IRQn                =53,        /**< \brief UART5ȫ���ж� */
    TIM6_IRQn                 =54,        /**< \brief TIM6ȫ���ж� */
    TIM7_IRQn                 =55,        /**< \brief TIM7ȫ���ж� */
    DMA2_CH1_IRQn             =56,        /**< \brief DMAͨ��1ȫ���ж� */
    DMA2_CH2_IRQn             =57,        /**< \brief DMAͨ��2ȫ���ж� */
    DMA2_CH3_IRQn             =58,        /**< \brief DMAͨ��3ȫ���ж� */
    DMA2_CH4_IRQn             =59,        /**< \brief DMAͨ��4ȫ���ж� */
    DMA2_CH5_IRQn             =60,        /**< \brief DMAͨ��5ȫ���ж� */
    Reserved6                 =61,        /**< \brief RESERVED */
    Reserved7                 =62,        /**< \brief RESERVED */
    Reserved8                 =63,        /**< \brief RESERVED */
    COMP1_2_IRQn              =64,        /**< \brief ����EXTI�ıȽ���1/2�ж� */
    Reserved9                 =65,        /**< \brief RESERVED */
    Reserved10                =66,        /**< \brief RESERVED */
    USB_FS_IRQn               =67,        /**< \brief USB_FSȫ���ж� */
    Reserved11                =68,        /**< \brief RESERVED */
    Reserved12                =69,        /**< \brief RESERVED */
    Reserved13                =70,        /**< \brief RESERVED */
    UART6_IRQn                =71,        /**< \brief UART6ȫ���ж� */
    Reserved14                =72,        /**< \brief RESERVED */
    Reserved15                =73,        /**< \brief RESERVED */
    Reserved16                =74,        /**< \brief RESERVED */
    Reserved17                =75,        /**< \brief RESERVED */
    Reserved18                =76,        /**< \brief RESERVED */
    Reserved19                =77,        /**< \brief RESERVED */
    Reserved20                =78,        /**< \brief RESERVED */
    Reserved21                =79,        /**< \brief RESERVED */
    Reserved22                =80,        /**< \brief RESERVED */
    Reserved23                =81,        /**< \brief RESERVED */
    UART7_IRQn                =82,        /**< \brief UART7ȫ���ж� */
    UART8_IRQn                =83         /**< \brief UART8ȫ���ж� */

} IRQn_Type;

/**
 * \endcond
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_INUM_H */

/* end of file */
