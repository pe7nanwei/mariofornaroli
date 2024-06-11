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
 * \brief I2C�ӻ���׼�ӿ�
 *
 * \note �û��ɵ��ô˽ӿ�ͨ��MCU��ģ��һ��I2C���豸
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-06  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_I2C_SLV_H
#define __AM_I2C_SLV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * @addtogroup am_if_i2c_slv
 * @copydoc am_i2c_slv.h
 * @{
 */

/**
 * \name I2C�ӻ��豸  ���Ա�־������ am_i2c_slv_device �� dev_flags ��Ա
 * @{
 */
#define AM_I2C_SLV_ADDR_7BIT          0x0000u            /**< \brief 7-bits �豸��ַ(Ĭ��) */
#define AM_I2C_SLV_ADDR_10BIT         0x0001u            /**< \brief 10-bits �豸��ַ */

#define AM_I2C_SLV_GEN_CALL_NACK      0X0000u             /**< \brief ����Ӧ�㲥��ַ (Ĭ��) */
#define AM_I2C_SLV_GEN_CALL_ACK       0X0002u             /**< \brief ��Ӧ�㲥��ַ  */

/* �������ں����ӵ�ַ���豸 */
#define AM_I2C_SLV_SUBADDR_1BYTE      0X0000u            /**< \brief �ӵ�ַ���1�ֽ�(Ĭ��) */
#define AM_I2C_SLV_SUBADDR_2BYTE      0X0004u            /**< \brief �ӵ�ַ���2�ֽ� */


#define AM_I2C_SLV_SUBADDR_SELF_INCREASING       0X0000u   /**< \brief ֧���ӵ�ַ����  (Ĭ��)*/
#define AM_I2C_SLV_SUBADDR_NSELF_INCREASING      0X0100u   /**< \brief ��֧���ӵ�ַ����   */
/** @} */


/**
 * \name  �ص������ķ���ֵ����
 *
 * \ note Ҫ������Ӳ���Ƿ�֧�ֿ��ƴӻ���Ӧ
 * @{
 */
#define AM_I2C_SLV_ACK          0       /**< \brief �ӻ���Ӧ  */
#define AM_I2C_SLV_NACK         1       /**< \brief �ӻ�����Ӧ */

/** @} */



struct am_i2c_slv_device;

/**
 * \brief I2C�ӻ�����������
 */
struct am_i2c_slv_drv_funcs {
    /** \brief ʹ��I2C�ӻ��豸��ʼ���� */
    int (*pfn_i2c_slv_setup) (void *p_drv, struct am_i2c_slv_device *p_i2c_slv_dev);

    /** \brief �ر�I2C���豸 */
    int (*pfn_i2c_slv_shutdown) (void *p_drv, struct am_i2c_slv_device *p_i2c_slv_dev);

    /** \brief ��ȡ�������ɵĴӻ��豸���� */
    int (*pfn_i2c_slv_num_get) (void *p_drv);
};

/**
 * \brief I2C�ӻ���׼����ṹ��
 */

typedef struct am_i2c_slv_serv {
    struct am_i2c_slv_drv_funcs   *p_funcs;   /**< \brief I2C����������         */
    void                          *p_drv;     /**< \brief I2C������������ڲ��� */
} am_i2c_slv_serv_t;

/** \brief I2C�ӻ���׼�������������� */
typedef am_i2c_slv_serv_t *am_i2c_slv_handle_t;

/**
 * \brief �ص����� ���ڷ���������ӻ�������״̬
 *
 * \note ����ֵ�ο� �����ص������ķ���ֵ���͡�
 */
typedef struct am_i2c_slv_cb_funcs {

    /** \brief �ӻ���ַƥ��ʱ�ص��������� is_rx ΪAM_TRUEʱ��ʾ �ӻ������������ ,Ϊ AM_FALSEʱ��ʾ�ӻ������������   */
    int (*pfn_addr_match)(void *p_arg, am_bool_t is_rx);

    /** \brief ��ȡһ�������ֽڻص����� */
    int (*pfn_txbyte_get)(void *p_arg, uint8_t *p_byte);

    /** \brief �ύһ�����յ����ֽڻص�����  */
    int (*pfn_rxbyte_put)(void *p_arg, uint8_t byte);

    /** \brief ֹͣ����ص����� */
    void (*pfn_tran_stop)(void *p_arg);

    /** \brief �㲥�ص�����   */
    int (*pfn_gen_call)(void *p_arg, uint8_t byte);

}am_i2c_slv_cb_funcs_t;


/**
 * \brief I2C�ӻ��豸�ṹ��  (�Ƽ�ʹ�� am_i2c_slv_mkdev() ���ñ����ݽṹ)
 */
typedef struct am_i2c_slv_device {
    am_i2c_slv_handle_t    handle;              /**< \brief ����豸������I2C�����׼handle    */
    am_i2c_slv_cb_funcs_t *p_cb_funs;           /**< \brief �ص�����,�û�����Ҫ�Ļص�������ֵΪNULL���� */
    uint16_t               dev_addr;            /**< \brief ���豸�ĵ�ַ */
    uint16_t               dev_flags;           /**< \brief �豸�����ԣ�����I2C���豸���Ա�־�� */
    void                  *p_arg;               /**< \brief �ص��������� */
}am_i2c_slv_device_t;

/**
 * \brief I2C���ӻ��豸 �����ṹ���������
 *
 * \param[in] p_dev                 : ָ��ӻ��豸�����ṹ���ָ��
 * \param[in] handle                : ����豸������I2C��׼����������
 * \param[in] p_cb_funs             : �ص�����
 * \param[in] dev_addr              : �ӻ��豸��ַ
 * \param[in] dev_flags             : �ӻ��豸���ԣ�����I2C���豸���Ա�־��
 * \param[in] p_arg                 : �ص���������
 *
 * \return ��
 *
 * \par ����
 * \code
 * #include "am_i2c_slv.h"
 *
 *   am_i2c_slv_device_t  i2c_slv_dev;
 *
 *   am_i2c_slv_mkdev(  &i2c_slv_dev,
 *                      i2c_slv_handle,
 *                      &__g__cb_funs,
 *                      0x55,
 *                      AM_I2C_SLV_ADDR_7BIT
 *                      &i2c_slv_dev);
 * \endcode
 */
am_static_inline
void am_i2c_slv_mkdev (am_i2c_slv_device_t    *p_dev,
                       am_i2c_slv_handle_t     handle,
                       am_i2c_slv_cb_funcs_t  *p_cb_funs,
                       uint16_t                dev_addr,
                       uint16_t                dev_flags,
                       void                   *p_arg)

{
    p_dev->handle           = handle;
    p_dev->dev_addr         = dev_addr;
    p_dev->dev_flags        = dev_flags;
    p_dev->p_cb_funs        = p_cb_funs;
    p_dev->p_arg            = p_arg;
}

/**
 * \brief ����I2C�ӻ��豸
 *
 * \param[in] p_dev  : I2C�ӻ��豸
 *
 * \retval  AM_OK      :�����ɹ�
 * \retval  AM_EINVAL  :��������
 * \retval  AM_EAGAIN  :�޿��õĴӻ�����
 *
 * \note  ����am_i2c_slv_mkdev��������һ���ӻ��豸֮�󣬱�����ô˺��� �����ӻ�
 *
 */
am_static_inline
int am_i2c_slv_setup (am_i2c_slv_device_t *p_dev)
{
    return p_dev->handle->p_funcs->pfn_i2c_slv_setup(p_dev->handle->p_drv, p_dev);
}

/**
 * \brief �ر�I2C�ӻ��豸
 *
 * \param[in] p_dev  : I2C�ӻ��豸
 *
 * \retval  AM_OK      : �رճɹ�
 *
 * \note �ر�֮���������¿����� ���� am_i2c_slv_start ����
 */
am_static_inline
int am_i2c_slv_shutdown ( am_i2c_slv_device_t *p_dev)
{
    return p_dev->handle->p_funcs->pfn_i2c_slv_shutdown(p_dev->handle->p_drv, p_dev);
}

/**
 * \brief ��ȡ���õĴӻ��豸����
 *
 * \param[in] handle   : I2C�ӻ���׼����������
 *
 * \retval  ����ֵΪ���õĴӻ�����
 *          ���� 0 ���޿��ôӻ����� �� �����ٵ��� am_i2c_slv_setup ����
 *          ���� 1 �����ôӻ�����Ϊ 1�����ٵ���am_i2c_slv_setup ����һ�Σ����������ɵ��豸����
 *          ...
 *          ���� n : ���ôӻ�����Ϊ n,���ٵ���am_i2c_slv_setup ����n��,���������ɵ��豸���� .
 */
am_static_inline
int am_i2c_slv_num_get (am_i2c_slv_handle_t handle)
{
    return handle->p_funcs->pfn_i2c_slv_num_get(handle->p_drv);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2C_SLV_H */

/* end of file */
