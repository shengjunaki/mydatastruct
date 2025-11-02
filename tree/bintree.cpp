#include <stdio.h>
#include <malloc.h>
#include <assert.h>
// ABC##DE##F##G#H##
#define elemtype char
typedef struct bintreenode
{
    elemtype data;
    struct bintreenode *leftchild;
    struct bintreenode *rightchild;
} bintreenode;
typedef struct bintree
{
    bintreenode *root;
    elemtype refvalue;
} bintree;
void createbintree1(bintree *bt);
void createbintree1(bintree *bt, bintreenode **t);
void createbintree2(bintree *bt);
void createbintree2(bintree *bt, bintreenode *&t);
void createbintree3(bintree *bt);
bintreenode *createbintree3_(bintree *bt);
void createbintree4(bintree *bt, char *str);
void createbintree4(bintree *bt, bintreenode *&t, char *&str);
void initbintree(bintree *bt, elemtype ref);

void inorder(bintree *bt);
void inorder(bintreenode *t);
void xianorder(bintree *bt);
void xianorder(bintreenode *t);
void houorder(bintree *bt);
void houorder(bintreenode *t);

void Levlorder(bintree *bt);
void Levlorder(bintreenode *t);

int size(bintree *bt);
int size(bintreenode *t);

int high(bintree *bt);
int high(bintreenode *t);
bintreenode *search(bintree *bt, elemtype key);
bintreenode *search(bintreenode *t, elemtype key);
bintreenode *parent(bintree *bt,bintreenode *p);
bintreenode *parent(bintreenode* t,bintreenode *p);
bintreenode *leftchild(bintreenode *p);
bintreenode *rightchild(bintreenode *p);
bool bintreeempty(bintree *bt);
void copy(bintree *bt1,bintree *bt2);
void copy(bintreenode *&t1,bintreenode *&t2);

void bintreeclear(bintree *bt);
void bintreeclear(bintreenode *&bt);

struct bintreenode;
#define ElemType bintreenode *

/* 链式队列结点 */
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode;

/* 链队列结构 */
typedef struct
{
    QNode *front, *rear;
} LinkQueue;
void init(LinkQueue *q);
int enqueue(LinkQueue *q, ElemType x);
void showqueue(const LinkQueue *q);
int dequeue(LinkQueue *q, ElemType *x);
int gethead(const LinkQueue *q, ElemType *x);
int length(const LinkQueue *q);
void clear(LinkQueue *q);
void destroy(LinkQueue *q);
bool queueisempty(LinkQueue *q);


/* 8个操作函数 */
void init(LinkQueue *q)
{
    q->front = q->rear = NULL;
}

int enqueue(LinkQueue *q, ElemType x)
{
    QNode *p = (QNode *)malloc(sizeof(QNode));
    if (!p)
    {
        printf("内存分配失败\n");
        return 0;
    }
    p->data = x;
    p->next = NULL;
    if (!q->rear) /* 空队列 */
        q->front = q->rear = p;
    else
    {
        q->rear->next = p;
        q->rear = p;
    }
    return 1;
}

void showqueue(const LinkQueue *q)
{
    if (!q->front)
    {
        printf("队列空\n");
        return;
    }
    printf("队列内容：");
    for (QNode *cur = q->front; cur; cur = cur->next)
        printf("%d ", cur->data);
    printf("\n");
}

