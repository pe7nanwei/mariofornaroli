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
 * \brief SDCard�ӿ�
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
 * \name SD���汾
 * @{
 */
#define AM_SDCARD_VERSION        0x00E0
#define AM_SDCARD_SDV2X          0x0020
#define AM_SDCARD_SDV1X          0x0040
#define AM_SDCARD_MMC            0x0080
/** @} */

/**
 * \name SD����������
 * @{
 */
#define AM_SDCARD_CAPACITY_VER   0x0300
#define AM_SDCARD_SDSC           0x0100        /** <\brief ��׼����SD���濨��<2GB�� */
#define AM_SDCARD_SDHC           0x0200        /** <\brief ������SD���濨��2GB~32GB�� */
#define AM_SDCARD_SDXC           0x0400        /** <\brief ��������SD���濨��32GB~2TB��*/
/** @} */

#define AM_SD_OCR_ERRORBITS      0xFDFFE008

/**
 * \name SD���������ʷ���
 * @{
 */
#define AN_SDCARD_SPEED_CLASS    0x001F
#define AN_SDCARD_CLASS_0        0x0001        /** <\brief ���࿨Ƭ��ָ������ */
#define AN_SDCARD_CLASS_2        0x0002        /** <\brief ������2MB/S */
#define AN_SDCARD_CLASS_4        0x0004        /** <\brief ������4MB/S */
#define AN_SDCARD_CLASS_6        0x0008        /** <\brief ������6MB/S */
#define AN_SDCARD_CLASS_10       0x0010        /** <\brief ������10MB/S */
/** @} */

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

/** \brief CID , only in memory card */
typedef struct am_sdcard_cid {
    uint32_t    mid;
    uint16_t    oid;
    char        pnm[8];
    uint8_t     prv;
    uint32_t    psn;
    uint16_t    year;
    uint8_t     month;
    uint8_t     hwrev;
    uint8_t     fwrev;
}am_sdcard_cid_t;

/** \brief SCR register, only in memory card */
typedef struct am_sdcard_scr {
    uint8_t             structure;          /**< \brief structure version */
    uint8_t             sda_vsn;            /**< \brief SDA version */
    uint8_t             sda_spec3;
    uint8_t             bus_widths;         /**< \brief bus width */
#define AM_SD_SCR_BUS_WIDTH_1  (1<<0)
#define AM_SD_SCR_BUS_WIDTH_4  (1<<2)
    uint8_t             cmds;               /**< \brief CMD support */
#define AM_SD_SCR_CMD20_SUPPORT   (1<<0)
#define AM_SD_SCR_CMD23_SUPPORT   (1<<1)
    uint8_t             erase_value;        /**< \brief erase_value */
}am_sdcard_scr_t;

/** \brief SSR register, only in memory card */
typedef struct am_sdcard_ssr {
    uint32_t            au_size;            /**< \brief In sectors */
    uint32_t            erase_timeout;      /**< \brief In milliseconds */
    uint32_t            erase_offset;       /**< \brief In milliseconds */
}am_sdcard_ssr_t;

/** \brief CSD register, only in memory card */
typedef struct awbl_sdcard_csd {
    uint8_t     mmca_vsn;                   /**< \brief MMC version */
    uint32_t    max_tr_speed;               /**< \brief MAX transfer speed */
    uint16_t    cmd_class;                  /**< \brief command class  */
    uint16_t    sector_size;                /**< \brief sector size */
    uint32_t    sector_cnt;                 /**< \brief sector count */
    uint16_t    block_size;                 /**< \brief block size */
}am_sdcard_csd_t;

/**
 * \brief SD Card information
 */
typedef struct am_sdcard_mem_info{
    am_sdcard_csd_t csd;                    /**< \brief CSD�Ĵ��� */
    am_sdcard_cid_t cid;                    /**< \brief CID�Ĵ��� */
    am_sdcard_ssr_t ssr;                    /**< \brief SSR�Ĵ��� */
    am_sdcard_scr_t scr;                    /**< \brief SCR�Ĵ��� */

    uint32_t        ocr;                    /**< \brief OCR�Ĵ��� */
    uint32_t        rca;                    /**< \brief RCA�Ĵ��� */
    uint16_t        attribute;              /**< \brief SD Card��������*/
} am_sdcard_mem_info_t;

/**
 * \brief SDCARD �豸��Ϣ�ṹ��
 */
typedef struct am_sdcard_devinfo{
    uint16_t         mode;                  /**< \brief �豸��SDIOģʽ��־����ο���SDIOģʽ��־��*/
    uint32_t         speed;                 /**< \brief SDIO����*/
    am_bool_t        sdio_crc_en;           /**< \brief SDIO CRCʹ�ܱ�־*/
    uint32_t         ocr_valid;             /**< \brief SD Card֧�ֵ�ORC����ѹ��Χ�� */
}am_sdcard_devinfo_t;

/**
 * \brief SDCARD �豸�ṹ��
 */
typedef struct am_sdcard_dev{
    am_sdio_device_t           sdio_dev;    /**< \brief SDIO�豸*/
    const am_sdcard_devinfo_t *p_devinfo;   /**< \brief ָ��SD Card�豸��Ϣʵ����ָ��*/
    uint32_t                   blk_size;    /**< \brief SD Card ���С*/
    am_sdcard_mem_info_t       sdcard_info; /**< \brief SD Card ��������Ϣ*/
    am_wait_t                  wait;        /**< \brief wait �ȴ�*/
}am_sdcard_dev_t;

/** \brief SDIO ��׼�������������� */
typedef am_sdcard_dev_t *am_sdcard_handle_t;

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
                               uint32_t          *p_rca);

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
int am_sdcard_csd_get (am_sdcard_handle_t handle,
                       uint32_t           rca,
                       uint32_t          *p_csd);

/**
 * \brief ��ȡ�洢���Ĵ���SCRֵ(CMD55 + ACMD51)
 *
 * \param[in]   p_card      : SDIO�豸
 * \param[in]   rca         : �洢����Ե�ַ
 * \param[out]  p_scr       : �Ĵ���scrֵ
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
int am_sdcard_scr_get (am_sdcard_handle_t handle,
                       uint32_t           rca,
                       uint32_t          *p_scr);

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
                             uint8_t             width);

/**
 * \brief SD Card ���ÿ��С
 *
 * \param[in]  handle       : SD Card ���
 * \param[in]  blk_size     : ��Ҫ���õĿ��С����λ���ֽڣ�
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
int am_sdcard_status_get (am_sdcard_handle_t handle,
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
am_sdcard_handle_t am_sdcard_init(am_sdcard_dev_t           *p_dev,
                                  const am_sdcard_devinfo_t *p_devinfo,
                                  am_sdio_handle_t           sdio_handle);

/**
 * \brief SDCard �豸���ʼ��
 *
 * \param[in]  handle : SDCard�豸�������
 *
 * \retval AM_OK�����ɹ�������ʧ��
 */
int am_sdcard_deinit (am_sdcard_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* __AM_SDCARD_H */

/*end of file */

