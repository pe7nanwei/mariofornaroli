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
 * - 1.00 19-01-22  bzq, first
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_fsl_i2c.h"
#include "am_fsl_i2c_slv.h"
#include "am_clk.h"
#include "string.h"
/*******************************************************************************
  ��������
*******************************************************************************/

/** \brief I2CӲ����ʼ�� */
static int __i2c_slv_hard_init(am_fsl_i2c_slv_dev_t *p_dev);

/** \brief I2C�жϴ����� */
static void __i2c_slv_irq_handler (void *p_arg);

/** \brief ����I2C�ӻ��豸 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev);

/** \brief �ر� I2C�ӻ��豸 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev);

/** \brief ��ȡ���õĴӻ��豸���� */
static int __i2c_slv_num_get(void *p_drv);

/** \brief ���ôӻ�����ʱ�� */
static void __i2c_set_hold_time(amhw_fsl_i2c_t *base,
		                        uint32_t scl_stop_hold_time_ns,
								uint32_t clock);

/** \brief SCL clock divider used to calculate baudrate. */
static const uint16_t __i2c_divider_table[] = {
    20,   22,   24,   26,   28,   30,   34,   40,
	28,   32,   36,   40,   44,   48,   56,   68,
    48,   56,   64,   72,   80,   88,   104,  128,
	80,   96,   112,  128,  144,  160,  192,  240,
    160,  192,  224,  256,  288,  320,  384,  480,
	320,  384,  448,  512,  576,  640,  768,  960,
    640,  768,  896,  1024, 1152, 1280, 1536, 1920,
	1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840};

/**
 * \brief I2C���豸 ������������
 */
static am_const struct am_i2c_slv_drv_funcs __g_i2c_slv_drv_funcs = {
    __i2c_slv_setup,
    __i2c_slv_shutdown,
    __i2c_slv_num_get,
};

/**
 *  \brief ���ôӻ�����ʱ��
 */
static void __i2c_set_hold_time(amhw_fsl_i2c_t *p_hw_i2c,
		                        uint32_t scl_stop_hold_time_ns,
								uint32_t clock)
{
    uint32_t multiplier;
    uint32_t computed_scl_hold_time;
    uint32_t abs_error;
    uint32_t best_error = UINT32_MAX;
    uint32_t best_mult  = 0u;
    uint32_t best_icr   = 0u;
    uint8_t  mult;
    uint8_t  i;

    for (mult = 0u; (mult <= 2u) && (best_error != 0); ++mult) {
        multiplier = 1u << mult;

        /* Scan table to find best match. */
        for (i = 0u; i < sizeof(__i2c_divider_table) / sizeof(__i2c_divider_table[0]); ++i) {
            computed_scl_hold_time = ((multiplier * __i2c_divider_table[i]) * 500000000U) / clock;
            abs_error = scl_stop_hold_time_ns > computed_scl_hold_time ?
                (scl_stop_hold_time_ns - computed_scl_hold_time) :
                (computed_scl_hold_time - scl_stop_hold_time_ns);

            if (abs_error < best_error)
            {
                best_mult  = mult;
                best_icr   = i;
                best_error = abs_error;

                if (abs_error == 0)
                {
                    break;
                }
            }
        }
    }
    /* Set frequency register based on best settings. */
    amhw_fsl_i2c_clk_div_set(p_hw_i2c, I2C_F_MULT(best_mult) | I2C_F_ICR(best_icr));
}


/**
 *  \brief I2CӲ����ʼ��
 *  \note  1: ���ñ���ʱ��
 */
