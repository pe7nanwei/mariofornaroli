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
 * \brief ZMF159 IWDG �û������ļ�
 * \sa am_hwconf_zmf159_iwdg.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-24  zcb, first implementation
 * \endinternal
 */

#include "am_zlg_iwdg.h"
#include "am_zmf159.h"
#include "hw/amhw_zmf159_rcc.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_iwdg
 * \copydoc am_hwconf_zmf159_iwdg.c
 * @{
 */

/** \brief IDWG ƽ̨��ʼ�� */
static void __zmf159_iwdg_plfm_init (void)
{

    /* ��鸴λ�Ƿ��ɿ��Ź���ɵ� */
    if (amhw_zmf159_rcc_reset_flag() & AMHW_ZMF159_RCC_CSR_IWDGRSTF) {
        amhw_zmf159_rcc_reset_flag_clear();
    }

    amhw_zmf159_rcc_lsi_enable();

    while (amhw_zmf159_rcc_lsirdy_read() == AM_FALSE);
}

/** \brief ��� IWDG ƽ̨��ʼ�� */
static void __zmf159_iwdg_plfm_deinit (void)
{
}

/** \brief IWDG �豸��Ϣ */
static const am_zlg_iwdg_devinfo_t __g_iwdg_devinfo = {
    ZMF159_IWDG_BASE,           /**< \brief IWDG �Ĵ�����ַ */
    __zmf159_iwdg_plfm_init,    /**< \brief IWDG ƽ̨��ʼ�� */
    __zmf159_iwdg_plfm_deinit,  /**< \brief ���IWDG ƽ̨��ʼ�� */
};

/** \brief IWDG�豸ʵ�� */
static am_zlg_iwdg_dev_t __g_iwdg_dev;

/**
 * \brief IWDG ʵ����ʼ�������IWDG��׼������
 */
am_wdt_handle_t am_zmf159_iwdg_inst_init (void)
{
    return am_zlg_iwdg_init(&__g_iwdg_dev, &__g_iwdg_devinfo);
}

/**
 * \brief IWDG ʵ�����ʼ��
 */
void am_zmf159_iwdg_inst_deinit (am_wdt_handle_t handle)
{
    am_zlg_iwdg_deinit(handle);
}

/**
 * @}
 */

/* end of file */
