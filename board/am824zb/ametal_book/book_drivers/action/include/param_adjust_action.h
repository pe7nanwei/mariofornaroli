#ifndef __PARAM_ADJUST_ACTION_H__
#define __PARAM_ADJUST_ACTION_H__

#include "am_softimer.h"
#include "model_temp_monitor.h"
#include "view_digitron.h"

typedef struct _param_adjust_action {
    int                      led0_id;     	// LED0��ID��
    int                      led1_id;     	// LED1��ID��
    am_softimer_t            timer;       	// ����LED��˸�������ʱ��
    model_temp_monitor_t		*p_model;  	    // �¶�ģ��
    view_digitron_t       	*p_view;    	  // �¶�ģ�͵��������ͼ
    int                      digitron_id; 	// �������ʾ�����
    uint32_t                 adj_val;     	// ��ǰ���ڵ�ֵ
    uint8_t                  adj_pos;     	// ����״̬�µĵ���λ�ã���λ��ʮλ......
} param_adjust_action_t;

	
int param_adjust_action_init (param_adjust_action_t 	*p_this,
                              model_temp_monitor_t  	*p_model,
                              view_digitron_t			    *p_model_view,
                              int                      led0_id,
                              int                      led1_id,
                              int                      digitron_id);

void param_adjust_action_min_start (param_adjust_action_t *p_this);
void param_adjust_action_normal_start(param_adjust_action_t *p_this);
void param_adjust_action_normal_stop(param_adjust_action_t *p_this);
void param_adjust_action_min_stop(param_adjust_action_t *p_this);
void param_adjust_action_max_start(param_adjust_action_t *p_this);															
void param_adjust_action_max_stop(param_adjust_action_t *p_this);														
void param_adjust_action_inc(param_adjust_action_t *p_this);														
void param_adjust_action_lr(param_adjust_action_t *p_this);	
void param_adjust_action_dec(param_adjust_action_t *p_this);
															
#endif
