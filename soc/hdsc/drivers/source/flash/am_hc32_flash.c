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
 * \brief Flashģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#include "am_hc32_flash.h"

#include "am_types.h"
#include "am_bitops.h"
#include "ametal.h"

/*******************************************************************************
  defines
*******************************************************************************/

#define UNLOCK_HC32_FLASH_KEY1   0x5A5A  /**< \brief unlock key word */
#define UNLOCK_HC32_FLASH_KEY2   0xA5A5  /**< \brief unlock key word */

#define FLASH_ADDRESS_BASE   0x00000000
#define FLASH_ADDRESS_SIZE   0x00000000 + FLASH_SIZE
/******************************************************************************
*   ��������
******************************************************************************/

/**
 * \brief Flashģ���ʼ��
 *
 * \param[in] p_hw_gpio ָ��FLASH�Ĵ������ָ��
 *
 * \return ��
 */
void am_hc32_flash_init (amhw_hc32_flash_t *p_hw_flash)
{
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

    amhw_hc32_flash_int_flag_clr(p_hw_flash, AMHW_HC32_FLASH_INT_ALL_FLAG);
}

/**
 * \brief ��������
 *
 * \param[in] p_hw_flash  ָ��FLASH�Ĵ������ָ��
 * \param[in] start_addr ��������ʼ��ַ
 *
 * \return > 0: ִ�н��, -AM_EINVAL: �����ַ����
 */
int32_t am_hc32_flash_sector_erase (amhw_hc32_flash_t *p_hw_flash,
                                      uint32_t             start_addr)
{
    if (FLASH_ADDRESS_SIZE < start_addr) {
        return -AM_EINVAL;
    }

    /* æ����һֱ�ȴ�*/
    while (AM_TRUE == amhw_hc32_flash_busy_check(p_hw_flash)) {
        ;
    }

    /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

    /* ѡ��FLASH�������� */
    amhw_hc32_flash_opt_set(p_hw_flash, AMHW_HC32_FLASH_OPT_SECTOR_ERASE);

    /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

    /* ����ĳ��ĳ�������в�д */
    amhw_hc32_flash_erase_enable(p_hw_flash,
                                   (start_addr - FLASH_ADDRESS_BASE) >> 11);

    /* �������ڵ�ÿһҳ�������ַд���������ݣ�����ҳ����������������������� */
    *((uint8_t *)(start_addr + 0 * 512)) = 0x00;
    *((uint8_t *)(start_addr + 1 * 512)) = 0x00;
    *((uint8_t *)(start_addr + 2 * 512)) = 0x00;
    *((uint8_t *)(start_addr + 3 * 512)) = 0x00;

    /* æ����һֱ�ȴ�*/
    while (AM_TRUE == amhw_hc32_flash_busy_check(p_hw_flash)) {
        ;
    }

    return AM_OK;
}

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
int32_t am_hc32_flash_flash_program (amhw_hc32_flash_t *p_hw_flash,
                                       uint32_t             dst_addr,
                                       uint32_t            *p_src,
                                       uint32_t             size)
{
    uint32_t i;
    uint32_t t;

    /** size���ܴ��������Ĵ�С */
    if (size > SECTOR_SIZE || dst_addr >= FLASH_ADDRESS_SIZE) {
        return -AM_EINVAL;
    }

    /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

    /* ѡ��FLASHд���� */
    amhw_hc32_flash_opt_set(p_hw_flash, AMHW_HC32_FLASH_OPT_WRITE);

    /* ����д�����ݸ�������һ�������������Ҫ�Զ������ȡ����д���� */
    t =  size / SECTOR_SIZE + 1;

    /* ����ĳ��ĳ�������в�д */
    for (i = 0; i < t; i++) {

        /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
        amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
        amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

        /* ����ĳ��ĳ�������в�д */
        amhw_hc32_flash_erase_enable(p_hw_flash,
                                       ((dst_addr - FLASH_ADDRESS_BASE) >> 11) + i);
    }

    for (i = 0; i < size; i++) {

        /** ����д�� */
        *(uint16_t *)(dst_addr + i * 4)     = (uint16_t)p_src[i];

        /* æ����һֱ�ȴ�*/
        while (AM_TRUE == amhw_hc32_flash_busy_check(p_hw_flash)) {
            ;
        }

        /** ����д�� */
        *(uint16_t *)(dst_addr + i * 4 + 2) = (uint16_t)(p_src[i] >> 16);

        /* æ����һֱ�ȴ�*/
        while (AM_TRUE == amhw_hc32_flash_busy_check(p_hw_flash)) {
            ;
        }
    }

    for (i = 0; i < size; i++) {

       /** ����д�� */
      if (p_src[i] != *(uint32_t *)(dst_addr + i * 4)) {
          break;
      }
    }
    return i;
}

/**
 * \brief ������������
 *
 * \param[in] p_hw_flash ָ��FLASH�Ĵ������ָ��
 *
 * \return ִ�н��
 *
 */
uint32_t am_hc32_flash_all_sector_erase (amhw_hc32_flash_t *p_hw_flash)
{
    uint8_t i;

    /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
    amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

    /* ѡ��FLASHд���� */
    amhw_hc32_flash_opt_set(p_hw_flash, AMHW_HC32_FLASH_OPT_CHIP_ERASE);

    /* ȡ������������д���� */
    for(i = 0; i < 128; i++) {

        /* д��ָ�����ݣ�ʹ�ܼĴ�����д */
        amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY1);
        amhw_hc32_flash_key_set(p_hw_flash, UNLOCK_HC32_FLASH_KEY2);

        /* ����ĳ��ĳ�������в�д */
        amhw_hc32_flash_erase_enable(p_hw_flash, i);
    }

    /* ��Ƭ�ڵ������ַ����д����������ȫƬ���� */
    *((uint8_t *) 0x00000000) = 0x00;

    /* æ����һֱ�ȴ�*/
    while (AM_TRUE == amhw_hc32_flash_busy_check(p_hw_flash)) {
        ;
    }

    return AM_OK;
}

/* end of file */
