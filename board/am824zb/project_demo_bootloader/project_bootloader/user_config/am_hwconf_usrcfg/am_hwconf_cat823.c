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
 * \brief CAT823 WDT �û������ļ�
 * \sa am_hwconf_cat823.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-04-28  ipk, first implementation.
 * \endinternal
 */

#include "am_lpc82x.h"
#include "am_cat823.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_cat823
 * \copydoc am_hwconf_cat823.c
 * @{
 */

/** \brief WDT �豸��Ϣ */
static const am_cat823_devinfo_t  __g_wdt_devinfo = {
    PIO0_22,                /* CAT823 WDI ���� */
};

/** \brief WDT�豸ʵ�� */
static am_cat823_dev_t __g_wdt_dev;

/**
 * \brief  WDT ʵ����ʼ�������WDT��׼������
 */
am_wdt_handle_t am_cat823_inst_init (void)
{
    return am_cat823_init(&__g_wdt_dev, &__g_wdt_devinfo);
}

/**
 * \brief WDT ʵ�����ʼ��
 */
void am_cat823_inst_deinit (am_wdt_handle_t handle)
{
    am_cat823_deinit((am_cat823_dev_t *)handle);
}

/**
 * @}
 */

/* end of file */
