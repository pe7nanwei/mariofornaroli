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
 * \brief LPC82X ����ʵ����ʼ����������
 *
 * ���������豸��I2C��SPI��ADC...����ʵ����ʼ���������ڱ�ͷ�ļ���������ʹ��ʵ��
 * ��ʼ���������������ɻ��һ������ľ����Ȼ��ʹ����صĽӿں�����������в���
 *
 * \sa am_lpc84x_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 15-12-11  tee, first implementation
 * \endinternal
 */

#ifndef __AM_LPC82X_INST_INIT_H
#define __AM_LPC82X_INST_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_adc.h"
#include "am_crc.h"
#include "am_i2c.h"
#include "am_cap.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_uart.h"
#include "am_timer.h"
#include "am_dac.h"
#include "am_ep24cxx.h"
#include "am_lpc_sct.h"
#include "am_hwconf_lm75.h"
#include "am_hwconf_led_gpio.h"
#include "am_hwconf_key_gpio.h"
#include "am_hwconf_buzzer_pwm.h"
#include "am_hwconf_debug_uart.h"
#include "am_hwconf_system_tick_softimer.h"

/**
 * \addtogroup am_if_lpc84x_inst_init
 * \copydoc am_lpc84x_inst_init.h
 * @{
 */

/**
 * \brief ADC0 (DMA ��ʽ) ʵ����ʼ������� ADC ��׼������
 *
 * \param ��
 *
 * \return ADC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_lpc84x_adc0_dma_inst_init (void);

/**
 * \brief ADC0 (DMA ��ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_adc0_dma_inst_init() ������õ� ADC ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_adc0_dma_inst_deinit (am_adc_handle_t handle);

/**
 * \brief ADC0 (�жϷ�ʽ) ʵ����ʼ������� ADC ��׼������
 *
 * \param ��
 *
 * \return ADC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_adc_handle_t am_lpc84x_adc0_int_inst_init (void);

/**
 * \brief ADC0 (�жϷ�ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_adc0_int_inst_init() ������õ� ADC ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_adc0_int_inst_deinit (am_adc_handle_t handle);

/**
 * \brief CLK ʵ����ʼ������ʼ��ϵͳʱ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_lpc84x_clk_inst_init (void);

/**
 * \brief CRC ʵ����ʼ������� CRC ��׼������
 *
 * \param ��
 *
 * \return CRC ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_crc_handle_t am_lpc84x_crc_inst_init (void);

/**
 * \brief CRC ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_lpc84x_crc_inst_deinit (void);

/**
 * \brief DMA ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_lpc84x_dma_inst_init (void);

/**
 * \brief DMA ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_lpc84x_dma_inst_deinit (void);

/**
 * \brief GPIO ʵ����ʼ��
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_lpc84x_gpio_inst_init (void);

/**
 * \brief GPIO ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_lpc84x_gpio_inst_deinit (void);

/**
 * \brief I2C0 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc84x_i2c0_inst_init (void);

/**
 * \brief I2C0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_i2c0_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_lpc84x_i2c0_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C1 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc84x_i2c1_inst_init (void);

/**
 * \brief I2C1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_i2c1_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_lpc84x_i2c1_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C2 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc84x_i2c2_inst_init (void);

/**
 * \brief I2C2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_i2c2_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_lpc84x_i2c2_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C3 ʵ����ʼ������� I2C ��׼������
 *
 * \param ��
 *
 * \return I2C ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_i2c_handle_t am_lpc84x_i2c3_inst_init (void);

/**
 * \brief I2C3 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_i2c3_inst_init() ������õ� I2C ��׼������
 *
 * \return ��
 */
void am_lpc84x_i2c3_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief MRT ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc84x_mrt_inst_init (void);

/**
 * \brief MRT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_mrt_inst_init() ������õ� TIMER ��׼������
 *
 * \return ��
 */
void am_lpc84x_mrt_inst_deinit (am_timer_handle_t handle);

/**
 * \brief SCT0 PWM ʵ����ʼ������� PWM ��׼������
 *
 * \param ��
 *
 * \return PWM ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_pwm_handle_t am_lpc84x_sct0_pwm_inst_init (void);

/**
 * \brief SCT0 PWM ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_sct0_pwm_inst_init() ������õ� PWM ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_sct0_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief SCT0 TIMING ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc84x_sct0_timing_inst_init (void);

/**
 * \brief SCT0 TIMING ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_sct0_timing_inst_init() ������õ� TIMER ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_sct0_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief SCT0 ʵ����ʼ������� SCT ������
 *
 * \param ��
 *
 * \return SCT ����������Ϊ NULL��������ʼ��ʧ��
 */
