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
 * \brief UART������ʵ�ֺ�����DMA  ˫����ģʽ��
 *
 * \internal
 * \par Modification history
 * - 1.01 18-12-13  htf, first implementation.
 * \endinternal
 */

/*******************************************************************************
includes
*******************************************************************************/

#include <am_kl26_uart_dma.h>
#include "am_int.h"
#include "am_clk.h"
#include "am_kl26_dma.h"
#include "kl26_periph_map.h"
#include "am_kl26_uart_dma.h"

/**
 * \brief ����ģʽ����ѯ���жϣ�����
 */
static int  __uart_dma_mode_set (am_kl26_uart_dma_dev_t  *p_dev, uint32_t new_mode);


static int uart_rx_dma_tran_cfg (am_kl26_uart_dma_dev_t   *p_dev,
                                 uint32_t                  dma_tran_len);
/**
 * \brief ����ģʽ�ж�ģʽ��������
 */
static void __uart_tx_handler (am_fsl_uart_dev_t *p_dev);
static void __uart_irq_handler (void *p_arg);
/**
 * \brief ��������
 */
static int  __uart_dma_opt_set (void *p_drv, uint32_t opts);


/* Kl26 ���������������� */
static int __uart_ioctl (void *p_drv, int, void *);

static int __uart_tx_startup (void *p_drv);

static int __uart_callback_set (void *p_drv,
                                int   callback_type,
                                void *pfn_callback,
                                void *p_arg);

static int __uart_poll_getchar (void *p_drv, char *p_char);

static int __uart_poll_putchar (void *p_drv, char outchar);


static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
    __uart_ioctl,
    __uart_tx_startup,
    __uart_callback_set,
    __uart_poll_getchar,
    __uart_poll_putchar,
};

static int count1 = 0,count2= 0;

/**
 * \brief ���ڷ����жϷ���
 */
void __uart_tx_handler (am_fsl_uart_dev_t *p_dev)
{
    amhw_fsl_uart_t *p_hw_uart = p_dev->p_devinfo->p_hw_uart;
    char             data;
    uint32_t         int_stat;

    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
        int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    }else{
        int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }

    if (((int_stat & AMHW_FSL_UART_INTSTAT_S1_TDRE) != 0) || /* �Ƿ�Ϊ����Tx�ж� */
        ((int_stat & AMHW_FSL_UART_INTSTAT_S1_IDLE) != 0)) {

        /* ��ȡ�������ݲ����� */
        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_fsl_uart_txdata_write(p_hw_uart, data);
        } else {
            /* û�����ݴ��;͹رշ����ж� */
            amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);

            /* ��ֹ��485���Ϳ������� */
            if (p_dev->p_devinfo->uart_int_485_send) {
                p_dev->p_devinfo->uart_int_485_send(AM_FALSE);
            }
        }
    }
}


/**
 * \brief ��ȡDMA��������
 */
