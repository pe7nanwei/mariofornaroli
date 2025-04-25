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
 * \brief CRC TABLE ���壬 ������� CRC ����
 *
 * ���ļ������� ���ֳ���CRC�� TABLE����ֱ������ (\sa am_crc_soft_init()) ������
 * p_table ����.
 *
 * \internal
 * \par modification history
 * - 1.00 18-01-19  tee, first implementation
 * \endinternal
 */

#ifndef __AM_CRC_TABLE_DEF_H
#define __AM_CRC_TABLE_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_crc_table
 * \copydoc am_crc_table.h
 * @{
 */
#include "am_common.h"
#include "am_crc.h"
#include "am_crc_soft.h"

/**
 * \name 8λ��8λ����crc table
 *
 * ��ǰ�Ѿ�֧�ֵ�ģ�ͣ�����Ѿ������ã��������½�����ֱ��ʹ�ü��ɡ�
 * �����������g_crc_table_X_Y(_ref)[256] X��Y����һ�����֡�
 *   - ���� g_crc_table ������X��ʾcrc��ȣ���crc5���Ӧ g_crc_table_5
 *   - �����»��ߺ������Y��ʾpoly,���ɶ���ʽ��
 *      - 8λ��8λ���£�polyʹ��8λ��ʾ��  ��09,��ʡ��0
 *      - 9��16λ     ��polyʹ��16λ��ʾ����8005,��ʡ��0
 *      - 17 ��32λ   ��polyʹ��32λ��ʾ����04C11DB7,��ʡ��0.
 *   - ��׺��ref�ı�ʾ�ñ�Ϊ�������crcģ����refin == TRUEʱ��
 *     Ӧ�ô����׺��ref�ı�
 *
 * ��ˣ�����ʹ�õ�crcģ�ͣ�����֪����ʹ���ĸ�����crcģ��Ϊ��
 *     width = 5��poly = 0x09,refin = TRUE.
 * ��ֱ��ʹ�� g_crc_table_5_09_ref ���ɡ�
 *
 * \note �����������ͬ���ʺ�������λ����CRC table��
 * @{
 */

/** \brief crc4  poly = 0x03, refin = TRUE  */
am_import am_const am_crc_table_t g_crc_table_4_03_ref;

/** \brief crc5  poly = 0x09, refin = FALSE */
am_import am_const am_crc_table_t g_crc_table_5_09;

/** \brief crc5  poly = 0x15, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_5_15_ref;

/** \brief crc5  poly = 0x05, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_5_05_ref;

/** \brief crc6  poly = 0x03, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_6_03_ref;

/** \brief crc7  poly = 0x09, refin = FALSE */
am_import am_const am_crc_table_t g_crc_table_7_09;

/** \brief crc8  poly = 0x07, refin = FALSE */
am_import am_const am_crc_table_t g_crc_table_8_07;

/** \brief crc8  poly = 0x07, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_8_07_ref;

/** \brief crc8  poly = 0x31, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_8_31_ref;

/** @} */

/**
 * \name 9λ��16λcrc table
 * @{
 */

/** \brief crc16  poly = 0x8005, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_16_8005_ref;

/** \brief crc16  poly = 0x1021, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_16_1021_ref;

/** \brief crc16  poly = 0x1021, refin = FALSE */
am_import am_const am_crc_table_t g_crc_table_16_1021;

/** \brief crc16  poly = 0x3D65, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_16_3d65_ref;

/** @} */

/**
 * \name 17λ��32λcrc table
 * @{
 */

/** \brief crc32  poly = 0x04c11db7, refin = TRUE */
am_import am_const am_crc_table_t g_crc_table_32_04c11db7_ref;

/** \brief crc32  poly = 0x04c11db7, refin = FALSE */
am_import am_const am_crc_table_t g_crc_table_32_04c11db7;

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CRC_TABLE_H */

/* end of file */
