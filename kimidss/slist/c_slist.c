#ifndef DLLIST_H_
#define DLLIST_H_

typedef int ElemType;

/* 结点 */
typedef struct Node
{
    ElemType data;
    struct Node *prev, *next;
} Node;

/* 链表管理器 */
typedef struct
{
    Node *head; /* 哨兵头结点 */
    Node *tail; /* 指向最后一个结点，便于尾插/尾删 */
    int len;    /* 当前长度 */
} List;

/* 基础生命周期 */
void list_init(List *lst);
void list_destroy(List *lst);
void list_clear(List *lst); /* 保留头结点，长度归零 */

/* 插入 */
int list_push_front(List *lst, ElemType e);
int list_push_back(List *lst, ElemType e);
int list_insert(List *lst, int pos, ElemType e); /* 0<=pos<=len */

/* 删除 */
int list_pop_front(List *lst, ElemType *out);
int list_pop_back(List *lst, ElemType *out);
int list_erase_pos(List *lst, int pos, ElemType *out);
int list_erase_val(List *lst, ElemType e, int *cnt); /* 删全部匹配 */

/* 功能 */
void list_reverse(List *lst);
void list_sort(List *lst);                        /* 升序，简单插入排序 */
Node *list_find_val(const List *lst, ElemType e); /* 按值查找，返回第一个匹配的结点 */

/* 调试打印 */
void list_print(const List *lst);
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#endif

static Node *node_new(ElemType e)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if (!p)
        return NULL;
    p->data = e;
    p->prev = p->next = NULL;
    return p;
}

/* 初始化：仅创建头结点，循环指向自身 */
void list_init(List *lst)
{
    lst->head = node_new(0); /* data 无意义 */
    lst->head->prev = lst->head->next = lst->head;
    lst->tail = lst->head;
    lst->len = 0;
}

void list_destroy(List *lst)
{
    list_clear(lst);
    free(lst->head);
    lst->head = lst->tail = NULL;
    lst->len = 0;
}

void list_clear(List *lst)
{
    Node *p = lst->head->next;
    while (p != lst->head)
    {
        Node *nxt = p->next;
        free(p);
        p = nxt;
    }
    lst->head->next = lst->head->prev = lst->head;
    lst->tail = lst->head;
    lst->len = 0;
}

/* 头插 */
int list_push_front(List *lst, ElemType e)
{
    Node *p = node_new(e);
    if (!p)
        return -1;
    p->next = lst->head->next;
    p->prev = lst->head;
    lst->head->next->prev = p;
    lst->head->next = p;
    if (lst->tail == lst->head)
        lst->tail = p;
    ++lst->len;
    return 0;
}

/* 尾插 */
int list_push_back(List *lst, ElemType e)
{
    Node *p = node_new(e);
    if (!p)
        return -1;
    p->prev = lst->tail;
    p->next = lst->tail->next; /* tail->next 就是 head */
    lst->tail->next->prev = p;
    lst->tail->next = p;
    lst->tail = p;
    ++lst->len;
    return 0;
}

/* 在 pos 位置插入，0<=pos<=len */
int list_insert(List *lst, int pos, ElemType e)
{
    if (pos < 0 || pos > lst->len)
        return -1;
    /* 找到第 pos 个结点（从 0 开始） */
    Node *cur = lst->head->next;
    for (int i = 0; i < pos; ++i)
        cur = cur->next;
    Node *p = node_new(e);
    if (!p)
        return -1;
    p->next = cur;
    p->prev = cur->prev;
    cur->prev->next = p;
    cur->prev = p;
    ++lst->len;
    return 0;
}

int list_pop_front(List *lst, ElemType *out)
{
    if (lst->len == 0)
        return -1;
    Node *p = lst->head->next;
    *out = p->data;
    lst->head->next = p->next;
    p->next->prev = lst->head;
    if (lst->tail == p)
        lst->tail = lst->head;
    free(p);
    --lst->len;
    return 0;
}

int list_pop_back(List *lst, ElemType *out)
{
    if (lst->len == 0)
        return -1;
    Node *p = lst->tail;
    *out = p->data;
    lst->tail = p->prev;
    p->prev->next = lst->head;
    lst->head->prev = p->prev;
    free(p);
    --lst->len;
    return 0;
}

/* 删除位置 pos 结点，0<=pos<len */
int list_erase_pos(List *lst, int pos, ElemType *out)
{
    if (pos < 0 || pos >= lst->len)
        return -1;
    Node *cur = lst->head->next;
    for (int i = 0; i < pos; ++i)
        cur = cur->next;
    *out = cur->data;
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    if (lst->tail == cur)
        lst->tail = cur->prev;
    free(cur);
    --lst->len;
    return 0;
}

/* 删除所有值等于 e 的结点，返回删除个数 */
int list_erase_val(List *lst, ElemType e, int *cnt)
{
    int c = 0;
    Node *p = lst->head->next;
    while (p != lst->head)
    {
        Node *nxt = p->next;
        if (p->data == e)
        {
            p->prev->next = p->next;
            p->next->prev = p->prev;
            if (lst->tail == p)
                lst->tail = p->prev;
            free(p);
            ++c;
        }
        p = nxt;
    }
    lst->len -= c;
    if (cnt)
        *cnt = c;
    return c;
}

