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
 * \brief SDIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.01 15-08-17  tee, modified some interface.
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_SDIO_H
#define __AM_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "string.h"
#include "am_list.h"

/**
 * \addtogroup am_if_sdio
 * \copydoc am_sdio.h
 * @{
 */

/**
 * \name SD ����
 * @{
 */
#define AM_SDIO_CMD0               0
#define AM_SDIO_CMD1               1
#define AM_SDIO_CMD2               2
#define AM_SDIO_CMD3               3
#define AM_SDIO_CMD4               4
#define AM_SDIO_CMD5               5
#define AM_SDIO_CMD6               6
#define AM_SDIO_CMD7               7
#define AM_SDIO_CMD8               8
#define AM_SDIO_CMD9               9
#define AM_SDIO_CMD10              10
#define AM_SDIO_CMD11              11
#define AM_SDIO_CMD12              12
#define AM_SDIO_CMD13              13
#define AM_SDIO_CMD14              14
#define AM_SDIO_CMD15              15
#define AM_SDIO_CMD16              16
#define AM_SDIO_CMD17              17
#define AM_SDIO_CMD18              18
#define AM_SDIO_CMD19              19
#define AM_SDIO_CMD20              20
#define AM_SDIO_CMD21              21
#define AM_SDIO_CMD22              22
#define AM_SDIO_CMD23              23
#define AM_SDIO_CMD24              24
#define AM_SDIO_CMD25              25
#define AM_SDIO_CMD26              26
#define AM_SDIO_CMD27              27
#define AM_SDIO_CMD28              28
#define AM_SDIO_CMD29              29
#define AM_SDIO_CMD31              31
#define AM_SDIO_CMD32              32
#define AM_SDIO_CMD33              33
#define AM_SDIO_CMD34              34
#define AM_SDIO_CMD35              35
#define AM_SDIO_CMD36              36
#define AM_SDIO_CMD37              37
#define AM_SDIO_CMD38              38
#define AM_SDIO_CMD39              39
#define AM_SDIO_CMD40              40
#define AM_SDIO_CMD41              41
#define AM_SDIO_CMD42              42
#define AM_SDIO_CMD43              43
#define AM_SDIO_CMD44              44
#define AM_SDIO_CMD45              45
#define AM_SDIO_CMD46              46
#define AM_SDIO_CMD47              47
#define AM_SDIO_CMD48              48
#define AM_SDIO_CMD49              49
#define AM_SDIO_CMD50              50
#define AM_SDIO_CMD51              51
#define AM_SDIO_CMD52              52
#define AM_SDIO_CMD53              53
#define AM_SDIO_CMD54              54
#define AM_SDIO_CMD55              55
#define AM_SDIO_CMD56              56
#define AM_SDIO_CMD57              57
#define AM_SDIO_CMD57              57
#define AM_SDIO_CMD58              58
#define AM_SDIO_CMD59              59

#define AM_SDIO_ACMD6              6
#define AM_SDIO_ACMD13             13
#define AM_SDIO_ACMD14             14
#define AM_SDIO_ACMD15             15
#define AM_SDIO_ACMD16             16
#define AM_SDIO_ACMD22             22
#define AM_SDIO_ACMD23             23
#define AM_SDIO_ACMD28             28
#define AM_SDIO_ACMD41             41
#define AM_SDIO_ACMD42             42
#define AM_SDIO_ACMD51             51
/** @} */

#define AM_SD_VOLTAGE_WINDOW_SD            ((uint32_t)0x80100000)
#define AM_SD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define AM_SD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define AM_SD_CHECK_PATTERN                ((uint32_t)0x000001AA)

#define AM_SDIO_M_WR            0x0000u    /**< \brief д����           */
#define AM_SDIO_M_RD            0x0002u    /**< \brief ������           */
//#define AM_SDIO_M_NOSTART       0x0004u    /**< \brief ������������     */
//#define AM_SDIO_M_REV_DIR_ADDR  0x0008u    /**< \brief ��д��־λ��ת   */
//#define AM_SDIO_M_RECV_LEN      0x0010u    /**< \brief �ݲ�֧��         */

/**
 * \name card status of R1 on SPI mode
 * \anchor grp_awbl_spi_r1_state
 * @{
 */

/** \brief ָʾ���Ƿ��ڿ���״̬ */
#define AM_SDIO_SPI_R1_IN_IDLE_STATE       0x01

/** \brief ��������λ */
#define AM_SDIO_SPI_R1_ERASE_RESET         0x02

/** \brief ���ڵ�ǰ��״̬Ϊ�Ƿ�����  */
#define AM_SDIO_SPI_R1_ILLEGAL_CMD         0x04

/** \brief CRCУ��ʧ�� */
#define AM_SDIO_SPI_R1_COM_CRC_ERROR       0x08

/** \brief �������� */
#define AM_SDIO_SPI_R1_ERASE_SEQ_ERROR     0x10

