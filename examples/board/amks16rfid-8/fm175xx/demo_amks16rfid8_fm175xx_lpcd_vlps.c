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
 * \brief LPCDģʽ  ���ϵͳ���͹���ֹͣģʽ  �ڳ��͹��������ʵ�ֿ�Ƭ��⹦��
 *      �ڴ������У�KS16�������VLPSģʽ�������͹���ֹͣģʽ��
 *      ��FM175xx����LPCDģʽ֮��MUC����VLPSģʽ��������MCU������
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߣ���λ�������ӡ�����ʾ��Ϣ���û����Ը�����ʾ��Ϣ���ж��Ƿ����LPCDģʽ�ɹ�
 *   3. ����LPCDģʽ�ɹ��󣬽�����ж�������������ӡ��Ƭ�����Ϣ��
 *
 * - ʵ������
 *   1. ���ڴ�ӡ����Ƭ���ͺźͿ��ż���Ƭ��Ϣ
 *
 * \par Դ����
 * \snippet demo_amks16rfid8_dr_fm175xx_lpcd_vlps_read_id.c src_amks16rfid8_dr_fm175xx_lpcd_vlps_read_id
 *
 * \internal
 * \par Modification history
 * - 1.00 19-07-012  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_amks16rfid8_core_dr_fm175xx_lpcd_vlps_read_id
 * \copydoc demo_amks16rfid8_core_dr_fm175xx_lpcd_vlps_read_id.c
 */

/** [src_amks16rfid8_dr_fm175xx_lpcd_vlps_read_id] */
#include "kl26_pin.h"
#include "am_kl26_pmu.h"
#include "am_vdebug.h"
#include "am_fm175xx.h"
#include "am_fm175xx_ant.h"
#include "am_fm175xx_reg.h"
#include "am_kl26_pmu.h"
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
 * \brief �����������ص�����  �û����Լ���������   �������Զ�ȡIDΪ��
 */
static int8_t  picca_active_info(am_fm175xx_handle_t handle)
{
    uint8_t      tag_type[2]  = { 0 };      /* ATQA */
    uint8_t      uid[10]      = { 0 };      /* UID */
    uint8_t      uid_real_len =   0;        /* ���յ���UID�ĳ��� */
    uint8_t      sak[3]       = { 0 };      /* SAK */
    uint8_t      i;

    /* ���������  */
    if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                              (handle,
                                               AM_FM175XX_PICCA_REQ_ALL,
                                               tag_type,
                                               uid,
                                               &uid_real_len,
                                               sak)) {
        am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

        /* ��ӡUID */
        am_kprintf("UID  :");
        for (i = 0; i < uid_real_len; i++) {
            am_kprintf("%02x ", uid[i]);
        }
        am_kprintf("\n");

        /* ��ӡSAK */
        am_kprintf("SAK  :");
        for (i = 4; i <= uid_real_len; i+=3) {
            am_kprintf("%02x ", sak[(i - 4) / 3]);
        }
        am_kprintf("\n\n");
        return AM_OK;
    }else{
        return AM_ERROR;
    }
}

/**
 * \brief �û��ص�����
 *
 *  �����ж�֮�󽫻��Զ��˳�LPCDģʽ  �ٴν����û������am_fm175xx_lpcd_mode_entry
 *  ���½���LPCDģʽ
 */
static void  __fm175xx_lpcd_cb(void *p_arg)
{
    int *p_flag = (int *)p_arg;
    *p_flag =1;
}

/**
 * \brief A��LPCDģʽ ���������ͺͿ�������
 */
void demo_amks16rfid8_dr_fm175xx_lpcd_vlps_read_id (void)
{
    int int_flag = 0;

    /* B�汾���İ���ڴ�����   ��Ҫ����ʹ������
     * ��ΪA�汾���İ���ɶԸ��д������ע��
     */
    am_gpio_pin_cfg(__ANT_ENABLE_PIN, AM_GPIO_OUTPUT_INIT_HIGH);

    /* ��ʼ�����߲�ѡ������1   ע��˴�һ��Ҫ��ѡ������*/
    am_cd4051_pin_init(&__g_antenna_info);
    am_cd4051_channel_selected(&__g_antenna_info, 0);

    am_fm175xx_handle_t handle = am_fm175xx_inst_init();


    am_kprintf("FM175xx LPCD mode test!\n");

    /* ���ûص���������������
     * ע�⣬��ʹ��INT SPI �жϻص������У�������FM175xx����ͨ�š�
     * ���򽫻ᷢ��ͬ���ȼ��ж�Ƕ�ף����³���һֱ���ж��еȴ��жϷ���
     */
    am_fm175xx_lpcd_cb_set(handle, __fm175xx_lpcd_cb, &int_flag);

    /* ����LPCDģʽ */
    am_fm175xx_lpcd_mode_entry(handle);

    am_kprintf("Enter VLPS_MODE.\n");
    if(am_kl26_pmu_mode_into(AM_KL26_PMU_MODE_VLPS) != AM_OK) {
        am_kprintf("Enter VLPS_MODE Failed !\r\n");
    } else {
        am_kprintf("Wake Up from VLPS_MODE !\r\n");
    }
    while(1){
        uint8_t isr;

         /* �����������ص�����
          * ע�⣬LPCDģʽֻ�ᴥ�������жϣ��������ж��Լ��Զ������ж�
          */
        if(int_flag == 1){

            int_flag = 0;

            isr = am_fm175xx_get_reg_ext(handle, AM_FM175XX_LPCD_IRQ);

            if((isr & AM_FM175XX_LPCD_CARD_IRQ) == AM_FM175XX_LPCD_CARD_IRQ){

                /* �˳�LPCDģʽ��Ҫ�Բ���FM175xx�������½������� */
                am_fm175xx_exit_lpcd_config(handle);

                /*���ڴ˽�����Ӧ�Ŀ�����*/
                picca_active_info(handle);

                /* ��������ʱ�Զ������ж� */
            }else if((isr & AM_FM175XX_LPCD_WUP_IRQ) == AM_FM175XX_LPCD_WUP_IRQ){
                am_fm175xx_lpcd_init(handle);
            }
            /* �ٴν���LPCDģʽ */
            am_fm175xx_lpcd_mode_entry(handle);

            am_kprintf("Enter VLPS_MODE.\n");
            if(am_kl26_pmu_mode_into(AM_KL26_PMU_MODE_VLPS) != AM_OK) {
                am_kprintf("Enter VLPS_MODE Failed !\r\n");
            } else {
                am_kprintf("Wake Up from VLPS_MODE !\r\n");
            }
        }
    }
}

/** [demo_amks16rfid8_core_dr_fm175xx_lpcd_vlps_read_id] */

/* end of file */



