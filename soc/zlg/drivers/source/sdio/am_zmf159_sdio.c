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
 * \brief SDIO����������SDIO��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 17-12-28  pea, add a timeout mechanism, enable TX_ABRT and STOP_DET
 *                  interrupt
 * - 1.00 17-04-24  sdy, first implementation
 * \endinternal
 */

/*******************************************************************************
  ͷ�ļ�
*******************************************************************************/
#include "ametal.h"
#include "am_clk.h"
#include "zmf159_clk.h"
#include "am_int.h"
#include "am_sdio.h"
#include "am_zmf159_sdio.h"
#include "hw/amhw_zmf159_sdio.h"

/*******************************************************************************
  �궨��
*******************************************************************************/

#define __SDIO_EVT_NONE            (0xFFu)          /* ���¼� */
#define __SDIO_EVT_MSG_LAUNCH      (0xFEu)          /* ��ʼ����һ���µ���Ϣ */
#define __SDIO_EVT_TRANS_LAUNCH    (0xFDu)          /* ��ʼ����һ���µĴ��� */

#define __SDIO_ST_MSG_START        (0x11u)          /* ��Ϣ���俪ʼ״̬ */
#define __SDIO_ST_IDLE             (0x10u)          /* ����״̬ */
#define __SDIO_ST_TRANS_START      (0x12u)          /* �������俪ʼ״̬ */
#define __SDIO_ST_SEND_CMD         (0x13u)          /* ��������״̬ */
#define __SDIO_ST_M_SEND_DATA      (0x14u)          /* ��������״̬ */
#define __SDIO_ST_M_RECV_DATA      (0x15u)          /* ��������״̬ */

///* check if transfers empty */
//#define __SDIO_TRANS_EMPTY(p_dev) \
//    ((p_dev)->p_cur_trans >= (p_dev)->p_cur_msg->p_transfers \
//                             + (p_dev)->p_cur_msg->trans_num)

/** \brief SDIO ��Ϣ������ */
static int __sdio_msg_start (void *p_drv);

/** \brief SDIO Ӳ����ʼ�� */
static int __sdio_hard_init (am_zlg_sdio_dev_t *p_dev);

/** \brief SDIO �жϴ����� */
static void __sdio_irq_handler (void *p_arg);

/** \brief SDIO �жϴ����� */
static int __sdio_send_cmd (void *p_drv, am_sdio_cmd_t *cmd_msg);
static int __sdio_msg_send(void *p_drv,  struct am_sdio_message  *p_msg  , uint16_t len);
static int __sdio_msg_recv(void *p_drv,  struct am_sdio_message  *p_msg  , uint16_t len);

static int __sdio_mst_sm_event(am_zlg_sdio_dev_t *p_dev, uint32_t event);

/**
 * \brief SDIO ������������
 */
static am_const struct am_sdio_drv_funcs __g_sdio_drv_funcs = {
     __sdio_msg_send,
     __sdio_msg_recv,
     __sdio_send_cmd,
     __sdio_msg_start
};

/**
 * \brief ���һ�� message �������������б�ĩβ
 *
 * \attention ���ô˺�����������������
 */
//am_static_inline
//void __sdio_msg_in (am_zlg_sdio_dev_t *p_dev, struct am_sdio_message *p_msg)
//{
//    am_list_add_tail((struct am_list_head *)(&p_msg->ctlrdata),
//                    &(p_dev->msg_list));
//}

///**
// * \brief �ӿ����������б��ͷȡ��һ�� message
// *
// * \attention ���ô˺�����������������
// */
//am_static_inline
//struct am_sdio_message *__sdio_msg_out (am_zlg_sdio_dev_t *p_dev)
//{
//    if (am_list_empty_careful(&(p_dev->msg_list))) {
//        return NULL;
//    } else {
//        struct am_list_head *p_node = p_dev->msg_list.next;
//        am_list_del(p_node);
//        return am_list_entry(p_node, struct am_sdio_message, ctlrdata);
//    }
//}


//static uint32_t  f_hclk = 6000000;

