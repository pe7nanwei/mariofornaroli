


#pragma once
#include "ametal.h"
#include "mvc.h"

typedef struct _view_digitron { 
    observer_t  	isa;        				// ��������
    int      		digitron_id;  				// �������ʾ��ID��
} view_digitron_temp_t;

typedef struct _view_digitron {
	observer_t   		isa;
	int           		digitron_id;  	// �������ʾ��ID��
} view_digitron_t;


//  �������ͼ��ʼ��
int view_digitron_init (view_digitron_t *p_view_digitron, int digitron_id);
