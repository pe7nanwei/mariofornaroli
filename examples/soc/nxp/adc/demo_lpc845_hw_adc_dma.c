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
 * \brief ADC ���̣�ת���������ͨ�� DMA ���䣬ͨ�� HW ��ӿ�ʵ��
 *
 *
 * - ʵ������
 *   1. ADC ת����� 100 �Σ����ڴ�ӡ�� 100 ��������ѹֵ��
 *
 * \note
 *    ����۲촮�ڴ�ӡ�ĵ�����Ϣ����Ҫ�� PIO0_0 �������� PC ���ڵ� TXD��
 *    PIO0_4 �������� PC ���ڵ� RXD��
 *
 * \par Դ����
 * \snippet demo_lpc824_hw_adc_dma.c src_lpc824_hw_adc_dma
 *
 * \internal
 * \par Modification history
 * - 1.01 15-11-24  hgo, modified
 * - 1.00 15-07-23  bob, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_adc_dma
 * \copydoc demo_lpc824_hw_adc_dma.c
 */

/** [src_lpc824_hw_adc_dma] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_lpc84x_dma.h"
#include "hw/amhw_lpc84x_adc.h"
#include "hw/amhw_lpc84x_syscon.h"

/** \brief ��������С */
#define __ADC_BUF_LEN   100

/** \brief ADC ת����������� */
am_local uint32_t __g_adc_abuf[__ADC_BUF_LEN];
am_local uint32_t __g_adc_bbuf[__ADC_BUF_LEN];

/** \brief DMA ����������(16 �ֽڶ���) */
am_local __attribute__((aligned(16))) am_lpc84x_dma_xfer_desc_t __g_desc[2];

/** \brief DMA ������ɱ�־ */
am_local volatile am_bool_t __g_trans_adone;
am_local volatile am_bool_t __g_trans_bdone;

/** \brief DMA ��������� */
am_local am_lpc84x_dma_controller_t *__gp_dma_ctr = NULL;

/**
 * \brief DMA �жϷ������
 *
 * \param[in] p_arg �û��Զ��������ͨ�� am_lpc84x_dma_xfer_desc_startup() ��������
 * \param[in] state DMA �ж�״̬��־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                  (#AM_LPC84X_DMA_STAT_INTERR)��(#AM_LPC84X_DMA_STAT_INTA)��
 *                  (#AM_LPC84X_DMA_STAT_INTB)�������ǵĻ�ֵ���
 *
 * \return ��
 */
am_local void __dma_isr (void *p_arg, int state)
{
    if (state & AM_LPC84X_DMA_STAT_INTERR) {

        /* ���䷢������ */
        return;
    }

    if ((state & AM_LPC84X_DMA_STAT_INTA) &&
        (state & AM_LPC84X_DMA_STAT_INTB)) {

        /* �����ʹ��� */
        /* �û��轵�Ͳ����� */
    } else if (state & AM_LPC84X_DMA_STAT_INTA) {

        /* DMA������� */
        __g_trans_adone = AM_TRUE;
    } else if (state & AM_LPC84X_DMA_STAT_INTB) {
        __g_trans_bdone = AM_TRUE;
    }
}

/**
 * \brief ADC ʹ�� DMA ģʽʱ��������
 */
am_local void __adc_dma_startup (am_lpc84x_dma_controller_t *p_dma_ctr)
{
    uint32_t dma_aflags = 0;
    uint32_t dma_bflags = 0;

    p_dma_ctr = am_lpc84x_dma_controller_get(
                    DMA_CHAN_0,
                    DMA_CHAN_OPT_PRIO_1           |         /* ͨ�����ȼ�Ϊ 1 */
                    DMA_CHAN_OPT_HWTRIG_MODE_RISE |         /* �����ش��� */
                    DMA_CHAN_OPT_HWTRIG_BURST_EN  |         /* ʹ��ͻ��ģʽ */
                    DMA_CHAN_OPT_HWTRIG_BURST_1   |         /* ͻ�������СΪ 1 */
                    DMA_CHAN_OPT_HWTRIG_SRC_ADC0_SEQA_IRQ); /* ADC0 ���� A �жϴ��� DMA ���� */

    if (p_dma_ctr == NULL) {
        AM_DBG_INFO("Geting a Controller Faild !\r\n");
        AM_FOREVER {};
    }

    /* DMA �������� */
    dma_aflags = AM_LPC84X_DMA_XFER_VALID        |  /* ��ǰͨ����������Ч */
                 AM_LPC84X_DMA_XFER_RELOAD       |  /* �����������ͨ�������� */
                 AM_LPC84X_DMA_XFER_WIDTH_32BIT  |  /* �������ݿ�ȣ�32 λ */
                 AM_LPC84X_DMA_XFER_SRCINC_NOINC |  /* Դ�����ݵ�ַ������ */
                 AM_LPC84X_DMA_XFER_DSTINC_1X    |  /* Ŀ���ַ�� 1x ��ȵ��� */
                 AM_LPC84X_DMA_XFER_SETINTA;        /* ʹ���ж� A */

    /* DMA �������� */
    dma_bflags = AM_LPC84X_DMA_XFER_VALID        |  /* ��ǰͨ����������Ч */
                 AM_LPC84X_DMA_XFER_RELOAD       |  /* ����������ͨ�������� */
                 AM_LPC84X_DMA_XFER_WIDTH_32BIT  |  /* �������ݿ�ȣ�32 λ */
                 AM_LPC84X_DMA_XFER_SRCINC_NOINC |  /* Դ�����ݵ�ַ������ */
                 AM_LPC84X_DMA_XFER_DSTINC_1X    |  /* Ŀ���ַ�� 1x ��ȵ��� */
                 AM_LPC84X_DMA_XFER_SETINTB;        /* ʹ���ж� B */

    /* ����ͨ�������� A */
    am_lpc84x_dma_xfer_desc_build(
       &__g_desc[0],                         /* A ������������ */
        (uint32_t)(&LPC84X_ADC0->dat0), /* Դ�����ݵ�ַ */
        (uint32_t)&__g_adc_abuf[0],          /* A ��Ŀ��˵�ַ */
        (__ADC_BUF_LEN << 2),                /* �����ֽ��� */
        dma_aflags);                         /* �������� */

    /* ����ͨ�������� B */
    am_lpc84x_dma_xfer_desc_build(
       &__g_desc[1],                         /* B ������������ */
        (uint32_t)(&LPC84X_ADC0->dat0), /* Դ�����ݵ�ַ */
        (uint32_t)&__g_adc_bbuf[0],          /* B ��Ŀ��˵�ַ */
        (__ADC_BUF_LEN << 2),                /* �����ֽ��� */
        dma_bflags);                         /* �������� */

    /* �������������� */
    am_lpc84x_dma_xfer_desc_link(&__g_desc[1], &__g_desc[0]);
    am_lpc84x_dma_xfer_desc_link(&__g_desc[0], &__g_desc[1]);

    /* ���� DMA ���䣬���Ͽ�ʼ���� */
    am_lpc84x_dma_xfer_desc_startup(p_dma_ctr,
                                   &__g_desc[0],
                                    __dma_isr,
                                    (void *)0);
}

