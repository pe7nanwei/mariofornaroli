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
 * \brief PMU ��ȵ���ģʽ���̣�ͨ�� HW ��ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���г���һ��� LED0 ��˸һ�κ������ȵ���ģʽ��
 *   2. �ȴ� 5s ��WKT ��ʱʱ�䵽��CPU �����ѣ����ͨ�üĴ�������У����ȷ��LED0
 *      ��˸һ�Σ����ͨ�üĴ�������У�����LED0 ������˸��
 *
 * \note
 *    1. LED0 ��Ҫ�̽� J9 ����ñ�����ܱ� PIO0_20 ���ƣ�
 *    2. ������ȵ���ģʽ��ֻ�� WAKEUP ���ź� WKT ��ʱ���ܻ���оƬ������Ĭ��״̬��
 *       WAKEUP ���Ż���ʹ�ܣ�����һ��ȷ�� WAKEUP �ⲿ��������Դ����֤��Ч�ĸߵ�ƽ
 *       ״̬��������������Ѳ��������۲첻�� WKT ���� CPU���������̽� WAKEUP ����
 *       (PIO0_4)���ѹ��ܽ�ֹ�ˣ����Բ���Ҫ�� PIO0_4 ������
 *    3. ��demoʹ�ñ�׼���ʼ��wkt��ʱ������Ҫ�� am_hwconf_lpc82x_wkt.c�н�wktʱ��Դѡ��Ϊ
 *       �͹���ʱ�� AMHW_LPC_WKT_LOW_POWER_CLOCK��
 *    4. ʹ�øó���󣬻ᵼ���´γ�����д��ʱ���ⲻ��оƬ������оƬ������ȵ���
 *       ģʽ�� SWD ����ģʽ�رգ����´�����ʱ�� P0_12 ���ͻ򰴶���λ��֮��һ����
 *       �����������ص��ԡ�
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_pmu_deeppowerdown.c src_lpc824_hw_pmu_deeppowerdown
 *
 * \internal
 * \par Modification history
 * - 1.02 19-04-17  ipk, modified
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-14  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_deeppowerdown
 * \copydoc demo_lpc824_hw_pmu_deeppowerdown.c
 */

/** [src_lpc824_hw_pmu_deeppowerdown] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc_wkt.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/*******************************************************************************
  ����ȫ�ֱ�������
*******************************************************************************/

/** \brief �жϱ�־���� */
am_local volatile uint8_t __g_deeppowerdown_wkt_flag = 0;

/*******************************************************************************
  ���غ�������
*******************************************************************************/

/**
 * \brief WKT �жϷ�����
 */
am_local void __deeppowerdown_wkt_isr (void *p_arg)
{
    if (amhw_lpc_wkt_alarmflag_get(LPC82X_WKT)) {
        amhw_lpc_wkt_alarmflag_clear(LPC82X_WKT);      /* ����жϱ�־ */
        __g_deeppowerdown_wkt_flag = 1;                /* �ı��жϱ�־���� */
    }
}

/**
 * \brief PMU ��ȵ���ģʽ��ʼ��
 */
void demo_lpc824_hw_pmu_deeppowerdown_entry (amhw_lpc82x_pmu_t *p_hw_pmu,
                                             am_timer_handle_t  wkt_handle)
{
  
    /* ��ʱһ�룬�����´����س��� */
    am_mdelay(1000);

    /* LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    /* �Ѿ�����ȵ����л��� */
    if (amhw_lpc82x_pmu_dpdflag_get(p_hw_pmu) != 0x0) {

        /* �����ȵ���ģʽ��־λ */
        amhw_lpc82x_pmu_dpdflag_clear(p_hw_pmu);

        if ((amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_0) != 0x12345678) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_1) != 0x87654321) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_2) != 0x56781234) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_3) != 0x43218765)) {

            /* ����ȵ��绽�Ѻ�ͨ�üĴ������ݼ��ʧ�ܣ�LED0 ������˸ */
            AM_FOREVER {

                /* LED0 �� 0.5s �ļ��һֱ��˸ */
                am_led_toggle(LED0);
                am_mdelay(500);
            }
        }
    } else {

        /* δ������ȵ���ģʽ������ͨ�üĴ������ݣ����ڲ��� */
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_0, 0x12345678);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_1, 0x87654321);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_2, 0x56781234);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_3, 0x43218765);

        /* �������� PIO0_4 �ϵĻ��ѹ��� */
        amhw_lpc82x_pmu_lposcen_disable(p_hw_pmu);

        /* ������ȵ���ģʽ */
        amhw_lpc82x_lowpower_mode_set(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_DEEPPD);

        /* WKT �����жϻص� */
        am_timer_callback_set(wkt_handle, 0, __deeppowerdown_wkt_isr, NULL);

        /* ���� WKT ��ʱʱ�� 5s */
        am_timer_enable_us(wkt_handle, 0, 5000000);

        /* ������ȵ���ģʽ */
        __WFI();
    }
    
    /* ����ȵ���ģʽ���Ѻ�ͨ�üĴ������ݼ����ȷ��LED0 ��˸һ�� */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc824_hw_pmu_deeppowerdown] */

/* end of file */
