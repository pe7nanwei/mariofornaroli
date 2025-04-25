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
 * \brief ѭ������У��(CRC) ���ʵ��
 *
 * \internal
 * \par modification history
 * - 1.00 18-01-19  tee, first implementation
 * \endinternal
 */

#ifndef __AM_CRC_SOFT_H
#define __AM_CRC_SOFT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_crc_soft
 * \copydoc am_crc_soft.h
 * @{
 */
#include "am_common.h"
#include "am_crc.h"

/**
 * \brief CRC TABLE��
 *
 *     Ϊ�˼ӿ���� CRC ������ٶȣ�ʹ���˲���������Ҫ�ڳ�ʼ��һ�����CRC��
 * ����ʱ(\sa am_crc_soft_init())�ṩһ������CRC����ı��ñ�ľ���������CRCģ
 * ���У�width��poly �� refin ������Ա��ֵ��أ�ֻҪһ��ģ����������ֵ��ȣ���
 * �ǾͿ���ʹ��ͬһ�� table ��
 */
typedef struct am_crc_table {

    uint8_t     width;                     /**< \brief CRC���                */
    uint32_t    poly;                      /**< \brief CRC���ɶ���ʽ          */
    am_bool_t   refin;                     /**< \brief �����ֽ�bit����        */

    /**
     * \brief ָ��ʵ�� TABLE ������Ϣ ��ָ��
     *
     * TBALE�ĳ��ȹ̶�Ϊ256����ʵ�������� width��ֵ���
     *     - 8λ��8λ���£�p_data ָ���  TABLE ԭ��Ӧ��Ϊ�� uint8_t data[256]
     *     - 9  ��16λ��    p_data ָ���  TABLE ԭ��Ӧ��Ϊ��uint16_t data[256]
     *     - 17 ��32λ��   p_data ָ���  TABLE ԭ��Ӧ��Ϊ��uint32_t data[256]
     */
    const void *p_data;

} am_crc_table_t;

/**
 * \brief ���CRC
 */
typedef struct am_crc_soft {

    /** \brief ���CRC�ܹ��ṩ��׼��CRC�������    */
    am_crc_serv_t            serv;

    /** \brief ���CRCʹ�õ�TABLE������ */
    const am_crc_table_t    *p_table;

    /* ��ǰ�� CRC ����ģ��  */
    am_crc_pattern_t        *p_pattern;

    /** \brief CRC����ֵ          */
    uint32_t                 value;

} am_crc_soft_t;

/**
 * \brief һ��ͨ�õ� CRC table ��������
 *
 *   Ϊ�˼ӿ���� CRC ������������ʣ�ʹ���˲���������Ҫ�ڳ�ʼ��һ�����CRC
 * ������ʱ(\sa am_crc_soft_init())�ṩһ������CRC����ı��ñ�ľ���������CRC
 * ģ���У�width��poly �� refin ������Ա��ֵ��أ�ֻҪһ��ģ����������ֵ��ȣ���
 * ���ǾͿ���ʹ��ͬһ�� table ��
 *
 * \param[in] p_table : TABLE��ʵ��
 * \param[in] width   : CRC���
 * \param[in] poly    : ���ɶ���ʽ
 * \param[in] refin   : �����ֽ�bit����
 * \param[in] p_data  : �洢���ݵ�����ռ䣬��ʵ�������� width��ֵ��ء�
 *                     - 8λ��8λ���£���ָ��� TABLE ԭ��Ϊ��uint8_t  data[256]
 *                     - 9  ��16λ��   ��ָ��� TABLE ԭ��Ϊ��uint16_t data[256]
 *                     - 17 ��32λ��   ��ָ��� TABLE ԭ��Ϊ��uint32_t data[256]
 *
 * \retval AM_OK      : ���ɳɹ�
 * \retval -AM_EINVAL : ����ʧ�ܣ��������ڴ���
 *
 * \note Ϊ�˱����û�ʹ�ã��Ѿ��ṩ�˳����� table ����� \ref am_if_crc_table_def.
 * �û�����ֱ��ʹ����ЩTABLE���������Ϊ��ʼ������ p_table ��ֵ���������ṩ��table��
 * ����δ�ҵ���ʹ�õ�CRCģ�͡������ʹ�� �ú�������һ��table��
 */
int am_crc_table_create (am_crc_table_t  *p_table,
                         uint8_t          width,
                         uint32_t         poly,
                         am_bool_t        refin,
                         void            *p_data);

/**
 * \brief ��ʼ��һ����� CRC ������
 *
 * \param[in] p_crc   : CRC ������ʵ��
 * \param[in] p_table : ����� CRC ʹ�õ� TABLE ��TABLE����ʹ�õ�CRCģ����أ�
 *                      ��� \ref am_if_crc_table_def. �������ṩ��table�б���δ
 *                      �ҵ���ʹ�õ�CRCģ�͡������ʹ�� \sa am_crc_table_create()
 *                      ��������һ��table��
 *
 * \return ��׼��CRC����������ΪNULL�� ���ʾ��ʼ��ʧ��
 *
 * \warning ���ﴫ���TABLE�������˸� CRC ������֧�ֵ�CRCģ�ͣ���֧�ֵ�CRCģ�� \n
 * �У�width��poly��refin ��ֵ������ TABLE ���������ֵһ�¡�
 *
 * \note ����ʹ�øú�����ʼ�����CRC���������Ա�֧�ֶ��ֲ�ͬģ�͵�CRC��
 */
am_crc_handle_t am_crc_soft_init (am_crc_soft_t         *p_crc,
                                  const am_crc_table_t  *p_table);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CRC_SOFT_H */

/* end of file */