/**
 * \brief ADC ���ã�ͨ�� HW �㺯���ӿ�ʵ��
 */
am_local void __adc_config (amhw_lpc84x_adc_t *p_hw_adc, int ch)
{
    uint32_t seq_flags = 0;

    /* ʹ������ A �ж� */
    amhw_lpc84x_adc_int_enable(p_hw_adc,
                               AMHW_LPC84X_ADC_INTEN_SEQA_ENABLE);

    /* ʹ������ A ת�� */
    amhw_lpc84x_adc_seq_enable(p_hw_adc, AMHW_LPC84X_ADC_SEQ_A);

    /* 256 ��Ƶ */
    amhw_lpc84x_adc_clkdiv_set(p_hw_adc, 256 - 1);

    /* ���� DMA ����ʱ��NVIC �� ADC ��Ӧ���жϱ���ر� */
    am_int_disable(INUM_ADC0_SEQA);

    seq_flags = AMHW_LPC84X_ADC_SEQ_CTRL_MODE_BURST   | /* ����ͻ��ת��ģʽ */
                AMHW_LPC84X_ADC_SEQ_CTRL_TRIG_POL_POS | /* �Ƽ�ʹ�������ش�����ʽ */
                AMHW_LPC84X_ADC_SEQ_CTRL_MODE_EOS     | /* ����ת����ɺ󴥷� DMA */
                AMHW_LPC84X_ADC_SEQ_CTRL_ENA          | /* ���� A ʹ�� */
                AMHW_LPC84X_ADC_SEQ_CTRL_ENABLE_CH(ch); /* ʹ�� ADC ͨ�� */

    /* ADC ���� A ���� */
    amhw_lpc84x_adc_seq_config(p_hw_adc,
                               AMHW_LPC84X_ADC_SEQ_A,
                               seq_flags);
}

void demo_lpc845_hw_adc_dma_entry(amhw_lpc84x_adc_t *p_hw_adc,
                                  int                ch,
                                  uint32_t        vref_mv)
{
    int i = 0;
  
    /* ���� DMA ���䣬������Ҫ������ DMA�������� ADC */
    __adc_dma_startup(__gp_dma_ctr);

    /* ADC ���� */
    __adc_config(p_hw_adc, ch);

    AM_FOREVER {
        if (__g_trans_adone) {
            __g_trans_adone =  AM_FALSE;

            for (i = 0; i < 100; i++) {

                /* �������������ѹ */
                AM_DBG_INFO("The buffer A conversion %2d: %4d mV \r\n",
                            i,
                            AMHW_LPC84X_ADC_DR_RESULT(__g_adc_abuf[i]) *
                            2500 / ((1 << 12) - 1));
            }
            am_mdelay(50);
        }

        if (__g_trans_bdone) {
            __g_trans_bdone =  AM_FALSE;

            for (i = 0; i < 100; i++) {

                /* �������������ѹ */
                AM_DBG_INFO("The buffer B conversion %2d: %4d mV \r\n",
                            i,
                            AMHW_LPC84X_ADC_DR_RESULT(__g_adc_bbuf[i]) *
                            vref_mv / ((1 << 12) - 1));
            }
            am_mdelay(50);
        }
    }
}

/** [src_lpc824_hw_adc_dma] */

/* end of file */
