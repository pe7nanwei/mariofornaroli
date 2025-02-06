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
 * \brief �����嵥5.64   �ó�����û���κ�Ч����
 *
 * 
 * \internal
 * \par Modification history
 * - 1.00 18-09-17  adw, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_spi.h"

static void __spi_msg_complete_callback (void *p_arg)
{
    // ��Ϣ�������
}

int am_main(void)
{
    am_spi_message_t   spi_msg;           // ����һ��SPI��Ϣ�ṹ��

    am_spi_msg_init (                     
        &spi_msg,                         
        __spi_msg_complete_callback,      // ��Ϣ������ɻص�����
        NULL);                            // δʹ�ûص������Ĳ���p_arg������ΪNULL
    return 0;
}



/* end of file */

