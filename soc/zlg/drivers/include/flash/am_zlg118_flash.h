/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg118.cn/
*******************************************************************************/

/**
 * \file
 * \brief Flash������ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG118_FLASH_H
#define __AM_ZLG118_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"
#include "soc_cfg.h"
#include "hw/amhw_zlg118_flash.h"

/**
 * \addtogroup am_zlg118_if_flash
 * \copydoc am_zlg118_flash.h
 * @{
 */

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_zlg118_flash_init (amhw_zlg118_flash_t *p_hw_flash);

/**
 * \brief ��������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr  ��������ʼ��ַ
 *
 * \return >0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_zlg118_flash_sector_erase (amhw_zlg118_flash_t *p_hw_flash,
                                      uint32_t             start_addr);

/**
 * \brief ��������̻򲿷��������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 * \param[in] dst_addr   д�뵽flash����ʼ��ַ
 * \param[in] p_src      Ҫд�뵽flash�е����ݵ���ʼ��ַ
 * \param[in] size       д����(32bit)�ĸ���
 *
 * \retval 0 ʵ�ʳɹ�д�������
 */
int32_t am_zlg118_flash_flash_program (amhw_zlg118_flash_t *p_hw_flash,
                                       uint32_t             dst_addr,
                                       uint32_t            *p_src,
                                       uint32_t             size);

/**
 * \brief ������������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
uint32_t am_zlg118_flash_all_sector_erase (amhw_zlg118_flash_t *p_hw_flash);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /** __AM_ZLG118_FLASH_H */
