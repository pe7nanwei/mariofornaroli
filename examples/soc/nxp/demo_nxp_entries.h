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
 * \brief NXPϵ�������������������̺����������
 * \sa    demo_nxp_entries.h
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-28  adw, first implementation
 * \endinternal
 */
#ifndef __DEMO_NXP_ENTRIES_H
#define __DEMO_NXP_ENTRIES_H

#include "am_clk.h"
#include "am_timer.h"
#include "am_adc.h"
#include "am_lpc_sct.h"
#include "hw/amhw_lpc_wwdt.h"
#include "hw/amhw_lpc_crc.h"
#include "hw/amhw_lpc_i2c.h"
#include "hw/amhw_lpc_sct.h"
#include "hw/amhw_lpc_usart.h"
#include "hw/amhw_lpc_spi.h"
#include "hw/amhw_lpc_wkt.h"
#include "hw/amhw_lpc_mrt.h"
#include "hw/amhw_lpc_fmc.h"

#include "hw/amhw_lpc82x_adc.h"
#include "hw/amhw_lpc82x_acmp.h"
#include "hw/amhw_lpc82x_gpio.h"
#include "hw/amhw_lpc82x_pmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief WWDT Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_wwdt : ָ�� WWDT ����Ĵ������ָ��
 * \param[in] inum      : �жϺ�
 * \param[in] wdt_freq  : WWDTƵ��
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� WWDT ģ����Ӧ��ʱ�ӣ�
 * ���ú��ʵ�WDTʱ��Ƶ�ʡ�
 */
void demo_lpc_hw_wwdt_entry (amhw_lpc_wwdt_t *p_hw_wwdt,
                             int              inum,
                             uint32_t         wdt_freq);
/**
 * \brief acmp Ӳ���㣨ʹ�����жϣ��������
 *
 * \param[in] p_hw_acmp : ָ�� acmp ����Ĵ������ָ��
 * \param[in] flags     : acmp����
 * \param[in] inum      : �жϺ�
 * \param[in] pin       : �Ƚ��������
 *
 * \note һ������£���ʹ�ñ� demo ǰ������� WWDT ģ����Ӧ��ʱ�ӣ�
 * ���ú��ʵ�WDTʱ��Ƶ�ʡ�
 */
void demo_lpc824_hw_acmp_int_entry (amhw_lpc82x_acmp_t *p_hw_acmp, 
                                    uint32_t            flags, 
                                    int                 inum, 
                                    int                 pin);
/**
 * \brief acmp Ӳ���㣨��ѹ���ݣ��������
 *
 * \param[in] p_hw_acmp : ָ�� acmp ����Ĵ������ָ��
 * \param[in] pin       : ����Ƚ�����
 */
void demo_lpc824_hw_acmp_lad_entry (amhw_lpc82x_acmp_t *p_hw_acmp, 
                                    int                 pin);
                             
/**
 * \brief acmp Ӳ���㣨��ѯ���������
 *
 * \param[in] p_hw_acmp : ָ�� acmp ����Ĵ������ָ��
 * \param[in] p_acmp    : ģ��ȽϼĴ�����
 */
void demo_lpc824_hw_acmp_poll_entry (amhw_lpc82x_acmp_t *p_hw_acmp,
                                     int                 pin);
/**
 * \brief adc ��׼adc��dma��ʽ���������
 *
 * \param[in] adc_handle  : adc �Ĵ�����
 * \param[in] chan        : adc ͨ��
 * \param[in] vref_mv     : adc �ο���ѹ
 */
void demo_lpc824_hw_adc_dma_entry (amhw_lpc82x_adc_t *p_hw_adc,
                                   int                ch,
                                   uint32_t           vref_mv);
/**
 * \brief adc ��׼adc��dma��ʽ���������
 *
 * \param[in] adc_handle  : adc �Ĵ�����
 * \param[in] inum        : �жϺ�
 * \param[in] vref_mv     : adc �ο���ѹ
 */
void demo_lpc824_hw_adc_thcmp_entry (amhw_lpc82x_adc_t  *p_hw_adc, 
                                     int                 inum,
                                     uint32_t            vref_mv);
/**
 * \brief acmp ��׼adc��dma int��ʽ���������
 *
 * \param[in] adc_handle  : adc ���
 * \param[in] chan        : adc ͨ��
 * \param[in] rate        : adc ��������
 */
