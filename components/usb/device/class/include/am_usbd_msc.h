/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBD MSC
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_MSC_H
#define __AM_USBD_MSC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_usb.h"
#include "am_usb_dci.h"



/** \brief msc���豸�����ʶ  */
#define AM_USBD_CONFIG_MSC_CLASS_CODE                     (0x08U)
#define AM_USBD_MSC_SUBCLASS                              (0x06U)
#define AM_USBD_MSC_PROTOCOL                              (0x50U)

/** \brief �õ�����LUN */
#define AM_USBD_MSC_GET_MAX_LUN                           (0xFEU)
/** \brief ��������������������  */
#define AM_USBD_MSC_BULK_ONLY_MASS_STORAGE_RESET          (0xFFU)



/*******************************************************************************
  �꺯������
*******************************************************************************/

/**< \brief ���16λʱ���ʽ�ĸ��ֽ� */
#define AM_TIME_HB(H,M,S) (((((H)<<11))|((M)<<5)|(S))>>8)

/**< \brief ���16λʱ���ʽ�ĵ��ֽ� */
#define AM_TIME_LB(H,M,S) ((((H)<<11))|((M)<<5)|(S))

/**< \brief ���16λ���ڸ�ʽ�ĸ��ֽ� */
#define AM_DATE_HB(Y,M,D) (((((Y)-1980)<<9)|((M)<<5)|(D))>>8)

/**< \brief ���16λ���ڸ�ʽ�ĵ��ֽ� */
#define AM_DATE_LB(Y,M,D) ((((Y)-1980)<<9)|((M)<<5)|(D))

//#define AM_BULK_MAX_PACKET_SIZE           (0x40)       /**< \brief �����������������ֽ��� */
#define AM_SCSI_COMMAND_SIZE              (0x1f)         /**< \brief ����SISI�����ֽ��� */

#define AM_USBD_MSC_DISD_SIZE             (32748 * 1024U)  /**< \brief ģ��U�̵����ڴ��С   256K~32748K*/
#define AM_USBD_MSC_SECTOR_SIZE           (512U)         /**< \brief ������С */
#define AM_USBD_MSC_USE_DATE_OFST         (2048U)        /**< \brief �û�������FAT������ƫ��λ�� */
#define AM_USBD_MSC_FAT1_OFST             (512U)         /**< \brief FAT1��FAT���е�ƫ��λ�� */

/**< \brief CBW ��ʶ�� */
#define AM_BOT_CBW_SIGNATURE              (0x43425355)

/**< \brief CSW ��ʶ�� */
#define AM_BOT_CSW_SIGNATURE              (0x53425355)

/*******************************************************************************
  SBU_MSC SCSI�������н׶�
*******************************************************************************/

#define AM_USBD_MSC_IDLE                  (0)  /**< \brief Idle state */
#define AM_USBD_MSC_DATA_OUT              (1)  /**< \brief Data Out state */
#define AM_USBD_MSC_DATA_IN               (2)  /**< \brief Data In state */
#define AM_USBD_MSC_DATA_IN_LAST          (3)  /**< \brief Last Data In Last */
#define AM_USBD_MSC_CSW_SEND              (4)  /**< \brief Command Status Wrapper */
#define AM_USBD_MSC_DATA_ERROR            (5)  /**< \brief error state */

/*******************************************************************************
  CSW״̬�������ݳ���/ֵ
*******************************************************************************/

/**< \brief BYTCHK �ֽڼ��λ */
#define AM_USBD_MSC_BLKVFY                          (0x04)
/**< \brief �豸������  */
#define AM_USBD_MSC_MEDIUM_NOT_PRESENT              (0x3A)
/**< \brief ��ַ������Χ  */
#define AM_USBD_MSC_ADDRESS_OUT_OF_RANGE            (0x21)
/**< \brief ����������ȴ���  */
#define AM_USBD_MSC_PARAMETER_LIST_LENGTH_ERROR     (0x1A)
/**< \brief REQUEST_SENSE_DATA CSW���ݳ��� */
#define AM_USBD_MSC_REQUEST_SENSE_DATA_LEN          (0x12)
/**< \brief MODE_SENSE10_DATA CSW���ݳ��� */
#define AM_USBD_MSC_MODE_SENSE10_DATA_LEN           (0x08)
/**< \brief READ_FORMAT_CAPACITY_DATA CSW���ݳ��� */
#define AM_USBD_MSC_READ_FORMAT_CAPACITY_DATA_LEN   (0x0C)
/**< \brief READ_CAPACITY10_DATA CSW���ݳ��� */
#define AM_USBD_MSC_READ_CAPACITY10_DATA_LEN        (0x08)
/**< \brief MODE_SENSE6_DATA CSW���ݳ��� */
#define AM_USBD_MSC_MODE_SENSE6_DATA_LEN            (0x04)
/**< \brief STANDARD_INQUIRY_DATA CSW���ݳ��� */
#define AM_USBD_MSC_STANDARD_INQUIRY_DATA_LEN       (0x24)


/*******************************************************************************
  SCSI Commands
*******************************************************************************/