/** \brief SDIO �жϴ����� */
static void __sdio_irq_handler (void *p_arg)
{
    am_zlg_sdio_dev_t *p_dev     = (am_zlg_sdio_dev_t *)p_arg;
    amhw_zlg_sdio_t   *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;
    uint16_t           status    = 0;

    amhw_zlg_sdio_get_int_status( p_hw_sdio, &status);

    if (ZMF159_SDIO_INT_CMD_COMPLE & status) {
        if (p_dev->int_status == ZMF159_SDIO_INT_CMD_COMPLE) {
            p_dev->int_status = 0;
            am_wait_done(&p_dev->wait);
        }
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_CMD_COMPLE);
    }

    if (ZMF159_SDIO_INT_DAT_COMPLE & status) {
        if (p_dev->int_status == ZMF159_SDIO_INT_DAT_COMPLE) {
            p_dev->int_status = 0;
            am_wait_done(&p_dev->wait);
        }
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_DAT_COMPLE);
    }

    if (ZMF159_SDIO_INT_DAT_ERR & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_DAT_ERR);
    }

    if (ZMF159_SDIO_INT_CMD_ERR & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_CMD_ERR);
    }

    if (ZMF159_SDIO_INT_MB_COMPLE & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_MB_COMPLE);
    }

    if (ZMF159_SDIO_INT_MB_TIMEOUT & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_MB_TIMEOUT);
    }

    if (ZMF159_SDIO_INT_CR_TIMEOUT & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_CR_TIMEOUT);
    }

    if (ZMF159_SDIO_INT_CRC & status) {
        am_wait_done(&p_dev->wait);
        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_CRC);
    }
}

static int __sdio_hard_init (am_zlg_sdio_dev_t *p_dev)
{
    uint8_t  card_clkdiv = 0;

    amhw_zlg_sdio_t  *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;

    /* ʹ��CRC���� */
    amhw_zlg_sdio_set_cardctrl_enable(p_hw_sdio, AM_TRUE);

    /* ʹ��clkʱ�� */
    amhw_zlg_sdio_set_cardclk_enable(p_hw_sdio, AM_TRUE);

    /* ���÷�Ƶֵ */
    card_clkdiv = ( am_clk_rate_get (CLK_PLLOUT)/(p_dev->p_devinfo->speed * 2)) - 1;

    amhw_zlg_sdio_set_cardclk_div (p_hw_sdio, card_clkdiv);

    /* ���ô����ٶȺ�ʱ�ӻ���ʱ�ӷ�Ƶ  */
    if(p_dev->p_devinfo->speed_mode == AMHW_ZLG_SDIO_SPEED_MODE_HIGH) {
        amhw_zlg_sdio_speed_mode_set (p_hw_sdio, AMHW_ZLG_SDIO_SPEED_MODE_HIGH);
    } else {
        amhw_zlg_sdio_speed_mode_set (p_hw_sdio, AMHW_ZLG_SDIO_SPEED_MODE_LOW);
    }
    amhw_zlg_sdio_prot_clk_set (p_hw_sdio, AMHW_ZLG_ADIO_PORT_CLK_MODE_1_2BASECLK);

    /*ʹ��CRC */
    amhw_zlg_sdio_set_crcctl_enable(p_hw_sdio, ZMF159_SDIO_CMDCRC | ZMF159_SDIO_DATCRC);

    amhw_zlg_sdio_bus_width_set(p_hw_sdio, p_dev->p_devinfo->width);

    amhw_zlg_sdio_speed_mode_set ( p_hw_sdio, p_dev->p_devinfo->speed_mode);

    amhw_zlg_sdio_prot_clk_set (p_hw_sdio, 0);

    amhw_zlg_sdio_output_mode_set (p_hw_sdio, AMHW_ZLG_SDIO_OUTPUT_SELECTION_PP_MODE);

    amhw_zlg_sdio_signal_mode_set (p_hw_sdio, AMHW_ZLG_SDIO_SIGNAL_AUTO_MODE);

    amhw_zlg_sdio_port_operation_set(p_hw_sdio, AMHW_ZLG_SDIO_PORT_OPER_SDIO_MODE);

    amhw_zlg_sdio_set_int_enable (p_hw_sdio, ZMF159_SDIO_INT_CMD_COMPLE |
                                             ZMF159_SDIO_INT_DAT_COMPLE);

//    amhw_zlg_sdio_out_8nullclk(p_hw_sdio);

//    amhw_zlg_sdio_autotr_enable(p_hw_sdio);

    return AM_OK;
}