void demo_lpc_std_adc_dma_int_entry (am_adc_handle_t adc_handle,
                                     int             chan,
                                     uint32_t        rate);
/**
 * \brief acmp ��׼adc��dma poll��ʽ���������
 *
 * \param[in] adc_handle  : adc���
 * \param[in] chan        : adc ͨ��
 * \param[in] rate        : adc ��������
 */
void demo_lpc_std_adc_dma_poll_entry (am_adc_handle_t adc_handle,
                                      int             chan,
                                      uint32_t        rate);
/**
 * \brief acmp ��׼adc��int��ʽ���������
 *
 * \param[in] adc_handle  : adc���
 * \param[in] chan        : adc ͨ��
 * \param[in] rate        : adc �������� 
 */
void demo_lpc_std_adc_int_entry (am_adc_handle_t adc_handle,
                                 int             chan,
                                 uint32_t        rate);
/**
 * \brief acmp ��׼adc��poll ��ʽ���������
 *
 * \param[in] adc_handle  : adc���
 * \param[in] ch          : ͨ��
 * \param[in] rate        : ����
 */
void demo_lpc_std_adc_poll_entry (am_adc_handle_t handle, 
                                  int             ch, 
                                  uint32_t        rate);
/**
 * \brief acmp Ӳ���� crc�������
 *
 * \param[in] p_hw_crc  : crc ���
 * \param[in] p_data    : ��������
 * \param[in] rate      : �������ݳ���
 */
void demo_lpc_hw_crc_entry (amhw_lpc_crc_t  *p_hw_crc,
                            am_const char   *p_data, 
                            uint32_t         nbytes);
/**
 * \brief dma Ӳ�������������
 *
 * \param[in] chan : dma ͨ��
 * \param[in] pin  : ��������
 */
void demo_lpc824_drv_dma_hwtrigger_burst_entry (uint8_t  chan,
                                                int      pin);
/**
 * \brief dma �ڴ浽�ڴ��������
 *
 * \param[in] p_src : ��������Դ��ַ
 * \param[in] len   : �������ݵĳ���
 */
void demo_lpc824_drv_dma_m2m_entry (uint8_t *p_src,
                                    int      len);
/**
 * \brief DMA ping-pong �������
 *
 * \param[in] chan  : DMA ͨ��
 * \param[in] p_src : ��������Դ��ַ
 * \param[in] len   : �������ݵĳ���
 */
void demo_lpc824_drv_dma_ping_pong_entry (uint8_t  chan, 
                                          uint8_t *p_src, 
                                          int      len);
/**
 * \brief flash Ӳ�����������
 *
 * \param[in] chan  : DMA ͨ��
 * \param[in] p_src : ��������Դ��ַ
 * \param[in] len   : �������ݵĳ���
 */
void demo_lpc824_hw_flash_ctrl_entry (amhw_lpc_fmc_time_t time);
/**
 * \brief gpio Ӳ�����������
 *
 * \param[in] p_hw_gpio  : GPIO �Ĵ�����ָ��
 * \param[in] pin        : ����
 */
void demo_lpc824_hw_gpio_entry (amhw_lpc82x_gpio_t *p_hw_gpio, 
                                int                 pin);
/**
 * \brief gpio Ӳ�����ж��������
 *
 * \param[in] key_pin  : ��������
 * \param[in] led_pin  : led����
 * \param[in] pint_sel : �ж�ͨ����
 * \param[in] inum     : �жϺ�
 */
void demo_lpc824_hw_gpio_int_entry (int                 key_pin,
                                    int                 led_pin,
                                    int                 pint_sel,
                                    int                 inum);
/**
 * \brief gpio ƥ��ģʽ�������
 *
 * \param[in] pin  : led����
 */
void demo_lpc824_hw_gpio_pmatch_entry (int pin);
/**
 * \brief gpio Ӳ���㣨�������������
 *
 * \param[in] pin  : ��������
 */
void demo_lpc_std_gpio_key_entry (int pin);
/**
 * \brief i2c master Ӳ���㣨dma���������
 *
 * \param[in] p_hw_i2c  : i2c�Ĵ�����
 * \param[in] clkdiv    : ��Ƶ����
 * \param[in] addr      : ������ַ
 * \param[in] sub_addr  : �ӻ���ַ
 */
void demo_lpc824_hw_i2c_master_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                          uint32_t        clkdiv,
                                          uint8_t         addr,
                                          uint8_t         sub_add);
