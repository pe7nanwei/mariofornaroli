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
 * \brief fm175xxʹ�ò�ͬ�ķ�����ȡ��Ƭ��Ϣ��ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڡ�
 *   2. ��ȷ���Ӻ����ߡ�
 *   3. ��A�࿨�������߸�Ӧ����
 *
 * - ʵ������
 *   1. �����Ƭ֧��haltָ���ÿ�����½����������߸�Ӧ���󣬴���ֻ�ܴ�ӡ�����ο�Ƭ��Ϣ��
 *   2. �����Ƭ��֧��haltָ��򽫿��������߸�Ӧ���󣬴������������ϵĴ�ӡ����Ƭ��Ϣ��
 *
 * \par Դ����
 * \snippet demo_fm175xx_picca_halt.c src_fm175xx_picca_halt
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-17  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_fm175xx_picca_halt
 * \copydoc demo_fm175xx_picca_halt.c
 */

/** [src_fm175xx_picca_halt] */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"

/**
 * \brief A�࿨�����߿�����
 */
void demo_fm175xx_picca_halt (am_fm175xx_handle_t handle)
{
    uint8_t tag_type[2] = { 0 };      /* ATQA */
    uint8_t uid[10]     = { 0 };      /* UID */
    uint8_t uid_real_len = 0;         /* ���յ���UID�ĳ��� */
    uint8_t sak[3]      = { 0 };      /* SAK */
    uint8_t i;

    while (1) {

        /* Ѱ����δ���ߣ�halt���Ŀ� */
        am_kprintf("read idle...\n");
        if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                         (handle,
                                          AM_FM175XX_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {
            am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

            am_kprintf("UID  :");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\n");
            am_kprintf("SAK  :%02x\n\n", sak[0]);

            am_fm175xx_picca_halt(handle);  /* �ÿ�Ƭ���� */
            am_kprintf("halt\n");
            am_kprintf("read halt...\n");
            /* �����еĿ����ܶ������ߵĿ��� */
            if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                             (handle,
                                              AM_FM175XX_PICCA_REQ_ALL,
                                              tag_type,
                                              uid,
                                              &uid_real_len,
                                              sak)) {

                am_kprintf("ATQA :%02x %02x\n", tag_type[0], tag_type[1]);

                am_kprintf("UID  :");
                for (i = 0; i < uid_real_len; i++) {
                    am_kprintf("%02x ", uid[i]);
                }
                am_kprintf("\n");
                am_kprintf("SAK  :%02x\n\n", sak[0]);
            }
        }
        am_mdelay(500);
    }
}

/** [src_fm175xx_picca_halt] */

/* end of file */