static int __i2c_slv_hard_init (am_fsl_i2c_slv_dev_t *p_dev)
{
    amhw_fsl_i2c_t *p_hw_i2c  = NULL;

    if (p_dev == NULL) {
        return -AM_EINVAL;
    }

    p_hw_i2c = (amhw_fsl_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    /* Configure low power wake up feature. */
    int src_clock_hz = am_clk_rate_get(p_dev->p_devinfo->clk_id);

    /* Set hold time. */
    __i2c_set_hold_time(p_hw_i2c, p_dev->p_devinfo->sclStopHoldTime_ns, src_clock_hz);

    return AM_OK;
}

/**
 *  \brief I2CӲ����ʼ��
 *  \note  1: ���ñ���ʱ��
 */
static inline void amhw_fsl_clear_status_flags(amhw_fsl_i2c_t *p_hw_i2c, uint32_t status_mask)
{
    /* Must clear the STARTF / STOPF bits prior to clearing IICIF */
    if (status_mask & kL16_I2C_START_DETECT_FLAG){
    	p_hw_i2c->glitch_filter |= (uint8_t)(status_mask >> 8U);
    }

    if (status_mask & kL16_I2C_STOP_DETECT_FLAG){
    	p_hw_i2c->glitch_filter |= (uint8_t)(status_mask >> 8U);
    }

    amhw_fsl_i2c_stat_clr(p_hw_i2c, status_mask);
}

/**
 * \brief ��ʼ�ӻ��豸
 */
static int __i2c_slv_setup (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{

    am_fsl_i2c_slv_dev_t *p_dev      = NULL;
    amhw_fsl_i2c_t       *p_hw_i2c   = NULL;

    if ((p_drv         == NULL) ||
        (p_i2c_slv_dev == NULL)) {
        return -AM_EINVAL;
    }

    p_dev    = (am_fsl_i2c_slv_dev_t *)p_drv;
    p_hw_i2c = (amhw_fsl_i2c_t *) (p_dev->p_devinfo->i2c_regbase);

    amhw_fsl_i2c_addr1_set(p_hw_i2c, p_i2c_slv_dev->dev_addr, p_i2c_slv_dev->dev_flags);

    p_dev->p_i2c_slv_dev[0] = p_i2c_slv_dev;

    amhw_fsl_i2c_enable(p_hw_i2c);

    amhw_fsl_i2c_int_enable(p_hw_i2c, AMHW_FSL_I2C_INT_IICIE);

    return AM_OK;
}

/**
 * \brief �ر� �ӻ��豸
 */
static int __i2c_slv_shutdown (void *p_drv, am_i2c_slv_device_t *p_i2c_slv_dev)
{
    am_fsl_i2c_slv_dev_t *p_dev    = (am_fsl_i2c_slv_dev_t *)p_drv;
    amhw_fsl_i2c_t   *p_hw_i2c_slv = NULL;

    if ( (p_dev              == NULL) ||
         (p_i2c_slv_dev      == NULL)) {
        return -AM_EINVAL;
    }
    p_hw_i2c_slv = (amhw_fsl_i2c_t *) p_dev->p_devinfo->i2c_regbase;

    /**
     * \brief ʧ�ܶ�Ӧ�ӵ�ַ ,���ݴӻ���ַ����ȷ���ùر���һ���ӻ��豸
     *
     * \note FSLֻ������һ�����豸 ��ֱ�ӹر�ʧ��I2C����
     */
    amhw_fsl_i2c_disable (p_hw_i2c_slv);

    return AM_OK;
}

/**
 * \brief ��ȡ���ôӻ��豸����
 */
static int __i2c_slv_num_get (void *p_drv)
{
    int     count = 0;
    uint8_t i     = 0;
    am_fsl_i2c_slv_dev_t *p_dev = (am_fsl_i2c_slv_dev_t *)p_drv;

    if ((p_dev == NULL)) {
        return -AM_EINVAL;
    }

    /* ��ȡ�ܵĴ��豸���� */
    uint8_t fsl_i2c_slv_dev_num = p_dev->fsl_i2c_slv_dev_num;

    for (i = 0; i < fsl_i2c_slv_dev_num; i++) {
        if (NULL == p_dev->p_i2c_slv_dev[i]) {
            count++;
        }
    }
    return count;
}

/**
 * \brief ��ȡ�ӻ�״̬��־
 */
static uint32_t __i2c_slv_get_status_flags(amhw_fsl_i2c_t *p_hw_i2c)
{
    uint32_t status_flags = amhw_fsl_i2c_stat_get (p_hw_i2c);

    /* Look up the STOPF bit from the filter register. */
    if (amhw_fsl_i2c_stop_is_dec(p_hw_i2c) == AM_TRUE)
    {
        status_flags |= kL16_I2C_STOP_DETECT_FLAG;
    }

    /* Look up the STARTF bit from the filter register. */
    if (amhw_fsl_i2c_start_is_dec(p_hw_i2c) == AM_TRUE)
    {
        status_flags |= kL16_I2C_START_DETECT_FLAG;
    }

    return status_flags;
}


/**
 * \brief I2C �жϴ�����
 *
 * \param[in] p_arg : ָ��I2C�豸�ṹ���ָ��
 *
 * \return ��
 */
static void __i2c_slv_irq_handler (void *p_arg)
{

    am_fsl_i2c_slv_dev_t  *p_dev              = (am_fsl_i2c_slv_dev_t *)p_arg;
    am_i2c_slv_device_t   *p_i2c_slv_dev      = (am_i2c_slv_device_t *)p_dev->p_i2c_slv_dev[0];
    amhw_fsl_i2c_t        *p_hw_i2c_slv       = (amhw_fsl_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    uint16_t status;
    uint8_t  do_transmit                      = AM_FALSE;
    uint8_t  data;

    status = __i2c_slv_get_status_flags(p_hw_i2c_slv);

    /* Check stop flag. */
    if (status & kL16_I2C_STOP_DETECT_FLAG) {
    	amhw_fsl_clear_status_flags(p_hw_i2c_slv, kL16_I2C_STOP_DETECT_FLAG);

        /* Clear the interrupt flag. */
        amhw_fsl_i2c_stat_clr(p_hw_i2c_slv, AMHW_FSL_I2C_STAT_IICIF);
        p_i2c_slv_dev->p_cb_funs->pfn_tran_stop(p_i2c_slv_dev->p_arg);

        do_transmit = AM_FALSE;
//        am_softimer_stop(&p_dev->softimer);
    if (!(status & kL16_I2C_ADDRESS_MATCH_FLAG))
       {
           return;
       }
    }

    /* Check start flag. */
    if (status & kL16_I2C_START_DETECT_FLAG) {
    	amhw_fsl_clear_status_flags(p_hw_i2c_slv, kL16_I2C_START_DETECT_FLAG);
        /* Clear the interrupt flag. */
    	amhw_fsl_i2c_stat_clr(p_hw_i2c_slv, AMHW_FSL_I2C_STAT_IICIF);

        if (!(status & kL16_I2C_ADDRESS_MATCH_FLAG))
           {
               return;
           }
    }

    /* Clear the interrupt flag. */
    amhw_fsl_i2c_stat_clr(p_hw_i2c_slv, AMHW_FSL_I2C_STAT_IICIF);

    /* Check NAK */
    if (status & KL16_I2C_RECEIVE_NAK_FLAG) {
        /* Set receive mode. */
    	amhw_fsl_i2c_transmode_set (p_hw_i2c_slv , AMHW_FSL_I2C_TRANSMODE_RECV);
    	data = amhw_fsl_i2c_data_read(p_hw_i2c_slv);
		//		am_softimer_stop(&p_dev->softimer);
    } else if (status & kL16_I2C_ADDRESS_MATCH_FLAG) {

        /* Slave transmit, master reading from slave. */
        if (status & KL16_I2C_TRANSFER_DIRECTION_FLAG) {
            /* Change direction to send data. */
    		amhw_fsl_i2c_transmode_set (p_hw_i2c_slv, AMHW_FSL_I2C_TRANSMODE_SEND);

            do_transmit = AM_TRUE;
        } else {
            /* Slave receive, master writing to slave. */
        	amhw_fsl_i2c_transmode_set (p_hw_i2c_slv , AMHW_FSL_I2C_TRANSMODE_RECV);
        }
        p_i2c_slv_dev->p_cb_funs->pfn_addr_match(p_i2c_slv_dev->p_arg, p_hw_i2c_slv->data);

    } else if (status & kL16_I2C_TRANSFER_COMPLETE_FALG) { /* Check transfer complete flag. */
        /* Slave transmit, master reading from slave. */
        if (status & KL16_I2C_TRANSFER_DIRECTION_FLAG) {
            do_transmit = AM_TRUE;

        } else {
            /* Slave receive, master writing to slave. */
            p_i2c_slv_dev->p_cb_funs->pfn_rxbyte_put(p_i2c_slv_dev->p_arg, p_hw_i2c_slv->data);
        }
    } else {
        /* Read dummy to release bus. */
    	data = amhw_fsl_i2c_data_read(p_hw_i2c_slv);
    }

    /* Send data if there is the need. */
    if (do_transmit)
    {
//        am_softimer_stop(&p_dev->softimer);

    	p_i2c_slv_dev->p_cb_funs->pfn_txbyte_get(p_i2c_slv_dev->p_arg, &data);
    	amhw_fsl_i2c_data_write(p_hw_i2c_slv, data);
        /* ��ʼ�������ʱ����ʱ 1ms */
//        am_softimer_start(&p_dev->softimer, 1);
    } else {
    	amhw_fsl_i2c_transmode_set (p_hw_i2c_slv , AMHW_FSL_I2C_TRANSMODE_RECV);
    	data = amhw_fsl_i2c_data_read(p_hw_i2c_slv);
    }
}


/**
 * \brief �����ʱ���ص�����
 *
 * \note �ڿ�ʼ�ź�֮�� ������������1�뻹δ��ֹͣ�ź� ���򽫴ӻ����и�λ
 */
static void __i2c_slv_timing_callback (void *p_arg)
{
	am_fsl_i2c_slv_dev_t *p_dev         = ( am_fsl_i2c_slv_dev_t *) p_arg;
    amhw_fsl_i2c_t       *p_hw_i2c_slv  = (amhw_fsl_i2c_t *)p_dev->p_devinfo->i2c_regbase;
	uint8_t               data = 0;

	amhw_fsl_i2c_transmode_set (p_hw_i2c_slv , AMHW_FSL_I2C_TRANSMODE_RECV);
	data = amhw_fsl_i2c_data_read(p_hw_i2c_slv);
    /** ֹͣ��ʱ */
    am_softimer_stop(&p_dev->softimer);
}


/**
 * \brief I2C��ʼ��
 *
 * \note Ӳ����ʼ�� ͨ���û����ÿ�ʼ���豸����ʼ��
 */
am_i2c_slv_handle_t am_fsl_i2c_slv_init (am_fsl_i2c_slv_dev_t           *p_dev,
                                         const am_fsl_i2c_slv_devinfo_t *p_devinfo)
{
    if (p_dev == NULL || p_devinfo == NULL ) {
        return NULL;
    }

    p_dev->i2c_slv_serv.p_funcs = (struct am_i2c_slv_drv_funcs *)&__g_i2c_slv_drv_funcs;
    p_dev->i2c_slv_serv.p_drv   = p_dev;

    p_dev->p_devinfo            = p_devinfo;

    if (p_devinfo->pfn_plfm_init) {
        p_devinfo->pfn_plfm_init();
    }

    __i2c_slv_hard_init(p_dev);

    /* ��ʼ�������ʱ�� */
    am_softimer_init(&p_dev->softimer, __i2c_slv_timing_callback, p_dev);

    /* �����ж� */
    am_int_connect(p_dev->p_devinfo->inum, __i2c_slv_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);

    return &(p_dev->i2c_slv_serv);
}

/**
 * \brief I2C���ʼ��
 */
void am_fsl_i2c_slv_deinit (am_i2c_slv_handle_t handle)
{
    amhw_fsl_i2c_t       *p_hw_i2c_slv = NULL;
    am_fsl_i2c_slv_dev_t *p_dev    = NULL;

    if (NULL == handle) {
        return ;
    }

    p_dev    = (am_fsl_i2c_slv_dev_t *)handle;
    p_hw_i2c_slv = (amhw_fsl_i2c_t *)p_dev->p_devinfo->i2c_regbase;

    amhw_fsl_i2c_disable (p_hw_i2c_slv);

    /* ȥ���ж����� */
    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum, __i2c_slv_irq_handler, (void *)p_dev);

    if (p_dev->p_devinfo->pfn_plfm_deinit) {
        p_dev->p_devinfo->pfn_plfm_deinit();
    }
}

/* end of file */
