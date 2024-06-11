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
 * \brief �����ӵ�ַ��I2C�ӻ���׼�ӿ�
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-19  vir, first implementation.
 * \endinternal
 */

#ifndef __AM_I2C_SLV_SUBADDR_H
#define __AM_I2C_SLV_SUBADDR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "am_i2c_slv.h"

/**
 * @addtogroup am_if_i2c_slv_subaddr
 * @copydoc am_i2c_slv_subaddr.h
 * @{
 */

struct am_i2c_slv_subaddr_device;

/**
 * \brief �����ӵ�ַ�豸�Ļص����� �����ڷ���
 */
typedef struct am_i2c_slv_subaddr_cb_funcs {

    /** \brief �ӻ���ַƥ��ʱ�ص����� */
    void (*pfn_addr_match)( void       *p_arg,
                            am_bool_t   is_rx);

    /**
     * \brief ������ɻص�����
     *         is_rx:   ΪAM_TRUEʱ��ʾ �ӻ������������ , Ϊ AM_FALSEʱ��ʾ�ӻ������������
     *         subaddr�� �������ӻ����͵��ӵ�ַ ��������� �������������� (��Ĵ���λ���޹� )
     *                  eg: �ӻ�������Ϊ ��int16_t buf[5]��subaddr=2ʱ ����������ӻ���buf[2]��ʼ����
     *         size�� ������ӻ� ����д�˶����ֽ�
     *
     */
    void (*pfn_tran_finish)(void        *p_arg,
                            am_bool_t    is_rx,
                            uint32_t     subaddr,
                            uint32_t     size);

    /** \brief �㲥�ص�����   */
    int (*pfn_gen_call)(void *p_arg, uint8_t byte);

}am_i2c_slv_subaddr_cb_funcs_t;

/**
 * \name ���豸�Ĵ����ռ��С
 * \anchor grp_i2c_slv_reg_mode
 * @{
 */

#define AM_I2C_SLV_REG_8_BIT           0X01u            /**< \brief ÿ���ӵ�ַ��Ӧ�ļĴ����ռ��СΪ8λ ( Ĭ��) */
#define AM_I2C_SLV_REG_16_BIT          0X02u            /**< \brief ÿ���ӵ�ַ��Ӧ�ļĴ����ռ��СΪ16λ  */
#define AM_I2C_SLV_REG_32_BIT          0X04u            /**< \brief ÿ���ӵ�ַ��Ӧ�ļĴ����ռ��СΪ32λ  */
#define AM_I2C_SLV_REG_IRREGULAR       0X08u            /**< \brief �ӵ�ַ��Ӧ�ļĴ����ռ��С������  */

/** @} */

/**
 * \brief �����ӵ�ַ�ļĴ�����Ϣ�ṹ��
 *
 * \note ����ע�͵� 1 ��ʾ ��ÿ���ӵ�ַ��Ӧ�ļĴ����ڴ�ռ� ����ͬ ����
 *                     ĳ���ӵ�ַ��Ӧ�ļĴ����ռ� ��С��Ϊ1��2��4�ֽ� (������8λ��16λ��32λ)
 *
 *              2 ��ʾ �� ÿ���ӵ�ַ��Ӧ�ļĴ����ռ��С��Ϊ1�ֽ� ��2�ֽ� ��4�ֽ� (��8λ��16λ��32λ)
 *                     Ĭ�����мĴ�����������
 *
 * \par ����
 * \code
 * #include "am_i2c_slv_subaddr.h"
 *
 *   //���� 1 �� �Ĵӻ��豸�Ĵ���
 *    reg_mode = AM_I2C_SLV_REG_IRREGULAR
 *
 *   static uint8_t   reg1[5];    //�ӵ�ַΪ0
 *   static uint16_t  reg2[10];   //�ӵ�ַΪ1
 *   static uint32_t  reg3[1];    //�ӵ�ַ λ2
 *   .....
 *   static uint32_t  reg3_wr[1] = {0XFFFF0000}; //�Ĵ���3�Ķ�д������־
 *
 *   am_i2c_slv_subaddr_reg_info_t   i2c_slv_reg[] =
 *   {
 *      { sizeof(reg1), reg1, NULL },
 *      { sizeof(reg2), reg2, NULL },
 *      { sizeof(reg3), reg3, reg3_wr},
 *      ....
 *   }
 *
 *   //����2 ��Ĵӻ��豸�Ĵ���
 *   reg_mode = AM_I2C_SLV_REG_8_BIT   ��
 *   reg_mode = AM_I2C_SLV_REG_16_BIT  ��
 *   reg_mode = AM_I2C_SLV_REG_32_BIT
 *
 *   static uint16_t  reg[20];  //�ӵ�ַ���������������
 *  am_i2c_slv_subaddr_reg_info_t i2c_slv_reg[1] =
 *  {
 *      { sizeof(reg), reg,  NULL },
 *  }
 *
 * \endcode
 *
 */
typedef struct am_i2c_slv_subaddr_reg_info {

    /**
     *  \brief 1 ĳ���ӵ�ַ��Ӧ�Ĵ����ռ�ĳ���(�ֽ�)
     *         2 ���豸���мĴ������ܳ��� (�ֽ�)
     */
    uint32_t  reg_len;

    /**
     *  \brief 1 ĳ���ӵ�ַ ��Ӧ�Ĵ����ռ���׵�ַ
     *         2 ���豸�Ĵ������׵�ַ
     */
    uint8_t  *p_reg_addr;

    /**
     * \brief  1 ĳ���ӵ�ַ ��Ӧ�Ĵ����ռ�ĵĶ�д������־(����λֵΪ  0���ɶ���д    1��ֻ�ɶ�������д)
     *            ������Ҫ��ֵΪNULL����Ĭ�Ͽɶ���д
     *         2 ���豸�Ĵ����Ķ�д������־
     */
    uint8_t  *p_reg_wr;
}am_i2c_slv_subaddr_reg_info_t;



