/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief FM175xx LPCDģʽ
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *
 * - ʵ������
 *   1. ��ִ�в�������1 2�� ��󿨽���͹����Զ���Ƭ��⣨LPCD��ģʽ
 *   2. �������ø�Ӧ����FM175xx�豸�������������жϱ�־��ִ����Ӧ�趨������
 *   3. �ƿ���Ƭ�󣬴ﵽ�趨��AUTO_WUP_TIME��ʱ��ʱ��FM175xx�Զ��˳�LPCDģʽ���Զ����е�У��
 *
 * \par Դ����
 * \snippet demo_amks16rfid8_m175xx_picca_lpcd_mode.c demo_amks16rfid8_fm175xx_picca_lpcd_mode
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-20  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16rfid8_fm175xx_picca_lpcd_mode
 * \copydoc demo_amks16rfid8_fm175xx_picca_lpcd_mode.c
 */

/** [src_demo_amks16rfid8_fm175xx_picca_lpcd_mode] */

#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"
#include "kl26_pin.h"
#include "am_kl26_inst_init.h"
#include "am_fm175xx_ant.h"
#include "am_hwconf_fm175xx.h"
#include "demo_components_entries.h"
#include "demo_amks16rfid8_entries.h"

/**
 * \name ����CD4051������
 * @{
 */
#define __CD4051_PIN_EN PIOB_19
#define __CD4051_PIN_S2 PIOB_18
#define __CD4051_PIN_S1 PIOB_17
#define __CD4051_PIN_S0 PIOB_16

/* ���� fm175xx �����л���Ϣ */
static am_antenna_info_t  __g_antenna_info = {
    {
        __CD4051_PIN_EN,
        __CD4051_PIN_S0,
        __CD4051_PIN_S1,
        __CD4051_PIN_S2
    },
    AM_FM175XX_ANTENNA_EIGHT
};

/**
 * \brief LPCDģʽ
 */
void demo_amks16rfid8_fm175xx_lpcd_read_id (void)
{
    am_fm175xx_handle_t handle;

    /* ��ʼ�����߲�ѡ������1   ע��˴�һ��Ҫ��ѡ������*/
    am_cd4051_pin_init(&__g_antenna_info);
    am_cd4051_channel_selected(&__g_antenna_info, 0);

    handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_lpcd_mode(handle);
}

/** [demo_amks16rfid8_fm175xx_picca_lpcd_mode] */

/* end of file */
