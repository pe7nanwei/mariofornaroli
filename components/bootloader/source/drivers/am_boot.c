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
 * \brief bootloader ��׼�ӿ�
 *
 * \internal
 * \par modification history:
 * - 1.00 18-12-11  yrh, first implementation.
 * \endinternal
 */
#include "am_boot.h"

static am_boot_serv_t *__gp_boot_serv = NULL;


/**
 * \brief ��ת��Ӧ�ô���
 */
int am_boot_go_application(void)
{
    if(__gp_boot_serv == NULL) {
        return -AM_ERROR;
    }
    return __gp_boot_serv->p_funcs->pfn_go_application();
}

am_bool_t am_boot_app_is_ready(void)
{
    if(__gp_boot_serv != NULL) {
        return __gp_boot_serv->p_funcs->pfn_app_is_ready();
    }
    return AM_FALSE;
}

void am_boot_reset(void)
{
    if(__gp_boot_serv != NULL) {
        __gp_boot_serv->p_funcs->pfn_reset();
    }
}

/**
 * \brief ��ȡӦ�ô����ŵ���ʼ��ַ
 *
 * \retval > 0 ����Ӧ�ô����ŵ���ʼ��ַ
 * \retval < 0 �޷���ȡ��ַ
 */
int am_boot_get_app_addr(void)
{
    if(__gp_boot_serv->p_funcs->pfn_get_app_sta_addr != NULL) {
        return __gp_boot_serv->p_funcs->pfn_get_app_sta_addr();
    }
    return AM_ERROR;
}

void am_boot_init(am_boot_serv_t *p_boot_serv)
{
    __gp_boot_serv = p_boot_serv;
}

