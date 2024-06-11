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
 * \brief I2C �ӻ�ģ�� TMP100 ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. ���Ӷ�Ӧ���š�
 *
 * \par Դ����
 * \snippet demo_std_i2c_slave_subaddr.c src_std_i2c_slave_subaddr
 *
 * \internal
 * \par Modification history
 * - 1.00  17-09-12  vir, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_i2c_slave_subaddr
 * \copydoc demo_std_i2c_slave_subaddr.c
 */

/** [src_std_i2c_slave_subaddr] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_i2c_slv_subaddr.h"

#define __I2C_SLV_DEV_ADDR   0X49     /**< \brief ���豸�ĵ�ַ */

/** \brief �Ĵ������� */
static uint8_t __reg1[6] = {0X11, 0X22, 0X33, 0X44, 0X55, 0X66};
static uint8_t __reg2[2] = {0X77, 0X88};
static uint8_t __reg3[6] = {0X01, 0X02, 0X03, 0X04, 0X05, 0X06};
static uint8_t __reg4[6] = {0X10, 0X20, 0X30, 0X40, 0X50, 0X60};

/** \brief �����ӵ�ַ�ļĴ�����Ϣ�ṹ�� */
static am_i2c_slv_subaddr_reg_info_t __g_i2c_slv_dev_reg[4] = {
    {sizeof(__reg1), __reg1, NULL},
    {sizeof(__reg2), __reg2, NULL},
    {sizeof(__reg3), __reg3, NULL},
    {sizeof(__reg4), __reg4, NULL},
};

/**
 * \brief �ص���������
 */
static void __i2c_slv_dev_tran_finish_callback (void     *p_arg,
                                                am_bool_t is_rx,
                                                uint32_t  reg_off,
                                                uint32_t  size);

/**
 * \brief �����ӵ�ַ�豸�Ļص����� �����ڷ���
 */static am_i2c_slv_subaddr_cb_funcs_t __g_tmp100_cb_funs = {
        NULL,
        __i2c_slv_dev_tran_finish_callback,
};

/**
 * \brief ������ӻ���д������ʱ����Ҫ�û�����
 */
static void __i2c_slv_dev_tran_finish_callback (void     *p_arg,
                                                am_bool_t is_rx,
                                                uint32_t  reg_off,
                                                uint32_t  size)
{

    /* do some thing */
}

/**
 * \brief �������
 */
void demo_std_i2c_slave_subaddr_entry (am_i2c_slv_handle_t handle)
{
    am_i2c_slv_subaddr_device_t    tmp100_dev;
    am_i2c_slv_subaddr_reg_info_t *p_tmp100_reg = &__g_i2c_slv_dev_reg[0];

    am_i2c_slv_subaddr_mkdev(&tmp100_dev,
                              handle,
                             &__g_tmp100_cb_funs,
                             &tmp100_dev,
                              __I2C_SLV_DEV_ADDR,
                              AM_I2C_SLV_ADDR_7BIT |
                              AM_I2C_SLV_GEN_CALL_ACK |
                              AM_I2C_SLV_SUBADDR_1BYTE |
                              AM_I2C_SLV_SUBADDR_SELF_INCREASING,
                              p_tmp100_reg,
                              4,
                              AM_I2C_SLV_REG_IRREGULAR);

    /* �������豸 */
    am_i2c_slv_setup(&tmp100_dev.i2c_slv_dev);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_std_i2c_slave_subaddr] */

/* end of file */
