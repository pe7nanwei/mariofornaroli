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

/** \brief ˫���û�������Ч */
#define AM_BOOTLOADER_FLAG_APP     (0x12345678)  //305419896
/** \brief ˫������������Ч */
#define AM_BOOTLOADER_FLAG_UPDATE  (0x87654321)  //2271560481
/** \brief ˫���޴��� */
#define AM_BOOTLOADER_FLAG_NO      (0xFFFFFFFF)


/**
 * \brief �ж�Ӧ�ô����Ƿ������ת��ȥִ��
 * 
 * \param[in] app_start_addr : Ӧ�ô����׵�ַ
 * 
 * \retval  ��
 */ 
am_bool_t am_boot_app_is_ready(void);

/**
 * \brief ��ת��Ӧ�ô������
 *
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
 * \brief ˫��bootloader��־����
 *
 * \param[in] flags ��־
 * AM_BOOTLOADER_FLAGS_APP    ˫���û�������Ч
 * AM_BOOTLOADER_FLAGS_UPDATE ˫������������Ч
 * AM_BOOTLOADER_FLAGS_NO     ˫���޴���
 *
 * \retval AM_OK �ɹ�
 */
int am_boot_update_flag_set(uint32_t flag);


#ifdef __cplusplus
}
#endif

 #endif /* __AM_BOOT_H */
 
 /* end of file */
