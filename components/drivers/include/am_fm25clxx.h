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
 * \brief ���깫˾��MX25ϵ��FM25CLXXоƬ���� 
 * 
 * ��֪����оƬ�� 
 *   - MX25L1606E
 *   - MX25L8006E
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-09-14  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AM_FM25CLXX_H
#define __AM_FM25CLXX_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "ametal.h"
#include "am_types.h"
#include "am_gpio.h"
#include "am_spi.h"
    
/*******************************************************************************
  �궨��
*******************************************************************************/

/**
 * \name SPI FLASH�ĸ�������
 * @{
 */

#define  __FM25CL64B_WREN  0x06  //����дʹ��������
#define  __FM25CL64B_WRDI  0x04  //д����
#define  __FM25CL64B_RDSR  0x05  //��״̬�Ĵ���
#define  __FM25CL64B_WRSR  0x01  //д״̬�Ĵ���
#define  __FM25CL64B_READ  0x03  //��ȡ�ڴ�����
#define  __FM25CL64B_WRITE 0x02  //д���ڴ�����
/** @} */


/**
 * \name ״̬�Ĵ�����ֵ
 * @{
 * �Ĵ���˵����bit7:   WPEN  д����ʹ��λ��
 *            bit3:2  BP1:0 �鱣����
 *                          00--��
 *                          01--��1/4
 *                          10--��1/2
 *                          11--ȫ��
 *            bit1    WEL   дʹ�ܣ�
 */
#define  __PROTECTED_ALL        0x8E //ȫ����ַд����:0000h-1FFFh
#define  __PROTECTED_HALF       0x8A //��벿��д����:1000h-1FFFh
#define  __PROTECTED_HALF_HALF  0x86 //��1/4д����   :1800h-1FFFh
#define  __PROTECTED_NO         0x82 //��д����
/** @} */

/**
 * \addtogroup am_if_fm25clxx
 * \copydoc am_fm25clxx.h
 * @{
 */

 
/**
 * \brief FM25CLXX ʵ����Ϣ
 */
typedef struct am_fm25clxx_devinfo {
 
    uint16_t          spi_mode;      /**< \brief ����ʹ�õ�SPIģʽ */
    int               spi_cs_pin;    /**< \brief SPIƬѡ����       */
    uint32_t          spi_speed;     /**< \brief ʹ�õ�SPI����     */
} am_fm25clxx_devinfo_t;
     
/**
 * \brief FM25CLXX ʵ��
 */
typedef struct am_fm25clxx_dev {
    am_spi_device_t              spi_dev;        /**< \brief SPI�豸              */
    const am_fm25clxx_devinfo_t *p_devinfo;      /**< \brief ʵ����Ϣ            */
} am_fm25clxx_dev_t;

/** \brief ���� FM25CLXX ��ʵ��������� */
typedef struct am_fm25clxx_dev *am_fm25clxx_handle_t;


/** 
 * \brief ��ʼ�� FM25CLXX����ȡ���� FM25CLXX �� handle
 * 
 * \param[in] p_dev      : ָ�� FM25CLXX ʵ����ָ��
 * \param[in] p_devinfo  : ָ�� FM25CLXX ʵ����Ϣ��ָ��
 * \param[in] handle     : SPI��׼����handle,ʹ�ø� handle �� FM25CLXX ����ͨ��
 *
 * \return FM25CLXX ��������������ʼ��ʧ�ܣ��򷵻�ֵΪNULL
 */
am_fm25clxx_handle_t am_fm25clxx_init(am_fm25clxx_dev_t            *p_dev,
                                      const am_fm25clxx_devinfo_t  *p_devinfo,
                                      am_spi_handle_t               spi_handle);

/**
 * \brief ��ȡ����
 *
 * \param[in] handle : FM25CLXX �������
 * \param[in] addr   : ��ȡ���ݵ��׵�ַ
 * \param[in] p_buf  : ��ȡ���ݴ�ŵĻ�����
 * \param[in] len    : ���ݶ�ȡ�ĳ���
 *
 * \retval  AM_OK     : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡ����ʧ��, ��������
 * \retval -AM_EIO    : ��ȡ����ʧ��, SPIͨ�ų���
 */
int am_fm25clxx_read(am_fm25clxx_handle_t  handle,
                     uint32_t              addr,
                     uint8_t              *p_buf,
                     uint32_t              len);


/** 
 * \brief д������
 *
 * \param[in] handle : FM25CLXX �������
 * \param[in] addr   : д�����ݵ��׵�ַ
 * \param[in] p_buf  : д�����ݴ�ŵĻ�����
 * \param[in] len    : ���ݶ�ȡ�ĳ���
 *
 * \retval  AM_OK     : ��ȡ���ݳɹ�
 * \retval -AM_EINVAL : ��ȡ����ʧ��, ��������
 * \retval -AM_EIO    : ��ȡ����ʧ��, SPIͨ�ų���
 */
int am_fm25clxx_write(am_fm25clxx_handle_t  handle,
                      uint32_t              addr,
                      uint8_t              *p_buf,
                      uint32_t              len);

                            
/** 
 * \brief ��ȡFM25CLXX״̬�Ĵ�����ֵ
 * 
 * \param[in]  handle : FM25CLXX �������
 * \param[out] p_stat : ��ȡ����״̬�Ĵ�����ֵ
 *
 * \retval  AM_OK     : ��ȡ״̬�Ĵ����ɹ�
 * \retval -AM_EINVAL : ��ȡʧ��, ��������
 * \retval -AM_EIO    : ��ȡʧ��, SPIͨ�ų���
 */
int am_fm25clxx_status_read(am_fm25clxx_handle_t  handle,
                            uint8_t              *p_stat);

/** 
 * \brief ����FM25CLXX״̬�Ĵ�����ֵ
 * 
 * \param[in] handle : FM25CLXX �������
 * \param[in] val    : д��״̬�Ĵ�����ֵ
 *
 * \retval  AM_OK     : д��״̬�Ĵ����ɹ�
 * \retval -AM_EINVAL : д��ʧ��, ��������
 * \retval -AM_EIO    : д��ʧ��, SPIͨ�ų���
 *
 */
int am_fm25clxx_status_write(am_fm25clxx_handle_t  handle,
                             uint8_t               val);

/** 
 * \brief FM25CLXX���ʼ�����ͷ������Դ
 * 
 *     ���ʼ����FM25CLXX��غ���������ʹ�ã�����ʹ��FM25CLXX��ȡ
 * ����NVRAM��׼����handle��
 * 
 * \param[in] p_dev : ָ�� FM25CLXX �豸��ָ��
 *
 * \return ��
 */
void am_fm25clxx_deinit(am_fm25clxx_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __AM_FM25CLXX_H */

/* end of file */
