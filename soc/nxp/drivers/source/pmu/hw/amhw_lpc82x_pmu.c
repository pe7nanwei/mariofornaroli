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
 * \brief �͹���ģʽӲ����ӿ�
 * 
 * \internal
 * \par Modification History
 * - 1.00 19-04-16  ipk, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \brief ϵͳ���ƼĴ����趨
 *
 * \param[in] flags ϵͳ���ƼĴ����� (#AMHW_LPC82X_SCR_ISRBACK_NTO_SLP)
 *
 * \return ��
 */
am_local void __scb_scr_set (uint32_t flags)
{
    SCB->SCR = flags;
}

/**
 * \brief �͹���ģʽ����
 */
int amhw_lpc82x_lowpower_mode_set (amhw_lpc82x_pmu_t       *p_hw_pmu,
                                   amhw_lpc82x_pmu_pm_src_t mode)
{
    uint32_t flag;

    switch (mode) {
        case AMHW_LPC82X_PMU_PCON_MODE_NORMAL:
             flag = AMHW_LPC82X_SCR_ISRBACK_NTO_SLP| /* �жϷ���ʱ������˯��ģʽ */
                    AMHW_LPC82X_SCR_LOWPWR_MODE_SLP| /* ˯��ģʽ��Ϊ�͹���ģʽ */
                    AMHW_LPC82X_SCR_WKUP_BY_ENAISR;  /* ֻ��ʹ�ܵ��жϲ��ܻ��� */
            break;
        case AMHW_LPC82X_PMU_PCON_MODE_DEEPSLP:
        case AMHW_LPC82X_PMU_PCON_MODE_PD:
            flag = AMHW_LPC82X_SCR_ISRBACK_NTO_SLP   | /* �жϷ���ʱ������˯��ģʽ */
                   AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP | /* ���˯��ģʽ��Ϊ�͹���ģʽ */
                   AMHW_LPC82X_SCR_WKUP_BY_ENAISR;     /* ֻ��ʹ�ܵ��жϲ��ܻ��� */
            break;
        case AMHW_LPC82X_PMU_PCON_MODE_DEEPPD:
             flag = AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP;
             break;
        default:
            return AM_ERROR;
    }

    if (mode == AMHW_LPC82X_PMU_PCON_MODE_DEEPPD) {

        /* ʹ�ܵ͹������� */
        amhw_lpc82x_pmu_lposcen_enable(p_hw_pmu);

        /* ��ȵ���ģʽ��ʹ�ܵ͹������� */
        amhw_lpc82x_pmu_lposcdpden_enable(p_hw_pmu);
    } else {

        /* ���û��ѼĴ��� */
        amhw_lpc82x_syscon_deepwakeup_cfg(amhw_lpc82x_syscon_powerstat_get());

        /* BOD�ϵ磬���Ź�������Դ�ϵ� */
        amhw_lpc82x_syscon_deepsleep_enable(AMHW_LPC82X_SYSCON_PD_BOD |
                                            AMHW_LPC82X_SYSCON_PD_WDT_OSC);
    }

    /* ARM Cortex-M0+ �ں˵ĵ͹���ģʽ */
    __scb_scr_set(flag);

    amhw_lpc82x_pmu_pm_cfg(p_hw_pmu, mode);

    return AM_OK;
}

/* end of file */
