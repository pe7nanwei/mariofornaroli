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
 * \brief Miniport-595 �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-13  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_HWCONF_ZSN60X_I2C_H
#define __AM_HWCONF_ZSN60X_I2C_H

#include "ametal.h"
#include "zsn60x.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief ZSN60x (I2C ģʽ) ʵ����ʼ��
 *
 * \retval  handle  ��ʼ���ɹ�
 * \retval  NULL    ��ʼ��ʧ��
 */
zsn60x_handle_t  am_zsn60x_i2c_inst_init (void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
