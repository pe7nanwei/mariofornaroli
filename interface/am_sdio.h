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
#include "am_list.h"

/**
 * \addtogroup am_if_sdio
 * \copydoc am_sdio.h
 * @{
 */

/**
 * \name SDIOģʽ��־������am_sdio_mkdev()������mode����
 * @{
 */

/**
  * @brief SDIO Commands  Index
  */
#define AM_SD_CMD_GO_IDLE_STATE           ((uint8_t)0)
#define AM_SD_CMD_SEND_OP_COND            ((uint8_t)1)
#define AM_SD_CMD_ALL_SEND_CID            ((uint8_t)2)
#define AM_SD_CMD_SET_REL_ADDR            ((uint8_t)3) /*!< SDIO_SEND_REL_ADDR for SD Card */
#define AM_SD_CMD_SET_DSR                 ((uint8_t)4)
#define AM_SD_CMD_SDIO_SEN_OP_COND        ((uint8_t)5)
#define AM_SD_CMD_HS_SWITCH               ((uint8_t)6)
#define AM_SD_CMD_SEL_DESEL_CARD          ((uint8_t)7)
#define AM_SD_CMD_HS_SEND_EXT_CSD         ((uint8_t)8)
#define AM_SD_CMD_SEND_CSD                ((uint8_t)9)
#define AM_SD_CMD_SEND_CID                ((uint8_t)10)
#define AM_SD_CMD_READ_DAT_UNTIL_STOP     ((uint8_t)11) /*!< SD Card doesn't support it */
#define AM_SD_CMD_STOP_TRANSMISSION       ((uint8_t)12)
#define AM_SD_CMD_SEND_STATUS             ((uint8_t)13)
#define AM_SD_CMD_HS_BUSTEST_READ         ((uint8_t)14)
#define AM_SD_CMD_GO_INACTIVE_STATE       ((uint8_t)15)
#define AM_SD_CMD_SET_BLOCKLEN            ((uint8_t)16)
#define AM_SD_CMD_READ_SINGLE_BLOCK       ((uint8_t)17)
#define AM_SD_CMD_READ_MULT_BLOCK         ((uint8_t)18)
#define AM_SD_CMD_HS_BUSTEST_WRITE        ((uint8_t)19)
#define AM_SD_CMD_WRITE_DAT_UNTIL_STOP    ((uint8_t)20) /*!< SD Card doesn't support it */
#define AM_SD_CMD_SET_BLOCK_COUNT         ((uint8_t)23) /*!< SD Card doesn't support it */
#define AM_SD_CMD_WRITE_SINGLE_BLOCK      ((uint8_t)24)
#define AM_SD_CMD_WRITE_MULT_BLOCK        ((uint8_t)25)
#define AM_SD_CMD_PROG_CID                ((uint8_t)26) /*!< reserved for manufacturers */
#define AM_SD_CMD_PROG_CSD                ((uint8_t)27)
#define AM_SD_CMD_SET_WRITE_PROT          ((uint8_t)28)
#define AM_SD_CMD_CLR_WRITE_PROT          ((uint8_t)29)
#define AM_SD_CMD_SEND_WRITE_PROT         ((uint8_t)30)
#define AM_SD_CMD_SD_ERASE_GRP_START      ((uint8_t)32) /*!< To set the address of the first write
                                                      block to be erased. (For SD card only) */
#define AM_SD_CMD_SD_ERASE_GRP_END        ((uint8_t)33) /*!< To set the address of the last write block of the
                                                      continuous range to be erased. (For SD card only) */
#define AM_SD_CMD_ERASE_GRP_START         ((uint8_t)35) /*!< To set the address of the first write block to be erased.
                                                      (For MMC card only spec 3.31) */

#define AM_SD_CMD_ERASE_GRP_END           ((uint8_t)36) /*!< To set the address of the last write block of the
                                                      continuous range to be erased. (For MMC card only spec 3.31) */

#define AM_SD_CMD_ERASE                   ((uint8_t)38)
#define AM_SD_CMD_FAST_IO                 ((uint8_t)39) /*!< SD Card doesn't support it */
#define AM_SD_CMD_GO_IRQ_STATE            ((uint8_t)40) /*!< SD Card doesn't support it */
#define AM_SD_CMD_LOCK_UNLOCK             ((uint8_t)42)
#define AM_SD_CMD_APP_CMD                 ((uint8_t)55)
#define AM_SD_CMD_GEN_CMD                 ((uint8_t)56)
#define AM_SD_CMD_NO_CMD                  ((uint8_t)64)


#define AM_SD_VOLTAGE_WINDOW_SD            ((uint32_t)0x80100000)
#define AM_SD_HIGH_CAPACITY                ((uint32_t)0x40000000)
#define AM_SD_STD_CAPACITY                 ((uint32_t)0x00000000)
#define AM_SD_CHECK_PATTERN                ((uint32_t)0x000001AA)