int dequeue(LinkQueue *q, ElemType *x)
{
    if (!q->front)
    {
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

int gethead(const LinkQueue *q, ElemType *x)
{
    if (!q->front)
    {
        printf("队列空，无队头\n");
        return 0;
    }
    *x = q->front->data;
    return 1;
}

int length(const LinkQueue *q)
{
    int len = 0;
    for (QNode *cur = q->front; cur; cur = cur->next)
        ++len;
    printf("队列长度：%d\n", len);
    return len;
}
bool queueisempty(LinkQueue *q)
{
    return q->front == NULL;
}
void clear(LinkQueue *q)
{
    QNode *cur = q->front;
    while (cur)
    {
        QNode *next = cur->next;
        free(cur);
        cur = next;
    }
    q->front = q->rear = NULL;
    printf("队列已清空\n");
}

void destroy(LinkQueue *q)
{
    clear(q);
    printf("队列已销毁\n");
}
void initbintree(bintree *bt, elemtype ref)
{
    bt->root = NULL;
    bt->refvalue = ref;
}
void createbintree1(bintree *bt)
{
    createbintree1(bt, &(bt->root));
}
void createbintree1(bintree *bt, bintreenode **t)
{
    elemtype item;
    scanf("%c", &item);
    if (item == bt->refvalue)
        (*t) = NULL;
    else
    {
        (*t) = (bintreenode *)malloc(sizeof(bintreenode));
        assert((*t) != NULL);
        (*t)->data = item;
        createbintree1(bt, &((*t)->leftchild));
        createbintree1(bt, &((*t)->rightchild));
    }
}
void createbintree2(bintree *bt)
{
    createbintree2(bt, bt->root);
}
void createbintree2(bintree *bt, bintreenode *&t)
{
    elemtype item;
    scanf("%c", &item);
    if (item == bt->refvalue)
        t = NULL;
    else
    {
        t = (bintreenode *)malloc(sizeof(bintreenode));
        assert(t != NULL);
        t->data = item;
        createbintree2(bt, t->leftchild);
        createbintree2(bt, t->rightchild);
    }
}
void createbintree3(bintree *bt)
{
    bt->root = createbintree3_(bt);
}
bintreenode *createbintree3_(bintree *bt)
{
    elemtype item;
    scanf("%c", &item);
    if (item == bt->refvalue)
        return NULL;
    else
    {
        bintreenode *t = (bintreenode *)malloc(sizeof(bintreenode));
        t->data = item;
        t->leftchild = createbintree3_(bt);
        t->rightchild = createbintree3_(bt);
        return t;
    }
}
void createbintree4(bintree *bt, char *str)
{
    createbintree4(bt, bt->root, str);
}
void createbintree4(bintree *bt, bintreenode *&t, char *&str)
{
    if (*str == bt->refvalue)
        t = NULL;
    else
    {
        t = (bintreenode *)malloc(sizeof(bintreenode));
        assert(t != NULL);
        t->data = *str;
        createbintree4(bt, t->leftchild, ++str);
        createbintree4(bt, t->rightchild, ++str);
    }
}
void inorder(bintree *bt)
{
    inorder(bt->root);
}
void inorder(bintreenode *t)
{
    if (t)
    {
        inorder(t->leftchild);
        printf("%c", t->data);
        inorder(t->rightchild);
    }
}
void xianorder(bintree *bt)
{
    xianorder(bt->root);
}
void xianorder(bintreenode *t)
{
    if (t)
    {
        printf("%c", t->data);
        xianorder(t->leftchild);
        xianorder(t->rightchild);
    }
}
void houorder(bintree *bt)
{
    houorder(bt->root);
}
void houorder(bintreenode *t)
{
    if (t)
    {
        houorder(t->leftchild);
        houorder(t->rightchild);
        printf("%c", t->data);
    }
}
void Levlorder(bintree *bt)
{
    Levlorder(bt->root);
}
void Levlorder(bintreenode *t)
{
    if (t)
    {
        bintreenode *v;
        LinkQueue Q;
        init(&Q);
        enqueue(&Q, t);
        while (!queueisempty(&Q))
        {
            gethead(&Q, &v);
            dequeue(&Q, &v);
            printf("%c", v->data);
            if (v->leftchild)
                enqueue(&Q, v->leftchild);
            if (v->rightchild)
                enqueue(&Q, v->rightchild);
        }
    }
}
int size(bintree *bt)
{
    return size(bt->root);
}
int size(bintreenode *t)
{
    if(!t)return 0;
    return size(t->leftchild)+size(t->rightchild)+1;
}
int high(bintree *bt)
{
    return high(bt->root);
}
int high(bintreenode*t)
{
    if(!t)return 0;
    int left=high(t->leftchild);
    int right=high(t->rightchild);
    return (right>left?right:left)+1;
}
bintreenode *search(bintree *bt, elemtype key)
{
    return search(bt->root,key);
}
bintreenode *search(bintreenode *t, elemtype key)
{
    if(!t)return NULL;
    if(t->data==key)return t;
    bintreenode *p=search(t->leftchild,key);
    if(p)return p;
    return search(t->rightchild,key);
}
bintreenode *parent(bintree *bt,bintreenode *p)
{
    return parent(bt->root,p);
}
bintreenode *parent(bintreenode* t,bintreenode *p)
{
    if(!t||!p)return NULL;
    if(t->leftchild==p||t->rightchild==p)return t;
    bintreenode*q=parent(t->leftchild,p);
    if(q)return q;
    return parent(t->rightchild,p);
}
bintreenode *leftchild(bintreenode *p)
{
    if(p) return p->leftchild;
    return NULL;
}
bintreenode *rightchild(bintreenode *p)
{
    if(p) return p->rightchild;
    return NULL;
}
bool bintreeempty(bintree *bt)
{
    return bt->root==NULL;
}
void copy(bintree *bt1,bintree *bt2)
{
    copy(bt1->root,bt2->root);
}
void copy(bintreenode *&t1,bintreenode *&t2)
{
    if(!t2)t1=NULL;
    else
    {    
        t1=(bintreenode*)malloc(sizeof(bintreenode));
        assert(t1!=NULL);
        t1->data=t2->data;
        copy(t1->leftchild,t2->leftchild);
        copy(t1->rightchild,t2->rightchild);
    }
}
void bintreeclear(bintree *bt)
{
    bintreeclear(bt->root);
}
void bintreeclear(bintreenode *&t)
{
    if(t)
    {
        bintreeclear(t->leftchild);
        bintreeclear(t->rightchild); 
        free(t);
        t=NULL;
    }
}

int main()
{
    char str[] = "ABC##DE##F##G#H##";
    char str1[] = "ABC##D##G#H##";
    bintree mytree;
    initbintree(&mytree, '#');
    createbintree4(&mytree, str);
    bintree youtree;
    initbintree(&youtree,'#');
    copy(&youtree,&mytree);
    // printf("size=%d\n",size(&mytree));
    // printf("high=%d\n",high(&mytree));
    // bintreenode *p=search(&mytree,'D');
    // bintreenode *paret=parent(&mytree,p);
    // printf("%c\n",paret->data);
    // printf("%p",p);
    // Levlorder(&mytree);
    // printf("\n");
    // xianorder(&mytree);
    // printf("\n");
    // inorder(&mytree);
    // printf("\n");
    // houorder(&mytree);
    // printf("\n");
    bintreeclear(&mytree);
    bintreeclear(&youtree);
    return 0;
}
