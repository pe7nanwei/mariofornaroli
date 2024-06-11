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
 * \brief ͨ������������ض���ͷ�ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_TYPES_H
#define __AM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdio.h"
#include "am_errno.h"
 
/**
 * \addtogroup am_if_types
 * \copydoc am_types.h
 * @{
 */
 
/** \brief �������Ͷ��� */
typedef uint8_t am_bool_t;

/** \brief �棬�ɸ�ֵ���������� */
#define AM_TRUE   1

/** \brief �٣��ɸ�ֵ���������� */
#define AM_FALSE  0

/**
 * \brief ��ָ�붨��
 */
#ifndef NULL
#define NULL      ((void *)0)
#endif
 
/**
 * \brief inline ����
 * @{
 */
#if   defined (__CC_ARM)     

typedef	 long		off_t;	

#define am_inline   __inline             /**< inline for ARMCC    */
#define am_static_inline  static  __inline  
    
#elif defined (__ICCARM__)
#define am_inline   inline               /**< inline for IAR      */
#define am_static_inline  static inline 

#elif defined   (__GNUC__)
#define am_inline   inline               /**< inline for GNU      */
#define am_static_inline  static inline  

#elif defined   (__TASKING__)
#define am_inline   inline               /**< inline for TASKING  */
#define am_static_inline  static inline  

#endif /* __CC_ARM */
/** @} */

/** \todo  ���ݱ���������ѡ�� static �ؼ��� */
#define am_local    static

/** \todo  ���ݱ���������ѡ�� const �ؼ��� */
#define am_const    const
    
/** \todo  ���ݱ���������ѡ�� extern �ؼ��� */
#define am_extern   extern

/** \todo  ���ݱ���������ѡ�� extern �ؼ��� */
#define am_import   extern

/** \todo  ���ݱ���������ѡ�� extern �ؼ��� */
#define am_export   extern


#ifdef __cplusplus
  #define   __I     volatile             /**< Defines ֻ��     */
#else
  #define   __I     volatile const       /**< Defines ֻ��     */
#endif
#define     __O     volatile             /**< Defines ֻд     */
#define     __IO    volatile             /**< Defines �ɶ���д */


/** \brief void (*pfn) (void *) */
typedef void (*am_pfnvoid_t) (void *);

/** \brief the tick type for system ticks */
typedef unsigned long   am_tick_t;

/**
 * @} 
 */
 
#ifdef __cplusplus
}
#endif
 
#endif /* __AM_TYPES_H */

/* end of file */