static void __dma_buffer_data_get(void  *p_drv, int flag)
{
    int len = 0;
    am_kl26_uart_dma_dev_t *p_dev = (am_kl26_uart_dma_dev_t  *)p_drv;
    const am_kl26_uart_dma_devinfo_t *p_devinfo = p_dev->p_devinfo;
    amhw_kl26_dma_t                  *p_hw_dma = p_devinfo->p_hw_dma;

    len = p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dsr_bcr & 0xfffff;
    /* ��֤��ǰDMA�Ļ�������������  */
    if(len != (p_devinfo->dmabuffer_size / 2)){

        int key = am_int_cpu_lock();
        /* ֹͣDMA����  */
        p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dsr_bcr |= 1 << 24;
        /* ��д�����ֽ���  */
        p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dsr_bcr &= 0x00000;
        p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dsr_bcr |= (p_devinfo->dmabuffer_size / 2);
        /* ��flag = 2   ���ʾΪDMA���������жϣ��ڴ��������  ��Ҫ����DMA������������  �ô��ڲŻ��������� */
        if(flag == 2){
            /* ���¿������������� */
            p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dcr &= ~(0x40000000);
            p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dcr |= (0x40000000);
        }
        /* ����DMA����  */
        p_hw_dma->dma_chan[p_devinfo->dma_chan_rx].dma_dsr_bcr &= ~(1 << 24);

        am_int_cpu_unlock(key);

        /*�жϽ��յ����ݳ���*/
        len = (p_devinfo->dmabuffer_size / 2) - len;

        /* DMA����Ϊ��������������DMA���Զ���ƫ��Ϊ0�ĵ�ַ��ʼ�������  
         * ����ȡ�����ݵĵ�ַ�������õ��ܵĴ�С  ��ô���������Ҫ�����ν��ж�ȡ����һ��Ϊ��ǰ��λ���������������ƫ�Ƶ�ַ
         * �ڶ��ζ�ȡ����Ϊƫ��Ϊ0�ĵ�ַ���ܹ���Ҫ��ȡ�����ݼ�ȥ��һ��ȡ�������ݼ��ɡ�
         */
        if((p_dev->count + len ) > (p_devinfo->dmabuffer_size - 1)){
            am_rngbuf_put(&p_dev->rngbuf,
            (const char *)&p_dev->p_dma_buffer[p_dev->count],
                           p_dev->dma_size-p_dev->count);

            len = len - (p_dev->dma_size - p_dev->count);
            p_dev->count = 0;
        }
        am_rngbuf_put(&p_dev->rngbuf, (const char *)&p_dev->p_dma_buffer[p_dev->count], len);
        p_dev->count += len;
    }
}


void am_softimer_cb(void  *p_drv)
{
    int count;
    char data;
    am_kl26_uart_dma_dev_t *p_dev = (am_kl26_uart_dma_dev_t  *)p_drv;
    am_fsl_uart_dev_t      *p_uart_dev = &p_dev->uart_dev;
    count1++;
    am_softimer_stop(&p_dev->timer);
    __dma_buffer_data_get(p_drv, 1);
    count = am_rngbuf_nbytes(&p_dev->rngbuf);

    for( ; count > 0 ; count --){
        am_rngbuf_get(&p_dev->rngbuf, &data, 1);
        p_uart_dev->pfn_rxchar_put(p_uart_dev->rxput_arg, data);
    }
}

/**
 * \brief �豸���ƺ���
 *
 * ���а������û�ȡ�����ʣ�ģʽ���ã��ж�/��ѯ������ȡ֧�ֵ�ģʽ��Ӳ��ѡ�����õȹ��ܡ�
 *
 */
static int __uart_ioctl (void *p_drv, int request, void *p_arg)
{
    int                     status     =  AM_OK;
    am_kl26_uart_dma_dev_t *p_dev      = (am_kl26_uart_dma_dev_t *) p_drv;
    am_fsl_uart_dev_t      *p_uart_dev = &p_dev->uart_dev;

    switch (request) {

    /* ���������� */
    case AM_UART_BAUD_SET:

        if(p_uart_dev->p_devinfo->ver == AM_FSL_UART_VER0){
            status = amhw_fsl_uart_ver0_baudrate_set(p_uart_dev->p_devinfo->p_hw_uart,
                                     am_clk_rate_get(p_uart_dev->p_devinfo->clk_id),
                                     (uint32_t)p_arg);
        }else{
            status = amhw_fsl_uart_ver1_baudrate_set(p_uart_dev->p_devinfo->p_hw_uart,
                                      am_clk_rate_get(p_uart_dev->p_devinfo->clk_id),
                                     (uint32_t)p_arg);
        }


        if (status > 0) {
            p_uart_dev->baud_rate = status;
            status = AM_OK;
        } else {
            status = -AM_EIO;
        }
        break;

     /* �����ʻ�ȡ */
    case AM_UART_BAUD_GET:
        *(int *)p_arg = p_uart_dev->baud_rate;
        break;

    /* ģʽ���� */
    case AM_UART_MODE_SET:
        status = (__uart_dma_mode_set(p_dev, (int)p_arg) == AM_OK)
                 ? AM_OK : -AM_EIO;
        break;

    /* ģʽ��ȡ */
    case AM_UART_MODE_GET:
        *(int *)p_arg = p_uart_dev->channel_mode;
        break;

    /* ��ȡ���ڿ����õ�ģʽ */
    case AM_UART_AVAIL_MODES_GET:
        *(int *)p_arg = AM_UART_MODE_INT | AM_UART_MODE_POLL;
        break;

    /* ����ѡ������ */
    case AM_UART_OPTS_SET:
        status = (__uart_dma_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    /* ����ѡ���ȡ */
    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_uart_dev->options;
        break;
    default:
        status = -AM_EIO;
        break;
    }

    return (status);
}

/**
 * \brief �������ڷ���(�����ж�ģʽ)
 */
int __uart_tx_startup (void *p_drv)
{
    am_fsl_uart_dev_t   *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t     *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    /* ʹ��485���Ϳ������� */
    if (p_dev->p_devinfo->uart_int_485_send) {
        p_dev->p_devinfo->uart_int_485_send(AM_TRUE);
    }

    /* ʹ�ܷ����ж� */
    amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_TIE);

    return AM_OK;
}

