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
 * \brief SDCard��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-04  ipk, first implementation.
 * \endinternal
 */

#ifndef __AM_SDCARD_H
#define __AM_SDCARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_sdio.h"
#include "am_wait.h"

/**
 * \brief Supported SD Memory Cards
 */
#define AM_SDIO_STD_CAPACITY_SD_CARD_V1_1          0x00
#define AM_SDIO_STD_CAPACITY_SD_CARD_V2_0          0x01
#define AM_SDIO_HIGH_CAPACITY_SD_CARD              0x02
#define AM_SDIO_MULTIMEDIA_CARD                    0x03
#define AM_SDIO_SECURE_DIGITAL_IO_CARD             0x04
#define AM_SDIO_HIGH_SPEED_MULTIMEDIA_CARD         0x05
#define AM_SDIO_SECURE_DIGITAL_IO_COMBO_CARD       0x06
#define AM_SDIO_HIGH_CAPACITY_MMC_CARD             0x07

#define AM_SD_OCR_ERRORBITS                        0xFDFFE008

/**
 * \name OCR�Ĵ���
 * \anchor grp_awbl_sd_ocr_range
 * @{
 */

/** \brief VDD ��ѹ 1.65 - 1.95 */
#define AM_SD_OCR_VDD_165_195    0x00000080

/** \brief VDD ��ѹ 2.0 ~ 2.1 */
#define AM_SD_OCR_VDD_20_21      0x00000100

/** \brief VDD ��ѹ 2.1 ~ 2.2 */
#define AM_SD_OCR_VDD_21_22      0x00000200

/** \brief VDD ��ѹ 2.2 ~ 2.3 */
#define AM_SD_OCR_VDD_22_23      0x00000400

/** \brief VDD ��ѹ 2.3 ~ 2.4 */
#define AM_SD_OCR_VDD_23_24      0x00000800

/** \brief VDD ��ѹ 2.4 ~ 2.5 */
#define AM_SD_OCR_VDD_24_25      0x00001000

/** \brief VDD ��ѹ 2.5 ~ 2.6 */
#define AM_SD_OCR_VDD_25_26      0x00002000

/** \brief VDD ��ѹ 2.6 ~ 2.7 */
#define AM_SD_OCR_VDD_26_27      0x00004000

/** \brief VDD ��ѹ 2.7 ~ 2.8 */
#define AM_SD_OCR_VDD_27_28      0x00008000

/** \brief VDD ��ѹ 2.8 ~ 2.9 */
#define AM_SD_OCR_VDD_28_29      0x00010000

/** \brief VDD ��ѹ 2.9 ~ 3.0 */
#define AM_SD_OCR_VDD_29_30      0x00020000

/** \brief VDD ��ѹ 3.0 ~ 3.1 */
#define AM_SD_OCR_VDD_30_31      0x00040000

/** \brief VDD ��ѹ 3.1 ~ 3.2 */
#define AM_SD_OCR_VDD_31_32      0x00080000

/** \brief VDD ��ѹ 3.2 ~ 3.3 */
#define AM_SD_OCR_VDD_32_33      0x00100000

/** \brief VDD ��ѹ 3.3 ~ 3.4 */
#define AM_SD_OCR_VDD_33_34      0x00200000

/** \brief VDD ��ѹ 3.4 ~ 3.5 */
#define AM_SD_OCR_VDD_34_35      0x00400000

/** \brief VDD ��ѹ 3.5 ~ 3.6 */
#define AM_SD_OCR_VDD_35_36      0x00800000

/** \brief 1.8V switching request */
#define AM_SD_OCR_S18R           0x01000000

/** \brief SDXC power control */
#define AM_SD_OCR_XPC            0x10000000

/** \brief Card Capacity Status (CCS)1 */
#define AM_SD_OCR_CCS            0x40000000
/** @} */

/**
 * \brief  SD Card States
 */
typedef enum {
  AM_SD_CARD_READY                  = 0x01,
  AM_SD_CARD_IDENTIFICATION         = 0x02,
  AM_SD_CARD_STANDBY                = 0x03,
  AM_SD_CARD_TRANSFER               = 0x04,
  AM_SD_CARD_SENDING                = 0x05,
  AM_SD_CARD_RECEIVING              = 0x06,
  AM_SD_CARD_PROGRAMMING            = 0x07,
  AM_SD_CARD_DISCONNECTED           = 0x08,
  AM_SD_CARD_ERROR                  = 0xFF
}am_sd_card_state;

