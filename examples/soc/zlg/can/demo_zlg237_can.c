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
 * \brief CAN��ʾ����
 *
 * - �������裺
 *   1. ����������am_prj_config.hͷ�ļ���ʹ��
 *   -  ��Ӧƽ̨�Ĵ����豸��(AM_DEV_XXXXX_UART1)��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ50k��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *   5. ��λ�� ����֡��ʽΪ ��չ֡  Զ��������Ҫ��(����֡��Զ��֡����) IDΪ 0x -7- ��  ��4-6 λΪ1
 *   6. ��Ҫ�޸� �����ļ�ע����λ�����͵�֡��ʽ������  �����ļ��� amh_hwconf_zlg237_can.c
 *      �޸�֡��ʽ�����ͺ� �� ��Ҫ��ע��table������ ��ʽ�仯 �����ע��
 * - ʵ������
 *   1. ��λ���������ݺ��յ����͵����ݡ�
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 *
 * \par Դ����
 * \snippet demo_zlg237_can.c src_std_can
 *
 * \internal
 * \par Modification History
 * - 19-8-12, zc, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_can
 * \copydoc demo_std_can.c
 */

/** [src_std_can] */
#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "amhw_zlg237_can.h"
#include "am_zlg237_can.h"

/**
 *  2��16λ������  ��ʶ������λģʽ
 *  ����am_hwconf_zlg237_can.c�е�__g_can_filter����Ϊ
 *  AMHW_ZLG237_CAN_FILTER_MODE_IDMASK  AMHW_ZLG237_CAN_FILTER_SCALE_16BIT
 *
 *
 *  ע�� ��
 *      ������ ��չ��ʶ��ģʽʱ�� ������Ϊ����ֻ��������EXID ����������STID��λ�� �������ݷ��޷�����
 *
 *      ������Ϊ��׼��ʶ��ģʽʱ��������λֻ��������STIDλ�ϣ�����������EXID��  ���������޷�����
 *      16λ�Ĵ���ӳ������ �� STID[10:3] STID[2:0] RTR IDR EXID[17:15]
 *
 *      table�д����IDΪ ��׼��ʶ��ģʽ  STID[10:3] STID[2:0]
 *                     ��չ��ʶ��ģʽ EXID[17:15]  STID[10:3] STID[2:0]
 *
 *  �������ļ����޸�֡���� Ϊ  CAN_ID_EXT
 *  static uint8_t table[8] = {0x28, 0x00, 0x00,  0x07,  0x28, 0x00, 0x00, 0x07};
 *                       �� ID_H 0X28 ID_L  0X00  ��ID��ʵ��ֵΪ 0x28000
 *                       ������λ������ʱ��������ID(0x28,0x00)Ϊ   0x28000 (��Ϊ18λ����չID)
 *                       ����0x7 Ϊ ��չ��ʶ������ STID[17:15] ÿһλ����ƥ��
 *                       ��λ������IDλ 28xxx ��ʶ��Ϊ��չ  Զ��������Ҫ��
 *
 *  �������ļ����޸�֡����Ϊ CAN_IS_STD
 *  static uint8_t table[8] = {0x00, 0x01, 0x00,  0x20,  0x00, 0x02, 0x00, 0x40};
 *       ���˲����  ����Ϊ �������ID�ĵ�0λ ��� 1 λ Ϊ 1 ���ɴ���FIFO��
 *       ��λ����������Ϊ   ��ʶ��Ϊ��׼֡ Զ��������Ҫ��
 *    STID[10:3] STID[2:0] RTR IDR EXID[17:15]
 *
 *    ����Զ�����������  ͬ�Ͻ�������
 *
 *      table�д����MASK����
 *      table[0] 0x28   0b101000 EXID[17:15]  0b101  STID[10:8] 0b000
 *      table[1] 0x00   STID[7:0] 0
 *      table[2] 0x00   MASK_STD[10:3]
 *      table[3] 0x07   0b00000111  MASK_STD[2:0] MASK_RTR MASK_IDE MASK_EXID
 *      table[4] - table[7] ��һ��
 *                            id_h  id_l  mask_h mask_l
 * static uint8_t table[8] = {0x28, 0x00, 0x00,  0x07,  0x28, 0x00, 0x00, 0x07};
 */