void list_reverse(List *lst)
{
    if (lst->len <= 1)
        return;
    
    /* 只反转数据结点，不改变head指针 */
    Node *p = lst->head->next;
    while (p != lst->head)
    {
        Node *tmp = p->next;
        p->next = p->prev;
        p->prev = tmp;
        p = tmp;
    }
    
    /* 交换head的next和prev指针 */
    Node *tmp = lst->head->next;
    lst->head->next = lst->head->prev;
    lst->head->prev = tmp;
    
    /* 更新tail指针 */
    lst->tail = lst->head->prev;
}

/* 简单插入排序，升序 */
void list_sort(List *lst)
{
    if (lst->len <= 1)
        return;
    Node *sorted_tail = lst->head->next; /* 已排好序部分的尾 */
    while (sorted_tail != lst->tail)
    {
        Node *cur = sorted_tail->next; /* 待插入结点 */
        if (cur->data >= sorted_tail->data)
        {
            sorted_tail = cur;
            continue;
        }
        /* 把 cur 从原位置摘下 */
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        if (cur == lst->tail)
            lst->tail = cur->prev;
        /* 找到插入位置 */
        Node *pos = lst->head->next;
        while (pos != sorted_tail->next && pos->data < cur->data)
            pos = pos->next;
        /* 插入到 pos 前 */
        cur->prev = pos->prev;
        cur->next = pos;
        pos->prev->next = cur;
        pos->prev = cur;
        if (pos == lst->head->next)
            lst->head->next = cur;
    }
}

/* 按值查找，返回第一个匹配的结点，未找到返回NULL */
Node *list_find_val(const List *lst, ElemType e)
{
    Node *p = lst->head->next;
    while (p != lst->head)
    {
        if (p->data == e)
        {
            return p; /* 找到匹配的结点 */
        }
        p = p->next;
    }
    return NULL; /* 未找到 */
}

void list_print(const List *lst)
{
    printf("List[%d]: ", lst->len);
    Node *p = lst->head->next;
    while (p != lst->head)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    puts("");
}
int main()
{
    List lst;
    list_init(&lst);

    ElemType item;
    Node *p = NULL;
    int select;

    while (select)
    {
        printf("***位置均按索引******************\n");
        printf("* 1.push_back                  *\n");
        printf("* 2.push_front                 *\n");
        printf("* 3.show_list                  *\n");
        printf("* 4.pop_back                   *\n");
        printf("* 5.pop_front                  *\n");
        printf("* 6.insert_pos                 *\n");
        printf("* 7.find                       *\n");
        printf("* 8.length                     *\n");
        printf("* 9.delete_pos                 *\n");
        printf("* 10.delete_val                *\n");
        printf("* 11.sort                      *\n");
        printf("* 12.reverse                   *\n");
        printf("* 13.clear                     *\n");
        printf("* 0.quit_system                *\n");
        printf("********************************\n");
        printf("please input:>");
        scanf("%d", &select);

        switch (select)
        {
        case 1:
            printf("please input(-1 end):");
            while (scanf("%d", &item), item != -1)
            {
                list_push_back(&lst, item);
            }
            break;

        case 2:
            printf("please input(-1 end):");
            while (scanf("%d", &item), item != -1)
            {
                list_push_front(&lst, item);
            }
            break;

        case 3:
            list_print(&lst);
            break;

        case 4:
            if (list_pop_back(&lst, &item) == 0)
            {
                printf("pop back: %d\n", item);
            }
            else
            {
                printf("list is empty!\n");
            }
            break;

        case 5:
            if (list_pop_front(&lst, &item) == 0)
            {
                printf("pop front: %d\n", item);
            }
            else
            {
                printf("list is empty!\n");
            }
            break;

        case 6:
            printf("please input position and value:");
            int pos;
            scanf("%d %d", &pos, &item);
            if (list_insert(&lst, pos, item) == 0)
            {
                printf("insert success!\n");
            }
            else
            {
                printf("insert failed!\n");
            }
            break;

        case 7:
            printf("please input value to find:");
            scanf("%d", &item);
            p = list_find_val(&lst, item);
            if (p)
            {
                printf("found value %d at address: %p\n", item, p);
            }
            else
            {
                printf("value %d not found!\n", item);
            }
            break;

        case 8:
            printf("list length: %d\n", lst.len);
            break;

        case 9:
            printf("please input position to delete:");
            scanf("%d", &pos);
            if (list_erase_pos(&lst, pos, &item) == 0)
            {
                printf("delete position %d, value: %d\n", pos, item);
            }
            else
            {
                printf("delete failed!\n");
            }
            break;

        case 10:
            printf("please input value to delete:");
            scanf("%d", &item);
            int cnt;
            if (list_erase_val(&lst, item, &cnt) > 0)
            {
                printf("deleted %d nodes with value %d\n", cnt, item);
            }
            else
            {
                printf("no nodes with value %d found!\n", item);
            }
            break;

        case 11:
            list_sort(&lst);
            printf("list sorted!\n");
            break;

        case 12:
            list_reverse(&lst);
            printf("list reversed!\n");
            break;

        case 13:
            list_clear(&lst);
            printf("list cleared!\n");
            break;

        case 0:
            printf("quitting system...\n");
            break;

        default:
            printf("invalid choice!\n");
            break;
        }
    }
    list_destroy(&lst);
    return 0;
}