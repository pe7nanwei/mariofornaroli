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
 * \brief SDIO Ӳ�������ӿ�
 * \internal
 * \par Modification history
 * - 1.00 17-04-13  ari, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZLG_SDIO_H
#define __AMHW_ZLG_SDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "am_bitops.h"

#define ZMF159_SDIO_CMDCRC          (0x01 << 7)
#define ZMF159_SDIO_DATCRC          (0x01 << 6)
#define ZMF159_SDIO_AUTOCRC         (0x01 << 5)
#define ZMF159_SDIO_READ_MRBLOCK    (0x01 << 4)
#define ZMF159_SDIO_CMDRCRCE_RO     (0x01 << 1)
#define ZMF159_SDIO_DATRCRCE_RO     (0x01 << 0)


#define ZMF159_SDIO_INT_ALL            0x1ff
#define ZMF159_SDIO_INT_DATA1          (0x01 << 8)
#define ZMF159_SDIO_INT_CRC            (0x01 << 7)
#define ZMF159_SDIO_INT_CR_TIMEOUT     (0x01 << 6)
#define ZMF159_SDIO_INT_MB_TIMEOUT     (0x01 << 5)
#define ZMF159_SDIO_INT_MB_COMPLE      (0x01 << 4)
#define ZMF159_SDIO_INT_CMD_ERR        (0x01 << 3)
#define ZMF159_SDIO_INT_DAT_ERR        (0x01 << 2)
#define ZMF159_SDIO_INT_DAT_COMPLE     (0x01 << 1)
#define ZMF159_SDIO_INT_CMD_COMPLE     (0x01 << 0)

/**
 * \addtogroup amhw_zlg_sdio
 * \copydoc amhw_zlg_sdio.h
 * @{
 */

/**
 * \brief sdio structure of register
 */
typedef struct amhw_zlg_sdio {
    __IO uint32_t  mmc_ctrl;        /**< \brief sdio mmc_ctrl register */
    __IO uint32_t  mmc_io;          /**< \brief sdio mmc_io register */
    __IO uint32_t  mmc_bytecntl;    /**< \brief sdio mmc_bytecntl register */
    __IO uint32_t  mmc_tr_blockcnt; /**< \brief sdio interrupt enable register */
    __IO uint32_t  mmc_crcctl;      /**< \brief sdio mmc_crcctl register */
    __IO uint32_t  cmd_crc;         /**< \brief sdio cmd_crc register*/
    __IO uint32_t  dat_crcl;        /**< \brief sdio dat_crcl control */
    __IO uint32_t  dat_crch;        /**< \brief sdio dat_crch register */
    __IO uint32_t  mmc_port;
    __IO uint32_t  mmc_int_mask;    /**< \brief sdio mmc_int_mask number */
    __IO uint32_t  clr_mmc_int;     /**< \brief sdio clr_mmc_int register */
    __IO uint32_t  mmc_cardsel;     /**< \brief sdio mmc_cardsel control */
    __I  uint32_t  mmc_siq;         /**< \brief sdio mmc_siq control */
    __IO uint32_t  mmc_io_mbctl;    /**< \brief sdio mmc_io_mbctl control */
    __IO uint32_t  mmc_blockcnt;    /**< \brief sdio mmc_blockcnt control */
    __IO uint32_t  mmc_timeoutcnt;  /**< \brief sdio mmc_timeoutcnt control */
    __IO uint32_t  cmd_bufx[16];    /**< \brief sdio cmd_bufx control */
    __IO uint32_t  buf_ctll;        /**< \brief sdio buf_ctll control */
    __IO uint32_t  resiver[31];     /**< \brief sdio cmd_bufx control */
    __IO uint32_t  data_buf[128];   /**< \brief sdio data_buf control */
} amhw_zlg_sdio_t;

/**
 * \brief sdio��DAT��λ��
 */
typedef enum amhw_zlg_sdio_width {
    AMHW_ZLG_SDIO_WIDTH_1BIT      = 0x0,   /**< \brief 1λ */
	AMHW_ZLG_SDIO_WIDTH_4BIT      = 0x2,   /**< \brief 4λ */
} amhw_zlg_sdio_width_t;

/**
 * \brief sdio�ٶ�ģʽ����
 */
