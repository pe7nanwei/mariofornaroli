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
 * \brief ZLG217 kboot KinetisFlashTool �û������ļ�
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */


/**
 * \addtogroup am_if_src_bootconf_zlg217_kft
 * \copydoc am_bootconf_zlg217_kft.c
 * @{
 */
#include "am_boot_kft.h"
#include "ametal.h"
#include "am_gpio.h"
#include "am_zlg217.h"
#include "am_zlg217_inst_init.h"
#include "am_zlg217_boot_serial_uart.h"
#include "am_zlg217_boot_flash.h"
#include "am_zlg217_boot.h"
#include "am_boot.h"
#include "am_boot_autobaud.h"
#include "am_boot_flash.h"
#include "am_zlg_tim_cap.h"
#include "am_zlg_flash.h"
#include "zlg217_regbase.h"
/**
 * \name �Զ������ʼ��궨��
 * @{
 */

/** \brief ��Ҫ�õ��Ķ�ʱ��λ�� */
#define     TIMER_WIDTH           16

/** @} */

/*******************************************************************************
 * �Զ������ʼ������
 ******************************************************************************/

/** \brief �Զ������ʵ�ƽ̨��ʼ�� */
void __zlg217_plfm_autobaud_init (void)
{
    amhw_zlg_tim_prescale_set((amhw_zlg_tim_t *)ZLG217_TIM2_BASE, (uint16_t)8);
}

/** \brief �Զ������ʵ�ƽ̨���ʼ��  */
void __zlg217_plfm_autobaud_deinit (void)
{

}

/** \brief ƽ̨����ʱ�������־��ȡ  */
int __fsl_plfm_stat_flag_get (void *parg)
{
    return AM_OK;
}

/** \brief �Զ������ʵ��豸��Ϣʵ�� */
static am_boot_autobaud_devinfo_t  __g_zlg217_boot_autobaud_devinfo = {

    2,                            /**< \brief CAP����ͨ���� */
    TIMER_WIDTH,                  /**< \brief TIMER��ʱ��λ�� */
    10,                           /**< \brief ����һ�����ݵĳ�ʱʱ��(ms)*/
    AM_CAP_TRIGGER_FALL,          /**< \brief CAP���񴥷���ʽ */
    __zlg217_plfm_autobaud_init,  /**< \brief ƽ̨��ʼ������ */
    __zlg217_plfm_autobaud_deinit,/**< \brief ƽ̨���ʼ������ */

    __fsl_plfm_stat_flag_get,
};

/** \brief �Զ������ʹ��ܵ��豸ʵ�� */
am_boot_autobaud_dev_t  __g_zlg217_boot_autobaud_dev;

/** \brief ʵ����ʼ��������Զ������ʷ����� */
am_boot_autobaud_handle_t am_zlg217_boot_autobaud_inst_init (void)
{
    am_cap_handle_t   cap_handle   = am_zlg217_tim1_cap_inst_init();

    am_zlg_tim_cap_dev_t *p_cap_dev = (am_zlg_tim_cap_dev_t *)cap_handle;

    __g_zlg217_boot_autobaud_dev.cap_pin =
            p_cap_dev->p_devinfo->p_ioinfo[__g_zlg217_boot_autobaud_devinfo.cap_chanel].gpio;

    return am_boot_autobaud_init(&__g_zlg217_boot_autobaud_dev,
                                 &__g_zlg217_boot_autobaud_devinfo,
                                  cap_handle);
}

/** \brief �Զ�������ʵ�����ʼ�� */
void am_zlg217_boot_autobaud_inst_deinit (am_boot_autobaud_handle_t handle)
{
    am_zlg217_tim1_cap_inst_deinit(handle->cap_handle);
    am_boot_autobaud_deinit(handle);
}


/*******************************************************************************
 * flash����
 ******************************************************************************/
/**
 * < \brief bootloader flash �豸��Ϣ
 */
static am_zlg217_boot_flash_devinfo_t __g_flash_devinfo = {
    /** \brief flash����ʼ��ַ */
    0x08000000,
    /** \brief flash���ܵĴ�С */
    128 * 1024,
    /** \brief flash������С */
    1024,
    /** \brief flash������ */
    128,
    /** \brief flash�Ĵ����Ļ���ַ */
    ZLG217_FLASH_BASE,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨����ʼ������ */
    NULL,
};

/**
 * < \brief bootloader flash �豸ʵ��
 */
static am_zlg217_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 *
 * \param ��
 *
 * \return bootloader flash��׼����������Ϊ NULL��������ʼ��ʧ��
 */
am_boot_flash_handle_t am_zlg217_boot_flash_inst_init(void)
{
    return am_zlg217_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}



/*******************************************************************************
 * ��׼bootloader�ӿ�����
 ******************************************************************************/
/**
 * < \brief bootloader��׼�豸��Ϣ
 */
static am_zlg217_boot_devinfo_t __g_zlg217_boot_devinfo = {
    /**< \brief Ӧ�ô�������ʼ��ַ*/
    0x08005800,
    /**< \brief ������־�Ĵ�ŵ�ַ*/
    0x0801FC00,
    /** \brief flash��ʼ��ַ*/
    0x08000000,
    /** \brief flash��С */
    128 * 1024,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram������ַ */
    20 * 1024,
    /** \brief ƽ̨��ʼ������ */
    NULL,
    /** \brief ƽ̨���ʼ������ */
    NULL,
};

/**
 * < \brief bootloader��׼�豸ʵ��
 */
static am_zlg217_boot_dev_t __g_zlg217_boot_dev;

int am_zlg217_std_boot_inst_init(am_boot_flash_handle_t flash_handle)
{
    return am_zlg217_boot_init(&__g_zlg217_boot_dev, &__g_zlg217_boot_devinfo, flash_handle);
}

/*******************************************************************************
 * kboot KinetisFlashTool ����
 ******************************************************************************/

/**
 * < \brief kboot KinetisFlashTool �豸��Ϣ
 */
static am_boot_kft_dev_info_t  __g_zlg217_boot_kft_dev_info = {
    /**< \brief Ӧ�ô������ʼ��ַ*/
    0x08005800,
    /** \brief flash��ʼ��ַ*/
    0x08000000,
    /** \brief flash��С */
    128 * 1024,
    /** \brief ram��ʼ��ַ */
    0x20000000,
    /** \brief ram������ַ */
    20 * 1024,
    NULL,
    NULL,
};

/**
 * < \brief kboot KinetisFlashTool �豸ʵ��
 */
static am_boot_kft_dev_t __g_zlg217_boot_kft_dev;
/**
 * \brief bootloader kboot KinetisFlashTool ʵ����ʼ��
 *
 * \return ��Ϊ AM_OK��������ʼ���ɹ�
 */
int am_zlg217_boot_kft_inst_init( am_boot_flash_handle_t flash_handle)
{

    //am_boot_flash_handle_t flash_handle = am_zlg217_boot_flash_inst_init();

    am_boot_autobaud_handle_t autobaud_handle = am_zlg217_boot_autobaud_inst_init();

    am_boot_serial_handle_t serial_handle  = am_zlg217_boot_serial_uart_init(autobaud_handle);

    return am_boot_kft_init(&__g_zlg217_boot_kft_dev,
                            &__g_zlg217_boot_kft_dev_info,
                             flash_handle,
                             serial_handle);
}

/** @} */

/* end of file */
