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
 * \brief NVRAM(����ʧ�Դ洢��)��׼�ӿ�
 *
 * \par ��ʾ��
 * \code
 *  #include "am_nvram.h"
 *
 *  char ip[4] = {1, 1, 1, 1};
 *  char data[4];
 *
 *  am_nvram_set("ip", 0, &ip[0],   0, 4);    // ���÷���ʧ������"ip"
 *  am_nvram_get("ip", 0, &data[0], 0, 4);    // ��ȡ����ʧ������"ip"
 * \endcode
 *
 * // �������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-12  tee,first implementation
 * \endinternal
 */

#ifndef __AM_NVRAM_H
#define __AM_NVRAM_H

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus  */

/**
 * \addtogroup am_if_nvram
 * \copydoc am_nvram.h
 * @{
 */
   
#include "ametal.h"

/** 
 * \brief �洢�����Ͷ���
 *
 *      �ýṹ����Ҫ��������һ���洢�Σ�ÿ���洢�ζ����봦��ĳ���洢���豸�У��ô�
 *  �����豸ʹ�� p_dev_name �� dev_unit ȷ����ϵͳʹ�õ����д洢�ζ�Ӧֱ�Ӷ�����
 *  \sa am_nvram_cfg() �ļ��С�
 *
 *      �ٶ�Ӧ����Ҫ4���洢�Σ��ֱ𱣴�����IP��ַ��4�ֽڡ�2�����¶�����ֵ��4�ֽڣ���
 *  ϵͳ������50�ֽڣ���ϵͳ�п�����ΪNVRAM���豸Ϊ FM24C02������Զ������´洢
 *  ���б�
 *  const am_nvram_segment_t g_nvram_segs[] = {
 *      {"ip",         0,  0,  4,   "fm24c02"},
 *      {"ip",         1,  4,  4,   "fm24c02"},
 *      {"temp_limit", 0,  8,  4,   "fm24c02"},
 *      {"system",     0,  12, 50,  "fm24c02"},
 *      {"test",       0,  62, 178, "fm24c02"},
 *      {NULL,         0,   0,   0,      NULL}  // �մ洢�Σ����뱣��
 * };
 */
typedef struct am_nvram_segment {
    char       *p_name;       /**< \brief �洢������                    */
    int         unit;         /**< \brief �洢�ε�Ԫ��                  */
    uint32_t    seg_addr;     /**< \brief �洢���ڴ洢�����е���ʼ��ַ  */
    uint32_t    seg_size;     /**< \brief �洢�εĴ�С                  */
    const char *p_dev_name;   /**< \brief �洢�������Ĵ洢���豸��      */
} am_nvram_segment_t;

/**
 * \brief NVRAM ���������ṹ��
 */
struct am_nvram_drv_funcs {
    
    /** \brief ָ�� NVRAM ���ݻ�ȡ����*/
    int (*pfn_nvram_get) (void       *p_drv,
                          int         offset,
                          uint8_t    *p_buf,
                          int         len);
 
    /** \brief ָ�� NVRAM �������ú��� */
    int (*pfn_nvram_set) (void          *p_drv,
                          int            offset,
                          uint8_t       *p_buf,
                          int            len);
};

/**
 * \brief NVRAM�洢���豸���Ͷ���
 */
typedef struct am_nvram_dev {
    const char                      *p_dev_name; /**< \brief �豸��           */
    const struct am_nvram_drv_funcs *p_funcs;    /**< \brief ��Ӧ����������   */
    void                            *p_drv;      /**< \brief ������������     */
    struct am_nvram_dev             *p_next;     /**< \brief ָ����һ���豸   */
} am_nvram_dev_t;

/**
 * \brief NVRAM �����ʼ��
 * \param[in] p_seglist : ϵͳ�洢���б�
 * \return AM_OK����ʼ���ɹ�������ֵ����ʼ��ʧ�ܡ�  
 * \note �ú���һ����ϵͳ����ʱ���ã�Ӧ�ó�������ֱ��ʹ�øú���
 */
int am_nvram_init (const am_nvram_segment_t *p_seglist);

/**
 * \brief ��ϵͳ��ע��һ��NVRAM�洢���豸
 * \param[in] p_dev : ��ע����豸
 * \return AM_OK��ע��ɹ�������ֵ��ע��ʧ�ܡ�
 * \note �ú���һ���ɴ洢�������������ã�Ӧ�ó�������ֱ��ʹ�øú���
 */
int am_nvram_dev_register (am_nvram_dev_t *p_dev);

/**
 * \brief ȡ��һ����ע���NVRAM�洢���豸
 * \param[in] p_dev : ��ȡ�����Ѿ�ע��� NVRAM�洢���豸
 * \return AM_OK��ȡ��ע��ɹ�������ֵ��ȡ��ע��ʧ�ܡ�
 * \note �ú���һ���ɴ洢�������������ã�Ӧ�ó�������ֱ��ʹ�øú���
 */
