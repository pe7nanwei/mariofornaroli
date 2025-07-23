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
 * \brief fm175xx��CPU�����в��ԣ�ͨ�������ӿ�ʵ��
 *
 * - �������裺
 *   1. ��ȷ���Ӳ����úô��ڣ�
 *   2. ��ȷ���Ӻ����ߣ�
 *   3. ��CPU���������߸�Ӧ����
 *
 * - ʵ������
 *   1. ����Ƭ�������߸�Ӧ���󴮿ڴ�ӡ����Ƭ��ID��
 *   2. ������õĿ�Ƭ��CPU��������ӡATS��COSָ��Ĳ��������
 *
 * \par Դ����
 * \snippet demo_fm175xx_cpu_card.c src_fm175xx_cpu_card
 *
 * \internal
 * \par Modification history
 * - 1.00 18-02-06  sdq, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_kl26_if_dr_fm175xx_cpu_card
 * \copydoc demo_kl26_dr_fm175xx_cpu_card.c
 */

/** [src_kl26_dr_fm175xx_cpu_card] */
#include "am_fm175xx.h"
#include "am_fm175xx_reg.h"
#include "am_vdebug.h"
#include "am_delay.h"

/**
 * \brief CPU����������
 */
void demo_fm175xx_cpu_card (am_fm175xx_handle_t handle)
{
    uint8_t tag_type[2]  = { 0 };         /* ATQA */
    uint8_t uid[10]      = { 0 };         /* UID */
    uint8_t uid_real_len =   0;           /* ���յ���UID�ĳ��� */
    uint8_t sak[3]       = { 0 };         /* SAK */
    uint8_t i, j;
    
    /* cpu������ʱ�õ����²��� */    
    uint8_t  cid           = 0x00;        /* FSDI/CID */
    uint8_t  ats[20]       = { 0 };       /* ���RATSָ���ATS��Ӧ */
    uint8_t  sellect_MF[7] = {0x00 ,0xA4 ,0x00 ,0x00 ,0x02 ,0x3F ,0x00};  /* ѡ�����ļ����� */
    uint32_t ats_nbytes    =   0;          /* ATS��Ӧ���ݵĳ��� */
    uint8_t  rbuf[200]     = { 0 };        /* �ļ�����ʱ���������ݽ��ջ����� */
    uint32_t r_nbyte       =   0;          /* ÿ�ν����ļ�ʱ�����յ������ݳ��� */

    while (1) {

        if (AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_active\
                                         (handle,
                                          AM_FM175XX_PICCA_REQ_IDLE,
                                          tag_type,
                                          uid,
                                          &uid_real_len,
                                          sak)) {

            am_kprintf("UID : ");
            for (i = 0; i < uid_real_len; i++) {
                am_kprintf("%02x ", uid[i]);
            }
            am_kprintf("\r\n");

            if(AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_rats_get(
                                            handle,
                                            cid,
                                            ats,
                                            20,
                                            &ats_nbytes
                                                )) {
                 am_kprintf("ATS data: ");
                 for (j = 0; j < ats_nbytes; j++) {
                     am_kprintf(" %02x ",ats[j]);
                 }   
                 am_kprintf("\r\n");
                 
                 if(AM_FM175XX_STATUS_SUCCESS == am_fm175xx_picca_transfer(
                                                 handle,
                                                 sellect_MF,
                                                 7,   /* ����ΪCOSָ��ĳ��ȣ��˴�Ϊ��ѡ�����ļ�00 A4 00 00 02 3F 00������ĳ���*/
                                                 rbuf,
                                                 200,       
                                                 &r_nbyte )) {
                                                     
                     am_kprintf("send data : "); 
                     for (j = 0; j < 7; j++) {
                         am_kprintf(" %02x ",sellect_MF[j]);
                     } 
                     am_kprintf("\r\n");  
                     
                     am_kprintf("return data : ");                                                                    
                     for (j = 0; j < r_nbyte; j++) {
                         am_kprintf(" %02x ",rbuf[j]);
                     }
                     am_kprintf("\r\n");        
                 }
                 else {
                     am_kprintf("sellect_MF err!"); 
                 }
             }
             else {
                 am_kprintf("RATS err!\r\n");  
             }                                               
             am_kprintf("\r\n\r\n\r\n\r\n");
        }
        am_mdelay(500);  
    }
}

/** [src_fm175xx_cpu_card] */

/* end of file */