/** \brief ��ַ���󣬷Ƕ�������ݳ��Ȳ�ƥ�� */
#define AM_SDIO_SPI_R1_ADDRESS_ERROR       0x20

/** \brief ����������������β��Ϸ�  */
#define AM_SDIO_SPI_R1_PARA_ERROR          0x40
#define AM_SDIO_SPI_R1_ALL_ERROR           0x7E
#define AM_SDIO_SPI_R1_MASK                0x7F
/** @} */

/** \brief SDIO���߿�� */
typedef enum am_sdio_bus_width {
    AM_SDIO_BUS_WIDTH_1B  = 1, /**< \brief 1λ������ */
    AM_SDIO_BUS_WIDTH_4B  = 2, /**< \brief 4λ������ */
    AM_SDIO_BUS_WIDTH_8B  = 3, /**< \brief 8λ������ */
} am_sdio_bus_width_t;

/** \brief command */
typedef struct am_sdio_trans{

    struct am_list_head  trans_node;

    uint32_t             cmd;        /**< \brief SDIO ����*/
    uint32_t             arg;        /**< \brief ������� */
    uint8_t              opt;        /**< \brief ������� */
#define AM_SDIO_OW       0           /**< \brief ֻд */
#define AM_SDIO_WR       1           /**< \brief ��д��� */

    void                *p_data;     /**< \brief ���ݻ����� */
    uint32_t             blk_size;   /**< \brief ������С */
    uint32_t             nblock;     /**< \brief ��������� */
    uint8_t              rsp_type;   /**< \brief ������Ӧ���� */
#define AM_SDIO_RSP_NONE      0
#define AM_SDIO_RSP_R1        1
#define AM_SDIO_RSP_R1B       2
#define AM_SDIO_RSP_R2        3
#define AM_SDIO_RSP_R3        4
#define AM_SDIO_RSP_R4        5
#define AM_SDIO_RSP_R5        6
#define AM_SDIO_RSP_R6        7
#define AM_SDIO_RSP_R7        8

    uint32_t            *p_rsp;      /**< \brief ��Ӧ���� */
    uint8_t              retries;    /**< \brief ��ʱ�ط����� */
} am_sdio_trans_t;

/** \brief message */
typedef struct am_sdio_msg {
    struct am_list_head  msg_node;
    struct am_list_head  trans_list;
    int                  status;            /**< \brief ���״̬  */
    void                *p_arg;             /**< \brief �ص��������� */
    void (*pfn_complete) (void *p_arg);     /**< \brief ������ɻص�����*/
} am_sdio_msg_t;

/**
 * \brief sdio���������ṹ��
 */
struct am_sdio_drv_funcs {

    /** \brief ����SDIO��Ϣ���䣬��ɺ���ûص�����  */
    int (*pfn_sdio_msg_start)(void                  *p_drv,
                              struct am_sdio_msg    *p_msg);
};

/**
 * \brief SDIO ��׼����ṹ��
 */
typedef struct am_sdio_serv {
    struct am_sdio_drv_funcs   *p_funcs;    /**< \brief SDIO  sdio��������     */
    void                       *p_drv;      /**< \brief SDIO  sdio������������ */
} am_sdio_serv_t;

/** \brief SDIO ��׼�������������� */
typedef am_sdio_serv_t *am_sdio_handle_t;

/**< \brief ��Ӧ���� */
#define AM_SDIO_RESPONSE_NO                    0
#define AM_SDIO_RESPONSE_SHORT                 1
#define AM_SDIO_RESPONSE_LONG                  2

/**
 * \brief SDIO ���������ṹ��
 */
typedef struct am_sdio_cmd {
    uint32_t             cmd;        /**< \brief SDIO ����*/
    uint32_t             arg;        /**< \brief ������� */
    uint8_t              rsp_type;   /**< \brief ��Ӧ���� */
    uint32_t             p_rsp[4];   /**< \brief ��Ӧ���� */
} am_sdio_cmd_t;

/** \brief SDIO timeout obj */
typedef struct am_sdio_timeout_obj {
    am_tick_t   ticks;
    am_tick_t   timeout;
} am_sdio_timeout_obj_t;

am_static_inline
void am_adio_timeout_set (am_sdio_timeout_obj_t *p_t,
                          uint32_t              ms)
{
    p_t->timeout = am_ms_to_ticks(ms);
    p_t->ticks   = am_sys_tick_get();
}

/**
 * \brief check if timeout
 * \param[in] t     timeout obj
 */
am_static_inline
am_bool_t am_sdio_timeout (am_sdio_timeout_obj_t *p_t)
{
    return ((am_sys_tick_diff(p_t->ticks, am_sys_tick_get())) >= p_t->timeout);
}