/** \brief SDIO ����ͺ��� */
static int __sdio_send_cmd (void *p_drv, am_sdio_cmd_t *cmd_msg)
{
    int                ret;
    am_zlg_sdio_dev_t *p_dev     = (am_zlg_sdio_dev_t *)p_drv;
    amhw_zlg_sdio_t   *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;

    amhw_zlg_sdio_write_cmd(p_hw_sdio, 4, 0x40 | cmd_msg->cmd);
    amhw_zlg_sdio_write_cmd(p_hw_sdio, 3, ((cmd_msg->arg & 0xff000000) >> 24));
    amhw_zlg_sdio_write_cmd(p_hw_sdio, 2, ((cmd_msg->arg & 0xff0000) >> 16));
    amhw_zlg_sdio_write_cmd(p_hw_sdio, 1, ((cmd_msg->arg & 0xff00) >> 8));
    amhw_zlg_sdio_write_cmd(p_hw_sdio, 0, (cmd_msg->arg & 0xff));

    amhw_zlg_sdio_autotr_enable(p_hw_sdio, 1);

    p_dev->int_status = ZMF159_SDIO_INT_CMD_COMPLE;
    if ((ret = am_wait_on_timeout(&p_dev->wait, 500)) != AM_OK) {
        return ret;
    }
//    while(1) {
//        if(p_hw_sdio->clr_mmc_int & 0x1) {                                          //judge which interrupt generation
//            p_hw_sdio->clr_mmc_int = 0x1;                                           //write 1 clear interrup
//            break;
//        }
//    }

    if (cmd_msg->rsp_type == SDIO_RESPONSE_SHORT) {

        amhw_zlg_sdio_pclkg_set(p_hw_sdio, AMHW_ZLG_SDIO_RESIVE_MODE);
        amhw_zlg_sdio_autotr_enable(p_hw_sdio, 1);

        p_dev->int_status = ZMF159_SDIO_INT_CMD_COMPLE;
        if ((ret = am_wait_on_timeout(&p_dev->wait, 500)) != AM_OK) {
            return ret;
        }
//        while(1) {
//            if(p_hw_sdio->clr_mmc_int & 0x1) {                            //judge which interrupt generation
//                p_hw_sdio->clr_mmc_int = 0x1;                                           //write 1 clear interrup
//                break;
//            }
//        }

        amhw_zlg_sdio_pclkg_set(p_hw_sdio, AMHW_ZLG_SDIO_SEND_MODE);
        cmd_msg->p_rsp[0] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 3) << 24  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 2) << 16  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 1) << 8   |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 0);
        cmd_msg->p_rsp[1] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 4);

    } else if (cmd_msg->rsp_type == SDIO_RESPONSE_LONG) {

        amhw_zlg_sdio_get_cid_csd(p_hw_sdio);
        amhw_zlg_sdio_pclkg_set(p_hw_sdio, AMHW_ZLG_SDIO_RESIVE_MODE);
        amhw_zlg_sdio_autotr_enable(p_hw_sdio, 1);

        p_dev->int_status = ZMF159_SDIO_INT_CMD_COMPLE;
        if ((ret = am_wait_on_timeout(&p_dev->wait, 500)) != AM_OK) {
            return ret;
        }
//        while(1) {
//            if(p_hw_sdio->clr_mmc_int & 0x1) {                               //judge which interrupt generation
//                p_hw_sdio->clr_mmc_int = 0x1;                                //write 1 clear interrup
//                break;
//            }
//        }

        p_hw_sdio->mmc_io &= ~(1 << 4);
        amhw_zlg_sdio_pclkg_set(p_hw_sdio, AMHW_ZLG_SDIO_SEND_MODE);
        cmd_msg->p_rsp[0] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 3) << 24  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 2) << 16  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 1) << 8   |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 0);
        cmd_msg->p_rsp[1] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 7) << 24  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 6) << 16  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 5) << 8   |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 4);
        cmd_msg->p_rsp[2] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 11) << 24  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 10) << 16  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 9)  << 8   |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 8);
        cmd_msg->p_rsp[3] =  amhw_zlg_sdio_read_cmd(p_hw_sdio, 15) << 24  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 14) << 16  |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 13) << 8   |
                             amhw_zlg_sdio_read_cmd(p_hw_sdio, 12);
    }

    return AM_OK;
}

