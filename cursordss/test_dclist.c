#include "dclist.h"

int main() {
    DCLinkList list;
    ElemType data;
    int pos;
    
    printf("=== 双向循环链表测试程序 ===\n\n");
    
    // 1. 初始化链表
    printf("1. 初始化链表\n");
    InitList(&list);
    PrintList(&list);
    printf("\n");
    
    // 2. 测试头插法
    printf("2. 测试头插法插入元素：1, 2, 3\n");
    InsertHead(&list, 1);
    InsertHead(&list, 2);
    InsertHead(&list, 3);
    PrintList(&list);
    printf("\n");
    
    // 3. 测试尾插法
    printf("3. 测试尾插法插入元素：4, 5, 6\n");
    InsertTail(&list, 4);
    InsertTail(&list, 5);
    InsertTail(&list, 6);
    PrintList(&list);
    printf("\n");
    
    // 4. 测试任意位置插入
    printf("4. 测试在位置2插入元素：99\n");
    InsertAt(&list, 2, 99);
    PrintList(&list);
    printf("\n");
    
    // 5. 测试获取元素
    printf("5. 测试获取第3个元素\n");
    if (GetElement(&list, 3, &data)) {
        printf("第3个元素是：%d\n", data);
    }
    printf("\n");
    
    // 6. 测试查找元素
    printf("6. 测试查找元素5的位置\n");
    pos = FindPosition(&list, 5);
    if (pos != -1) {
        printf("元素5的位置是：%d\n", pos);
    } else {
        printf("未找到元素5\n");
    }
    printf("\n");
    
    // 7. 测试头删法
    printf("7. 测试头删法删除元素\n");
    if (DeleteHead(&list, &data)) {
        printf("删除的元素是：%d\n", data);
    }
    PrintList(&list);
    printf("\n");
    
    // 8. 测试尾删法
    printf("8. 测试尾删法删除元素\n");
    if (DeleteTail(&list, &data)) {
        printf("删除的元素是：%d\n", data);
    }
    PrintList(&list);
    printf("\n");
    
    // 9. 测试按位置删除
    printf("9. 测试删除第2个元素\n");
    if (DeleteAt(&list, 2, &data)) {
        printf("删除的元素是：%d\n", data);
    }
    PrintList(&list);
    printf("\n");
    
    // 10. 测试按值删除
    printf("10. 测试删除值为4的元素\n");
    DeleteByValue(&list, 4);
    PrintList(&list);
    printf("\n");
    
    // 11. 添加一些重复元素测试按值删除所有
    printf("11. 添加重复元素并测试删除所有匹配元素\n");
    InsertTail(&list, 7);
    InsertTail(&list, 7);
    InsertTail(&list, 8);
    InsertTail(&list, 7);
    PrintList(&list);
    DeleteAllByValue(&list, 7);
    PrintList(&list);
    printf("\n");
    
    // 12. 测试排序功能
    printf("12. 测试排序功能\n");
    InsertTail(&list, 3);
    InsertTail(&list, 1);
    InsertTail(&list, 4);
    InsertTail(&list, 2);
    printf("排序前：");
    PrintList(&list);
    SortList(&list);
    printf("排序后：");
    PrintList(&list);
    printf("\n");
    
    // 13. 测试逆置功能
    printf("13. 测试逆置功能\n");
    printf("逆置前：");
    PrintList(&list);
    ReverseList(&list);
    printf("逆置后：");
    PrintList(&list);
    printf("\n");
    
    // 14. 测试清除功能
    printf("14. 测试清除功能\n");
    printf("清除前：");
    PrintList(&list);
    ClearList(&list);
    printf("清除后：");
    PrintList(&list);
    printf("\n");
    
    // 15. 重新添加元素测试
    printf("15. 重新添加元素测试\n");
    InsertTail(&list, 10);
    InsertTail(&list, 20);
    InsertTail(&list, 30);
    PrintList(&list);
    printf("\n");
    
    // 16. 测试边界情况
    printf("16. 测试边界情况\n");
    printf("尝试在位置0插入：");
    InsertAt(&list, 0, 100);
    printf("尝试在位置100插入：");
    InsertAt(&list, 100, 100);
    printf("尝试删除位置0：");
    DeleteAt(&list, 0, &data);
    printf("尝试删除位置100：");
    DeleteAt(&list, 100, &data);
    printf("\n");
    
    // 17. 最终状态
    printf("17. 最终链表状态\n");
    PrintList(&list);
    printf("链表长度：%d\n", GetSize(&list));
    printf("链表是否为空：%s\n", IsEmpty(&list) ? "是" : "否");
    printf("\n");
    
    // 18. 摧毁链表
    printf("18. 摧毁链表\n");
    DestroyList(&list);
    printf("链表长度：%d\n", GetSize(&list));
    printf("链表是否为空：%s\n", IsEmpty(&list) ? "是" : "否");
    
    printf("\n=== 测试完成 ===\n");
    
    return 0;
}
