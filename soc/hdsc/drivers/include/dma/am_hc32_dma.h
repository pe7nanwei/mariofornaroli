/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.hc32.cn/
*******************************************************************************/

/**
 * \file
 * \brief DMA驱动，服务DMA接口
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-17  zp, first implementation
 * \endinternal
 */

#ifndef __AM_HC32_DMA_H
#define __AM_HC32_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "hw/amhw_hc32_dma.h"

/**
 * \addtogroup am_hc32_if_dma
 * \copydoc am_hc32_dma.h
 * @{
 */

/**
 * \name 通道传输中断标志
 * \anchor am_hc32_dma_chan_cfg_flags
 * @{
 */

#define AM_HC32_DMA_INT_COMPLETE            0  /** \brief 完成中断标识 */
#define AM_HC32_DMA_INT_ERR_ADDR_OVERFLOW   1  /** \brief 地址溢出传输错误 */
#define AM_HC32_DMA_INT_ERR_STOPASK         2  /** \brief 传输停止请求引起中止 */
#define AM_HC32_DMA_INT_ERR_SRCADDR         3  /** \brief 传输源地址访问错误 */
#define AM_HC32_DMA_INT_ERR_DSTADDR         4  /** \brief 传输目的地地址访问错误 */
#define AM_HC32_DMA_INT_ERR_STOP            5  /** \brief 传输暂停 */

/** @} */

/** \brief DMA中断回调函数类型 */
typedef void (*am_hc32_pfn_dma_isr_t)(void *p_arg, uint32_t flag);

/** \brief DMA中断回调函数信息 */
struct am_hc32_dma_int_info {

    /** \brief DMA触发回调函数 */
    am_hc32_pfn_dma_isr_t  pfn_isr;

    /** \brief 回调函数的第一个入口参数 */
    void                    *p_arg;
};

/** \brief DMA设备信息 */
typedef struct am_hc32_dma_devinfo {

    /** \brief 指向DMA寄存器块的指针 */
    uint32_t   dma_reg_base;

    /** \brief DMA中断号开始 */
    uint8_t    inum;

    /** \brief 平台初始化函数，如打开时钟，配置引脚等工作 */
    void     (*pfn_plfm_init)(void);

    /** \brief 平台解初始化函数 */
    void     (*pfn_plfm_deinit)(void);

} am_hc32_dma_devinfo_t;

/**
 * \brief DMA设备实例
 */
typedef struct am_hc32_dma_dev {

    /** \brief 指向DMA设备信息的指针 */
    const am_hc32_dma_devinfo_t *p_devinfo;

}am_hc32_dma_dev_t;

/**
 * \brief 设置通道0优先级最高
 */
void am_hc32_dma_priority_ch0_highest (void);

/**
 * \brief 设置通道0和通道1优先级相同，采用轮询方式传输数据
 */
void am_hc32_dma_priority_same (void);

/**
 * \brief 触发源为软件是，软件请求产生
 */
void am_hc32_dma_chan_soft_ask_start (int chan);

/**
 * \brief 触发源为软件是，软件请求停止
 */
void am_hc32_dma_chan_soft_ask_stop (int chan);

/**
 * \brief 配置DMA传输通道
 *
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] src  : 设定通道请求的触发源（请查看hc32_dma_chan.h宏定义）
 *
 */
void am_hc32_dma_chan_src_set (int chan, uint8_t src);

/**
 * \brief 配置DMA传输通道
 *
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] src  : 设定通道请求的触发源（请查看hc32_dma_chan.h宏定义）
 *
 * \retval AM_OK    : 配置成功
 * \retval AM_ERROR : 配置错误，该通道之前配置过
 */
int am_hc32_dma_chan_start (int chan);

/**
 * \brief 停止通道传输
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 *
 * \retval AM_OK   : 操作成功
 */
int am_hc32_dma_chan_stop (int chan);

