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
 * \brief UART������������DMA˫����ģʽ
 *
 *
 * \internal
 * \par Modification History
 * - 1.01 18-12-13  htf, first implementation.
 * \endinternal
 */

#ifndef __AM_KL26_UART_DMA_H
#define __AM_KL26_UART_DMA_H

#include "am_uart.h"
#include "hw/amhw_fsl_uart.h"
#include "am_fsl_uart.h"
#include "am_rngbuf.h"
#include "hw/amhw_kl26_dma.h"
#include "am_softimer.h"

typedef struct am_kl26_uart_dma_devinfo {

    const am_fsl_uart_devinfo_t      *p_uart_devinfo;    /**< \brief �����豸��Ϣ */
    amhw_kl26_dma_t                  *p_hw_dma;          /**< \brief DMA�Ĵ�����Ļ���ַ */
    uint8_t                           dma_chan_rx;       /**< \brief DMA����ͨ���� */
    char                             *p_dma_buffer;      /**< \brief DMA ӳ����ڴ� */
    char                             *p_rec_buffer;      /**< \brief ���ڽ��յ����ݵĻ����� */
    amhw_kl26_dma_buffer_size_set_t   dma_circular_size; /**< \brief DMA �Զ����λ����С */
    uint16_t                          dmabuffer_size;    /**< \brief DMA �����С */
    uint16_t                          recbuffer_size;    /**< \brief ���ڽ��ջ����С */
}am_kl26_uart_dma_devinfo_t;


typedef struct am_kl26_uart_dma_dev {
    am_fsl_uart_dev_t                 uart_dev;       /**< \brief �����豸 */
    const am_kl26_uart_dma_devinfo_t *p_devinfo;      /**< \brief DMA�����豸��Ϣ */

    struct am_rngbuf  rngbuf;                         /**< \brief ���λ�����*/
    uint32_t          buffer_size;                    /**< \brief ��������С*/
    uint32_t          dma_size;                       /**< \brief DMA��������С */

    char             *p_rec_buffer;                   /**< \brief ���ڽ��ջ����� */
    char             *p_dma_buffer;                   /**< \brief DMA���ջ����� */
    uint32_t          count ;                         /**< \brief DMA���λ���������ֵ*/
    am_softimer_t     timer;                          /**< \brief ��ʱ����������û����DMA�ж϶�ȡ����*/

}am_kl26_uart_dma_dev_t;

/**
 * \brief ��ʼ��UART������UART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return DMA UART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t am_uart_dma_init (
                     am_kl26_uart_dma_dev_t           *p_dev,
                     const am_kl26_uart_dma_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��UARTʱ�����ʼ��UART���ͷ������Դ
 * \param[in] p_dev : ָ��DMA�����豸��ָ��
 */
void am_uart_dma_deinit (am_fsl_uart_dev_t  *p_drv);

#endif



