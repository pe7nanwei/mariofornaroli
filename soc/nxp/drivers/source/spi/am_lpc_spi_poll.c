/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 19-11-01  htf, first implementation.
 * \endinternal
 */

#include "am_clk.h"
#include "am_gpio.h"
#include "am_lpc_spi_poll.h"

#define __SPI_ST_IDLE  0
/*******************************************************************************
  ģ���ں�������
*******************************************************************************/
am_local void __spi_default_cs_ha    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_la    (am_spi_device_t *p_dev, int state);
am_local void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state);

am_local void __spi_cs_on  (am_lpc_spi_poll_dev_t *p_this, am_spi_device_t *p_dev);
am_local void __spi_cs_off (am_lpc_spi_poll_dev_t *p_this, am_spi_device_t *p_dev);

am_local void __spi_write_data (am_lpc_spi_poll_dev_t *p_dev);
am_local void __spi_read_data (am_lpc_spi_poll_dev_t *p_dev);

am_local int  __spi_hard_init (am_lpc_spi_poll_dev_t *p_this);
am_local int  __spi_config (am_lpc_spi_poll_dev_t *p_this);

am_local int  __spi_mst_sm_event (am_lpc_spi_poll_dev_t *p_dev);
/*******************************************************************************
  SPI������������
*******************************************************************************/
am_local int __spi_info_get (void *p_arg, am_spi_info_t   *p_info);
am_local int __spi_setup    (void *p_arg, am_spi_device_t *p_dev );
am_local int __spi_msg_start (void              *p_drv,
                              am_spi_device_t   *p_dev,
                              am_spi_message_t  *p_msg);

/**
 * \brief SPI ��������
 */
am_local am_const struct am_spi_drv_funcs __g_spi_drv_funcs = {
    __spi_info_get,
    __spi_setup,
    __spi_msg_start,
};

/******************************************************************************/

/**
 * \brief Ĭ��CS�ſ��ƺ������ߵ�ƽ��Ч
 */
am_local
void __spi_default_cs_ha (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 1 : 0);
}

/**
 * \brief Ĭ��CS�ſ��ƺ������͵�ƽ��Ч
 */
am_local
void __spi_default_cs_la (am_spi_device_t *p_dev, int state)
{
    am_gpio_set(p_dev->cs_pin, state ? 0 : 1);
}

/**
 * \brief Ĭ��CS�ſ��ƺ�������Ӳ�����п���
 */
am_local
void __spi_default_cs_dummy (am_spi_device_t *p_dev, int state)
{
    return;
}

/**
 * \brief CS���ż���
 */
am_local
void __spi_cs_on (am_lpc_spi_poll_dev_t *p_this, am_spi_device_t *p_dev)
{
    /* if last device toggled after message */
    if (p_this->p_tgl_dev != NULL) {

        /* last message on defferent device */
        if (p_this->p_tgl_dev != p_dev) {
            p_this->p_tgl_dev->pfunc_cs(p_this->p_tgl_dev, 0);
        }
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 1);
}

/**
 * \brief CS����ȥ��
 */
am_local
void __spi_cs_off (am_lpc_spi_poll_dev_t   *p_this,
                   am_spi_device_t  *p_dev)
{
    if (p_this->p_tgl_dev == p_dev) {
        p_this->p_tgl_dev = NULL;
    }

    p_dev->pfunc_cs(p_dev, 0);
}

/******************************************************************************/

/**
 * \brief SPI Ӳ����ʼ��
 */
am_local
int __spi_hard_init (am_lpc_spi_poll_dev_t *p_this)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    if (p_this == NULL) {
        return -AM_EINVAL;
    }

    /* �ȴ�SPI���У������������üĴ��� */
    while ((amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_IDLE) == 0);
    amhw_lpc_spi_cfg_set(p_hw_spi,
                         (AMHW_LPC_SPI_CFG_ENABLE |
                         AMHW_LPC_SPI_CFG_MASTER));

    /* ��ʼ������SPI */
    return AM_OK;
}