/**
 * \brief i2c master Ӳ���㣨dma���������
 *
 * \param[in] p_hw_i2c  : i2c�Ĵ�����
 * \param[in] clkdiv    : ��Ƶ����
 * \param[in] addr      : ������ַ
 */
void demo_lpc_hw_i2c_master_poll_entey (amhw_lpc_i2c_t *p_hw_i2c,
                                        uint32_t        clkdiv,
                                        uint8_t         addr);
/**
 * \brief i2c master Ӳ���㣨dma���������
 *
 * \param[in] p_hw_i2c : i2c�Ĵ�����
 * \param[in] chan     : dmaͨ����
 */
void demo_lpc824_hw_i2c_slave_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                         uint8_t         chan);
/**
 * \brief i2c slave Ӳ���㣨int���������
 *
 * \param[in] p_hw_i2c  : i2c�Ĵ�����
 * \param[in] inum      : �жϺ�
 */
void demo_lpc_hw_i2c_slave_int_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                      int             inum);
/**
 * \brief i2c slave Ӳ���㣨poll���������
 *
 * \param[in] p_hw_i2c  : i2c�Ĵ�����
 */
void demo_lpc_hw_i2c_slave_poll_entry (amhw_lpc_i2c_t *p_hw_i2c);
/**
 * \brief iap Ӳ�����������
 */
void demo_lpc824_hw_iap_entry (void);
/**
 * \brief i2c master Ӳ���㣨dma���������
 *
 * \param[in] p_hw_mrt  : mrt�Ĵ�����
 * \param[in] inum      : �жϺ�
 */
void demo_lpc824_hw_mrt_entry (amhw_lpc_mrt_t *p_hw_mrt, int inum);
/**
 * \brief pll Ӳ�����������
 */
void demo_lpc824_hw_pll_entry(void);
/**
 * \brief pmu Ӳ���㣨deeppowerdown���������
 *
 * \param[in] p_hw_mrt  : pmu�Ĵ�����
 */
void demo_lpc824_hw_pmu_deeppowerdown_entry (amhw_lpc82x_pmu_t  *p_hw_pmu);
/**
 * \brief pmu Ӳ���㣨deepsleep���������
 *
 * \param[in] p_hw_mrt  : pmu�Ĵ�����
 * \param[in] pin       : ����
 */
void demo_lpc824_hw_pmu_deepsleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin);
/**
 * \brief pmu Ӳ���㣨powerdown���������
 *
 * \param[in] p_hw_mrt  : pmu�Ĵ�����
 * \param[in] pin       : ����
 */
void demo_lpc824_hw_pmu_powerdown_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin);
/**
 * \brief pmu Ӳ���㣨sleep���������
 *
 * \param[in] p_hw_mrt  : pmu�Ĵ�����
 * \param[in] pin       : ����
 */
void demo_lpc824_hw_pmu_sleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                     int                 pin);
/**
 * \brief sct �����㣨pwm���������
 *
 * \param[in] sct_handle  : sct����������
 */
void demo_lpc_drv_sct_timing_pwm_entry (am_lpc_sct_handle_t sct_handle);
/**
 * \brief sct Ӳ���㣨pwm���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] frq       : ϵͳʱ��Ƶ��
 */
void demo_lpc_hw_sct_1_32bit_pwm_entry (amhw_lpc_sct_t *p_hw_sct, 
                                           uint32_t        frq);
/**
 * \brief sct Ӳ���㣨timing_32bit���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] inum      : �жϺ�
 * \param[in] frq       : ϵͳʱ��Ƶ��
 */
void demo_lpc_hw_sct_1_32bit_timing_entry (amhw_lpc_sct_t *p_hw_sct,
                                           int             inum,
                                           uint32_t        frq);
/**
 * \brief sct Ӳ���㣨timing_16bit���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] inum      : �жϺ�
 * \param[in] frq       : ϵͳʱ��Ƶ��
 * \param[in] pin       : ����������
 */
void demo_lpc_hw_sct_2_16bit_timing_entry (amhw_lpc_sct_t *p_hw_sct, 
                                           int             inum,
                                           uint32_t        frq,
                                           int             pin);
/**
 * \brief sct Ӳ���㣨pwm_16bit���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] frq       : ϵͳʱ��Ƶ��
 */
void demo_lpc_hw_sct_2_16bit_pwm_entry(amhw_lpc_sct_t *p_hw_sct,
                                       int             frq);
