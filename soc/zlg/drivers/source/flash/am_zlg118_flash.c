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
 * \brief Flashģ���������ʵ��
 *
 * \internal
 * \par Modification History
 * - 1.00 19-09-04  zp, first implementation
 * \endinternal
 */

#include "am_zlg118_flash.h"
#include "am_types.h"
#include "am_bitops.h"
#include "am_int.h"
#include "ametal.h"


/*******************************************************************************
  defines
*******************************************************************************/
#define AM_ZLG118_FLASH                 ((amhw_zlg118_flash_typedef *)0x40020000UL)

#define AM_ZLG118_FLASH_END_ADDR        (0x0003FFFFu)
#define AM_ZLG118_FLASH_BYPASS()        AM_ZLG118_FLASH->bypass = 0x5A5A;\
                                      AM_ZLG118_FLASH->bypass = 0xA5A5;
#define AM_ZLG118_FLASH_IE_AM_TRUE      (0x03)
#define AM_ZLG118_FLASH_IE_FALSE        (0x00)
#define AM_ZLG118_FLASH_TIMEOUT_INIT    (0xFFu)
#define AM_ZLG118_FLASH_TIMEOUT_PGM     (0xFFu)
#define AM_ZLG118_FLASH_TIMEOUT_ERASE   (0xFFu)
#define AM_ZLG118_FLASH_LOCK_ALL        (0u)
#define AM_ZLG118_FLASH_UNLOCK_ALL      (0xFFFFFFFFu)