am_local
int __spi_info_get (void *p_arg, am_spi_info_t *p_info)
{
    am_lpc_spi_poll_dev_t  *p_this   = (am_lpc_spi_poll_dev_t *)p_arg;

    if (p_info == NULL) {
        return -AM_EINVAL;
    }

    /* ������ʵ��� PCLK */
    p_info->max_speed = am_clk_rate_get(p_this->p_devinfo->clk_id);
    p_info->min_speed = p_info->max_speed / 65536;
    p_info->features  = AM_SPI_CPHA  |
                        AM_SPI_CPOL  |
                        AM_SPI_NO_CS |
                        AM_SPI_LOOP  |
                        AM_SPI_CS_HIGH;   /* features */
    return AM_OK;
}

/******************************************************************************/
am_local
int __spi_config (am_lpc_spi_poll_dev_t *p_this)
{
    const am_lpc_spi_poll_devinfo_t *p_devinfo = p_this->p_devinfo;
    amhw_lpc_spi_t                 *p_hw_spi  = (amhw_lpc_spi_t *)(p_devinfo->spi_regbase);
    am_spi_transfer_t              *p_trans   = p_this->p_cur_trans;

    uint32_t                       mode_flag = 0;
    uint32_t                       div_val;

    /* ���Ϊ0��ʹ��Ĭ�ϲ���ֵ */
    if (p_trans->bits_per_word == 0) {
        p_trans->bits_per_word = p_this->p_cur_spi_dev->bits_per_word;
    }

    if (p_trans->speed_hz == 0) {
        p_trans->speed_hz = p_this->p_cur_spi_dev->max_speed_hz;
    }

    /* �����ֽ�����Ч�Լ�� */
    if (p_trans->bits_per_word > 16 || p_trans->bits_per_word < 4) {
        return -AM_EINVAL;
    }

    /* ���÷�Ƶֵ��Ч�Լ�� */
    if (p_trans->speed_hz > am_clk_rate_get(p_this->p_devinfo->clk_id) ||
        p_trans->speed_hz < (am_clk_rate_get(p_this->p_devinfo->clk_id) / 65536)) {
        return -AM_EINVAL;
    }

    /* ���ͺͽ��ջ�������Ч�Լ�� */
    if ((p_trans->p_txbuf == NULL) && (p_trans->p_rxbuf == NULL)) {
        return -AM_EINVAL;
    }

    /* �����ֽ������ */
    if (p_trans->nbytes == 0) {
        return -AM_ELOW;
    }

    /**
     * ���õ�ǰ�豸ģʽ
     */
    mode_flag = 0;

    if (p_this->p_cur_spi_dev->mode & AM_SPI_CPHA) {
        mode_flag |= AMHW_LPC_SPI_CFG_CHANGE;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_CPOL) {
        mode_flag |= AMHW_LPC_SPI_CFG_STAT_HIGH;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_CS_HIGH) {
        mode_flag |= AMHW_LPC_SPI_CFG_SPOL0_HIGH;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_LSB_FIRST) {
        mode_flag |= AMHW_LPC_SPI_CFG_LSB;
    }
    if (p_this->p_cur_spi_dev->mode & AM_SPI_LOOP) {
        mode_flag |= AMHW_LPC_SPI_CFG_LOOP;
    }

    /* ����ʱ��ֹͣ����  */
    amhw_lpc_spi_disable(p_hw_spi);

    /* ����ģʽ(���������������ӻ�ģʽ) */
    amhw_lpc_spi_cfg_set(p_hw_spi, (mode_flag               |
                                    AMHW_LPC_SPI_CFG_ENABLE |
                                    AMHW_LPC_SPI_CFG_MASTER));

    /* ���õ�֡����λ�� */
    amhw_lpc_spi_data_flen_set (p_hw_spi, p_trans->bits_per_word);

    /* ���÷�Ƶֵ����SPI���� */
    div_val = (am_clk_rate_get(p_this->p_devinfo->clk_id) / p_trans->speed_hz);
    amhw_lpc_spi_div_set(p_hw_spi, div_val);

    /* ���״̬λ */
    amhw_lpc_spi_stat_clear(p_hw_spi, AMHW_LPC_SPI_STAT_RXOVERRUN   |
                                      AMHW_LPC_SPI_STAT_TXUNDERRUN  |
                                      AMHW_LPC_SPI_STAT_SELNASSERT  |
                                      AMHW_LPC_SPI_STAT_SELNDEASSERT);

    /* ʹ��SPI���շ�������ж� */
    amhw_lpc_spi_int_enable(p_hw_spi,
                            AMHW_LPC_SPI_INTENSET_RXOVERRUN |
                            AMHW_LPC_SPI_INTENSET_TXUNDERRUN);

    return AM_OK;
}

