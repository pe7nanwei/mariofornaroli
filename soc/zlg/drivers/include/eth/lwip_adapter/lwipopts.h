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
 * \brief lwipopts.h
 *
 * \internal
 * \par Modification History
 * - 1.00 19-06-11  wyy, first implementation
 * \endinternal
 */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/**
 * SYS_LIGHTWEIGHT_PROT==1: if you want inter-task protection for certain
 * critical regions during buffer allocation, deallocation and memory
 * allocation and deallocation.
 */
#define SYS_LIGHTWEIGHT_PROT        0

/**
 * NO_SYS==1: Provides VERY minimal functionality. Otherwise,
 * use lwIP facilities.
 */
#define NO_SYS                      1

/**
 * NO_SYS_NO_TIMERS==1: Drop support for sys_timeout when NO_SYS==1
 * Mainly for compatibility to old versions.
 */
#define NO_SYS_NO_TIMERS            1

/**
 * MEM_ALIGNMENT: should be set to the alignment of the CPU for which
 * lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
 * byte alignment -> define MEM_ALIGNMENT to 2. 
 */
#define MEM_ALIGNMENT               4

/** 
 * MEM_SIZE: the size of the heap memory. If the application will send
 * a lot of data that needs to be copied, this should be set high. 
 */
#define MEM_SIZE                    (10*1024)

/** 
 * MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
 * sends a lot of data out of ROM (or other static memory), this
 * should be set high. 
 */
#define MEMP_NUM_PBUF               50

/** 
 * MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
 * per active UDP "connection". 
 */
#define MEMP_NUM_UDP_PCB            6

/** brief MEMP_NUM_TCP_PCB: the number of simulatenously active TCP connections. */
#define MEMP_NUM_TCP_PCB            10

/** brief MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections. */
#define MEMP_NUM_TCP_PCB_LISTEN     6

/** brief MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments. */
#define MEMP_NUM_TCP_SEG            12

/** brief MEMP_NUM_SYS_TIMEOUT: the number of simulateously active timeouts. */
#define MEMP_NUM_SYS_TIMEOUT        10

/** brief PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE              10

/** brief PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE           500

#define LWIP_TCP                    1

#define TCP_TTL                     255

/** 
 * Controls if TCP should queue segments that arrive out of
 * order. Define to 0 if your device is low on memory. 
 */
#define TCP_QUEUE_OOSEQ             0

/** brief TCP Maximum segment size. */
#define TCP_MSS                     (1500 - 40)	  

/** brief TCP sender buffer space (bytes). */
#define TCP_SND_BUF                 (4 * TCP_MSS)

/**  
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work. 
 */
#define TCP_SND_QUEUELEN            (2 * TCP_SND_BUF/TCP_MSS)

/** brief TCP receive window. */
#define TCP_WND                     (2 * TCP_MSS)

#define LWIP_ICMP                   1

#define LWIP_DHCP                   1

#define LWIP_UDP                    1

#define UDP_TTL                     255

#define LWIP_STATS                  0

#define LWIP_PROVIDE_ERRNO          1

#define LWIP_NETIF_LINK_CALLBACK    1

#define LWIP_NETCONN                0

#define LWIP_SOCKET                 0

#endif /* __LWIPOPTS_H__ */
