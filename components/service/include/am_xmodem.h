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
 * \brief  XmodemЭ�� Ӧ�ýӿ��ļ�
 *
 * \internal
 * \par Modification History
 * - 1.00 18-8-31 , xgg, first implementation.
 * \endinternal
 */
#ifndef __AM_XMODEM_H
#define __AM_XMODEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_crc.h"
#include "am_uart.h"
#include "am_errno.h"
#include "am_softimer.h"

/**
 * @addtogroup am_if_am_xmodem
 * @copydoc am_xmodem.h
 * @{
 */

/**
 * \name Xmodem ����ģʽ
 *
 * @{
 */
#define AM_XMODEM_1K_MODE     0    /**< \brief ���ݶ���1K�ֽڵĹ���ģʽ*/
#define AM_XMODEM_128_MODE    1    /**< \brief ���ݶ���128�ֽڵĹ���ģʽ*/

/** @} */

/**
 * \name XmodemУ�鷽ʽ
 *
 * @{
 */
#define AM_XMODEM_CRC_MODE    0    /**< \brief ����CRCУ�� */
#define AM_XMODEM_SUM_MODE    1    /**< \brief �����ۻ���У�� */

/** @} */

/**
 * \name Xmodem���ܹ����в������¼�
 * ���º궨�����Xmodem���ܻص������д��룬�û���Ҫ���ݴ����event�¼�����
 * ��һ���Ĳ�����
 * @{
 */
#define AM_DATA_CAN          0x19  /**< \brief ���ͷ�ȡ������*/
#define AM_DATA_SUC          0x20  /**< \brief �ļ����ճɹ� */
#define AM_XMODEM_DOWN       0x25  /**< \brief Xmodem����δ����*/
#define AM_XMODEM_CHECK_ERR  0x26  /**< \brief У�������*/
/** @} */

/**
 * \name Xmodem���͹����в������¼�
 *
 * @{
 */
#define AM_XMODEM_ACK        0x06 /**< \brief ���շ���ȷ���źţ���ʾһ֡���ݽ������ */
#define AM_XMODEM_NAK        0x15 /**< \brief Xmodem������128�ֽڹ���ģʽ */
#define AM_XMODEM_1k         'C'  /**< \brief Xmodem������1K�ֽڹ���ģʽ*/
#define AM_XMODEM_CAN        0x18 /**< \brief ���շ�����ȡ������ */
#define AM_XMODEM_NAK_TIME   0x40 /**< \brief ���ط�������ط����� */
#define AM_XMODEM_MOU_SUC    0x41 /**< \brief �ļ�������� */

/** @} */

/*******************************************************************************
  ״̬������ָ�����Ͷ���
*******************************************************************************/
/** \brief ����Xmodem����״̬������ָ������ */
typedef am_bool_t (*pfn_xmodem_rx_t)(void *p_arg, char inchar);

/** \brief ����Xmodem����״̬������ָ������ */
typedef am_bool_t (*pfn_xmodem_tx_t)(void *p_arg, char *p_outchar);

/******************************************************************************/
/**
 * \breif �û����ջص�����
 *
 * \param[in] p_arg    : �û���������ص������Ĳ��������û����ڻص�������
 *                       ʹ��Xmodem������ɽ��������˲�����
 * \param[in] p_frames : Xmodem���յ���һ֡���ݱ���ĵ�ַ���û���ֱ��
 *                       ʹ�øõ�ַ��ȡ���յ���һ֡����
 * \param[in] event    : ���ж�eventֵ��������������0����һ֡���ݽ���
 *                       �ɹ���event������ǽ��յ����ֽ�������event
 *                       ֵΪ��������ֵΪ-AM_DATA_SUC�������ļ����ճ�
 *                       �����������ʧ�ܿɸ���event��ֵ�ж����������ִ���
 *                       -AM_ETIME            : ��ǰ֡���ݳ�ʱδ���յ�
 *                       -AM_EBADMSG          : δ��ʱ���ط���������������Ȼ����
 *                       -AM_DATA_CAN         : ���ͷ�����ȡ�����͵��´������
 *                       -AM_XMODEM_DOWN      : δ��������λ��
 *                       -AM_XMODEM_CHECK_ERR : У�������
 * \note ���ײ����������������������޷����Դ�����¼�ʱ��������ͨ���˺�����֪ͨ
 *       �û������û�������δ����Ӧ���¼������������¼�������û���Ҫ�ر�ע��:
 * 1��event > 0 ʱ������ǰ�����Ѿ��յ���һ֡���ݣ�֡���ݵĴ�С������event��,����
 *   �û���ȡ�����¼�ʱ,�����Ҫ������ȡ��һ֡������Ӧ�õ���am_xmodem_rec_ack_set
 *   ������
 * 2��event == -AM_XMODEM_DOWN�����ն�δ�ܽ���Xmodem���ӣ����û���Ҫ���½�������
 *   ����ǰ�¼�ʱ���Ե���am_xmodem_rec_start�������½������ӡ������޲���ֱ���˳���
 * 3��event == -AM_ETIME �����ն�δ���ڹ涨�涨ʱ���ܽ��յ�֡���ݣ������û�����
 *    �޲����˳���
 * 4��event == -AM_DATA_CAN �������ͷ�����ȡ���˴��䣬�û�������������������ֱ��
 *    �˳���
 * 5��event == -AM_EBADMSG ������ǰ����֡�д����Ѿ��ط���������������Ȼ��
 *    ���û����Կ�����λ�����͵������Ƿ������⡣
 * 6��event == -AM_XMODEM_CHECK_ERR У��������û��������½���У�顣
 *
 * \return ��
 */
