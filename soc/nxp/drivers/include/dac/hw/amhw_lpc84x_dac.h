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
 * \brief ��ģת����DAC�������ӿ�
 * 1. Ƭ�Ͽɱ�����������(��ѹ����� 1mv ��  3300mv)
 * 2. ������ͣ��ģʽ�ľ�̬����
 * 3. ֧�� DMA
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-26  mkr, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC_DAC_H
#define __AMHW_LPC_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_fsl_if_dac
 * \copydoc amhw_fsl_dac.h
 * @{
 */

/**
 * \brief dac �Ĵ�����ṹ��
 */
typedef struct amhw_lpc_dac {
    __IO uint32_t cr;            /**< \brief DAC���ƼĴ���0     */
    __IO uint32_t ctrl;          /**< \brief DAC���ƼĴ��� 1     */
    __IO uint32_t cntval;        /**< \brief DAC���ƼĴ��� 2     */
} amhw_lpc_dac_t;


/**
 * \brief DAC ͨ�����
 */
#define AMHW_LPC_DAC0_CHAN_0          0      /**< \brief DAC ͨ�� 0 */

/**
 * \brief DAC ��������С
 */
#define AMHW_LPC_DAC_DATL_COUNT       2      /**< \brief DAC ��������С */


/**
 * \name DAC���ݼĴ�������λ�궨��
 * @{
 */

/**
 * \brief DAC �ο���ѹѡ������
 */
typedef enum amhw_lpc_dac_bias_sel {
    AMHW_LPC84X_DAC_UPDATA_1MHZ = 0,                    /**< \brief  DACREF_1 ��Ϊ�ο���ѹ */
	AMHW_LPC84X_DAC_UPDATA_400KHZ,                    /**< \brief  DACREF_2 ��Ϊ�ο���ѹ */
} amhw_lpc_dac_vref_sel_t;


/** \brief DACʹ��                                                        */

#define AMHW_LPC84x_DAC_DBLBUF_EN       1
#define AMHW_LPC84x_DAC_DBLBUF_DISEN    0

#define AMHW_LPC84x_DAC_CNT_EN          1
#define AMHW_LPC84x_DAC_CNT_DISEN       0

#define AMHW_LPC84x_DAC_DMA_EN          1
#define AMHW_LPC84x_DAC_DMA_DISEN       0
/** @} */

/**
 * \brief ����DAC���ֵ����
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] value    : �����ѹΪ(VREFP) * value/1024
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_cr_set (amhw_lpc_dac_t *p_hw_dac, uint32_t value)
{

    uint32_t reg = p_hw_dac->cr;

    AM_BIT_CLR_MASK(reg, AM_SBF(0x3ff, 6));
    AM_BIT_SET_MASK(reg, AM_SBF(value, 6));

    p_hw_dac->cr = reg;
}


/**
 * \brief ����DAC����ֵ����
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] value    : ����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_cntval_set (amhw_lpc_dac_t *p_hw_dac, uint32_t value)
{
    p_hw_dac->cntval = value - 1;
}


/**
 * \brief bias����ѡ��
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] bias      : AMHW_LPC84X_DAC_UPDATA_1MHZ ���� AMHW_LPC84X_DAC_UPDATA_1MHZ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_bias_set (amhw_lpc_dac_t *p_hw_dac, uint8_t bias)
{
	bias ? AM_BIT_SET(p_hw_dac->cr, 16):AM_BIT_CLR(p_hw_dac->cr, 16);
}

/**
 * \brief �Ƿ���DMA�ж�
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] int_dma   : AMHW_LPC84x_DAC_DMA_EN ���� AMHW_LPC84x_DAC_DMA_DIS
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_dma_int_req_set (amhw_lpc_dac_t *p_hw_dac,uint8_t int_dma)
{
	int_dma ? AM_BIT_SET(p_hw_dac->ctrl, 0):AM_BIT_CLR(p_hw_dac->ctrl, 0);
}

/**
 * \brief �Ƿ���dblbuf
 *
 * \param[in] p_hw_dac  : ָ��DAC�Ĵ������ָ��
 * \param[in] dblbuf    : AMHW_LPC84x_DAC_DBLBUF_EN ���� AMHW_LPC84x_DAC_DBLBUF_DIS
 * \param[in] dat       : datֵ
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_dblbuf_set (amhw_lpc_dac_t *p_hw_dac,uint8_t dblbuf)
{
	dblbuf ? AM_BIT_SET(p_hw_dac->ctrl, 1):AM_BIT_CLR(p_hw_dac->ctrl, 1);
}



/**
 * \brief �Ƿ��������ж�
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 * \param[in] cnt      �� AMHW_LPC84x_DAC_CNT_EN ���� AMHW_LPC84x_DAC_CNT_EN
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_cnt_set (amhw_lpc_dac_t *p_hw_dac,uint8_t cnt)
{
	cnt ? AM_BIT_SET(p_hw_dac->ctrl, 2):AM_BIT_CLR(p_hw_dac->ctrl, 2);
}


/**
 * \brief ����DAC���ܺ���
 *
 * \param[in] p_hw_dac : ָ��DAC�Ĵ������ָ��
 *
 * \return ��
 */
am_static_inline
void amhw_lpc84x_dac_cnt_en_set (amhw_lpc_dac_t *p_hw_dac,uint8_t dma_en)
{
	dma_en ? AM_BIT_SET(p_hw_dac->ctrl, 3):AM_BIT_CLR(p_hw_dac->ctrl, 3);
}

#endif /* __AMHW_FSL_DAC_H */

/* end of file */
