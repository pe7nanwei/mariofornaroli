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
 * \brief zsn60x �Զ����ģʽ���в���
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��ȷ���Ӻ����ߣ�
 *   3. ����Ƭ���ڸ�Ӧ��
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ��Ӧ��Ϣ��
 *
 * \par Դ����
 * \snippet demo_zsn60x_auto_detect_test.c src_zsn60x_auto_detect_test
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-18  htf, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zsn60x_auto_detect_test
 * \copydoc demo_zsn60x_auto_detect_test.c
 */

/** [src_zsn60x_auto_detect_test] */
#include "zsn60x.h"  
#include "ametal.h"
#include "am_vdebug.h"
static int a = 0;

/* ��⵽��Ƭ�ص����� */
void __card_input(void *p_arg){
    a = 1;
}

/* ZSN60x  �Զ������Գ��� */
void demo_zsn60x_auto_detect_test_entry(zsn60x_handle_t handle)
{
    uint8_t ret;
    /* ʹ��Ĭ����Կ */
    uint8_t data[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    zsn60x_auto_detect_ctrl_t  auto_ctrl;
    zsn60x_auto_detect_data_t  auto_data;

    //�Զ����ģʽ����
    auto_ctrl.ad_mode        = ZSN60X_AUTO_DETECT_CONTINUE | ZSN60X_AUTO_DETECT_INTERRUPT |
                               ZSN60X_AUTO_DETECT_SEND;
    auto_ctrl.tx_mode        = ZSN60X_ANT_MODE_TX12;
    auto_ctrl.req_code       = ZSN60X_MIFARE_REQUEST_IDLE;
    auto_ctrl.auth_mode      = ZSN60X_AUTO_DETECT_KEY_AUTH;
    auto_ctrl.key_type       = ZSN60X_ICC_KEY_TYPE_A;
    auto_ctrl.p_key          = data;
    auto_ctrl.key_len        = 6;
    auto_ctrl.block          = 4;
    auto_ctrl.pfn_card_input = __card_input;
    auto_ctrl.p_arg          = NULL;

    ret = zsn60x_auto_detect(handle, &auto_ctrl);
    if(ret == 0){
        am_kprintf("Entry auto detect card mode success!\r\n");
    }else{
        am_kprintf("Entry auto detect card mode fail beacuse error 0x%02x!\r\n", ret);
        return ;
    }

    /* �ȴ��ص��������� */
    while(a == 0);
    ret = zsn60x_get_auto_detect(handle, 0, &auto_data);
    a = 0;

    if(ret == 0){
        am_kprintf("Auto detect card success!\r\n");
    }else{
        am_kprintf("Auto detect card fail beacuse error 0x%2x!\r\n", ret);
    }
}  
/** [src_zsn60x_auto_detect_test] */

/* end of file */
