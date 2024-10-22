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
 * \brief  NVIC�����������жϱ�׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 17-04-10  sdy, modified.
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */

#ifndef __AM_ARM_NVIC_H
#define __AM_ARM_NVIC_H

#include "hw/amhw_arm_nvic.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_arm_if_nvic
 * \copydoc am_arm_nvic.h
 * @{
 */

/**
 * \brief ϵͳ�쳣��Ŷ���
 */
#define    INUM_NMI             -14    /**< \brief ���������ж� */
#define    INUM_HARDFAULT       -13    /**< \brief Ӳ������ */
#define    INUM_MEMMANAGE       -12    /**< \brief �洢�������쳣��M0��M0+�޴��쳣�� */
#define    INUM_BUSFAULT        -11    /**< \brief �����쳣��M0��M0+�޴��쳣�� */
#define    INUM_USAGEFAULT      -10    /**< \brief Ӧ���쳣��M0��M0+�޴��쳣�� */
#define    INUM_SVCALL          -5     /**< \brief ϵͳ�����쳣 */
#define    INUM_PENDSV          -2     /**< \brief ������ϵͳ�����쳣 */
#define    INUM_SYSTICK         -1     /**< \brief ϵͳ�δ�ʱ���쳣 */

enum {
    AM_ARM_NVIC_CORE_M0,      /**< \brief M0 �ں� */
    AM_ARM_NVIC_CORE_M0PLUS,  /**< \brief M0+�ں� */
    AM_ARM_NVIC_CORE_M3,      /**< \brief M3 �ں� */
    AM_ARM_NVIC_CORE_M4,      /**< \brief M4 �ں� */
};

/**
 * \brief �жϷ�����Ϣ
 */
struct am_arm_nvic_servinfo {

    /** \brief ��ʼ�жϺ� */
    int inum_start;

    /** \brief ĩβ�жϺ� */
    int inum_end;
};

/** \brief �жϷ���������Ϣ */
struct am_arm_nvic_isr_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_isr;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};


/** \brief �ж��豸��Ϣ */
typedef struct am_arm_nvic_devinfo {
    
    /** \brief �жϷ�����Ϣʵ�� */
    const struct am_arm_nvic_servinfo int_servinfo;
    
    /** \brief �ں� */
    uint8_t core;

    /** \brief ���ȼ�λ�� */
    uint8_t prio_bits;

    /** \brief �������ȼ��� */
    int group;

    /** \brief ���ж����� */
    int input_cnt;

    /** \brief ISR ��Ϣӳ��(��С�� input_cnt һ��) */
    uint8_t *p_isrmap;

    /** \brief ISR ��Ϣ���� */
    int isrinfo_cnt;

    /** \brief ISR ��Ϣӳ���ڴ�(��С�� isrinfo_cnt һ��) */
    struct am_arm_nvic_isr_info *p_isrinfo;
    
    /** \brief ƽ̨��ʼ������ */
    void     (*pfn_plfm_init)(void);

    /** \brief ƽ̨���ʼ������ */
    void     (*pfn_plfm_deinit)(void);
    
} am_arm_nvic_devinfo_t;

/**
 * \brief �ж��豸ʵ�� 
 */
typedef struct am_arm_nvic_dev {
    
    /** \brief ָ���ж��豸��Ϣ��ָ�� */
    const am_arm_nvic_devinfo_t *p_devinfo;
    
    /** \brief ������Ч��־ */
    am_bool_t                    valid_flg;
    
} am_arm_nvic_dev_t;


/**
 * \brief	�����ж����ȼ�
 *
 * \param[in]	  inum             : �жϺ�
 * \param[in]	  preempt_priority : �����ȼ�
 * \param[in]     sub_priority     : �����ȼ������m0�ں˴�ֵ��Ч��
 *
 * \retval  AM_OK       : �����ɹ�
 * \retval -AM_EINVAL   : ��Ч����
 */
int am_arm_nvic_priority_set(int inum,
                             uint32_t preempt_priority,
                             uint32_t sub_priority);

/**
 * \brief �жϳ�ʼ�� 
 *
 * \param[in] p_dev     : ָ���ж��豸��ָ�� 
 * \param[in] p_devinfo : ָ���ж��豸��Ϣ��ָ�� 
 *
 * \retval  AM_OK       : �����ɹ� 
 * \retval -AM_EINVAL   : ��Ч���� 
 */
int am_arm_nvic_init (am_arm_nvic_dev_t           *p_dev,
                      const am_arm_nvic_devinfo_t *p_devinfo);

/**
 * \brief �ж�ȥ��ʼ��
 * \return  �� 
 */
void am_arm_nvic_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_ARM_NVIC_H */

/* end of file */