#define AM_SCSI_FORMAT_UNIT                (0x04)  /**< \brief ��ʽ���������� */
#define AM_SCSI_INQUIRY                    (0x12)  /**< \brief ��ѯ�豸��Ϣ���� */
#define AM_SCSI_MODE_SENSE6                (0x1A)  /**< \brief ģʽ��֪���� */
#define AM_SCSI_MODE_SENSE10               (0x5A)  /**< \brief ���ز������� */
#define AM_SCSI_ALLOW_MEDIUM_REMOVAL       (0x1E)  /**< \brief д�������� */
#define AM_SCSI_READ10                     (0x28)  /**< \brief ���豸��ȡ�������� */
#define AM_SCSI_READ_CAPACITY10            (0x25)  /**< \brief ��ȡ�豸�������� */
#define AM_SCSI_REQUEST_SENSE              (0x03)  /**< \brief ��ȡ״̬��Ϣ���� */
#define AM_SCSI_START_STOP_UNIT            (0x1B)  /**< \brief ��ʼ/ֹͣ���� */
#define AM_SCSI_TEST_UNIT_READY            (0x00)  /**< \brief ��ѯ�豸�Ƿ�ready���� */
#define AM_SCSI_WRITE10                    (0x2A)  /**< \brief д���ݵ������豸���� */
#define AM_SCSI_VERIFY10                   (0x2F)  /**< \brief ��֤���� */
#define AM_SCSI_READ_FORMAT_CAPACITIES     (0x23)  /**< \brief ��ȡ��ǰ�豸�����Ϳɸ�ʽ������ */

/*******************************************************************************
  CSW Status Definitions
*******************************************************************************/

#define AM_USBD_MSC_CSW_DATA_LENGTH     (0x000D) /**< \brief CSW���ݳ��� */
#define AM_USBD_MSC_CSW_CMD_PASSED      (0x00)   /**< \brief ����ִ�гɹ� */
#define AM_USBD_MSC_CSW_CMD_FAILED      (0x01)   /**< \brief ����ִ��ʧ�� */
#define AM_USBD_MSC_CSW_PHASE_ERROR     (0x02)   /**< \brief ����ִ��ʧ�� */
#define AM_USBD_MSC_SEND_CSW_DISABLE    (0)      /**< \brief SCW����ʧ�� */
#define AM_USBD_MSC_SEND_CSW_ENABLE     (1)      /**< \brief SCW���ͳɹ� */
#define AM_USBD_MSC_ILLEGAL_REQUEST     (5)      /**< \brief Sence Keyֵ */
#define AM_USBD_MSC_NOT_READY           (2)      /**< \brief Sence Keyֵ */
#define AM_USBD_MSC_Max_LUN             (0)      /**< \brief ����߼���Ԫ */
#define AM_USBD_MSC_TXFR_IDLE           (0)      /**< \brief ����״̬ */
#define AM_USBD_MSC_TXFR_ONGOING        (1)      /**< \brief ����״̬ */
#define AM_USBD_MSC_NO_SENSE            (0)      /**< \brief ������ */
#define AM_USBD_MSC_INVALID_CMD         (0x24)   /**< \brief ��Ч������ */


/**
 * \brief SICI Command Block Wrapper ���ݽṹ
 *
 * \note С���ֽ� (���ֽ�����)
 */
typedef struct am_bulk_only_cbw {
    uint32_t dsignature;    /**< \brief ���ֶ�ΪCBW ��־ */
    uint32_t dtag;          /**< \brief CBW��ǩ��������������䣬��Ҫ��CSW�е�dtag����ñ�ǩ */
    uint32_t ddata_length;  /**< \brief ��Ҫ�����ݴ���׶δ�������ݳ��� */
    uint8_t  bm_flags;      /**< \brief ��ʾ���ݴ��䷽�� (D7λΪ1���������ݣ�D7λΪ0���������) */
    uint8_t  blun;          /**< \brief �߼���Ԫ�ı�ţ�(����Ϊ0) */
    uint8_t  bcb_length;    /**< \brief ��Ҫִ�е�����ĳ��� ��Ч��Χ1-16 */
    uint8_t  cb[16];        /**< \brief ��Ҫִ�еľ������� */
} am_bulk_only_cbw_t;

/**
 * \brief SICI Command Status Wrapper ���ݽṹ
 *
 */
typedef struct am_bulk_only_csw {
    uint32_t dsignature;    /**< \brief ���ֶ�ΪCSW ��־ */
    uint32_t dtag;          /**< \brief ������״̬��װ���ı�ǩ ��ֵΪ CBW �е� dtag һ�� */
    uint32_t ddata_residue; /**< \brief ��¼����Ҫ������ֽ��� */
    uint8_t  bstatus;       /**< \brief ����ִ�е�״̬ */
} am_bulk_only_csw_t;

/**
 * \brief usb_msc u����Ϣ
 *
 * \note ��ͬ������u�� �������ĵ�ַ��һ��
 */