/**
 * \brief  Card Specific Data: CSD Register
 */
typedef struct am_sdcard_csd {
   uint8_t  csd_struct;             /**< \brief CSD structure */
   uint8_t  sys_specversion;        /**< \brief System specification version */
   uint8_t  Reserved1;              /**< \brief Reserved */
   uint8_t  taac;                   /**< \brief Data read access-time 1 */
   uint8_t  nsac;                   /**< \brief Data read access-time 2 in CLK cycles */
   uint8_t  max_bus_clkfrec;        /**< \brief Max. bus clock frequency */
   uint16_t card_comd_classes;      /**< \brief Card command classes */
   uint8_t  rdblocklen;             /**< \brief Max. read data block length */
   uint8_t  part_block_read;        /**< \brief Partial blocks for read allowed */
   uint8_t  wrblock_misalign;       /**< \brief Write block misalignment */
   uint8_t  rdblock_misalign;       /**< \brief Read block misalignment */
   uint8_t  dsrimpl;                /**< \brief DSR implemented */
   uint8_t  Reserved2;              /**< \brief Reserved */
   uint32_t device_size;            /**< \brief Device Size */
   uint8_t  max_rd_current_vddmin;  /**< \brief Max. read current @ VDD min */
   uint8_t  max_rd_current_vddmax;  /**< \brief Max. read current @ VDD max */
   uint8_t  max_wr_current_vddmin;  /**< \brief Max. write current @ VDD min */
   uint8_t  max_wr_current_vddmax;  /**< \brief Max. write current @ VDD max */
   uint8_t  device_size_mul;        /**< \brief Device size multiplier */
   uint8_t  erase_grsize;           /**< \brief Erase group size */
   uint8_t  erase_grmul;            /**< \brief Erase group size multiplier */
   uint8_t  wrprotect_grsize;       /**< \brief Write protect group size */
   uint8_t  wrprotect_grenable;     /**< \brief Write protect group enable */
   uint8_t  man_deflecc;            /**< \brief Manufacturer default ECC */
   uint8_t  wrspeed_fact;           /**< \brief Write speed factor */
   uint8_t  max_wrblocklen;         /**< \brief Max. write data block length */
   uint8_t  write_block_pa_partial; /**< \brief Partial blocks for write allowed */
   uint8_t  reserved3;              /**< \brief Reserded */
   uint8_t  content_protect_appli;  /**< \brief Content protection application */
   uint8_t  file_format_grouop;     /**< \brief File format group */
   uint8_t  copy_flag;              /**< \brief Copy flag (OTP) */
   uint8_t  perm_wr_protect;        /**< \brief Permanent write protection */
   uint8_t  temp_wr_protect;        /**< \brief Temporary write protection */
   uint8_t  file_format;            /**< \brief File Format */
   uint8_t  ecc;                    /**< \brief ECC code */
   uint8_t  csd_crc;                /**< \brief CSD CRC */
   uint8_t  reserved4;              /**< \brief always 1*/
} am_sdcard_csd_t;

/**
 * \brief  Card Identification Data: CID Register
 */
typedef struct am_sdcard_cid {
   uint8_t  manu_facturer_id;      /**< \brief ManufacturerID */
   uint16_t oem_appli_id;          /**< \brief OEM/Application ID */
   uint32_t prod_name1;            /**< \brief Product Name part1 */
   uint8_t  prod_name2;            /**< \brief Product Name part2*/
   uint8_t  prod_rev;              /**< \brief Product Revision */
   uint32_t prod_sn;               /**< \brief Product Serial Number */
   uint8_t  reserved1;             /**< \brief Reserved1 */
   uint16_t manufact_date;         /**< \brief Manufacturing Date */
   uint8_t  cid_crc;               /**< \brief CID CRC */
   uint8_t  reserved2;             /**< \brief always 1 */
} am_sdcard_cid_t;

/**
 * \brief SD Card information
 */
