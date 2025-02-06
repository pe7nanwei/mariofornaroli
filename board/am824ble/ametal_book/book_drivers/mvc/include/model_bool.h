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
 * \brief book`s model_bool driver for AM824
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-26  ipk, first implementation
 * \endinternal
 */
#ifndef __MODEL_BOOL_H__
#define __MODEL_BOOL_H__

#include "ametal.h"
#include "mvc.h"

//����model_bool_tģ����
typedef struct _model_bool{
    model_t         isa;
    am_bool_t       value;                    // boolģ�͵�����
}model_bool_t;


int model_bool_init (model_bool_t *p_this, am_bool_t init_value);  // ģ�ͳ�ʼ��
int model_bool_set (model_bool_t *p_this, am_bool_t value);        // ����ģ�͵�valueֵ
int model_bool_get (model_bool_t *p_this, am_bool_t *p_value);     // ��ȡģ�͵�valueֵ



#endif /* __MODEL_BOOL_H__ */
/* end of file */
