/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.fsl.cn/
*******************************************************************************/

/**
 * \file
 * \brief I2C�ӻ�����������I2C�ӻ���׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 17-09-06  vir, first implementation
 * \endinternal
 */

#ifndef __AM_FSL_I2C_SLV_H
#define __AM_FSL_I2C_SLV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_int.h"
#include "am_i2c_slv.h"
#include "am_softimer.h"

/**
 * \addtogroup am_fsl_if_i2c_slv
 * \copydoc am_fsl_i2c_slv.h
 * @{
 */

/*! @name S - I2C Status register */
#define I2C_S_RXAK_MASK                          (0x1U)
#define I2C_S_IICIF_MASK                         (0x2U)
#define I2C_S_SRW_MASK                           (0x4U)
#define I2C_S_RAM_MASK                           (0x8U)
#define I2C_S_ARBL_MASK                          (0x10U)
#define I2C_S_BUSY_MASK                          (0x20U)
#define I2C_S_IAAS_MASK                          (0x40U)
#define I2C_S_TCF_MASK                           (0x80U)

/*! @name F - I2C Frequency Divider register */
#define I2C_F_ICR_MASK                           (0x3FU)
#define I2C_F_ICR_SHIFT                          (0U)
#define I2C_F_ICR(x)                             (((uint8_t)(((uint8_t)(x)) << I2C_F_ICR_SHIFT)) & I2C_F_ICR_MASK)
#define I2C_F_MULT_MASK                          (0xC0U)
#define I2C_F_MULT_SHIFT                         (6U)
#define I2C_F_MULT(x)                            (((uint8_t)(((uint8_t)(x)) << I2C_F_MULT_SHIFT)) & I2C_F_MULT_MASK)

/*! @name FLT - I2C Programmable Input Glitch Filter register */
#define I2C_FLT_STARTF_MASK                      (0x10U)
#define I2C_FLT_STOPF_MASK                       (0x40U)

#define KL16_I2C_RECEIVE_NAK_FLAG         I2C_S_RXAK_MASK          /*!< I2C receive NAK flag. */
#define KL16_I2C_INT_PENDING_FLAG         I2C_S_IICIF_MASK         /*!< I2C interrupt pending flag. */
#define KL16_I2C_TRANSFER_DIRECTION_FLAG  I2C_S_SRW_MASK           /*!< I2C transfer direction flag. */
#define kL16_I2C_RANGE_ADDRESS_MATCH_FLAG I2C_S_RAM_MASK           /*!< I2C range address match flag. */
#define kL16_I2C_ARDITRATION_LOST_FLAG    I2C_S_ARBL_MASK          /*!< I2C arbitration lost flag. */
#define kL16_I2C_BUSBUSY_FLAG             I2C_S_BUSY_MASK          /*!< I2C bus busy flag. */
#define kL16_I2C_ADDRESS_MATCH_FLAG       I2C_S_IAAS_MASK          /*!< I2C address match flag. */
#define kL16_I2C_TRANSFER_COMPLETE_FALG   I2C_S_TCF_MASK           /*!< I2C transfer complete flag. */
#define kL16_I2C_STOP_DETECT_FLAG         I2C_FLT_STOPF_MASK << 8  /*!< I2C stop detect flag. */
#define kL16_I2C_START_DETECT_FLAG        I2C_FLT_STARTF_MASK << 8 /*!< I2C start detect flag. */

/**
 * \brief I2C�豸��Ϣ�����ṹ��
 */
typedef struct am_fsl_i2c_slv_devinfo {

    /** \brief I2C �Ĵ������ַ */
	struct amhw_fsl_i2c  *i2c_regbase;

    /** \brief I2C ���������жϺ� */
    uint16_t  inum;

    uint32_t  clk_id;

    /* Set default SCL stop hold time to 4us which is minimum requirement in I2C spec. */
    uint32_t sclStopHoldTime_ns;

    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);

} am_fsl_i2c_slv_devinfo_t;


/**
 * \brief I2C�豸�ṹ��
 */
typedef struct am_fsl_i2c_slv_dev {

    /** \brief ��׼I2C���豸���� */
    am_i2c_slv_serv_t                  i2c_slv_serv;

   /** \brief �ӻ��豸,ֻ�ܴ�һ���ӻ���ַ,ֻ������һ���豸 */
    am_i2c_slv_device_t               *p_i2c_slv_dev[1];

    /** \brief ZLG���������Ĵӻ��������ɷŶ��ٸ��ӻ���ַ,�� p_i2c_slv_dev�����������һ��, */
    uint8_t                            fsl_i2c_slv_dev_num;

    /** \brief �㲥���� ��־ */
    am_bool_t                          is_gen_call;

    /** �����ʱ��,���ڳ�ʱ���� */
    am_softimer_t                      softimer;

    /** \brief ָ��I2C�豸��Ϣ��ָ�� */
    const am_fsl_i2c_slv_devinfo_t    *p_devinfo;

} am_fsl_i2c_slv_dev_t;



/**
 * \brief I2C��ʼ��
 *
 * \param[in] p_dev     : ָ���I2C�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ���I2C�豸��Ϣ�ṹ���ָ��
 *
 * \return ��I2C��׼����������
 */
am_i2c_slv_handle_t am_fsl_i2c_slv_init (am_fsl_i2c_slv_dev_t           *p_dev,
                                         const am_fsl_i2c_slv_devinfo_t *p_devinfo);

/**
 * \brief ���I2C��ʼ��
 * \param[in] handle : ����豸�����Ĵ�I2C��׼����������
 * \return ��
 */
void am_fsl_i2c_slv_deinit (am_i2c_slv_handle_t handle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ZLG_I2C_SLV_H */

/* end of file */