typedef struct {
    am_sdcard_csd_t csd;
    am_sdcard_cid_t cid;
    uint64_t        capacity;     /**< \brief Card Capacity */
    uint32_t        block_size;   /**< \brief Card Block Size */
    uint16_t        rca;
    uint32_t        type;
} am_sdcard_info_t;

/**
 * \brief SDCARD �豸��Ϣ�ṹ��
 */
typedef struct am_sdcard_devinfo{

    /** \brief ���豸��SDIOģʽ��־����ο���SDIOģʽ��־��*/
    uint16_t         mode;

    uint16_t         blk_size;

    uint32_t         ocr_valid;        /**< \brief ֧�ֵ�ORC����ѹ��Χ�� */

}am_sdcard_devinfo_t;

/**
 * \brief SDCARD �豸�ṹ��
 */
typedef struct am_sdcard_dev{
    am_sdio_handle_t        sdio_handle;
    am_sdio_device_t        sdio_dev;
    am_sdcard_devinfo_t    *p_devinfo;
    am_sdcard_info_t        sdcard_info;
    am_wait_t               wait;
}am_sdcard_dev_t;

/** \brief SDIO ��׼�������������� */
typedef am_sdcard_dev_t *am_sdcard_handle_t;

/**
 * \brief SD Card ��λ
 *
 * \param[in]  handle       : SD Card ���
 *
 * \retval AM_OK            : ��λ�ɹ�
 */
int am_sdcard_rest (am_sdcard_handle_t handle);

