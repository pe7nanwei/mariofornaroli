/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief xmodem������ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *    1��ͨ�����ڽ������뿪�������ӣ����ô��ڲ����ʵ�
 *    2������Ҫ��������ݱ�������Ӧ��С�������У���
 *      ��λ�������յ���λ�������������ַ��󣬽����ݰ���
 *      ����֡��С������λ����
 *
 * - ʵ������:
 *    ���շ������յ��ն˷��͵�__TRANS_DATA_LEN���ֽڵ���Ч�����ڴ�������п��ܻ�
 *    ͨ�����ڴ�ӡ������Ϣ��
 *    1����ǰ֡���ͳɹ����ӡ��The current data have been sent!��
 *
 *    2����ʱδ�ܽ��յ���Ӧ���ӡ��The timeout did not receive response!��
 *
 *    3�����շ���Ӧ�쳣���Ѿ��ط������������ӡ��Have been sent nak maxtimes!��
 *
 *    4���ļ�������ɻ��ӡ��File sent successfully!��
 *
 * \note ��ӡ��Ϣ�Ĵ�����Ҫ��Xmodem����Ĵ��ڷֿ��������ӡ��Ϣ�����Xmodem����
 *       ��Xmodem�������ô���Ϊuart0�����ӡ��Ϣ����ӦΪuart1�����Ǵ�����Դ���ޣ�
 *       ���Խ���ӡ��Ϣע�͵���
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-5 xgg, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_xmodem_transmit
 * \copydoc demo_xmodem_transmit.c
 */

/** [src_xmodem_transmit] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_xmodem.h"

/******************************************************************************
�궨��
*******************************************************************************/
#define __TRANS_DATA_LEN   (1024+3)     /**< \brief �ļ���С(��λΪbyte)*/
/*******************************************************************************
ȫ�ֱ���
*******************************************************************************/
/* xmodem���ͻص���־*/
volatile static int  __g_tx_flag = 0;

/* xmodem�����¼���־*/
volatile static int __g_tx_event = 0;

/* ���ݻ�����*/
static char __g_xmodem_test[__TRANS_DATA_LEN];

/**
 * \brief ���ͻص�����
 *
 * \param[in] p_arg : �û��Զ������
 * \param[in] event : ��ǰ�����¼����ɲο�am_xmodem.h�й���
 *                    am_xmodem_user_tx_t�ص��������͵�
 *                    ע�͡�
 * \note �û���Ҫ����event��������ǰ����Ĳ���
 */
static void demo_tx_callback (void *p_arg, int event)
{
    /* ���ͻص���־��1*/
    __g_tx_flag  = 1;
    /* ���淢���¼�*/
    __g_tx_event = event;
}

/* �������*/
void  demo_xmodem_tx_entry (am_xmodem_tx_handle_t  handle)
{
    uint32_t i = 0;

    /* һ֡���ݵĳ���*/
    uint32_t frames_len   = 0;

    /* ��ǰ�ѷ��͵��ֽ���*/
    uint32_t index_bytes  = 0;

    /* ��ǰ�Ѿ�����֡��*/
    uint32_t index_frames = 0;

    if (handle == NULL) {
        return;
    }

    /* ���ݻ��������*/
    for (i = 0; i < __TRANS_DATA_LEN; i++) {
        __g_xmodem_test[i] = i;
    }

    /* ע�ᷢ�ͻص�����*/
    am_xmodem_tx_cb_reg(handle, demo_tx_callback, (void *)handle);

    while (1) {

        if (__g_tx_flag) {

            __g_tx_flag = 0;

            switch (__g_tx_event) {

            /* ��������״̬*/
            case AM_XMODEM_NAK:
                frames_len = 128;
                am_xmodem_tx_pack(handle, __g_xmodem_test, frames_len);
                break;

            case AM_XMODEM_1k:
                frames_len = 1024;
                am_xmodem_tx_pack(handle, __g_xmodem_test, frames_len);
                break;

            /* ��ʱδ�ܽ��յ���Ӧ*/
            case -AM_ETIME:
                /* �¼���־��0*/
                __g_tx_event = 0;
                index_bytes  = 0;
                index_frames = 0;
                am_kprintf("The timeout did not receive response!\r\n");
                return;

            /* ���շ���Ӧ�쳣���Ѵﵽ����ط�����*/
            case AM_XMODEM_NAK_TIME:
                __g_tx_event = 0;
                index_bytes  = 0;
                index_frames = 0;
                am_kprintf("Have been sent nak maxtimes! \r\n");
                return;

            /* �ļ��������*/
            case AM_XMODEM_MOU_SUC:
                __g_tx_event = 0;
                index_bytes  = 0;
                index_frames = 0;
                am_kprintf("File sent successfully!\r\n");
                am_xmodem_tx_over(handle);
                return;

            case AM_XMODEM_ACK:
                __g_tx_event = 0;
                index_frames++;
                index_bytes += frames_len;
                /* �յ���һ֡��Ӧ��һ֡���������ɣ���ӡ��Ϣ*/
                am_kprintf("The current %d data have been sent!\r\n", index_frames);
                /* ������һ֡����*/
                if (__TRANS_DATA_LEN - index_bytes < frames_len) {
                    am_xmodem_tx_pack(handle,
                                      &__g_xmodem_test[index_bytes],
                                      __TRANS_DATA_LEN - index_bytes);
                } else {
                    am_xmodem_tx_pack(handle,
                                      &__g_xmodem_test[index_bytes],
                                      frames_len);
                }
                break;

            default :
                break;
            }
        }
    }
}

/** [src_xmodem_transmit] */

/* end of file */
