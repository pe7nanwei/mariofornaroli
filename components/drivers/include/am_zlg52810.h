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
 * \brief ZLG52810�ӿں���
 *
 * \internal
 * \par Modification History
 * - 1.00 19-01-22  htf, first implementation.
 * \endinternal
 */

#ifndef __AM_ZLG52810_H
#define __AM_ZLG52810_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_types.h"
#include "am_i2c.h"
#include "am_softimer.h"
#include "am_uart_rngbuf.h"

/**
 * @addtogroup am_if_zlg52810
 * @copydoc am_zlg52810.h
 * @{
 */

/* \brief  ZLG52810 �����ʶ */
#define  AM_ZLG52810_RECVIVE_INVALID       0x01  /* ����������Ч */
#define  AM_ZLG52810_PARAMETER_INVALID     0x02  /* ������Ч */
#define  AM_ZLG52810_COMMAND_INVALID       0x03  /* ������Ч */

/* \brief ZLG52810 ���������ñ�ʶ */
#define  AM_ZLG52810_BAUD_4800             0
#define  AM_ZLG52810_BAUD_9600             1
#define  AM_ZLG52810_BAUD_19200            2
#define  AM_ZLG52810_BAUD_38400            3
#define  AM_ZLG52810_BAUD_57600            4
#define  AM_ZLG52810_BAUD_115200           5
#define  AM_ZLG52810_BAUD_230400           6
#define  AM_ZLG52810_BAUD_460800           7
#define  AM_ZLG52810_BAUD_1000000          8

/* \brief ZLG52810 �������ñ�ʶ */
#define  AM_ZLG52810_FLOWC_DISABLE         0
#define  AM_ZLG52810_FLOWC_EN_NOFLOW       1
#define  AM_ZLG52810_FLOWC_EN_FLOW         2

/**
 * \name ZLG52810��������
 * 
 *     ������������ am_zlg52810_ioctl() ������ cmd ��������p_arg������ʵ����������
 * ����Ĳ�ͬ����ͬ��
 *
 * @{
 */

/**
 * \brief ��ѯ�Զ�������Ӽ������λms
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ���ֵ��ʾ��ȡ��BLE�Զ�������Ӽ����
 * �������ΧΪ 0006~0C80  ����Ϊ4���ַ�
 * 4 ���ַ�����һ�� 16 λ�����ø�16 λ������ 1.25 ��Ϊϣ�����õ����Ӽ������λ ms
 */
#define  AM_ZLG52180_ACOMA_GET                    1

/**
 * \brief ��ȡBLE���Ӽ������λms
 *
 * ��ʱ�� p_arg ����������Ϊ char ָ�����ͣ���ֵ��ʾ���õ�BLE�Զ�������Ӽ����
 * �������ΧΪ 0006~0C80
 * 4 ���ַ�����һ�� 16 λ�����ø�16 λ������ 1.25 ��Ϊϣ�����õ����Ӽ������λ ms
 */
#define  AM_ZLG52810_ACOMA_SET                     2

/**
 * \brief ��ѯ�Զ��������Ӳ���
 *
 * ��ʱ�� p_arg ����������Ϊuint32_t ָ������
 * ��Чֵ�У�0 �����Զ����²���     1 ʹ���Զ����²���
 */
#define  AM_ZLG52810_ACOUP_GET                    3

/**
 * \brief �����Զ��������Ӳ���
 *
 * ��ʱ�� p_arg ����������Ϊuint32_t ָ������
 * ��Чֵ�У�0 �����Զ����²���     1 ʹ���Զ����²���
 */
#define  AM_ZLG52810_ACOUP_SET                    4

/**
 * \brief ��ѯ�豸��ַ
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ����ʾ�豸��ַ���ַ���
 */
#define  AM_ZLG52810_ADDR_GET                         5