/**
 * \brief �����жϷ���ص�����
 */
static int __uart_callback_set (void  *p_drv,
                                int    callback_type,
                                void  *pfn_callback,
                                void  *p_arg)
{
    am_fsl_uart_dev_t *p_dev = (am_fsl_uart_dev_t *)p_drv;

    switch (callback_type) {

    /* ���÷��ͻص������еĻ�ȡ�����ַ��ص����� */
    case AM_UART_CALLBACK_TXCHAR_GET:
        p_dev->pfn_txchar_get = (am_uart_txchar_get_t)pfn_callback;
        p_dev->txget_arg      = p_arg;
        return (AM_OK);

    /* ���ý��ջص������еĴ�Ž����ַ��ص����� */
    case AM_UART_CALLBACK_RXCHAR_PUT:
        p_dev->pfn_rxchar_put = (am_uart_rxchar_put_t)pfn_callback;
        p_dev->rxput_arg      = p_arg;
        return (AM_OK);

    /* ���ô����쳣�ص����� */
    case AM_UART_CALLBACK_ERROR:
        p_dev->pfn_err = (am_uart_err_t)pfn_callback;
        p_dev->err_arg = p_arg;
        return (AM_OK);

    default:
        return (-AM_ENOTSUP);
    }
}

/**
 * \brief ��ѯģʽ�·���һ���ַ�
*/
static int __uart_poll_putchar (void *p_drv, char outchar)
{
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t   *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    uint32_t  idle_stat;
    if(p_dev->p_devinfo->ver == AM_FSL_UART_VER0){
         idle_stat = (uint32_t)(amhw_fsl_uart_ver0_intstat_get(p_hw_uart)>>7);
    }else{
         idle_stat = (uint32_t)(amhw_fsl_uart_ver1_intstat_get(p_hw_uart)>>7);
    }

    /* ����ģ���Ƿ����, 0:æ; 1: ���� */
    if(((uint8_t)idle_stat & amhw_fsl_uart_stat1_tdre_get(p_hw_uart)) == 0) {
        return (-AM_EAGAIN);
    } else {
        /* ��Ϊ����ģʽ */
        if (p_dev->p_devinfo->uart_int_485_send != NULL) {
            /* set to transmit mode */
            p_dev->p_devinfo->uart_int_485_send(AM_TRUE);
        }
        /* ����һ���ַ� */
        amhw_fsl_uart_txdata_write(p_hw_uart, outchar);

        /* �ȴ����Է��� */
        if (p_dev->p_devinfo->uart_int_485_send) {
            /* �����485�������������ȴ���ǰ�ֽڷ�����ɲ��ܸı����ݷ���  */
            while(!amhw_fsl_uart_stat1_tc_get(p_hw_uart));
            /* ��Ϊ����ģʽ */
            p_dev->p_devinfo->uart_int_485_send(AM_FALSE);
        } else {
            while(!amhw_fsl_uart_stat1_tdre_get(p_hw_uart));
        }
    }
    return (AM_OK);
}


