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
 * \brief LPC84X ����ӳ��
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-07  cyl, first implementation.
 * \endinternal
 */
 
#ifndef __LPC84X_PERIPH_MAP_H
#define __LPC84X_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {    
#endif 

#include "lpc84x_regbase.h"

#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc_mrt.h"
#include "hw/amhw_lpc_sct.h"
#include "hw/amhw_lpc_spi.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc_wkt.h"

#include "hw/amhw_lpc84x_adc.h"
#include "hw/amhw_lpc84x_dma.h"
#include "hw/amhw_lpc84x_gpio.h"
#include "hw/amhw_lpc84x_inmux.h"
#include "hw/amhw_lpc84x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc84x_swm.h"
#include "hw/amhw_lpc82x_acmp.h"

/** 
 * \addtogroup lpc82x_if_periph_map
 * \copydoc lpc82x_periph_map.h
 * @{
 */

/**
 * \name ���趨��
 * @{
 */

/** \brief  ϵͳ�δ�ʱ��(SYSTICK)�Ĵ�����ָ��   */
#define LPC84X_SYSTICK     ((amhw_arm_systick_t    *)LPC84X_SYSTICK_BASE)
                                                        
/** \brief  IO����(IOCON)�Ĵ�����ָ��           */                               
#define LPC84X_IOCON       ((amhw_lpc84x_iocon_t   *)LPC84X_IOCON_BASE  )
                                                        
/** \brief  ͨ���������(GPIO)�Ĵ�����ָ��      */                               
#define LPC84X_GPIO        ((amhw_lpc84x_gpio_t    *)LPC84X_GPIO_BASE   )
                                                        
/** \brief  �����ж�(PINT)�Ĵ�����ָ��          */                               
#define LPC84X_PINT        ((amhw_lpc82x_pint_t    *)LPC84X_PINT_BASE   )
                                                        
/** \brief  ���ؾ���(SWM)�Ĵ�����ָ��           */
#define LPC84X_SWM         ((amhw_lpc84x_swm_t     *)LPC84X_SWM_BASE    )
                                                        
/** \brief  ���븴�ÿ���(INMUX)�Ĵ�����ָ��     */                               
#define LPC84X_INMUX       ((amhw_lpc82x_inmux_t   *)LPC84X_INMUX_BASE  )
                                                        
/** \brief  DMA������(DMA)�Ĵ�����ָ��          */                               
#define LPC84X_DMA         ((amhw_lpc82x_dma_t     *)LPC84X_DMA_BASE    )
                                                        
/** \brief  ��Ƶ�ʶ�ʱ��(MRT)�Ĵ�����ָ��       */                               
#define LPC84X_MRT         ((amhw_lpc_mrt_t     *)LPC84X_MRT_BASE       )
                                                        
/** \brief ״̬�����ö�ʱ��(SCT0)�Ĵ�����ָ��   */                              
#define LPC84X_SCT0        ((amhw_lpc_sct_t     *)LPC84X_SCT0_BASE      )

/** \brief ϵͳ����(SYSCON)�Ĵ�����ָ��         */
#define LPC84X_SYSCON      ((amhw_lpc84x_syscon_t  *)LPC84X_SYSCON_BASE )
                                                        
/** \brief ��������ӿ�(SPI0)�Ĵ�����ָ��       */                               
#define LPC84X_SPI0        ((amhw_lpc_spi_t     *)LPC84X_SPI0_BASE   )
                                                                               
/** \brief ��������ӿ�(SPI1)�Ĵ�����ָ��       */                                                      
#define LPC84X_SPI1        ((amhw_lpc_spi_t     *)LPC84X_SPI1_BASE   )
                                                        
/** \brief I2C���߿�����(I2C0)�Ĵ�����ָ��      */                               
#define LPC84X_I2C0        ((amhw_lpc_i2c_t     *)LPC84X_I2C0_BASE   )
                                                                             
/** \brief I2C���߿�����(I2C1)�Ĵ�����ָ��      */                                                    
#define LPC84X_I2C1        ((amhw_lpc_i2c_t     *)LPC84X_I2C1_BASE   )
                                                                             
/** \brief I2C���߿�����(I2C2)�Ĵ�����ָ��      */                                                    
#define LPC84X_I2C2        ((amhw_lpc_i2c_t     *)LPC84X_I2C2_BASE   )
                                                        
/** \brief I2C���߿�����(I2C3)�Ĵ�����ָ��      */                                                      
#define LPC84X_I2C3        ((amhw_lpc_i2c_t     *)LPC84X_I2C3_BASE   )
   
/** \brief ����(UART0)�Ĵ�����ָ��              */
#define LPC84X_USART0      ((amhw_lpc_usart_t   *)LPC84X_USART0_BASE )
                                                        
/** \brief ����(UART1)�Ĵ�����ָ��              */                               
#define LPC84X_USART1      ((amhw_lpc_usart_t   *)LPC84X_USART1_BASE )
                                                        
/** \brief ����(UART2)�Ĵ�����ָ��              */                               
#define LPC84X_USART2      ((amhw_lpc_usart_t   *)LPC84X_USART2_BASE )
                                                      
/** \brief ѭ������У��(CRC)�Ĵ�����ָ��        */                             
#define LPC84X_CRC         ((amhw_lpc_crc_t     *)LPC84X_CRC_BASE    )
                                                        
/** \brief �Ի��Ѷ�ʱ��(WKT)�Ĵ�����ָ��        */                               
#define LPC84X_WKT         ((amhw_lpc_wkt_t     *)LPC84X_WKT_BASE    )
                                                        
/** \brief ��Դ����Ԫ(PMU)�Ĵ�����ָ��        */                               
#define LPC84X_PMU         ((amhw_lpc82x_pmu_t  *)LPC84X_PMU_BASE    )

/** \brief FLASH������(FMC)�Ĵ�����ָ��         */                              
#define LPC84X_FMC         ((amhw_lpc_fmc_t     *)LPC84X_FMC_BASE    )
  
/** \brief ģ��ת��(ADC)�Ĵ�����ָ��            */                              
#define LPC84X_ADC0        ((amhw_lpc84x_adc_t  *)LPC84X_ADC0_BASE   )

/** \brief ģ��Ƚ���(ACMP)�Ĵ�����ָ��         */                     
#define LPC84X_ACMP        ((amhw_lpc82x_acmp_t *)LPC84X_ACMP_BASE   )

/** \brief ���ڿ��Ź�(WWDT)�Ĵ�����ָ��         */
#define LPC84X_WWDT        ((amhw_lpc_wwdt_t    *)LPC84X_WWDT_BASE   )

/** \brief ���ڿ��Ź�(WWDT)�Ĵ�����ָ��         */
#define LPC84X_DAC0        ((amhw_lpc_dac_t     *)LPC84X_DAC0_BASE   )

/** \brief ���ڿ��Ź�(WWDT)�Ĵ�����ָ��         */
#define LPC84X_DAC1        ((amhw_fsl_dac_t     *)LPC84X_DAC1_BASE   )


/** @} */

/**
 * @} lpc82x_if_periph_map
 */
    
#ifdef __cplusplus
}
#endif

#endif /* LPC84X_REG_BASE_H */

/* end of file */
