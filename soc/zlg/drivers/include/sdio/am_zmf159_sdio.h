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
 * - 1.00 19-06-04  ipk, first implementation
 * \endinternal
 */

#ifndef __AM_ZMF159_SDIO_H
#define __AM_ZMF159_SDIO_H

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
typedef struct am_zmf159_sdio_devinfo {

    /** \brief SDIO�Ĵ�������ַ */
    uint32_t              regbase;

    /** \brief SDIO�жϺ� */
    uint32_t              inum;

    /** \brief SDIOʱ��ID */
    int                   clk_num;

    /** \brief SDIO����ģʽ */
    uint8_t               speed_mode;

    /** \brief ƽ̨��ʼ������ */
    void    (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void    (*pfn_plfm_deinit)(void);

} am_zmf159_sdio_devinfo_t;

/**
 * \brief SDIO�豸�ṹ��
 */
typedef struct am_zmf159_sdio_dev {

    /** \brief SDIO��׼����  */
    am_sdio_serv_t                  sdio_serv;

    /** \brief ָ��SDIO�豸��Ϣ  */
    const am_zmf159_sdio_devinfo_t *p_devinfo;

    /** \brief wait�ȴ�  */
    am_wait_t                       wait;

    /** \brief �����ж�״̬  */
    uint16_t                        int_status;

} am_zmf159_sdio_dev_t;

/**
 * \brief SDIO��ʼ��
 *
 * \param[in] p_dev     : ָ��SDIO�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SDIO�豸��Ϣ�ṹ���ָ��
 *
 * \return SDIO��׼����������
 */
am_sdio_handle_t am_zmf159_sdio_init (am_zmf159_sdio_dev_t           *p_dev,
                                     const am_zmf159_sdio_devinfo_t *p_devinfo);

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

#endif /* __AM_ZMF159_SDIO_H */

/* end of file */
