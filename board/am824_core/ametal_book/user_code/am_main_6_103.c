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
 * \brief �����嵥6.103
 *
 * \note ��������Ҫ�õ��������⣬hash table
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-25  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_zlg600.h"
#include "am_hwconf_zlg600.h"
uint8_t g_key[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int am_main (void)
{
    	am_zlg600_handle_t zlg600_handle = am_zlg600_uart_inst_init();
    
    	am_zlg600_ic_key_load (
		zlg600_handle,
		AM_ZLG600_IC_KEY_TYPE_A,		// ���α������A����Կ
		0,								// ����������Ϊ0������
		g_key,							// ���������Կ
		6);								// ��Կ����6�ֽ�
	while (1) {
	}
}

/* end of file */
