/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC8XX FMC Ӳ�������ӿ�����
 *
 * 1. �ɿ����������ʱ�䣻
 * 2. �ṩ������������ǩ���ļĴ�����
 *
 * \internal
 * \par Modification history
 * - 1.01 15-12-04  sky, modified.
 * - 1.00 15-07-16  aii, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC_FMC_H
#define __AMHW_LPC_FMC_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_lpc_if_fmc
 * \copydoc amhw_lpc_fmc.h
 * @{
 */

/**
 * \brief Flash�������Ĵ����ṹ���
 */
typedef struct amhw_lpc_fmc {
    __I  uint32_t reserved0[4];         /**< \brief ���� */
    __IO uint32_t flashcfg;             /**< \brief �������üĴ��� */
    __I  uint32_t reserved1[3];         /**< \brief ���� */
    __IO uint32_t fmsstart;             /**< \brief ǩ����ʼ��ַ�Ĵ��� */
    __IO uint32_t fmsstop;              /**< \brief ǩ��ֹͣ��ַ�Ĵ��� */
    __I  uint32_t reserved2[1];         /**< \brief ���� */
    __I  uint32_t fmsw0;                /**< \brief ǩ���� */
} amhw_lpc_fmc_t;

/**
 * \brief �����������ʱ������
 *        1��ϵͳʱ�ӵ��������ʱ��ֻ����20MHzʱ����
 *        2��ϵͳʱ�ӵ��������ʱ��ֻ����30MHzʱ����
 */
typedef enum amhw_lpc_fmc_time {
    AMHW_LPC_FMC_FLASHTIM_1 = 0,     /**< \brief 1��ϵͳʱ�ӵ��������ʱ�� */
    AMHW_LPC_FMC_FLASHTIM_2 = 1      /**< \brief 2��ϵͳʱ�ӵ��������ʱ�� */
} amhw_lpc_fmc_time_t;

/**
 * \brief �������ʱ������
 * \param[in] time : �������ʱ��(ϵͳʱ������Ϊ��λ)
 * \return ��
 */
am_static_inline
void amhw_lpc_fmc_flashtim_set (amhw_lpc_fmc_t * p_hw_fmc, amhw_lpc_fmc_time_t time)
{
	p_hw_fmc->flashcfg = time & 0x3;
}

/**
 * \brief ��ȡ�������ʱ��
 * \param[in] : ��
 * \return ǩ������ʱ��(ϵͳʱ������Ϊ��λ)
 */
am_static_inline
amhw_lpc_fmc_time_t amhw_lpc_fmc_flashtim_get (amhw_lpc_fmc_t * p_hw_fmc)
{
    return (amhw_lpc_fmc_time_t)(p_hw_fmc->flashcfg & 0x3);
}

/**
 * \brief ǩ��������ʼ��ַ
 * \param[in] addr : ǩ��������ʼ��ַ(��Ӧ��AHB�ֽڵ�ַλ��20:4����16λ����)
 * \return ��
 */
am_static_inline
void amhw_lpc_fmc_fmsstart_set (amhw_lpc_fmc_t * p_hw_fmc, uint32_t addr)
{
	p_hw_fmc->fmsstart = (addr >> 4) & 0x1ffff;
}

/**
 * \brief ��ȡǩ��������ʼ��ַ
 * \param[in] : ��
 * \return ǩ��������ʼ��ַ
 */
am_static_inline
uint32_t amhw_lpc_fmc_fmsstart_get (amhw_lpc_fmc_t * p_hw_fmc)
{
    return ((p_hw_fmc->fmsstart) & 0x1ffff) << 4;
}

/**
 * \brief ǩ�����ɽ�����ַ
 * \param[in] addr : ǩ�����ɽ�����ַ(��Ӧ��AHB�ֽڵ�ַλ��20:4����16λ����)
 * \return ��
 * \note STOPAָ���ְ����ڵ�ַ��Χ����ַ��λΪ�洢�ֶ����ֽ�
 */
am_static_inline
void amhw_lpc_fmc_fmsstop_set (amhw_lpc_fmc_t * p_hw_fmc, uint32_t addr)
{
	p_hw_fmc->fmsstop = (addr >> 4) & 0x1ffff;
}

/**
 * \brief ��ȡǩ�����ɽ�����ַ
 * \param[in] : ��
 * \return ǩ�����ɽ�����ַ
 */
am_static_inline
uint32_t amhw_lpc_fmc_fmsstop_get (amhw_lpc_fmc_t * p_hw_fmc)
{
    return ((p_hw_fmc->fmsstop) & 0x1ffff) << 4;
}

/**
 * \brief ��ʼǩ������
 */
am_static_inline
void amhw_lpc_fmc_strtbist (amhw_lpc_fmc_t * p_hw_fmc)
{
	p_hw_fmc->fmsstop |= (1UL << 31);
}

/**
 * \brief ��ȡǩ����Ϣ
 * \param[in] : ��
 * \return ����flashǩ����Ϣ
 */
am_static_inline
uint32_t amhw_lpc_fmc_flash_sign_get (amhw_lpc_fmc_t * p_hw_fmc)
{
    return p_hw_fmc->fmsw0;
}

/**
 * \brief ���ٻ�ȡǩ����Ϣ
 *
 * \param[in] start_addr : ǩ��������ʼ��ַ(��Ӧ��AHB�ֽڵ�ַλ��20:4����16λ����)
 * \param[in] end_addr   : ǩ�����ɽ�����ַ(��Ӧ��AHB�ֽڵ�ַλ��20:4����16λ����)
 *
 * \return ����flashǩ����Ϣ
 */
am_static_inline
uint32_t amhw_lpc_fmc_flash_sign (amhw_lpc_fmc_t * p_hw_fmc, uint32_t start_addr, uint32_t end_addr)
{
	p_hw_fmc->fmsstart = (start_addr >> 4) & 0x1ffff;
	p_hw_fmc->fmsstop  = ((end_addr >> 4) & 0x1ffff) | 0x80000000;
    return p_hw_fmc->fmsw0;
}

/**
 * @} amhw_lpc_if_fmc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC84X_FMC_H */

/* end of file */
