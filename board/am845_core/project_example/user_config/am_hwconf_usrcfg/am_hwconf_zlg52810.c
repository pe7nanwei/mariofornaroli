/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2017 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ZLG52810 �û������ļ�
 * \sa am_hwconf_zlg52810.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-28  pea, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zlg52810.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_zlg52810
 * \copydoc am_hwconf_zlg52810.c
 * @{
 */

am_local uint8_t __g_zlg52810_txbuf[128]; /**< \brief ���ͻ����� */
am_local uint8_t __g_zlg52810_rxbuf[128]; /**< \brief ���ջ����� */

/** \brief �豸ʵ�� */
am_local am_zlg52810_dev_t __g_zlg52810_dev;

/** \brief �豸��Ϣ */
am_local am_const am_zlg52810_devinfo_t __g_zlg52810_devinfo = {
    -1,                    /**< \brief RTS����   �������� */
    -1,                    /**< \brief CTS����   �������� */
    PIO0_28,                    /**< \brief ��λ���� */
    -1,                         /**< \brief RESTORE ���ţ����ڻָ��������� */
    -1,                         /**< \brief low power wakeup ���ţ����ڵ͹��Ļ��� */
    9600,                       /**< \brief ģ�鵱ǰʹ�õĲ����� */
    __g_zlg52810_rxbuf,         /**< \brief ���ջ��� */
    __g_zlg52810_txbuf,         /**< \brief ���ͻ��� */
    sizeof(__g_zlg52810_rxbuf), /**< \brief ���ջ��泤�� */
    sizeof(__g_zlg52810_txbuf)  /**< \brief ���ͻ��泤�� */
};

/**
 * \brief  ZLG52810 ʵ����ʼ������� ZLG52810 ��׼����������
 *
 * \return  ZLG52810 ��׼����������
 */
am_zlg52810_handle_t am_zlg52810_inst_init (void)
{
    am_uart_handle_t uart_handle = am_lpc84x_usart1_inst_init();

    return am_zlg52810_init(&__g_zlg52810_dev,
                            &__g_zlg52810_devinfo,
                             uart_handle);
}

/**
 * @}
 */

/* end of file */
