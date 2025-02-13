#pragma once
#include "ametal.h"
#include "mvc.h"

// ����ģ��״̬
#define MODEL_TEMP_MONITOR_STATUS_NORMAL	0   // �¶�����
#define MODEL_TEMP_MONITOR_STATUS_UPPER		1   // ���������¶�ֵ
#define MODEL_TEMP_MONITOR_STATUS_LOWER	  2   // ���������¶�ֵ

// �����¶ȼ��ģ������
typedef struct _model_temp_monitor {
	model_t   isa;          					  // model��������
	int       status;         			    // ��ǰ�¶�״̬
	float		  temp_cur;      				    // ��ǰ�¶�ֵ
	float     temp_max;      				    // �����¶�ֵ
	float		  temp_min;      				    // �����¶�ֵ
} model_temp_monitor_t; 

int model_temp_monitor_init (model_temp_monitor_t *p_model, float max, float min, float cur);

int model_temp_monitor_cur_set (model_temp_monitor_t *p_model, float value);
int model_temp_monitor_max_set (model_temp_monitor_t *p_model, float value);
int model_temp_monitor_min_set (model_temp_monitor_t *p_model, float value);
int model_temp_monitor_cur_get (model_temp_monitor_t *p_model, float *p_value);
int model_temp_monitor_max_get (model_temp_monitor_t *p_model, float *p_value);
int model_temp_monitor_min_get (model_temp_monitor_t *p_model, float *p_value);
int model_temp_monitor_status_get(model_temp_monitor_t *p_model);