/**
 * \brief ��ѯģʽ�½����ַ�
 */
static int __uart_poll_getchar (void *p_drv, char *p_char)
{
    int                     len;
    uint8_t                *p_inchar   = (uint8_t *)p_char;
    am_kl26_uart_dma_dev_t *p_dev      = (am_kl26_uart_dma_dev_t *)p_drv;

    __dma_buffer_data_get(p_dev, 1);

    len = am_rngbuf_nbytes(&p_dev->rngbuf);
    if(len >0 ){
        len = am_rngbuf_get(&p_dev->rngbuf, (char *)p_inchar, 1);
        if(len == 1){
            return (AM_OK);
        }else{
            return (-AM_EAGAIN);
        }
    }else{
        return (-AM_EAGAIN);
    }
}

/**
 * \brief ���ô���ģʽ
 */
static int __uart_dma_mode_set (am_kl26_uart_dma_dev_t  *p_dev, uint32_t new_mode)
{
    am_fsl_uart_dev_t *p_uart_dev = &p_dev->uart_dev;
    amhw_fsl_uart_t   *p_hw_uart  = p_uart_dev->p_devinfo->p_hw_uart;

    /* ��֧������ģʽ */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }

    if (new_mode == AM_UART_MODE_INT) {

        am_int_connect(p_uart_dev->p_devinfo->inum, __uart_irq_handler, (void *)p_dev);
        amhw_fsl_uart_int_disable(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart, AMHW_FSL_UART_INT_ALL);
        amhw_fsl_uart_int_enable(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart, AMHW_FSL_UART_INT_C2_ILIE);
        /* ����UART0 ����Ҫ������������жϣ� ����DMA���� */
        if(p_hw_uart != KL26_UART0){
            amhw_fsl_uart_int_enable(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart, AMHW_FSL_UART_INT_C2_IRIE);
        }
        am_int_enable(p_uart_dev->p_devinfo->inum);

    } else {
        /* �ر����д����ж� */
        amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_ALL);
    }

    p_uart_dev->channel_mode = new_mode;

    return (AM_OK);
}

/**
 * \brief ����ѡ������
 */
static int __uart_dma_opt_set (void *p_drv, uint32_t options)
{
    uint8_t            cfg_flags = 0;
    am_fsl_uart_dev_t *p_dev     = (am_fsl_uart_dev_t *)p_drv;
    amhw_fsl_uart_t   *p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_uart = p_dev->p_devinfo->p_hw_uart;

    /* �ڸı�UART�Ĵ���ֵǰ ���շ��ͽ��� */
    amhw_fsl_uart_disable(p_hw_uart);

    /* �������ݳ��� */
    switch (options & AM_UART_CSIZE) {

    case AM_UART_CS8:
        cfg_flags &= ~(1 << 4);
        cfg_flags |= AMHW_FSL_UART_C1_M_8BIT;
        break;

    default:
        break;
    }

    /* ����ֹͣλ */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x01 << 5);
        cfg_flags |= AMHW_FSL_UART_BDH_SBNS_STOP_2;
    } else {
        cfg_flags &= ~(0x01 << 5);
        cfg_flags |= AMHW_FSL_UART_BDH_SBNS_STOP_1;
    }

    /* ���ü��鷽ʽ */
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x03 << 0);

        if (options & AM_UART_PARODD) {
            cfg_flags |= AMHW_FSL_UART_C1_PARITY_ODD;
        } else {
            cfg_flags |= AMHW_FSL_UART_C1_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x03 << 0);
        cfg_flags |= AMHW_FSL_UART_C1_PARITY_NO;
    }

    /* �������Ч���� */
    amhw_fsl_uart_stop_bit_set (p_hw_uart, (cfg_flags & 0x20));
    amhw_fsl_uart_data_mode_set(p_hw_uart, (cfg_flags & 0x10));
    amhw_fsl_uart_parity_set(p_hw_uart,    (cfg_flags & 0x03));

    amhw_fsl_uart_enable(p_hw_uart);

    p_dev->options = options;

    return (AM_OK);
}