typedef void (*am_xmodem_user_rx_t) (void    *p_arg,
                                     void    *frames,
                                     int      event);

/** \brief xmodemЭ������豸��Ϣ�ṹ�� */
typedef struct am_xmodem_rec_dev_info {
    char      *frames_info;     /**< \brief ����Xmodemһ֡��Ϣ������ָ�� */
    uint8_t    nak_max_times;   /**< \brief �ط������� */
    uint32_t   frames_bytes;    /**< \brief һ֡���ݵ��ֽ��� */
    uint32_t   data_mode;       /**< \brief ����ģʽ  */
    uint32_t   parity_mode;     /**< \brief У��ģʽ */
    uint32_t   rx_timeout;      /**< \brief ���ճ�ʱʱ�� */
    /** \brief �������ʱ��
     * �û��ڵ���am_xmodem_rec_start�ӿ��������ܺ󣬻�ÿ��
     * start_time��ʱ�䷢�������ַ���ֱ��xmodem�������ӣ����
     * ���ط���nak_max_times����Ȼ���ܽ������ӣ���ͨ���ص�����
     * ����event = -AM_XMODEM_DOWN��֪ͨ�û�Xmodemδ��
     * ���ӡ�
     */
    uint32_t   start_time;
} am_xmodem_rec_dev_info_t;

/**
 * \brief xmodem�����豸�ṹ��
 */
typedef struct am_xmodem_rec_dev {
    int                  rx_bytes;       /**< \brief ��ǰ���յ����ֽ��� */
    char                 fra_sum_parity; /**< \brief �����ۻ���У��λ */
    uint16_t             fra_crc_pry;    /**< \brief ����CRCУ���� */
    volatile uint8_t     char_get_state; /**< \brief �ַ���ȡ״̬��־λ */
    volatile uint8_t     nak_state;      /**< \brief ��ǰ�ط�״̬ */
    volatile uint8_t     frames_num;     /**< \brief ��ǰ��һ֡���ݵ����к� */
    volatile uint8_t     con_state;      /**< \brief Xmodemͨ������״̬*/
    am_softimer_t        rx_softimer;    /**< \brief ���ճ�ʱ��ʱ�� */
    am_uart_handle_t     uart_handle;    /**< \brief ���ھ�� */
    am_xmodem_user_rx_t  pfn_rx_callback;/**< \brief ע���û����ܻص����� */
    am_crc_handle_t      crc_handle;     /**< \brief ��׼CRC���*/
    am_crc_pattern_t     crc_pattern;    /**< \brief ���� CRC ģ�� */
    void                *p_arg;          /**< \brief �û��ص��������� */
    volatile pfn_xmodem_rx_t  p_rec_func;/**< \brief ����״̬���������*/

    /* �����豸��Ϣ�ṹ��ָ��*/
    const am_xmodem_rec_dev_info_t *p_rec_devinfo;
} am_xmodem_rec_dev_t;

/** \brief xmodem���ܱ�׼�������������Ͷ��� */
typedef am_xmodem_rec_dev_t *am_xmodem_rec_handle_t;

/******************************************************************************/

