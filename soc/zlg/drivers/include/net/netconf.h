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
 * \brief netconf.h
 *
 * \internal
 * \par Modification History
 * - 1.00 19-06-11  wyy, first implementation
 * \endinternal
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NETCONF_H
#define __NETCONF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "am_zlgxx.h"

/* Exported types ------------------------------------------------------------*/
/* DHCP״̬ */
#define AM_ETH_DHCP_START                 1
#define AM_ETH_DHCP_WAIT_ADDRESS          2
#define AM_ETH_DHCP_ADDRESS_ASSIGNED      3
#define AM_ETH_DHCP_TIMEOUT               4
#define AM_ETH_DHCP_LINK_DOWN             5

//#define USE_DHCP       /* enable DHCP, if disabled static address is used */

/* ������Ϣ��� */
//#define SERIAL_DEBUG 
/* Զ��IP��ַ�Ͷ˿� */
#define AM_ETH_DEST_IP_ADDR0               192
#define AM_ETH_DEST_IP_ADDR1               168
#define AM_ETH_DEST_IP_ADDR2                40
#define AM_ETH_DEST_IP_ADDR3               179
#define AM_ETH_DEST_PORT                 50000
#define AM_ETH_LOCAL_SERVER_PORT         60000

/* MAC��ַ��������ַ */
#define AM_ETH_MAC_ADDR0                     22
#define AM_ETH_MAC_ADDR1                     33
#define AM_ETH_MAC_ADDR2                     44
#define AM_ETH_MAC_ADDR3                     55
#define AM_ETH_MAC_ADDR4                     66
#define AM_ETH_MAC_ADDR5                     77

/*��̬IP��ַ */
#define AM_ETH_IP_ADDR0                    192
#define AM_ETH_IP_ADDR1                    168
#define AM_ETH_IP_ADDR2                     40
#define AM_ETH_IP_ADDR3                    110

/* �������� */
#define AM_ETH_NETMASK_ADDR0               255
#define AM_ETH_NETMASK_ADDR1               255
#define AM_ETH_NETMASK_ADDR2               255
#define AM_ETH_NETMASK_ADDR3                 0

/* ���� */
#define AM_ETH_GW_ADDR0                    192
#define AM_ETH_GW_ADDR1                    168
#define AM_ETH_GW_ADDR2                     40
#define AM_ETH_GW_ADDR3                      1

/* ���PHY��·״̬��ʵ�ʼ��(��λ��ms) */
#ifndef AM_ETH_LINK_TIMER_INTERVAL
#define AM_ETH_LINK_TIMER_INTERVAL        1000
#endif

void am_eth_lwip_init(void);
void am_eth_lwip_pkg_handle(void);
void am_eth_lwip_periodic_handle(__IO uint32_t localtime);

#ifdef __cplusplus
}
#endif

#endif /* __NETCONF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

