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
 * \brief bootloader drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_lpc824_boot.h"
#include "am_arm_nvic.h"
#include "am_int.h"
#include "am_vdebug.h"

static am_lpc824_boot_dev_t *__gp_boot_dev = NULL;
static int __boot_source_release(void);
static int __boot_update_flag_get_and_dispose (void);
/**
 * \brief �ж�Ӧ�ô����Ƿ��ִ��
 */
am_bool_t am_boot_app_is_ready(void)
{
    if(__gp_boot_dev == NULL) {
        return AM_FALSE;
    }

    uint32_t app_start_addr = __gp_boot_dev->p_devinfo->app_start_addr;
    if ((!app_start_addr) || (app_start_addr == 0xffffffff)) {
        return AM_FALSE;
    }
    uint32_t flash_start_addr = __gp_boot_dev->p_devinfo->flash_start_addr;
    uint32_t flash_end_adrr   = __gp_boot_dev->p_devinfo->flash_start_addr + \
        __gp_boot_dev->p_devinfo->flash_size - 1;
    uint32_t ram_start_addr = __gp_boot_dev->p_devinfo->ram_start_addr;
    uint32_t ram_size    = __gp_boot_dev->p_devinfo->ram_size;


    if(app_start_addr < flash_start_addr || app_start_addr > flash_end_adrr) {
        return AM_FALSE;
    } else {
        if((*(uint32_t *)app_start_addr) > (ram_start_addr + ram_size )||
           (*(uint32_t *)app_start_addr) < ram_start_addr) {
            return AM_FALSE;
        }
    }
    return AM_TRUE;
}
/**
 * \brief ��ת��Ӧ�ô���
 */
int am_boot_go_application(void)
{
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }

    uint32_t app_start_addr = __gp_boot_dev->p_devinfo->app_start_addr;
    uint32_t stack_pointer = *(uint32_t *)app_start_addr;
    
    void (*farewell_bootloader)(void);

    farewell_bootloader = (void (*)(void))(*(uint32_t *)(app_start_addr + 4));

   __boot_source_release();
   
    /* ����ջָ�� */
    __set_MSP(stack_pointer);
    __set_PSP(stack_pointer);

    /* ��ת��Ӧ�ô��� */
    farewell_bootloader();
    /*���������ת�����벻��ִ�е�����*/
    return -AM_ERROR;
}

/**
 * \brief ϵͳ����
 */
void am_boot_reset(void)
{
    if(__gp_boot_dev == NULL) {
        return;
    }
    NVIC_SystemReset();
}

/**
 * \brief �ͷ�ϵͳ��Դ
 *
 * \note bootloader����ת��Ӧ�ô���ǰ��������ô˽ӿڣ�
 *       ��bootloader���������Դ���߳�ʼ����ĳЩ���趼Ӧ�����ͷźͽ��ʼ���������Ӧ�ó������Ӱ�졣

 * \retval AM_OK : �ɹ�
 */
static int __boot_source_release(void)
{
	  
    am_arm_nvic_deinit();
    __disable_irq();
    return AM_OK;
}

/**
 * \brief BootLoader��ʼ������
 */
int am_lpc824_boot_init(am_lpc824_boot_dev_t     *p_dev,
                        am_lpc824_boot_devinfo_t *p_devinfo,
                        am_boot_flash_handle_t    flash_handle)
{
    if(p_devinfo == NULL || p_dev == NULL) {
        return -AM_ENXIO;
    }
    p_dev->flash_handle = flash_handle;
    p_dev->p_devinfo    = p_devinfo;

    __gp_boot_dev = p_dev;

    return AM_OK;
}

/* end of file */
