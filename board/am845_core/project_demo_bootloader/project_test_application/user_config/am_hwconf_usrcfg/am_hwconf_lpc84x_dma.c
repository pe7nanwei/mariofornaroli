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
 * \brief LPC84X DMA �û������ļ�
 * \sa am_hwconf_lpc84x_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-08  mem,modified
 * - 1.00 15-07-12  win, first implementation
 * \endinternal
 */

#include <am_lpc84x.h>
#include "ametal.h"
#include "am_lpc84x_dma.h"
#include "hw/amhw_lpc84x_dma.h"
#include "hw/amhw_lpc84x_clk.h"

/**
 * \addtogroup am_if_src_hwconf_lpc84x_dma
 * \copydoc am_hwconf_lpc84x_dma.c
 * @{
 */

/**
 * \brief ʹ�õ� DMA ͨ������
 *
 * Ĭ��ʹ�����е� DMA ͨ�����û����Ը���ʵ��ʹ��ͨ���������Ĵ�ֵ������ DMA �ڴ��ռ��
 *
 * \note �����Ҫʹ�� DMA�����ֵ����Ӧ��Ϊ 1������ DMA ��ʼ�����ɹ�
 */
#define __DMA_CHAN_USE_COUNT    AMHW_LPC84X_DMA_CHAN_CNT

/**
 * \brief DMA ƽ̨��ʼ��
 */
am_local void __lpc84x_dma_plfm_init (void)
{

    amhw_lpc84x_syscon_periph_reset(AMHW_LPC84X_RESET_DMA);
    amhw_lpc84x_clk_periph_enable(AMHW_LPC84X_CLK_DMA);
}

/**
 * \brief DMA ƽ̨���ʼ��
 */
am_local void __lpc84x_dma_plfm_deinit (void)
{
    amhw_lpc84x_clk_periph_disable(AMHW_LPC84X_CLK_DMA);
}

/** \brief ������ӳ��� */
am_local uint8_t __g_dam_controller_map[AMHW_LPC84X_DMA_CHAN_CNT];

/** \brief �������ڴ� */
am_local am_lpc84x_dma_controller_t __g_dma_controller[__DMA_CHAN_USE_COUNT];

/** \brief DMA ͨ���������б����� 512 �ֽڶ��� */
am_local __attribute__((aligned(512)))
am_lpc84x_dma_xfer_desc_t __g_dma_xfer_tab[AMHW_LPC84X_DMA_CHAN_CNT];

/** \brief DMA �豸��Ϣ */
am_local am_const am_lpc84x_dma_devinfo_t __g_lpc84x_dma_devinfo = {
    LPC84X_DMA_BASE,               /* DMA �Ĵ������ַ */
    LPC84X_INMUX_BASE,             /* INMUX �Ĵ������ַ */
    &__g_dam_controller_map[0],    /* ָ�������ӳ����ָ�� */
    &__g_dma_controller[0],        /* ָ��������ڴ��ָ�� */
    &__g_dma_xfer_tab[0],          /* ��������������ַ��512 �ֽڶ��� */
    __DMA_CHAN_USE_COUNT,          /* ʹ�õ� DMA ͨ������ */
    INUM_DMA,                      /* DMA �жϺ� */
    __lpc84x_dma_plfm_init,        /* ƽ̨��ʼ������ */
    __lpc84x_dma_plfm_deinit,      /* ƽ̨���ʼ������ */
};

/** \brief DMA �豸ʵ�� */
am_local am_lpc84x_dma_dev_t __g_lpc84x_dma_dev;

/**
 * \brief DMA ʵ����ʼ��
 */
int am_lpc84x_dma_inst_init (void)
{
    return am_lpc84x_dma_init(&__g_lpc84x_dma_dev, &__g_lpc84x_dma_devinfo);
}

/**
 * \brief DMA ʵ�����ʼ��
 */
void am_lpc84x_dma_inst_deinit (void)
{
    am_lpc84x_dma_deinit();
}

/**
 * @}
 */

/* end of file */
