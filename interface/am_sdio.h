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
struct am_sdio_cmd;           /**< \brief ����SDIO��Ϣ�Ľṹ������     */

/**
 * \brief sdio���������ṹ��
 */
struct am_sdio_drv_funcs {

    /** \brief SDIO���ݷ��� */
    int (*pfn_sdio_data_send) (void     *p_drv,
                              uint8_t  *p_buf,
                              uint16_t  len);

    /** \brief SDIO���ݽ��� */
    int (*pfn_sdio_data_recv) (void    *p_drv,
                              uint8_t *p_buf,
                              uint16_t len);

    /** \brief SDIO�����   */
    int (*pfn_sdio_send_cmd) (void               *p_drv,
                              struct am_sdio_cmd *p_cmd);

    /** \brief ����SDIO��Ϣ���䣬��ɺ���ûص�����  */
    int (*pfn_sdio_msg_start)(void *p_drv);
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

am_static_inline
int am_sdio_send_cmd (am_sdio_handle_t handle,
                      am_sdio_cmd_t   *p_cmd)
{
    return handle->p_funcs->pfn_sdio_send_cmd(handle->p_drv,
                                              p_cmd);
}

am_static_inline
int am_sdio_msg_send (am_sdio_handle_t handle,
                      uint8_t         *p_buf,
                      uint16_t         len)
{
     return handle->p_funcs->pfn_sdio_data_send(handle->p_drv,
                                               p_buf,
                                               len);
}

am_static_inline
int am_sdio_msg_recv (am_sdio_handle_t handle,
                      uint8_t         *p_buf,
                      uint16_t         len)
{
    return handle->p_funcs->pfn_sdio_data_recv(handle->p_drv,
                                              p_buf,
                                              len);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDIO_H */

/*end of file */
