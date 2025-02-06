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
 * \brief book`s mvc.h file
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-26  ipk, first implementation
 * \endinternal
 */
#ifndef __MVC_H
#define __MVC_H

#include "ametal.h"
#include "slist.h"

struct _model;
struct _observer;


typedef void (*update_view_t)(struct _observer *p_this, struct _model *p_model);

typedef struct _observer{
	slist_node_t	node;
	update_view_t	pfn_update_view;
} observer_t;

typedef struct _model{
	slist_head_t  head;
} model_t;

// ��ͼ��ʼ��
int view_init(observer_t *p_this,update_view_t pfn_update_view);

// ģ�ͳ�ʼ��
int model_init(model_t *p_this);

// �����ͼ
int model_attach(model_t *p_this, observer_t *p_observer);

// ɾ����ͼ
int model_detach(model_t *p_this, observer_t *p_observer);

// ֪ͨ��������ͼ
int model_notify(model_t *p_this);


#endif /* __MVC_H */
/* end of file */