/******************************************************************************/
am_local
int __spi_setup (void *p_arg, am_spi_device_t *p_dev)
{
    am_lpc_spi_poll_dev_t *p_this   = (am_lpc_spi_poll_dev_t *)p_arg;

    uint32_t max_speed, min_speed;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    /* Ĭ������Ϊ8λ����󲻳���16λ */
    if (p_dev->bits_per_word == 0) {
        p_dev->bits_per_word = 8;
    } else if (p_dev->bits_per_word > 16) {
        return -AM_ENOTSUP;
    }

    /* ���SPI���ʲ��ܳ�����ʱ�ӣ���С����С����ʱ��65536��Ƶ */
    max_speed = am_clk_rate_get(p_this->p_devinfo->clk_id);
    min_speed = max_speed / 65536;

    if (p_dev->max_speed_hz > max_speed) {
        p_dev->max_speed_hz = max_speed;
    } else if (p_dev->max_speed_hz < min_speed) {
        return -AM_ENOTSUP;
    }

    /* ��Ƭѡ���� */
    if (p_dev->mode & AM_SPI_NO_CS) {
        p_dev->pfunc_cs = __spi_default_cs_dummy;

    /* ��Ƭѡ���� */
    }  else {

        /* ���ṩ��Ĭ��Ƭѡ���� */
        if (p_dev->pfunc_cs == NULL) {

            /* Ƭѡ�ߵ�ƽ��Ч */
            if (p_dev->mode & AM_SPI_CS_HIGH) {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_LOW);
                p_dev->pfunc_cs = __spi_default_cs_ha;

            /* Ƭѡ�͵�ƽ��Ч */
            } else {
                am_gpio_pin_cfg(p_dev->cs_pin, AM_GPIO_OUTPUT_INIT_HIGH);
                p_dev->pfunc_cs = __spi_default_cs_la;
            }
        }
    }

    /* ���Ƭѡ�ź� */
    __spi_cs_off(p_this, p_dev);

    return AM_OK;
}

/******************************************************************************/

am_local
void __spi_write_data (am_lpc_spi_poll_dev_t *p_dev)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;

    /* tx_buf ��Ч */
    if (p_trans->p_txbuf != NULL) {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
            /** \brief ���������ݵĻ�ַ+ƫ�� */
            uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
            amhw_lpc_spi_txdat_write(p_hw_spi, *ptr);
        } else {
            uint16_t *ptr = (uint16_t *)((uint8_t *)(p_trans->p_txbuf)
                                                     + p_dev->data_ptr);
        }
    } else {
        /** \brief ������������Ч ֱ�ӷ�0, ������ȫ˫����ϵ�����ڶ���ʱ�����Ҫ�����ݣ�оƬ�Ż���һ��Ҫ��������  */
        amhw_lpc_spi_txdat_write(p_hw_spi, 0x0000);
    }
    /** \brief ��������ݵ�byte�� */
    p_dev->nbytes_to_recv = p_dev->p_cur_spi_dev->bits_per_word < 9 ? 1 : 2;
    p_dev->p_cur_msg->actual_length += p_dev->nbytes_to_recv;
}

am_local
void __spi_read_data (am_lpc_spi_poll_dev_t *p_dev)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);
    am_spi_transfer_t *p_trans  = p_dev->p_cur_trans;
    uint8_t *p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;

    /* rx_buf ��Ч */
    if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
             *p_buf8 = amhw_lpc_spi_rxdata_8bit_read(p_hw_spi);
        } else {
             *(uint16_t *)(p_buf8) = amhw_lpc_spi_rxdata_16bit_read(p_hw_spi);
        }
    /* rx_buf ��Ч���߲���Ҫ�������� */
    } else {
        if ((p_dev->p_cur_spi_dev->bits_per_word) <= 8) {
            (void)amhw_lpc_spi_rxdata_8bit_read(p_hw_spi);

        } else {
            (void)amhw_lpc_spi_rxdata_16bit_read(p_hw_spi);
        }
    }

    /* �Ѿ����ͻ���յ�����byte�� */
    p_dev->data_ptr += p_dev->nbytes_to_recv;
    p_dev->nbytes_to_recv = 0;
}

