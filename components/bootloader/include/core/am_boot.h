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
 * \brief bootloader ͨ�û�����׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 18-11-13  yrh, first implementation.
 * \endinternal
 */
 
 #ifndef __AM_BOOT_H
 #define __AM_BOOT_H
 
#ifdef __cplusplus
extern "C" {
#endif
#include "ametal.h"
#include "am_boot_memory.h"

struct am_boot_drv_funcs{
    /**< \brief ���Ӧ�ó����Ƿ���Ч */
    am_bool_t (*pfn_app_is_ready)(void);
    /**< \brief ϵͳ���� */
    void      (*pfn_reset)(void);
    /**< \brief ��ת����Ӧ�ó��� */
    int       (*pfn_go_application)(void);
    /**< \brief ��ȡӦ�ó����ڴ��ŵ���ʼ��ַ */
    int       (*pfn_get_app_sta_addr)(void);
};

typedef struct am_boot_serv {
    struct am_boot_drv_funcs *p_funcs;
    void                     *drv;
}am_boot_serv_t;



/**
 * \brief �ж�Ӧ�ô����Ƿ���Ч
 * 
 * \retval AM_TRUE : ��Ч
 * \retval AM_TRUE : ��Ч
 */ 
am_bool_t am_boot_app_is_ready(void);

/**
 * \brief ��ת��Ӧ�ô������
 *
 * \retval AM_ERROR ��ת�������תĿ�ĵ�ַ����
 */
int am_boot_go_application(void);

/**
 * \brief ϵͳ�������
 *
 * \retval ��
 */
void am_boot_reset(void);

/**
 * \brief ��ȡӦ�ô����ŵ���ʼ��ַ
 *
 * \retval > 0 ����Ӧ�ô����ŵ���ʼ��ַ
 *         < 0 �޷���ȡ��ַ
 */
int am_boot_get_app_addr(void);


void am_boot_init(am_boot_serv_t *p_dev);

#ifdef __cplusplus
}
#endif

 #endif /* __AM_BOOT_H */
 
 /* end of file */
