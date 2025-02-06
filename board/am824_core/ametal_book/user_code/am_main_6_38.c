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
 * \brief �����嵥6.38
 *
 * \note ��������Ҫ�õ��������⣬hash table, ��Ҫʹ�ø�demo����Ҫ�� am_prj_config.h
 *  �еĺ� AM_CFG_NVRAM_ENABLE ����Ϊ1��Ĭ��Ϊ0���������demo���Խ������ȷ��
 *  �ٲ�������demo����Ҫ���껹ԭΪ0.��������ڴ治�㡣 
 *
 * \internal
 * \par Modification history
 * - 1.00 18-09-25  adw, first implementation
 * \endinternal
 */
 #include <stdio.h>
#include <stdlib.h>
#include "hash_kv.h"
#include "am_vdebug.h"
typedef struct _student{
    char        name[10];                       // ����
    char        sex;                            // �Ա�
    int         height, weight;                 // ��ߡ�����
} student_t;

int db_id_to_idx (unsigned char id[6])          // ͨ��ID�õ���������
{
    int i;
    int sum = 0;
    for (i = 0; i < 6; i++)
        sum += id[0];
    return sum % 250;
}

int student_info_generate (unsigned char *p_id, student_t *p_student) // �������һ��ѧ����¼
{
    int i;
    for (i = 0; i < 6; i++)                            // �������һ��ѧ��
        p_id[i] = rand();
    for (i = 0; i < 9; i++)                            // ������֣��� 'a' ~ 'z' ���
        p_student->name[i] = (rand() % ('z' - 'a')) + 'a';
    p_student->name[i]= '\0';                          // �ַ���������
    p_student->sex    = (rand() & 0x01) ? 'F' : 'M';   // ����Ա�
    p_student->height = (int)rand() / rand();
    p_student->weight = (int)rand() / rand();
    return 0;
}

int am_main ()
{
		
    student_t      stu;
    unsigned char  id[6];
    int            i;
    hash_kv_t      hash_students;
	
    hash_kv_init(&hash_students, 250, 6, sizeof(student_t), (hash_kv_func_t)db_id_to_idx, "hash_students");

    for (i = 0; i < 100; i++){                              // ���100��ѧ������Ϣ
        student_info_generate(id, &stu);                    // ����ѧ����Ϣ�����������Ϊ����
        if (hash_kv_search(&hash_students, id, &stu) == 0){ // ���ҵ��Ѿ����ڸ�ID��ѧ����¼
            am_kprintf("��ID�ļ�¼�Ѿ����ڣ�\n");
            continue;
        }
        am_kprintf("���Ӽ�¼��ID : %02x%02x%02x%02x%02x%02x",id[0],id[1],id[2],id[3],id[4],id[5]);
        am_kprintf("��Ϣ�� %s  %c %d %d\n", stu.name, stu.sex, stu.height, stu.weight);
        if (hash_kv_add(&hash_students, id, &stu) != 0){
            am_kprintf("���ʧ��\n");
        }
    }
    am_kprintf("����IDΪ��%02x%02x%02x%02x%02x%02x����Ϣ\n",id[0],id[1],id[2],id[3],id[4],id[5]);
    if (hash_kv_search(&hash_students, id, &stu) == 0)
        am_kprintf("ѧ����Ϣ�� %s  %c %d %d\n", stu.name, stu.sex, stu.height, stu.weight);
    else
        am_kprintf("δ�ҵ���ID�ļ�¼��\r\n");

    hash_kv_deinit(&hash_students);
    return 0;
}



/* end of file */