/**
 * \brief ��message�б��ͷȡ��һ�� transfer
 * \attention ���ô˺�����������������
 */
am_static_inline
struct am_spi_transfer *__spi_trans_out (am_spi_message_t *msg)
{
    if (am_list_empty_careful(&(msg->transfers))) {
        return NULL;
    } else {
        struct am_list_head *p_node = msg->transfers.next;
        am_list_del(p_node);
        return am_list_entry(p_node, struct am_spi_transfer, trans_node);
    }
}

/**
 * \brief SPI �������ݺ���
 */
am_local
int __spi_msg_start (void              *p_drv,
                     am_spi_device_t   *p_dev,
                     am_spi_message_t  *p_msg)
{
    am_lpc_spi_poll_dev_t *p_this   = (am_lpc_spi_poll_dev_t *)p_drv;
    amhw_lpc_spi_t      *p_hw_spi  = (amhw_lpc_spi_t *)(p_this->p_devinfo->spi_regbase);

    p_this->p_cur_spi_dev  = p_dev;                         /* ����ǰ�豸������Ϣ���� */
    p_this->p_cur_msg      = p_msg;                         /* ����ǰ�豸������Ϣ���� */
    p_this->nbytes_to_recv = 0;                             /* �������ַ�����0 */
    p_this->data_ptr       = 0;                             /* �ѽ����ַ�����0 */


    /* �豸��Ч�Լ�� */
    if ((p_drv              == NULL) ||
        (p_dev              == NULL) ||
        (p_msg              == NULL) ){
        return -AM_EINVAL;
    }

    /* ���������ɽ���λ */
    amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);

    p_this->busy = AM_TRUE;
    p_msg->status = -AM_EISCONN; /* �����Ŷ��� */

    /* ����״̬�� */
    return __spi_mst_sm_event(p_this);
}


/******************************************************************************/

/******************************************************************************/
/**
 * \brief  SPI ʹ��״̬������
 */