/******************************************************************************
  UART interrupt request handler
******************************************************************************/
/**
 * \brief ���ڽ��տ��з���
 */
static void __uart_dma_irq_idle_handler (am_kl26_uart_dma_dev_t *p_dev)
{
    char               data;
    int                count      = 0;
    am_fsl_uart_dev_t *p_uart_dev = &p_dev->uart_dev;
    am_softimer_stop(&p_dev->timer);
    count1++;
    /* ������Ϊ�жϽ���     ��ѭ�������û����ݻ�ȡ�ص�����    ֱ�����ջ�����Ϊ��*/
    __dma_buffer_data_get(p_dev, 1);

    count = am_rngbuf_nbytes(&p_dev->rngbuf);

    for( ; count > 0 ; count --){
        am_rngbuf_get(&p_dev->rngbuf, &data, 1);
        p_uart_dev->pfn_rxchar_put(p_uart_dev->rxput_arg, data);
    }
}

/**
 * \brief �����жϷ�����
 */
void __uart_irq_handler (void *p_arg)
{
    am_kl26_uart_dma_dev_t *p_dev      = (am_kl26_uart_dma_dev_t *)p_arg;
    am_fsl_uart_dev_t      *p_uart_dev = (&p_dev->uart_dev);
    amhw_fsl_uart_t        *p_hw_uart  = p_uart_dev->p_devinfo->p_hw_uart;
    uint32_t  uart_int_stat;


    if(p_uart_dev->p_devinfo->ver == AM_FSL_UART_VER0){
        uart_int_stat = amhw_fsl_uart_ver0_intstat_get(p_hw_uart);
    }else{
        uart_int_stat = amhw_fsl_uart_ver1_intstat_get(p_hw_uart);
    }
    if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_IDLE) {
        /*���ڳ��������ж�˵���˴δ������     ��Դ������ݽ��д���*/
        if(p_hw_uart != KL26_UART0){
            /* �˾���벻��ɾ��   KL26��UART0ʱ������������ݼĴ�������������ж� */
            char a = p_hw_uart->data;
            //*((unsigned int *)0x4006A004) |= 0xc0;
        }
        __uart_dma_irq_idle_handler((void *)p_dev);
    }
    else if (uart_int_stat & AMHW_FSL_UART_INTSTAT_S1_TDRE) {
        __uart_tx_handler((am_fsl_uart_dev_t *)p_dev);
    } else  {

    }
    /* �����ж� */
    if ((p_uart_dev->other_int_enable & uart_int_stat) != 0) {

        uart_int_stat &= p_uart_dev->other_int_enable;

        if (p_uart_dev->pfn_err != NULL) {
            p_uart_dev->pfn_err(p_uart_dev->err_arg,
                           AM_FSL_UART_ERRCODE_UART_OTHER_INT,
                           (void *)uart_int_stat,
                           1);
        }
    }
}
/* DMA��������жϺ��� */
static void __uart_dma_isr_handler(void *p_arg , uint8_t flag)
{
    int  count = 0;
    char data;
    am_kl26_uart_dma_dev_t *p_dev = (am_kl26_uart_dma_dev_t  *)p_arg;
    am_fsl_uart_dev_t *p_uart_dev = &p_dev->uart_dev;
    am_softimer_stop(&p_dev->timer);
    __dma_buffer_data_get(p_arg,2);
    am_softimer_start(&p_dev->timer, 4);
    count = am_rngbuf_nbytes(&p_dev->rngbuf);
    count2 ++;
    for( ; count > 0 ; count --){
        am_rngbuf_get(&p_dev->rngbuf, &data, 1);
        p_uart_dev->pfn_rxchar_put(p_uart_dev->rxput_arg, data);
    }
}