/**
 * 4��16λ ��ʶ���б��˲���
 * ����am_hwconf_zlg237_can.c�е�__g_can_filter����Ϊ
 * AMHW_ZLG237_CAN_FILTER_MODE_IDLIST  AMHW_ZLG237_CAN_FILTER_SCALE_16BIT
 *
 *ע��:  ����չģʽ�� ֻ�ܶ� ��չID��EID[17:15] �������� ����λ�������ã����������ñ�׼ID��ֵ��
 *      �ڱ�׼ģʽ��ֻ�ܶԱ�׼ID�Ľ�������  ����������չID��ֵ
 *
 *      table�д����IDΪ ��׼��ʶ��ģʽ  STID[10:3]   STID[2:0]
 *                     ��չ��ʶ��ģʽ EXID[17:15]  STID[10:3] STID[2:0]
 *
 *                     ��չ��ʶ������ID��λʵ��ֵ����  2��16λ������  ��ʶ������λģʽ
 *      table[0]  ID��λ
 *      table[1]  ID��λ
 *      ÿ����Ԫ��Ϊһ��ID
 *
 * CAN_IS_STD
 *                             ID_H  ID_L  ID_H ID_L ....
 * static uint8_t table[16] = {0x00, 0x01, 0x00, 0X02, 0x00, 0x03, 0x00, 0x04,
 *                             0x00, 0x05, 0x00, 0X06, 0x00, 0x07, 0x00, 0x08};
 *  ��table����IDΪ           0x1 0x2 0x3 0x4 0x5 0x6 0x7 0x8
 *  ֡ģʽΪ  ��׼֡  Զ��֡������Ҫ�������ļ������õ�ƥ��
 *
 * CAN_ID_EXT
 * static uint8_t table[8] = {0x08, 0x00, 0x18, 0x00, 0x20, 0x00, 0x30, 0x00};
 *  ��table�ɹ��˵�IDΪ                            0x8xxx     0x18xxx     0x2xxxx     0x3xxxx
 *  ֡ģʽΪ  ��չ֡  Զ��֡������Ҫ�������ļ������õ�ƥ��
 *
 * ����չ֡ģʽ�±�������չIDΪ����IDֵ ��EXID[17:15] ������һλΪ 1
 *
 */

/**
 *  1��32λ������  ��ʶ������
 *  ����am_hwconf_zlg237_can.c�е�__g_can_filter����Ϊ
 *  AMHW_ZLG237_CAN_FILTER_MODE_IDMASK  AMHW_ZLG237_CAN_FILTER_SCALE_32BIT
 *
 *      table�д����IDΪ ��׼��ʶ��ģʽ  STID[10:0]
 *                     ��չ��ʶ��ģʽ EXID[28��0]
 *
 *  �����ע֡��ʽ���������ú�ID�����������Ƿ�ƥ��
 *
 *  ����ID Ϊ 0x70                         0b1 1100 00
 *   ���������ù���ʱ Ϊ table[7]   0x01 0xc0  0b1 1100 0000 (�����λΪ IDE RTR)
 *   MASK :    EXIT[28:0] IDE RTR
 *         ����  STID[10:0] IDE RTR
 *
 * CAN_ID_EXT
 *                            ID_H  ID_H  ID_L  ID_L  MASK_H  MASK_H MASK_L MASK_L
 * static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};
 * ��λ������IDΪ 0x x7x  ֡��ʽΪ ��չ֡ Զ��������Ҫ��
 *
 * CAN_IS_STD
 *                            ID_H  ID_H  ID_L  ID_L  MASK_H  MASK_H MASK_L MASK_L
 * static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};
 * ��λ������IDΪ 0x x7x  ֡��ʽΪ ��չ֡ Զ��������Ҫ��
 *
 * table�д����MASK����    STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] IDR RTR
 *
 *
 *
 */


