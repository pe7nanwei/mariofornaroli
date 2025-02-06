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
 * \brief �����嵥 9.61
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-26  ipk, first implementation
 * \endinternal
 */
#include "mvc.h"

static void view_update(observer_t *p_view, struct _model *p_model)	// ��ͼ��ʾ����
{
	// ...
}

int am_main(void)
{
	observer_t	view;
	model_t  	  model;
	
	view_init(&view, view_update);
	model_init(&model);
	model_attach(&model, &view); 
	
  while (1){
  // ״̬�仯��֪ͨ������ͼ
  	model_notify(&model);
  // ...
  }
}
/* end of file */
