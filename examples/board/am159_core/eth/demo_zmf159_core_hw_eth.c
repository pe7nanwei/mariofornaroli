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
 * \brief ETH���̣�ͨ��HW��ӿ�ʵ��
 * - �������裺
 *   1.ʹ�ñ�����֮ǰ����Ҫ������ֲLWIPЭ��ջ(�����ametal/3rdparty)��
 *     �������ù��̣����ͷ�ļ�·��������IP6�ļ��У�.
 *   2.Demo��ʵ��tcp_server & tcp_client��ʹ�ú�AM_ZMF159_CORE_TCP_SERVER_TEST
       & AM_ZMF159_CORE_TCP_CLIENT_TEST �����Ӧ����
 *   3.�û����޸������ļ����Թܽţ�IP��ַ, port�˿�, ���ʣ�˫����Ϣ�Ƚ�������
 *      (am_hwconf_zmf159_eth.c), �Ƽ�ʹ��Ĭ�����ã��������Զ�ʶ��PHY����
 * - ʵ������
 *   1.ʹ��tcp_server��ʹ��������Թ��ߴ����ͻ������Ӻ󣬿ɽ����շ�����.
 *   2.ʹ��tcp_client��ʹ��������Թ��ߴ��������������Ӻ󣬿ɽ����շ�����.
 *
 *\note
 *   1.Ϊ��ʶETH�������ڹ���������LED1��ʵ��ʹ�ÿ���ȥ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-06-11  wyy, first implementation
 * \endinternal
 */

/***************************************************************************
 includes
 ***************************************************************************/
#include "demo_zlg_entries.h"
#include "am_zmf159_inst_init.h"
#include "am_zlg_eth.h"
#include "am_vdebug.h"
#include "am_zlg_phy.h"
#include "stdint.h"
#include "eth_conf.h"
#include "am_timer.h"
#include "amhw_zlg_eth_reg.h"
#include "zmf159_periph_map.h"
#include "amhw_zlg_eth.h"

#define __AM_ZMF159_ETH_TICK_PERIOD_MS             10 /**< \brief tick time */
#define __AM_ZMF159_ETH_LED1                       1  /**< \brief led num */
#define __AM_ZMF159_ETH_OCCUPY                     1  /**< \brief net occupyed */
#define __AM_ZMF159_ETH_RELEASE                    0  /**< \brief net release */

//#define AM_ZMF159_CORE_TCP_CLIENT_TEST
#define AM_ZMF159_CORE_TCP_SERVER_TEST

#if defined(AM_ZMF159_CORE_TCP_CLIENT_TEST)
extern void am_zlg_eth_tcp_client_init(void);
extern void am_zlg_eth_tcp_client_close(void);
#elif defined (AM_ZMF159_CORE_TCP_SERVER_TEST)
extern void am_zlg_eth_tcp_server_init(void);
extern void am_zlg_eth_tcp_server_close(void);
#else
#error "Please define TCP_CLIENT_TEST or TCP_SERVICE_TEST"
#endif


__IO uint32_t g_local_time = 0;

extern amhw_zlg_eth_t *gp_hw_eth;
extern am_eth_regs_conf g_eth_regs_config;
extern void zmf159_eth_gpio_config(void);
extern void zmf159_eth_usr_config(am_eth_regs_conf *p_eth_regs_config);

static void __time_update(void)
{
    g_local_time += __AM_ZMF159_ETH_TICK_PERIOD_MS;
}

static void __tim_timing_callback (void *p_arg)
{
    am_led_toggle (__AM_ZMF159_ETH_LED1);
    __time_update();
}

static void __timer_init(am_timer_handle_t handle)
{
    am_timer_callback_set(handle, 0, __tim_timing_callback, NULL);
    /* ���ö�ʱʱ��Ϊ 0.01s */
    am_timer_enable_us(handle, 0, 1000000 / 100);
}

static void __eth_test_entry(amhw_zlg_eth_t *p_hw_eth)
{
    uint8_t flag = __AM_ZMF159_ETH_RELEASE;    
    gp_hw_eth = p_hw_eth;    
    zmf159_eth_gpio_config();    
    zmf159_eth_usr_config(&g_eth_regs_config);
    am_zlg_eth_init(p_hw_eth);
    while (1) {
        if ((AM_ZLG_ETH_LINK_ST_UP == g_eth_link_status) 
            && (__AM_ZMF159_ETH_RELEASE == flag)) {
#if defined(AM_ZMF159_CORE_TCP_CLIENT_TEST)
            printf("connect to tcp server\n");
            /*connect to tcp server */
            am_zlg_eth_tcp_client_init();
#endif 

#if defined(AM_ZMF159_CORE_TCP_SERVER_TEST)
            printf("create tcp server\n");
            /*create tcp server */
            am_zlg_eth_tcp_server_init();
#endif

            flag = __AM_ZMF159_ETH_OCCUPY;
        }
        if ((AM_ZLG_ETH_LINK_ST_DOWN == g_eth_link_status) 
            && (__AM_ZMF159_ETH_OCCUPY == flag)) {
#if defined(AM_ZMF159_CORE_TCP_CLIENT_TEST)        		
            printf("disconnect to tcp server\n");
            am_zlg_eth_tcp_client_close();
#endif 

#if defined(AM_ZMF159_CORE_TCP_SERVER_TEST)        		
            printf("close tcp server\n");
            am_zlg_eth_tcp_server_close();
#endif 
            flag = __AM_ZMF159_ETH_RELEASE;
        }
        if (am_zlg_eth_check_frame_received()) {
            am_zlg_eth_lwip_pkg_handle(p_hw_eth);
        }
        am_zlg_eth_lwip_periodic_handle(p_hw_eth, g_local_time);
    }
	
}

void demo_zmf159_core_hw_eth_entry(void)
{
    printf("demo_zmf159_core_hw_eth_entry!\r\n");    
    __timer_init(am_zmf159_tim1_timing_inst_init());
    __eth_test_entry(ZMF159_ETH);
}