/**
 * \brief 建立传输描述符
 *
 * \param[in] p_desc   : 指向DMA传输描述符的指针
 * \param[in] src_addr : 源端首地址
 * \param[in] dst_addr : 目标端首地址
 * \param[in] nbytes   : 传输字节数
 * \param[in] flags    : 配置参数
 *
 * \retval  AM_OK      : 建立成功
 * \retval -AM_EINVAL  : 未对齐，无效参数
 */
int am_hc32_dma_xfer_desc_build (amhw_hc32_dma_xfer_desc_t *p_desc,
                                   uint32_t                  src_addr,
                                   uint32_t                  dst_addr,
                                   uint32_t                  nbytes,
                                   uint32_t                  flags);

/**
 * \brief 开始DMA传输
 *
 * \param[in] p_desc  : 指向DMA传输描述符的指针
 * \param[in] type    : DMA传输模式设置 ：有对应的枚举体dma_transfer_type_t
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 *
 * \retval  AM_OK     : 操作成功
 * \retval -AM_EINVAL : 参数无效
 */
int am_hc32_dma_xfer_desc_chan_cfg (amhw_hc32_dma_xfer_desc_t    *p_desc,
                                      amhw_hc32_dma_transfer_type_t type,
                                      uint8_t                         chan);

/**
 * \brief 连接DMA回调函数
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AM_HC32_DMA_INT*
 *            见本文件上方宏定义处
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] pfn_isr : 回调函数指针
 * \param[in] p_arg   : 回调函数的第一个入口参数 ，在连接过程中，对应通道写上对应数字，
 *                      例如DMA0通道，则该参数为(void *)0
 *
 * \retval  AM_OK     : 连接成功
 * \retval -AM_EPERM  : 参数错误
 */
int am_hc32_dma_isr_connect (int                       chan,
                               am_hc32_pfn_dma_isr_t      pfn_isr,
                               void                     *p_arg);

/**
 * \brief 删除DMA回调函数的连接
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AM_HC32_DMA_INT*
 *            见本文件上方宏定义处
 *            该回调函数的第三个参数是产生中断的通道，其取值范围是DMA_CHAN_* (#DMA_CHAN_1)
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] pfn_isr : 回调函数指针
 * \param[in] p_arg   : 回调函数的第一个入口参数，在连接过程中，对应通道写上对应数字，
 *                      例如DMA0通道，则该参数为(void *)0
 *
 * \retval  AM_OK     : 删除成功
 * \retval -AM_EPERM  : 参数错误
 */
int am_hc32_dma_isr_disconnect (int                      chan,
                                  am_hc32_pfn_dma_isr_t  pfn_isr,
                                  void                    *p_arg);

/**
 * \breif 获取  某通道当前传输剩余的字节数
 *
 * \param[in] chan DMA 通道号，值为 DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 *
 * \retval  字节数
 */
uint16_t am_hc32_dma_tran_data_get (int chan);

/**
 * \breif 设置 某通道当前传输剩余的字节数
 *
 * \param[in] chan            DMA 通道号，值为 DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] trans_data_byte 要传输的字节数
 *
 * \retval  无
 *
 * \note 在设置传输的字节数之前必须停止通道传输
 */
void am_hc32_dma_tran_data_size (int chan, uint32_t trans_data_byte);

/**
 * \breif 设置每次传输时，块大小
 *
 * \param[in] chan            DMA 通道号，值为 DMA_CHAN_* (#DMA_CHAN_1) 或 (#DMA_CHAN_2)
 * \param[in] block_data_num  块大小数量
 *
 * \retval  无
 *
 * \note 在设置传输的字节数之前必须停止通道传输
 */
void am_hc32_dma_block_data_size (int chan, uint8_t block_data_num);

/**
 * \brief DMA初始化
 *
 * \param[in] p_dev         : 指向DMA设备的指针
 * \param[in] p_dma_devinfo : 指向DMA设备信息的指针
 *
 * \retval  AM_OK       : 初始化成功
 */
int am_hc32_dma_init (am_hc32_dma_dev_t           *p_dev,
                        const am_hc32_dma_devinfo_t *p_dma_devinfo);

/**
 * \brief DMA去初始化
 *
 * \return 无
 */
void am_hc32_dma_deinit (void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_HC32_DMA_H */

/* end of file */