static uint8_t uart_dma_src_request_set (amhw_fsl_uart_t   *p_hw_uart){
    if (p_hw_uart == KL26_UART0) {
        return DMA_REQUEST_MUX0_UART0RX;
    } else if (p_hw_uart == KL26_UART1) {
        return DMA_REQUEST_MUX0_UART1RX;
    } else {
        return DMA_REQUEST_MUX0_UART2RX;
    }
}

/**
 * \brief UART����DMA��������
 */
static int uart_rx_dma_tran_cfg (am_kl26_uart_dma_dev_t   *p_dev,
                                 uint32_t                  dma_tran_len)
{
    uint32_t flags;
    am_fsl_uart_dev_t *p_uart_dev = (am_fsl_uart_dev_t *)(&p_dev->uart_dev);
    amhw_fsl_uart_t   *p_hw_uart  = p_uart_dev->p_devinfo->p_hw_uart;
    const am_kl26_uart_dma_devinfo_t *p_devinfo = p_dev->p_devinfo;
    static amhw_kl26_dma_xfer_desc_t  desc;    /**< \brief DMA ���������� */

    /* DMA�������� */
    flags = KL26_DMA_DCR_PER_REQUEST_ENABLE     |  /* ��������Դʹ��        */
            KL26_DMA_DCR_SINGLE_TRANSFERS       |  /* ���δ���                    */
            KL26_DMA_DCR_AUTO_ALIGN_DISABLE     |  /* �Զ��������            */
            KL26_DMA_DCR_SOURCE_SIZE_8_BIT      |  /* Դ��ַ1�ֽڶ�ȡ     */
            KL26_DMA_DCR_DESTINATION_SIZE_8_BIT |  /* Ŀ�ĵ�ַ1�ֽ�д�� */
            KL26_DMA_DCR_REQUEST_NO_AFFECTED    |  /* ������Ӱ��                */
            KL26_DMA_DCR_NO_LINKING             |  /* ��ͨ������                */
            KL26_DMA_DCR_INTERRUTP_ENABLE       |  /* DMA�ж�ʹ��           */
            KL26_DMA_DCR_START_DISABLE ;           /* DMA��ʼ����ʹ��   */

    /* ����DMA�жϷ����� */
    am_kl26_dma_isr_connect(p_devinfo->dma_chan_rx, __uart_dma_isr_handler, (void *)p_dev);

    am_int_enable(p_devinfo->dma_chan_rx);

    am_kl26_dma_chan_cfg(p_devinfo->dma_chan_rx,
                         KL26_DMA_TRIGGER_DISABLE |            /**< \brief DMA����ģʽ */
                         uart_dma_src_request_set(p_hw_uart)); /**< \brief ����Դ      */

    /* ����ͨ�������� */
    am_kl26_dma_xfer_desc_build(&desc,                          /* ͨ��������   */
                      (uint32_t)&p_hw_uart->data,               /* Դ�����ݻ��� */
                       (uint32_t)p_dev->p_dma_buffer,           /* Ŀ�����ݻ��� */
                       (uint32_t)(p_devinfo->dmabuffer_size/2), /* �����ֽ���  �˴�����ΪDMA��������С��1/2��Ϊ��ʹDMA�ڽ��յ����趨��С��1/2ʱ�����������ж� */
                                 flags);                        /* ��������     */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    if (am_kl26_dma_chan_start(&desc,
                               KL26_DMA_PER_TO_MER,          /* ���赽 �ڴ�   */
                      (uint8_t)p_devinfo->dma_chan_rx) == AM_ERROR) {
        return AM_ERROR;
    }

    /* ����DMA���λ�������С   */
    amhw_kl26_dma_destination_buffer_set(p_devinfo->p_hw_dma,
                                         p_devinfo->dma_circular_size,
                                         p_devinfo->dma_chan_rx);

    return AM_OK;
}
/**
 * \brief Ĭ�ϻص�����
 *
 * \returns AW_ERROR
 */