am_lpc_sct_handle_t am_lpc84x_sct0_inst_init (void);

/**
 * \brief SCT0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_sct0_inst_init() ������õ� SCT ������
 *
 * \return ��
 */
void am_lpc84x_sct0_inst_deinit (am_lpc_sct_handle_t handle);

/**
 * \brief SPI0 (DMA ��ʽ) ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc84x_spi0_dma_inst_init (void);

/**
 * \brief SPI0 (DMA ��ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_spi0_dma_inst_init() ������õ� SPI ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_spi0_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI0 (�жϷ�ʽ) ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc84x_spi0_int_inst_init (void);

/**
 * \brief SPI0 (�жϷ�ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_spi0_int_inst_init() ������õ� SPI ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_spi0_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 (DMA ��ʽ) ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc84x_spi1_dma_inst_init (void);

/**
 * \brief SPI1 (DMA ��ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_spi1_dma_inst_init() ������õ� SPI ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_spi1_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 (�жϷ�ʽ) ʵ����ʼ������� SPI ��׼������
 *
 * \param ��
 *
 * \return SPI ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_spi_handle_t am_lpc84x_spi1_int_inst_init (void);

/**
 * \brief SPI1 (�жϷ�ʽ) ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_spi1_int_inst_init() ������õ� SPI ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_spi1_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief USART0 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc84x_usart0_inst_init (void);

/**
 * \brief USART0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_usart0_inst_init() ������õ� UART ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_usart0_inst_deinit (am_uart_handle_t handle);

/**
 * \brief USART1 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc84x_usart1_inst_init (void);

/**
 * \brief USART1 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_usart1_inst_init() ������õ� UART ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_usart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief USART2 ʵ����ʼ������� UART ��׼������
 *
 * \param ��
 *
 * \return UART ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_uart_handle_t am_lpc84x_usart2_inst_init (void);

/**
 * \brief USART2 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_usart2_inst_init() ������õ� UART ��׼
 *                   ������
 *
 * \return ��
 */
void am_lpc84x_usart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief WKT ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_lpc84x_wkt_inst_init (void);

/**
 * \brief WKT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_wkt_inst_init() ������õ� TIMER ��׼������
 *
 * \return ��
 */
void am_lpc84x_wkt_inst_deinit (am_timer_handle_t handle);

/**
 * \brief WWDT ʵ����ʼ������� WDT ��׼������
 *
 * \param ��
 *
 * \return WDT ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_wdt_handle_t am_lpc84x_wwdt_inst_init (void);

/**
 * \brief WWDT ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_wwdt_inst_init() ������õ� WDT ��׼������
 *
 * \return ��
 */
void am_lpc84x_wwdt_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief �ж�ʵ����ʼ������ʼ���ж�����
 *
 * \param ��
 *
 * \return ���� AW_OK Ϊ��ʼ���ɹ�������Ϊ��ʼ��ʧ��
 */
int am_arm_nvic_inst_init (void);

/**
 * \brief �ж�ʵ�����ʼ��
 *
 * \param ��
 *
 * \return ��
 */
void am_arm_nvic_inst_deinit (void);

/**
 * \brief SYSTICK ʵ����ʼ������� TIMER ��׼������
 *
 * \param ��
 *
 * \return TIMER ��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_timer_handle_t am_arm_systick_inst_init (void);

/**
 * \brief SYSTICK ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_arm_systick_inst_init() ������õ� TIMER ��׼������
 *
 * \return ��
 */
void am_arm_systick_inst_deinit (am_timer_handle_t handle);

/**
 * \brief DAC0 ʵ����ʼ��
 *
 * \return ��
 */
am_dac_handle_t am_lpc84x_dac0_inst_init (void);

/**
 * \brief DAC0 ʵ�����ʼ��
 *
 * \param[in] handle ͨ�� am_lpc84x_dac0_inst_init() ������õ� dac ��׼������
 *
 * \return ��
 */
void am_lpc84x_dac0_inst_deinit (am_dac_handle_t handle);

/**
 * \brief SP0I (��ѯ��ʽ) ʵ����ʼ��
 */
am_spi_handle_t am_lpc84x_spi0_poll_inst_init (void);

/**
 * \brief SPI0 (��ѯ��ʽ) ʵ�����ʼ��
 */
void am_lpc84x_spi0_poll_inst_deinit (am_spi_handle_t handle);

/**
 * \brief CAT24C512 EEPROM ʵ����ʼ��
 */
am_ep24cxx_handle_t am_eeprom_cat24c512_inst_init (void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_LPC82X_INST_INIT_H */

/* end of file */