static int __sdio_msg_recv(void *p_drv, struct am_sdio_message  *p_msg, uint16_t len)
{
    int                i         = 0;
    uint32_t           data      = 0;
    uint8_t           *p_buf     = p_msg->p_data;
    am_zlg_sdio_dev_t *p_dev     = (am_zlg_sdio_dev_t *)p_drv;
    amhw_zlg_sdio_t   *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;
    uint8_t n;

    p_hw_sdio->mmc_io |= 0x02;

    while(1) {                                   //wait FIFO full interrupt
        n = 100;
        while(n--);
        if((p_hw_sdio->buf_ctll & 0x1)) {                //judge which interrupt generation
            break;
        }
    }
    p_hw_sdio->buf_ctll = 0x000;

    for (i = 0; i < len ;) {
        if(p_hw_sdio->buf_ctll & 0x2) {
            break;
        }
        data =  p_hw_sdio->data_buf[0];
       *p_buf++ = data;
       *p_buf++ = data >> 8;
       *p_buf++ = data >> 16;
       *p_buf++ = data >> 24;
        i += 4;
    }
    return i;
}

static int __sdio_msg_send(void *p_drv, struct am_sdio_message  *p_msg, uint16_t len)
{
    am_zlg_sdio_dev_t *p_dev     = (am_zlg_sdio_dev_t *)p_drv;
    amhw_zlg_sdio_t   *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;
    int i = 0;
    uint32_t          *p_data    = (uint32_t *)p_msg->p_data;

    for (i = 0; i < 128; i++) {
        p_hw_sdio->data_buf[0] = *p_data++;
    }

    p_dev->int_status = ZMF159_SDIO_INT_DAT_COMPLE;
    return am_wait_on_timeout(&p_dev->wait, 500);

}

/*  ״̬���ڲ�״̬�л� */
#define __SDIO_NEXT_STATE(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

