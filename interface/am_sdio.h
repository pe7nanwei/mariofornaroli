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
 * - 1.00 19-06-12  ipk, first implementation.
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
 * \name SDIO ����
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

/**
 * \name SD mode R1 response
 * \anchor grp_awbl_sd_r1_rsp
 * @{
 */

/** \brief command argument out of range */
#define AM_SDIO_R1_OUT_OF_RANGE          (1 << 31)

/** \brief address error */
#define AM_SDIO_R1_ADDRESS_ERROR         (1 << 30)

/** \brief not support block length or transmit mismatch to the block length */
#define AM_SDIO_R1_BLOCK_LEN_ERROR       (1 << 29)

/** \brief erase sequence error */
#define AM_SDIO_R1_ERASE_SEQ_ERROR       (1 << 28)

/** \brief the block write or erase is invalid */
#define AM_SDIO_R1_ERASE_PARAM           (1 << 27)

/** \brief the block write is protected */
#define AM_SDIO_R1_WP_VIOLATION          (1 << 26)

/** \brief indicate whether the card is locked */
#define AM_SDIO_R1_CARD_IS_LOCKED        (1 << 25)

/** \brief indicate in the lock/unlock command��password verify error */
#define AM_SDIO_R1_LOCK_UNLOCK_FAILED    (1 << 24)

/** \brief CRC error */
#define AM_SDIO_R1_COM_CRC_ERROR         (1 << 23)

/** \brief ECC failed */
#define AM_SDIO_R1_CARD_ECC_FAILED       (1 << 21)

/** \brief card host error */
#define AM_SDIO_R1_CC_ERROR              (1 << 20)

/** \brief unknown error */
#define AM_SDIO_R1_ERROR                 (1 << 19)

#define AM_SDIO_R1_UNDERRUN              (1 << 18)
#define AM_SDIO_R1_OVERRUN               (1 << 17)

/** \brief CID/CSD overwrite */
#define AM_SDIO_R1_CID_CSD_OVERWRITE     (1 << 16)

/** \brief skip write protected area */
#define AM_SDIO_R1_WP_ERASE_SKIP         (1 << 15)

/** \brief indicate whether card ECC is forbid */
#define AM_SDIO_R1_CARD_ECC_DISABLED     (1 << 14)

#define AM_SDIO_R1_ERASE_RESET           (1 << 13)
#define AM_SDIO_R1_STATUS(x)             (x & 0xFFFFE000)

/** \brief current state */
#define AM_SDIO_R1_CURRENT_STATE(x)      ((x & 0x00001E00) >> 9)

/** \brief bus can transmit data */
#define AM_SDIO_R1_READY_FOR_DATA        (1 << 8)
#define AM_SDIO_R1_SWITCH_ERROR          (1 << 7)
#define AM_SDIO_R1_EXCEPTION_EVENT       (1 << 6)
/** \brief indicate whether the card into APP CMD mode */
#define AM_SDIO_R1_APP_CMD               (1 << 5)
#define AM_SDIO_R1_ALL_ERROR             0xF9F90000
/** @} */

/**
 * \name card status of R1 on SD mode
 * \anchor grp_awbl_sd_r1_state
 * @{
 */
#define AM_SDIO_R1_STATE_IDLE   0
#define AM_SDIO_R1_STATE_READY  1
#define AM_SDIO_R1_STATE_IDENT  2
#define AM_SDIO_R1_STATE_STBY   3
#define AM_SDIO_R1_STATE_TRAN   4
#define AM_SDIO_R1_STATE_DATA   5
#define AM_SDIO_R1_STATE_RCV    6
#define AM_SDIO_R1_STATE_PRG    7
#define AM_SDIO_R1_STATE_DIS    8
/** @} */

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

/**
 * \name SPIģʽ R2״̬
 * \anchor grp_awbl_spi_r2_state
 * @{
 */

/** \brief �������� */
#define AM_SDIO_SPI_R2_CARD_LOCKED         0x01

/** \brief ����д����,���� */
#define AM_SDIO_SPI_R2_WP_ERASE_SKIP       0x02

/** \brief LOCK��UNLOCK����ʧ�� */
#define AM_SDIO_SPI_R2_LOCK_UNLOCK_FAIL    0x02

/** \brief Ϊֹ���� */
#define AM_SDIO_SPI_R2_ERROR               0x04

/** \brief ���ڲ����������� */
#define AM_SDIO_SPI_R2_CC_ERROR            0x08

/** \brief ECC���� */
#define AM_SDIO_SPI_R2_CARD_ECC_ERROR      0x10

/** \brief ��д�������������д���� */
#define AM_SDIO_SPI_R2_WP_VIOLATION        0x20

/** \brief ����������Ч������Ч������� */
#define AM_SDIO_SPI_R2_ERASE_PARAM         0x40

/** \brief    */
#define AM_SDIO_SPI_R2_OUT_OF_RANGE        0x80
#define AM_SDIO_SPI_R2_CSD_OVERWRITE       0x80
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
#define AM_SDIO_OW           0       /**< \brief ֻд */
#define AM_SDIO_WR           1       /**< \brief ��д��� */

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