/**
 * \brief �����ӵ�ַ��I2C�ӻ��豸�ṹ��
 */
typedef struct am_i2c_slv_subaddr_device {
    uint32_t   subaddr ;               /**< \brief �����������ӻ����ӵ�ַ */
    uint32_t   off_byte ;              /**< \brief ����Ҫ����������ݶ�������豸�Ĵ��������׵�ַ��ƫ��  */
    am_bool_t  is_subaddr;             /**< \brief �жϵ�ǰ���ܵ��Ƿ����ӵ�ַ */
    am_bool_t  is_rx;                  /**< \brief �жϵ�ǰ�ӻ��Ƿ��ͻ��ǽ�������  */
    uint8_t    reg_bit_width;          /**< \brief �ӻ��Ĵ���λ�� ,��8λ��16λ����32λ */
    uint8_t    subaddr_count_flag;     /**< \brief �����ӵ�ַ������ʶ  */
    uint32_t    data_count;            /**< \brief ���ܻ����ֽ�ͳ�� (��ȥ�ӵ�ַ���ֽ���)*/
    uint16_t   subaddr_dev_flags;      /**< \brief �ӵ�ַ�豸��ʶ  */
    am_bool_t  reg_mode;               /**< \brief һ���ӵ�ַ��Ӧ�ڴ�ռ��С��ģʽ (8λ,16λ,32λ���߲�����) */
    uint32_t   reg_num;                /**< \brief �ӻ��Ĵ������� */

    am_i2c_slv_subaddr_reg_info_t     *reg_info;            /**< \brief �����豸�Ĵ����ڴ���׵�ַ */
    am_i2c_slv_subaddr_reg_info_t     *cur_reg_info;        /**< \brief ��ǰ�����ӵ�ַ��Ӧ����Ϣ */


    am_i2c_slv_subaddr_cb_funcs_t *p_cb_funs;    /**< \brief �����ӵ�ַ�Ļص�����  */
    void                          *p_arg;        /**< \brief �ص���������  */

    am_i2c_slv_device_t            i2c_slv_dev;  /**< \brief I2C�ӻ��豸 */
}am_i2c_slv_subaddr_device_t;

/**
 * \brief �����ӵ�ַ���豸��������
 *
 * \param[in] p_dev                 : ָ�����ӵ�ַ�ӻ��豸�����ṹ���ָ��
 * \param[in] handle                : ����豸������I2C��׼����������
 * \param[in] p_cb_funs             : �����û������Ļص�����
 * \param[in] p_arg                 : �ص���������
 * \param[in] dev_addr              : �ӻ��豸��ַ
 * \param[in] dev_flags             : �ӻ��豸���ԣ��磺�豸��ַ���ӵ�ַ��� �ȣ� ����I2C���豸���Ա�־������am_i2c_slv.h��
 * \param[in] p_reg_info            : ���豸�Ĵ����� ��Ϣ ��
 * \param[in] reg_num               : ���豸�Ĵ����� ���� ������ļĴ����ռ��С�ɲ��������������ֵΪ1����
 * \param[in] reg_mode              : ���豸�Ĵ�����ģʽ  ��ֵ�ο� ��\ref grp_i2c_slv_reg_mode
 *
 * \return ��
 *
 * \par ����
 * \code
 * #include "am_i2c_slv_subaddr.h"
 *
 *   static uint8_t   reg1[5];    //�ӵ�ַΪ0
 *   static uint16_t  reg2[10];   //�ӵ�ַΪ1
 *   static uint32_t  reg3[1];    //�ӵ�ַ λ2
 *
 *   static uint32_t  reg3_wr[1] = {0XFFFF0000}; //�Ĵ���3�Ķ�д������־ ����16λֻ������д
 *
 *   am_i2c_slv_subaddr_reg_info_t   i2c_slv_reg[3] =
 *   {
 *      { sizeof(reg1), reg1, NULL },
 *      { sizeof(reg2), reg2, NULL },
 *      { sizeof(reg3), reg3, reg3_wr},
 *   }
 *
 *   am_i2c_slv_subaddr_device_t  i2c_slv_dev;
 *   uint32_t reg_num = sizeof(i2c_slv_reg) / sizeof(am_i2c_slv_subaddr_reg_info_t );
 *
 *   am_i2c_slv_subaddr_mkdev( &i2c_slv_dev,
 *                              i2c_slv_handle,
 *                             &__g__cb_funs,
 *                             &i2c_slv_dev
 *                              0x55,
 *                              AM_I2C_SLV_ADDR_7BIT|AM_I2C_SLV_SUBADDR_1BYTE,
 *                              &i2c_slv_reg[0],
 *                              reg_num,
 *                              AM_I2C_SLV_REG_IRREGULAR);
 * \endcode
 *
 * \note ���� �����ӵ�ַ���豸ʱ���������  am_i2c_slv_setup ���� �����ӻ�����
 *       ͬʱ�ɵ��� am_i2c_slv_shutdown �رո��豸
 */
void am_i2c_slv_subaddr_mkdev( am_i2c_slv_subaddr_device_t   *p_dev,
                               am_i2c_slv_handle_t            handle,
                               am_i2c_slv_subaddr_cb_funcs_t *p_cb_funs,
                               void                          *p_arg,
                               uint16_t                       dev_addr,
                               uint16_t                       dev_flags,
                               am_i2c_slv_subaddr_reg_info_t *p_reg_info,
                               uint32_t                       reg_num,
                               uint8_t                        reg_mode);



/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2C_SLV_SUBADDR_H */

/* end of file */