//__sdio_mst_sm_event(am_zlg_sdio_dev_t *p_dev, uint32_t event)
//{
//
//    volatile uint32_t  new_event = __SDIO_EVT_NONE;
//    amhw_zlg_sdio_t *p_hw_sdio  = NULL;
//
//    if (p_dev == NULL) {
//        return -AM_EINVAL;
//    }
//
//    p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;
//
//    while(1) {
//
//        /* ����Ƿ����µ��¼���״̬���ڲ����� */
//        if (new_event != __SDIO_EVT_NONE) {
//            event      = new_event;
//            new_event  = __SDIO_EVT_NONE;
//        }
//
//        /* ���豸��״̬Ϊ��׼����״̬������ */
//        switch (p_dev->state) {
//            case __SDIO_ST_IDLE:
//            case __SDIO_ST_MSG_START:
//            {
//                am_sdio_message_t *p_cur_msg = NULL;
//
//                int key;
//
//                key = am_int_cpu_lock();
//                p_cur_msg        = __sdio_msg_out(p_dev);
//                p_dev->p_cur_msg = p_cur_msg;
//
//                if (p_cur_msg) {
//
//                    p_cur_msg->status = -AM_EINPROGRESS;
//
//                } else {
//
//                    /* �ر��ж� */
////                    amhw_zlg_i2c_intr_mask_clear (p_hw_sdio, 0xfff);
//
//                    p_dev->busy = AM_FALSE;
//                }
//
//                am_int_cpu_unlock(key);
//
//                /* ����Ҫ�������Ϣ */
//                if (p_cur_msg == NULL) {
//
//                    __SDIO_NEXT_STATE(__SDIO_ST_IDLE, __SDIO_EVT_NONE);
//
//                    break;
//                } else {
//
//                    p_cur_msg->done_num = 0;
//                    p_dev->p_cur_trans  = p_cur_msg->p_transfers;
//                    p_dev->data_ptr     = 0;
//
//                    __SDIO_NEXT_STATE(__SDIO_ST_TRANS_START,
//                                        __SDIO_EVT_TRANS_LAUNCH);
//
//                    /* ֱ�ӽ�����һ��״̬����ʼһ�����䣬�˴�����break */
//                    event     = new_event;
//                    new_event = __SDIO_EVT_NONE;
//                }
//            }
//                /* no break */
//
//            case __SDIO_ST_TRANS_START:
//            {
//                struct am_sdio_message *p_cur_msg = p_dev->p_cur_msg;
//                if (NULL == p_cur_msg) {
////                    __sdio_re_init(p_dev);
//                    return -AM_EINVAL;
//                }
//
//                /* ��ǰ��Ϣ������� */
//                if (__SDIO_TRANS_EMPTY(p_dev)) {
//
//                    /* ��Ϣ���ڴ����� */
//                    if (p_cur_msg->status == -AM_EINPROGRESS) {
//                        p_cur_msg->status = AM_OK;
//                    }
//
//                    p_dev->is_complete = AM_TRUE;
//                    //amhw_zlg_i2c_con_set(p_hw_sdio, 1 << 9); /* ����һ��ֹͣ�ź� */
//                    __SDIO_NEXT_STATE(__SDIO_ST_IDLE,
//                                     __SDIO_EVT_NONE);
//                } else {                    /* ��ȡ��һ�����䣬��ȷ����ô��伴�� */
//
//                        /* ������������ */
//                        __SDIO_NEXT_STATE(__SDIO_ST_SEND_CMD,
//                                         __SDIO_EVT_NONE);
//
////                    struct am_sdio_transfer *p_cur_trans = p_dev->p_cur_trans;
////
////                    if (NULL == p_cur_trans && ) {
//////                        __softimer_stop(p_dev);
//////                        __i2c_re_init(p_dev);
////
////                        return -AM_EINVAL;
////                    }
////
////                    p_dev->data_ptr = 0;
//
//
////                    am_bool_t is_read = (p_cur_trans->opt & AM_SDIO_M_RD) ?
////                                     AM_TRUE : AM_FALSE;
////
////
////                    if (is_read == AM_TRUE) {
////
////                        /* ������������ */
////                        __SDIO_NEXT_STATE(__SDIO_ST_M_RECV_DATA,
////                                         __SDIO_EVT_NONE);
////
//////                        amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
//////                                                  AMHW_ZLG_INT_FLAG_RX_FULL);
////                    } else {
////
////                        /* ������������ */
////                        __SDIO_NEXT_STATE(__SDIO_ST_M_SEND_DATA,
////                                         __SDIO_EVT_NONE);
//////                        amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
//////                                                   AMHW_ZLG_INT_FLAG_TX_EMPTY);
////                    }
//
//
//                    /*
//                     * ����Ҫ�����źţ�ֱ�Ӵ��䣬����ͬʱ������������������
//                     * 1.�����˱�־ AM_SDIO_M_NOSTART
//                     * 2.��ǰ���䲻��һ����Ϣ�еĵ�һ������
//                     * 3.��ǰ��������һ������ķ���һ��
//                     */
////                    if ((p_cur_trans->flags & AM_SDIO_M_NOSTART) &&
////                        (p_cur_trans != p_cur_msg->p_transfers) &&
////                        ((p_cur_trans->flags & AM_SDIO_M_RD) ==
////                        ((p_cur_trans - 1)->flags & AM_SDIO_M_RD))) {
////
////                        am_bool_t is_read = (p_cur_trans->flags & AM_SDIO_M_RD) ?
////                                         AM_TRUE : AM_FALSE;
////
////                        p_dev->trans_state = 1;
////                        if (is_read == AM_TRUE) {
////
////                            /* ������������ */
////                            __SDIO_NEXT_STATE(__SDIO_ST_M_RECV_DATA,
////                                             __SDIO_EVT_NONE);
////
////                            amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
////                                                      AMHW_ZLG_INT_FLAG_RX_FULL);
////                        } else {
////
////                            /* ������������ */
////                            __SDIO_NEXT_STATE(__SDIO_ST_M_SEND_DATA,
////                                             __SDIO_EVT_NONE);
////                            amhw_zlg_i2c_intr_mask_set(p_hw_i2c,
////                                                       AMHW_ZLG_INT_FLAG_TX_EMPTY);
////                        }
////
////                    /* ���ʹӻ���ַ */
////                    } else {
////                        p_dev->trans_state = 0;
////
////                        /* ��һ�������Ƿ��ʹӻ���ַ */
////                        __SDIO_NEXT_STATE(__SDIO_ST_SEND_SLA_ADDR,
////                                         __SDIO_EVT_MST_IDLE);
////                    }
////                }
//
//                }
//            }
//
//            case __SDIO_ST_SEND_CMD:
//            {
//                struct am_sdio_message  *p_cur_msg   = p_dev->p_cur_msg;
//                //struct am_sdio_transfer *p_cur_trans = p_dev->p_cur_trans;
//
//                if (NULL == p_cur_msg) {
////                    __sdio_re_init(p_dev);
//                    return -AM_EINVAL;
//                }
//
//                /** \brief SDIO �жϴ����� */
//                __sdio_send_cmd (p_dev, p_cur_msg->p_transfers->p_cmd);
//
//                break;
//            }
//            case __SDIO_ST_M_SEND_DATA:
//
//                break;
//            case __SDIO_ST_M_RECV_DATA:
//
//                break;
//            default:
//                break;
//        }
//
//            if (p_dev->is_abort != AM_FALSE) {
//                p_dev->is_abort = AM_FALSE;
//                return -AM_EINVAL;
//            }
//
//            /* �ڲ�û�����¼����������� */
//            if (new_event == __SDIO_EVT_NONE) {
//                break;
//            }
//    }
//
//    p_dev->busy   = AM_FALSE;
//    return AM_OK;
//}


