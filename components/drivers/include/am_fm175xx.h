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
 * \brief FM175XX�ײ�������ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-12-23  sky, first implementation.
 * - 1.01 17-10-31  sdq, make some changes.
 * \endinternal
 */

#ifndef __AM_FM175XX_H
#define __AM_FM175XX_H

#include "am_spi.h"
#include "am_types.h"
#include "am_softimer.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_fm175xx
 * \copydoc am_fm175xx.h
 * @{
 */

/**
 * \name FM175XX Command Code  FM175XX�����붨��
 * @{
 */

#define AM_FM175XX_CMD_IDLE              0x0  /**< \brief �޶���,ȡ����ǰָ��ִ�� */
#define AM_FM175XX_CMD_MEM               0x1  /**< \brief �洢25�ֽ����ݵ��ڲ���������FM17510��֧�֣� */
#define AM_FM175XX_CMD_RANDOM_ID         0x2  /**< \brief ����һ��10�ֽ��������FM17510��֧�֣� */
#define AM_FM175XX_CMD_CALC_CRC          0x3  /**< \brief ����CRCЭ������ */
#define AM_FM175XX_CMD_TRANSMIT          0x4  /**< \brief ����FIFO�������е����� */
#define AM_FM175XX_CMD_NO_CMD_CHANGE     0x7  /**< \brief ָ��ı�,���������ڲ�Ӱ��ָ���������޸�CMD�Ĵ���,��PDλ */
#define AM_FM175XX_CMD_RECEIVE           0x8  /**< \brief �����������· */
#define AM_FM175XX_CMD_TRANSCEIVE        0xC  /**< \brief ����FIFO�������е����ݵ�����,���ڷ�����Զ���������� */
#define AM_FM175XX_CMD_AUTHENT           0xE  /**< \brief ��Ϊ��й��ģʽִ�е�M1��ȫ��֤ */
#define AM_FM175XX_CMD_SOFT_RESET        0xF  /**< \brief ��λFM175XX */

/** @} */


/**
 * \name ״̬�붨��
 * @{
 */
#define AM_FM175XX_STATUS_SUCCESS                  (0)     /**< \brief �����ɹ� */
#define AM_FM175XX_STATUS_COMM_OK                  0x00    /**< \brief �ɹ� */
#define AM_FM175XX_STATUS_COMM_TIMEOUT             0x01    /**< \brief ͨ�ų�ʱ */
#define AM_FM175XX_STATUS_COMM_DVC_NOT_ONLINE      0x02    /**< \brief �豸������ */
#define AM_FM175XX_STATUS_COMM_ERROR               0x03    /**< \brief ͨ�Ŵ��� */
#define AM_FM175XX_STATUS_CMD_ERROR                0x04    /**< \brief ������� */
#define AM_FM175XX_STATUS_FAIL                     0x05    /**< \brief ����ʧ�ܣ���֡���� */

#define AM_FM175XX_STATUS_I2CMODE                  0x10    /**< \brief ģ����I2CͨѶģʽ */
#define AM_FM175XX_STATUS_UARTMODE                 0x11    /**< \brief ģ����UARTͨѶģʽ */

#define AM_FM175XX_STATUS_IDLE                     0x8A    /**< \brief ���� */
#define AM_FM175XX_STATUS_ABORT                    0x8B    /**< \brief ��ֹ��������ֹͣ�� */
#define AM_FM175XX_STATUS_BUSY                     0x8C    /**< \brief æ������ִ��������� */
#define AM_FM175XX_STATUS_EXECUTING                0x8D    /**< \brief ����ִ�У�����δִ���꣩ */
#define AM_FM175XX_STATUS_SENDING                  0x8E    /**< \brief ���ڷ��ͣ�����δ�����꣩ */
#define AM_FM175XX_STATUS_RECEIVING                0x8F    /**< \brief ���ڽ��գ�δ��ʱ������δ�����꣩ */
        
#define AM_FM175XX_STATUS_RFU90                    0x90    /**< \brief RFU 0x90 */
#define AM_FM175XX_STATUS_RFU91                    0x91    /**< \brief RFU 0x91 */
#define AM_FM175XX_STATUS_RFU92                    0x92    /**< \brief RFU 0x92 */
#define AM_FM175XX_STATUS_SEQ_ERROR                0x93    /**< \brief ���ݷְ����� */
#define AM_FM175XX_STATUS_ADR_ERROR                0x94    /**< \brief ���Ǳ�����ַ�����ӵ�ַ���� */
#define AM_FM175XX_STATUS_RCV_LENGTH_ERR           0x95    /**< \brief ���յĳ������� */
#define AM_FM175XX_STATUS_MAC_ERR                  0x96    /**< \brief MACУ������ */
#define AM_FM175XX_STATUS_USER_DATA_LEN_ERR        0x97    /**< \brief �û��������ݳ������� */
#define AM_FM175XX_STATUS_USER_PARAMETER_ERR       0x98    /**< \brief �û�����Ĳ������� */
#define AM_FM175XX_STATUS_USER_DATA_TOO_MANY       0x99    /**< \brief �û����ݹ��� */
#define AM_FM175XX_STATUS_USER_BUF_TOO_SMALL       0x9A    /**< \brief �û�������̫С */
#define AM_FM175XX_STATUS_FUNCTION_ERR             0x9B    /**< \brief ���ܴ��� */
#define AM_FM175XX_STATUS_INVALID_COMMAND          0x9C    /**< \brief ��Ч����/��֧�ֵ����� */
#define AM_FM175XX_STATUS_NOT_SAME_CARD            0x9D    /**< \brief ����ͬһ�ſ� */
#define AM_FM175XX_STATUS_TRAN_NOT_COMPLETED       0x9E    /**< \brief ����δ��� */
#define AM_FM175XX_STATUS_APP_NOT_ENABLED_ERR      0x9F    /**< \brief Ӧ��δ���� */
#define AM_FM175XX_STATUS_IC_POWER_ERR             0x60    /**< \brief ����ICδ�ϵ����� */

#define AM_FM175XX_STATUS_CARD_TYPE_ERR            0xA0    /**< \brief �����ʹ��� */
#define AM_FM175XX_STATUS_RFUA1                    0xA1    /**< \brief RFU 0xA1 */
#define AM_FM175XX_STATUS_RFUA2                    0xA2    /**< \brief RFU 0xA2 */
#define AM_FM175XX_STATUS_RFUA3                    0xA3    /**< \brief RFU 0xA3 */
#define AM_FM175XX_STATUS_RFUA4                    0xA4    /**< \brief RFU 0xA4 */
#define AM_FM175XX_STATUS_RFUA5                    0xA5    /**< \brief RFU 0xA5 */
#define AM_FM175XX_STATUS_RFUA6                    0xA6    /**< \brief RFU 0xA6 */
#define AM_FM175XX_STATUS_RFUA7                    0xA7    /**< \brief RFU 0xA7 */
#define AM_FM175XX_STATUS_RFUA8                    0xA8    /**< \brief RFU 0xA8 */
#define AM_FM175XX_STATUS_RFUA9                    0xA9    /**< \brief RFU 0xA9 */
#define AM_FM175XX_STATUS_RFUAA                    0xAA    /**< \brief RFU 0xAA */
#define AM_FM175XX_STATUS_RFUAB                    0xAB    /**< \brief RFU 0xAB */
#define AM_FM175XX_STATUS_IID_ERROR                0xAC    /**< \brief IID����(��֧�ֵ�IID) */
#define AM_FM175XX_STATUS_VPC_TIMEOUT              0xAD    /**< \brief �����м̹��� */
#define AM_FM175XX_STATUS_NOT_SUPPORT_VC           0xAE    /**< \brief ��֧�����⿨���� */
#define AM_FM175XX_STATUS_PCD_CAP_ERROR            0xAF    /**< \brief PCD�������� */

#define AM_FM175XX_STATUS_RFUB0                    0xB0    /**< \brief RFU 0xB0 */
#define AM_FM175XX_STATUS_RFUB1                    0xB1    /**< \brief RFU 0xB1 */
#define AM_FM175XX_STATUS_RFUB2                    0xB2    /**< \brief RFU 0xB2 */
#define AM_FM175XX_STATUS_RFUB3                    0xB3    /**< \brief RFU 0xB3 */
#define AM_FM175XX_STATUS_RFUB4                    0xB4    /**< \brief RFU 0xB4 */
#define AM_FM175XX_STATUS_RFUB5                    0xB5    /**< \brief RFU 0xB5 */
#define AM_FM175XX_STATUS_AUTH_ERROR               0xB6    /**< \brief ��֤���� */
#define AM_FM175XX_STATUS_CMD_OVERFLOW             0xB7    /**< \brief ����(����)��� */
#define AM_FM175XX_STATUS_INVALID_MAC              0xB8    /**< \brief ��Ч��MAC */
#define AM_FM175XX_STATUS_INVALID_BLOCK            0xB9    /**< \brief ��Ч�Ŀ� */
#define AM_FM175XX_STATUS_INEXISTENT_BLOCK         0xBA    /**< \brief �����ڵĿ� */
#define AM_FM175XX_STATUS_NOT_SATISFIED            0xBB    /**< \brief ��ȫ�ȼ����� Security level is insufficient */
#define AM_FM175XX_STATUS_MORE_THAN_RETRIES        0xBC    /**< \brief �������Դ��� */
#define AM_FM175XX_STATUS_HANDLE_ERROR             0xBD    /**< \brief ������� */
#define AM_FM175XX_STATUS_INTERNAL_COMM_ERRPR      0xBE    /**< \brief �豸�ڲ�ͨ�Ŵ��� */
#define AM_FM175XX_STATUS_GENERAL_ERROR            0xBF    /**< \brief ��ͨ�������� */

#define AM_FM175XX_STATUS_NO_DATA_ERROR            0xC0    /**< \brief �����ݴ���(��Ҫ��������ʱ,FIFO��������) */
#define AM_FM175XX_STATUS_INTEG_ERROR              0xC1    /**< \brief ���������Դ���(����CRC����żУ�����) */
#define AM_FM175XX_STATUS_NAD_ERROR                0xC2    /**< \brief NAD���� */
#define AM_FM175XX_STATUS_INVALID_VALUE            0xC3    /**< \brief ֵ���ʽ���� */
#define AM_FM175XX_STATUS_PERORM_ERROR             0xC4    /**< \brief ����ִ�н������ */
#define AM_FM175XX_STATUS_EDC_ERROR                0xC5    /**< \brief У���ֽ�����(ͨ��У��) */
#define AM_FM175XX_STATUS_APDU_ERROR               0xC6    /**< \brief APDU������� */
#define AM_FM175XX_STATUS_SEND_ERROR               0xC7    /**< \brief ���ʹ��� */
#define AM_FM175XX_STATUS_LENGTH_ERROR             0xC8    /**< \brief ���ȴ��� */
#define AM_FM175XX_STATUS_NAK_ERROR                0xC9    /**< \brief NAK���� */
#define AM_FM175XX_STATUS_PCB_ERROR                0xCA    /**< \brief PCB���� */
#define AM_FM175XX_STATUS_CID_ERROR                0xCB    /**< \brief CID���� */
#define AM_FM175XX_STATUS_BLOCK_FORMAT_ERROR       0xCC    /**< \brief ����֡��ʽ����  */
#define AM_FM175XX_STATUS_PPS_ERROR                0xCD    /**< \brief PPSS���� */
#define AM_FM175XX_STATUS_ATS_ERROR                0xCE    /**< \brief ATS����(ISO14443-4); ��λӦ���(ISO7816-3) */
#define AM_FM175XX_STATUS_CARD_COMM_ERROR          0xCF    /**< \brief �뿨Ƭ֮���ͨ�ų��� */

#define AM_FM175XX_STATUS_EXECUTE_FAILED           0xD0    /**< \brief ִ��ʧ�� */
#define AM_FM175XX_STATUS_COMPARE_ERROR            0xD1    /**< \brief �Ƚϴ��� */
#define AM_FM175XX_STATUS_ACCESS_BANNED            0xD2    /**< \brief ��ֹ���� */
#define AM_FM175XX_STATUS_ACCESS_ERROR             0xD3    /**< \brief �洢�����ʴ��� */
#define AM_FM175XX_STATUS_BCC_ERROR                0xD4    /**< \brief BCCУ����� */
#define AM_FM175XX_STATUS_NO_TARGET                0xD5    /**< \brief ��Ŀ�� */
#define AM_FM175XX_STATUS_UNDEFINE_ERROR           0xD6    /**< \brief δ����Ĵ��� */
#define AM_FM175XX_STATUS_NO_RF_FIELD              0xD7    /**< \brief ��RF������ */
#define AM_FM175XX_STATUS_POWER_SHORTAGE           0xD9    /**< \brief ���ʲ��� */
#define AM_FM175XX_STATUS_SERNR_ERROR              0xDA    /**< \brief ��֧�ֵķ���ײ�ȼ� */
#define AM_FM175XX_STATUS_NO_BITWISE_ANTICOLL      0xDB    /**< \brief ��֧��Bit֡����ͻ */
#define AM_FM175XX_STATUS_INIT_ERROR               0xDC    /**< \brief ��ʼ������ */
#define AM_FM175XX_STATUS_TEMP_ERROR               0xDD    /**< \brief �¶����� */
#define AM_FM175XX_STATUS_INVALID_DEVICE_STATE     0xDE    /**< \brief �������� */
#define AM_FM175XX_STATUS_INSUFFICIENT_RESOURCES   0xDF    /**< \brief ϵͳ��Դ���� */

#define AM_FM175XX_STATUS_OTHER_ERROR              0xE0    /**< \brief �������� */
#define AM_FM175XX_STATUS_NO_ID_AVAILABLE          0xE1    /**< \brief �޿���ID���� */
#define AM_FM175XX_STATUS_ID_NOT_IN_USE            0xE2    /**< \brief ָ����ID����ʹ�� */
#define AM_FM175XX_STATUS_INSTANCE_ALREADY_IN_USE  0xE3    /**< \brief INSTANCE �ѱ�ʹ�� */
#define AM_FM175XX_STATUS_ID_ALREADY_IN_USE        0xE4    /**< \brief ID�ѱ�ʹ�� */
#define AM_FM175XX_STATUS_SLOT_ALREADY_IN_USE      0xE4    /**< \brief �����ѱ�ʹ�� */
#define AM_FM175XX_STATUS_WRONG_HALT_FORMAT        0xE5    /**< \brief �����ʽ���� */
#define AM_FM175XX_STATUS_WRONG_UID_CHECKBYTE      0xE6    /**< \brief Ŀ��UID������ */
#define AM_FM175XX_STATUS_TARGET_RESET_TOX         0xE7    /**< \brief Ŀ�긴λ */
#define AM_FM175XX_STATUS_TARGET_SET_TOX           0xE8    /**< \brief Ŀ�����ó�ʱ */
#define AM_FM175XX_STATUS_TARGET_DEADLOCKED        0xE9    /**< \brief Ŀ������ */
#define AM_FM175XX_STATUS_BLOCKNR_NOT_EQUAL        0xEA    /**< \brief ͨ�ſ���� */
#define AM_FM175XX_STATUS_ACK_SUPPOSED             0xEB    /**< \brief ACK���� */
#define AM_FM175XX_STATUS_AUTHENT_ERROR            0xEC    /**< \brief ��֤���� */
#define AM_FM175XX_STATUS_INTERFACE_NOT_ENABLED    0xED    /**< \brief �ӿ�δ���� */
#define AM_FM175XX_STATUS_INVALID_FORMAT           0xEE    /**< \brief ��Ч��ʽ */
#define AM_FM175XX_STATUS_INTERFACE_ERROR          0xEF    /**< \brief �����ӿڴ��� */

#define AM_FM175XX_STATUS_UNSUPPORTED_COMMAND      0xF0    /**< \brief ��֧�ֵ����� */
#define AM_FM175XX_STATUS_UNSUPPORTED_PARAMETER    0xF1    /**< \brief ��֧�ֵĲ��� */
#define AM_FM175XX_STATUS_INVALID_PARAMETER        0xF2    /**< \brief ��Ч���� */
#define AM_FM175XX_STATUS_USER_BUFFER_FULL         0xF3    /**< \brief �û��������� */
#define AM_FM175XX_STATUS_FIFO_WRITE_ERROR         0xF4    /**< \brief FIFOд���� */
#define AM_FM175XX_STATUS_NOT_YET_IMPLEMENTED      0xF5    /**< \brief ��δ��Ч */
#define AM_FM175XX_STATUS_PROTOCOL_ERROR           0xF6    /**< \brief Э������ */
#define AM_FM175XX_STATUS_BUFFER_OVERFLOW          0xF7    /**< \brief BUF������� */
#define AM_FM175XX_STATUS_FIFO_OVERFLOW            0xF7    /**< \brief FIFO������� */
#define AM_FM175XX_STATUS_ACCESS_DENIED            0xF8    /**< \brief д��ֹ */
#define AM_FM175XX_STATUS_BUFFER_TOO_SMALL         0xF9    /**< \brief ��������С */
#define AM_FM175XX_STATUS_COLLISION_ERROR          0xFA    /**< \brief λ��ͻ���� */
#define AM_FM175XX_STATUS_FRAMING_ERROR            0xFB    /**< \brief ֡���� */
#define AM_FM175XX_STATUS_BIT_COUNT_ERROR          0xFC    /**< \brief ����λ���������� */
#define AM_FM175XX_STATUS_PARITY_ERROR             0xFD    /**< \brief ��żУ����� */
#define AM_FM175XX_STATUS_CRC_ERROR                0xFE    /**< \brief CRCУ����� */
#define AM_FM175XX_STATUS_IO_TIMEOUT               0xFF    /**< \brief ��Ӧ����� */

/** @} */


/**
 * \name ������ʱ����
 *
 * \note ��ʱʱ�䲻�˳���100ms��������ܵ���MCU�ڲ���ʱ����Ч��
 * @{
 */
#define AM_FM175XX_RIC_DELAY1MS                2           /**< \brief ��ʱ1ms */
#define AM_FM175XX_RIC_DELAY2MS                3           /**< \brief ��ʱ2ms */
#define AM_FM175XX_RIC_DELAY5MS                6           /**< \brief ��ʱ4.832ms */
#define AM_FM175XX_RIC_DELAY10MS               11          /**< \brief ��ʱ9.966ms */
#define AM_FM175XX_RIC_DELAY20MS               21          /**< \brief ��ʱ19.932ms */
#define AM_FM175XX_RIC_DELAY50MS               51          /**< \brief ��ʱ50.132ms */
#define AM_FM175XX_RIC_DELAY100MS              101         /**< \brief ��ʱ99.962ms */

/** @} */


/**
 * \name LPCD������߽׶�ʱ������
 *
 * \note �û��ɸ��ݵ͹���Ҫ������޸�
 * @{
 */
#define AM_FM175XX_LCPD_SLEEP0MS               0          /**< \brief 0ms */
#define AM_FM175XX_LCPD_SLEEP200MS             1          /**< \brief 200ms */
#define AM_FM175XX_LCPD_SLEEP400MS             2          /**< \brief 400ms */
#define AM_FM175XX_LCPD_SLEEP500MS             3          /**< \brief 500ms */
#define AM_FM175XX_LCPD_SLEEP600MS             4          /**< \brief 600ms */
#define AM_FM175XX_LCPD_SLEEP700MS             5          /**< \brief 700ms */
#define AM_FM175XX_LCPD_SLEEP800MS             6          /**< \brief 800ms */
#define AM_FM175XX_LCPD_SLEEP900MS             7          /**< \brief 900ms */
#define AM_FM175XX_LCPD_SLEEP1000MS            8          /**< \brief 1s */
#define AM_FM175XX_LCPD_SLEEP1100MS            9          /**< \brief 1.1s */
#define AM_FM175XX_LCPD_SLEEP1200MS            10         /**< \brief 1.2ms */
#define AM_FM175XX_LCPD_SLEEP1300MS            11         /**< \brief 1.3ms */
#define AM_FM175XX_LCPD_SLEEP1400MS            12         /**< \brief 1.4ms */
#define AM_FM175XX_LCPD_SLEEP1500MS            13         /**< \brief 1.5ms */
#define AM_FM175XX_LCPD_SLEEP1600MS            14         /**< \brief 1.6ms */
#define AM_FM175XX_LCPD_SLEEP1700MS            15         /**< \brief 1.7ms */
/** @} */


/**
 * \name LPCD���׶�ʱ������
 *
 * \note �û��ɸ��ݵ͹���Ҫ������޸�
 * @{
 */
#define AM_FM175XX_LCPD_DETECT0US              1           /**< \brief 0us */
#define AM_FM175XX_LCPD_DETECT4US              2           /**< \brief 4.7us */
#define AM_FM175XX_LCPD_DETECT9US              3           /**< \brief 9.4us */
#define AM_FM175XX_LCPD_DETECT14US             4           /**< \brief 14.1us */
#define AM_FM175XX_LCPD_DETECT18US             5           /**< \brief 18.8us */
#define AM_FM175XX_LCPD_DETECT23US             6           /**< \brief 23.5us */
#define AM_FM175XX_LCPD_DETECT28US             7           /**< \brief 28.2us */
#define AM_FM175XX_LCPD_DETECT32US             8           /**< \brief 32.9us */
#define AM_FM175XX_LCPD_DETECT37US             9           /**< \brief 37.6us */
#define AM_FM175XX_LCPD_DETECT42US             10          /**< \brief 42.3us */
#define AM_FM175XX_LCPD_DETECT47US             11          /**< \brief 47us */
#define AM_FM175XX_LCPD_DETECT51US             12          /**< \brief 51.7us */
#define AM_FM175XX_LCPD_DETECT56US             13          /**< \brief 56.4us */
#define AM_FM175XX_LCPD_DETECT61US             14          /**< \brief 61.1us */
#define AM_FM175XX_LCPD_DETECT65US             15          /**< \brief 65.8us */
#define AM_FM175XX_LCPD_DETECT70US             16          /**< \brief 70.5us */
#define AM_FM175XX_LCPD_DETECT75US             17          /**< \brief 75.2us */
#define AM_FM175XX_LCPD_DETECT79US             18          /**< \brief 79.9us */
#define AM_FM175XX_LCPD_DETECT84US             19          /**< \brief 84.6us */
#define AM_FM175XX_LCPD_DETECT89US             20          /**< \brief 89.3us */
#define AM_FM175XX_LCPD_DETECT94US             21          /**< \brief 94us */
#define AM_FM175XX_LCPD_DETECT98US             22          /**< \brief 98.7us */
#define AM_FM175XX_LCPD_DETECT103US            23          /**< \brief 103.4us */
#define AM_FM175XX_LCPD_DETECT108US            24          /**< \brief 108.1us */
#define AM_FM175XX_LCPD_DETECT112US            25          /**< \brief 112.8us */
#define AM_FM175XX_LCPD_DETECT117US            26          /**< \brief 117.5us */
#define AM_FM175XX_LCPD_DETECT122US            27          /**< \brief 122.2us */
#define AM_FM175XX_LCPD_DETECT126US            28          /**< \brief 126.9us */
#define AM_FM175XX_LCPD_DETECT131US            29          /**< \brief 131.6us */
#define AM_FM175XX_LCPD_DETECT136US            30          /**< \brief 136.3us */
#define AM_FM175XX_LCPD_DETECT141US            31          /**< \brief 141us */
/** @} */


/**
 * \name LPCD������������
 *
 * @{
 */
#define AM_FM175XX_LCPD_TX2_RF_ENABLE          1           /**< \brief LPCD TX2����ʹ�� */
#define AM_FM175XX_LCPD_TX2_RF_DISABLE         0           /**< \brief LPCD TX2������� */

#define AM_FM175XX_LCPD_RF_NMOS_46             0           /**< \brief LPCD ����NMOS��������Ϊ46ŷķ */
#define AM_FM175XX_LCPD_RF_NMOS_23             1           /**< \brief LPCD ����NMOS��������Ϊ23ŷķ */

#define AM_FM175XX_LCPD_RF_PMOS_180            0           /**< \brief LPCD ����NMOS��������Ϊ180ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_90             1           /**< \brief LPCD ����PMOS��������Ϊ90ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_46             2           /**< \brief LPCD ����PMOS��������Ϊ46ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_23             3           /**< \brief LPCD ����PMOS��������Ϊ23ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_12             4           /**< \brief LPCD ����PMOS��������Ϊ12ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_6              5           /**< \brief LPCD ����PMOS��������Ϊ6ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_3              6           /**< \brief LPCD ����PMOS��������Ϊ3ŷķ */
#define AM_FM175XX_LCPD_RF_PMOS_1              7           /**< \brief LPCD ����PMOS��������Ϊ1.5ŷķ */

/** @} */


/**
 * \name LPCD����������
 *
 * @{
 */
#define AM_FM175XX_LCPD_AUTO_DETECT_TIMES_3    0           /**< \brief LPCD �Զ�������κ�����ж� */
#define AM_FM175XX_LCPD_AUTO_DETECT_TIMES_1    1           /**< \brief LPCD �Զ����һ�κ�����ж�  */

#define AM_FM175XX_LCPD_INT_DISABLE            0           /**< \brief LPCD �������ж� */
#define AM_FM175XX_LCPD_INT_ENABLE             1           /**< \brief LPCD �����ж� */

#define AM_FM175XX_LCPD_AUTO_WUP_DISANLE       0           /**< \brief LPCD �����Զ�����ģʽ */
#define AM_FM175XX_LCPD_AUTO_WUP_ENABLE        1           /**< \brief LPCD ʹ���Զ�����ģʽ*/

#define AM_FM175XX_LCPD_AUTO_WUP_TIME_6S       0           /**< \brief LPCD �����Զ�����ʱ��  6s*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_12S      1           /**< \brief LPCD �����Զ�����ʱ�� 12s*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_15MIN    2           /**< \brief LPCD �����Զ�����ʱ�� 15minutes*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_30MIN    3           /**< \brief LPCD �����Զ�����ʱ�� 30minutes*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_60MIN    4           /**< \brief LPCD �����Զ�����ʱ�� 1hours*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_108MIN   5           /**< \brief LPCD �����Զ�����ʱ�� 1.8hours*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_216MIN   6           /**< \brief LPCD �����Զ�����ʱ�� 3.6hours*/
#define AM_FM175XX_LCPD_AUTO_WUP_TIME_432MIN   7           /**< \brief LPCD �����Զ�����ʱ�� 7.2hours*/

/** @} */
/** \brief  LPCDģʽ��ʼ������״̬��*/
#define  AM_FM175XX_INIT_SUCCESS               0x00       /**< \brief �豸LPCDģʽ��ʼ���ɹ�  */
#define  AM_FM175XX_REG_INIT_ERROR             0x01       /**< \brief �豸LPCDģʽ�Ĵ�����ʼ��ʧ��  */
#define  AM_FM175XX_CALIBRA_INIT_ERROR         0x02       /**< \brief �豸LPCDģʽ��У��ʼ��ʧ��  */

/**
 * \name  T=CL �ṹ֡��������
 * @{
 */
#define AM_FM175XX_PCB_TYPE_MASK               0xC0        /**< \brief PCB�������� */
#define AM_FM175XX_PCB_BLOCK_NUM_MASK          0x01        /**< \brief PCB�������� */
#define AM_FM175XX_PCB_I_BLOCK                 0x00        /**< \brief I_BLOCK */
#define AM_FM175XX_PCB_R_BLOCK                 0x80        /**< \brief R_BLOCK */
#define AM_FM175XX_PCB_S_BLOCK                 0xC0        /**< \brief S_BLOCK */
#define AM_FM175XX_PCB_CID_MASK                0x08        /**< \brief PCB��CID���� */
#define AM_FM175XX_PCB_NAD_MASK                0x04        /**< \brief PCB��NAD���� */
#define AM_FM175XX_PCB_CID                     0x08        /**< \brief PCB��CID */
#define AM_FM175XX_PCB_NAD                     0x04        /**< \brief PCB��NAD */
#define AM_FM175XX_PCB_CHAINING                0x10        /**< \brief ���ݷ��� */

#define AM_FM175XX_PCB_I_RFU                   0x02        /**< \brief I_BLOCK ����λ */

#define AM_FM175XX_PCB_R_TYPE_MASK             0x10        /**< \brief R_BLOCK �������� */
#define AM_FM175XX_PCB_R_NAK                   0x10        /**< \brief R_BLOCK NAK */
#define AM_FM175XX_PCB_R_ACK                   0x00        /**< \brief R_BLOCK ACK */
#define AM_FM175XX_PCB_R_RFU                   0x22        /**< \brief R_BLOCK ����λ */

#define AM_FM175XX_PCB_S_TYPE_MASK             0x30        /**< \brief S_BLOCK �������� */
#define AM_FM175XX_PCB_S_WTX                   0x30        /**< \brief S_BLOCK WTX */
#define AM_FM175XX_PCB_S_DESELECT              0x00        /**< \brief S_BLOCK DESELECT */
#define AM_FM175XX_PCB_S_RFU                   0x02        /**< \brief S_BLOCK ����λ */

/** @} */

/**
 * \name  ��������
 * @{
 */
#define AM_FM175XX_MAX_FS_TAB_NO    9    /**< \brief �ӿ��豸�ܽ��յ��ֽ����� */
#define AM_FM175XX_MAX_FSDI         8    /**< \brief �ӿ��豸����ܽ��ջ�����Ϊ256�ֽ� */
#define AM_FM175XX_MAX_FSCI         8    /**< \brief �ӿ��豸����ܷ��ͻ�����Ϊ256�ֽ�  */
                                         /**< \brief 0 -> 16�ֽ�; 1 -> 24�ֽ�;  2 -> 32�ֽ�; */
                                         /**< \brief 3 -> 40�ֽ�; 4 -> 48�ֽ�;  5 -> 64�ֽ�; */
                                         /**< \brief 6 -> 96�ֽ�; 7 -> 128�ֽ�; 8 -> 256�ֽ� */

#define AM_FM175XX_FSDI_BUF_SIZE    262  /**< \brief ����ӿ��豸�������ֽ��� */

/**  @} */

/** \brief  ����ISO14443���� */
#define AM_FM175XX_PICC_RATS                   0xE0        /**< \brief ATS���������� */
#define AM_FM175XX_PICC_PPS                    0xD0        /**< \brief PPS���� */

/** \brief  ͨ�Ų����ṹ���붨�� */
#define AM_FM175XX_PARA_FO_CID_MASK            0x02        /**< \brief ͨ�Ų������Ƿ���CID���� */
#define AM_FM175XX_PARA_FO_NAD_MASK            0x01        /**< \brief ͨ�Ų������Ƿ���NAD���� */

/**
 * \brief ����Э�����ͺ��ٶ�
 */
typedef enum am_fm175xx_prot_type
{
    /* ISO14443AЭ�飬106kbit/s ��FM17510ֻ֧��ISO14443AЭ�飩 */
    AM_FM175XX_PROT_TYPE_ISO14443A_106 = 0x00,

    /**< \brief ISO14443BЭ�飬106kbit/s */
    AM_FM175XX_PROT_TYPE_ISO14443B_106 = 0x04,
} am_fm175xx_prot_type_t;


/**
 * \brief am_fm175xx_cmd_input_para fm175xx������������ṹ�嶨��
 */
typedef struct am_fm175xx_cmd_input_para
{
    uint8_t         cmd_code;       /**< \brief �������� */
    uint16_t        tmo;            /**< \brief ��ʱʱ�� */
    uint16_t        nbytes;         /**< \brief �����ֽ��� */
    const void     *pbuf;           /**< \brief �������� */
} am_fm175xx_cmd_input_para_t;


/**
 * \brief am_fm175xx_cmd_output_para fm175xx������������ṹ�嶨��
 */
typedef struct am_fm175xx_cmd_output_para
{
    uint8_t         nlastbits;      /**< \brief ����ֽڽ��յ�λ */
    uint16_t        nbufsize;       /**< \brief ���ջ�������С */
    uint16_t        nbytes;         /**< \brief ���յ��ֽ��� */
    void           *pbuf;           /**< \brief ���ջ����� */
} am_fm175xx_cmd_output_para_t;

/**
 * \brief am_fm175xx_cmd_info ����������Ϣ�ṹ�嶨��
 */
typedef struct am_fm175xx_cmd_info
{
    uint8_t         status;         /**< \brief ״̬ */
    uint8_t         dorcv;          /**< \brief �Ƿ�������ձ�־ */
    uint8_t         ncollpos;       /**< \brief ��ײλ�� */
    uint8_t         nlastbits;      /**< \brief ����ֽڽ���λ */

    uint8_t         irqen;          /**< \brief ������ж� */
    uint8_t         waitirq;        /**< \brief �ȴ����ж� */
    uint8_t         irqsource;      /**< \brief ���е��ж� */

    uint16_t        nbytesreceived; /**< \brief �ѽ��յ��ֽ��� */
    uint16_t        nbytessent;     /**< \brief �ѷ��͵��ֽ��� */
    uint16_t        nbytestosend;   /**< \brief ��Ҫ���͵��ֽ��� */
    uint16_t        nmaxbufsize;    /**< \brief ����û����������� */

    const void     *psbuf;          /**< \brief �������ݻ����� */
    void           *prbuf;          /**< \brief �������ݻ����� */
} am_fm175xx_cmd_info_t;


/**
 * \brief T=CLЭ�����
 */
typedef struct am_fm175xx_tpcl_prot_para {
    uint8_t pcb_num;                /**< \brief �ְ���־ */
    uint8_t cid;                    /**< \brief CID */
    uint8_t fsdi;                   /**< \brief PCD  �ܽ��յ����֡ */
    uint8_t fsci;                   /**< \brief PICC �ܽ��յ����֡ */
    uint8_t ta1;                    /**< \brief ��DR��DS */
    uint8_t bit_rate;               /**< \brief λ���ʣ�ͬTA1����DR��DS�� */
    uint8_t fwi;                    /**< \brief ֡�ȴ�ʱ������ */
    uint8_t sfgi;                   /**< \brief ֡����ʱ������ */
    uint8_t tc1;                    /**< \brief ���Ƿ�֧��CID��NID */
    uint8_t fo;                     /**< \brief ѡ���Ƿ�֧��CID��NID��ͬTC1�� */
} am_fm175xx_tpcl_prot_para_t;

/**
 * \brief FM175XX LPCDģʽ����������Ϣ����
 */
typedef struct am_fm175xx_lpcd_cfginfo {
    uint8_t         sleep_time;                      /**< \brief LPCD������߽׶�ʱ������ */
    uint8_t         detect_time;                     /**< \brief LPCD���׶�ʱ������ */

    uint8_t         tx2_rf_enable;                   /**< \brief LPCD�Ƿ�ʹ��TX2���� */
    uint8_t         cwn;                             /**< \brief LPCD����NMOS��������*/
    uint8_t         cwp;                             /**< \brief LPCD����PMOS��������*/
    float           detectsensitive;                 /**< \brief LPCD������������������    0.04 - 0.15*/

    uint8_t         ie;                              /**< \brief LPCD�ж�ʹ������*/
    uint8_t         auto_detect_times;               /**< \brief LPCD�Զ�����������*/
    uint8_t         wake_up_enable;                  /**< \brief LPCD�Զ�����ʹ��*/
    uint8_t         wake_up_time;                    /**< \brief LPCD�Զ�����ʱ������*/


} am_fm175xx_lpcd_cfginfo_t;

/**
 * \brief FM175XX �豸��Ϣ����
 */
typedef struct am_fm175xx_devinfo {
    int                               reset_pin;      /**< \brief fm175xxоƬ��λ���� */
    int                               cs_pin;         /**< \brief fm175xxоƬSPIƬѡ���� */
    int                               int_pin;        /**< \brief fm175xxоƬ�ж����� */
    am_fm175xx_prot_type_t            iso_type;       /**< \brief ��ʼʹ�õ�Э������ */
    const  am_fm175xx_lpcd_cfginfo_t *p_lpcd_cfg_info;  /**< \brief lpcdģʽ������Ϣ */
} am_fm175xx_devinfo_t;


/**
 * \brief FM175XX LPCD ģʽ��Ϣ
 */
typedef struct am_fm175xx_lpcd_modeinfo {
    int8_t                              int_flag;       /**< \brief LPCDģʽ�жϱ�ʶ*/

    const am_fm175xx_lpcd_cfginfo_t    *p_cfg_info;   /**< \brief LPCDģʽ������Ϣ*/
} am_fm175xx_lpcd_modeinfo_t;;


/**
 * \brief FM175XX LPCDģʽ��У������Ϣ����
 */
typedef struct am_fm175xx_lpcd_calibrate_info {
    uint8_t        detect_timer_clkdivk;       /**< \brief LPCD ��ⶨʱ����Ƶ�� */
    uint8_t        bias_current;               /**< \brief LPCD LPCD��׼�������� */
    uint8_t        gain_reduce;                /**< \brief LPCD ˥������ */
    uint8_t        gain_amplify;               /**< \brief LPCD �Ŵ������� */
    uint8_t        adc_reference;              /**< \brief LPCD ADC��ѹ���յ�ƽ */

    uint8_t        sleep_time;                 /**< \brief LPCD ˯��ʱ�� */
    uint8_t        ready_time;                 /**< \brief LPCD ���׼��ʱ�� */
    uint8_t        detect_time;                /**< \brief LPCD ���ʱ��  */

    uint8_t        adc_full_scale;             /**< \brief LPCD ��ʱ��������ADCֵ */
    uint8_t        adc_threshold;              /**< \brief LPCD �����ȣ�����Ϊ���ֵ */
    uint8_t        lpcd_threshold_l;           /**< \brief LPCD ���ȵ���ֵ */
    uint8_t        lpcd_threshold_h;           /**< \brief LPCD ���ȸ���ֵ */
    uint8_t        adc_center;                 /**< \brief LPCD ����������ֵ */
}am_fm175xx_calibrate_info_t;

/**
 * \brief FM175XX �豸����
 */
typedef struct am_fm175xx_dev {
    am_spi_device_t         spi_dev;            /**< \brief SPI �豸 */
    am_softimer_t           timer;              /**< \brief �����ʱ�������ڳ�ʱ  */
    volatile uint32_t       tmo_cnt;            /**< \brief ��ʱ������ */
    am_fm175xx_prot_type_t  iso_type;           /**< \brief �������оƬЭ�� */
    am_fm175xx_cmd_info_t   cmd_info;           /**< \brief ������Ϣ */
    volatile uint8_t        tx_state;           /**< \brief ����״̬ */
    volatile am_bool_t      power_down;         /**< \brief �����־ */

    am_fm175xx_tpcl_prot_para_t  cur_prot_para; /**< \brief T=CLͨ��Э����� */

    const am_fm175xx_devinfo_t  *p_devinfo;     /**< \brief �豸��Ϣ */

    void                       (*lpcd_int_cb)(void *p_arg);
    void                        *p_lpcd_cb_arg;
} am_fm175xx_dev_t;

/* FM175XX �豸��� */
typedef am_fm175xx_dev_t* am_fm175xx_handle_t;

/**
 * \name ͨ�ú����ӿ�����
 * @{
 */

/**
 * \brief fm175xx ��ʼ�����õ�fm175xx�豸
 *
 * \param[out] p_dev       ��fm175xx�豸
 * \param[in]  spi_handle  ��SPI���
 * \param[in]  p_devinfo   ���豸��Ϣ
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_init (am_fm175xx_dev_t           *p_dev,
                         am_spi_handle_t             spi_handle,
                         const am_fm175xx_devinfo_t *p_devinfo);


/**
 * \brief дfm175xx �Ĵ���
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nregaddr : �Ĵ�����ַ
 * \param[in] nregval  : д���ֵ
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_reg (am_fm175xx_dev_t *p_dev,
                             uint8_t           nregadr,
                             uint8_t           nregval);


/**
 * \brief дfm175xx ��չ�Ĵ���
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nregaddr : ��չ�Ĵ�����ַ
 * \param[in] nregval  : ��չ�Ĵ���д���ֵ
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_reg_ext (am_fm175xx_dev_t *p_dev,
                             uint8_t           nregadr,
                             uint8_t           nregval);


/**
 * \brief ��fm175xx �Ĵ���
 *
 * \param[in]  p_dev    : fm175xx�豸
 * \param[in]  nregaddr : �Ĵ�����ַ
 *
 * \retval fm175xx�豸�Ĵ�����ֵ
 */
uint8_t am_fm175xx_get_reg (am_fm175xx_dev_t *p_dev, uint8_t nregadr);


/**
 * \brief ��fm175xx ��չ�Ĵ���
 *
 * \param[in]  p_dev    : fm175xx�豸
 * \param[in]  nregaddr : ��չ�Ĵ�����ַ
 *
 * \retval fm175xx�豸��չ�Ĵ�����ֵ
 */
uint8_t am_fm175xx_get_reg_ext (am_fm175xx_dev_t *p_dev, uint8_t nregadr);


/**
 * \brief ��fm175xx�Ĵ�����mask��Ϊ1��λ ��λ
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_bit (am_fm175xx_dev_t *p_dev,
                             uint8_t           nregadr,
                             uint8_t           mask);


/**
 * \brief ��fm175xx�Ĵ�����mask��Ϊ1��λ��0
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nregaddr : �Ĵ�����ַ
 * \param[in] mask     : �޸ĵ�λ����
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_clr_bit (am_fm175xx_dev_t *p_dev,
                             uint8_t           nregadr,
                             uint8_t           mask);


/**
 * \brief �޸�fm175xx�Ĵ�����λ
 *
 * \param[in] p_dev     : fm175xx�豸
 * \param[in] nregaddr  : �Ĵ�����ַ
 * \param[in] modifyval : �޸ĵ�λ����(0--��mask��1��λ��0;����--��mask��1��λ��1)
 * \param[in] mask      : �޸ĵ�λ����
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_modify_reg (am_fm175xx_dev_t *p_dev,
                                uint8_t           nregaddr,
                                uint8_t           modifyval,
                                uint8_t           mask);


/**
 * \brief дfm175xx ��չ�Ĵ���
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nregaddr : ��չ�Ĵ����ӵ�ַ
 * \param[in] nregval  : д����չ�Ĵ�����ֵ
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_extend_reg (am_fm175xx_dev_t *p_dev,
                                    uint8_t           nregaddr,
                                    uint8_t           nregval);


/**
 * \brief ��fm175xx ��չ�Ĵ���
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nregaddr : ��չ�Ĵ����ӵ�ַ
 *
 * \retval fm175xx��չ�Ĵ�����ֵ
 */
uint8_t am_fm175xx_get_extend_reg (am_fm175xx_dev_t *p_dev, uint8_t nregaddr);


/**
 * \brief fm175xx����״̬��⣬�����⵽����оƬ�Ĵ�����ֵ�쳣�仯���������ö���оƬ
 *
 * \param[in] p_dev    : fm175xx�豸
 *
 * \retval AM_FM175XX_STATUS_SUCCESS�����ͨ��
 * \retval AM_FM175XX_STATUS_FAIL   ����鲻ͨ��
 */
uint8_t am_fm175xx_check (am_fm175xx_dev_t *p_dev);


/**
 * \brief fm175xx�رգ��رյ�ģʽ�������������й�
 *
 * \param[in] p_dev    : fm175xx�豸
 *
 * \retval �ɹ�����AM_OK��ʧ�ܷ���AM_ERROR
 */
am_err_t am_fm175xx_close (am_fm175xx_dev_t *p_dev);


/**
 * \brief ���ý�����ʱ
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] _1ms  : ��ʱʱ�䣨��λΪ���룩����ֵӦʹ����ʱ�����ꡣ
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_tmo (am_fm175xx_dev_t *p_dev, uint16_t _1ms);


/**
 * \brief ���ÿ�ƬЭ�����ͺ��ٶȣ�ͬʱ������
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] type  : ��ƬЭ�����ͺ��ٶ�
 *                   - AM_FM175XX_PROT_TYPE_ISO14443A_106
 *                   - AM_FM175XX_PROT_TYPE_ISO14443B_106
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_set_iso_type (am_fm175xx_dev_t       *p_dev,
                                 am_fm175xx_prot_type_t  type);


/**
 * \brief FM175XX��λ
 *
 * \param[in] p_dev : fm175xx�豸
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_reset (am_fm175xx_dev_t *p_dev);


/**
 * \brief fm175xx����
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] type  : Э�����ͺ��ٶ�
 *                   - AM_FM175XX_PROT_TYPE_ISO14443A_106
 *                   - AM_FM175XX_PROT_TYPE_ISO14443B_106
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_config (am_fm175xx_dev_t         *p_dev,
                           am_fm175xx_prot_type_t    type);


/**
 * \brief ��������ֽڷ��͵�λ��
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] ntxlastbits : ����ֽڷ��͵�λ��
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_tx_last_bits (am_fm175xx_dev_t *p_dev,
                                      uint8_t           ntxlastbits);


/**
 * \brief ���ý������ݴ�ŵ���ʼλ��(λ)
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] nrxalign : �������ݴ�ŵ���ʼλ��
 *
 * \retval AM_OK       : ��Ϣ����ɹ�
 * \retval -AM_EINVAL  : ��������
 * \retval -AM_EIO     : �������
 */
am_err_t am_fm175xx_set_rx_align (am_fm175xx_dev_t *p_dev, uint8_t nrxalign);

/**
 * \brief ���ó�ͻλ��������Ǳ��ֻ�����0
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] keep_or_clr : ��ͻλ�������״̬
 *                        - 0    -- ��0
 *                        - ����    -- ����
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_set_keep_after_coll (am_fm175xx_dev_t *p_dev,
                                         uint8_t           keep_or_clr);


/**
 * \brief ��ȡ��ײλ��
 *
 * \param[in] p_dev : fm175xx�豸
 *
 * \retval ��ײλ��
 *
 * \note ֻ��am_fm175xx_cmd()���ء�AM_FM175XX_STATUS_COLLISION_ERROR�����󣬲���ͨ����
 *       ������ȡ��ײλ��
 */
uint8_t am_fm175xx_get_coll_pos (am_fm175xx_dev_t *p_dev);


/**
 * \name CRC����
 * @{
 */

#define AM_FM175XX_TX_CRC_EN       0x80      /**< \brief ����CRCʹ�� */
#define AM_FM175XX_RX_CRC_EN       0x40      /**< \brief ����CRCʹ�� */
#define AM_FM175XX_TX_CRC_DIS      0x00      /**< \brief ����CRC��ֹ */
#define AM_FM175XX_RX_CRC_DIS      0x00      /**< \brief ����CRC��ֹ */

 /** @} */

/**
 * \brief ʹ��/��ֹCRC
 *
 * \param[in] p_dev     : fm175xx�豸
 * \param[in] en_or_dis : ��ͻλ�������״̬
 *                        - en_or_dis.7 ����CRC����
 *                             - 1 -- ����ʹ��CRC;
 *                             - 0 -- ���ͽ�ֹCRC;
 *                        - en_or_dis.6 ����CRC����
 *                             - 1 -- ����ʹ��CRC;
 *                             - 0 -- ���ս�ֹCRC.
 *
 * \retval AM_OK        : ��Ϣ����ɹ�
 * \retval -AM_EINVAL   : ��������
 * \retval -AM_EIO      : �������
 */
am_err_t am_fm175xx_set_crc (am_fm175xx_dev_t *p_dev, uint8_t en_or_dis);


/**
 * \brief fm175xx��ֹCrypto1����
 *
 * \param[in] p_dev   : fm175xx�豸
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 */
am_err_t am_fm175xx_dis_crypto1 (am_fm175xx_dev_t *p_dev);


/**
 * \brief fm175xxִ������
 *
 * \param[in]  p_dev : fm175xx�豸
 * \param[in]  p_in  : ָ��fm175xx�����������
 * \param[out] p_out : ָ��fm175xx�������
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_cmd (am_fm175xx_dev_t                    *p_dev,
                        const am_fm175xx_cmd_input_para_t   *p_in,
                        am_fm175xx_cmd_output_para_t        *p_out);


/**
 * \brief ������������ģʽ
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] mode  : ��������ģʽ
 *                   - mode.0    -- TX1����
 *                               - 0        -- TX1�ر�
 *                               - 1        -- TX1��
 *                   - mode.1    -- TX2����
 *                               - 0        -- TX2�ر�
 *                               - 1        -- TX2��
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 *
 * \note ��ȻFM17510��֧��TX2������������TX2Ҳû��ϵ��
 */
am_err_t am_fm175xx_set_tx_mode (am_fm175xx_dev_t *p_dev, uint8_t mode);


/**
 * \brief ��ȡ���ߵ�ǰ����״̬
 *
 * \param[in]  p_dev : fm175xx�豸
 *
 * \retval ��������״̬���μ�am_fm175xx_set_tx_mode()
 */
uint8_t am_fm175xx_get_tx_mode (am_fm175xx_dev_t *p_dev);


/**
 * \brief ��/�ر��ز�
 *
 * \param[in]  p_dev : fm175xx�豸
 * \param[in]  moon_or_off : AM_TRUE -- ���ز���AM_FALSE -- �ر��ز�
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 *
 * \note ���ز�ֻ�ӳ���5ms,����Ҫ��������ʱ�������ⲿ���ӳ١�
 *       �ú�������ı���������ģʽ�������ز�ֻ���am_fm175xx_set_tx_mode()
 *       ���õ����������ˣ������Ǵ����е�����������
 */
am_err_t am_fm175xx_turn_carrier_wave (am_fm175xx_dev_t *p_dev,
                                       am_bool_t         on_or_off);


/**
 * \brief ��RF��(�ز�)����1����ͣ��ʹ����λ
 *
 * \param[in] p_dev    : fm175xx�豸
 * \param[in] pause_ms : ��ͣʱ�䣬�ر�RF����ʱ������´򿪣���Ϊ0�����´�
 * \param[in] wait_ms  : RF�����´򿪺�����ȴ���ʱ�䣬��Ϊ0�򲻵ȴ�
 *
 * \retval AM_OK      : ��Ϣ����ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EIO    : �������
 *
 * \note �ȴ�ʱ��ɸ��ݿ��Ĺ��Ķ�������Mifare1���Ĺ��Ľ�С���ȴ�2~5���뼴�ɣ�
 *       ��CPU�����Ľϴ���Ҫ�ȴ�10�������ҡ�
 */
am_err_t am_fm175xx_pause_carrier (am_fm175xx_dev_t *p_dev,
                                   uint8_t           pause_ms,
                                   uint8_t           wait_ms);


/**
 * \brief MF1����Crypto1��֤
 *
 * \param[in] p_dev  : fm175xx�豸
 * \param[in] mode   : ��֤ģʽ
 *                     - mode.6-0        -- ��Կ����
 *                         - KEY_TYPE_A    -- ��ԿA
 *                         - KEY_TYPE_B    -- ��ԿB
 *                     - mode.7          -- ��Կ��Դ
 *                         - KEY_SOURCE_EXT    -- ʹ���ⲿ�������Կ��֤
 *                         - KEY_SOURCE_E2     -- ʹ���ڲ�E2����Կ��֤
 * \param[in] p_key  : 6�ֽ���Կ��ʹ���ڲ���Կʱ����1�ֽ�Ϊ��Կ���������
 * \param[in] p_uid  : 4�ֽ�UID
 * \param[in] nblock : ��֤�Ŀ��
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note ִ�гɹ����Ժ��ͨ�ű�����
 */
uint8_t am_fm175xx_crypto1 (am_fm175xx_dev_t *p_dev,
                            uint8_t           mode,
                            const uint8_t     p_key[6],
                            const uint8_t     p_uid[4],
                            uint8_t           nblock);


/**
 * \name Mifare������ģʽ
 * @{
 */

#define AM_FM175XX_PICCA_REQ_IDLE 0x26 /**< \brief IDLEģʽ��������еĿ� */
#define AM_FM175XX_PICCA_REQ_ALL  0x52 /**< \brief ALLģʽ���������еĿ�  */

/** @}*/

/**
 * \brief Mifare���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443A��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in] p_dev       : fm175xx�豸
 * \param[in] req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_FM175XX_PICCA_REQ_IDLE
 *                           - #AM_FM175XX_PICCA_REQ_ALL
 * \param[out] p_atq      : ��ȡ����Ӧ����Ϣ��ATQ����ָ�룬��ֵΪ16λ��
 *                          ���������ATQ������NULL��
 *                          ��ͬ�����ͷ��ص���Ϣ��ͬ,�������ͷ��ص�ATQ���£�
 *
 *            Mifare1 S50    | Mifare1 S70 | Mifare1 Light | Mifare0 UltraLight
 *       --------------------|-------------|---------------|-------------------
 *              0x0004       |    0x0002   |    0x0010     |      0x0044
 *       ----------------------------------------------------------------------
 *          Mifare3 DESFire  |   SHC1101   |    SHC1102    |      11RF32
 *       --------------------|-------------|---------------|-------------------
 *               0x0344      |    0x0004   |    0x3300     |      0x0004
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note ���������ߺ󣬴���Ƶ���л�ȡ�������Ӷ��õ縴λ����λ�󿨴���IDLEģʽ��
 * ����������ģʽ����һ������ʱ����ʱ�Ŀ�������Ӧ������ĳһ�ſ��ɹ������˹���
 * ������Halt�����DeSelect������������Haltģʽ����ʱ�Ŀ�ֻ��ӦALL��0x52��
 * ģʽ�����󣬳��ǽ����뿪���߸�Ӧ�����ٽ��롣
 */
uint8_t am_fm175xx_picca_request (am_fm175xx_dev_t  *p_dev,
                                  uint8_t            req_mode,
                                  uint8_t            p_atq[2]);


/**
 * \name Mifare������ײ�ȼ�
 * @{
 */
#define AM_FM175XX_PICCA_ANTICOLL_1  0x93  /**< \brief ��һ������ײ  */
#define AM_FM175XX_PICCA_ANTICOLL_2  0x95  /**< \brief �ڶ�������ײ  */
#define AM_FM175XX_PICCA_ANTICOLL_3  0x97  /**< \brief ����������ײ  */
/** @}*/

/**
 * \brief Mifare���ķ���ײ����
 *
 *  ��Ҫ�ɹ�ִ��һ�������������������ɹ������ܽ��з���ײ���������򷵻ش���
 *
 * \param[in] p_dev          : fm175xx�豸
 * \param[in] anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_FM175XX_PICCA_ANTICOLL_1
 *                             - #AM_FM175XX_PICCA_ANTICOLL_2
 *                             - #AM_FM175XX_PICCA_ANTICOLL_3
 * \param[out] p_uid   : ����ײ���ȡ���Ŀ����к�

 * \param[out] p_real_uid_len : �����кŵ�ʵ�ʴ�С���ֽ�������
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note  ����ISO14443A��׼�������кŶ���ȫ��Ψһ�ģ���������Ψһ�ԣ�����ʵ�ַ�
 * ��ײ���㷨�߼������������ſ�ͬʱ�����߸�Ӧ��������������ܹ��ҵ�һ�����кŽ�
 * ��Ŀ���������
 */
uint8_t am_fm175xx_picca_anticoll (am_fm175xx_dev_t  *p_dev,
                                   uint8_t            anticoll_level,
                                   uint8_t           *p_uid,
                                   uint8_t           *p_real_uid_len);

/**
 * \brief Mifare����ѡ�����
 *
 *  ��Ҫ�ɹ�ִ��һ�η���ײ��������سɹ������ܽ��п�ѡ����������򷵻ش���
 *
 * \param[in]  p_dev          : fm175xx�豸
 * \param[in]  anticoll_level : ����ײ�ȼ�����ʹ�����к꣺
 *                             - #AM_FM175XX_PICCA_ANTICOLL_1
 *                             - #AM_FM175XX_PICCA_ANTICOLL_2
 *                             - #AM_FM175XX_PICCA_ANTICOLL_3
 * \param[in]  uid     : ǰһ������ײ������ȡ��UID
 * \param[in]  uid_len : ǰһ������ײ������ȡ��UID�ĳ��ȣ��ֽ�����
 * \param[out] p_sak   : ���ص���Ϣ����bit2Ϊ1�������UID�����������������SAK����NULL��
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note  �������кų��������֣�4�ֽڡ�7�ֽں�10�ֽڡ� 4�ֽڵ�ֻҪ��һ��ѡ�񼴿�
 * �õ����������кţ���Mifare1 S50/S70�ȣ�7�ֽڵ�Ҫ�ö���ѡ����ܵõ�����������
 * �ţ�ǰһ�����õ������кŵ�����ֽ�Ϊ������־0x88�������к���ֻ�к�3�ֽڿ��ã�
 * ��һ��ѡ���ܵõ�4�ֽ����кţ����߰�˳�����Ӽ�Ϊ7�ֽ����кţ���UltraLight
 * ��DesFire�ȣ�10�ֽڵ��Դ����ƣ�������δ���ִ��࿨��
 */
uint8_t am_fm175xx_picca_select (am_fm175xx_dev_t  *p_dev,
                                 uint8_t            anticoll_level,
                                 const uint8_t     *p_uid,
                                 uint8_t            uid_len,
                                 uint8_t           *p_sak);

/**
 * \brief Mifare���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *  ��HALT״̬�£���������Ӧ������������IDLEģʽ�����󣬳��ǽ�����λ���뿪���߸�
 *  Ӧ�����ٽ��롣��������Ӧ������������ALL����
 *
 * \param[in]  p_dev          : fm175xx�豸
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_halt (am_fm175xx_dev_t  *p_dev);

/**
 * \brief Mifare������ú������ڼ��Ƭ�������󡢷���ײ��ѡ�������������ϡ�
 *
 * \param[in]  p_dev      : fm175xx�豸
 * \param[in]  req_mode   : ����ģʽ����ʹ�����к꣺
 *                           - #AM_FM175XX_PICCA_REQ_IDLE
 *                           - #AM_FM175XX_PICCA_REQ_ALL
 * \param[out] p_atq      : ��Ƭ���ͣ�������������NULL��
 * \param[out] p_uid      : ������кŵĻ�����������Ӧ�������кų��ȱ���һ�£�
 *                          �粻ȷ����������ʹ����󳤶�10�����ܴ���NULL��

 * \param[out] p_uid_real_len   :���кŵ�ʵ�ʳ��ȣ�4�ֽڡ�7�ֽڻ�10�ֽڣ�������������NULL��
 * \param[out] p_sak      : ���һ��ѡ��Ӧ��SAK��������������NULL��
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_active (am_fm175xx_dev_t   *p_dev,
                                 uint8_t             req_mode,
                                 uint8_t             p_atq[2],
                                 uint8_t             p_uid[10],
                                 uint8_t            *p_uid_real_len,
                                 uint8_t             p_sak[1]);

/**
 * \name IC���ܳ�����
 * @{
 */

#define  AM_FM175XX_IC_KEY_TYPE_A      0x60    /**< \brief ���� A  */
#define  AM_FM175XX_IC_KEY_TYPE_B      0x61    /**< \brief ���� B  */

/** @}*/

/**
 * \brief Mifare����Կ��֤�����������Կ�뿨����Կ������֤
 *
 * \param[in] p_dev      : fm175xx�豸
 * \param[in] key_type   : ��Կ���ͣ�����ʹ������ֵ��
 *                          - #AM_FM175XX_IC_KEY_TYPE_A
 *                          - #AM_FM175XX_IC_KEY_TYPE_B
 * \param[in] p_uid      : �����кţ�4�ֽ�
 * \param[in] p_key      : ��Կ��6�ֽڡ�Ĭ�ϵ���Կ����ȫ1����6��0xff
 * \param[in] nblock     : ��Ҫ��֤�Ŀ���ţ�ȡֵ��Χ�뿨�����йأ�
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 *
 * \retval ��֤�ɹ�����AM_FM175XX_STATUS_SUCCESS�����򷵻�ȥ����״̬�롣
 *         (��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note PLUS CPUϵ�еĿ��Ŀ�����4�ֽں�7�ֽ�֮�֣�����7�ֽڿ��ŵĿ���
 *       ֻ��Ҫ�����ŵĸ�4�ֽڣ��ȼ�2����ײ�õ��Ŀ��ţ���Ϊ��֤�Ŀ��ż��ɡ�
 */
uint8_t am_fm175xx_picca_authent (am_fm175xx_dev_t  *p_dev,
                                  uint8_t            key_type,
                                  const uint8_t      p_uid[4],
                                  const uint8_t      p_key[6],
                                  uint8_t            nblock);

/**
 * \brief Mifare�����ݶ�ȡ
 *
 *     ����֤�ɹ�֮�󣬲��ܶ���Ӧ�Ŀ����ݣ�����֤�Ŀ�������ű�����ͬһ�������ڣ�
 * Mifare1���ӿ��0��ʼ��˳��ÿ4����1����������Ҫ��һ�ſ��еĶ���������в�������
 * ��ĳһ����������Ϻ󣬱������һ����������ܶ���һ������ֱ�ӽ�����֤�������
 * ���������ʼ����������PLUS CPU��������һ������������Կ�͵�ǰ��������Կ��ͬ��
 * ����Ҫ�ٴ���֤��Կ��ֱ�Ӷ����ɡ�
 *
 * \param[in]  p_dev      : fm175xx�豸
 * \param[in]  nblock     : ��ȡ���ݵĿ��
 *                          - S50��0 ~ 63
 *                          - S70��0 ~ 255
 *                          - PLUS CPU 2K��0 ~ 127
 *                          - PLUS CPU 4K��0 ~ 255
 * \param[out] p_buf      : ��Ŷ�ȡ�����ݣ���16bytes
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_read (am_fm175xx_dev_t  *p_dev,
                               uint8_t            nblock,
                               uint8_t            p_buf[16]);


/**
 * \brief Mifare��д���ݣ�д֮ǰ����ɹ�������Կ��֤��
 *
 *      �Կ���ĳһ�������֤�ɹ��󣬼��ɶ�ͬһ�����ĸ��������д������ֻҪ��������������
 *  ���а���λ������β������飬���Ǹ��������Ψһ����������PLUS CPU���ȼ�2��3��AES��
 *  Կ����������λ���޸���Կ��
 *
 * \param[in] p_dev      : fm175xx�豸
 * \param[in] nblock     : ��ȡ���ݵĿ��
 *                         - S50��0 ~ 63
 *                         - S70��0 ~ 255
 *                         - PLUS CPU 2K��0 ~ 127
 *                         - PLUS CPU 4K��0 ~ 255
 * \param[in] p_buf      : д�����ݻ���������С����Ϊ 16
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_write (am_fm175xx_dev_t  *p_dev,
                                uint8_t            nblock,
                                const uint8_t      p_buf[16]);

/**
 * \name Mifare��ֵ����ģʽ
 * @{
 */

#define AM_FM175XX_PICCA_PICC_ADD       0xC1   /**< \brief ��ֵ */
#define AM_FM175XX_PICCA_PICC_SUB       0xC0   /**< \brief ��ֵ */

/** @}*/

/**
 * \brief Mifareֵ��������Mifare����ֵ����мӼ�����
 *
 * \param[in] p_dev      : fm175xx�豸
 * \param[in] mode       : ֵ������ģʽ�������Ǽӻ����ʹ�����к꣺
 *                          - AM_FM175XX_PICCA_PICC_ADD
 *                          - AM_FM175XX_PICCA_PICC_SUB
 * \param[in] nblock     : ����ֵ�����Ŀ��
 *                          - S50��0 ~ 63
 *                          - S70��0 ~ 255
 *                          - PLUS CPU 2K��0 ~ 127
 *                          - PLUS CPU 4K��0 ~ 255
 * \param[in] ntransblk  : �����ţ�������ֵ��ŵĿ��
 * \param[in] value      : 4�ֽ��з�����
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note Ҫ���д�������������ݱ���Ҫ��ֵ��ĸ�ʽ������ʹ��
 * am_fm175xx_picca_val_set()���������ݿ��ʼ��Ϊֵ��ĸ�ʽ���ɲο�NXP�������
 * ���������� * ���봫������ͬ���򽫲�����Ľ��д��ԭ���Ŀ��ڣ���������봫���Ų���ͬ���򽫲������
 * ���д�봫����ڣ����������ڵ����ݱ����ǣ�ԭ���ڵ�ֵ���䡣���ڵȼ�2��PLUS CPU����֧��ֵ���������
 * ��1��3֧�֡�
 *       ���м�ֵ������������֤KEYB�����м�ֵ������������֤KEYA��
 *       ����ͨ�����벻ͬ�Ŀ飬����value��ֵ��Ϊ0���������ݡ�
 */
uint8_t am_fm175xx_picca_val_operate (am_fm175xx_dev_t  *p_dev,
                                      uint8_t            mode,
                                      uint8_t            nblock,
                                      uint8_t            ntransblk,
                                      int32_t            value);

/**
 * \brief Mifareֵ����������ֵ���ֵ
 *
 * \param[in] p_dev      : fm175xx�豸
 * \param[in] nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[in] value      : ���õ�ֵ
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note �ú���ʹ��ֱ��д���ݵķ�ʽ����ָ���Ŀ��ʽת��Ϊ��ֵ�飬����ʼ����ֵ���ֵ��Ҳ����ʹ�øú�����
 *       ����ֵ���ֵ���Կ���ĳһ�������֤�ɹ��󣬲��ҷ�������������ܽ��д˲�����
 */
uint8_t am_fm175xx_picca_val_set (am_fm175xx_dev_t  *p_dev,
                                  uint8_t            nblock,
                                  int32_t            value);


/**
 * \brief Mifareֵ��������ȡֵ���ֵ
 *
 * \param[in]  p_dev      : fm175xx�豸
 * \param[in]  nblock     : ��ȡ���ݵ�ֵ���ַ
 * \param[out] p_value    : ��ȡֵ��ָ��
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note �ú���ʹ��ֱ��д���ݵķ�ʽ����ָ���Ŀ��ʽת��Ϊ��ֵ�飬����ʼ����ֵ���ֵ��Ҳ����ʹ�øú�����
 *       ����ֵ���ֵ���Կ���ĳһ�������֤�ɹ��󣬲��ҷ�������������ܽ��д˲�����
 */
uint8_t am_fm175xx_picca_val_get (am_fm175xx_dev_t  *p_dev,
                                  uint8_t            nblock,
                                  int32_t           *p_value);

/**
 * \brief A��Э�����
 *
 * \param[in] p_dev : fm175xx�豸
 * \param[in] cid   : ��ʶ��ţ�ȡֵ��Χ0--14
 * \param[in] p_ats : RATS
 *
 * \return �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_prot_parse (am_fm175xx_dev_t  *p_dev,
                                     uint8_t            cid,
                                     const uint8_t     *p_ats);

/**
 * \brief RATS
 *
 * \param[in]  p_dev    : fm175xx�豸
 * \param[in]  cid      : ��ʶ��ţ�ȡֵ��Χ0--14
 * \param[out] p_rats   : ����Ӧ������Ӧ��Ϣ
 * \param[out] buf_size : ��Ӧ��Ϣ�Ļ�������С
 * \param[out] p_nbytes : ����Ӧ������Ӧ��Ϣ���ֽ���
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_rats_get (am_fm175xx_dev_t *p_dev,
                                   uint8_t   cid,
                                   void     *p_rats,
                                   uint32_t  buf_size,
                                   uint32_t *p_nbytes);

/**
 * \brief A��Э��Ͳ���ѡ������
 *
 * \param[in]  p_dev    : fm175xx�豸
 * \param[in]  flags    : λ�ʱ���
 *                      - b3:2 -- PCD  -> PICC��λ�ʱ���
 *                      - b1:0 -- PICC -> PCD ��λ�ʱ���
 *                          - (00)b -> 106Kb
 *                          - (01)b -> 212Kb
 *                          - (10)b -> 424Kb
 *                          - (11)b -> 847Kb
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_pps_set (am_fm175xx_dev_t *p_dev,
                                  uint8_t flags);

/**
 * \brief A��ȡ��ѡ��
 *
 * \param[in]  p_dev    : fm175xx�豸
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_deselect (am_fm175xx_dev_t *p_dev);

/**
 * \brief ���䣨T=CL��
 *
 * \param[in]  p_dev  : fm175xx�豸
 * \param[in] p_txbuf : ��������ݻ�����
 * \param[in] n_tx    : ��Ҫ����������ֽ���
 * \param[in] p_rxbuf : �������ݻ�����
 * \param[in] n_rx    : ��Ҫ���յ��ֽ���
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_picca_transfer (am_fm175xx_dev_t *p_dev,
                                   const void       *p_txbuf,
                                   uint32_t          n_tx,
                                   void             *p_rxbuf,
                                   uint32_t          buf_size,
                                   uint32_t         *p_n_rx);

/**
 * \brief ��д����IC�����ݽ���
 *
 * \param[in]  p_dev       : fm175xx�豸
 * \param[in]  sendbuf     : �����͵�����
 * \param[in]  sendlen     : �������ݵĳ���
 * \param[out] recvbuf     : �����յ�����
 * \param[in]  recvbufsize : ��Ҫ���յ����ݸ���
 * \param[out] recvlen     : �����յ����ֽ���
 * \param[in]  nwtxm_crc   : crcУ�����
 * \param[in]  nfwi        : ��ʱ
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_exchange_block (am_fm175xx_dev_t *p_dev,
                                   uint8_t          *sendbuf,
                                   uint32_t          sendlen,
                                   uint8_t          *recvbuf,
                                   uint32_t          recvbufsize,
                                   uint16_t         *recvlen,
                                   uint8_t           nwtxm_crc,
                                   uint8_t           nfwi);

/**
 * \name PICCB������ģʽ
 * @{
 */

#define AM_FM175XX_PICCB_REQ_IDLE 0x00 /**< \brief IDLEģʽ,������еĿ� */
#define AM_FM175XX_PICCB_REQ_ALL  0x08 /**< \brief ALLģʽ,�������еĿ�  */

/** @}*/

/**
 * \brief PICCB���������
 *
 *  �ú�����Ϊ�������������ֻҪ����ISO14443B��׼�Ŀ���Ӧ�ܷ�����Ӧ��
 *
 * \param[in]  p_dev       : fm175xx�豸
 * \param[in]  req_mode    : ����ģʽ����ʹ�����к꣺
 *                           - #AM_FM175XX_PICCB_REQ_IDLE
 *                           - #AM_FM175XX_PICCB_REQ_ALL
 * \param[in]  slot_time   : ʱ϶������0 ~ 4
 * \param[out] atqb        : ���ض�REQB�������Ӧ������Ϊ12
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_piccb_request (am_fm175xx_dev_t *p_dev,
                                  uint8_t           req_mode,
                                  uint8_t           slot_time,
                                  uint8_t           atqb[12]);

/**
 * \brief B�࿨��ATTRIB����
 *
 * \param[in] p_dev      : fm175xx�豸
 * \param[in] p_pupi     : PUPI,��СΪ4�ֽڵı�ʶ��
 * \param[in] cid        : ȡֵ��ΧΪ 0 - 14, ����֧��CID��������Ϊ0��CID��PCD�涨����������
 *                         ͬһʱ�̴���ACTIVE״̬��PICC��Ψһ��
 * \param[in] protype    : ֧�ֵ�Э��
 *                          - bit3 : 1-PCD��ֹ��PICC����ͨ��,0-PCD��PICC����ͨ��
 *                          - bit2 ~ bit1 :
 *                              - 11 : 10 etu + 512 / fs
 *                              - 10 : 10 etu + 256 / fs
 *                              - 01 : 10 etu + 128 / fs
 *                              - 00 : 10 etu + 32 / fs
 *                          - bit0 : 1-��ѭISO14443-4,0-����ѭISO14443-4
 *                                   (�������֤�����λ����Ϊ1)
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note ִ�и�����ʱ�����ȳɹ�ִ��һ��request����
 */
uint8_t am_fm175xx_piccb_attrib (am_fm175xx_dev_t *p_dev,
                                 const uint8_t     pupi[4],
                                 uint8_t           cid,
                                 uint8_t           protype);

/**
 * \brief ��ȡB�࿨��UID
 *
 * \param[in]  p_dev   : fm175xx�豸
 * \param[out] uid     : ��ȡ����8�ֽ�UID
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note ִ�и�����ʱ�����ȳɹ�ִ��һ��attrib����
 */
uint8_t am_fm175xx_piccb_guid (am_fm175xx_dev_t *p_dev, uint8_t uid[8]);

/**
 * \brief PICC B�������ȡUID
 *
 * \param[in]  p_dev    : fm175xx�豸
 * \param[in]  req_mode : ����ģʽ����ʹ�����к꣺
 *                         - #AM_FM175XX_PICCB_REQ_IDLE
 *                         - #AM_FM175XX_PICCB_REQ_ALL
 * \param[out] p_uid    : UID�����Ϣ������Ϊ8
 * \param[out] p_uid_len  : UID����(���֤Ϊ8������B����Ϊ4)
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 *
 * \note �ڵ��øú���ǰ����Ҫȷ��IC����ģʽ�Ѿ�����ΪTypeBģʽ��
 */
uint8_t am_fm175xx_piccb_active (am_fm175xx_dev_t *p_dev,
                                 uint8_t           req_mode,
                                 uint8_t           uid[8],
                                 uint8_t          *p_uid_len);

/**
 * \brief PICC B���Ĺ��������ʹ��ѡ��Ŀ�����HALT״̬
 *
 *     �ú�������B�Ϳ�������ִ�й�������ǰ��������ִ�гɹ���һ���������ִ��
 * ��������ɹ��󣬿�Ƭ���ڹ���״̬��ģ�����ͨ��ALL��ʽ����Ƭ����������IDLE��
 * ʽ����
 *
 * \param[in] p_dev   : fm175xx�豸
 * \param[in] pupi    : PUPI,��СΪ4�ֽڵı�ʶ��
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
uint8_t am_fm175xx_piccb_halt (am_fm175xx_dev_t *p_dev,
                               const uint8_t     pupi[4]);

/**
 * \brief PCD����LPCDģʽ�ĳ�ʼ��
 *
 *    FM175xx�豸�ڴ˺����������  �Ĵ����ĳ�ʼ��   ��У������ʼ��   �ж����ó�ʼ��
 *��У���̣�����GPA��������    �ο���ѹ����   ��ֵ���õȣ���
 *
 * \param[in] p_dev   : fm175xx�豸
 *
 * \retval �������(��ϸ˵����am_fm175xx.h�е�״̬�붨��)
 */
int8_t am_fm175xx_lpcd_init(am_fm175xx_dev_t *p_dev);

/**
 * \brief PCD����LPCDģʽ
 *
 *    ����֮ǰ�����am_fm175xx_lpcd_init��������LPCDģʽ�Ĵ������г�ʼ��
 *
 * \param[in] handle   : fm175xx�豸���
 *
 */
void  am_fm175xx_lpcd_mode_entry(am_fm175xx_handle_t handle);

/**
 * \brief PCD�˳�LPCDģʽ
 *
 *    �˳�LPCDģʽ֮����Ҫ��ʱ1ms��ȷ���豸��������ʹ�ô˺����˳���
 *�����am_fm175xx_exit_lpcd_config ������δ��������ݽ����������ã�ȷ���豸��������
 *
 * \param[in] handle   : fm175xx�豸���
 *
 */
void  am_fm175xx_lpcd_mode_exit(am_fm175xx_handle_t handle);
/**
 * \brief PCD�˳�LPCDģʽ���δ��������ݽ�����������
 *
 * \param[in] p_dev   : fm175xx�豸
 *
 */
void  am_fm175xx_exit_lpcd_config(am_fm175xx_dev_t   *p_dev);

/**
 * \brief PCDģʽ�����������жϻص���������
 *
 * \param[in] p_dev   : fm175xx�豸
 * \param[in] pfn_callback   : �ص�����
 * \param[in] p_lpcd_cb_arg   : �ص���������
 *
 */
void  am_fm175xx_lpcd_cb_set(am_fm175xx_dev_t   *p_dev,
                             am_pfnvoid_t        pfn_callback,
                             void               *p_lpcd_cb_arg);
/** @} */

/**
 * @} am_if_fm175xx
 */

#ifdef __cplusplus
}
#endif

#endif /* __FM175XX_H */

/* end of file */