/**
 * \brief �û����ͻص�����
 *
 * \param[in] p_arg : �û���Ҫ����Ĳ���,���Լ�����
 * \param[in] event : �ص����ص��¼����û��ɸ����¼�������������һ������
 * 1��event == AM_XMODEM_NAKʱ,Xmodem������128�ֽڹ���ģʽ��
 *   ������Ҫ��ʼ���͵�һ֡���ݣ����ڻص���ֱ�ӵ���am_xmodem_tx_pack�ӿ�
 *   ����������־������ѭ���е��ô˽ӿڣ�����������κ����ݣ������޲�����
 * 2��event == AM_XMODEM_1Kʱ,Xmodem������1K�ֽڹ���ģʽ��
 *   ͬ�����û���Ҫ��ʼ���͵�һ֡���ݣ��ɵ���am_xmodem_tx_pack�ӿڻ��޲���
 * 3��event == AM_XMODEM_NAK_TIMEʱ,�ط������ﵽ�涨ֵ(�ڲ���ȡ������);
 *   ���¼����������ѷ��͵����շ��������շ�Ҫ���ط�����ʱ�������ڲ��Ѿ���Ҫ����
 *   ����������������ȡ���˷��ͣ��ɿ��ǽ��շ��Ƿ�����쳣��
 * 4��event == AM_XMODEM_MOU_SUCʱ,�ļ��������;
 *   ��ǰ�����Ѿ���������ļ�������ϣ�Xmodem�����Ѿ��Ͽ����û�����ѡ���޲�����
 * 5��event == AM_XMODEM_CANʱ,�������շ�ȡ���˴���;
 *   ���¼��������շ��Ͽ���Xmodem���ӣ��û����Կ����޲���ֱ���˳�
 * 6��event == AM_XMODEM_ACKʱ��һ֡���ݷ������;
 *   ���¼�������ǰ��һ֡�����Ѿ�������ϣ��û����Ե���am_xmodem_tx_pack��������
 *   ������һ֡
 * 7��event == -AM_ETIMEʱ,���շ����յ�һ֡���ݺ�δ�ڹ涨��ʱ���ڻ�Ӧ;
 *
 * \return ��
 */
typedef void (*am_xmodem_user_tx_t) (void *p_arg, int event);


/** \brief XmodemЭ�鷢���豸��Ϣ�ṹ��*/
typedef struct am_xmodem_tx_dev_info {
    uint32_t   tx_timeout;       /**< \brief ���ͳ�ʱʱ��*/
    uint8_t    nak_times_max;    /**< \brief ���������ط�����*/
} am_xmodem_tx_dev_info_t;

/**
 * \brief Xmodem�����豸
 */
typedef struct am_xmodem_tx_dev {
    char                           fra_sum_parity; /**< \brief �����ۻ���У��λ */
    char                          *p_tx_buf;       /**< \brief �ļ�ָ�� */
    uint8_t                        nake_state;     /**< \brief ��ǰ�ط�״̬ */
    uint8_t                        tx_state;       /**< \brief ���ƻ�ȡ�ַ�����״̬*/
    uint16_t                       fra_crc_pry;    /**< \brief ����CRCУ���� */
    uint32_t                       frame_tx_bytes; /**< \brief ���͵�һ֡���ݴ�С */
    uint32_t                       doc_bytes;      /**< \brief �ļ���С */
    uint32_t                       ctrlz_num;      /**< \brief �����ֽ���*/
    volatile uint8_t               state_flag;     /**< \brief ���ڷֱ����ģʽ�ַ�*/
    volatile uint32_t              tx_bytes;       /**< \brief ��ǰһ֡�ѷ��Ͷ��� */
    volatile uint32_t              frames_num;     /**< \brief ��ǰ��һ֡���ݵ����к� */
    pfn_xmodem_tx_t                p_tx_func;      /**< \brief ״̬���������*/
    am_softimer_t                  tx_softimer;    /**< \brief ���ճ�ʱ��ʱ�� */
    void                          *p_arg;          /**< \brief �û��ص��������� */
    am_xmodem_user_tx_t            pfn_tx_callback;/**< \brief ע���û����ͻص����� */
    am_crc_handle_t                crc_handle;     /**< \brief CRC���*/
    am_crc_pattern_t               crc_pattern;    /**< \brief CRCģ��*/
    am_uart_handle_t               uart_handle;    /**< \brief ���ھ�� */
    const am_xmodem_tx_dev_info_t *p_tx_devinfo;   /**< \brief �����豸��Ϣ�ṹ��ָ��*/
}am_xmodem_tx_dev_t;

/** \brief xmodem���ܱ�׼�������������Ͷ��� */
typedef am_xmodem_tx_dev_t *am_xmodem_tx_handle_t;