static int __sdio_msg_start (void *p_drv)
{
    am_zlg_sdio_dev_t *p_dev    = (am_zlg_sdio_dev_t *)p_drv;
    amhw_zlg_sdio_t   *p_hw_sdio = (amhw_zlg_sdio_t *)p_dev->p_devinfo->regbase;

 //   amhw_zlg_sdio_autotr_enable(p_hw_sdio);

//    amhw_zlg_sdio_transfdir_set(p_hw_sdio, AMHW_ZLG_SDIO_READ_MODE);
//
//    amhw_zlg_sdio_autodattr_enable(p_hw_sdio);

    p_hw_sdio->mmc_io          = 0x2;
    //SDIO1->BUF_CTL |= 0x20 << 2;
    p_hw_sdio->mmc_io          |= 0x1;

//    int key;
//
//    if ( (p_dev              == NULL)   ||
//         (p_trans              == NULL) ||
//         (p_trans->p_transfers == NULL) ||
//         ((p_trans->trans_num   == 0)   &&
//         (p_trans->p_transfers == NULL))) {
//
//        return -AM_EINVAL;
//    }
//
//    key = am_int_cpu_lock();
//    __sdio_msg_in(p_dev, p_trans);
//    /* ��ǰ���ڴ�����Ϣ��ֻ��Ҫ���µ���Ϣ���������� */
//    if (p_dev->busy == AM_TRUE) {
//
//        __sdio_msg_in(p_dev, p_trans);
//
//        am_int_cpu_unlock(key);
//
//        return AM_OK;
//
//    } else {
//        p_dev->busy = AM_TRUE;
//        __sdio_msg_in(p_dev, p_trans);
//        p_trans->status = -AM_EISCONN; /* �����Ŷ��� */
//        am_int_cpu_unlock(key);
//
//        /* ��������ж� */
//        amhw_zlg_sdio_clr_int_status(p_hw_sdio, ZMF159_SDIO_INT_ALL);
//
//        return __sdio_mst_sm_event(p_dev, __SDIO_EVT_MSG_LAUNCH);
//    }
}


am_sdio_handle_t am_zmf159_sdio_init (am_zlg_sdio_dev_t           *p_dev,
                                     const am_zlg_sdio_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }

    p_dev->sdio_serv.p_funcs = (struct am_sdio_drv_funcs *)&__g_sdio_drv_funcs;
    p_dev->sdio_serv.p_drv   = p_dev;

//    p_dev->p_cur_trans       = NULL;
    p_dev->p_cur_msg         = NULL;
    p_dev->p_devinfo         = p_devinfo;
    p_dev->sdio_serv.p_drv   = p_dev;
    p_dev->is_complete       = AM_FALSE;
    p_dev->data_ptr          = 0;
    p_dev->state             = __SDIO_ST_IDLE;
    p_dev->busy              = AM_FALSE;
    p_dev->is_abort          = AM_FALSE;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    am_list_head_init(&(p_dev->msg_list));

    am_wait_init(&p_dev->wait);

    __sdio_hard_init (p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __sdio_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->sdio_serv);
}

/* end of file */
