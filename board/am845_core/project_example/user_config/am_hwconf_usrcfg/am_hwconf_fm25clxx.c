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
 * \brief F-RAM(fm25clxx) �����ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-06  zjr, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_mtd.h"
#include "am_fm25clxx.h"
#include "am_lpc84x.h"
#include "am_lpc84x_inst_init.h"

/**
 * \addtogroup am_if_src_hwconf_microport_fm25clxx_flash
 * \copydoc am_hwconf_microport_fm25clxx_flash.c
 * @{
 */

/** \brief �豸��Ϣ */
struct am_fm25clxx_devinfo fm25clxx_devinfo = {
    AM_SPI_MODE_0,
    PIO0_0,
    3000000
};

/*******************************************************************************
  FRAM(fm25clxx) ʵ����ʼ��
*******************************************************************************/

/** \brief �豸���� */
am_local am_fm25clxx_dev_t __g_fm25clxx_flash_dev;

/** \brief ʵ����ʼ�� */
am_fm25clxx_handle_t am_fm25clxx_inst_init (void)
{
    return am_fm25clxx_init(&__g_fm25clxx_flash_dev,
                            &fm25clxx_devinfo,
                             am_lpc84x_spi0_int_inst_init());
}

/** \brief ʵ����ʼ�� */
void am_fm25clxx_inst_deinit (am_fm25clxx_handle_t handle)
{
    am_fm25clxx_deinit (handle);
}

/*******************************************************************************
  FRAM ʵ����ʼ������ FM24C02 ������׼�� NVRAM �豸��
*******************************************************************************/

/** \brief MicroPort-EEPROM �豸ʵ�� */
am_local am_nvram_dev_t __g_fram_nvram_dev;

/**
 * \brief MicroPort-EEPROM ʵ����ʼ������ FM24C02 ������׼�� NVRAM �豸��
 */
int am_fm25clxx_fram_nvram_inst_init (void)
{
    am_fm25clxx_handle_t handle = am_fm25clxx_inst_init();

    return am_fm25clxx_nvram_init(handle,
                                 &__g_fram_nvram_dev,
                                  "fram_nvram");
}
/**
 * @}
 */

/* end of file */
