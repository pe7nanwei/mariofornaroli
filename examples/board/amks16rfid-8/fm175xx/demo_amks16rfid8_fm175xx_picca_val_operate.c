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
 * \brief fm175xxд�����ݣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ������ԿA�Կ�Ƭָ���Ŀ������֤�������֤��ͨ�����ӡkey A authent failed��
 *   2. �����֤�ɹ�������ָ���Ŀ��еĸ�ʽΪ��ֵ��ĸ�ʽ��ô�����е���ֵ��5�ٴ�ӡ������
 *   3. �����֤�ɹ�������ָ�����еĸ�ʽ������ֵ��ĸ�ʽ����ô�����ӡ��ֵ����ʱ���Խ�130�е���������
 *      ��Ϊ1�������ִ�У�ˢ��ʱ�᲻�ϵĴ�ӡͬһ�����֣�֮���ٽ�130�е����������Ϊ0�������ִ�У���
 *      ˢ�����򴮿ڽ���ӡ����15��ʼ������-5����ֵ��
 *
 * \par Դ����
 * \snippet demo_amks16rfid8_fm175xx_picca_val_operate.c src_amks16rfid8_fm175xx_picca_val_operate
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-22  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_picca_val_operate
 * \copydoc demo_amks16rfid8_fm175xx_picca_val_operate.c
 */

/** [src_amks16rfid8_fm175xx_picca_val_operate] */
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
 * \name ������İ���ع̶�����
 * @{
 */
#define __CD4051_PIN_EN  PIOB_19         /**< \brief   CD4051ͨ������оƬ ʹ������  */
#define __CD4051_PIN_S2  PIOB_18         /**< \brief   CD4051ͨ������оƬS2����  */
#define __CD4051_PIN_S1  PIOB_17         /**< \brief   CD4051ͨ������оƬS1����  */
#define __CD4051_PIN_S0  PIOB_16         /**< \brief   CD4051ͨ������оƬS0����  */

#define __ANT_ENABLE_PIN PIOE_29         /**<\brief   ������ѹоƬʹ������  */

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
 * \brief A�࿨ֵ��������
 */
void demo_amks16rfid8_fm175xx_picca_val_operate (void)
{
    am_fm175xx_handle_t handle;

    /* B�汾���İ���ڴ�����   ��Ҫ����ʹ������
     * ��ΪA�汾���İ���ɶԸ��д������ע��
     */
    am_gpio_pin_cfg(__ANT_ENABLE_PIN, AM_GPIO_OUTPUT_INIT_HIGH);

    am_cd4051_pin_init(&__g_antenna_info);
    /* ѡ������1 */
    am_cd4051_channel_selected(&__g_antenna_info, 0);
    
    handle = am_fm175xx_inst_init();

    demo_fm175xx_picca_val_operate(handle);
}

/** [src_amks16rfid8_fm175xx_picca_val_operate] */

/* end of file */