typedef enum amhw_zlg_sdio_speed_mode {
    AMHW_ZLG_SDIO_SPEED_MODE_LOW      = 0x0,   /**< \brief ����ģʽ */
	AMHW_ZLG_SDIO_SPEED_MODE_HIGH     = 0x1,   /**< \brief ����ģʽ */
} amhw_zlg_sdio_speed_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_port_clk_mode {
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_2BASECLK      = 0x0,   /**< \brief 1/2������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_4BASECLK      = 0x1,   /**< \brief 1/4������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_6BASECLK      = 0x2,   /**< \brief 1/6������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_8BASECLK      = 0x3,   /**< \brief 1/8������ʱ����ģʽ */
	AMHW_ZLG_SDIO_PORT_CLK_MODE_1_10BASECLK     = 0x4,   /**< \brief 1/10������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_12BASECLK     = 0x5,   /**< \brief 1/12������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_14BASECLK     = 0x6,   /**< \brief 1/14������ʱ����ģʽ */
    AMHW_ZLG_SDIO_PORT_CLK_MODE_1_16BASECLK     = 0x7,   /**< \brief 1/16������ʱ����ģʽ */
} amhw_zlg_port_clk_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_output_selection_mode {
    AMHW_ZLG_SDIO_OUTPUT_SELECTION_OD_MODE    = 0x1,   /**< \brief ���ʹ��*/
	AMHW_ZLG_SDIO_OUTPUT_SELECTION_PP_MODE    = 0x0,   /**< \brief ʹ��mmc_portģʽ */
} amhw_zlg_output_selection_mode_t;

/**
 * \brief sdio�˿�ʱ������
 */
typedef enum amhw_zlg_signal_mode {
	AMHW_ZLG_SDIO_SIGNAL_MMC_PORT_MODE    = 0x0,   /**< \brief ʹ��mmc_portģʽ */
    AMHW_ZLG_SDIO_SIGNAL_AUTO_MODE        = 0x1,   /**< \brief �Զ�����ģʽ*/
} amhw_zlg_signal_mode_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_sdio_port_operation_mode {
	AMHW_ZLG_SDIO_PORT_OPER_SPI_MODE    = 0x0,   /**< \brief ʹ��SPI_ģʽ */
	AMHW_ZLG_SDIO_PORT_OPER_SDIO_MODE   = 0x1,   /**< \brief SDIO/SD/MMCģʽ*/
} amhw_zlg_sdio_port_operation_mode_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_sdio_pclkg_mode {
	AMHW_ZLG_SDIO_PCLKG_SEL_REORSEND    = 0x0,   /**< \brief �˿ڲ���8����ʱ�� */
	AMHW_ZLG_SDIO_PCLKG_8FREE_CLK       = 0x1,   /**< \brief ѡ�������Ӧ/��������*/
} amhw_zlg_sdio_pclkg_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_resive_or_send_mode {
    AMHW_ZLG_SDIO_SEND_MODE       = 0x0,   /**< \brief ʹ�÷���ģʽ*/
	AMHW_ZLG_SDIO_RECEIVE_MODE     = 0x1,   /**< \brief ʹ�ý���ģʽ */
} amhw_zlg_resive_or_send_mode_t;


/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_transfer_mode {
	AMHW_ZLG_SDIO_WRITE_MODE      = 0x0,   /**< \brief дģʽ */
	AMHW_ZLG_SDIO_READ_MODE       = 0x1,   /**< \brief ��ģʽ*/
} amhw_zlg_transfer_mode_t;

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum amhw_zlg_clk_selete_bety {
	AMHW_ZLG_SDIO_UP_PUSH_DOWN_PULL      = 0x0,   /**< \brief дģʽ */
	AMHW_ZLG_SDIO_UP_PULL_DOWN_PUSH      = 0x1,   /**< \brief ��ģʽ*/
} amhw_zlg_clk_selete_bety_t;


/**
 * \brief ���ȴ�ʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_read_wait_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= (1ul << 10);
}

/**
* \brief ���ȴ����ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_read_wait_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1ul << 10);
}

/**
 * \brief �ж�ʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_int_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= (1 << 9);
}

/**
* \brief �жϽ��ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_int_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1 << 9);
}

/**
 * \brief SDIOʹ�ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_mode_enable (amhw_zlg_sdio_t              *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl |= (1 << 8);
}

/**
* \brief SDIO���ܺ���
*
* \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
*
* \return ��
*/
am_static_inline
void amhw_zlg_sdio_mode_disable (amhw_zlg_sdio_t             *p_hw_sdio)
{
	p_hw_sdio->mmc_ctrl &= ~(1 << 8);
}