/**
 * \brief SDIO ģʽ����
 */
#define AM_SDIO_SDIO_M              0       /**< \brief SDIO SDIOģʽ */
#define AM_SDIO_SD_1B_M             1       /**< \brief SDIO SD 1��ģʽ */
#define AM_SDIO_SD_4B_M             2       /**< \brief SDIO SD 4��ģʽ */
#define AM_SDIO_SD_8B_M             3       /**< \brief SDIO SD 8��ģʽ */


/**
 * \brief ������Ӧ����
 */
#define AWBL_SDIO_RSP_NONE      0
#define AWBL_SDIO_RSP_R1        1
#define AWBL_SDIO_RSP_R1B       2
#define AWBL_SDIO_RSP_R2        3
#define AWBL_SDIO_RSP_R3        4
#define AWBL_SDIO_RSP_R4        5
#define AWBL_SDIO_RSP_R5        6
#define AWBL_SDIO_RSP_R6        7
#define AWBL_SDIO_RSP_R7        8

/**
 * \brief ��д�����־
 */
#define AWBL_SDIO_NO_DATA       0
#define AWBL_SDIO_RD_DATA       1
#define AWBL_SDIO_WR_DATA       2


#define AM_SDIO_M_WR            0x0000u    /**< \brief д����           */
#define AM_SDIO_M_RD            0x0002u    /**< \brief ������           */
//#define AM_SDIO_M_NOSTART       0x0004u    /**< \brief ������������     */
//#define AM_SDIO_M_REV_DIR_ADDR  0x0008u    /**< \brief ��д��־λ��ת   */
//#define AM_SDIO_M_RECV_LEN      0x0010u    /**< \brief �ݲ�֧��         */

/**
 * \brief SDIO��������Ϣ�ṹ��
 */

struct am_sdio_transfer;      /**< \brief ����SDIO����Ľṹ������     */
struct am_sdio_message;       /**< \brief ����SDIO��Ϣ�Ľṹ������     */
struct am_sdio_cmd;           /**< \brief ����SDIO��Ϣ�Ľṹ������     */

/**
 * \brief sdio���������ṹ��
 */
struct am_sdio_drv_funcs {

//    /** \brief ��ȡSDIO��������Ϣ */
    int (*pfn_sdio_msg_send) (void *p_drv, struct am_sdio_message *p_buf, uint16_t len);

    //    /** \brief ��ȡSDIO��������Ϣ */
    int (*pfn_sdio_msg_recv) (void *p_drv, struct am_sdio_message *p_msg, uint16_t len);

    /** \brief ����SDIO�ӻ��豸   */
    int (*pfn_sdio_send_cmd) (void *p_drv,  struct am_sdio_cmd *p_cmd);

    /** \brief ����SDIO��Ϣ���䣬��ɺ���ûص�����  */
    int (*pfn_sdio_msg_start)(void                   *p_drv);
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

/** \brief SDIO���豸�����ṹ */
typedef struct am_sdio_device {

    am_sdio_handle_t  handle;       /**< \brief ���豸������SDIO��׼����handle */

    /** \brief ���豸��SDIOģʽ��־����ο���SDIOģʽ��־��*/
    uint16_t         mode;

    /* \brief �豸֧�ֵ�����ٶ� */
    uint32_t         max_speed_hz;

    /** \brief �ӻ��豸����*/
    uint16_t         dev_flags;
} am_sdio_device_t;

/**< \brief ��Ӧ���� */
#define SDIO_RESPONSE_NO                    0
#define SDIO_RESPONSE_SHORT                 1
#define SDIO_RESPONSE_LONG                  2

/**
 * \brief SDIO ���������ṹ��
 */
typedef struct am_sdio_cmd {
    uint32_t             cmd;        /**< \brief SDIO ����*/
    uint32_t             arg;        /**< \brief ������� */
    uint8_t              rsp_type;   /**< \brief ��Ӧ���� */
    uint32_t             p_rsp[4];   /**< \brief ��Ӧ���� */
} am_sdio_cmd_t;

/**
 * \brief SDIO ����ṹ�� (�Ƽ�ʹ�� am_sdio_mktrans() ���ñ����ݽṹ)
 */
typedef struct am_sdio_message {
//    am_sdio_cmd_t       *p_cmd;    /**< \brief ���������� */
    uint8_t             *p_data;     /**< \brief ���ݻ����� */
    uint32_t             blk_size;   /**< \brief ������С */
    uint32_t             nblock;     /**< \brief ��������� */
//    uint8_t              opt;      /**< \brief ������� */
} am_sdio_message_t;

///**
// * \brief SDIO ��Ϣ (�Ƽ�ʹ�� am_sdio_mkmsg() ���ñ����ݽṹ)
// */
//typedef struct am_sdio_message{
//    am_sdio_transfer_t *p_transfers;  /**< \brief �����Ϣ�Ĵ���              */
//    uint16_t            trans_num;    /**< \brief ������Ĵ������          */
//    uint16_t            done_num;     /**< \brief �ɹ�����Ĵ������          */
//    am_pfnvoid_t        pfn_complete; /**< \brief ������ɻص�����            */
//    void               *p_arg;        /**< \brief ���ݸ� pfn_complete �Ĳ���  */
//    int                 status;       /**< \brief ��Ϣ��״̬                  */
//    void               *ctlrdata[2];  /**< \brief ������ʹ��                  */
//}am_sdio_message_t;


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
}