static int __uart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

static void uart_hw_dma_init (am_kl26_uart_dma_dev_t   *p_dev)
{
    am_fsl_uart_dev_t *p_uart_dev =&p_dev->uart_dev;
    amhw_fsl_uart_t   *p_hw_uart  = p_uart_dev->p_devinfo->p_hw_uart;


    if(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart== KL26_UART0){
        amhw_fsl_uart_ver0_dma_rx_enable(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart);
    }else {
        amhw_fsl_uart_ver1_dma_rx_enable(p_dev->p_devinfo->p_uart_devinfo->p_hw_uart);
    }

    /* ��uart0����ʱDMA������Ҫʹ���ж� */
    if (p_hw_uart != KL26_UART0) {
       /* ʹ�ܽ����жϣ��ж��źŴ���DMA���� */
       amhw_fsl_uart_int_enable(p_hw_uart, AMHW_FSL_UART_INT_C2_IRIE);
    }

    /* ʹ�ܴ��� */
    amhw_fsl_uart_enable(p_hw_uart);
}

/**
 * \brief ���ڳ�ʼ������
 */
am_uart_handle_t am_uart_dma_init (
                     am_kl26_uart_dma_dev_t           *p_dev,
                     const am_kl26_uart_dma_devinfo_t *p_devinfo)
{
    uint32_t                      tmp;
    am_fsl_uart_dev_t            *p_uart_dev = &p_dev->uart_dev;
    amhw_fsl_uart_t              *p_hw_uart;
    const am_fsl_uart_devinfo_t  *p_uart_devinfo =
             (const am_fsl_uart_devinfo_t *)p_devinfo->p_uart_devinfo;

    if (p_devinfo == NULL || p_devinfo->p_uart_devinfo->p_hw_uart == NULL) {
        return NULL;
    }
    p_dev->p_dma_buffer     = p_devinfo->p_dma_buffer;

    p_dev->buffer_size      = p_devinfo->recbuffer_size;
    p_dev->p_rec_buffer     = p_devinfo->p_rec_buffer;
    p_dev->dma_size         = p_devinfo->dmabuffer_size;
    p_dev->count            = 0;

    p_dev->p_devinfo        = p_devinfo;
    p_uart_dev->p_devinfo   = p_devinfo->p_uart_devinfo;

    p_hw_uart = p_uart_dev->p_devinfo->p_hw_uart;
    /* ��ȡ���ò��� */
    p_uart_dev->p_devinfo         = (const  am_fsl_uart_devinfo_t *)p_uart_devinfo;
    p_uart_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;
    p_uart_dev->uart_serv.p_drv   = p_dev;
    p_uart_dev->baud_rate         = p_uart_devinfo->baud_rate;
    p_uart_dev->options           = 0;

    /* ��ʼ��Ĭ�ϻص����� */
    p_uart_dev->pfn_txchar_get    = (int (*) (void *, char*))__uart_dummy_callback;
    p_uart_dev->txget_arg         = NULL;
    p_uart_dev->pfn_rxchar_put    = (int (*) (void *, char ))__uart_dummy_callback;
    p_uart_dev->rxput_arg         = NULL;
    p_uart_dev->pfn_err           =
                          (int (*) (void *, int, void*, int))__uart_dummy_callback;

    p_uart_dev->err_arg           = NULL;

    p_uart_dev->other_int_enable  = p_uart_devinfo->other_int_enable  &
                                  ~(AMHW_FSL_UART_INT_C2_TCIE |
                                    AMHW_FSL_UART_INT_C2_IRIE |
                                    AMHW_FSL_UART_INT_C2_ILIE |
                                    AMHW_FSL_UART_INT_C2_TIE);

    if (p_uart_dev->p_devinfo->pfn_plfm_init) {
        p_uart_dev->p_devinfo->pfn_plfm_init();
    }

    /* ��ȡ�������ݳ�������ѡ�� */
    tmp = p_uart_devinfo->cfg_flags;
    tmp = (tmp >> 4) & 0x01;

    switch (tmp) {

    case 0:
        p_uart_dev->options |= AM_UART_CS7;
        break;

    case 1:
        p_uart_dev->options |= AM_UART_CS8;
        break;

    default:
        p_uart_dev->options |= AM_UART_CS8;
        break;
    }

    /* ��ȡ���ڼ��鷽ʽ����ѡ�� */
    tmp = p_uart_devinfo->cfg_flags;
    tmp = (tmp >> 0) & 0x03;

    if (tmp == 2) {
        p_uart_dev->options |= AM_UART_PARENB;
    } else if (tmp == 3) {
        p_uart_dev->options |= (AM_UART_PARENB | AM_UART_PARODD);
    }else{
    }
    /* ��ȡ����ֹͣλ����ѡ�� */
    if (p_uart_devinfo->cfg_flags & AMHW_FSL_UART_BDH_SBNS_STOP_2) {
        p_uart_dev->options |= AM_UART_STOPB;
    }else{

    }
    __uart_dma_opt_set (p_dev, p_uart_dev->options);

    /* ���ò����� */
    if(p_uart_devinfo->ver == AM_FSL_UART_VER0){
        p_uart_dev->baud_rate  = amhw_fsl_uart_ver0_baudrate_set(p_hw_uart,
                am_clk_rate_get(p_uart_dev->p_devinfo->clk_id),
                p_uart_devinfo->baud_rate);
    }else{
        p_uart_dev->baud_rate  = amhw_fsl_uart_ver1_baudrate_set(p_hw_uart,
                am_clk_rate_get(p_uart_dev->p_devinfo->clk_id),
                p_uart_devinfo->baud_rate);
    }

    am_softimer_init(&p_dev->timer, am_softimer_cb, (void *)p_dev);

    amhw_fsl_uart_int_disable(p_hw_uart, AMHW_FSL_UART_INT_ALL);

    /* Ĭ����ѯģʽ  */
    __uart_dma_mode_set(p_dev, AM_UART_MODE_POLL);

    am_rngbuf_init(&p_dev->rngbuf, (char *)p_dev->p_rec_buffer, p_dev->buffer_size);

    uart_hw_dma_init(p_dev);

    uart_rx_dma_tran_cfg(p_dev, p_dev->buffer_size);

    /* uartʹ�� */
    amhw_fsl_uart_enable(p_hw_uart);

    return &(p_dev->uart_dev.uart_serv);
}