am_local
int __spi_mst_sm_event (am_lpc_spi_poll_dev_t *p_dev)
{
    amhw_lpc_spi_t *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);
    am_spi_message_t  *p_cur_msg   = NULL;
    p_cur_msg = p_dev->p_cur_msg;

    while (!(am_list_empty(&(p_cur_msg->transfers)))) {

        am_spi_transfer_t *p_cur_trans = __spi_trans_out(p_cur_msg);
        p_dev->p_cur_trans             = p_cur_trans;

        /* reset current data pointer */
        p_dev->data_ptr                = 0;
        p_dev->nbytes_to_recv          = 0;

        /* ����ô���ָ��SPI�ֽ�������  �������ж� �û��Զ�������  */
        if(p_dev->p_cur_trans->bits_per_word != 0){

            amhw_lpc_spi_data_flen_set (p_hw_spi, p_dev->p_cur_spi_dev->bits_per_word);
            p_dev->bef_bits_per_word = p_dev->p_cur_trans->bits_per_word;
        /* ����ô���Ĭ��SPI�ֽ�������  ���ϴδ��䱣���SPI�ֽ����� SPI �豸��ͬ  �������������  */
        }else if(p_dev->p_cur_trans->bits_per_word == 0 &&
               p_dev->bef_bits_per_word != p_dev->p_cur_spi_dev->bits_per_word){

            p_dev->bef_bits_per_word = p_dev->p_cur_spi_dev->bits_per_word;
            /* �ж�ʹ�ú��ִ��䷽ʽ   �ı�ʱ������������ */
            amhw_lpc_spi_data_flen_set (p_hw_spi, p_dev->p_cur_spi_dev->bits_per_word);
            p_dev->bef_bits_per_word = p_dev->p_cur_spi_dev->bits_per_word;
        }
        /* ����ô���ָ��SPI�ٶȴ���  �������ж� �û��Զ�������  */
        if(p_dev->p_cur_trans->speed_hz != 0){
            __spi_config(p_dev);
            p_dev->bef_speed_hz = p_dev->p_cur_trans->speed_hz;
        /* ����ô���Ĭ��SPI�ٶȴ���  ���ϴδ��䱣���SPI�ֽ����� SPI �豸��ͬ  �������������  */
        }else if(p_dev->p_cur_trans->speed_hz == 0 &&
                p_dev->bef_speed_hz != p_dev->p_cur_spi_dev->max_speed_hz ){
            /* ����SPI�������    �ı�ʱ������������     */
            __spi_config(p_dev);
            p_dev->bef_speed_hz = p_dev->p_cur_spi_dev->max_speed_hz;
        }

        /* CSѡͨ */
        __spi_cs_on(p_dev, p_dev->p_cur_spi_dev);

        while(p_dev->data_ptr < p_cur_trans->nbytes){

            if ((amhw_lpc_spi_stat_get(p_hw_spi) & AMHW_LPC_SPI_STAT_TXRDY)!= 0) {

                if (p_dev->p_cur_spi_dev->bits_per_word <= 8) {
                    if ((p_dev->data_ptr == (p_cur_trans->nbytes - 1))) {
                        amhw_lpc_spi_txctl_set(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                    } else {
                        amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                    }
                } else {
                    if ((p_dev->data_ptr == (p_cur_trans->nbytes - 2))) {
                        amhw_lpc_spi_txctl_set(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                    } else {
                        amhw_lpc_spi_txctl_clear(p_hw_spi, AMHW_LPC_SPI_TXDATCTL_EOT);
                    }
                }
                /* SPIд���� */
                __spi_write_data(p_dev);

                while(p_dev->nbytes_to_recv != 0){
                    /* SPI��ȡ���� */
                    __spi_read_data(p_dev);
                }
            }
        }
    }

    /* notify the caller  */
    if (p_cur_msg->pfn_complete != NULL) {
        p_cur_msg->pfn_complete(p_cur_msg->p_arg);
    }

    /* Ƭѡ�ر� */
    __spi_cs_off(p_dev, p_dev->p_cur_spi_dev);

    return AM_OK;
}

/******************************************************************************/

/**
 * \brief SPI ��ʼ��
 */
am_spi_handle_t am_lpc_spi_poll_init (am_lpc_spi_poll_dev_t            *p_dev,
                                      const am_lpc_spi_poll_devinfo_t  *p_devinfo)
{
    if (NULL == p_devinfo || NULL == p_dev ) {
        return NULL;
    }

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    p_dev->spi_serve.p_funcs = (struct am_spi_drv_funcs *)&__g_spi_drv_funcs;
    p_dev->spi_serve.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    p_dev->p_cur_spi_dev    = NULL;
    p_dev->p_tgl_dev        = NULL;
    p_dev->busy             = AM_FALSE;
    p_dev->p_cur_msg        = NULL;
    p_dev->p_cur_trans      = NULL;
    p_dev->data_ptr         = 0;
    p_dev->nbytes_to_recv   = 0;
    p_dev->state            = __SPI_ST_IDLE;     /* ��ʼ��Ϊ����״̬ */

    am_list_head_init(&(p_dev->msg_list));

    if (__spi_hard_init(p_dev) != AM_OK) {
        return NULL;
    }

    return &(p_dev->spi_serve);
}

/**
 * \brief SPI ȥ����ʼ��
 */
void am_lpc_spi_poll_deinit (am_spi_handle_t handle)
{
    am_lpc_spi_poll_dev_t *p_dev    = (am_lpc_spi_poll_dev_t *)handle;
    amhw_lpc_spi_t       *p_hw_spi = (amhw_lpc_spi_t *)(p_dev->p_devinfo->spi_regbase);

    if (NULL == p_dev) {
        return ;
    }

    p_dev->spi_serve.p_funcs = NULL;
    p_dev->spi_serve.p_drv   = NULL;

    /* ���� SPI */
    amhw_lpc_spi_disable(p_hw_spi);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}
/* end of file */
