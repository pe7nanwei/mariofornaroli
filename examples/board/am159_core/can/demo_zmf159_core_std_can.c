/*******************************************************************************
*                                 AMorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
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
 *   1. ����������am_prj_params.hͷ�ļ���ʹ��
 *   - ��Ӧƽ̨��CAN�豸��(AM_DEV_XXXXX_CAN1);
 *   - AM_COM_CONSOLE;
 *   -  ��Ӧƽ̨�Ĵ����豸��(AM_DEV_XXXXX_UART1)��
 *   2. ����CAN1��������ŵ�CAN�շ������ٽ�CAN�շ����ӿ���USBCAN-II�豸������
 *   3. ��CAN��λ�������ò�����Ϊ500k��
 *   4. �򿪴��ڵ����նˣ�������115200-8-N-1.
 *
 * - ʵ������
 *   1. ��λ���������ݺ��յ����͵����ݡ�
 *   2. ���ڴ�ӡ��ص�����Ϣ��
 *
 * - ��ע��
 *   1. ���� CAN ID �� ���������� ��Ҫ���ݾ���Ӳ��ƽ̨�޸ġ�
 *
 * \par Դ����
 * \snippet test_flexcan.c src_test_flexcan
 *
 * \internal
 * \par modification history:
 * - 17-12-15, mex, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_zmf159_inst_init.h"
#include "am_vdebug.h"

#define  CAN_CHN              0     /*CAN ID�����ݾ���ƽ̨�޸�*/
#define  CAN_RCV_BUFF_LENTH   1024

static am_can_message_t    can_rcv_msg;
static am_can_bus_err_t    can_bus_err_status;
static am_can_int_type_t   can_int_status;


static am_can_message_t can_send_test_msg = {
        0x111,
		AM_CAN_SELF_SEND_FLAG,          /**< \brief �Է��������� */
        8,                              /**< \brief msglen ���ĳ��� */
    {0x11,0x02,0x13,0x04,0x15,0x06,0x17,0x08}
};

/** \brief �����ʱ������ȡ���ھ���Ӳ��ƽ̨����Ҫ���ݾ���Ӳ��ƽ̨������Ӧ���޸�*/
/** \brief �����ʱ�ʹ��CAN�����ʼ��㹤�߼���ó�,�����ο�(Ŀǰ����ʱ��ΪPLL3 6��Ƶ ��2��Ƶ 40MHz) */
/** \brief 6ul�����ʼ����봫ͳ��ͬ,ʹ��ʱ�����߼���ֵ�е�tseg1-1���� */
/** \brief tseg1 tseg2 sjw brp smp */
//static am_can_bps_param_t can_btr_1000k = {4 - 1,   1,   1,   0,   4  };   /* 1000k, sample point 75% */
//static am_can_bps_param_t can_btr_800k  = {4 - 1,   3,   1,   0,   4  };   /* 800k,  sample point 60% */
static am_can_bps_param_t can_btr_500k  = {4 - 1,   1,   1,   0,   9  };   /* 500k,  sample point 75% */
//static dam_can_bps_param_t can_btr_250k  = {4 - 1,   1,   1,   0,   19 };   /* 250k,  sample point 75% */
//static am_can_bps_param_t can_btr_125k  = {4 - 1,   1,   1,   0,   39 };   /* 125k,  sample point 75% */
//static am_can_bps_param_t can_btr_100k  = {4 - 1,   1,   1,   0,   49 };   /* 100k,  sample point 75% */
//static am_can_bps_param_t can_btr_50k   = {4 - 1,   1,   1,   0,   99 };   /* 50k,   sample point 75% */
//static am_can_bps_param_t can_btr_20k   = {4 - 1,   1,   1,   0,   249};   /* 20k,   sample point 75% */
//static am_can_bps_param_t can_btr_10k   = {8 - 1,   5,   1,   0,   249};   /* 10k,   sample point 62.5% */
//static am_can_bps_param_t can_btr_6_25k = {15 - 1,  7,   1,   0,   255};   /* ����С�����ʣ�6.25k, sample point 68% */

/******************************************************************************/
void __can_err_sta( am_can_bus_err_t err)
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
 * \brief CAN demo
 *
 * \return ��
 */
void demo__zmf159_core_can_entry (void)
{
    am_can_err_t ret;

    /** \brief ��ʼ��CAN */
    am_can_handle_t  can_handle = NULL;

    can_handle = am_zmf159_can_inst_init ();

    ret = am_can_baudrate_set (can_handle, &can_btr_500k);

    if (ret == AM_CAN_NOERROR) {
        AM_INFOF(("\r\nCAN: controller initialize ok. \r\n"));
    } else {
        AM_INFOF(("\r\nCAN: controller initialize error! %d \r\n", ret));
    }

    ret = am_can_start (can_handle);

    if (ret == AM_CAN_NOERROR) {
        AM_INFOF(("\r\nCAN: controller start ok. \r\n"));
    } else {
        AM_INFOF(("\r\nCAN: controller start error! %d \r\n", ret));
    }

    /** \brief ����CAN */
    AM_INFOF(("CAN: controller start!\r\n"));

    AM_FOREVER {
    	ret = am_can_msg_send (can_handle, &can_send_test_msg);

        if (ret == AM_CAN_NOERROR) {
            AM_INFOF(("\r\nCAN: controller send ok. \r\n"));
        } else {
            AM_INFOF(("\r\nCAN: controller send error! %d \r\n", ret));
        }

        ret = am_can_msg_recv (can_handle, &can_rcv_msg);

        if (ret == AM_CAN_NOERROR) {
             AM_INFOF(("\r\nCAN: controller rcv ok. \r\n"));
        } else {
             AM_INFOF(("\r\nCAN: controller rcv error! %d \r\n", ret));
        }

        ret = am_can_status_get (can_handle, &can_int_status, &can_bus_err_status);

            am_mdelay(10); /* ��ʱ10ms */
            if (can_bus_err_status != AM_CAN_BUS_ERR_NONE) {
            	__can_err_sta(can_bus_err_status);
            }

        am_mdelay(1000);
    }
}

/** [src_test_flexcan] */

/* end of file */
