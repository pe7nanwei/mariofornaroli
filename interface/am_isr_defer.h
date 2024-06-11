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
 * \brief �ж��ӳٴ����׼�ӿ�
 *
 *     ʵ��Ӧ���У�����ϣ��Ӳ���жϺ��������ܿ�Ľ�������ˣ��������ж�ʵ����
 * Ҫ��ɵıȽϺ�ʱ�Ĺ����ŵ��ж��ӳ��д���
 *     �ж��ӳ����������ʱ����ָ�����ȼ����������������ӵ���������У�ִ��
 * һ������ʱ�����ȴ����������ȡ��һ�����ȼ���ߵ�����ֵ��ע����ǣ����ȼ�
 * �ߵ������������ִ�У��������ܴ�ϵ�ǰ����ִ�е����ȼ��ϵ͵����񣬱���ȴ�
 * ��ǰ����ִ����ɡ�
 *     ����˳��ִ�У�Ϊ�˱�֤�����ж��ӳ�����Ҳ������ɣ����鲻Ҫ���ж��ӳ���
 * ��������ʱ��
 *
 * ʹ�ñ�������Ҫ��������ͷ�ļ�:
 * \code
 * #include "am_isr_defer.h"
 * \endcode
 *
 * \attention ʹ�ø�ģ�������Ҫ�ɾ����ƽ̨֧��
 *
 * \internal
 * \par modification history:
 * - 1.00 15-09-17  tee, first implementation
 * \endinternal
 */

#ifndef __AM_ISR_DEFER_H
#define __AM_ISR_DEFER_H

/**
 * \addtogroup am_if_isr_defer
 * \copydoc am_isr_defer.h
 * @{
 */
#include "am_list.h"
#include "am_jobq.h"
#include <string.h>

/** \brief �����ж��ӳ��������� */
typedef am_jobq_job_t am_isr_defer_job_t;

/** 
 * \brief �����ڴ���䣬������ɸ�ָ�����ͻ�ȡ��������Ϣ 
 *
 * Ӧ�ó��������������ͣ�ֱ�Ӹ���ʵ������ʹ�� AM_ISR_DEFER_PRIORITY_NUM_DEF() 
 * �궨�����ȼ����ɡ�
 */
struct am_isr_defer_info {
    am_jobq_queue_t       jobq_queue;
    unsigned int          priority_num;
    unsigned int         *p_bitmap_job;
    struct am_list_head   pri_heads[1]; 
};

/**
 * \brief �����ж��ӳ�ģ��ʹ�õ����ȼ���Ŀ
 *
 * ֻ��Ҫʹ�øú궨��һ�Σ�job����Ч���ȼ���Ϊ��0 ~ pri_num - 1
 *
 * \note ����ʱ�����붨��Ϊȫ�ֵģ������.c�ļ��С�
 */
#define AM_ISR_DEFER_PRIORITY_NUM_DEF(pri_num)                      \
    struct __isr_defer_jobqinfo{                                    \
        am_jobq_queue_t       jobq_queue;                           \
        unsigned int          priority_num;                         \
        unsigned int         *p_bitmap_job;                         \
        struct am_list_head   pri_heads[pri_num];                   \
        unsigned int          bitmap_job[((pri_num) + 31) >> 5];    \
    };                                                              \
    static struct __isr_defer_jobqinfo __isr_defer_jobq_info;       \
    static struct __isr_defer_jobqinfo __isr_defer_jobq_info =      \
                 {{0}, pri_num,__isr_defer_jobq_info.bitmap_job,};  \
    struct am_isr_defer_info *gp_isr_defer_info =         \
                 (struct am_isr_defer_info *)&__isr_defer_jobq_info
            
/**
 * \brief �����ص���������
 */
typedef void (*am_isr_defer_add_cb_t) (void *p_arg);
 
/**
 * \brief �ж��ӳ�ģ���ʼ����ʹ���ж��ӳ�ǰ����ʹ�øú�����ʼ��
 *
 * \param[in] pfn_cb : ����ӳ���ҵʱ�Ļص�������ÿ��ʹ�� am_isr_defer_job_add()
 *                     ����µ��ӳ���ҵʱ��������øú���
 * \param[in] p_arg  : �ص������û�����
 *
 * \return ��
 *
 * \note ͨ������£���ʹ��һ�����ȼ���͵�����ж��������ж��ӳ���ҵ�������
 * Ҫ��ÿ������ж��ӳ���ҵʱ����һ����Ӧ����жϣ����������Ϳ��Է��ڸûص���
 * ���С��ر�أ����ж��ӳ���ҵ������ѭ���д��������κ�����������������pfn_cb
 * ��������ΪNULL��
 *
 * \attention �ڳ�ʼ��ǰ�����ʹ�� AM_ISR_DEFER_PRIORITY_NUM_DEF() �������ȼ���Ŀ
 */
void am_isr_defer_init (am_isr_defer_add_cb_t pfn_cb, void *p_arg);

/**
 * \brief �ж��ӳ�������
 *
 * һ����������������ѭ���е��øú�������ѭ��û������������ʱ������ ��һ����
 * �ȼ���͵�����ж��д���
 */
int am_isr_defer_job_process (void);

/**
 * \brief ��ʼ��һ���ӳ�����
 *
 * �ڽ�һ��������뵽����֮ǰ��ȷ��ʹ�øú�����һ�������ʼ��
 *
 * \param[in] p_job : ָ�������ָ��
 * \param[in] func  : �����Ӧ�Ĵ�����
 * \param[in] p_arg : ��������Ӧ���û�����
 * \param[in] pri   : ��������ȼ�
 *
 * \retval AM_OK      ����ʼ���ɹ�
 * \retval -AM_EINVAL : ��������
 *
 * \note ʹ�øú���ǰ��������ʹ�� am_jobq_job_t ����һ��job����ʹ�øú�����ʼ��
 *       ���еĸ�����Ա����������ʵ�ʴ������ڶ��д���ʱ����˶���ʱ���붨��Ϊ
 *       ȫ�ֱ�����̬������
 */
void am_isr_defer_job_init (am_isr_defer_job_t  *p_job,
                            am_pfnvoid_t         func,
                            void                *p_arg,
                            uint16_t             pri);
                            
/**
 * \brief ��һ��������ӵ��ж��ӳٹ���������
 *
 * \param[in] p_job   : ָ�������ָ��
 *
 * \retval AM_OK      ������ɹ�
 * \retval -AM_EINVAL : ��������
 * \retval -AM_EBUSY  : ������ǰ�����Ѿ��ڶ����У��޷��ظ����
 * \retval -AM_EPERM  : isr deferģ��δ��ȷ��ʼ��������ʹ��
 */
int am_isr_defer_job_add (am_isr_defer_job_t *p_job);

/** @}  */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif  /* __AM_ISR_DEFER_H */

/* end of file */