/**
 * \brief ��ѯ�㲥������
 *
 * ����������Ϊ  uint32_t ���͵�ָ��  ָ��ģ�����õĹ㲥������
 *  0 �ɷ��ֿ����ӣ�Ĭ�ϣ�   1 �ɷ��ֲ�������
 */
#define  AM_ZLG52810_ADTY_GET                         6

/**
 * \brief ���ù㲥������
 *
 * ����������Ϊ  uint32_t ����   ���õĹ㲥������
 *  0 �ɷ��ֿ����ӣ�Ĭ�ϣ�   1 �ɷ��ֲ�������
 */
#define  AM_ZLG52810_ADTY_SET                         7

/**
 * \brief ��ѯ�㲥ʱ����
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��㲥ʱ��������
 * ��Ч���� 0~F  0:100ms   1:152.5ms   2:211.25ms(Ĭ��)   3:318.75ms
 *            4:417.5ms    5:546.25ms   6:760ms         7:852.5ms
 *            8:1022.5ms   9:1285ms     A:2000ms        B:3000ms
 *            C:4000ms     D:5000ms     E:6000ms        F:10000ms
 *
 */
#define  AM_ZLG52810_ADVI_GET                         8

/**
 * \brief ���ù㲥ʱ����  �޸Ĺ㲥���������Ч���͹���
 *
 * ��ʱ�� p_arg ����������Ϊ  char ���ͣ���ʾ�㲥ʱ��������
 * ��Ч���� 0~F  0:100ms   1:152.5ms   2:211.25ms(Ĭ��)   3:318.75ms
 *            4:417.5ms    5:546.25ms   6:760ms         7:852.5ms
 *            8:1022.5ms   9:1285ms     A:2000ms        B:3000ms
 *            C:4000ms     D:5000ms     E:6000ms        F:10000ms
 *
 */
#define  AM_ZLG52810_ADVI_SET                         9

/**
 * \brief ��ȡ������
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ������
 * ��Чֵ�У�0:4800  1:9600  2:19200  3:38400  4:57600  5:115200
 *        6:230400  7:460800  8:1000000
 */
#define  AM_ZLG52810_BAUD_GET                         10

/**
 * \brief ���ò�����
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ��ʾ���õĲ����ʣ�
 * ��Чֵ�У�0:4800  1:9600  2:19200  3:38400  4:57600  5:115200
 *        6:230400  7:460800  8:1000000
 */
#define  AM_ZLG52810_BAUD_SET                         11

/**
 * \brief ��ȡ��ǰ������״̬
 *
 * ��ʱ�� p_arg ����������Ϊ  am_bool_t ָ�����ͣ����ڻ�ȡ����״̬��
 * ��ֵΪ AM_TRUE�����������ӣ���ֵΪ AM_FALSE������δ����
 */
#define  AM_ZLG52810_CONS_GET                         12

/**
 * \brief �Ͽ���ǰ����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define  AM_ZLG52810_DISCONNECT                       13

/**
 * \brief ��ѯ��ʱ���Ӳ���
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��4�ַ��Ļ�����
 * ���ص�4���ַ�����һ��16λ�����ø�������1.25��Ϊ��ǰ���Ӽ������λms
 * ��Ч��Χ��  0006~0C80
 */
#define  AM_ZLG52810_COPS_GET                         14

/**
 * \brief ������ʱ���Ӳ���
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��4�ַ�������ֵ
 * ���ص�4���ַ�����һ��16λ�����ø�������1.25��Ϊ��ǰ���Ӽ������λms
 * ��Ч��Χ��  0006~0C80
 */
#define  AM_ZLG52810_COPS_SET                         15

/**
 * \brief ����豸���а���Ϣ
 *
 * ��ʱ�� p_arg ΪNULL
 */
#define  AM_ZLG52810_ERASE                            16

/**
 * \brief �ָ���������
 *
 * ��ʱ�� p_arg ΪNULL
 */