/**
 * \brief DMA�����豸ȥ��ʼ��
 */
void am_uart_dma_deinit (am_fsl_uart_dev_t  *p_drv)
{
    am_kl26_uart_dma_dev_t *p_dev  = p_drv->uart_serv.p_drv;
    am_fsl_uart_dev_t *p_uart_dev  = &p_dev->uart_dev;
    amhw_fsl_uart_t   *p_hw_uart   = p_uart_dev->p_devinfo->p_hw_uart;
    p_uart_dev->uart_serv.p_funcs  = NULL;
    p_uart_dev->uart_serv.p_drv    = NULL;

    if (p_uart_dev->channel_mode == AM_UART_MODE_INT) {
        /* Ĭ��Ϊ��ѯģʽ */
        __uart_dma_mode_set(p_dev, AM_UART_MODE_POLL);
    }
    /* �رմ��� */
    amhw_fsl_uart_disable(p_hw_uart);
    am_kl26_dma_chan_stop(p_dev->p_devinfo->dma_chan_rx);
    am_kl26_dma_isr_disconnect(p_dev->p_devinfo->dma_chan_rx, NULL, NULL);

    if (p_uart_dev->p_devinfo->pfn_plfm_deinit) {
        p_uart_dev->p_devinfo->pfn_plfm_deinit();
    }

    am_int_disable(p_uart_dev->p_devinfo->inum);
}

/* end of file */