/**
 * \brief SDIO�ӻ��豸�����ṹ���������
 *
 * \param[in] p_dev       : ָ��ӻ��豸�����ṹ���ָ��
 * \param[in] handle      : ����豸������I2C��׼����������
 * \param[in] mode        : SDIOģʽ��־
 * \param[in] max_speed_hz: �豸֧�ֵ�����ٶ�
 * \param[in] dev_flags   : �ӻ��豸���ԣ�����SDIO���豸���Ա�־��
 *
 * \return ��
 */
am_static_inline
void am_sdio_mkdev (am_sdio_device_t *p_dev,
                    am_sdio_handle_t  handle,
                    uint16_t          mode,
                    uint32_t          max_speed_hz,
                    uint16_t          dev_flags)
{
    p_dev->handle        = handle;
    p_dev->mode          = mode;
    p_dev->max_speed_hz  = max_speed_hz;
    p_dev->dev_flags     = dev_flags;
}

/**
 * \brief SDIO����ṹ����Ϣ��������
 *
 * \param[in] p_trans  : ָ����ṹ���ָ��
 * \param[in] p_data   : ���ݻ�����
 * \param[in] p_cmd    : ���������ṹ��ָ��
 * \param[in] blk_size : �����Ĵ�С
 * \param[in] nblock   : �����ĸ���
 * \param[in] opt      : ���������
 *
 * \retval  AM_OK     : ����ṹ������������
 * \retval -AM_EINVAL : ��������
 */

//am_static_inline
//void am_sdio_mktrans (am_sdio_transfer_t *p_trans,
//                      uint8_t            *p_data,
//                      am_sdio_cmd_t      *p_cmd,
//                      uint32_t            blk_size,
//                      uint32_t            nblock,
//                      uint8_t             opt)
//{
//    p_trans->p_data   = p_data;
//    p_trans->blk_size = blk_size;
//    p_trans->nblock   = nblock;
//    p_trans->opt      = opt;
//    p_trans->p_cmd    = p_cmd;
//}

/**
 * \brief ��ʼ����Ϣ
 *
 * \param[in] p_msg        : SDIO��Ϣ������ָ��
 * \param[in] p_transfers  : �����Ϣ�Ĵ���
 * \param[in] trans_num    : ������Ĵ������
 * \param[in] pfn_complete : ������ɻص�����
 * \param[in] p_arg        : ���ݸ��ص������Ĳ���
 *
 * \return ��
 */
//am_static_inline
//void am_sdio_mkmsg (am_sdio_message_t  *p_msg,
//                   am_sdio_transfer_t  *p_transfers,
//                   uint16_t             trans_num,
//                   am_pfnvoid_t         pfn_complete,
//                   void                *p_arg)
//{
//
//    p_msg->p_transfers  = p_transfers;  /**< \brief �����Ϣ�Ĵ���              */
//
//    p_msg->trans_num    = trans_num;    /**< \brief ������Ĵ������          */
//    p_msg->done_num     = 0;            /**< \brief �ɹ�����Ĵ������          */
//    p_msg->pfn_complete = pfn_complete; /**< \brief ������ɻص�����            */
//    p_msg->p_arg        = p_arg;        /**< \brief ���ݸ� pfn_complete �Ĳ���  */
//    p_msg->status       = 0;            /**< \brief ��Ϣ��״̬                  */
//}

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
int am_sdio_msg_start (am_sdio_handle_t    handle)
{
    return handle->p_funcs->pfn_sdio_msg_start(handle->p_drv);
}

int (*pfn_sdio_send_cmd) (void *p_drv,  am_sdio_cmd_t *p_cmd);

am_static_inline
int am_sdio_send_cmd (am_sdio_handle_t    handle,
		              am_sdio_cmd_t      *p_cmd)
{
    return handle->p_funcs->pfn_sdio_send_cmd(handle->p_drv,
    		                                  p_cmd);
}

am_static_inline
int am_sdio_msg_send (am_sdio_handle_t handle,  struct am_sdio_message  *p_msg, uint16_t len)
{
	 return handle->p_funcs->pfn_sdio_msg_send(handle->p_drv, p_msg, len);
}

am_static_inline
int am_sdio_msg_recv (am_sdio_handle_t handle,   struct am_sdio_message  *p_msg, uint16_t len)
{
	return handle->p_funcs->pfn_sdio_msg_recv(handle->p_drv, p_msg, len);
}



/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDIO_H */

/*end of file */
