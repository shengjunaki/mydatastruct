#ifndef DCLIST_H
#define DCLIST_H

#include <stdio.h>
#include <stdlib.h>

// 定义数据类型
typedef int ElemType;

// 双向循环链表节点结构体
typedef struct Node {
    ElemType data;          // 数据域
    struct Node* prev;      // 前驱指针
    struct Node* next;      // 后继指针
} Node;

// 双向循环链表结构体
typedef struct {
    Node* head;             // 头节点指针（不包含数据）
    int size;               // 链表长度
} DCLinkList;

// 函数声明

// 初始化链表
void InitList(DCLinkList* list);

// 摧毁链表
void DestroyList(DCLinkList* list);

// 头插法插入元素
int InsertHead(DCLinkList* list, ElemType data);

// 尾插法插入元素
int InsertTail(DCLinkList* list, ElemType data);

// 在指定位置插入元素
int InsertAt(DCLinkList* list, int pos, ElemType data);

// 头删法删除元素
int DeleteHead(DCLinkList* list, ElemType* data);

// 尾删法删除元素
int DeleteTail(DCLinkList* list, ElemType* data);

// 按位置删除元素
int DeleteAt(DCLinkList* list, int pos, ElemType* data);

// 按值删除元素（删除第一个匹配的元素）
int DeleteByValue(DCLinkList* list, ElemType value);

// 按值删除所有匹配的元素
int DeleteAllByValue(DCLinkList* list, ElemType value);

// 清除链表（保留头节点）
void ClearList(DCLinkList* list);

// 逆置链表
void ReverseList(DCLinkList* list);

// 排序链表（冒泡排序）
void SortList(DCLinkList* list);

// 获取链表长度
int GetSize(DCLinkList* list);

// 判断链表是否为空
int IsEmpty(DCLinkList* list);

// 打印链表
void PrintList(DCLinkList* list);

// 查找元素位置（返回第一个匹配的位置，从1开始）
int FindPosition(DCLinkList* list, ElemType value);

// 获取指定位置的元素
int GetElement(DCLinkList* list, int pos, ElemType* data);

#endif // DCLIST_H
