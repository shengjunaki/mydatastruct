#include <stdio.h>
#include <stdlib.h>

#define MAX 30
typedef int ElemType;

/* 顺序循环队列结构 */
typedef struct
{
    ElemType data[MAX];
    int front, rear;
} SeqQueue;

/* 8个操作函数 */
void init(SeqQueue *q)
{
    q->front = q->rear = 0;
}

int enqueue(SeqQueue *q, ElemType x)
{
    if ((q->rear + 1) % MAX == q->front)
    {
        printf("队列满，入队失败\n");
        return 0;
    }
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
    return 1;
}

void showqueue(const SeqQueue *q)
{
    if (q->front == q->rear)
    {
        printf("队列空\n");
        return;
    }
    printf("队列内容：");
    for (int i = q->front; i != q->rear; i = (i + 1) % MAX)
        printf("%d ", q->data[i]);
    printf("\n");
}

int dequeue(SeqQueue *q, ElemType *x)
{
    if (q->front == q->rear)
    {
        printf("队列空，出队失败\n");
        return 0;
    }
    *x = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return 1;
}

int gethead(const SeqQueue *q, ElemType *x)
{
    if (q->front == q->rear)
    {
        printf("队列空，无队头\n");
        return 0;
    }
    *x = q->data[q->front];
    printf("队头元素：%d\n", *x);
    return 1;
}

int length(const SeqQueue *q)
{
    int len = (q->rear - q->front + MAX) % MAX;
    printf("队列长度：%d\n", len);
    return len;
}

void clear(SeqQueue *q)
{
    q->front = q->rear = 0;
    printf("队列已清空\n");
}

void destroy(SeqQueue *q)
{
    clear(q);
    printf("队列已销毁\n");
}

/* 主函数：循环菜单 */
int main(void)
{
    SeqQueue Q;
    init(&Q);
    ElemType x;
    int sel=1;
    while (sel)
    {
        printf("\n======== 顺序栈版队列菜单 ========\n");
        printf("1 init       2 enqueue    3 showqueue  4 dequeue\n");
        printf("5 gethead    6 length     7 clear      8 destroy\n");
        printf("0 清屏\n");
        printf("请选择：");
        if (scanf("%d", &sel) != 1)
            break;
        switch (sel)
        {
        case 1:
            init(&Q);
            break;
        case 2:
            printf("输入入队元素：");
            scanf("%d", &x);
            enqueue(&Q, x);
            break;
        case 3:
            showqueue(&Q);
            break;
        case 4:
            if (dequeue(&Q, &x))
                printf("出队元素：%d\n", x);
            break;
        case 5:
            gethead(&Q, &x);
            break;
        case 6:
            length(&Q);
            break;
        case 7:
            clear(&Q);
            break;
        case 8:
            destroy(&Q);
            init(&Q);
            break; /* 销毁后再初始化以便继续测试 */
        case 0:
            system("clear");
            break; /* Windows用cls */
        default:
            printf("无效选择\n");
        }
    }
    return 0;
}