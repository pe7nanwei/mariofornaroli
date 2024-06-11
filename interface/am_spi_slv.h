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
 * \brief spi�ӻ���׼�ӿ�
 *
 * \note ��ͨ���˽ӿڶ���һ��spi�ӻ��豸
 *
 * \internal
 * \par Modification History
 * -1.00 17-09-14 fra, first implementation
 * \endinternal
 */

#ifndef __AM_SPI_SLV_H
#define __AM_SPI_SLV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_list.h"

/**
 * \addtogroup am_if_spi_slv
 * \copydoc am_spi_slv.h
 * @{
 */

/**
 * \name SPI���豸ģʽ��־������am_spi_slv_mkdev()������mode����
 * @{
 */

#define AM_SPI_SLV_CPHA        0x01  /**< \brief ʱ����λ������             */
#define AM_SPI_SLV_CPOL        0x02  /**< \brief ʱ�Ӽ��Կ�����             */
#define AM_SPI_SLV_CS_HIGH     0x04  /**< \brief Ƭѡ����Ч                 */
#define AM_SPI_SLV_LSB_FIRST   0x08  /**< \brief ����λ�ȳ��ķ�ʽ��������֡ */
#define AM_SPI_SLV_3WIRE       0x10  /**< \brief 3��ģʽ��SI/SO �ź��߹���  */
#define AM_SPI_SLV_LOOP        0x20  /**< \brief �ػ�ģʽ                   */
#define AM_SPI_SLV_NO_CS       0x40  /**< \brief ���豸����, ��Ƭѡ         */

#define AM_SPI_SLV_MODE_0      (0 | 0)                 /**< \brief SPI�ӻ�ģʽ0 */
#define AM_SPI_SLV_MODE_1      (0 | AM_SPI_SLV_CPHA) /**< \brief SPI�ӻ�ģʽ1 */
#define AM_SPI_SLV_MODE_2      (AM_SPI_SLV_CPOL | 0) /**< \brief SPI�ӻ�ģʽ2 */
#define AM_SPI_SLV_MODE_3      (AM_SPI_SLV_CPOL | AM_SPI_SLV_CPHA) /**< \brief SPI�ӻ�ģʽ3 */

/** @} */

struct am_spi_slv_device;        /**< \brief ����SPI���豸�Ľṹ������ */

/**
 * \brief SPI���豸���������ṹ��
 */
struct am_spi_slv_drv_funcs {

    /** \brief �������豸  */
    int (*pfn_spi_slv_setup) (void *p_drv, struct am_spi_slv_device *p_dev);

    /** \brief �ر�SPI���豸   */
    int (*pfn_spi_slv_shutdown) (void *p_drv, struct am_spi_slv_device *p_dev);

};

/**
 * \brief SPI���豸 ��׼����ṹ��
 */
typedef struct am_spi_slv_serv {
    struct am_spi_slv_drv_funcs   *p_funcs;    /**< \brief SPI���豸��������     */
    void                          *p_drv;      /**< \brief SPI���豸������������ */
} am_spi_slv_serv_t;


/** \brief SPI���豸 ��׼�������������� */
typedef am_spi_slv_serv_t *am_spi_slv_handle_t;


/**
 * \brief SPI �ӻ�����
 *
 * - SPI �ӻ�����д�ĸ������ǵ��ڶ��ĸ�����Э������Ӧ�������ṩ \a rx_buf ��/��
 * \a tx_buf ����ĳЩ����£�����ͬ���������ṩ���ݴ����DMA��ַ�������Ļ�����
 * ����������ʹ��DMA���Խ������ݴ���Ĵ��ۡ�
 *
 * ������仺���� tx_bufΪ NULL rx_buf��ΪNULL�� ���ʾ�ӻ� ��0���͵������ϣ����ܵĴ浽rx_buf��
 * ������仺���� tx_buf��Ϊ NULL rx_bufΪNULL�� ���ʾ�ӻ� �������ܵ����� ��ֻ�����ķ�������
 *
 * - ���ڴ��У��������ǰ�CPU�ĵı����ֽ�˳���ţ������ֽ�˳���� (����ˣ�����
 * �豸ģʽ�����־�б������� AM_SPI_LSB_FIRST)�����磬��\a bits_per_word Ϊ
 * 16��������Ϊ 2N �ֽڳ� (\a len = 2N) ������CPU�ֽ�˳�㱣��N��16-bit�֡�
 *
 * - �� SPI ������ִ�С����2���ݴα�8-bitʱ����Щ�ڴ��е��ֽ����������bit����
 * �ڴ��У����������Ҷ���ģ���ˣ�δ���� (rx) ��δʹ�� (tx) ��λ���������Чλ��
 *
 */
typedef struct am_spi_slv_tansfer {
    /** \brief ָ���ͻ����ָ�� */
    const void *p_tx_buf;

    /** \brief ָ����ջ����ָ�� */
    void *p_rx_buf;

    /** \brief ���ݳ���(�ֽ���) */
    size_t  nbytes;

    /** \brief �ִ�С����Ϊ0����ʹ�� am_spi_device_t �����õ�ֵ */
    uint8_t     bits_per_word;

}am_spi_slv_transfer_t;

