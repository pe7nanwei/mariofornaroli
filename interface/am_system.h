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
 * \brief ϵͳ��ط���
 *
 * ֻҪ������ ametal.h �Ϳ���ʹ�ñ�����
 *
 * \par ��ʾ��:�������ִ��ʱ��
 * \code
 *  #include "ametal.h"
 *
 *  int main(){
 *      unsigned int tick;
 *
 *      tick = am_sys_tick_get();
 *      //  do something
 *      tick = am_sys_tick_get() - tick;
 *      am_kprintf("tick used=%d\n , time=%d ms",
 *                  tick,
 *                  am_ticks_to_ms(tick));
 *      return 0;
 *  }
 * \endcode
 *
 * //�������ݴ���ӡ�����
 *
 * \internal
 * \par modification history:
 * - 1.00 13-02-27  zen, first implementation
 * \endinternal
 */

#ifndef __AM_SYSTEM_H
#define __AM_SYSTEM_H

#include "am_types.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus	*/

/**
 * \addtogroup am_if_system
 * \copydoc am_system.h
 * @{
 */

/**
 * \brief ϵͳģ���ʼ����һ����ϵͳ����ʱ���ã�
 * \param[in] clkrate : ����Ƶ�ʣ����밴�ո�Ƶ�ʵ���  am_system_module_tick()������
 * \retval AM_OK     : ģ���ʼ���ɹ�����������ʹ��
 */
int am_system_module_init (unsigned long clkrate);

/**
 * \brief һ����ĳһ��ʱ���ж��������Եĵ��øú���
 */
int am_system_module_tick (void);

/**
 * \brief ȡ��ϵͳʱ�ӽ���Ƶ��
 *
 * \return ϵͳʱ�ӽ���Ƶ��, ����Ϊ unsigned long
 */
unsigned long am_sys_clkrate_get (void);

/**
 * \brief ȡ��ϵͳ��ǰ�Ľ��ļ���ֵ,
 *
 * ϵͳ�����󣬽��ļ���ֵ��0��ʼ��ÿ��1��tick����1 ��ϵͳ���ĵ�Ƶ�ʿɵ���
 * am_sys_clkrate_get() ��ȡ��
 *
 * \return ϵͳ��ǰ�Ľ��ļ���ֵ, ����Ϊ unsigned int
 *
 * \par ʾ��:�������ִ��ʱ��
 * \code
 *  #include "ametal.h"
 *
 *  int main(){
 *      unsigned int tick;
 *
 *      tick = am_sys_tick_get();
 *      //  do something
 *      tick = am_sys_tick_get() - tick;
 *      am_kprintf("tick used=%d\n , time=%d ms",
 *                  tick,
 *                  am_ticks_to_ms(tick));
 *      return 0;
 *  }
 * \endcode
 *
 * // �������ݴ���ӡ�����
 */
am_tick_t am_sys_tick_get (void);

/**
 * \brief ��������ʱ��tick�Ĳ�ֵ
 *
 *  ����Ҫ���Ƿ�ת������: �����ı�ʾ�������Զ����ⷴת���⣬��0xfffffff����ʾ�޷��ŵ����ֵ(32bit)��
 *  Ҳ��ʾ�з�������-1.
 * \return ϵͳ��ǰʱ���ֵ(ʱ�����ʱ���ļ���ֵ)
 */
static am_inline am_tick_t am_sys_tick_diff(am_tick_t __t0, am_tick_t __t1)
{
    return __t1 - __t0;
}

/**
 * \brief ת������ʱ��Ϊϵͳʱ�ӽ��ĸ���
 * \param ms ����ʱ��
 * \return ����ʱ���Ӧ�Ľ��ĸ���
 * \note ����������һ�����ĵĽ�����һ�����ġ���һ������Ϊ5���룬��1~5���붼��
 *      ת��Ϊ1�����ġ�
 * \par ʾ��
 * \code
 * #include "apollo.h"
 *
 * am_task_delay(am_ms_to_ticks(500));    // ��ʱ500ms
 * \endcode
 */
am_tick_t am_ms_to_ticks (unsigned int ms);

/**
 * \brief ת��ϵͳʱ�ӽ��ĸ���Ϊ����ʱ��
 * \param ticks ���ĸ���
 * \return  ϵͳʱ�ӽ�������Ӧ�ĺ���ʱ��
 *
 * \par ʾ��:�������ִ��ʱ��
 * \code
 *  #include "apollo.h"
 *
 *  int main(){
 *      unsigned int tick;
 *
 *      tick = am_sys_tick_get();
 *      //  do something
 *      tick = am_sys_tick_get() - tick;
 *      am_kprintf("tick used=%d\n , time=%d ms",
 *                  tick,
 *                  am_ticks_to_ms(tick));
 *      return 0;
 *  }
 * \endcode
 */
unsigned int am_ticks_to_ms (am_tick_t ticks);

 
/**
 * \brief ��ȡ��ǰ��������ID
 *
 * \return ��������ID
 */
uint32_t am_core_id_self(void);

/**
 * \brief ��ȡ���������ص�ַ��Ӧ��ȫ�ֵ�ַ (�����ַ, DMA��������������ʹ�ô˵�ַ)
 *
 * \return ȫ�ֵ�ַ
 */
void *am_global_addr_get(void *p_addr);

/** @} am_if_system */

#ifdef __cplusplus
}
#endif  /* __cplusplus  */

#endif    /* __AM_SYSTEM_H    */

/* end of file */