typedef struct am_usb_msc_diskinfo {
    uint8_t        is_win10;           /**< \brief ��ǰPC�����Ƿ�ΪWIN10*/

    uint8_t        max_lun;            /**< \brief ���LUN��*/

    uint32_t       memory_size;        /**< \brief U��������С */
    uint16_t       block_size;         /**< \brief U��������С */
    uint32_t       block_count;        /**< \brief U���������� */
    uint32_t       fat1_offset;        /**< \brief FAT1�ĵ�ַ���ƫ���� */
    uint32_t       fat2_offset;        /**< \brief FAT2�ĵ�ַ���ƫ���� */
    uint32_t       root_offset;        /**< \brief ��Ŀ¼�ĵ�ַ���ƫ���� */

    uint8_t       *p_cmd_buffer;       /**< \brief �����������ݻ�����*/

    const uint8_t *p_root_dir;         /**< \brief ��Ŀ¼������Ϣ*/
    uint32_t       rootdir_size;       /**< \brief ��Ŀ¼���ݴ�С*/

    const uint8_t *p_readme;           /**< \brief README�ļ���Ϣ*/
    uint32_t       readme_size;        /**< \brief README�ļ����ݴ�С*/

} am_usbd_msc_diskinfo_t;

/**
 * \brief usb_msc ����״̬��Ϣ
 *
 * \note usbö�ٳɹ��Ժ�ͨ�ŵ���Ҫ���̣�
 *       ��������CBW����->�豸��������(��Ҫ��������ʱ���д˹���)->�豸����CSW״̬
 */
typedef struct am_usb_msc_state {
    uint8_t     transfer_state;        /**< \brief ���ݿ�ʼ�����־ */
    uint8_t     bot_state;             /**< \brief U�̴����״̬���� */
    uint32_t    block_offset;          /**< \brief ��¼��/дλ�õ�ƫ���� */
    uint32_t    scsi_lab;              /**< \brief ��ŵ�ǰ��/д���ݵ��߼����ַ */
    uint32_t    scsi_blk_len;          /**< \brief ��ŵ�ǰ��/д���ݵ��߼������ */
} am_usb_msc_state_t;

typedef struct am_usbd_msc_endpoint {
    uint8_t endpoint_in;
    uint8_t endpoint_out;
}am_usbd_msc_endpoint_t;


typedef void (*am_usbd_msc_recv_cb_t)(void *p_arg, uint8_t *p_buff, uint16_t len);

typedef struct am_usbd_msc_cb {
    am_usbd_msc_recv_cb_t   pfn_recv;
    void                   *p_arg;
}am_usbd_msc_cb_t;

/** \brief usb device msc class struct */
typedef struct am_usbd_msc {
    am_usbd_dev_t         *p_dev;
    am_bulk_only_cbw_t     cbw;
    am_bulk_only_csw_t     csw;
    am_usb_msc_state_t     state;

    volatile uint8_t       int_status_in;    /**< \brief �����ж�״̬ */
    volatile uint8_t       int_status_out;   /**< \brief ����ж�״̬ */

    uint32_t               w_offset;         /**< \brief Ŀǰ��Ҫд���ݵĵ�ַƫ���� */
    uint32_t               w_length;         /**< \brief Ŀǰ����Ҫд���ݵ��ֽ��� */

    uint32_t               r_offset;         /**< \brief Ŀǰ��Ҫ�����ݵĵ�ַƫ���� */
    uint32_t               r_length;         /**< \brief Ŀǰ����Ҫ�����ݵ��ֽ��� */

    am_usbd_msc_endpoint_t endpoint;         /**< \brief �˵���Ϣ */

    am_usbd_msc_cb_t       msc_cb;           /**< \brief ���յ����ݵĻص����� */

    const am_usbd_msc_diskinfo_t *p_info;    /**< \brief FAT16�ļ�ϵͳ�����Ϣ */
}am_usbd_msc_t;

typedef am_usbd_msc_t *am_usbd_msc_handle;
/**
 * \brief usb��������˵�2�жϺ�������
 *
 * \param[in] p_dev : ָ��usb�豸��ָ��
 *
 * \return ��
 */
void am_usb_msc_enpoint2_bulk_out (void *p_arg);

/**
 * \brief usb��������˵�1�жϺ�������
 *
 * \param[in] p_dev : ָ��usb�豸��ָ��
 *
 * \return ��
 */
void am_usb_msc_enpoint1_bulk_in (void *p_arg);



am_usbd_msc_handle am_usbd_msc_init (am_usbd_msc_t                    *p_dev,
                                     const am_usbd_msc_diskinfo_t     *p_info,
                                     am_usbd_dev_t                    *p_usbd);

void am_usb_msc_deinit (am_usbd_msc_t *p_dev);

am_usb_status_t am_usbd_msc_vendor_request_callback(am_usbd_msc_handle    handle,
                                                    am_vendor_request_t   pfn_cb,
                                                    void                 *p_arg);

am_usb_status_t am_usbd_msc_recv_callback (am_usbd_msc_handle    handle,
                                           am_usbd_msc_recv_cb_t pfun,
                                           void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_MSC_H */

/* end of file */