/**
 * \brief SDIO��������ṹ����Ϣ��������
 *
 * \param[in] p_cmd : ָ���������ṹ��ָ��
 * \param[in] cmd   : SDIO ����
 * \param[in] arg   : �������
 *
 * \retval  AM_OK     : ����ṹ������������
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
void am_sdio_mkcmd (am_sdio_cmd_t *p_cmd,
                    uint32_t       cmd,
                    uint32_t       arg,
                    uint8_t        rsp_type)
{
    p_cmd->cmd = cmd;
    p_cmd->arg = arg;
    p_cmd->rsp_type = rsp_type;
    p_cmd->p_rsp[0] = 0;
    p_cmd->p_rsp[1] = 0;
    p_cmd->p_rsp[2] = 0;
    p_cmd->p_rsp[3] = 0;
}

/**
 * \brief SDIO��������ṹ����Ϣ��������
 *
 * \param[in] p_trans : ָ����ṹ��ָ��
 * \param[in] cmd       CMD ����
 * \param[in] cmd_arg   �������
 * \param[in] opt       ���䷽ʽ
 * \param[in] p_data    �������ݻ���
 * \param[in] blk_size  ������С
 * \param[in] nblk      ���������
 * \param[in] rsp_type  ��Ӧ����
 * \param[in] rsp_type  ��Ӧ���ݻ���
 * \param[in] retries   ��ʱ�ط�����
 *
 * \retval  AM_OK     : ����ṹ������������
 * \retval -AM_EINVAL : ��������
 */
am_static_inline
void am_sdio_mktrans (am_sdio_trans_t *p_trans,
                      uint8_t          cmd,
                      uint32_t         cmd_arg,
                      uint8_t          opt,
                      void            *p_data,
                      uint32_t         blk_size,
                      uint32_t         nblk,
                      uint8_t          rsp_type,
                      void            *p_rsp,
                      uint8_t          retries)
{
    p_trans->cmd      = cmd;
    p_trans->arg      = cmd_arg;
    p_trans->opt      = opt;
    p_trans->p_data   = p_data;
    p_trans->blk_size = blk_size;
    p_trans->nblock   = nblk;
    p_trans->rsp_type = rsp_type;
    p_trans->p_rsp    = p_rsp;
    p_trans->retries  = retries;
}

am_static_inline
void am_sdio_msg_init (am_sdio_msg_t *p_msg)
{
    memset(p_msg, 0, sizeof(*p_msg));

    AM_INIT_LIST_HEAD(&(p_msg->trans_list));

    p_msg->status = -AM_ENOTCONN;
}

/**
 * \brief ��������ӵ���Ϣĩβ
 * \param p_msg     message object
 * \param p_cmd     command to be added
 */
am_static_inline
void am_sdio_trans_add_tail (am_sdio_msg_t   *p_msg,
                             am_sdio_trans_t *p_trans)
{
    am_list_add_tail(&p_trans->trans_node, &p_msg->trans_list);
}

/**
 * \brief ���������Ϣ��ɾ��
 * \param[in] p_trans : ������ɾ���Ĵ���
 * \return ��
 * \note ɾ��ǰ�����ȷ���ô���ȷʵ�Ѿ���������Ϣ��
 */
am_static_inline
void am_sdio_trans_del (am_sdio_trans_t *p_trans)
{
    am_list_del(&p_trans->trans_node);
}

/**
 * \brief ��message�б��ͷȡ��һ�� transfer
 * \attention ���ô˺�����������������
 *
 * \retval  p_msg
 */
am_static_inline
am_sdio_trans_t *am_sdio_msg_out (am_sdio_msg_t *p_msg)
{
    am_sdio_trans_t *p_trans = NULL;

    if (!(am_list_empty(&p_msg->trans_list))) {
        p_trans = am_list_entry(p_msg->trans_list.next,
                                am_sdio_trans_t,
                                trans_node);
        am_list_del(p_msg->trans_list.next);
    }

    return p_trans;
}

/**
 * \brief ��ʼ����һ����Ϣ
 *
 *     ���첽�ķ�ʽ������Ϣ������ǰSDIO���������У������Ϣ��õ�����ִ�У�
 * �������������У���Ὣ����Ϣ����һ���������Ŷӵȴ���SDIO��������˳����
 * �����е���Ϣ����Ϣ�Ĵ���״̬�ͽ����ӳ��\a p_msg->status��
 * ��Ϣ�������(�ɹ�����ʱ�����)ʱ���������\a p_msg->pfn_complete ������
 * ����\a p_msg->p_arg��
 *
 * \param[in]     handle : SDIO��׼����������
 * \param[in,out] p_msg  : Ҫ�������Ϣ
 *
 * \retval  AM_OK     : �����������д���
 * \retval -AM_EINVAL : �����������
 *  ��������Լ����״̬��ͨ������ص�������ȡ״̬λ
 *    \li  AM_OK  : �������
 *    \li -AM_EIO : �������
 */
am_static_inline
int am_sdio_msg_start (am_sdio_handle_t  handle,
                       am_sdio_msg_t    *p_msg)
{
    return handle->p_funcs->pfn_sdio_msg_start(handle->p_drv,
                                               p_msg);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDIO_H */

/*end of file */
