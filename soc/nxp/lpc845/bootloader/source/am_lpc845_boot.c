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
#include "am_lpc845_boot.h"
#include "am_lpc84x.h"
#include "am_arm_nvic.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "hw/amhw_lpc84x_iap.h"
#include "hw/amhw_arm_systick.h"

static am_lpc845_boot_dev_t *__gp_boot_dev = NULL;
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
#if  AM_DOUBLE_BOOT
    if(AM_OK != __boot_update_flag_get_and_dispose()) {
        return AM_FALSE;
    }
#endif

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
//    AMHW_ARM_SYSTICK->ctrl = 0;
//    AMHW_ARM_SYSTICK->val  = 0;
//    AMHW_ARM_SYSTICK->load = 0;

    am_arm_nvic_deinit();
    __disable_irq();
    return AM_OK;
}


/**
 * \brief ˫��bootloader��־����
 *
 * \param[in] flags ��־
 * AM_BOOTLOADER_FLAG_APP    ˫���û�������Ч
 * AM_BOOTLOADER_FLAG_UPDATE ˫������������Ч
 * AM_BOOTLOADER_FLAG_NO     ˫���޴���
 *
 * \retval AM_OK �ɹ�
 */
int am_boot_update_flag_set(uint32_t flag)
{
    amhw_lpc84x_iap_stat_t ret;
    uint32_t buf[16] = {0};
		buf[0] = flag;
    int key;
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }
    uint32_t start_page = __gp_boot_dev->p_devinfo->update_flag_addr / 64;
    uint32_t start_sector = __gp_boot_dev->p_devinfo->update_flag_addr / 1024;

    key = am_int_cpu_lock();

    ret = amhw_lpc84x_iap_prepare (start_sector,start_sector);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return AM_ERROR;
    }

    ret = amhw_lpc84x_iap_erase_page (start_page,start_page);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return AM_ERROR;
    }

    ret = amhw_lpc84x_iap_prepare (start_sector,start_sector);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return AM_ERROR;
    }

    amhw_lpc84x_iap_copy (__gp_boot_dev->p_devinfo->update_flag_addr, (uint32_t)buf, sizeof(buf));
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return AM_ERROR;
    }
    am_int_cpu_unlock(key);
    return AM_OK;
}

/**
 * \brief ˫��bootloader��־��ȡ������Ӧ����
 *
 */
static int __boot_update_flag_get_and_dispose ()
{
    uint32_t flags;
    uint16_t i = 0, j, ret;
    uint8_t buf[1024]= {0};
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }

   uint32_t addr = (uint32_t)__gp_boot_dev->p_devinfo->update_flag_addr;
   uint32_t app_sector_count = (__gp_boot_dev->p_devinfo->update_start_addr - \
                                __gp_boot_dev->p_devinfo->app_start_addr) / 1024;

   flags = *(uint32_t *)(addr);
   if (flags == AM_BOOTLOADER_FLAG_APP) {
       return AM_OK;
   } else if(flags == AM_BOOTLOADER_FLAG_UPDATE) {
       for(i = 0; i < app_sector_count; i++) {
           am_boot_flash_erase_region(
               __gp_boot_dev->flash_handle,
               __gp_boot_dev->p_devinfo->app_start_addr + i * 1024,
               1024 - 1);
       }

       uint32_t addr = __gp_boot_dev->p_devinfo->update_start_addr;
       for (i = 0 ; i < app_sector_count ; i++) {
           for(j = 0; j < sizeof(buf); j++) {
               buf[j] = *(uint8_t *)addr;
               addr++;
           }

           ret = am_boot_flash_program(
               __gp_boot_dev->flash_handle,
               __gp_boot_dev->p_devinfo->app_start_addr + i * 1024,
               (uint32_t *)buf,
               1024);

           if (ret != AM_OK) {
               am_kprintf("bootloader : firmware update error %d\r\n",ret);
               return AM_ERROR;
           }
       }
       am_boot_update_flag_set(AM_BOOTLOADER_FLAG_APP);
   } else {
       return AM_ERROR;
   }
   return AM_OK;
}

/**
 * \brief BootLoader��ʼ������
 */
int am_lpc845_boot_init(am_lpc845_boot_dev_t     *p_dev,
                        am_lpc845_boot_devinfo_t *p_devinfo,
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