#define  AM_ZLG52810_FARESET                          17

/**
 * \brief ��ѯ�������ع���
 *
 * ��ʱ�� p_arg ����������Ϊ  int32_t ָ�����ͣ����Ի�ȡ��ǰ�������ع���״̬
 * ��Чֵ�У� 0:�رգ�Ĭ�ϣ�  1:��
 */
#define  AM_ZLG52810_FLC_GET                          18

/**
 * \brief ���ô������ع���
 *
 * ��ʱ�� p_arg ����������Ϊ  int32_t ���ͣ���������    ��ǰ�������ع���״̬
 * ��Чֵ�У� 0:�رգ�Ĭ�ϣ�  1:��
 */
#define  AM_ZLG52810_FLC_SET                          19

/**
 * \brief ��ѯLE secure connection ���ܿ���
 *
 * ��ʱ�� p_arg ����������Ϊ  int32_t ָ�����ͣ����Ի�ȡLE secure connection ���ܿ���״̬
 * ��Чֵ��: 0:�رգ�Ĭ�ϣ�   1:��
 */
#define  AM_ZLG52810_LESC_GET                         20

/**
 * \brief ����LE secure connection ���ܿ���
 *
 * ��ʱ�� p_arg ����������Ϊ  int32_t ���ͣ���������LE secure connection ���ܿ���״̬
 * ��Чֵ��: 0:�رգ�Ĭ�ϣ�   1:��
 */
#define  AM_ZLG52810_LESC_SET                         21

/**
 * \brief ��ѯ�͹��ĵȼ�
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ���ֵ���ڻ�ȡ�͹��ĵȼ�
 * ��Чֵ�У�0:ȫ�����У�Ĭ�ϣ�     1:�͹���1     2:�͹���2
 */
#define  AM_ZLG52810_LOWL_GET                         22

/**
 * \brief ���õ͹��ĵȼ�
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ֵ�������õ͹��ĵȼ�
 * ��Чֵ�У�0:ȫ�����У�Ĭ�ϣ�     1:�͹���1     2:�͹���2
 */
#define  AM_ZLG52810_LOWL_SET                         23

/**
 * \brief ��ѯ�㲥���Զ����ֶ�����
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ����ڻ�ȡ�㲥���Զ����ֶ�����
 */
#define  AM_ZLG52810_MFSD_GET                         24

/**
 * \brief ���ù㲥���Զ����ֶ�����
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ��������ù㲥���Զ����ֶ�����
 * ��Ч��ΧΪ  0~52���ַ�         26���ֽڲ��52��16���Ƶ��ַ�
 */
#define  AM_ZLG52810_MFSD_SET                         25

/**
 * \brief ��ѯ�豸��
 *
 * ��ʱ�� p_arg ����Ϊchar ָ�����ͣ������ڴ�Ų�ѯ���豸��
 */
#define  AM_ZLG52810_NAME_GET                         26

/**
 * \brief �����豸��
 *
 * ��ʱ�� p_arg ����Ϊchar ָ�����ͣ������ڴ�����õ��豸��
 */
#define  AM_ZLG52810_NAME_SET                         27

/**
 * \brief ����ģ��������
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ����ʾ�������ַ������ַ���
 * �����ǡ�0��~��9���е�6����������ַ�����Ĭ��123456����
 */
#define  AM_ZLG52810_PASS_SET                          28

/**
 * \brief ��ȡģ��������
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ��һ��ת������루�ַ������Ļ�������
 * ��������СΪ6�ֽڣ�Ĭ��Ϊ123456����
 */
#define  AM_ZLG52810_PASS_GET                          29

/**
 * \brief ��ѯ���书��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ�ָ���ѯ�ķ��书�ʣ�
 * ��Чֵ��:  0:-20dbm   1:-12dbm   2:-4dbm  3:0dbm(Ĭ��)  4:4dbm
 */
#define  AM_ZLG52810_POWE_GET                         30

