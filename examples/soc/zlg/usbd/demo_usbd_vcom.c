/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB printer_counter ����
 *
 * - ʵ������
 * 1.��USB ���µ� DN ��AM227_core �� ������PA11, DP��core ��PA12�� ��USB����˵����PC����
 * 2.��������¼�����̣��ȴ�3��(��������3����ʱ��Ϊ��ģ��USB�γ�����)��3���pc������ʾ��װ������
 *   ����Ĭ�ϰ�װwindows ͨ�ô�ӡ����������ϸ�ɿ�������װ˵���ĵ�������û���Ҫ���Լ����������������и��¡�
 * 3.�ڵ��������½�һ��txt�ļ��������ַ���,֮�����ļ���ӡ�����ڴ����п��Կ����ļ�����.
 *
 * \par Դ����
 * \snippet demo_usbd_printer.c src_usbd_printer
 *
 * \internal
 * \par Modification History
 * - 1.00 19-1-09  adw, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usbd_printer
 * \copydoc demo_usbd_printer.c
 */

/** [src_usbd_printer] */
#include "ametal.h"
#include "string.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_rngbuf.h"
#include "am_vdebug.h"
#include "am_softimer.h"
#include "am_zmf159_usbd.h"
#include "am_zmf159_inst_init.h"
#include "am_zmf159_usbd.h"
#include "am_usbd_cdc_vcom.h"

extern am_usbd_cdc_vcom_handle am_zmf159_usbd_vcom_inst_init (void);

/**
 * \brief �������
 */
void demo_zmf159_usbd_vcom_entry (void)
{
    am_kprintf("zmf159 vcom demo \r\n");

    am_usbd_cdc_vcom_handle handle = am_zmf159_usbd_vcom_inst_init();

    for (;;){
    	am_mdelay(1000);

    	am_usbd_cdc_vcom_send(handle, (uint8_t *)"1234", sizeof("1234"));
    }

}
/** [src_usbd_printer] */

/* end of file */
