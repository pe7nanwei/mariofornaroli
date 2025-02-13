/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief book`s app_ble_led_control driver for AM824
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-12  adw, first implementation.
 * \endinternal
 */
 
#include "ametal.h"
#include "model_temp_monitor.h"

static void __update_status (model_temp_monitor_t *p_model) 
{
	if (p_model->temp_cur > p_model->temp_max) {
		p_model->status = MODEL_TEMP_MONITOR_STATUS_UPPER;
	} else if (p_model->temp_cur < p_model->temp_min) {
		p_model->status = MODEL_TEMP_MONITOR_STATUS_LOWER;
	} else {
		p_model->status = MODEL_TEMP_MONITOR_STATUS_NORMAL;
	}
}


int model_temp_monitor_init (model_temp_monitor_t *p_model, float min, float max, float cur)
{
	if (p_model == NULL) {
		return -1;
	}
	if (min > max) {
		return -1;
	}
	model_init(&(p_model->isa));
	p_model->temp_max = max;
	p_model->temp_min = min;
	p_model->temp_cur = cur;
	__update_status(p_model);    			// ���ݳ�ʼֵ����״ֵ̬����ʼ��״ֵ̬
	return 0;
}

int model_temp_monitor_cur_set(model_temp_monitor_t *p_model, float value)
{
	if (p_model == NULL) {
		return -1;
	}
	if (p_model->temp_cur != value){
		p_model->temp_cur = value;
       	    	__update_status(p_model);          		// ����״̬
          	model_notify((model_t *)p_model);  		// ֪ͨ������ͼ
	}
	return 0;
}

int model_temp_monitor_max_set (model_temp_monitor_t *p_model, float value)
{
	if ((p_model == NULL) || (value < p_model->temp_min)) {
		return -1;
	}
	if (p_model->temp_max != value) {
		p_model->temp_max = value;
     		__update_status(p_model);          			// ����״̬
     		model_notify((model_t *)p_model);  			// ֪ͨ������ͼ
	}
	return 0;
}



int model_temp_monitor_min_set (model_temp_monitor_t *p_model, float value)
{
	if ((p_model == NULL) || (value > p_model->temp_max)) {
		return -1;
	}
	if (p_model->temp_min != value) {
		p_model->temp_min = value;
     		__update_status(p_model);          			// ����״̬
     		model_notify((model_t *)p_model);  			// ֪ͨ������ͼ
	}
	return 0;
}

int model_temp_monitor_cur_get (model_temp_monitor_t *p_model, float *p_value)
{
	if ((p_model == NULL) || (p_value == NULL)) {
		return -1;
	}
	*p_value = p_model->temp_cur;
	return 0;
}



int model_temp_monitor_max_get (model_temp_monitor_t *p_model, float *p_value)
{
	if ((p_model == NULL) || (p_value == NULL)) {
		return -1;
	}
	*p_value = p_model->temp_max;
	return 0;
}


int model_temp_monitor_min_get (model_temp_monitor_t *p_model, float *p_value)
{
	if ((p_model == NULL) || (p_value == NULL)) {
		return -1;
	}
	*p_value = p_model->temp_min;
	return 0;
}

int model_temp_monitor_status_get (model_temp_monitor_t *p_model)
{
	if (p_model == NULL){
		return -1;
	}
	return p_model->status;
}






















