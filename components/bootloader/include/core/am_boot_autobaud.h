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
 * \brief �Զ������ʷ��񣬿���ʵ����δ֪�����ʵĴ����豸�Զ�ƥ�䲨����
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  ipk, first implementation
 * \endinternal
 */

#ifndef __AM_AUTO_BAUDRATE_H__
#define __AM_AUTO_BAUDRATE_H__

/**
 * \brief bootloader �Զ������ʼ�� ���������ṹ��
 */
struct am_boot_autobaud_drv_funcs {

    /** \brief ��ȡ������*/
    int (*pfn_get_baudrate) (void *p_drv, uint32_t *p_baud);

};

/**
 * \brief bootloader memory ��׼����ṹ��
 */
typedef struct am_boot_autobaud_serv {
    const struct am_boot_autobaud_drv_funcs *p_funcs;  /**< \brief �豸���������ṹ��ָ��    */
    void                                    *p_drv;    /**< \brief �豸����������һ������ */
} am_boot_autobaud_serv_t;

/** \brief bootloader �Զ������� ��׼�������������Ͷ��� */
typedef am_boot_autobaud_serv_t  *am_boot_autobaud_handle_t;


/**
 * \brief ��ȡ�������ݵĲ����ʺ���
 *
 * \param[in]  handle     : �Զ������ʷ�����
 * \param[out] p_baudrate : ָ���ȡ�Ĳ����ʵ�ַ
 *
 * \retval AM_OK    : ��ȡ�ɹ�
 *         AM_ERROR : ��ȡʧ��
 */
am_static_inline
int am_boot_baudrate_get (am_boot_autobaud_handle_t handle,
                          uint32_t                 *p_baudrate)
{
    if(handle && handle->p_funcs->pfn_get_baudrate) {
        return handle->p_funcs->pfn_get_baudrate(handle->p_drv, p_baudrate);
    }
    return -AM_EINVAL;
}
#endif /* __AM_AUTO_BAUDRATE_H__ */
/* end of file */
