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
 * \brief LPC84X bootloader����
 *
 * - �������裺
 *   �ο�AMmetal-AM845-Core-bootloader�����ֲ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "demo_am845_core_entries.h"

/**
 * \brief AMetal Ӧ�ó������
 */
void am_main (void) 
{ 

   demo_am845_core_bootloader_entry();

}

/* end of file */