/**
 * \brief sct Ӳ���㣨pwm_16bit���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] inum      : �жϺ�
 * \param[in] frq       : ϵͳʱ��Ƶ��
 */
void demo_lpc_hw_sct_cap_entry (amhw_lpc_sct_t *p_hw_sct, 
                                int             inum, 
                                uint32_t        frq);
/**
 * \brief sct Ӳ���㣨pwm_16bit���������
 *
 * \param[in] p_hw_sct  : sct�Ĵ�����
 * \param[in] frq       : ϵͳʱ��Ƶ��
 */
void demo_lpc_hw_sct_multi_states_entry(amhw_lpc_sct_t *p_hw_sct,
                                        uint32_t        frq);
/**
 * \brief bod Ӳ���㣨������ԣ��������
 */
void demo_lpc824_hw_bod_entry(void);
/**
 * \brief clk Ӳ���㣨ʱ��Ƶ��������������
 */
void demo_lpc824_hw_clkout_entry (void);
/**
 * \brief usart Ӳ���㣨�Զ������ʣ��������
 *
 * \param[in] p_hw_usart  : usart�Ĵ�����
 * \param[in] u_clk       : ���ڻ�������Ƶ��
 */
void demo_lpc824_hw_usart_autobaud_entry(amhw_lpc_usart_t *p_hw_usart,
                                         uint32_t          u_clk);
/**
 * \brief usart Ӳ���㣨poll���������
 *
 * \param[in] p_hw_usart  : usart�Ĵ�����
 * \param[in] u_clk       : ���ڻ�������Ƶ��
 * \param[in] baudrate    : ������
 */
void demo_lpc_hw_usart_poll_entry(amhw_lpc_usart_t *p_hw_usart,
                                  uint32_t          u_clk,
                                  uint32_t          baudrate);
/**
 * \brief usart Ӳ���㣨rx dma���������
 *
 * \param[in] p_hw_usart  : usart�Ĵ�����
 * \param[in] u_clk       : ���ڻ�������Ƶ��
 * \param[in] baudrate    : ������
 * \param[in] chan        : ����dma����ͨ��
 */
void demo_lpc824_hw_usart_rx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan);
/**
 * \brief usart Ӳ���㣨tx dma���������
 *
 * \param[in] p_hw_usart  : usart�Ĵ�����
 * \param[in] u_clk       : ���ڻ�������Ƶ��
 * \param[in] baudrate    : ������
 * \param[in] chan        : ����dma����ͨ��
 */
void demo_lpc824_hw_usart_tx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan);
/**
 * \brief usart Ӳ���㣨poll���������
 *
 * \param[in] uart_handle  : ������
 */
void demo_lpc_std_usart_flowctrl_entry (am_uart_handle_t  uart_handle);
/**
 * \brief wkt Ӳ���㣨deeppowerdown-wakeup���������
 *
 * \param[in] p_hw_pmu  : pmu�Ĵ�����
 * \param[in] p_hw_wkt  : wkt�Ĵ�����
 * \param[in] inum      : �жϺ�
 * \param[in] delay_inms: ��ʱʱ�䣨���ѣ�
 */
void demo_lpc824_hw_wkt_deeppowerdown_wakeup_entry(amhw_lpc82x_pmu_t *p_hw_pmu,
                                                   amhw_lpc_wkt_t    *p_hw_wkt,
                                                   int                inum,
                                                   uint32_t           delay_inms);
/**
 * \brief wkt Ӳ���㣨deeppowerdown-wakeup���������
 *
 * \param[in] p_hw_wkt   : wkt�Ĵ�����
 * \param[in] wkt_mdelay : ��ʱʱ��
 */
void demo_lpc_hw_wkt_timer(amhw_lpc_wkt_t *p_hw_wkt,
                           uint32_t        wkt_mdelay);
/**
 * \brief wkt ��׼�㣨timer���������
 *
 * \param[in] timer_handle   : �������
 * \param[in] chan           : ͨ��
 * \param[in] clkin          : ��ʱ��ʱ��
 */
void demo_lpc_std_wkt_timer_entry (am_timer_handle_t timer_handle,
                                   uint8_t           chan,
                                   uint32_t          clkin);
/**
 * \brief spi Ӳ���㣨master���������
 *
 * \param[in] p_hw_spi  : spi�Ĵ�����  
 * \param[in] clk       : ʱ��
 */
