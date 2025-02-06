#ifndef __PARAM_ADJUST_SM_H__
#define __PARAM_ADJUST_SM_H__

#include "ametal.h"
#include "am_softimer.h"
#include "model_temp_monitor.h"
#include "view_digitron.h"
#include "param_adjust_action.h"

#define PARAM_ADJUST_NUM  2

struct _adjust_state;
typedef struct _adjust_state adjust_state_t;
		 
// �����������״̬��
typedef struct _param_adjust_sm {
	const struct _adjust_state 	*p_state;      			// ��ǰ״̬
	param_adjust_action_t     *p_action;        		// ������
} param_adjust_sm_t;

typedef void (*event_handle_t) (param_adjust_sm_t *p_this);

typedef struct _adjust_state {
	event_handle_t  pfn_entry;						  // ���붯��
	event_handle_t  pfn_event_set;					// SET�¼�������
	event_handle_t  pfn_event_inc;					// ��1�¼�������
	event_handle_t  pfn_event_lr;					  // ����/�����¼�������
	event_handle_t  pfn_event_dec;					// ��1�¼�������
	event_handle_t  pfn_exit;						    // �˳�����
} adjust_state_t;


// ״̬����ʼ��
int param_adjust_sm_init (param_adjust_sm_t *p_this,param_adjust_action_t *p_action);

int param_adjust_sm_event_key_set (param_adjust_sm_t *p_this);			// SET������
int param_adjust_sm_event_key_lr  (param_adjust_sm_t *p_this);			// L/R������
int param_adjust_sm_event_key_inc (param_adjust_sm_t *p_this);			// �Ӽ�����
int param_adjust_sm_event_key_dec (param_adjust_sm_t *p_this);			// ��������
		 
	 
#endif