/**
 *  2��32λ������  ��ʶ���б�
 *  ����am_hwconf_zlg237_can.c�е�__g_can_filter����Ϊ
 *  AMHW_ZLG237_CAN_FILTER_MODE_IDLIST  AMHW_ZLG237_CAN_FILTER_SCALE_32BIT
 *
 *      table�д����IDΪ ��׼��ʶ��ģʽ  STID[10:0]
 *                     ��չ��ʶ��ģʽ EXID[28��0]
 *

 *
 * table�д����MASK: STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] IDR RTR
 *
 * static uint8_t table[16] = {0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02,
 *                             0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04};
 *
 * ��table����IDΪ  0x1 0x2 0x3 0x4  ֡���ͺ�֡��ʽ��������õĽ���ƥ��
 *
 *
 *
 */

/**\brief �˲��� */
 static uint8_t table[8] = {0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x01, 0xc0};

/**
 * \brief �����ж�
 */
static void __can_err_sta( am_can_bus_err_t err)
{

    if (err & AM_CAN_BUS_ERR_BIT) {    /**< \brief λ���� */
        am_kprintf(("AM_CAN_BUS_ERR_BIT\n"));
    }
    if (err &AM_CAN_BUS_ERR_ACK) {     /**< \brief Ӧ����� */
        am_kprintf(("AM_CAN_BUS_ERR_ACK\n"));
    }
    if (err &AM_CAN_BUS_ERR_CRC) {     /**< \brief CRC���� */
        am_kprintf(("AM_CAN_BUS_ERR_CRC\n"));
    }
    if (err &AM_CAN_BUS_ERR_FORM) {    /**< \brief ��ʽ���� */
        am_kprintf(("AM_CAN_BUS_ERR_FORM\n"));
    }
    if (err &AM_CAN_BUS_ERR_STUFF) {   /**< \brief ������ */
        am_kprintf(("AM_CAN_BUS_ERR_STUFF\n"));
    }
}

/**
 * \brief �������
 */
void demo_zlg237_can_entry (am_can_handle_t      can_handle,
                            am_can_bps_param_t  *can_btr_baud)
{
    am_can_err_t ret;
    uint8_t      i = 0;
    am_can_message_t    can_rcv_msg = {0};
    am_can_bus_err_t    can_bus_err_status;
    am_can_int_type_t   can_int_status;

    /* ���ò����� */
    ret = am_can_baudrate_set (can_handle, can_btr_baud);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller baudrate set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller baudrate set error! %d \r\n", ret);
    }

    /* �����˲��� */
    ret = am_can_filter_tab_set(can_handle,table,
                                sizeof(table)/sizeof(uint8_t));

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller filter tab set ok. \r\n");
    } else {
        am_kprintf("\r\nCAN: controller filter tab set error! %d \r\n", ret);
    }

    /* ����can */
    ret = am_can_start (can_handle);

    if (ret == AM_CAN_NOERROR) {
        am_kprintf("\r\nCAN: controller start \r\n");
    } else {
        am_kprintf("\r\nCAN: controller start error! %d \r\n", ret);
    }

    AM_FOREVER {
        ret = am_can_msg_recv (can_handle, &can_rcv_msg);

        if (can_rcv_msg.msglen  || can_rcv_msg.flags || can_rcv_msg.id) {
            am_kprintf("can recv id: 0x%x\r\n",can_rcv_msg.id);
            for (i = 0; i < can_rcv_msg.msglen; i++) {
                am_kprintf("data: 0x%x \r\n",can_rcv_msg.msgdata[i]);
            }
            ret = am_can_msg_send (can_handle, &can_rcv_msg);

            if (ret == AM_CAN_NOERROR) {
                am_kprintf(("\r\nCAN: controller rcv data ok. \r\n"));
            } else {
                am_kprintf("\r\nCAN: controller no rcv data! \r\n");
            }
        }

        ret = am_can_status_get (can_handle,
                                &can_int_status,
                                &can_bus_err_status);

        am_mdelay(10);
        if (can_bus_err_status != AM_CAN_BUS_ERR_NONE) {
            __can_err_sta(can_bus_err_status);
        }
    }
}
/** [src_zlg237_can] */

/* end of file */
