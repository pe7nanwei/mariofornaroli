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
 * \brief �������ʾ��60s ��ʱ��Ӧ��
 * 
 * ��Ӧ����Ҫʹ�õ���λ����ܣ�ָ�����������ʾ���������ٰ�����λ�����
 *
 * - ��������
 *   1. ������ں���������ָ�����������ʾ�����
 *
 * - ʵ������
 *   1. ���Կ�����ֵ 0 ~ 59 �����������
 *   2. ����С��30ʱ����λ��˸������30ʱʮλ��˸��
 *
 * \par Դ����
 * \snippet demo_std_digitron_60s_counting.c src_std_digitron_60s_counting
 *
 * \internal
 * \par Modification history
 * - 1.00 15-07-21  tee, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_digitron_60s_counting
 * \copydoc demo_std_digitron_60s_counting.c
 */

/** [src_std_digitron_60s_counting] */
#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_digitron_disp.h"

/**
 * \brief �������
 */
void demo_std_digitron_60s_counting_entry (int32_t id)
{
    int i   = 0;
    int num = 0;

    /* ��ʼ��������8��ASCII���� */
    am_digitron_disp_decode_set(id, am_digitron_seg8_ascii_decode);

    am_digitron_disp_char_at(id, 0, '0');        /* ʮλ�������ʾ�ַ�0 */
    am_digitron_disp_char_at(id, 1, '0');        /* ��λ�������ʾ�ַ�0 */

    /* ��ʼ��ֵС��30����λ��˸ */
    am_digitron_disp_blink_set(id, 1, AM_TRUE);

    while(1) {
       for (i = 0; i < 60; i++) {
             am_mdelay(1000);

             /* ��ֵ��1�� 0 ~ 59ѭ�� */
             num = (num + 1) % 60;

             /* ���¸�λ��ʮλ��ʾ */
             am_digitron_disp_char_at(id, 0, '0' + num / 10 );
             am_digitron_disp_char_at(id, 1, '0' + num % 10);

             if (num < 30) {
                 /* С��30����λ��˸��ʮλ����˸ */
                 am_digitron_disp_blink_set(id, 0, AM_FALSE);
                 am_digitron_disp_blink_set(id, 1, AM_TRUE);
             } else {

                 /* ����30��ʮλ��˸����λ����˸ */
                 am_digitron_disp_blink_set(id, 0, AM_TRUE);
                 am_digitron_disp_blink_set(id, 1, AM_FALSE);
            }
        }
    }
}
/** [src_std_digitron_60s_counting] */

/* end of file */
