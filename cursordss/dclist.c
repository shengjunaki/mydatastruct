#include "dclist.h"
void InitList(DCLinkList* list) {
    if (list == NULL) {
        printf("错误：链表指针为空\n");
        return;
    }
    // 创建头节点（不包含数据）
    list->head = (Node*)malloc(sizeof(Node));
    if (list->head == NULL) {
        printf("错误：内存分配失败\n");
        return;
    }
    
    // 头节点的前驱和后继都指向自己，形成循环
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
    
    printf("链表初始化成功\n");
}

// 摧毁链表
void DestroyList(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    
    // 先清除所有数据节点
    ClearList(list);
    
    // 释放头节点
    free(list->head);
    list->head = NULL;
    list->size = 0;
    
    printf("链表已摧毁\n");
}

// 头插法插入元素
int InsertHead(DCLinkList* list, ElemType data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("错误：内存分配失败\n");
        return 0;
    }
    
    newNode->data = data;
    
    // 在头节点后插入新节点
    newNode->next = list->head->next;
    newNode->prev = list->head;
    list->head->next->prev = newNode;
    list->head->next = newNode;
    
    list->size++;
    return 1;
}

// 尾插法插入元素
int InsertTail(DCLinkList* list, ElemType data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("错误：内存分配失败\n");
        return 0;
    }
    
    newNode->data = data;
    
    // 在头节点前插入新节点（即尾插）
    newNode->prev = list->head->prev;
    newNode->next = list->head;
    list->head->prev->next = newNode;
    list->head->prev = newNode;
    
    list->size++;
    return 1;
}

// 在指定位置插入元素
int InsertAt(DCLinkList* list, int pos, ElemType data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (pos < 1 || pos > list->size + 1) {
        printf("错误：位置无效，有效范围：1-%d\n", list->size + 1);
        return 0;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("错误：内存分配失败\n");
        return 0;
    }
    
    newNode->data = data;
    
    // 找到插入位置的前一个节点
    Node* current = list->head;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    
    // 插入新节点
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    
    list->size++;
    return 1;
}

// 头删法删除元素
int DeleteHead(DCLinkList* list, ElemType* data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空，无法删除\n");
        return 0;
    }
    
    Node* toDelete = list->head->next;
    if (data != NULL) {
        *data = toDelete->data;
    }
    
    // 删除第一个数据节点
    list->head->next = toDelete->next;
    toDelete->next->prev = list->head;
    free(toDelete);
    
    list->size--;
    return 1;
}

// 尾删法删除元素
int DeleteTail(DCLinkList* list, ElemType* data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空，无法删除\n");
        return 0;
    }
    
    Node* toDelete = list->head->prev;
    if (data != NULL) {
        *data = toDelete->data;
    }
    
    // 删除最后一个数据节点
    list->head->prev = toDelete->prev;
    toDelete->prev->next = list->head;
    free(toDelete);
    
    list->size--;
    return 1;
}

// 按位置删除元素
int DeleteAt(DCLinkList* list, int pos, ElemType* data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空，无法删除\n");
        return 0;
    }
    
    if (pos < 1 || pos > list->size) {
        printf("错误：位置无效，有效范围：1-%d\n", list->size);
        return 0;
    }
    
    // 找到要删除的节点
    Node* current = list->head;
    for (int i = 1; i <= pos; i++) {
        current = current->next;
    }
    
    if (data != NULL) {
        *data = current->data;
    }
    
    // 删除节点
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    
    list->size--;
    return 1;
}

// 按值删除元素（删除第一个匹配的元素）
int DeleteByValue(DCLinkList* list, ElemType value) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空，无法删除\n");
        return 0;
    }
    
    Node* current = list->head->next;
    while (current != list->head) {
        if (current->data == value) {
            // 找到匹配的节点，删除它
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            list->size--;
            return 1;
        }
        current = current->next;
    }
    
    printf("未找到值为 %d 的元素\n", value);
    return 0;
}

// 按值删除所有匹配的元素
int DeleteAllByValue(DCLinkList* list, ElemType value) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空，无法删除\n");
        return 0;
    }
    
    int count = 0;
    Node* current = list->head->next;
    
    while (current != list->head) {
        Node* next = current->next;
        if (current->data == value) {
            // 找到匹配的节点，删除它
            current->prev->next = current->next;
            current->next->prev = current->prev;
            free(current);
            list->size--;
            count++;
        }
        current = next;
    }
    
    if (count > 0) {
        printf("删除了 %d 个值为 %d 的元素\n", count, value);
    } else {
        printf("未找到值为 %d 的元素\n", value);
    }
    
    return count;
}

// 清除链表（保留头节点）
void ClearList(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    
    Node* current = list->head->next;
    while (current != list->head) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    // 重置头节点的指针
    list->head->prev = list->head;
    list->head->next = list->head;
    list->size = 0;
    
    printf("链表已清空\n");
}

// 逆置链表
void ReverseList(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return;
    }
    
    if (list->size <= 1) {
        printf("链表长度小于等于1，无需逆置\n");
        return;
    }
    
    Node* current = list->head->next;
    Node* temp;
    
    // 交换每个节点的前驱和后继指针
    while (current != list->head) {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }
    
    // 交换头节点的前驱和后继指针
    temp = list->head->next;
    list->head->next = list->head->prev;
    list->head->prev = temp;
    
    printf("链表逆置完成\n");
}

// 排序链表（冒泡排序）
void SortList(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return;
    }
    
    if (list->size <= 1) {
        printf("链表长度小于等于1，无需排序\n");
        return;
    }
    
    int swapped;
    Node* current;
    Node* last = list->head;
    
    do {
        swapped = 0;
        current = list->head->next;
        
        while (current->next != last) {
            if (current->data > current->next->data) {
                // 交换数据
                ElemType temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
    
    printf("链表排序完成（升序）\n");
}

// 获取链表长度
int GetSize(DCLinkList* list) {
    if (list == NULL) {
        return 0;
    }
    return list->size;
}

// 判断链表是否为空
int IsEmpty(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        return 1;
    }
    return list->head->next == list->head;
}

// 打印链表
void PrintList(DCLinkList* list) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return;
    }
    
    if (IsEmpty(list)) {
        printf("链表为空\n");
        return;
    }
    
    printf("链表内容（长度：%d）：", list->size);
    Node* current = list->head->next;
    while (current != list->head) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 查找元素位置（返回第一个匹配的位置，从1开始）
int FindPosition(DCLinkList* list, ElemType value) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return -1;
    }
    
    if (IsEmpty(list)) {
        printf("链表为空\n");
        return -1;
    }
    
    int pos = 1;
    Node* current = list->head->next;
    
    while (current != list->head) {
        if (current->data == value) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    
    return -1; // 未找到
}

// 获取指定位置的元素
int GetElement(DCLinkList* list, int pos, ElemType* data) {
    if (list == NULL || list->head == NULL) {
        printf("错误：链表未初始化\n");
        return 0;
    }
    
    if (IsEmpty(list)) {
        printf("错误：链表为空\n");
        return 0;
    }
    
    if (pos < 1 || pos > list->size) {
        printf("错误：位置无效，有效范围：1-%d\n", list->size);
        return 0;
    }
    
    Node* current = list->head->next;
    for (int i = 1; i < pos; i++) {
        current = current->next;
    }
    
    if (data != NULL) {
        *data = current->data;
    }
    
    return 1;
}