/**
 * \brief ��ѯ���书��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ�ָ�����õķ��书�ʣ�
 * ��Чֵ��:  0:-20dbm   1:-12dbm   2:-4dbm  3:0dbm(Ĭ��)  4:4dbm
 */
#define  AM_ZLG52810_POWE_SET                         31

/**
 * \brief �����λ����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define  AM_ZLG52810_RESET                            32

/**
 * \brief ��ѯģ���ӡ����
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ�ָ���ȡ��ģ���ӡ����
 * ��Чֵ��: 0:�ر�       1:��(Ĭ��)
 */
#define  AM_ZLG52810_RSPI_GET                         33

/**
 * \brief ����ģ���ӡ����
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ʾ���õ�ģ���ӡ����
 * ��Чֵ��: 0:�ر�       1:��(Ĭ��)
 */
#define  AM_ZLG52810_RSPI_SET                         34

/**
 * \brief ��ѯURATE������ʱ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ�ָ���ȡ��URATE������ʱ
 * ��Чֵ��: 0:10ms     1:20ms  3:30ms   4:40ms  5:50ms  6:100ms  7:500ms
 */
#define  AM_ZLG52810_UTDT_GET                         35

/**
 * \brief ����URATE������ʱ
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ʾ���õ�URATE������ʱ
 * ��Чֵ��: 0:10ms     1:20ms  3:30ms   4:40ms  5:50ms  6:100ms  7:500ms
 */
#define  AM_ZLG52810_UTDT_SET                         36

/**
 * \brief ��ѯ�豸��ȫ�ȼ�
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ�ָ���ȡ���豸��ȫ�ȼ���
 * ��Чֵ��: 0:����֤������        1:��֤������          3:����֤����          4:��֤����
 */
#define  AM_ZLG52810_SECL_GET                         37

/**
 * \brief �����豸��ȫ�ȼ�
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ���ͣ���ʾ���õ��豸��ȫ�ȼ���
 * ��Чֵ��: 0:����֤������        1:��֤������          3:����֤����          4:��֤����
 */
#define  AM_ZLG52810_SECL_SET                         38

/**
 * \brief ��ѯTX characteristic UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ���ȡ��TX  UUID��
 * ��Чֵ��: 0000~FFFF
 */
#define  AM_ZLG52810_UUTX_GET                         39

/**
 * \brief ����TX characteristic UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ���ͣ���ʾ���õ�TX  UUID��
 *  ��Чֵ��: 0000~FFFF
 */
#define  AM_ZLG52810_UUTX_SET                         40

/**
 * \brief ��ѯRX characteristic UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ�ָ���ȡ��RX  UUID��
 * ��Чֵ��: 0000~FFFF
 */
#define  AM_ZLG52810_UURX_GET                         41

/**
 * \brief ����RX characteristic UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ���ʾ���õ�RX  UUID��
 *  ��Чֵ��: 0000~FFFF
 */
#define  AM_ZLG52810_UURX_SET                         42

/**
 * \brief ��ѯ͸������UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ���ʾ��ѯ��͸�������  UUID��
 */
#define  AM_ZLG52810_UUSE_GET                         43

/**
 * \brief ����͸������UUID
 *
 * ��ʱ�� p_arg ����������Ϊ  char ָ�����ͣ���ʾ���õ�͸�������  UUID��
 */
#define  AM_ZLG52810_UUSE_SET                         44

/**
 * \brief ��ȡ�̼��汾��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ�汾��
 */
#define  AM_ZLG52810_VERS_GET                         45

/**
 * \name ZLG52810֧��һЩ���ڿ�������
 * @{
 */

/**
 * \brief ��ȡ���ջ��������ѽ��յ����ݸ���
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ���ջ��������ѽ��յ����ݸ���
 */
#define AM_ZLG52810_NREAD                             46