/**
 * \brief Ӧ�ó����ʼ��(CMD8)
 *
 * \param[in]   handle      : SDIO�豸
 * \param[in]   ocr         : SDIO HOST֧�ֵ�OCR��Χ
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_send_if_cond (am_sdcard_handle_t handle,
                            uint32_t           ocr);

/**
 * \brief Ӧ�ó����ʼ��(CMD55 + ACMD41)
 *
 * \param[in]   handle      : SDIO�豸
 * \param[in]   rca         : ��Ե�ַ
 * \param[in]   ocr         : SDIO HOST֧�ֵ�OCR��Χ
 * \param[in]   p_rocr      : ��ȡ��SDIO�豸֧�ֵ�OCR��Χ
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_send_app_op_cond (am_sdcard_handle_t handle,
                                uint32_t           rca,
                                uint32_t           ocr,
                                uint32_t          *p_rocr);

/**
 * \brief ��ȡ�洢�����е�CID(CMD2)
 *
 * \param[in]   handle      : SDIO�豸
 * \param[in]   p_cid       : �Ĵ���cid��������
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_all_cid_get (am_sdcard_handle_t handle,
                           uint32_t          *p_cid);

/**
 * \brief ��ȡ�洢����Ե�ַ(CMD3)
 *
 * \param[in]   handle      : SDIO�豸
 * \param[out]  p_rca       : �洢�����ص�rcaֵ
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdio_relative_addr_get (am_sdcard_handle_t handle,
                               uint16_t          *p_rca);

/**
 * \brief ѡ��ָ����Ե�ַ�Ŀ�(CMD7)
 *
 * \param[in]   p_card      : SDIO�豸
 * \param[in]   rca         : �洢����Ե�ַ
 * \param[out]  select      : ѡ�񿨣�1�� / ȡ������ 0��
 *
 * \retval AW_OK            : ����ɹ�
 * \retval -AW_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AW_ECANCELED    : ������ȡ��
 * \retval -AW_EIO          : SDIO����I/O����
 * \retval -AW_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AW_EINVAL       : ��������
 * \retval -AW_ETIME        : HOST����ʱ
 * \retval -AW_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_card_select (am_sdcard_handle_t handle,
                           uint32_t           rca,
                           uint8_t            select);

/**
 * \brief ��ȡ�洢���Ĵ���CSDֵ(CMD9)
 *
 * \param[in]   handle      : SDIO�豸
 * \param[in]   rca         : �洢����Ե�ַ
 * \param[out]  p_csd       : �Ĵ���csdֵ
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int aw_sdcard_csd_get (am_sdcard_handle_t handle,
                       uint32_t           rca,
                       uint32_t          *p_csd);

/**
 * \brief ���ô洢�����߿��(CMD55 + ACMD6)
 *
 * \param[in]  handle       : SDIO�豸
 * \param[in]  rca          : �洢����Ե�ַ
 * \param[out] width        : ���߿��
 *
 * \retval AW_OK            : ����ɹ�
 * \retval -AW_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AW_ECANCELED    : ������ȡ��
 * \retval -AW_EIO          : SDIO����I/O����
 * \retval -AW_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AW_EINVAL       : ��������
 * \retval -AW_ETIME        : HOST����ʱ
 * \retval -AW_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_bus_width_set (am_sdcard_handle_t  handle,
                             uint32_t            rca,
                             am_sdio_bus_width_t width);

/**
 * \brief SD Card ���ÿ��С
 *
 * \param[in]  handle       : SD Card ���
 * \param[in]  blk_size     : ��Ҫ���õĿ��С
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_block_size_set(am_sdcard_handle_t handle,
                             uint32_t           blk_size);

/**
 * \brief ͬ���Ӵ洢���ж�ȡ���ݿ�
 *
 * \param[in]  handle       : SDIO�豸
 * \param[in]  p_buf        : ���ݻ�����
 * \param[in]  blk_start    : ��ʼ���
 * \param[in]  blk_num      : �����
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_blocks_read (am_sdcard_handle_t handle,
                           uint8_t           *p_buf,
                           uint32_t           blk_start,
                           uint32_t           blk_num);

/**
 * \brief ͬ���Ӵ洢����д�����ݿ�
 *
 * \param[in]  handle       : SD Card ���
 * \param[in]  p_buf        : ���ݻ�����
 * \param[in]  blk_start    : ��ʼ���
 * \param[in]  blk          : ��Ҫд��Ŀ�����
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_blocks_write (am_sdcard_handle_t  handle,
                            uint8_t            *p_buf,
                            uint32_t            blk_start,
                            uint32_t            blk_num);

/**
 * \brief ������(CMD38)
 *
 * \param[in]  handle       : SD Card ���
 * \param[in]  blk_start    : ��Ҫ��������ʼ���
 * \param[in]  blk_num      : ��Ҫ�����Ŀ�����
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_blocks_erase (am_sdcard_handle_t handle,
                            uint32_t           blk_start,
                            uint32_t           blk_num);

/**
 * \brief ֹͣ����(CMD12)
 *
 * \param[in]  handle       : SD Card ���
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_transfer_stop (am_sdcard_handle_t handle);


int am_sdcard_sdinfo_get (am_sdcard_handle_t handle,
                          am_sdcard_info_t  *p_sdinfo);

/**
 * \brief ��ȡ��״̬(CMD13)
 *
 * \param[in]  handle       : SDIO�豸
 * \param[in]  rca          : �洢����Ե�ַ
 * \param[out] p_status     : �洢��״̬
 *
 * \retval AM_OK            : ����ɹ�
 * \retval -AM_ENOMEM       : �ڴ�ռ䲻��
 * \retval -AM_ECANCELED    : ������ȡ��
 * \retval -AM_EIO          : SDIO����I/O����
 * \retval -AM_EBUSY        : SDIO HOSTæ�����ڴ�������msg
 * \retval -AM_EINVAL       : ��������
 * \retval -AM_ETIME        : HOST����ʱ
 * \retval -AM_ENOTSUP      : HOST��֧�ָù���
 */
int am_sdcard_status_reg_get (am_sdcard_handle_t handle,
                              uint32_t           rca,
                              uint32_t          *p_status);

/**
 * \brief SDCard �豸��ʼ��
 *
 * \param[in]  p_dev       : SDCard�豸
 * \param[in]  p_devinfo   : SDCard�豸��Ϣ�ṹ��ָ��
 * \param[out] sdio_handle : SDIO��׼���
 *
 * \return �ɹ��򷵻�SDCard�豸���������ʧ�ܷ���NULL
 */
am_sdcard_handle_t am_sdcard_sdio_init(am_sdcard_dev_t      *p_dev,
                                       am_sdcard_devinfo_t  *p_devinfo,
                                       am_sdio_handle_t      sdio_handle);

/**
 * \brief SDCard �豸���ʼ��
 *
 * \param[in]  handle : SDCard�豸�������
 *
 * \retval AM_OK�����ɹ�������ʧ��
 */
int am_sdcard_sdio_deinit (am_sdcard_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDIO_H */

/*end of file */




