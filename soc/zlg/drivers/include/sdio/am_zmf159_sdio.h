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

#ifndef __AM_ZLG_SDIO_H
#define __AM_ZLG_SDUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_sdio.h"
#include "am_list.h"
#include "am_wait.h"
#include "am_softimer.h"

#include "am_vdebug.h"

/**
 * \addtogroup am_zlg_if_sdio
 * \copydoc am_zlg_sdio.h
 * @{
 */

/**
 * \brief SDIO�豸��Ϣ�����ṹ��
 */
typedef struct am_zlg_sdio_devinfo {

    uint32_t              regbase;

    uint32_t              inum;

    /** \brief ʱ��ID */
    int                   clk_num;

    uint8_t               width;

    uint32_t              speed;

    uint8_t               speed_mode;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_zlg_sdio_devinfo_t;

/**
 * \brief SDIO�豸�ṹ��
 */
typedef struct am_zlg_sdio_dev {

	am_sdio_serv_t                          sdio_serv;

    /** \brief SDIO��������Ϣ���� */
    struct am_list_head                     msg_list;

//    /** \brief ָ��SDIO����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
//    am_sdio_transfer_t                      *p_cur_trans;

    /** \brief �Ƿ���ɱ�����Ϣ */
    volatile am_bool_t                       is_complete;

    /** \brief �������ݽ���/���ͼ��� */
    volatile uint32_t                        data_ptr;

    /** \brief æ��ʶ */
    volatile am_bool_t                       busy;

    /** \brief ״̬ */
    volatile uint8_t                         state;

    /** \brief �Ƿ��ж�״̬�� */
    volatile am_bool_t                       is_abort;

    /** \brief ָ��SDIO�豸��Ϣ��ָ�� */
    const am_zlg_sdio_devinfo_t             *p_devinfo;

    am_wait_t                                wait;

    uint16_t                                 int_status;

} am_zlg_sdio_dev_t;

/**
 * \brief SDIO��ʼ��
 *
 * \param[in] p_dev     : ָ��SDIO�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SDIO�豸��Ϣ�ṹ���ָ��
 *
 * \return SDIO��׼����������
 */
am_sdio_handle_t am_zmf159_sdio_init (am_zlg_sdio_dev_t           *p_dev,
                                     const am_zlg_sdio_devinfo_t *p_devinfo);

/**
 * \brief ���SDIO��ʼ��
 *
 * \param[in] handle : ����豸������SDIO��׼����������
 *
 * \return ��
 */
void am_zmf159_sdio_deinit (am_sdio_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG_SDIO_H */

/* end of file */