void demo_lpc_hw_spi_master_entry(amhw_lpc_spi_t *p_hw_spi,
                                  uint32_t        clk);
/**
 * \brief spi Ӳ���㣨slave���������
 *
 * \param[in] p_hw_spi  : spi�Ĵ�����  
 * \param[in] clk       : ʱ��
 */
void demo_lpc_hw_spi_slave_entry (amhw_lpc_spi_t *p_hw_spi,
                                  uint32_t        clk);
/**
 * \brief spi Ӳ���㣨slave���������
 *
 * \param[in] p_hw_spi  : spi�Ĵ�����  
 * \param[in] chan      : dmaͨ��
 */
void demo_lpc824_hw_spi_slave_dma_entry(amhw_lpc_spi_t *p_hw_spi, 
                                        uint8_t         chan);

/**
 * \brief
 */
//void demo_lpc845_hw_gpio_entry (amhw_lpc84x_gpio_t *p_hw_gpio,
//                                int                 pin);
/**
 * \brief
 */
void demo_lpc845_hw_gpio_pmatch_entry (int pin);

/**
 * \brief
 */
void demo_lpc845_hw_gpio_int_entry(int    key_pin,
                                   int    led_pin,
                                   int    pint_sel,
                                   int    inum);

/**
 * \brief
 */
void demo_lpc845_hw_mrt_entry (amhw_lpc_mrt_t *p_hw_mrt, int inum);

/**
 * \brief
 */
void demo_lpc845_hw_bod_entry (void);

/**
 * \brief
 */
void demo_lpc845_hw_clkout_entry (void);

/**
 * \brief
 */
void demo_lpc845_hw_i2c_slave_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                         uint8_t         chan);

/**
 * \brief
 */
void demo_lpc845_hw_wkt_deeppowerdown_wakeup_entry(amhw_lpc82x_pmu_t *p_hw_pmu,
                                                   amhw_lpc_wkt_t    *p_hw_wkt,
                                                   int                inum,
                                                   uint32_t           delay_inms);
/**
 * \brief
 */
void demo_lpc845_hw_flash_ctrl_entry(amhw_lpc_fmc_time_t time);

///**
// * \brief
// */
//void demo_lpc_hw_dac_buf_int_entry (amhw_lpc_dac_t *p_hw_dac,
//                                    int             inum);
///**
// * \brief
// */
//void demo_lpc845_hw_adc_dma_entry(amhw_lpc84x_adc_t *p_hw_adc,
//                                  int                ch,
//                                  uint32_t        vref_mv);
///**
// * \brief
// *
// */
//void demo_lpc845_hw_adc_thcmp_entry(amhw_lpc84x_adc_t  *p_hw_adc,
//                                    int                 inum,
//                                    uint32_t            vref_mv);


void demo_lpc845_drv_dma_hwtrigger_burst_entry (uint8_t  chan,
                                                int      pin);

/**
 * \brief
 */
void demo_lpc845_hw_pmu_powerdown_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin);

/**
 * \brief
 */
void demo_lpc845_drv_dma_m2m_entry(uint8_t *p_src, int len);

/**
 * \brief
 */
void demo_lpc845_drv_dma_ping_pong_entry (uint8_t  chan,
                                          uint8_t *p_src,
                                          int      len);
/**
 * \brief
 */
void demo_lpc845_hw_acmp_poll_entry(amhw_lpc82x_acmp_t *p_hw_acmp,
                                    int                 pin);

/**
 * \brief
 */
void demo_lpc845_hw_i2c_master_dma_entry (amhw_lpc_i2c_t *p_hw_i2c,
                                          uint32_t        clkdiv,
                                          uint8_t         addr,
                                          uint8_t         sub_addr);

/**
 * \brief
 */
void demo_lpc845_hw_pmu_deepsleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin);

/**
 * \brief
 */
void demo_lpc845_hw_usart_rx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan);

/**
 * \brief
 */
void demo_lpc845_hw_pmu_sleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                     int                 pin);

/**
 * \brief
 */
void demo_lpc845_hw_usart_tx_dma_entry (amhw_lpc_usart_t *p_hw_usart,
                                        uint32_t          uclk,
                                        uint32_t          baudrate,
                                        int               chan);

/**
 * \brief
 */
void demo_lpc845_hw_iap_entry (void);

#ifdef __cplusplus
}
#endif

#endif /* __DEMO_NXP_ENTRIES_H */

/* end of file */
