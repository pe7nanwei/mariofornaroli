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
 * \brief ZMF159 DMA �û������ļ�
 * \sa am_hwconf_zmf159_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "am_clk.h"
#include "am_zmf159.h"
#include "am_zlg_dma.h"
/**
 * \addtogroup am_if_src_hwconf_zmf159_dma
 * \copydoc am_hwconf_zmf159_dma.c
 * @{
 */

/**
 * \brief DMA1 ƽ̨��ʼ����
 */
static void __zmf159_plfm_dma1_init (void)
{
    am_clk_enable(CLK_DMA1);
}

/**
 * \brief DMA1 ƽ̨ȥ��ʼ����
 */
static void __zmf159_plfm_dma1_deinit (void)
{
    am_clk_disable(CLK_DMA1);
}

/** \brief DMA1 �豸��Ϣ */
static const am_zlg_dma_devinfo_t __g_dma1_devinfo = {
    ZMF159_DMA1_BASE,          /**< \brief ָ��DMA1�Ĵ������ָ�� */
    INUM_DMA1_1,               /**< \brief DMA�ж������ſ�ʼ */
    INUM_DMA1_7,               /**< \brief DMA�ж������Ž��� */
    __zmf159_plfm_dma1_init,   /**< \brief DMAƽ̨��ʼ�� */
    __zmf159_plfm_dma1_deinit  /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA1�豸ʵ�� */
static am_zlg_dma_dev_t __g_dma1_dev;

/**
 * \brief DMA1 ʵ����ʼ��
 * \return ��
 */
int am_zmf159_dma1_inst_init (void)
{
    return am_zlg_dma_init(&__g_dma1_dev, &__g_dma1_devinfo);
}

/**
 * \brief DMA1 ʵ�����ʼ��
 * \return ��
 */
void am_zmf159_dma1_inst_deinit (void)
{
    am_zlg_dma_deinit();
}

/*******************************************************************************/

/**
 * \brief DMA2 ƽ̨��ʼ����
 */
static void __zmf159_plfm_dma2_init (void)
{
    am_clk_enable(CLK_DMA2);
}

/**
 * \brief DMA2 ƽ̨ȥ��ʼ����
 */
static void __zmf159_plfm_dma2_deinit (void)
{
    am_clk_disable(CLK_DMA2);
}

/** \brief DMA2 �豸��Ϣ */
static const am_zlg_dma_devinfo_t __g_dma2_devinfo = {
    ZMF159_DMA2_BASE,          /**< \brief ָ��DMA2�Ĵ������ָ�� */
    INUM_DMA2_1,               /**< \brief DMA�ж������ſ�ʼ */
    INUM_DMA2_5,               /**< \brief DMA�ж������Ž��� */
    __zmf159_plfm_dma2_init,   /**< \brief DMAƽ̨��ʼ�� */
    __zmf159_plfm_dma2_deinit  /**< \brief DMAƽ̨���ʼ�� */
};

/** \brief DMA2�豸ʵ�� */
static am_zlg_dma_dev_t __g_dma2_dev;

/**
 * \brief DMA2 ʵ����ʼ��
 * \return ��
 */
int am_zmf159_dma2_inst_init (void)
{
    return am_zlg_dma_init(&__g_dma2_dev, &__g_dma2_devinfo);
}

/**
 * \brief DMA2 ʵ�����ʼ��
 * \return ��
 */
void am_zmf159_dma2_inst_deinit (void)
{
    am_zlg_dma_deinit();
}

/**
 * @}
 */

/* end of file */
