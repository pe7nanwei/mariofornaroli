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
 * \brief AM_ZML166_ADC Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 18-05-14  pea, first implementation
 * \endinternal
 */

#ifndef __AM_ZML166_ADC_H
#define __AM_ZML166_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup am_if_AM_ZML166_ADC
 * @copydoc am_AM_ZML166_ADC.h
 * @{
 */

#include "ametal.h"
#include "am_adc.h"
#include "am_wait.h"

#define  AM_ZML166_ADC_CFG_NUM   7 /**< \brief ϵͳ���üĴ������� */
/** \brief ��ѹУ׼ϵ�������ַ��  */
#define  FLASH_BLOCK_NUM         63
/** \brief PT100У׼ϵ�������ַ  */
#define  PT100_PARA_SAVE_ADDRESS  (((FLASH_BLOCK_NUM * 1024)) + 4 * 16)
/*******************************************************************************
  AM_ZML166_ADC �Ĵ�����ַ
*******************************************************************************/

/**
 * \name AM_ZML166_ADC �Ĵ�����ַ
 * @{
 */
#define AM_ZML166_ADC_SYS_ADDR       (0x00) /**< \brief ϵͳ���üĴ�����ַ */
#define AM_ZML166_ADC_ADC0_ADDR      (0x01) /**< \brief ADC ���üĴ��� 0 ��ַ */
#define AM_ZML166_ADC_ADC1_ADDR      (0x02) /**< \brief ADC ���üĴ��� 1 ��ַ */
#define AM_ZML166_ADC_ADC2_ADDR      (0x03) /**< \brief ADC ���üĴ��� 2 ��ַ */
#define AM_ZML166_ADC_ADC3_ADDR      (0x04) /**< \brief ADC ���üĴ��� 3 ��ַ */
#define AM_ZML166_ADC_ADC4_ADDR      (0x05) /**< \brief ADC ���üĴ��� 4 ��ַ */
#define AM_ZML166_ADC_ADC5_ADDR      (0x06) /**< \brief ADC ���üĴ��� 5 ��ַ */
#define AM_ZML166_ADC_ADO_ADDR       (0x09) /**< \brief ADC ת�����ݼĴ�����ַ */
#define AM_ZML166_ADC_ADS_ADDR       (0x0A) /**< \brief ADC ת�����ݶ�ȡ��׼�Ĵ�����ַ */
#define AM_ZML166_ADC_VREFT_ADDR     (0x11) /**< \brief ADC VREF VBE�޵��Ĵ��� */
#define AM_ZML166_ADC_LDOT_ADDR      (0x12) /**< \brief ADC LDOT�޵��Ĵ��� */
#define AM_ZML166_ADC_OSCT_ADDR      (0x13) /**< \brief ADC OSCT�޵��Ĵ��� */
#define AM_ZML166_ADC_TMUX_ADDR      (0x16) /**< \brief ADC TMUX������üĴ��� */
#define AM_ZML166_ADC_CLK_ADJ_ADDR   (0x55) /**< \brief ʱ��Ƶ���޵��Ĵ�����ַ */
#define AM_ZML166_ADC_TEST_MODE_ADDR (0x5A) /**< \brief оƬ����ģʽ���üĴ�����ַ */
#define AM_ZML166_ADC_RESET_ADDR     (0xEA) /**< \brief ϵͳ��λ�Ĵ�����ַ */
/**
 * @}
 */

/*******************************************************************************
  AM_ZML166_ADC SYS �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_TMODE_MASK    (3 << 6) /**< \brief ����ģʽ���� */
#define AM_ZML166_ADC_TMODE_POWER   (2 << 6) /**< \brief ��Դ��ѹ����ģʽ */
#define AM_ZML166_ADC_TMODE_MANUAL  (0 << 6) /**< \brief �ֶ�����ģʽ���������ã� */

#define AM_ZML166_ADC_PMODE_MASK    (3 << 4) /**< \brief ����ģʽ���� */
#define AM_ZML166_ADC_PMODE_MANUAL  (3 << 4) /**< \brief ����ģʽ(ADC ��������) */
#define AM_ZML166_ADC_PMODE_PWM     (2 << 4) /**< \brief ռ�ձ�ģʽ��DR = 640Hz */
#define AM_ZML166_ADC_PMODE_PER     (1 << 4) /**< \brief ����ģʽ */
#define AM_ZML166_ADC_PMODE_NORMAL  (0 << 4) /**< \brief ��ͨģʽ����ǰ�����ã� */

#define AM_ZML166_ADC_ENREF_ENABLE  (1 << 3) /**< \brief VREF ʹ�� */
#define AM_ZML166_ADC_ENREF_DISABLE (0 << 3) /**< \brief VREF �ر� */

#define AM_ZML166_ADC_ENADC_ENABLE  (1 << 2) /**< \brief ADC ʹ�� */
#define AM_ZML166_ADC_ENADC_DISABLE (0 << 2) /**< \brief ADC �ر� */

#define AM_ZML166_ADC_ENLDO_ENABLE  (1 << 1) /**< \brief LDO ʹ�� */
#define AM_ZML166_ADC_ENLDO_DISABLE (0 << 1) /**< \brief LDO �ر� */

/*******************************************************************************
  AM_ZML166_ADC ADC0 �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_IMODE_PER    (1 << 7)    /**< \brief ����������ģʽ����(��ͨģʽ����x2) */
#define AM_ZML166_ADC_IMODE_NORMAL (0 << 7)    /**< \brief ��������ͨģʽ���� */

#define AM_ZML166_ADC_FS_662_22    (1 << 6)    /**< \brief ����Ƶ��Ϊ 662.22KHz */
#define AM_ZML166_ADC_FS_331_11    (0 << 6)    /**< \brief ����Ƶ��Ϊ 331.11KHz */

#define AM_ZML166_ADC_INNS_MASK    (7 << 3)    /**< \brief PGA ���������ź����� */
#define AM_ZML166_ADC_INNS_TSN     (7 << 3)    /**< \brief PGA ���������źţ�TS ���� */
#define AM_ZML166_ADC_INNS_1_2_VS  (5 << 3)    /**< \brief PGA ���������źţ�1/2 VS����ģ��ѹ�� */
#define AM_ZML166_ADC_INNS_GND     (4 << 3)    /**< \brief PGA ���������źţ�GND������ TMODE=10 ��Ч�� */
#define AM_ZML166_ADC_INNS_AIN4    (3 << 3)    /**< \brief PGA ���������źţ�AIN4 */
#define AM_ZML166_ADC_INNS_AIN3    (2 << 3)    /**< \brief PGA ���������źţ�AIN3 */
#define AM_ZML166_ADC_INNS_AIN2    (1 << 3)    /**< \brief PGA ���������źţ�AIN2 */
#define AM_ZML166_ADC_INNS_AIN1    (0 << 3)    /**< \brief PGA ���������źţ�AIN1 */

#define AM_ZML166_ADC_INNS_AIN(ch) ((ch) << 3) /**< \brief PGA ���������źţ�AIN4~AIN1 */
#define AM_ZML166_ADC_INPS_AIN(ch) ((ch) << 0) /**< \brief PGA ���������źţ�AIN3~AIN0 */
#define AM_ZML166_ADC_INPS_MASK    (7 << 0)    /**< \brief PGA ���������ź����� */
#define AM_ZML166_ADC_INPS_TSP     (7 << 0)    /**< \brief PGA ���������źţ�TS ���� */
#define AM_ZML166_ADC_INPS_1_2_VS  (5 << 0)    /**< \brief PGA ���������źţ�1/2 VS����ģ��ѹ�� */
#define AM_ZML166_ADC_INPS_1_8_VDD (4 << 0)    /**< \brief PGA ���������źţ�1/8 VDD������ TMODE=10 ��Ч�� */
#define AM_ZML166_ADC_INPS_AIN3    (3 << 0)    /**< \brief PGA ���������źţ�AIN3 */
#define AM_ZML166_ADC_INPS_AIN2    (2 << 0)    /**< \brief PGA ���������źţ�AIN2 */
#define AM_ZML166_ADC_INPS_AIN1    (1 << 0)    /**< \brief PGA ���������źţ�AIN1 */
#define AM_ZML166_ADC_INPS_AIN0    (0 << 0)    /**< \brief PGA ���������źţ�AIN0 */
/*******************************************************************************
  AM_ZML166_ADC ADC1 �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_DR_MASK       (7 << 5)   /**< \brief ADC ����������� */
#define AM_ZML166_ADC_DR_1280       (7 << 5)   /**< \brief ADC �������Ϊ 1280 Hz */
#define AM_ZML166_ADC_DR_640        (6 << 5)   /**< \brief ADC �������Ϊ 640 Hz */
#define AM_ZML166_ADC_DR_320        (5 << 5)   /**< \brief ADC �������Ϊ 320 Hz */
#define AM_ZML166_ADC_DR_160        (4 << 5)   /**< \brief ADC �������Ϊ 160 Hz */
#define AM_ZML166_ADC_DR_80         (3 << 5)   /**< \brief ADC �������Ϊ 80 Hz */
#define AM_ZML166_ADC_DR_40         (2 << 5)   /**< \brief ADC �������Ϊ 40 Hz */
#define AM_ZML166_ADC_DR_20         (1 << 5)   /**< \brief ADC �������Ϊ 20 Hz */
#define AM_ZML166_ADC_DR_10         (0 << 5)   /**< \brief ADC �������Ϊ 10 Hz */

#define AM_ZML166_ADC_BUFBP_DISABLE (1 << 4)   /**< \brief Buffer �رգ�TBD����ǰ�����ã� */
#define AM_ZML166_ADC_BUFBP_ENABLE  (0 << 4)   /**< \brief Buffer ���� */

#define AM_ZML166_ADC_PGA_MASK      (3 << 2)   /**< \brief PGA �������� */
#define AM_ZML166_ADC_PGA_32        (3 << 2)   /**< \brief PGA ����Ϊ 32 */
#define AM_ZML166_ADC_PGA_16        (2 << 2)   /**< \brief PGA ����Ϊ 16 */
#define AM_ZML166_ADC_PGA_1         (0 << 2)   /**< \brief PGA ����Ϊ 1 */

#define AM_ZML166_ADC_ADGN_MASK     (3 << 0)   /**< \brief �������������� */
#define AM_ZML166_ADC_ADGN_8        (3 << 0)   /**< \brief ����������Ϊ 8��DR �½�Ϊ 1/4 */
#define AM_ZML166_ADC_ADGN_4        (2 << 0)   /**< \brief ����������Ϊ 4��DR �½�Ϊ 1/2 */
#define AM_ZML166_ADC_ADGN_2        (1 << 0)   /**< \brief ����������Ϊ 2 */
#define AM_ZML166_ADC_ADGN_1        (0 << 0)   /**< \brief ����������Ϊ 1 */

/*******************************************************************************
  AM_ZML166_ADC ADC3 �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_GTCSL_COARSE    (1 << 7) /**< \brief ������Ư�����ֵ���Ϊ����x6�����ڲ�����������Ư */
#define AM_ZML166_ADC_GTCSL_FINE      (0 << 7) /**< \brief ���������ڵ���оƬ������Ư */

#define AM_ZML166_ADC_GTC_MASK        (7 << 4) /**< \brief ������Ư�������� */
#define AM_ZML166_ADC_GTC_P_15PPM     (7 << 4) /**< \brief ������Ư���� 15PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_P_10PPM     (6 << 4) /**< \brief ������Ư���� 10PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_P_5PPM      (5 << 4) /**< \brief ������Ư���� 5PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_0PPM        (0 << 4) /**< \brief ������Ư���� 0PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_N_15PPM     (3 << 4) /**< \brief ������Ư���� -15PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_N_10PPM     (2 << 4) /**< \brief ������Ư���� -10PPM/��(CTCSL=0) */
#define AM_ZML166_ADC_GTC_N_5PPM      (1 << 4) /**< \brief ������Ư���� -5PPM/��(CTCSL=0) */

#define AM_ZML166_ADC_LVSCP_ENABLE    (1 << 3) /**< \brief ��ƽ��λģ��ն��ʹ�ܣ�ն��Ƶ�� Fs/128 */
#define AM_ZML166_ADC_LVSCP_DISABLE   (0 << 3) /**< \brief ��ƽ��λģ��ն����ʹ�� */

#define AM_ZML166_ADC_LVSHIFT_ENABLE  (1 << 2) /**< \brief ��ƽ��λʹ�� */
#define AM_ZML166_ADC_LVSHIFT_DISABLE (0 << 2) /**< \brief ��ƽ��λ��ʹ�� */

/*******************************************************************************
  AM_ZML166_ADC ADC4 �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_CHOPM_MASK       (3 << 6) /**< \brief ն��Ƶ������ */
#define AM_ZML166_ADC_CHOPM_64_128     (3 << 6) /**< \brief �Ƿ�ն��Ƶ��Ϊ fs_clk/64��������ն��Ƶ��Ϊ fs_clk/128 */
#define AM_ZML166_ADC_CHOPM_32_128     (2 << 6) /**< \brief �Ƿ�ն��Ƶ��Ϊ fs_clk/32��������ն��Ƶ��Ϊ fs_clk/128 */
#define AM_ZML166_ADC_CHOPM_32_256     (1 << 6) /**< \brief �Ƿ�ն��Ƶ��Ϊ fs_clk/32��������ն��Ƶ��Ϊ fs_clk/256 */
#define AM_ZML166_ADC_CHOPM_DISABLE    (0 << 6) /**< \brief ����ն�� fs_clk Ϊ MOD ����Ƶ�� */

#define AM_ZML166_ADC_ACCU_MASK        (3 << 4) /**< \brief ռ�ձ�ģʽ�� COMB �����ۼӸ������� */
#define AM_ZML166_ADC_ACCU_NUM_64      (3 << 4) /**< \brief ռ�ձ�ģʽ�� COMB �����ۼӸ���Ϊ 64 */
#define AM_ZML166_ADC_ACCU_NUM_32      (2 << 4) /**< \brief ռ�ձ�ģʽ�� COMB �����ۼӸ���Ϊ 32 */
#define AM_ZML166_ADC_ACCU_NUM_18      (1 << 4) /**< \brief ռ�ձ�ģʽ�� COMB �����ۼӸ���Ϊ 16 */
#define AM_ZML166_ADC_ACCU_NUM_8       (0 << 4) /**< \brief ռ�ձ�ģʽ�� COMB �����ۼӸ���Ϊ 8 */

#define AM_ZML166_ADC_ADREFS_MASK      (3 << 2) /**< \brief ADC �ο���ѹ���� */
#define AM_ZML166_ADC_ADREFS_VREF_GND  (3 << 2) /**< \brief ���ο�=�ڲ� VREF�����ο�=GND */
#define AM_ZML166_ADC_ADREFS_REFP_REFN (0 << 2) /**< \brief ���ο�=�ⲿ REFP�����ο�=�ⲿ REFN */

#define AM_ZML166_ADC_LDOS_MASK        (3 << 0) /**< \brief �ڲ� LDO ��� VS ��ѹ���� */
#define AM_ZML166_ADC_LDOS_3_0         (3 << 0) /**< \brief �ڲ� LDO ��� VS ��ѹΪ 3.0V */
#define AM_ZML166_ADC_LDOS_2_8         (2 << 0) /**< \brief �ڲ� LDO ��� VS ��ѹΪ 2.8V */
#define AM_ZML166_ADC_LDOS_2_45        (1 << 0) /**< \brief �ڲ� LDO ��� VS ��ѹΪ 2.45V */
#define AM_ZML166_ADC_LDOS_2_35        (0 << 0) /**< \brief �ڲ� LDO ��� VS ��ѹΪ 2.35V */

/*******************************************************************************
  AM_ZML166_ADC ADC5 �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_EN_OPA_ENABLE    (1 << 5) /**< \brief ʹ�� OPA_FIL���� AIN2~AIN4 ����Ϊ OPA_FIL �˿� */
#define AM_ZML166_ADC_EN_OPA_DISABLE   (0 << 5) /**< \brief �ر� OPA_FIL��AIN2~AIN4 ��ģ������ */

#define AM_ZML166_ADC_EXFIL_EN_ENABLE  (1 << 4) /**< \brief PGA �����ź�ʹ�� RC �˲� */
#define AM_ZML166_ADC_EXFIL_EN_DISABLE (0 << 4) /**< \brief PGA �����źŲ�ʹ�� RC �˲� */

#define AM_ZML166_ADC_FIL_EN_ENABLE    (1 << 2) /**< \brief Comb ֮��ĵ�ͨ�˲���ʹ�� */
#define AM_ZML166_ADC_FIL_EN_DISABLE   (0 << 2) /**< \brief Comb ֮��ĵ�ͨ�˲���ʧ�� */

#define AM_ZML166_ADC_FIL_CON1_DISABLE (1 << 1) /**< \brief �˲�����ʹ�ü����ṹ */
#define AM_ZML166_ADC_FIL_CON1_ENABLE  (0 << 1) /**< \brief �˲���ʹ�ü����ṹ */

#define AM_ZML166_ADC_FIL_CON2_2       (1 << 0) /**< \brief ʹ���˲���ϵ�� 2 */
#define AM_ZML166_ADC_FIL_CON2_1       (0 << 0) /**< \brief ʹ���˲���ϵ�� 1 */

/*******************************************************************************
  AM_ZML166_ADC ADS �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_ADS_ADO_BIT      (1 << 7) /**< \brief ADO �������Ѿ�����ȡ */

#define AM_ZML166_ADC_ADS_RST_BIT      (1 << 6) /**< \brief оƬ�ϵ縴λ��� */

/*******************************************************************************
  AM_ZML166_ADC VREFT �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_VREFTRIM_MASK     0xF0    /**< \brief �ڲ��ο� VREF �޵�ֵ���� */

#define AM_ZML166_ADC_BGTRIM_MASK       0x0F    /**< \brief �ڲ��ο� VBE �޵�ֵ���� */

/*******************************************************************************
  AM_ZML166_ADC LDOT �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_LDOTRIM_MASK      0x0F    /**< \brief �ڲ��ο� LDO �޵�ֵ���� */

/*******************************************************************************
  AM_ZML166_ADC OSCT �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_OSCTRIM_MASK      0xFF    /**< \brief �ڲ��ο� OSC �޵�ֵ���� */

/*******************************************************************************
  AM_ZML166_ADC TMUX �Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_TMUX_ENABLE       0<<7    /**< \brief ʹ��TMUX��� */
#define AM_ZML166_ADC_TMUX_DISABLE      1<<7    /**< \brief ����TMUX��� */

#define AM_ZML166_ADC_TMUX_CLK_16       0x07    /**< \brief TMUX����ڲ�ʱ�� 16 ��Ƶ */
#define AM_ZML166_ADC_TMUX_AGND         0x06    /**< \brief TMUX����ڲ� AGND */
#define AM_ZML166_ADC_TMUX_NEG_VOL      0x05    /**< \brief TMUX�����ƽ��λ���˵�ѹ */
#define AM_ZML166_ADC_TMUX_PSO_VOL      0x04    /**< \brief TMUX�����ƽ��λ���˵�ѹ */
#define AM_ZML166_ADC_TMUX_IDAC1        0x03    /**< \brief TMUX����ڲ� IDAC1 ���� */
#define AM_ZML166_ADC_TMUX_VS           0x02    /**< \brief TMUX����ڲ� VS ��ѹ */
#define AM_ZML166_ADC_TMUX_VREF         0x01    /**< \brief TMUX���VREF ��ѹ */
#define AM_ZML166_ADC_TMUX_VBE          0x00    /**< \brief TMUX���VBE ��ѹ*/
/*******************************************************************************
  AM_ZML166_ADC ʱ��Ƶ���޵��Ĵ���
*******************************************************************************/

#define AM_ZML166_ADC_CLK_ADJ_ENABLE    0xA5    /**< \brief ʹ��ʱ��Ƶ���޵� */
#define AM_ZML166_ADC_CLK_ADJ_DISABLE   0       /**< \brief ʧ��ʱ��Ƶ���޵� */

/*******************************************************************************
  AM_ZML166_ADC ϵͳ����ģʽ���üĴ���
*******************************************************************************/

#define AM_ZML166_ADC_TEST_MODE_ENABLE  0x5A    /**< \brief �������ģʽ */

/*******************************************************************************
  AM_ZML166_ADC ϵͳ��λ�Ĵ���
******************************************************************************/
#define AM_ZML166_ADC_RESET_ENABLE      0x96    /**< \brief ʹ��ADC��λ */

/*******************************************************************************
  AM_ZML166_ADC �޵���������
******************************************************************************/
#define AM_ZML166_ADC_ADJUST_PARA_ENABLE        0          /**< \brief �޵�����д����Ʊ�־ */
#define AM_ZML166_ADC_ADJUST_PARA_SAVE_ADDRESS  0x1FFFF810 /**< \brief �޵����������ַ*/

/*******************************************************************************
  AM_ZML166_ADC �������
******************************************************************************/
#define AM_ZML166_ADC_PGA_SET_1          0
#define AM_ZML166_ADC_PGA_SET_2          1
#define AM_ZML166_ADC_PGA_SET_4          2
#define AM_ZML166_ADC_PGA_SET_8          3
#define AM_ZML166_ADC_PGA_SET_16         4
#define AM_ZML166_ADC_PGA_SET_32         5
#define AM_ZML166_ADC_PGA_SET_64         6
#define AM_ZML166_ADC_PGA_SET_128        7

/** \brief ADCת�����ֵ */
typedef uint32_t am_adc_val_t;
/**

 * \brief AM_ZML166_ADC �豸��Ϣ�ṹ��
 */
typedef struct am_zml166_adc_devinfo {
    uint32_t  vref;             /**< \brief ADC �ο���ѹ����λ��mV */
    uint32_t  timeout;          /**< \brief ��ʱʱ�䣬��λΪ���� */
} am_zml166_adc_devinfo_t;

/**
 * \brief zml166_adc �豸�ṹ��
 */
typedef struct am_zml166_adc_dev {

    /** \brief ADC ��׼���� */
    am_adc_serv_t                  adc_serve;
    
    /** \brief ADC ���� */
    uint8_t                        dr;

    /** \brief �ж��Ƿ�ʹ�� */
    am_bool_t                      irq_en;
    
    /** \brief ��ǰ ADC ʱ��Ƶ�� */
    uint32_t                       clk_freq;

    /** \brief ����ת����ɵȴ� */
    am_wait_t                      ready_wait;

    /** \brief �Ĵ��������� */
    uint8_t                        reg[AM_ZML166_ADC_CFG_NUM];

    /** \brief ADC ״̬ 0: ���� 1:����ת�������� */
    uint8_t                        adc_state;

    /** \brief ͨ�� */
    uint8_t                        chan;

    /** \brief ��ǰת�������������������׵�ַ */
    am_adc_buf_desc_t             *p_desc;

    /** \brief ��ǰת������������������ */
    uint32_t                       desc_num;

    /** \brief ת���Ĵ��� */
    uint32_t                       count;

    /** \brief ת����־ */
    uint32_t                       flags;

    /** \brief ����û�����ת����Ļص����� */
    am_adc_seq_cb_t                pfn_callback;

    /** \brief �û������ص������Ļص��������� */
    void                          *p_arg;

    /** \brief �Ե�ǰ�����������Ѿ������Ĵ��� */
    uint32_t                       conv_cnt;

    /** \brief ����ִ�е�ǰ���������������� */
    uint32_t                       desc_index;

    /** \brief ����������ת����ɵĴ��� */
    uint32_t                       seq_cnt;

    /** \brief �豸��Ϣ */
    const am_zml166_adc_devinfo_t      *p_devinfo;
    /**< \brief У��ADS�Ĵ���ʹ�ܿ���*/
    int       verify_flag;
} am_zml166_adc_dev_t;

/**
 * \brief AM_ZML166_ADC �������
 */
typedef am_zml166_adc_dev_t *am_zml166_adc_handle_t;

/**
 * \brief AM_ZML166_ADC �Ĵ�������
 *
 * \param[in] p_dev ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[in] addr  �Ĵ�����ַ��ֻ�� SYS �� ADC �Ĵ�����д
 * \param[in] data  ��д�������
 *
 * \retval  AM_OK     д��ɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EBUSY  �豸æ
 */
am_err_t am_zml166_adc_reg_set (am_zml166_adc_dev_t *p_dev,
                                uint8_t              addr,
                                uint32_t             data);

/**
 * \brief AM_ZML166_ADC �Ĵ�����ȡ
 *
 * \param[in]  p_dev  ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[in]  addr   ����ȡ�ļĴ�����ַ
 * \param[out] p_data ָ����ջ�������ָ�룬��С����С�ڱ���ȡ�ļĴ�����С
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EBUSY  �豸æ
 */
am_err_t am_zml166_adc_reg_get (am_zml166_adc_dev_t *p_dev,
                                uint8_t              addr,
                                void                *p_data);

/**
 * \brief AM_ZML166_ADC ǰ�÷Ŵ�����������
 *
 * \param[in] p_dev ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[in] gain  ���棬������Ϊ 1��2��4��8��16��32��64��128��256
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EBUSY  �豸æ
 *
 * \note ����������Ϊ 4 �� 32 ʱ��ADC ������ʽ���Ϊ 1 / 2��
 *       ����������Ϊ 8��64��128 �� 256 ʱ��ADC ������ʽ���Ϊ 1 / 4
 */
am_err_t am_zml166_adc_gain_set (am_zml166_adc_dev_t *p_dev,
                                 uint16_t             gain);

/**
 * \brief AM_ZML166_ADC ǰ�÷Ŵ��������ȡ
 *
 * \param[in]  p_dev  ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[out] p_gain ָ�򱣴��ȡ���������ָ��
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zml166_adc_gain_get (am_zml166_adc_dev_t *p_dev,
                                 uint8_t             *p_gain);

/**
 * \brief AM_ZML166_ADC MUX ͨ����ȡ
 *
 * \param[in]  p_dev  ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[out] p_chan ָ�򱣴��ȡ���� MUX ͨ����ָ��
 *
 * \retval  AM_OK     ��ȡ�ɹ�
 * \retval -AM_EINVAL ��Ч����
 */
am_err_t am_zml166_adc_mux_get (am_zml166_adc_dev_t *p_dev,
                                uint8_t             *p_chan);

/**
 * \brief AM_ZML166_ADC MUX ͨ������
 *
 * \param[in] p_dev ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[in] chan  MUX ͨ����0~2 λΪ MUXP��3~5 λΪ MUXN
 *
 * \retval  AM_OK     ���óɹ�
 * \retval -AM_EINVAL ��Ч����
 * \retval -AM_EBUSY  �豸æ
 */
am_err_t am_zml166_adc_mux_set (am_zml166_adc_dev_t *p_dev,
                                uint8_t              chan);

/**
 * \brief AM_ZML166_ADC ��ʼ���Ĵ�������
 *
 * \param[in] p_dev     ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 *
 * \retval  AM_OK     ��ʼ���ɹ�
 * \retval  AM_ERROR  ��ʼ��ʧ��
 */
am_err_t am_zml166_adc_reg_init(am_zml166_adc_dev_t           *p_dev);

/**
 * \brief AM_ZML166_ADC ��ʼ������
 *
 * \param[in] p_dev     ָ�� AM_ZML166_ADC �豸�ṹ���ָ��
 * \param[in] p_devinfo ָ�� AM_ZML166_ADC �豸��Ϣ�ṹ���ָ��
 *
 * \return AM_ZML166_ADC �������Ϊ NULL��������ʼ��ʧ��
 */
am_zml166_adc_handle_t am_zml166_adc_init (am_zml166_adc_dev_t           *p_dev,
                                           const am_zml166_adc_devinfo_t *p_devinfo);

/**
 * \brief AM_ZML166_ADC ���ʼ������
 *
 * \param[in] handle AM_ZML166_ADC ���
 *
 * \return ��
 */
void am_zml166_adc_deinit (am_zml166_adc_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZML166_ADC_H */

/* end of file */
