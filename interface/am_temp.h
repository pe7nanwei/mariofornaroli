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
 * \brief �¶ȴ����������ӿ�
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "am_temp.h"
 * \endcode
 *
 * \internal
 * \par modification history
 * - 1.00 17-06-19  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_TEMP_H
#define __AM_TEMP_H

#ifdef __cplusplus
extern "C" {
#endif
    
/**
 * \addtogroup am_if_temp
 * \copydoc am_temp.h
 * @{
 */

#include "am_common.h"

/**
 * \brief �¶ȴ��������������ṹ��
 */
struct am_temp_drv_funcs {

    /** \brief ��ȡ�¶ȣ��õ����¶�ֵΪʵ���¶�ֵ��1000��  */
    int (*pfn_temp_read) (void *p_drv, int32_t *p_temp);
};
 
/** 
 * \brief �¶ȷ���
 */
typedef struct am_temp_dev {

    /** \brief �¶ȴ�������������   */
    const struct am_temp_drv_funcs  *p_funcs;
    
    /** \brief �������������ĵ�һ������ */
    void                            *p_cookie;

} am_temp_dev_t;

/** \brief �¶ȱ�׼�������������Ͷ��� */
typedef am_temp_dev_t *am_temp_handle_t;
 
/**
 * \brief ��ȡһ���¶ȴ������豸���¶�ֵ
 *
 * ʹ�øýӿڿ��Է���Ļ�ȡӲ�������϶�Ӧ�¶ȴ��������¶�ֵ��
 *
 * \param[in] handle  : ��׼�¶ȷ�����
 * \param[out] p_temp : ���ص�ǰ��ȡ�����¶�ֵ��Ϊʵ���¶�ֵ��1000��
 *
 * \retval AM_OK : ��ȡ�¶ȳɹ�
 * \retval  < 0  �� ��ȡ�¶ȳ���
 */
am_static_inline
int am_temp_read (am_temp_handle_t handle, int32_t *p_temp)
{
    return handle->p_funcs->pfn_temp_read(handle->p_cookie, p_temp);
}

/** @} am_if_temp */

#ifdef __cplusplus
}
#endif

#endif /* __AM_TEMP_H */

/* end of file */