/**
 * \brief ��ȡ���ͻ���������д������ݸ���
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ָ�����ͣ����ڻ�ȡ���ͻ���������д������ݸ���
 */
#define AM_ZLG52810_NWRITE                            47

/**
 * \brief ��շ��ͻ������ͽ��ջ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG52810_FLUSH                             48

/**
 * \brief ��շ��ͻ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG52810_WFLUSH                            49

/**
 * \brief ��ս��ջ�����
 *
 * ��ʱ�� p_arg ����δʹ�ã�ֵΪNULL
 */
#define AM_ZLG52810_RFLUSH                            50

/**
 * \brief ���ý��ճ�ʱʱ�䣨��λ��ms��
 *
 * ��ʱ�� p_arg ����������Ϊ  uint32_t ����
 */
#define AM_ZLG52810_TIMEOUT                           51

/** @} */
 
/**
 * \brief ZLG52810ʵ����Ϣ�ṹ�嶨��
 */
typedef struct am_zlg52810_devinfo {
    /** \brief RTS���ţ���������
     * �͵�ƽ:��ʾģ���ܹ�����MCU�����Ĵ������ݣ�MCU�ɼ�������
     * �ߵ�ƽ:��ʾģ�鲻�ܹ�����MCU�����Ĵ������ݣ�MCUӦֹͣ��������
     */
    int          pin_rts;

    /** \brief CTS���ţ���������
     * �͵�ƽ:����ǰ�û�MCU���ܽ�������ʱ��Ӧ������������
     * �ߵ�ƽ:����ǰ�û�MCU�ܽ�������ʱ��Ӧ����������
     */
    int          pin_cts;

    /** \brief Ӳ����λ����   �͵�ƽ��Ч */
    int          pin_rst;

    /** \brief RESTORE���ţ����ڻָ���������   ����ȫ������ģʽ������5s�ָ��������� */
    int          pin_restore;

    /** \brief WAKEUP���ţ����ڻ��ѵ͹���ģʽ���½�����Ч */
    int          pin_wakeup;

    /** \brief ģ���ʼ��������        */
    uint32_t     baudrate;

    /** \brief ���ڴ��ڽ��յĻ������������С��32����     */
    uint8_t     *p_uart_rxbuf;

    /** \brief ���ڴ��ڷ��͵Ļ������������С��32����     */
    uint8_t     *p_uart_txbuf;

    /** \brief ���ڴ��ڽ��յĻ�������С */
    uint16_t     rxbuf_size;

    /** \brief ���ڴ��ڷ��͵Ļ�������С */
    uint16_t     txbuf_size;

} am_zlg52810_devinfo_t;

/**
 * \brief ZLG52810�豸�ṹ�嶨��
 */
typedef struct am_zlg52810_dev {

    /** \brief ���ڷ����Ƿ������ع��� */
    volatile uint8_t            flowc_state;

    /** \brief BLE is connected? */
    volatile int                connect_state;

    /** \brief ������״̬  */
    volatile int                cmd_proc_state;

    /** \brief �˴��Ѿ��������ݵĸ���*/
    volatile int                stat_rep_cnt;

    /** \brief UARTʵ�����                    */
    am_uart_handle_t            uart_handle;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            rx_rngbuf;

    /** \brief �������ݻ��λ�����      */
    struct am_rngbuf            tx_rngbuf;

    /** \brief ���ڱ����豸��Ϣָ�� */
    const am_zlg52810_devinfo_t *p_devinfo;

    /** \brief ���ڽ�������Ӧ��ĵȴ��ṹ��       */
    am_wait_t                   ack_wait;

    /** \brief ���ڽ������ݵĵȴ��ṹ��   */
    am_wait_t                   rx_wait;

    /** \brief ���ճ�ʱʱ��                */
    volatile uint32_t           timeout_ms;

    /** \brief �����Ӧ���ջ�����  */
    uint8_t                    *p_cmd_rxbuf;

    /** \brief �����Ӧ���ջ������ĳ���  */
    volatile int                cmd_rxbuf_len;

    /** \brief �����Ӧ�Ѿ����յĳ���  */
    volatile int                cmd_rx_len;

    /** \brief �����ʱ�������ж�һ֡�Ƿ������� */
    am_softimer_t               timer;
} am_zlg52810_dev_t;