const uint32_t am_zlg118_flash_pcgtimer_4mhz[] = {0x20u, 0x17u, 0x1Bu, 0x4650u, 0x222E0u, 0x18u, 0xF0u, 0x3E8u };

 uint32_t am_zlg118_flash_writebyte(uint32_t addr, uint8_t u8Data)
{
    uint32_t           result  = AM_OK;
    volatile uint32_t  timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    volatile uint32_t key     = 0;

    key = am_int_cpu_lock();

    if (AM_ZLG118_FLASH_END_ADDR < addr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //set op
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while(Program != AM_ZLG118_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_ZLG118_FLASH_BYPASS();
            AM_ZLG118_FLASH->cr_f.op = Program;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_unlockall();

    //write data
    *((volatile uint8_t*)addr) = u8Data;

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_lockall();

    am_int_cpu_unlock(key);

    return (result);
}

 uint32_t am_zlg118_flash_writehalfword(uint32_t addr, uint16_t data)
{
    uint32_t          result  = AM_OK;
    volatile uint32_t timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    volatile uint32_t key     = 0;

    key = am_int_cpu_lock();

    if (AM_ZLG118_FLASH_END_ADDR < addr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //set op
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while(Program != AM_ZLG118_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_ZLG118_FLASH_BYPASS();
            AM_ZLG118_FLASH->cr_f.op = Program;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_unlockall();

    //write data
    *((volatile uint16_t*)addr) = data;

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_lockall();

    am_int_cpu_unlock(key);

    return (result);
}

 uint32_t am_zlg118_flash_writeword(uint32_t addr, uint32_t data)
{
    uint32_t             result  = AM_OK;
    volatile uint32_t    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    volatile uint32_t key     = 0;

    key = am_int_cpu_lock();

    if (AM_ZLG118_FLASH_END_ADDR < addr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_unlockall();

    //set op
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while(Program != AM_ZLG118_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_ZLG118_FLASH_BYPASS();
            AM_ZLG118_FLASH->cr_f.op = Program;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //write data
    *((volatile uint32_t*)addr) = data;

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_PGM;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_lockall();

    am_int_cpu_unlock(key);

    return (result);
}

 uint32_t am_zlg118_flash_sectorerase(uint32_t sectoraddr)
{
    uint32_t           result = AM_OK;
    volatile uint32_t  timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    volatile uint32_t key     = 0;

    key = am_int_cpu_lock();

    if (AM_ZLG118_FLASH_END_ADDR < sectoraddr)
    {
        result = AM_EINVAL;
        return (result);
    }

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_unlockall();

    //set op
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while(SectorErase != AM_ZLG118_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_ZLG118_FLASH_BYPASS();
            AM_ZLG118_FLASH->cr_f.op = SectorErase;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //write data
    *((volatile uint8_t*)sectoraddr) = 0;

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == (AM_ZLG118_FLASH->cr_f.busy))
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_lockall();

    am_int_cpu_unlock(key);

    return (result);
}

uint32_t am_zlg118_flash_chiperase(void)
{
    uint32_t          result  = AM_OK;
    volatile uint32_t timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    volatile uint32_t key     = 0;

    key = am_int_cpu_lock();

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //set op
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while(ChipErase != AM_ZLG118_FLASH->cr_f.op)
    {
        if(timeout--)
        {
            AM_ZLG118_FLASH_BYPASS();
            AM_ZLG118_FLASH->cr_f.op = ChipErase;
        }
        else
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_unlockall();

    //write data
    *((volatile uint8_t*)0) = 0;

    //busy?
    timeout = AM_ZLG118_FLASH_TIMEOUT_ERASE;
    while (AM_TRUE == AM_ZLG118_FLASH->cr_f.busy)
    {
        if(0 == timeout--)
        {
            return AM_EAGAIN;
        }
    }

    //Flash ����
    am_zlg118_flash_lockall();

    am_int_cpu_unlock(key);

    return (result);
}

 void am_zlg118_flash_lockall(void)
{
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock0 = AM_ZLG118_FLASH_LOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock1 = AM_ZLG118_FLASH_LOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock2 = AM_ZLG118_FLASH_LOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock3 = AM_ZLG118_FLASH_LOCK_ALL;
}

 void am_zlg118_flash_unlockall(void)
{
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock0 = AM_ZLG118_FLASH_UNLOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock1 = AM_ZLG118_FLASH_UNLOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock2 = AM_ZLG118_FLASH_UNLOCK_ALL;
    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->slock3 = AM_ZLG118_FLASH_UNLOCK_ALL;
}

int32_t am_zlg118_flash_sector_erase (amhw_zlg118_flash_t *p_hw_flash,
                                    uint32_t           addr)
{
    return am_zlg118_flash_sectorerase(addr);
}

int32_t am_zlg118_flash_sector_program (amhw_zlg118_flash_t *p_hw_flash,
                                      uint32_t             dst_addr,
                                      uint32_t            *p_src,
                                      uint32_t             size)
{
    uint32_t i    = 0;

    for(i = 0; i < size; i++) {
        am_zlg118_flash_writeword(dst_addr + i * 4, p_src[i]);
    }

    for (i = 0; i < size; i++) {

      if (p_src[i] != *(uint32_t *)(dst_addr + i * 4)) {
          break;
      }
    }
    return i;
}

int32_t am_zlg118_flash_waitcycle(amhw_zlg118_flash_read_waittime waitcycle)
{
    int32_t result = AM_OK;

    AM_ZLG118_FLASH_BYPASS();
    AM_ZLG118_FLASH->cr_f.wait = waitcycle;

    return result;
}

int32_t am_zlg118_flash_init(uint8_t freqcfg, am_bool_t able)
{
    uint32_t           index       = 0;
    volatile uint32_t  timeout     = AM_ZLG118_FLASH_TIMEOUT_INIT;
    int32_t            result      = AM_OK;
    uint32_t           prgtimer[8] = {0};
    volatile uint32_t  *pprgtimerreg = (volatile uint32_t*)AM_ZLG118_FLASH;

    if ((1  != freqcfg) && (2  != freqcfg) &&
        (4  != freqcfg) && (6  != freqcfg) &&
        (8  != freqcfg) && (12 != freqcfg))
    {
        result = AM_EINVAL;
        return (result);
    }

    AM_ZLG118_FLASH->cr_f.dpstb_en = able;

    //flashʱ���������ֵ����
    for(index=0; index<8; index++)
    {
        prgtimer[index] = freqcfg * am_zlg118_flash_pcgtimer_4mhz[index];
    }

    //flashʱ������Ĵ�������
    for(index=0; index<8; index++)
    {
        timeout = AM_ZLG118_FLASH_TIMEOUT_INIT;
        while(pprgtimerreg[index]  != prgtimer[index])
        {
            if(timeout--)
            {
                AM_ZLG118_FLASH_BYPASS();
                pprgtimerreg[index] = prgtimer[index];
            }
            else
            {
                return AM_ERROR;
            }
        }
    }

    return (result);
}


/* end of file */
