/**
 * \file
 * \brief bootloader ˫��Ӧ�ó�������
 *
 * - ��������
 *   1. LED����˸������ѭ����ӡ��
 *   2. �ȴ��û��������������Ӧ���������̼���
 *   
 *
 * \note
 *    �̼�����
 *
 *    ����ametal/tools/bootloader/�̼�У��/ �ļ��У�Ŀ¼����һ��bin_chek_sum.bin��ִ���ļ���
 *    �������̱������bin�ļ���������bin_chek_sum.binͬһ��Ŀ¼�£�
 *    �ڸ�Ŀ¼�´�cmd�������������������룺
 *         bin_chek_sum.bin  xxx.bin��������bin�ļ����ƣ� xxx.bin��Ŀ������ļ�����������ȡ��
 *
 *    ִ������������һ�����û��Լ�ȡ����Ŀ������ļ�������ļ�������Ҫ���͵Ĺ̼���
 *
 * \par Դ����
 * \snippet demo_am845_core_double_application.c src_am845_core_double_application
 *
 * \internal
 * \par Modification history
 * - 1.00 19-06-09  win, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_double_application
 * \copydoc demo_am845_core_double_application.c
 */

/** [src_am845_core_double_application] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_boot_enter_check_uart_cmd.h"
#include "am_boot_firmware_recv_uart.h"
#include "am_boot_firmware.h"
#include "am_lpc84x_inst_init.h"
#include "demo_boot_entries.h"
#include "am_appconf_lpc84x.h"

void demo_am845_core_double_application_entry (void)
{
    am_uart_handle_t             uart_handle;
    am_boot_firmware_handle_t    firmware_handle;
    am_boot_enter_check_handle_t check_handle;
    am_boot_firwa_recv_handle_t  firwa_recv_handle;
    am_boot_msg_handle_t         msg_handle;

    am_lpc84x_boot_inst_init();
    firmware_handle = am_lpc84x_boot_firmware_flash_inst_init();

    uart_handle = am_lpc84x_usart0_inst_init();
    am_debug_init(uart_handle, 9600);
    check_handle = am_boot_enter_check_uart_cmd_init(uart_handle);
    firwa_recv_handle = am_boot_firwa_recv_uart_init(firmware_handle, uart_handle);
    msg_handle = am_lpc84x_boot_msg_flag_inst_init();

    while(1) {
        /* ��demo��Ҫѭ������ */
        demo_std_double_application_entry(
            firwa_recv_handle,
            check_handle,
            msg_handle);

        am_led_toggle(0);
        am_mdelay(1000);
        AM_DBG_INFO("application : am845_core application running!\r\n");
    }
}
/** [src_am845_core_double_application] */

/* end of file */