/** \brief ����ZLG52810�������  */
typedef struct am_zlg52810_dev *am_zlg52810_handle_t;
                                      
/**
 * \brief ZLG52810��ʼ������
 *
 * ʹ��ZLG52810ǰ��Ӧ�����ȵ��øó�ʼ���������Ի�ȡ����ZLG52810��handle��
 *
 * \param[in] p_dev      : ָ��ZLG52810�豸��ָ��
 * \param[in] p_devinfo  : ָ��ZLG52810�豸��Ϣ��ָ��
 * \param[in] uart_handle : UART��׼������������ʹ�ø�UART�����ZLG52810ͨ�ţ�
 *
 * \return ����ZLG52810��handle������ʼ��ʧ�ܣ��򷵻�ֵΪNULL��
 *
 * \note �豸ָ��p_devָ����豸ֻ��Ҫ���壬����Ҫ�ڵ��ñ�����ǰ��ʼ����
 */
am_zlg52810_handle_t am_zlg52810_init (am_zlg52810_dev_t           *p_dev,
                                       const am_zlg52810_devinfo_t *p_devinfo,
                                       am_uart_handle_t             uart_handle);


/**
 * \brief ZLG52810���ƺ���
 *
 * \param[in] handle    : ZLG52810ʵ�����
 * \param[in] cmd       : ����ָ����磺#AM_ZLG52810_BAUD_SET
 * \param[in,out] p_arg : �����Ӧ�Ĳ��������磺 115200
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_EIO     : ִ�д���
 * \retval -AM_ENOTSUP : ָ�֧��
 *
 * \note ����
 */
int am_zlg52810_ioctl(am_zlg52810_handle_t  handle,
                      int                   cmd,
                      void                 *p_arg);


/**
 * \brief ����͸������
 *
 * \param[in] handle : ZLG52810ʵ�����
 * \param[in] p_buf  : �����͵�����
 * \param[in] len    : ���ݳ���
 *
 * \return �Ǹ�����ʵ�ʷ��͵��ֽ���������������ʧ��
 */
int am_zlg52810_send (am_zlg52810_handle_t  handle,
                     const uint8_t         *p_buf,
                     int                    len);


/**
 * \brief ����͸������
 *
 * \param[in] handle : ZLG52810ʵ�����
 * \param[in] p_buf  : �������ݵĻ�����
 * \param[out] len   : �������ݳ���
 *
 * \return �Ǹ�����ʵ�ʽ��յ��ֽ���������������ʧ��
 */
int am_zlg52810_recv (am_zlg52810_handle_t  handle,
                     uint8_t               *p_buf,
                     int                    len);
 
/**
 * \brief ZLG52810 �͹���ģʽ����
 *
 * \param[in] handle : ZLG52810ʵ�����
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval AM_FALSE    : ִ�д���  ����Ӧ��������
 */
int am_zlg52810_lpower_wakeup(am_zlg52810_handle_t  handle);

/**
 * \brief ZLG52810 �ָ���������
 *
 * \param[in] handle : ZLG52810ʵ�����
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval AM_FALSE    : ִ�д���  ����Ӧ��������
 */
int am_zlg52810_fareset(am_zlg52810_handle_t  handle);

/**
 * \brief ZLG52810 Ӳ����λ
 *
 * \param[in] handle : ZLG52810ʵ�����
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval AM_FALSE    : ִ�д���  ����Ӧ��������
 */
int am_zlg52810_reset(am_zlg52810_handle_t  handle);
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG52810_H */

/* end of file */
