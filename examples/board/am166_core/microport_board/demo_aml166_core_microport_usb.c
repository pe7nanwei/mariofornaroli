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
 * \brief MicroPort USB(XR21V141x) ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. �� MicroPort USB ������ӵ� aml166-Core �� MicroPort �ӿڣ�
 *   2. ��  MicroPort USB ����ϵ� USB �ӿ��� PC ���Ӳ�ͨ���������ִ򿪡�
 *
 * - ʵ������
 *   1. �������"MicroPort USB Test:"��
 *   2. ����������յ����ַ�����
 *
 * \note
 *   1. XR21V141x Ϊ USB ת����оƬ��ʹ��ǰ��Ҫ��װ���������û������� EXAR
 *      �ٷ���վ(http://www.exarcorp.cn/design-tools/software-drivers)���أ�
 *   2. ����ʹ�� USART0���� DEBUG ����ʹ�ô�����ͬ��
 *
 * \par Դ����
 * \snippet demo_aml166_core_microport_usb.c src_aml166_core_microport_usb
 *
 * \internal
 * \par Modification History
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_aml166_core_microport_usb
 * \copydoc demo_aml166_core_microport_usb.c
 */

/** [src_aml166_core_microport_usb] */
#include <am_aml166_inst_init.h>
#include "ametal.h"
#include "am_vdebug.h"
#include "demo_std_entries.h"
#include "demo_aml166_core_entries.h"

/**
 * \brief �������
 */
void demo_aml166_core_microport_usb_entry (void)
{
    AM_DBG_INFO("demo aml166_core microport usb!\r\n");

    demo_std_uart_polling_entry(am_zlg116_uart1_inst_init());
}
/** [src_aml166_core_microport_usb] */

/* end of file */
