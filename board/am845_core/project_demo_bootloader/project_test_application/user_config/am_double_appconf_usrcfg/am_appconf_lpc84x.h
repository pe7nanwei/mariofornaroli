#include "am_boot_msg.h"
#include "am_boot_flash.h"
#include "am_boot_firmware.h"
#include "am_boot_firmware_recv.h"
#include "am_boot_enter_check.h"

/**
 * \brief bootloader flashʵ����ʼ����������׼������
 */
am_boot_flash_handle_t am_lpc84x_boot_flash_inst_init(void);

/**
 * \brief bootloader ͨ����־������Ϣ ʵ����ʼ��
 */
am_boot_msg_handle_t am_lpc84x_boot_msg_flag_inst_init(void);

/**
 * \brief bootloader �̼���ŵ�flash ʵ����ʼ��
 */
am_boot_firmware_handle_t am_lpc84x_boot_firmware_flash_inst_init(void);

/**
 * \brief bootloader ��׼�ӿ�ʵ����ʼ��
 */
int am_lpc84x_boot_inst_init(void);

/* end of file */
