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
 *   1.ʹ�ñ�����֮ǰ����Ҫ������ֲLWIPЭ��ջ(ametal/3rdparty)
 *   2.Demo��ʵ��tcp_server & tcp_client��ʹ�ú꿪�ؼ����
 *   3.�û����޸������ļ����Թܽţ�IP��ַ, port�˿�, ���ʣ�˫����Ϣ�Ƚ�������
 *      (amhw_zlg_usr_conf.c), �Ƽ�ʹ��Ĭ�����ã��������Զ�ʶ��PHY����
 * - ʵ������
 *   1.ʹ��tcp_server��ʹ��������Թ��ߴ����ͻ������Ӻ󣬿ɽ���loopback.
 *   2.ʹ��tcp_client��ʹ��������Թ��ߴ��������������Ӻ󣬿ɽ���loopback.
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

void demo_zmf159_core_hw_eth_entry(void)
{
    printf("demo_zmf159_core_hw_eth_entry!\r\n");
    demo_zlg_hw_eth_entry();
}

