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
 * \brief �¼�������
 *
 * �������
 * 1. event category �����Ӧ���event type �Ͷ�� event handler
 * 2. event type     �����Ӧ���event handler
 * 3. event handler  �����Ӧһ���¼�������
 *
 * �¼�������
 * �¼���������С��λ�� event type���¼�����ʱ��
 * 1. ������ event type ���� event category �е����� event handler ִ��һ�顣
 * 2. ����¼���־���� AM_EVENT_PROC_FLAG_CAT_ONLY����� event type�����е�
 *    event handler Ҳ��ִ��һ�顣
 *
 * \internal
 * \par modification history:
 * - 1.00 17-05-12 tee, first implementation.
 * \endinternal
 */

#ifndef __AM_EVENT_H /* { */
#define __AM_EVENT_H

/**
 * \addtogroup am_if_event
 * \copydoc am_event.h
 * @{
 */

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name �¼���������־������am_event_handler_t��  flags ��Ա�������־��ʹ�û�����
 * @{
 */

/** \brief �¼�����󣬸��¼����������Զ�ע��   */
#define AM_EVENT_HANDLER_FLAG_AUTO_UNREG     (1u << 0)

/** @} */

/**
 * \name �¼���־�������־��ʹ�û�����
 * @{
 */

/* \brief ���¼�ֻ�ᴥ�� ������ event category �е� event handler  */
#define AM_EVENT_PROC_FLAG_CAT_ONLY         (1u << 0)

/** @} */

/** \breif event_category �ṹ���������� */
struct am_event_category;
typedef struct am_event_category am_event_category_t;

/** \breif event_type �ṹ���������� */
struct am_event_type;
typedef struct am_event_type am_event_type_t;

/** \breif event_handler �ṹ���������� */
struct am_event_handler;
typedef struct am_event_handler am_event_handler_t;

/**
 * \brief �¼����������Ͷ���
 *
 * \param[in]  p_evt_type : ָ���¼�
 * \param[in]  p_evt_data : �¼�������
 * \param[in]  p_hdl_data �� �¼���������˽������
 *
 * \return ��
 */
typedef void am_event_function_t (am_event_type_t   *p_evt_type,
                                  void              *p_evt_data,
                                  void              *p_hdl_data);

/**
 * \brief �¼��������ṹ�嶨��
 */
struct am_event_handler {
    uint16_t                 flags;     /**< \brief ��־��AM_EVENT_HANDLER_FLAG_*  */
    am_event_function_t     *pfn_proc;  /**< \brief ������  */
    void                    *p_data;    /**< \brief �¼�������˽������      */
    struct am_event_handler *p_next;    /**< \brief ָ����һ���¼�������  */
};

/** \brief ��ʼ���¼������� */
am_static_inline
void am_event_handler_init (am_event_handler_t  *p_handler,
                            am_event_function_t *pfn_proc,
                            void                *p_data,
                            uint16_t             flags)
{
    p_handler->flags    = flags;
    p_handler->pfn_proc = pfn_proc;
    p_handler->p_data   = p_data;
    p_handler->p_next   = NULL;
}


/** \brief �¼����ͽṹ���� */
struct am_event_type {
    am_event_handler_t  *p_handler;   /**< \brief ���¼������д����������� */
    am_event_category_t *p_category;  /**< \brief ���¼��������¼�����  */
    am_event_type_t     *p_next;      /**< \brief ָ����һ���¼�  */
};


/** \brief ��ʼ���¼�  */
am_static_inline
void am_event_init (am_event_type_t *p_event)
{
    p_event->p_category = NULL;
    p_event->p_handler  = NULL;
    p_event->p_next     = NULL;
}

/** \brief ע���¼����������¼��� */
int am_event_handler_register (am_event_type_t     *p_event,
                               am_event_handler_t  *p_handler);

/** \brief ���¼���ע���¼������� */
int am_event_handler_unregister (am_event_type_t     *p_event,
                                 am_event_handler_t  *p_handler);

/**
 * \brief ����һ���¼�
 *
 * �ᴥ���� event type ���� event category �е����� event handler ִ��һ�顣
 * ����¼���־���� AM_EVENT_PROC_FLAG_CAT_ONLY����� event type�����е�
 * event handler Ҳ��ִ��һ�顣
 *
 * \param p_event     �� �¼�
 * \param p_evt_data  �� �¼�����
 * \param flags       �� �����־, 0 �� AM_EVENT_PROC_FLAG_*
 *
 * \return ��׼�����
 */
int am_event_raise (am_event_type_t *p_event, void *p_evt_data, int flags);

/**
 * \brief �¼�����ṹ�嶨�壬���������¼����¼�������
 *
 * �������µ������¼�����ʱ�����������������µ������¼�������
 */
struct am_event_category {
    am_event_type_t    *p_event;    /**< \brief �¼�����  */
    am_event_handler_t *p_handler;  /**< \brief �¼����������� */
};


/** \brief ��ʼ���¼��¼����� */
am_static_inline
void am_event_category_init (am_event_category_t *p_category)
{
    p_category->p_event   = NULL;
    p_category->p_handler = NULL;
}

/** \brief ע���¼����������¼������� */
int am_event_category_handler_register (am_event_category_t *p_category,
                                        am_event_handler_t  *p_handler);

/** \brief ���¼�������ע���¼������� */
int am_event_category_handler_unregister (am_event_category_t *p_category,
                                          am_event_handler_t  *p_handler);

/** \brief ע���¼����¼�������  */
int am_event_category_event_register (am_event_category_t *p_category,
                                      am_event_type_t     *p_event);

/** \brief ���¼�������ע���¼�����  */
int am_event_category_event_unregister (am_event_category_t *p_category,
                                        am_event_type_t     *p_event);

#ifdef __cplusplus
}
#endif

/** @} grp_am_if_event */

#endif /* } __AM_EVENT_H */

/* end of file */
