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
 * \brief ˯��ģʽ���̣�ʹ�ö�ʱ�����ڻ��ѣ�ͨ��������ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0 �������ȴ� 5 ��󣬿�ʼ�͹��Ĳ��ԣ����ʱ���û��ɲ�������ģʽ�Ĺ��ģ�
 *   2. �������"enter sleep!"��Ϩ�� LED0��������ʱ����
 *      ����˯��ģʽ��J-Link ���ԶϿ�����ʱ�û��ɲ���˯��ģʽ�Ĺ��ģ�
 *   3. �ȴ���ʱʱ�䵽��MCU �����ѣ��������"wake_up!"������ LED0��Ȼ�����½���
 *      ˯��ģʽ��
 *
 * \note
 *   ���� TIM4 Ĭ�ϳ�ʼ������Ϊϵͳ�δ�ʹ�ã��ᶨ�ڲ����жϵ��»��ѣ� ���Ա�����
 *   ֮ǰӦ�� am_prj_config.h �еĺ� AM_CFG_SYSTEM_TICK_ENABLE��
 *   AM_CFG_SOFTIMER_ENABLE ��   AM_CFG_KEY_GPIO_ENABLE ����Ϊ 0��
 *
 * \par Դ����
 * \snippet demo_zmf237_drv_sleepmode_timer_wake_up.c src_zmf237_drv_sleepmode_timer_wake_up
 *
 * \internal
 * \par Modification History
 * - 1.00 18-05-16  pea, first implementation
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_zmf237_drv_sleepmode_timer_wake_up
 * \copydoc demo_zmf237_drv_sleepmode_timer_wake_up.c
 */
 
/** [src_zmf237_drv_sleepmode_timer_wake_up] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_vdebug.h"
#include "am_zmf237.h"
#include "am_zmf237_pwr.h"
#include "am_zmf237_clk.h"
#include "am_zmf237_inst_init.h"
#include "zmf237_periph_map.h"
#include "amhw_zlg_uart.h"
#include "demo_am237_core_entries.h"

/** \brief LSI ʱ��Ƶ�� */
#define    __LSI_CLK    (40000UL)

/**
 * \brief �ȴ� RTC ����Ϊ����״̬
 */
am_local void __wait_rtc_idle (void)
{
    while(!amhw_zmf237_rtc_crl_read_statu(ZMF237_RTC, AMHW_ZMF237_RTC_RSF));
    while(!amhw_zmf237_rtc_crl_read_statu(ZMF237_RTC, AMHW_ZMF237_RTC_RTOFF));
}

/**
 * \brief ��ʱ���ص�����
 */
am_local void __rtc_handler (void *p_arg)
{

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();
    
    /* �ж��ж�Դ */
    if (amhw_zmf237_rtc_crl_read_statu(ZMF237_RTC, AMHW_ZMF237_RTC_ALRF)) {
        
        /* �ȴ� RTC ����Ϊ����״̬ */
        __wait_rtc_idle();
        
        /* ����жϱ�־λ */
        amhw_zmf237_rtc_clr_status_clear(ZMF237_RTC, AMHW_ZMF237_RTC_ALRF);
    }
}

/**
 *  \brief ���� RTC ����ʱ��
 */
am_local void __rtc_alarm_set (uint32_t second)
{
    uint32_t sec = 0;

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    /* ��ȡ��ǰ RTC ʱ�� */
    sec = amhw_zmf237_rtc_cnth_get(ZMF237_RTC) << 16;
    sec |= amhw_zmf237_rtc_cntl_get(ZMF237_RTC);

    sec += second - 1;
    
    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();
    
    amhw_zmf237_rtc_crl_cnf_enter(ZMF237_RTC); /* �������� */
    amhw_zmf237_rtc_alrl_set(ZMF237_RTC, sec & 0xffff);
    amhw_zmf237_rtc_alrh_set(ZMF237_RTC, sec >> 16);
    amhw_zmf237_rtc_crl_cnf_out(ZMF237_RTC); /* ���ø��� */
}

/** \brief RTC ƽ̨��ʼ�� */
am_local void __rtc_init (void)
{
    
    /* ʹ�� LSI */
    amhw_zmf237_rcc_lsi_enable();
    while (amhw_zmf237_rcc_lsirdy_read() == AM_FALSE);

    amhw_zmf237_rcc_apb1_enable(AMHW_ZMF237_RCC_APB1_PWR); /* ʹ�ܵ�Դʱ�� */
    amhw_zmf237_rcc_apb1_enable(AMHW_ZMF237_RCC_APB1_BKP); /* ʹ�ܱ���ʱ�� */
    amhw_zlg_pwr_bkp_access_enable(ZMF237_PWR, 1); /* ȡ���������д���� */
    amhw_zmf237_rcc_bdcr_bdrst_reset();                    /* �������������λ */
    am_udelay(5);
    amhw_zmf237_rcc_bdcr_bdrst_reset_end();                /* �����������λ���� */
    
    /* RTC ʱ��Դѡ��Ϊ LSI */
    amhw_zmf237_rcc_bdcr_rtc_clk_set(AMHW_ZMF237_RTCCLK_LSI);
    am_mdelay(1);
    amhw_zmf237_rcc_bdcr_rtc_enable();                     /* RTCʱ��ʹ�� */

    /* ��ʱ�ȴ�Ԥ��Ƶ�Ĵ����ȶ� */
    am_mdelay(10);

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    /* ���������ж� */
    amhw_zmf237_rtc_crh_allow_int(ZMF237_RTC, AMHW_ZMF237_RTC_ALRIE);

    /* �ȴ� RTC ����Ϊ����״̬ */
    __wait_rtc_idle();

    amhw_zmf237_rtc_crl_cnf_enter(ZMF237_RTC); /* �������� RTC */
    amhw_zmf237_rtc_prll_div_write(ZMF237_RTC, (__LSI_CLK - 1) & 0xffff);
    amhw_zmf237_rtc_prlh_div_write(ZMF237_RTC, (__LSI_CLK - 1) >> 16);
    amhw_zmf237_rtc_crl_cnf_out(ZMF237_RTC); /* ���ø��� */

    /* ���Ӳ�ʹ�� RTC �����ж� */
    am_int_connect(INUM_RTC, __rtc_handler, NULL);
    am_int_enable(INUM_RTC);
    
}

/**
 * \brief �������
 */
void demo_zmf237_drv_sleepmode_timer_wake_up_entry (void)
{
    uint32_t i;
    
    AM_DBG_INFO("low power test!\r\n");
    am_led_on(LED0);

    /* ��ʼ�� RTC */
    __rtc_init();
    
    /* ��ʼ�� PWR */
    am_zmf237_pwr_inst_init();

    /* �������� */
    am_zmf237_wake_up_cfg(AM_ZMF237_PWR_MODE_SLEEP, NULL, NULL);

    for (i = 0; i < 5; i++) {
        am_mdelay(1000);
    }

    while (1) {

        /* ˯��֮ǰ�ر� LED */
        am_led_off(LED0);

        /* ���ö�ʱ�ж�����Ϊ 1S����������ʱ�� */        
        __rtc_alarm_set(1);

        /* ����˯��ģʽ */
        am_zmf237_pwr_mode_into(AM_ZMF237_PWR_MODE_SLEEP);

        AM_DBG_INFO("wake_up!\r\n");

        /* ����֮����� LED */
        am_led_on(LED0);
        am_mdelay(10);
    }
}

/** [src_zmf237_drv_sleepmode_timer_wake_up] */

/* end of file */
