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
 * \brief fm175xxͨ��CD4051����8�����߶�A�࿨��ID��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��ȷ���Ӻ����ߣ�
 *   3. �� MiniPort-LED ����ֱ���� AMKS16RFID-8 ���ΪJ4�� MiniPort�ӿ������ӣ�
 *   4. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ����Ƭ��ID��
 *   2. ������߸�Ӧ�����п�Ƭ�� MiniPort-LED ��Ӧλ�õ�LED�������
 *
 * - ע�⣺
 *   1. Ҫʹ�ø����̣���Ҫ��am_prj_config.h���潫AM_CFG_LED_ENABLE����Ϊ0��
 *
 * \par Դ����
 * \snippet demo_amks16rfid8_fm175xx_picca_8ante_read_id.c src_amks16rfid8_fm175xx_picca_8ante_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 18-02-06  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_picca_8ante_read_id
 * \copydoc demo_amks16rfid8_fm175xx_picca_8ante_read_id.c
 */

/** [src_amks16rfid8_fm175xx_picca_8ante_read_id] */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "kl26_pin.h"
#include "am_kl26_inst_init.h"
#include "am_delay.h"
#include "am_led.h"
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
 * \brief 8���߶�ȡA�࿨��������
 */
void demo_amks16rfid8_fm175xx_picca_8ante_read_id (void)
{
    uint8_t tag_type[2]  = { 0 };      /* ATQA */
    uint8_t uid[10]      = { 0 };      /* UID */
    uint8_t uid_real_len = 0;          /* ���յ���UID�ĳ��� */
    uint8_t sak[3]       = { 0 };      /* SAK */
    uint8_t i, j;
    am_fm175xx_handle_t handle;

    /* B�汾���İ���ڴ�����   ��Ҫ����ʹ������
     * ��ΪA�汾���İ���ɶԸ��д������ע��
     */
    am_gpio_pin_cfg(__ANT_ENABLE_PIN, AM_GPIO_OUTPUT_INIT_HIGH);
    am_cd4051_pin_init(&__g_antenna_info);

    handle = am_fm175xx_inst_init();

    am_miniport_led_inst_init();

    while (1) {
        for (j = 0; j < 8; j++) {
            am_cd4051_channel_selected(&__g_antenna_info, j);   /* ѡ������ */

            if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                             (handle,
                                              AM_FM175XX_PICCA_REQ_IDLE,
                                              tag_type,
                                              uid,
                                              &uid_real_len,
                                              sak)) {

                am_kprintf("antenna : %d\r\n", j + 1);
                am_kprintf("UID : ");
                for (i = 0; i < uid_real_len; i++) {
                    am_kprintf("%02x ", uid[i]);
                }
                am_kprintf("\r\n\r\n");
                am_led_on(j);
            } else {
                am_led_off(j);
            }
        }
    }
}

/** [src_amks16rfid8_fm175xx_picca_8ante_read_id] */

/* end of file */
