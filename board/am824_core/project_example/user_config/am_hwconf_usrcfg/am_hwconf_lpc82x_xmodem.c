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
 * \brief LPC82x Xmodem �û������ļ�
 * \sa am_hwconf_lpc82x_xmodem.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-08-31  xgg, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_uart.h"
#include "am_xmodem.h"
#include "am_lpc82x.h"
#include "am_lpc82x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_lpc82x_xmodem
 * \copydoc am_hwconf_lpc82x_xmodem.c
 * @{
 */

/* Xmodem���͹���ģʽ*/
#define __MODE   AM_XMODEM_128_MODE
#if (__MODE == AM_XMODEM_128_MODE)
#define  __BUFF_SIZE      128
#elif (__MODE == AM_XMODEM_1K_MODE)
#define  __BUFF_SIZE      1024
#endif

/* ���ݻ�����*/
static char __g_xmodem_rec_buf[__BUFF_SIZE];

/* �����豸ʵ��*/
static am_xmodem_tx_dev_t  __g_xmodem_tx_dev;

/* �����豸ʵ��*/
static am_xmodem_rec_dev_t __g_xmodem_rec_dev;

/* ����Xmodem�����豸��Ϣ�ṹ�� */
static const am_xmodem_rec_dev_info_t  __g_xmodem_dev_info = {
    __g_xmodem_rec_buf,         /**< \brief ���ջ�����*/
    10,                         /**< \brief ����ط�����*/
    sizeof(__g_xmodem_rec_buf), /**< \brief ���ջ�������С */
    __MODE,                     /**< \brief ���չ���ģʽ*/
    AM_XMODEM_CRC_MODE,         /**< \brief У�鷽ʽ*/
    3000,                       /**< \brief ���ճ�ʱʱ��*/
    8000                        /**< \brief �������ʱ��*/
};

/* ����Xmodem�����豸��Ϣ�ṹ��*/
static const am_xmodem_tx_dev_info_t __g_xmodem_tx_dev_info = {
   1000,        /**< \brief ���ͳ�ʱʱ��*/
   3,           /**< \brief ����ط�����*/
};


/* Xmodem����ʵ����ʼ������ȡXmodem���Ͳ������*/
am_xmodem_tx_handle_t   am_lpc82x_xmodem_tx_inst_init (void)
{
    am_crc_handle_t   crc_handle   = NULL;
    am_uart_handle_t  lpc82x_uart1 = NULL;

    lpc82x_uart1 = am_lpc82x_usart1_inst_init();

    crc_handle = am_lpc82x_crc_inst_init();

    return am_xmodem_tx_init(&__g_xmodem_tx_dev,
                             &__g_xmodem_tx_dev_info,
                             lpc82x_uart1,
                             crc_handle);
}

/* Xmodem����ʵ����ʼ������ȡXmodem���ղ������*/
am_xmodem_rec_handle_t   am_lpc82x_xmodem_rec_inst_init (void)
{
    am_crc_handle_t   crc_handle   = NULL;
    am_uart_handle_t  lpc82x_uart1 = NULL;

    lpc82x_uart1 = am_lpc82x_usart1_inst_init();

    crc_handle = am_lpc82x_crc_inst_init();

    return am_xmodem_rec_init(&__g_xmodem_rec_dev,
                              &__g_xmodem_dev_info,
                              lpc82x_uart1,
                              crc_handle);
}

/**
 * @}
 */

/* end of file */
