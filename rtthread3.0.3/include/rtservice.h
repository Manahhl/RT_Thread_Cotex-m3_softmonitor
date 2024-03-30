#ifndef __RTSERVICE_H__
#define __RTSERVICE_H__
#include "main.h"

/**
 * @brief 链表节点初始化
 * 
 */
rt_inline void rt_list_init(rt_list_t *l)
{
	l->next = l->prev = l;
}

/**
 * @brief 链表头部后面插入节点
 * 
 */
rt_inline void rt_list_insert_after(rt_list_t *l, rt_list_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->next = l;
}

/**
 * @brief 链表表头前面插入节点
 * 
 */
rt_inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

/**
 * @brief 删除链表节点
 * 
 */
rt_inline void rt_list_remove(rt_list_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

#endif //  __RTSERVICE_H