struct am_sdio_device;

/**
 * \brief sdio���������ṹ��
 */
struct am_sdio_drv_funcs {

    /** \brief ����SDIO�豸   */
    int (*pfn_sdio_setup) (void *p_drv, struct am_sdio_device *p_dev);

    /** \brief ����SDIO��Ϣ���䣬��ɺ���ûص�����  */
    int (*pfn_sdio_msg_start)(void                  *p_drv,
                              struct am_sdio_device *p_dev,
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

/** \brief SDIO host �豸  */
typedef struct am_sdio_device {
    am_sdio_handle_t        handle;

    uint8_t                 mode;           /**< \brief ����ģʽ  1��ģʽ 4��ģʽ SD 8��ģʽ*/
#define AM_SDIO_SPI_M               0       /**< \brief SDIO SPIģʽ */
#define AM_SDIO_SD_1B_M             1       /**< \brief SDIO SD 1��ģʽ */
#define AM_SDIO_SD_4B_M             2       /**< \brief SDIO SD 4��ģʽ */
#define AM_SDIO_SD_8B_M             3       /**< \brief SDIO SD 8��ģʽ */

    uint16_t                blk_size;       /**< \brief �������ݿ��С */

} am_sdio_device_t;

/**< \brief ��Ӧ���� */
#define AM_SDIO_RESPONSE_NO         0
#define AM_SDIO_RESPONSE_SHORT      1
#define AM_SDIO_RESPONSE_LONG       2

/** \brief SDIO timeout obj */
typedef struct am_sdio_timeout_obj {
    am_tick_t   ticks;
    am_tick_t   timeout;
} am_sdio_timeout_obj_t;

am_static_inline
void am_sdio_timeout_set (am_sdio_timeout_obj_t *p_t,
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

am_static_inline
void am_sdio_mkdev (am_sdio_device_t *p_dev,
                    am_sdio_handle_t  handle,
                    uint8_t           mode,
                    uint16_t          blk_size)
{
    p_dev->handle       = handle;
    p_dev->mode         = mode;
    p_dev->blk_size     = blk_size;
}

am_static_inline
int am_sdio_setup (am_sdio_device_t *p_dev)
{
    return p_dev->handle->p_funcs->pfn_sdio_setup(p_dev->handle->p_drv, p_dev);
}

/**
 * \brief ��ʼ����һ����Ϣ
 *
 *     ���첽��ͬ���ķ�ʽ������Ϣ������ǰSDIO���������У������Ϣ��õ�����ִ�У�
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
int am_sdio_msg_start (am_sdio_device_t *p_dev,
                       am_sdio_msg_t    *p_msg)
{
    return p_dev->handle->p_funcs->pfn_sdio_msg_start(p_dev->handle->p_drv,
                                                      p_dev,
                                                      p_msg);
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
void am_sdio_msg_init (am_sdio_msg_t *p_msg,
                       am_pfnvoid_t   pfn_complete,
                       void          *p_arg)
{
    memset(p_msg, 0, sizeof(*p_msg));

    AM_INIT_LIST_HEAD(&(p_msg->trans_list));

    p_msg->status        = -AM_ENOTCONN;
    p_msg->pfn_complete  = pfn_complete;
    p_msg->p_arg         = p_arg;
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
 * \brief SDIOд����
 *
 * \param[in]  p_dev        : SDIO�豸
 * \param[in]  cmd          : ��Ҫд�������
 * \param[in]  cmd_arg      : �������
 * \param[in]  rsp_type     : ��Ӧ����
 * \param[in]  p_rsp        : ��Ӧ���ݻ��棬����Ҫʱ�ɴ���NULL
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdio_cmd_write (am_sdio_device_t *p_dev,
                       uint8_t           cmd,
                       uint32_t          cmd_arg,
                       uint8_t           rsp_type,
                       uint32_t         *p_rsp);

/**
 * \brief SDIO���ݿ�д��
 *
 * \param[in]  p_dev        : SDIO�豸
 * \param[in]  p_buf        : ���ݻ�����
 * \param[in]  addr_start   : д�����ݵ���ʼ��ַ
 * \param[in]  blk          : ��Ҫд��Ŀ�����
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdio_blocks_write (am_sdio_device_t *p_dev,
                          uint8_t          *p_buf,
                          uint32_t          addr_start,
                          uint32_t          blk_num);

/**
 * \brief SDIO���ݿ��ȡ
 *
 * \param[in]  p_dev        : SDIO�豸
 * \param[in]  p_buf        : ���ݻ�����
 * \param[in]  addr_start   : ��ȡ���ݵ���ʼ��ַ
 * \param[in]  blk          : ��Ҫ��ȡ�Ŀ�����
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdio_blocks_read (am_sdio_device_t *p_dev,
                         uint8_t          *p_buf,
                         uint32_t          addr_start,
                         uint32_t          blk_num);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDIO_H */

/*end of file */