/**
 * \brief ����λ�������ܺ���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] width    p_hw_sdio ���ƼĴ���λ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_bus_width_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_width_t width)
{

	if (width) {
		p_hw_sdio->mmc_ctrl |= (1 << 7);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 7);
	}
}

/**
 * \brief ����ѡ���亯��
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƴ�������ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_speed_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_speed_mode_t mode)
{

	if (mode) {
		p_hw_sdio->mmc_ctrl |= (1 << 6);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 6);
	}
}

/**
 * \brief ����ѡ�����ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ���CLK����ѡ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_prot_clk_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_port_clk_mode_t speed)
{
	p_hw_sdio->mmc_ctrl |= (speed << 3);
}

/**
 * \brief ������ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ����������ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_output_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_output_selection_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 2);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 2);
	}
}


/**
 * \brief �ź�ѡ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λ�ж�����ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_signal_mode_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_signal_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 1);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 1);
	}
}

/**
 * \brief �˿�ģʽѡ��λ���ú���
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λ�˿�ģʽö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_port_operation_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_sdio_port_operation_mode_t mode)
{
	if (mode) {
	    p_hw_sdio->mmc_ctrl |= (1 << 0);
	} else {
		p_hw_sdio->mmc_ctrl &= ~(1 << 0);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] permit   SDIO ���ƼĴ�����λcmd��ֹ��־
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_cmd12_io_flag_set (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t cmd_stop)
{
	if (cmd_stop) {
	    p_hw_sdio->mmc_io |= (1 << 9);
	} else {
		p_hw_sdio->mmc_io &= ~(1 << 9);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return AM_TRUE  ��cmd12/IO��ֹ����
 *         AM_FALSE ����cmd12/IO��ֹ����
 */
am_static_inline
am_bool_t amhw_zlg_sdio_cmd12_io_flag_get (amhw_zlg_sdio_t *p_hw_sdio)
{
    if ((p_hw_sdio->mmc_io) & (1 << 9)) {
    	return AM_TRUE;
    } else {
    	return AM_FALSE;
    }
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] flg       AM_TRUE  ��ǰָ�������ݿ�
 *                      AM_FALSE ��ǰָ��󲻸����ݿ�
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_cmdch_flag_set (amhw_zlg_sdio_t *p_hw_sdio,
                                   am_bool_t        flg)
{
    AM_BIT_MODIFY(p_hw_sdio->mmc_io, 8, flg);
}

/**
 * \brief ʹ�ܵ������ݿ�
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_attoclkg_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= (1 << 7);
}

/**
 * \brief ���ܵ������ݿ�
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_attoclkg_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io &= ~(1 << 7);
}


/**
 * \brief ����������Զ�������Ӧ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_enrresp_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= (1 << 6);
}

/**
 * \brief ����������Զ�������Ӧ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_enrresp_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io &= ~(1 << 6);
}



am_static_inline
void amhw_zlg_sdio_out_8nullclk (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= ((1ul << 5));
}


am_static_inline
void amhw_zlg_sdio_get_cid_csd(amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->mmc_io |= (1ul << 4);
}

/**
 * \brief ���ö˿�ʱ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ����˿�ʱ��ѡ��ö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_pclkg_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_resive_or_send_mode_t mode)
{
	AM_BIT_MODIFY(p_hw_sdio->mmc_io, 3, mode);
}

/**
 * \brief �Ƿ�ʹ���Զ���Ӧ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autotr_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t flg)
{
    AM_BIT_MODIFY(p_hw_sdio->mmc_io, 2, flg);
}

/**
 * \brief �����Զ���Ӧ����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autotr_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
		p_hw_sdio->mmc_io &= ~(1 << 2);
}

/**
 * \brief ���ö�дģʽ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 * \param[in] mode   SDIO ���ƼĴ�����дö��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_transfdir_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_transfer_mode_t mode)
{
	if (mode == AMHW_ZLG_SDIO_READ_MODE) {
	    p_hw_sdio->mmc_io |= (1ul << 1);
	} else {
		p_hw_sdio->mmc_io &= ~(1ul << 1);
	}
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autodattr_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	    p_hw_sdio->mmc_io |= (1ul << 0);
}

/**
 * \brief
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_autodattr_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
		p_hw_sdio->mmc_io &= ~(1ul << 0);
}


/**
 * \brief ���ó�ʼ�����ֽڼ���ֵ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_cnt (amhw_zlg_sdio_t *p_hw_sdio, uint16_t cnt)
{
	p_hw_sdio->mmc_bytecntl = cnt;
}

/**
 * \brief ��ȡ�����ֽڼ���ֵ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��ȡ���ļ���ֵ
 */
