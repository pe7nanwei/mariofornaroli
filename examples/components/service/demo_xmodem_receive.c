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
 *    1���������崮�����ӵ������������ڵ��ô�demo֮ǰ
 *      ��ʼ����ش��ڡ�
 *    2����֧��Xmodem����λ��(����Tera_term��Xshell)
 *      �������������λ����ѡ����ص��ļ�ʹ��XmodemЭ�鴫�䡣
 *
 * - ʵ������:
 *   �ļ�����ÿ֡�涨�ֽ�(128��1024�ֽ�)���͵��նˣ��ն˶����ݽ��н��գ��������
 *   �п��ܳ���һ�¼�������:
 *   1�����ǽ��յ�֡���ݣ���ͨ�����ڽ���ȡ����һ֡���ݴ�ӡ�����¸�ʽ��ӡ����:
 *     ��Current : %d data: %s��
 *
 *   2�����Ƿ��ͷ�ȡ�����ͣ���ͨ�����ڴ�ӡ��Ϣ��The sender cancels the transmission!��
 *
 *   3�������ļ����ճɹ�����ͨ�����ڴ�ӡ��Ϣ��File received successfully !��
 *
 *   4���������ݳ�����ͨ�����ڴ�ӡ�����֡�����Ϣ��Current data err !��
 *
 *   5������δ�����ӵ���λ������ͨ�����ڴ�ӡ��Connection Failed!��
 *
 *   6�����ǳ�ʱ��Ȼδ�ܽ��յ����ݣ�����ӡ��Ϣ��No data was received for the timeout!��
 *
 *   7�����ǵ�ǰ֡У�����������ӡ��Ϣ��Current data check code err!��
 *
 * \note ��ӡ��Ϣ�Ĵ�����Ҫ��Xmodem����Ĵ��ڷֿ��������ӡ��Ϣ�����Xmodem����
 *       ��Xmodem�������ô���Ϊuart0�����ӡ��Ϣ����ӦΪuart1�����Ǵ�����Դ���ޣ�
 *       ���Խ���ӡ��Ϣע�͵������ļ�128�жԽ��յ������ݽ��д�ӡʱ�������м����
 *       �����ַ�'\0'����ӡ���̽���ֹ�������ӡʣ�µ����ݡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-6  xgg, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_xmodem_receive
 * \copydoc demo_xmodem_receive.c
 */
/** [src_xmodem_receive] */
#include "ametal.h"
#include "am_xmodem.h"
#include "am_vdebug.h"

/*******************************************************************************
ȫ�ֱ���
*******************************************************************************/
/* ���ջص���־*/
volatile static int __g_rx_flag  = 0;

/* ��ǰ�����¼�*/
volatile static int __g_rx_event = 0;

/* ������յ������ݻ���ָ��*/
volatile static void *__gp_rx_buff = NULL;

/**
 * \breif �û��ص�����
 * \param[in] p_arg    : �û���������ص������Ĳ��������û����ڻص�������
 *                       ʹ��Xmodem������ɽ��������˲�����
 * \param[in] p_frames : Xmodem���յ���һ֡���ݱ���ĵ�ַ���û���ֱ��
 *                       ʹ�øõ�ַ��ȡ���յ���һ֡����
 * \param[in] event    : ���ж�eventֵ��������������0����һ֡���ݽ���
 *                       �ɹ�����event������ǽ��յ����ֽ������ɹ����ܵ�һ
 *                       ֡���ݺ󣬿��Ե���am_xmodem_rec_ack_set�ӿ�
 *                       ���������һ֡���ݣ���eventֵΪ���������ʧ�ܣ���
 *                       ����event��ֵ�ж����������ִ���
 *                       -AM_ETIME       : ��һ֡���ݳ�ʱδ���յ�
 *                       -AM_EBADMSG     : δ��ʱ���ط��û��涨�Ĵ�����������Ȼ����
 *                       -AM_DATA_CAN    : ���ͷ�����ȡ�����͵��´������
 *                       -AM_DATA_SUC    : �����ļ��������
 *                       -AM_XMODEM_DOWN : ��λ��������δ�ڳ�ʱʱ������������λ��
 *                       -AM_XMODEM_CHECK_ERR : ��һ֡����У�������
 *
 * \note �����event�¼���δ���ɲο�am_xmodem.h��am_xmodem_user_rx_t����
 *    �ص�������ע��
 */
static void demo_rec_callback(void *p_arg, void *p_frames, int event)
{
    /* ���ջص���־��1*/
    __g_rx_flag  = 1;
    /* ��������¼�*/
    __g_rx_event = event;
    /* ����������ݻ����ָ��*/
    __gp_rx_buff = p_frames;
}

/* �������*/
void demo_xmodem_rec_entry (am_xmodem_rec_handle_t  handle)
{
    /* ���浱ǰ�ѽ��յ���֡��*/
    uint32_t index_rx_frames = 0;

    if (handle == NULL) {
        return;
    }

    /* ע����ջص�����*/
    am_xmodem_rec_cb_reg(handle, demo_rec_callback, (void *)handle);

    /* �������������ַ�*/
    am_xmodem_rec_start(handle);

    while (1) {
        /* �жϵ�ǰ�Ƿ��лص��¼�����*/
        if (__g_rx_flag) {

            __g_rx_flag = 0;

            if (__g_rx_event > 0) {
                __g_rx_event = 0;
                index_rx_frames++;
                /* �����ܵ������ݴ�ӡ����*/
                am_kprintf("Current %d data: %s\r\n",
                           index_rx_frames,
                           __gp_rx_buff);
                am_xmodem_rec_ack_set(handle);
                continue;
            }

            /* �жϵ�ǰ�ص��¼�*/
            switch (__g_rx_event) {

            /* �ļ�������ɺ󣬴�ӡ�ɹ������ļ���Ϣ*/
            case -AM_DATA_SUC:
                /* ���¼���־��0*/
                __g_rx_event    = 0;
                index_rx_frames = 0;
                am_kprintf("File received successfully !\r\n");
                return;

            /* �����쳣��ȡ�����Ͳ���ӡ��һ֡���ݳ���*/
            case -AM_EBADMSG:
                /* ���¼���־��0*/
                __g_rx_event = 0;
                /* ֡����1���ǳ����֡���*/
                index_rx_frames++;
                am_kprintf("Current %d data err !\r\n", index_rx_frames);
                am_xmodem_rec_can_set(handle);
                return;

            /* δ�����ӵ���λ��*/
            case -AM_XMODEM_DOWN:
                /* ���¼���־��0*/
                __g_rx_event = 0;
                am_kprintf("Connection Failed !\r\n");
                return;

            /* ���ͷ�ȡ������*/
            case -AM_DATA_CAN:
                /* ���¼���־��0*/
                __g_rx_event    = 0;
                index_rx_frames = 0;
                am_kprintf("The sender cancels the transmission!\r\n");
                return;

            /* ��ʱδ�ܽ��յ�����*/
            case -AM_ETIME:
                /* ���¼���־��0*/
                __g_rx_event    = 0;
                index_rx_frames = 0;
                am_kprintf("No data was received for the timeout!\r\n");
                return;

            /* ��ǰ֡У�������*/
            case -AM_XMODEM_CHECK_ERR:
                /* ���¼���־��0*/
                __g_rx_event = 0;
                index_rx_frames++;
                am_kprintf("Current %d data check code err!\r\n", index_rx_frames);
                am_xmodem_rec_can_set(handle);
                return;

            default:
                break;
            }
        }
        /* �û���������*/
    }
}

/** [src_xmodem_receive] */

/* end of file */