/**
 * \brief SPI���豸�ص���������
 */
typedef struct am_spi_slv_cb_funs{

    /** \brief ƬѡCS��Ч�ص� */
    int (*pfn_cs_active)(void *p_arg);

    /** \brief ƬѡCS��Ч�ص�  (nbytesΪ����Ƭѡ��Ч�д�������ֽ��� )*/
    int (*pfn_cs_inactive)(void *p_arg, size_t nbytes);

    /** \brief ��ȡ �������Ϣ  */
    int (*pfn_tansfer_get)(void *p_arg, am_spi_slv_transfer_t *p_trans);

} am_spi_slv_cb_funs_t;


/** \brief SPI���豸�����ṹ */
typedef struct am_spi_slv_device {

     /** \brief ���豸������SPI��׼����handle */
     am_spi_slv_handle_t  handle;

     /** \brief ���� ���ݴ������1�������֣��Ƚϳ������ִ�СΪ8-bit��12-bit�����ڴ�
      *   �У��ִ�СӦ����2���ݴη������磬20-bit�Դ�СӦʹ��32-bit�ڴ�
      *   Ϊ0ʱ��Ĭ��ѡ��Ϊ8bit
      */
     uint8_t                bits_per_word;

     /** \brief ���豸��SPIģʽ��־����ο���SPI�ӻ�ģʽ��־��
      *
      * �ò�����������SPI���豸��ʱ����λ�ͼ��ԣ���Ҫ������������ͬ
      */
     uint16_t               mode;

     /** \brief ���豸�ص����� */
     am_spi_slv_cb_funs_t *p_slv_cb_funcs;

     /** \brief �ص��������� */
     void                   *p_arg;

} am_spi_slv_device_t;

/**
 * \brief ����SPI�豸�ṹ�����
 *
 * \param[in] p_dev         : SPI�ӻ��豸������ָ��
 * \param[in] handle        : SPI��׼����������
 * \param[in] bits_per_word : �ִ�С��Ϊ0ʱʹ��Ĭ�ϵġ�8-bit�ִ�С��
 * \param[in] mode          : �豸ģʽ��־������SPIģʽ��־��
 * \param[in] p_slv_cb_funcs : SPI���豸�ص�����
 * \param[in] p_arg         : SPI���豸�ص������Ĳ���
 *
 * \return ��
 *
 * \par ����
 * �� am_spi_slv_setup()
 */
am_static_inline
void am_spi_slv_mkdev (am_spi_slv_device_t  *p_dev,
                       am_spi_slv_handle_t   handle,
                       uint8_t               bits_per_word,
                       uint16_t              mode,
                       am_spi_slv_cb_funs_t *p_slv_cb_funcs,
                       void                 *p_arg)
{
    p_dev->handle             = handle;
    p_dev->bits_per_word      = bits_per_word;
    p_dev->mode               = mode;
    p_dev->p_slv_cb_funcs     = p_slv_cb_funcs;
    p_dev->p_arg              = p_arg;

}


/**
 * \brief ����SPI�ӻ��豸
 *
 * \attention ��SPI�ӻ��豸��ʹ��ǰ�������ȵ��ñ������������ã����籾��������
 *            ������һ��������ʹ�ô�SPI�ӻ�
 *
 * \param[in] p_dev : SPI�ӻ��豸
 *
 * \retval   AM_OK           : ���óɹ�
 * \retval  -AM_ENOTSUP      : ����ʧ�ܣ���֧�ֵ�λ��ģʽ��
 *
 * \par ʾ��
 * \code
 *  am_spi_slv_device_t spi_slv_dev;     // ���豸�����ṹ
 *
 * // ��ʼ���豸�����ṹ
 * am_spi_slv_mkdev(&spi_slv_dev,
 *                    handle,         // SPI�ӻ���׼����handle
 *                    8��                                 // �ִ�СΪ8-bit
 *                    AM_SPI_MODE_1,  // SPI ģʽ1
 *                    __g_spi_slv_cb_funs,   // �ӻ��ص�����Ϊ__g_spi_slv_cb_funs
 *                    &spi_slv_dev);          // �ӻ��ص���������ڲ���
 *
 * // �����豸
 * am_spi_slv_setup(&spi_slv_dev);
 *
 * \endcode
 *
 */
am_static_inline
int am_spi_slv_setup (am_spi_slv_device_t *p_dev)
{
    return p_dev->handle->p_funcs->pfn_spi_slv_setup(p_dev->handle->p_drv, p_dev);
}



/**
 * \brief �ر�SPI�ӻ�
 *
 * \param[in]  handle : SPI��׼����������
 * \param[out] p_dev  : SPI�ӻ��豸
 *
 * \retval  AM_OK     : ���óɹ�
 */
am_static_inline
int am_spi_slv_shutdown (am_spi_slv_device_t *p_dev)
{
    return p_dev->handle->p_funcs->pfn_spi_slv_shutdown(p_dev->handle->p_drv, p_dev);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_SLV_H */

/* end of file */
