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
 * \brief �����嵥6.104
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

static void __zlg600_callback (void *p_arg) 
{
	// ���ûص�����ʱ��p_arg��ֵ����Ϊ detect_flag �ĵ�ַ�����p_argʵ���Ͼ���ָ��
	// detect_flag��ָ�룬���Խ���ת��Ϊuint8_t *���͵�ָ�룬�����޸�detect_flag��ֵΪ1
	 *(uint8_t *)p_arg = 1;
}

int am_main(void)
{
    	uint8_t 			detect_flag 	= 0;
    	am_zlg600_handle_t 	zlg600_handle 	= am_zlg600_uart_inst_init();
    	am_zlg600_mifare_card_auto_detect_cb_set(zlg600_handle, __zlg600_callback, &detect_flag);  	
	    // p_arg��ֵ����Ϊdetect_flag�ĵ�ַ
	
      return 0;
}
/* end of file */
