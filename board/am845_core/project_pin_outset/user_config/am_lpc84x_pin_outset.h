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
 * \brief LPC84x ���ż����ò�������
 * 
 * \note 1. ��ת�ƹ��ܿ�����������I/O���ţ�
 *          GPIO���ܺ����⹦�����ڹ̶����ܣ�ֻ�ܴ����Ӧ������ʹ�� \n
 *          ʾ����PIO0_0���Ź������ã� \n 
 *          - ����ΪGPIO����ʹ�ú꣺      PIO0_0_GPIO \n
 *          - ����Ϊ�Ƚ������빦��ʹ�ú꣺PIO0_0_ACMP_I1 \n
 *          - ���ô��ڷ������Ź���ʹ�ú꣺PIO_FUNC_U0_TXD
 *
 * \note 2. ���ù��ܷ��������������PIOx_x_GPIO_INPUT��PIOx_x_GPIO_OUTPUT
 *          �Ὣ��������Ϊ��ͨIO����������� 
 *
 * \internal
 * \par Modification History
 * - 1.00 19-07-02  YRZ, modified.
 * \endinternal
 */
#ifndef __LPC84X_PIN_OUTSET_H
#define __LPC84X_PIN_OUTSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lpc84x_pin.h"

/** 
 * \name ������������
 * @{
 */  
#define __KEY_KP0_PIN          PIO1_11      /**< \brief �������ſ�ѡ */
/** @} */   
  
/** 
 * \name LED��������
 * @{
 */  
#define __LED0_PIN             PIO1_8       /**< \brief �������ſ�ѡ */
#define __LED1_PIN             PIO1_10      /**< \brief �������ſ�ѡ */  
/** @} */ 
 
/** 
 * \name ADC��������
 * @{
 */
#define __ADC_IN0_PIN          PIO0_7       /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN1_PIN          PIO0_6       /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN2_PIN          PIO0_14      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN3_PIN          PIO0_23      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN4_PIN          PIO0_22      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN5_PIN          PIO0_21      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN6_PIN          PIO0_20      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN7_PIN          PIO0_19      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN8_PIN          PIO0_18      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN9_PIN          PIO0_17      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN10_PIN         PIO0_13      /**< \brief �̶����Ų��ɸ��� */
#define __ADC_IN11_PIN         PIO0_4       /**< \brief �̶����Ų��ɸ��� */
/** @} */
  
/** 
 * \name DAC��������
 * @{
 */
#define __DAC_OUT_PIN          PIO0_17      /**< \brief �̶����Ų��ɸ��� */
/** @} */

/** 
 * \name I2C��������
 * @{
 */
#define __I2C0_SCL_PIN         PIO0_10      /**< \brief �̶����Ų��ɸ��� */
#define __I2C0_SDA_PIN         PIO0_11      /**< \brief �̶����Ų��ɸ��� */
    
#define __I2C1_SCL_PIN         PIO0_18      /**< \brief �������ſ�ѡ */
#define __I2C1_SDA_PIN         PIO0_19      /**< \brief �������ſ�ѡ */
    
#define __I2C2_SCL_PIN         PIO0_9       /**< \brief �������ſ�ѡ */
#define __I2C2_SDA_PIN         PIO0_8       /**< \brief �������ſ�ѡ */
    
#define __I2C3_SCL_PIN         PIO0_6       /**< \brief �������ſ�ѡ */
#define __I2C3_SDA_PIN         PIO0_7       /**< \brief �������ſ�ѡ */
/** @} */

/** 
 * \name SCT CAP��������
 * @{
 */
#define __SCT0_CAP_PIN0        PIO0_25      /**< \brief �������ſ�ѡ */
#define __SCT0_CAP_PIN1        PIO0_26      /**< \brief �������ſ�ѡ */
#define __SCT0_CAP_PIN2        PIO0_27      /**< \brief �������ſ�ѡ */
#define __SCT0_CAP_PIN3        PIO0_28      /**< \brief �������ſ�ѡ */
/** @} */

/** 
 * \name SCT PWM��������
 * @{
 */
#define __SCT0_OUT0_PIN        PIO0_23      /**< \brief �������ſ�ѡ */
#define __SCT0_OUT1_PIN        PIO0_24      /**< \brief �������ſ�ѡ */
#define __SCT0_OUT2_PIN        PIO0_25      /**< \brief �������ſ�ѡ */
#define __SCT0_OUT3_PIN        PIO0_26      /**< \brief �������ſ�ѡ */
#define __SCT0_OUT4_PIN        PIO0_27      /**< \brief �������ſ�ѡ */
#define __SCT0_OUT5_PIN        PIO0_15      /**< \brief �������ſ�ѡ */
/** @} */

/** 
 * \name SPI0��������
 * @{
 */
#define __SPI0_SCK_PIN         PIO0_17      /**< \brief �������ſ�ѡ */
#define __SPI0_MOSI_PIN        PIO0_18      /**< \brief �������ſ�ѡ */
#define __SPI0_MISO_PIN        PIO0_19      /**< \brief �������ſ�ѡ */
/** @} */                                                            
                                                                     
/**                                                                  
 * \name SPI1��������                                                
 * @{                                                                 
 */                                                                  
#define __SPI1_SCK_PIN         PIO0_11      /**< \brief �������ſ�ѡ */
#define __SPI1_MOSI_PIN        PIO0_10      /**< \brief �������ſ�ѡ */
#define __SPI1_MISO_PIN        PIO0_9       /**< \brief �������ſ�ѡ */
/** @} */

/** 
 * \name USART0��������
 * @{
 */
#define __U0_TXD_PIN           PIO1_0       /**< \brief �������ſ�ѡ */
#define __U0_RXD_PIN           PIO1_2       /**< \brief �������ſ�ѡ */
/** @} */                      
                               
/**                            
 * \name USART1��������        
 * @{                          
 */                            
#define __U1_TXD_PIN           PIO0_23       /**< \brief �������ſ�ѡ */
#define __U1_RXD_PIN           PIO0_14       /**< \brief �������ſ�ѡ */
/** @} */                      
                               
/**                            
 * \name USART2��������        
 * @{                          
 */                            
#define __U2_TXD_PIN           PIO0_27      /**< \brief �������ſ�ѡ */
#define __U2_RXD_PIN           PIO0_26      /**< \brief �������ſ�ѡ */
/** @} */       

/**                            
 * \name USART3��������        
 * @{                          
 */                            
#define __U3_TXD_PIN           PIO0_27      /**< \brief �������ſ�ѡ */
#define __U3_RXD_PIN           PIO0_26      /**< \brief �������ſ�ѡ */
/** @} */     

/**                            
 * \name USART4��������        
 * @{                          
 */                            
#define __U4_TXD_PIN           PIO0_27      /**< \brief �������ſ�ѡ */
#define __U4_RXD_PIN           PIO0_26      /**< \brief �������ſ�ѡ */
/** @} */  

#endif /* __LPC82X_PIN_OUTSET_H */

/* end of file */