/******************************************************************************
 Xmodem ���������ӿ�
*******************************************************************************/
/**
 * \brief �豸��ʼ������
 *
 * \param[in] p_dev       : xmodem�豸
 * \param[in] p_decinfo   : �豸��Ϣ�ṹ��
 * \param[in] uart_handle : ���ھ��
 * \param[in] crc_handle  : CRC���
 *
 * \return ��ΪNULL���򷵻�ֵΪXmodem���վ����
 *         ��ΪNULL������������Ч��ʱ����ʼ��ʧ��
 */
am_xmodem_rec_handle_t  am_xmodem_rec_init (
                                 am_xmodem_rec_dev_t            *p_dev,
                                 const am_xmodem_rec_dev_info_t *p_devinfo,
                                 am_uart_handle_t                uart_handle,
                                 am_crc_handle_t                 crc_handle);

/**
 * \brief xmodem���ջص�����ע��
 *
 * \param[in] handle     : xmodem�豸���
 * \param[in] pfn_rec_cb : �û��ص�����
 * \param[in] p_arg      : �û�����Ĳ���
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_rec_cb_reg(am_xmodem_rec_handle_t  handle,
                               am_xmodem_user_rx_t     pfn_rec_cb,
                               void                   *p_arg);

/**
 * \brief ��ʼ���ܺ���(Xmodem�������պ���)
 *
 * \param[in] handle : xmodem�豸���
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_rec_start (am_xmodem_rec_handle_t handle);

/**
 * \brief �������պ���
 *
 * \param[in] handle : xmodem�豸���
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_rec_ack_set (am_xmodem_rec_handle_t handle);

/**
 * \brief ȡ�����亯��
 *
 * \param[in] p_dev xmodem�豸���
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_rec_can_set (am_xmodem_rec_handle_t handle);

/******************************************************************************
 Xmodem ���������ӿ�
*******************************************************************************/
/**
 * \brief �����豸��ʼ������
 *
 * \param[in] p_dev         : Xmodem�����豸
 * \param[in] p_tra_devinfo : Xmodem�����豸��Ϣ�ṹ��
 * \param[in] uart_handle   : ���ھ��
 * \param[in] crc_handle    : CRC���
 *
 * \return ��ΪNULL����ֵΪXmodem���;����ΪNULL����������Ч��ʱ����ʼ��ʧ��
 */
am_xmodem_tx_handle_t  am_xmodem_tx_init (
                              am_xmodem_tx_dev_t            *p_dev,
                              const am_xmodem_tx_dev_info_t *p_tra_devinfo,
                              am_uart_handle_t               uart_handle,
                              am_crc_handle_t                crc_handle);

/**
 * \brief ֡���ݷ��ͺ���
 *
 * \param[in] handle    : Xmodem���;��
 * \param[in] p_doc     : �û���Ҫ���͵������ָ��
 * \param[in] pack_size : ��Ҫ���͵����鳤�ȣ����ص�����������¼�ΪAM_XMODEM_NAK,
 *                        ��pack_size�����ֵΪ128,���ص�����������¼�Ϊ
 *                        AM_XMODEM_1K,��pack_size�����ֵΪ1024������ļ����һ
 *                        ֡���ݲ�����128����1024��pack_size��ֵ�û������Լ�����
 *                        ������Ϊ�ļ�ʣ�µ��ֽ�����
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_tx_pack (am_xmodem_tx_handle_t  handle,
                            char                  *p_doc,
                            uint32_t               pack_size);

/**
 * \brief xmodem���ͻص�����ע��
 *
 * \param[in] handle    : Xmodem���;��
 * \param[in] pfn_tx_cb : �û��ص�����ָ��
 * \param[in] p_arg     : �û������豸����
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_tx_cb_reg (am_xmodem_tx_handle_t handle,
                              am_xmodem_user_tx_t  pfn_tx_cb,
                              void                *p_arg);

/**
 * \brief �ļ����ͽ�������
 *
 * \param[in] handle : Xmodem���;��
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_tx_over (am_xmodem_tx_handle_t handle);

/**
 * \brief �û�ȡ�����ͺ���
 *
 * \param[in] handle : Xmodem���;��
 *
 * \retval AM_OK      : ִ�гɹ�
 * \retval -AM_EINVAL : ������Ч
 */
am_err_t am_xmodem_tx_can_set (am_xmodem_tx_handle_t handle);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_XMODEM_H */

/* end of file */