am_static_inline
uint16_t amhw_zlg_sdio_get_cnt (amhw_zlg_sdio_t *p_hw_sdio)
{
	return p_hw_sdio->mmc_bytecntl & 0xffff ;
}

/**
 * \brief ��ȡ�����ֽڼ���ֵ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_get_blockcnt (amhw_zlg_sdio_t *p_hw_sdio, uint16_t *cnt)
{
	*cnt = p_hw_sdio->mmc_blockcnt & 0xffff ;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_crcctl_enable (amhw_zlg_sdio_t *p_hw_sdio, uint8_t flags)
{
	p_hw_sdio->mmc_crcctl = (p_hw_sdio->mmc_crcctl & (~flags)) | flags;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_crcctl_disable (amhw_zlg_sdio_t *p_hw_sdio, uint8_t flags)
{
	p_hw_sdio->mmc_crcctl = (p_hw_sdio->mmc_crcctl & (~flags));
}


/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_get_cmdcrc (amhw_zlg_sdio_t *p_hw_sdio, uint8_t *cmdcrc)
{
	*cmdcrc = p_hw_sdio->cmd_crc & 0x7f ;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_get_datcrc (amhw_zlg_sdio_t *p_hw_sdio, uint16_t *dat_crc)
{
	*dat_crc = (p_hw_sdio->dat_crcl | 0xff) | ((p_hw_sdio->dat_crch | 0xff) << 8);
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_autotime_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t is_enable)
{
	is_enable? (p_hw_sdio->mmc_port |= (1 << 4)) : (p_hw_sdio->mmc_port &= ~(1 << 4));
}

/**
 * \brief ���ó�ʼ�����ֽڼ���ֵ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_outtime_cnt (amhw_zlg_sdio_t *p_hw_sdio, uint8_t cnt)
{
	cnt = cnt | 0xf;
	p_hw_sdio->mmc_port = (p_hw_sdio->mmc_port & (~cnt)) | cnt;
}

/**
 * \brief ���ó�ʼ�����ֽڼ���ֵ
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_get_outtime_cnt (amhw_zlg_sdio_t *p_hw_sdio, uint8_t *cnt)
{
	*cnt = p_hw_sdio->mmc_port & 0xf;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_int_enable (amhw_zlg_sdio_t *p_hw_sdio, uint8_t flags)
{
	p_hw_sdio->mmc_int_mask = (p_hw_sdio->mmc_int_mask & (~flags)) | flags;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_int_disable (amhw_zlg_sdio_t *p_hw_sdio, uint8_t flags)
{
	p_hw_sdio->mmc_int_mask = (p_hw_sdio->mmc_int_mask & (~flags));
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_get_int_status (amhw_zlg_sdio_t *p_hw_sdio, uint16_t *status)
{
	*status = p_hw_sdio->clr_mmc_int & 0x1ff;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_clr_int_status (amhw_zlg_sdio_t *p_hw_sdio, uint16_t flags)
{
	p_hw_sdio->clr_mmc_int = (p_hw_sdio->clr_mmc_int | (flags));
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_cardctrl_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t is_enable)
{
	is_enable? (p_hw_sdio->mmc_cardsel |= (1 << 7)) : (p_hw_sdio->mmc_cardsel &= ~(1 << 7));
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_cardclk_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t is_enable)
{
	is_enable? (p_hw_sdio->mmc_cardsel |= (1 << 6)) : (p_hw_sdio->mmc_cardsel &= ~(1 << 6));
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_set_cardclk_div (amhw_zlg_sdio_t *p_hw_sdio, uint8_t clk_div)
{
	clk_div &= 0x3f;

	p_hw_sdio->mmc_cardsel = (p_hw_sdio->mmc_cardsel & (~clk_div)) | clk_div;
}

/**
 * \brief ����CRC����
 *
 * \param[in] p_hw_sdio ָ�� amhw_zlg_sdio_t �ṹ��ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_zlg_sdio_clk_selete_bety_set (amhw_zlg_sdio_t *p_hw_sdio, amhw_zlg_clk_selete_bety_t flag)
{
	flag? (p_hw_sdio->mmc_io_mbctl |= (1ul << 3)) : (p_hw_sdio->mmc_io_mbctl &= ~(1ul << 3));
}

am_static_inline
void amhw_zlg_sdio_nblocks_cmd_tranfer_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t flag)
{
	flag? (p_hw_sdio->mmc_io_mbctl |= (1ul << 2)) : (p_hw_sdio->mmc_io_mbctl &= ~(1ul << 2));
}

am_static_inline
void amhw_zlg_sdio_nblocks_auto_tranfer_enable (amhw_zlg_sdio_t *p_hw_sdio, am_bool_t flag)
{
	flag? (p_hw_sdio->mmc_io_mbctl |= (1ul << 0)) : (p_hw_sdio->mmc_io_mbctl &= ~(1ul << 0));
}

am_static_inline
void amhw_zlg_sdio_nblocks_tranfer_dir_set (amhw_zlg_sdio_t         *p_hw_sdio,
                                            amhw_zlg_transfer_mode_t trans_dir)
{
    AM_BIT_MODIFY(p_hw_sdio->mmc_io_mbctl, 1, trans_dir);
}

am_static_inline
void amhw_zlg_sdio_nblocks_cnt_tranfer_set (amhw_zlg_sdio_t *p_hw_sdio, uint16_t cnt)
{
	p_hw_sdio->mmc_blockcnt = cnt;
}

am_static_inline
void amhw_zlg_sdio_set_tranfer_timeout (amhw_zlg_sdio_t *p_hw_sdio, uint8_t time)
{
	p_hw_sdio->mmc_timeoutcnt = time;
}

am_static_inline
void amhw_zlg_sdio_write_cmd (amhw_zlg_sdio_t *p_hw_sdio, uint8_t i,  uint8_t cmd_data)
{
    p_hw_sdio->cmd_bufx[i] = cmd_data;
}

am_static_inline
uint8_t amhw_zlg_sdio_read_cmd (amhw_zlg_sdio_t *p_hw_sdio, uint8_t i)
{
    return (uint8_t)(p_hw_sdio->cmd_bufx[i] & 0xff);
}


am_static_inline
void amhw_zlg_sdio_clr_databuf (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->buf_ctll |= (1 << 15) ;
}

am_static_inline
void amhw_zlg_sdio_dma_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->buf_ctll |= (1 << 14);
}

am_static_inline
void amhw_zlg_sdio_dma_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->buf_ctll &= ~(1 << 14);
}

am_static_inline
void amhw_zlg_sdio_fifo_status_enable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->buf_ctll |= (1u << 12);
}

am_static_inline
void amhw_zlg_sdio_fifo_status_disable (amhw_zlg_sdio_t *p_hw_sdio)
{
	p_hw_sdio->buf_ctll &= ~(1u << 12);
}

/**
 * \brief sdio�˿ڲ���ģʽѡ��
 */
