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
#include "am_nvram.h"

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

    /**< \brief SPI�豸              */
    am_spi_device_t              spi_dev;

    /**< \brief fm25clxx�豸�ṩ�� NVRAM ��׼���� */
    am_nvram_dev_t               *p_serv;

    /**< \brief ʵ����Ϣ             */
    const am_fm25clxx_devinfo_t  *p_devinfo;

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
 * \brief ��ʼ��fm25clxx��NVRAM���ܣ���ϵͳ�ṩ  NVRAM ��׼����
 * 
 *   �ú�����fm25clxx�豸��Ϊ��׼��NVRAM�豸ע�ᵽϵͳ��
 * 
 * \param[in] handle      : ep24cxx�������
 * \param[in] p_dev       : NVRAM ��׼�豸
 * \param[in] p_dev_name  : NVRAM ��׼�豸���豸��
 *
 * \return AM_OK, �ṩNVRAM����ɹ�������ֵ���ṩNVRAM����ʧ�ܡ�
 *
 * \note ʹ�øú����󣬼���ʹ��NVRAM��׼�ӿ� am_nvram_set() �� am_nvram_get() ����
 * fm25clxx�洢����ʹ�õĶα����� am_nvram_cfg.c�ļ��ж��壬�洢���������豸������
 * ��дΪ�˴� p_name ָ�������֣��� p_name Ϊ  "fm24c02", �������g_nvram_segs[]��
 * �����б�����������5���洢�Σ�����Ϊʾ������
 *    {"ip",         0,  0,  4,   "fm24c02"},
 *    {"ip",         1,  4,  4,   "fm24c02"},
 *    {"temp_limit", 0,  8,  4,   "fm24c02"},
 *    {"system",     0,  12, 50,  "fm24c02"},
 *    {"test",       0,  62, 178, "fm24c02"},
 */
int am_fm25clxx_nvram_init (am_fm25clxx_handle_t   handle,
                            am_nvram_dev_t        *p_dev,
                            const char            *p_dev_name);
                                
/**
 * @}
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __AM_FM25CLXX_H */

/* end of file */
