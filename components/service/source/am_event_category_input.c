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
 * \brief �����¼�����
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-12  tee, first implementation.
 * \endinternal
 */
#include "am_event.h"
#include "am_input.h"
#include "am_event_category_input.h"

/*******************************************************************************
  Global variables
*******************************************************************************/

static am_event_category_t   __g_category_input;
static am_event_handler_t    __g_handler_cat_input;

/*******************************************************************************
  Local functions
*******************************************************************************/

static void __input_event_manager (am_event_type_t *p_evt_type,
                                   void            *p_evt_data,
                                   void            *p_usr_data)
{
    /*
     * ִ��event_type��handler֮ǰ, ��ִ�и�category��handler
     * input category��handler��ʱ�������κ�����, Ԥ����δ��ʹ��
     */
}

/*******************************************************************************
  Public variables
*******************************************************************************/

void am_event_category_input_init (void)
{
    /* ��ʼ��һ���¼���� : Input��� */
    am_event_category_init(&__g_category_input);

    /* ΪInput����ʼ��һ��handler */
    am_event_handler_init(&__g_handler_cat_input,
                           __input_event_manager,
                           "cat_input",
                           0);                                 /* �������־   */

    /* ��handler��Input���� */
    am_event_category_handler_register(&__g_category_input,
                                       &__g_handler_cat_input);
}

/******************************************************************************/
int am_event_category_intput_event_register (am_event_type_t *p_evt_type)
{
    return am_event_category_event_register(&__g_category_input, p_evt_type);
}

/******************************************************************************/
int am_event_category_intput_event_unregister (am_event_type_t *p_evt_type)
{
    return am_event_category_event_unregister(&__g_category_input, p_evt_type);
}

/******************************************************************************/
int am_event_category_intput_handler_register (am_event_handler_t *p_evt_handler)
{
    return am_event_category_handler_register(&__g_category_input, p_evt_handler);
}

/******************************************************************************/
int am_event_category_intput_handler_unregister (am_event_handler_t *p_evt_handler)
{
    return am_event_category_handler_unregister(&__g_category_input, p_evt_handler);
}

/* end of file */
