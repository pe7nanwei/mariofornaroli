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
 * \brief ֧�ֶ�ʵ���Ķ�ʽ����������ӿ�
 *
 * ʹ�ñ�������Ҫ����ͷ�ļ� am_digitron_disp.h
 *
 * \par ʹ��ʾ��
 * \code
 * #include "am_digitron_disp.h"
 *
 * // ��ʼ��������8��ASCII����
 * am_digitron_disp_decode_set(0, am_digitron_seg8_ascii_decode);
 *
 * am_digitron_disp_blink_set(0, 0, AM_TRUE);  // ���õ�0���������˸
 * am_digitron_disp_at(0, 0, 0x54);            // ��0���������ʾ�Զ�����״0x54
 * am_digitron_disp_char_at(0, 1, 'A');        // ��1���������ʾ�ַ�'A'
 * am_digitron_disp_clr(0);                    // ��������������ʾ��������
 * am_digitron_disp_str(0, 0, 4, "0123");      // �������ʾ�ַ���"0123"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 17-05-18  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DIGITRON_DISP_H
#define __AM_DIGITRON_DISP_H

#include "am_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_digitron_disp
 * \copydoc am_digitron_disp.h
 * @{
 */

/**
 * \brief ͨ�õ�8�������ASCII�ַ����뺯��
 * \param[in] ascii_char �� Ҫ�����ASCII�ַ�
 * \return ASCII�ַ���Ӧ���������������, ����޷����룬���ؿհ��루0x00����
 *
 * \note
 * �ú���һ����Ϊ8������ܵ�Ĭ�Ͻ��뺯��������û���Ҫʹ���Զ���Ľ��뺯�����ַ�
 * ���н��룬����ʹ�� am_digitron_disp_set_decode() �����Զ���Ľ��뺯����
 *
 * �ú���֧�ֵ�ASCII�ַ��У�
 *  |  A  |  S  |  C  |  I  |  I  |
 *  |-----|-----|-----|-----|-----|
 *  | '0' | '1' | '2' | '3' | '4' |
 *  | '5' | '6' | '7' | '8' | '9' |
 *  | 'A' | 'B' | 'C' | 'D' | 'E' |
 *  | 'F' | 'H' | 'I' | 'J' | 'L' |
 *  | 'N' | 'O' | 'P' | 'R' | 'S' |
 *  | 'a' | 'b' | 'c' | 'd' | 'e' |
 *  | 'f' | 'h' | 'i' | 'j' | 'l' |
 *  | 'n' | 'o' | 'p' | 'r' | 's' |
 *  | '-' | '.' | ' ' |  -  |  -  |
 *
 */
uint16_t am_digitron_seg8_ascii_decode (uint16_t ascii_char);

/**
 * \brief �����������ʾ�����Ķ������ӿ�
 *
 * \param[in] id         : ��ʾ�����
 * \param[in] pfn_decode : ���뺯��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_decode_set (int        id,
                                 uint16_t (*pfn_decode) (uint16_t ch));

/**
 * \brief �����������ʾ��˸����
 *
 * \param[in] id    : ��ʾ�����
 * \param[in] index : �����������
 * \param[in] blink : ��˸���ԣ�TURE����˸��FALSE����ֹ��˸��
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_blink_set (int id, int index, am_bool_t blink);

/**
 * \brief ֱ���������д�������ʾ���ݡ�������һ��������ʾ�Զ����������Ż���״
 *
 * \param[in] id    : ��ʾ�����
 * \param[in] index : �����������
 * \param[in] seg   : ��ʾ�ġ��Ρ��루�ߵ�ƽ��Ч��λֵΪ1ʱ����Ӧ�Ķε�����
 *
 * \retval AM_OK      : д��ɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_at (int id, int index, uint16_t seg);

/**
 * \brief ��ָ����ŵ����������ʾASCII�ַ�
 *
 * \param[in] id    : ��ʾ�����
 * \param[in] index : �����������
 * \param[in] ch    : Ҫ��ʾ��ASCII�ַ�
 *
 * \retval AM_OK      : ���óɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 *
 * \note ����ʾ���ַ��ɽ��뺯��ȷ��
 */
int am_digitron_disp_char_at (int id, int index, const char ch);

/**
 * \brief �����������ʾASCII�ַ���
 *
 * \param[in] id    : ��ʾ�����
 * \param[in] index : �����������
 * \param[in] len   : ��ʾ����
 * \param[in] p_str : Ҫ��ʾ��ASCII�ַ���
 *
 * \retval AM_OK      : ��ʾ�ɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 *
 * \note ����ʾ���ַ��ɽ��뺯��ȷ��
 */
int am_digitron_disp_str (int id, int index, int len, const char *p_str);

/**
 * \brief ��������������ʾ
 *
 * \param[in] id  : ��ʾ�����
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_clr (int id);

/**
 * \brief ʹ���������ʾ������ɨ�裨Ĭ��״̬�ǿ����ģ�
 *
 * \param[in] id  : ��ʾ�����
 *
 * \retval AM_OK      : ʹ�ܳɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_enable (int id);

/**
 * \brief �����������ʾ,ֹͣɨ��
 *
 * \param[in] id  : ��ʾ�����
 *
 * \retval AM_OK      : ���ܳɹ�
 * \retval -AM_ENODEV : ��ʾ����������޴���ʾ��
 */
int am_digitron_disp_disable (int id);

/** @} am_if_digitron_disp */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DIGITRON_DISP_H */

/* end of file */
