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
 * \brief MiniPort-ZLG72128 �û������ļ�
 * \sa am_hwconf_miniport_zlg72128.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-21  adw, first implementation
 * \endinternal
 */
 
#include "ametal.h"
#include "am_lpc82x_inst_init.h"
#include "lpc82x_pin.h"
#include "am_zlg72128.h"

/**
 * \addtogroup am_if_src_hwconf_miniport_zlg72128
 * \copydoc am_hwconf_miniport_zlg72128.c
 * @{
 */
 
static am_zlg72128_dev_t     __g_zlg72128_dev;        // ����һ�� ZLG72128 ʵ��

static const am_zlg72128_devinfo_t __g_zlg72128_devinfo = {
    PIO0_6,      // ��λ����
    AM_TRUE,     // ͨ������£�����ʹ���ж�����
    PIO0_1,      // ZLG72128��KEY_INT������LPC824��PIO0_17����
    5            // ʹ���ж�����ʱ����ֵ�����塣����ʹ���ж����ţ���������Ϊ5����ѯ���Ϊ5ms
};

am_zlg72128_handle_t am_zlg72128_inst_init (void)
{
    am_i2c_handle_t i2c_handle = am_lpc82x_i2c2_inst_init();
    return am_zlg72128_init(&__g_zlg72128_dev, &__g_zlg72128_devinfo, i2c_handle);
}

/**
 * @}
 */

/* end of file */
