#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

/* 链式队列结点 */
typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode;

/* 链队列结构 */
typedef struct {
    QNode *front, *rear;
} LinkQueue;

/* 8个操作函数 */
void init(LinkQueue *q) {
    q->front = q->rear = NULL;
}

int enqueue(LinkQueue *q, ElemType x) {
    QNode *p = (QNode *)malloc(sizeof(QNode));
    if (!p) {
        printf("内存分配失败\n");
        return 0;
    }
    p->data = x;
    p->next = NULL;
    if (!q->rear) /* 空队列 */
        q->front = q->rear = p;
    else {
        q->rear->next = p;
        q->rear = p;
    }
    return 1;
}

void showqueue(const LinkQueue *q) {
    if (!q->front) {
        printf("队列空\n");
        return;
    }
    printf("队列内容：");
    for (QNode *cur = q->front; cur; cur = cur->next)
        printf("%d ", cur->data);
    printf("\n");
}

int dequeue(LinkQueue *q, ElemType *x) {
    if (!q->front) {
        printf("队列空，出队失败\n");
        return 0;
    }
    QNode *p = q->front;
    *x = p->data;
    q->front = p->next;
    if (q->rear == p) /* 最后一个元素 */
        q->rear = NULL;
    free(p);
    return 1;
}

int gethead(const LinkQueue *q, ElemType *x) {
    if (!q->front) {
        printf("队列空，无队头\n");
        return 0;
    }
    *x = q->front->data;
    printf("队头元素：%d\n", *x);
    return 1;
}

int length(const LinkQueue *q) {
    int len = 0;
    for (QNode *cur = q->front; cur; cur = cur->next) ++len;
    printf("队列长度：%d\n", len);
    return len;
}

void clear(LinkQueue *q) {
    QNode *cur = q->front;
    while (cur) {
        QNode *next = cur->next;
        free(cur);
        cur = next;
    }
    q->front = q->rear = NULL;
    printf("队列已清空\n");
}

void destroy(LinkQueue *q) {
    clear(q);
    printf("队列已销毁\n");
}

/* 主函数：循环菜单 */
int main(void) {
    LinkQueue Q;
    init(&Q);
    ElemType x;
    int sel;
    while (1) {
        printf("\n======== 链栈版队列菜单 ========\n");
        printf("1 init       2 enqueue    3 showqueue  4 dequeue\n");
        printf("5 gethead    6 length     7 clear      8 destroy\n");
        printf("0 清屏\n");
        printf("请选择：");
        if (scanf("%d", &sel) != 1) break;
        switch (sel) {
            case 1: init(&Q); break;
            case 2:
                printf("输入入队元素：");
                scanf("%d", &x);
                enqueue(&Q, x);
                break;
            case 3: showqueue(&Q); break;
            case 4:
                if (dequeue(&Q, &x))
                    printf("出队元素：%d\n", x);
                break;
            case 5: gethead(&Q, &x); break;
            case 6: length(&Q); break;
            case 7: clear(&Q); break;
            case 8: destroy(&Q); init(&Q); break;
            case 0: system("clear"); break;
            default: printf("无效选择\n");
        }
    }
    return 0;
}