int am_nvram_dev_unregister (am_nvram_dev_t *p_dev);

/**
 * \brief ��ȡһ������ʧ�Դ洢��Ϣ
 *
 * �������ӷ���ʧ�Դ洢�豸�ж�ȡ����ʧ����Ϣ�����浽�������ṩ�Ļ������С��κ�
 * ��Ҫʹ��NVRAM�����ģ�鶼����ʹ�ñ�������
 *
 * ������ʹ��\a p_name ��\a unit ����ʶһ������ʧ����Ϣ��
 *
 * ��������ʼλ����\a offset ָ������������������\a len ָ�������ָ���Ĵ�С����
 * �˸÷���ʧ����Ϣ�Ĵ�С��������Ϊδ���塣
 *
 * \param[in] p_name  ����ʧ�Դ洢��Ϣ������
 * \param[in] unit    ����ʧ�Դ洢��Ϣ�ĵ�Ԫ��
 * \param[in] p_buf   д�����ݻ�����
 * \param[in] offset  �ڷ���ʧ�Դ洢��Ϣ�е�ƫ��
 * \param[in] len     Ҫ�洢�ĳ���
 *
 * \retval AM_OK      �ɹ�
 * \retval -AM_EINVAL  \a p_name �� \a p_buf ΪNULL
 * \retval -AM_EIO    ָ���ķ���ʧ�Դ洢��Ϣ�����ڻ����ʧ��
 *
 * \par ʾ��
 * \code
 *  #include "aw_nvram.h"
 *
 *  char ip[4];
 *  aw_nvram_get("ip", 0, &ip[0], 0, 4);    // ��ȡ����ʧ������"ip"
 * \endcode
 *
 * \sa aw_nvram_set()
 */
int am_nvram_get (char *p_name, int unit, uint8_t *p_buf, int offset, int len);

/**
 * \brief д��һ������ʧ�Դ洢��Ϣ
 *
 * �������ӵ������ṩ�Ļ������ж�ȡ��Ϣ��������洢������ʧ�Դ洢�豸�С��κ�
 * ��Ҫʹ��NVRAM�����ģ�鶼����ʹ�ñ�������
 *
 * ������ʹ��\a p_name ��\a unit ����ʶһ������ʧ����Ϣ��
 *
 * �洢����ʼλ����\a offset ָ�����洢����������\a len ָ�������ָ���Ĵ�С����
 * �˸÷���ʧ����Ϣ�Ĵ�С��������Ϊδ���塣
 *
 * \param[in] p_name  ����ʧ�Դ洢��Ϣ������
 * \param[in] unit    ����ʧ�Դ洢��Ϣ�ĵ�Ԫ��
 * \param[in] p_buf   д�����ݻ�����
 * \param[in] offset  �ڷ���ʧ�Դ洢��Ϣ�е�ƫ��
 * \param[in] len     Ҫ�洢�ĳ���
 *
 * \retval AM_OK      �ɹ�
 * \retval -AM_EINVAL  \a p_name �� \a p_buf ΪNULL
 * \retval -AM_EIO    ָ���ķ���ʧ�Դ洢��Ϣ�����ڻ����ʧ��
 *
 * \par ʾ��
 * \code
 *  #include "am_nvram.h"
 *
 *  char ip[4] = {1, 1, 1, 1};
 *  am_nvram_set("ip", 0, &ip[0], 0, 4);    // д�����ʧ������"ip"
 * \endcode
 *
 * \sa am_nvram_get()
 */
int am_nvram_set (char *p_name, int unit, uint8_t *p_buf, int offset, int len);

/**
 * \brief ��ȡNVRAM�洢�ε�������С
 *
 * \param[in]  p_name  ����ʧ�Դ洢��Ϣ������
 * \param[in]  unit    ����ʧ�Դ洢��Ϣ�ĵ�Ԫ��
 * \param[out] p_size  �洢�ε�������С
 *
 * \retval AM_OK      �ɹ�
 * \retval -AM_EINVAL  \a p_name �� \a p_buf ΪNULL
 * \retval -AM_EIO    ָ���ķ���ʧ�Դ洢��Ϣ�����ڻ����ʧ��
 *
 * \par ʾ��
 * \code
 *  #include "am_nvram.h"
 *  size_t size = 0;
 *  am_nvram_set("ip", 0, &size);    // д�����ʧ������"ip"
 * \endcode
 *
 * \sa am_nvram_get()
 */
int am_nvram_size_get (char *p_name, int unit, size_t *p_size);

/** @} am_if_nvram */

#ifdef __cplusplus
}
#endif   /* __cplusplus  */

#endif   /* __AM_NVRAM_H */

/* end of file */