typedef enum {
    AMHW_ZLG_SDIO_BUF_DIR_READ       = 0x0,   /**< \brief ��ģʽ*/
    AMHW_ZLG_SDIO_BUF_DIR_WRITE      = 0x1,   /**< \brief дģʽ */
} amhw_zlg_sdio_buf_dir_t;

am_static_inline
void amhw_zlg_sdio_buf_dir_set (amhw_zlg_sdio_t        *p_hw_sdio,
                                amhw_zlg_sdio_buf_dir_t dir)
{
    AM_BIT_MODIFY(p_hw_sdio->buf_ctll, 11, dir);
}

am_static_inline
am_bool_t amhw_zlg_sdio_check_fifo_isempty (amhw_zlg_sdio_t *p_hw_sdio)
{
	return (p_hw_sdio->buf_ctll & 0x2)? AM_TRUE : AM_FALSE;
}

am_static_inline
am_bool_t amhw_zlg_sdio_check_fifo_isfull (amhw_zlg_sdio_t *p_hw_sdio)
{
	return (p_hw_sdio->buf_ctll & 0x1)? AM_TRUE : AM_FALSE;
}

am_static_inline
void amhw_zlg_sdio_data_buf_write (amhw_zlg_sdio_t *p_hw_sdio, uint32_t data)
{
    p_hw_sdio->data_buf[0] = data;
}

am_static_inline
uint32_t amhw_zlg_sdio_data_buf_read (amhw_zlg_sdio_t *p_hw_sdio)
{
    return p_hw_sdio->data_buf[0];
}

#endif

/* end of file */
