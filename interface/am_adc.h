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
 * \brief ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.03 18-04-12  zcb, del am_adc_val_t.
 * - 1.02 15-12-07  hgo, del am_adc_connect().
 * - 1.01 15-01-15  hbt, add am_adc_global_read.
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

#ifndef __AM_ADC_H
#define __AM_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup am_if_adc
 * \copydoc am_adc.h
 * \{
 */

/**
 * \name ADC����ת���ı�־������am_adc_start()������flags����
 * @{
 */

/** 
 * \brief ת��������������
 *
 * ���ݻ�������������λ������ADCת��λ��ʱ�����ݵ�λ��0��
 */
#define AM_ADC_DATA_ALIGN_LEFT    0x01

/** 
 * \brief ת����������Ҷ��룬���ַ�ʽ�����ܹ�ȡ�ø�����ٶ�(Ĭ��)
 *
 * ���ݻ�������������λ������ADCת��λ��ʱ�����ݸ�λ��0��
 */
#define AM_ADC_DATA_ALIGN_RIGHT   0x00

/** @} */


/**
 * \brief ��������ɻص��������Ͷ���
 *
 *     ����ADCת��ʱ��ÿ������������һ����Ӧ�Ļ�������ɻص��������û���������
 * ���������øûص�������״̬����ֵ(state)�����˱����������ݵ���Ч��:
 *    - AM_OK        : ������ȷ����������ʹ��
 *    - AM_ERROR     : �������󣬸û�����������Ӧ�ö�����
 *
 *     ����ת������ǰӦ��ȷ��ת��������״̬ΪAM_OK�������ΪAM_OK�������еĺ���
 * ת�����Զ�ȡ����������ת����ͨ������£�ת��������������ڻ�������buf��С��
 * ʹ��buf�л���Ҫ��Ƶ�������ݴ���ʱ���Գ������ݾ�����ˡ��������󻺳�����buf��
 * С������buf�л���ʱ������
 */
typedef void (*am_adc_buf_cb_t) (void *p_arg, int state);

/**
 * \brief ת����ɻص��������Ͷ���
 *
 * ������ɻص�������һ�������и�����������������,�����������Ϊ����ת����ɣ�
 *  - ���������������������������ɼ�����ת�����
 *  - ������������ӵ�һ�������������һ�������������������Ϊ����ת�����
 * 
 *     �����������ʱ��״̬����ֵΪAM_OK��������ĳ��������ʱ���ݳ���Ҳ���
 * �øú������Ҵ��ݲ���ΪAM_ERROR,���������д����������ʱ��ת���Զ�ֹͣ�����
 * �������л���δת�������У�����Զ�ȡ�������ټ���ת����
 *
 * �ú�������Ϊ������ɵ�һ��֪ͨ�����ݴ���Ӧ����ÿ���������Ļص���������ɡ�
 */
typedef void (*am_adc_seq_cb_t) (void *p_arg, int state);

/**
 * \brief ADC����������
 */
typedef struct am_adc_buf_desc {
    
    /** 
     * \brief ADC���ݻ������������������ADCλ���йأ�
     *        ADCλ�������ɺ���am_adc_bits_get()��ȡ��
     *
     *    ADC bits    |    buffer type
     *  ------------- | -------------------
     *     1  ~  8    |  uint8_t/int8_t
     *     9  ~  16   |  uint16_t/int16_t
     *    17  ~  32   |  uint32_t/int32_t
     */
    void                   *p_buf;
    
    /** \brief ���ݻ������ĳ��� */
    uint32_t                length;
    
    /** \brief �û����������������Ļص����� */
    am_adc_buf_cb_t         pfn_complete;
    
    /** \brief �ص������Ĳ��� */
    void                    *p_arg;
} am_adc_buf_desc_t;
    
 
/**
 * \brief ADC��������
 */
struct am_adc_drv_funcs {
    
    /** \brief ����ADCת��        */
    int (*pfn_adc_start) (void                   *p_drv,
                          int                     chan,
                          am_adc_buf_desc_t       *p_desc,
                          uint32_t                desc_num,
                          uint32_t                count,
                          uint32_t                flags,
                          am_adc_seq_cb_t         pfn_callback,
                          void                   *p_arg);
     
    /** \brief ֹͣת��           */
    int (*pfn_adc_stop) (void *p_drv, int chan);
                          
    /** \brief ��ȡADC�Ĳ�����    */
    int (*pfn_rate_get) (void      *p_drv, 
                         int        chan,
                         uint32_t  *p_rate);

    /** \brief ����ADC�Ĳ����ʣ�ʵ�ʲ����ʿ��ܴ��ڲ��� */
    int (*pfn_rate_set) (void     *p_drv, 
                         int       chan, 
                         uint32_t  rate);
    
    /** \brief ��ȡADCת������ */
    uint32_t (*pfn_bits_get)(void *p_drv, int chan);

    /** \brief ��ȡADC�ο���ѹ */
    uint32_t (*pfn_vref_get)(void *p_drv, int chan);
};

/**
 * \brief ADC��׼����
 */
typedef struct am_adc_serv {

    /** \brief ָ��ADC����������ָ�� */
    const struct am_adc_drv_funcs *p_funcs;

    /** \brief ����������һ����ڲ��� */
    void                          *p_drv;
} am_adc_serv_t;

/** \brief ADC��׼�������������� */
typedef am_adc_serv_t *am_adc_handle_t;

/**
 * \brief ����һ��������������
 * 
 * \param[in] p_desc       : ָ��һ��ADC��������������ָ��
 * \param[in] p_buf        : ���ݻ�����������������ADCλ���й�
 * \param[in] length       : ���ݻ������ĳ��ȣ������˿��Դ�Ŷ��ٴ�ת�����
 * \param[in] pfn_complete : �������ݻ������������Ļص�����
 * \param[in] p_arg        : �ص������û��Զ������
 *
 * \note ����p_buf���ݻ����������ͣ���������Ӧ����ADCת��λ������,
 *       ADCλ�������ɺ���am_adc_bits_get()��ȡ��
 *
 *      ADC bits    |    buffer type
 *    ------------- | -------------------
 *       1  ~  8    |  uint8_t/int8_t
 *       9  ~  16   |  uint16_t/int16_t
 *      17  ~  32   |  uint32_t/int32_t
 */
am_static_inline
void am_adc_mkbufdesc (am_adc_buf_desc_t      *p_desc,
                       void                   *p_buf,
                       uint32_t                length,
                       am_adc_buf_cb_t         pfn_complete,
                       void                   *p_arg)
{
    p_desc->p_buf        = p_buf;
    p_desc->length       = length;
    p_desc->pfn_complete = pfn_complete;
    p_desc->p_arg        = p_arg;
}


/**
 * \brief ����ADCת��
 * 
 * \param[in] handle       �� ADC��׼����������
 * \param[in] chan         ����ת����ͨ��
 * \param[in] p_desc       ��ָ�򻺳���������ָ��
 * \param[in] desc_num     �������������ĸ���
 * \param[in] count        �����е�ת��������һ�����б�ʾdesc_numָ�������Ļ�
 *                           �����������������Ϊ0��ʾ��Ҫ�������ϵ�ת����
 * \param[in] flags        : ���ñ�־��"ADC����ת���ı�־"
 * \param[in] pfn_callback ��������ɻص�����
 * \param[in] p_arg        ��������ɻص������û��Զ������
 *
 * \retval  AM_OK     : ����ת���ɹ�
 * \retval -AM_ENXIO  : ָ����ͨ��������
 * \retval -AM_EINVAL : ��Ч����
 *
 * \par ����
 * \code
 *  am_adc_buf_desc_t   desc[2];                // ʹ����������������
 *  uint16_t            adc_val0[80];           // ���ݻ�����1
 *  uint16_t            adc_val1[80];           // ���ݻ�����2
 *  
 *  uint8_t             g_flag_complete = 0;    // ��ɱ�־
 *
 *  void adc_callback(void *p_arg, int state)
 *  {
 *      
 *      if (state != AM_OK) {
 *         return;               // ��������
 *      }
 *      if ((int)p_arg == 0) {    // ������0ת�����
 *         // ���� adc_val0[]�е�80������
 *      } else {
 *         // ���� adc_val1[]�е�80������
 *      } 
 *  }
 *
 *  void adc_seq_complete (void *p_arg, int state) 
 *  {
 *      g_flag_complete = 1; 
 *  }
 * 
 *  int main()
 *  {
 *     // ���û�����������0
 *     am_adc_mkbufdesc(&desc[0],
 *                      (void *)&adc_val0, // ���ݴ�Ż�����
 *                      80,                // ��С��80
 *                      adc_callback,      // ת����ɻص�����
 *                      (void *)0);        // ���ݲ���0
 *
 *     // ���û�����������1
 *     am_adc_mkbufdesc(&desc[1],
 *                      (void *)&adc_val1, // ���ݴ�Ż�����
 *                      80,                // ��С��80
 *                      adc_callback,      // ת����ɻص�����
 *                      (void *)1);        // ���ݲ���1
 *   
 *     am_adc_start(adc_handle,
 *                  0,
 *                  &desc[0],
 *                  2,                     // ����������Ϊ2
 *                  1,                     // �������н������һ��
 *                  0,                     // �������־�������Ҷ���
 *                  NULL,                  // �����������ص�����
 *                  NULL);                 // �޻ص���������
 *       
 *      while(g_flag_complete == 0);       // �ȴ�����ת�����
 *
 *      //...
 *      while(1) {
 *          //...
 *      }
 *  }
 *
 * \endcode
 *
 */
am_static_inline
int am_adc_start (am_adc_handle_t         handle,
                  int                     chan,
                  am_adc_buf_desc_t      *p_desc,
                  uint32_t                desc_num,
                  uint32_t                count,
                  uint32_t                flags,
                  am_adc_seq_cb_t         pfn_callback,
                  void                   *p_arg)
{
   return handle->p_funcs->pfn_adc_start(handle->p_drv,
                                         chan,
                                         p_desc,
                                         desc_num,
                                         count,
                                         flags,
                                         pfn_callback,
                                         p_arg);
}

/**
 * \brief ֹͣADCת��
 * 
 * \param[in] handle  : ADC��׼����������
 * \param[in] chan    ��ֹͣת����ͨ��
 *
 * \retval  AM_OK     : ֹͣת���ɹ�
 * \retval -AM_ENXIO  ��ָ����ͨ��������
 * \retval -AM_EINVAL ����Ч����
 */
am_static_inline
int am_adc_stop (am_adc_handle_t handle, int chan)
{
   return handle->p_funcs->pfn_adc_stop(handle->p_drv, chan);
}

/**
 * \brief ��ȡADCת������
 *
 * \param[in] handle       : ADC��׼����������
 * \param[in] chan         ��ֹͣת����ͨ��
 *
 * \retval     >0     : ADCת��λ��
 * \retval -AM_EINVAL ����Ч����
 */
am_static_inline
uint32_t am_adc_bits_get (am_adc_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_bits_get(handle->p_drv, chan);
}

/**
 * \brief ��ȡADC�ο���ѹ����λ��mV
 *
 * \param[in] handle  : ADC��׼����������
 * \param[in] chan    ��ֹͣת����ͨ��
 *
 * \retval     >0     : ADC�ο���ѹ
 * \retval -AM_EINVAL ����Ч����
 */
am_static_inline
int am_adc_vref_get (am_adc_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_vref_get(handle->p_drv, chan);
}

/**
 * \brief ��ȡADC�Ĳ����ʣ���λHz
 *
 * \param[in] handle  : ADC��׼����������
 * \param[in] chan    ��ֹͣת����ͨ��
 * \param[out] p_rate �� ��ȡ������
 *
 * \retval  AM_OK     : ֹͣת���ɹ�
 * \retval -AM_EINVAL ����Ч����
 */
am_static_inline
int am_adc_rate_get (am_adc_handle_t handle, int chan, uint32_t  *p_rate)
{
    return handle->p_funcs->pfn_rate_get(handle->p_drv, chan, p_rate);
}


/**
 * \brief ����ADC�Ĳ����ʣ���λHz
 *
 * \param[in]  handle : ADC��׼����������
 * \param[in]  chan   ��ֹͣת����ͨ��
 * \param[out] rate   �����ò�����
 *
 * \retval  AM_OK     : ֹͣת���ɹ�
 * \retval -AM_EINVAL ����Ч����
 */
am_static_inline
int am_adc_rate_set (am_adc_handle_t handle, int chan, uint32_t rate)
{
    return handle->p_funcs->pfn_rate_set(handle->p_drv, chan, rate);
}

/**
 * \brief ��ȡָ��ͨ����ADCת��ֵ����ȡ������ŷ��أ�
 *
 * \param[in] handle   : ADC��׼����������
 * \param[in] chan     : ADCͨ����
 * \param[in] p_val    : ת�������ŵĻ������������Ҷ���
 * \param[in] length   : �������ĳ���
 *
 * \retval   AM_OK     : �����ɹ�
 * \retval  -AM_ENXIO  : ADCͨ���Ų�����
 * \retval  -AM_EINVAL : ��Ч����
 */
int am_adc_read(am_adc_handle_t  handle, 
                int              chan, 
                void            *p_val,
                uint32_t         length);

/**
 * \brief ��ADCת�����ֵת��Ϊ��ѹֵ
 *
 * \param[in] handle : ADC��׼����������
 * \param[in] chan   : ADCͨ����
 * \param[in] val    : ת���������ֵ��ŵĻ�����
 *     
 * \note valӦΪ�Ҷ���ת���õ�������
 *
 * \note ��֧��Ĭ��������Ҷ���ת���õ������ݣ� ����ʹ�����·�ʽ�õ�
 *       ����ֵ��Ӧ�ĵ�ѹֵ��
 *  adc_bits = am_adc_bits_get(handle,chan);
 *  ref_mv   = am_adc_vref_get(handle,chan);
 *
 *  ��ѹֵ = ref_mv * ����ֵ / ((1 << adc_bits) - 1);
 */
#define AM_ADC_VAL_TO_MV(handle, chan, val)   \
    ((am_adc_vref_get(handle,chan) * val) /    \
    ((1 << am_adc_bits_get(handle,chan)) - 1))

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ADC_H */

/* end of file */
