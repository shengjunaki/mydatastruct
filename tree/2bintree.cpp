#include <stdio.h>
#include <malloc.h>
#include <assert.h>
// ABC##DE##F##G#H##
struct bintreenode;
#define ElemType bintreenode *
typedef struct StackNode
{
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStack; // LinkStack 就是栈顶指针
/* 接口 */
int init(LinkStack *s); // 把栈顶置空
int isempty(const LinkStack *s);
int push(LinkStack *s, ElemType e);
int pop(LinkStack *s, ElemType *e);
int gettop(const LinkStack *s, ElemType *e);
void show(const LinkStack *s);
int length(const LinkStack *s);
void clear(LinkStack *s);
void destroy(LinkStack *s);

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

void xianorder(bintree *bt)
{
    xianorder(bt->root);
}
void xianorder(bintreenode *t)
{
    if (t)
    {
        LinkStack st;
        init(&st);
        push(&st, t);
        bintreenode *p;
        while (!isempty(&st))
        {
            pop(&st, &p);
            printf("%c ", p->data);
            if (p->rightchild)
                push(&st, p->rightchild);
            if (p->leftchild)
                push(&st, p->leftchild);
        }
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
        LinkStack st;
        init(&st);
        bintreenode *p;
        push(&st, t);
        while (!isempty(&st))
        {
            while (t && t->leftchild)
            {
                push(&st, t->leftchild);
                t = t->leftchild;
            }
            pop(&st, &p);
            printf("%c ", p->data);
            if (p->rightchild)
            {
                t = p->rightchild;

                if (t)
                {
                    push(&st, t);
                }
            }
        }
    }
}
int init(LinkStack *s)
{
    *s = NULL;
    return 1;
}
int isempty(const LinkStack *s)
{
    return *s == NULL;
}
int push(LinkStack *s, ElemType e)
{
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    if (!p)
        return 0;
    p->data = e;
    p->next = *s;
    *s = p;
    return 1;
}
int pop(LinkStack *s, ElemType *e)
{
    if (isempty(s))
        return 0;
    StackNode *p = *s;
    *e = p->data;
    *s = p->next;
    free(p);
    return 1;
}
int gettop(const LinkStack *s, ElemType *e)
{
    if (isempty(s))
        return 0;
    *e = (*s)->data;
    return 1;
}
void show(const LinkStack *s)
{
    printf("Stack(%d): ", length(s));
    StackNode *p = *s;
    /* 从栈顶往栈底打印 */
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int length(const LinkStack *s)
{
    int n = 0;
    StackNode *p = *s;
    while (p)
    {
        ++n;
        p = p->next;
    }
    return n;
}
void clear(LinkStack *s)
{
    ElemType tmp;
    while (!isempty(s))
        pop(s, &tmp);
}
void destroy(LinkStack *s)
{
    clear(s);
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
int main()
{
    char str[] = "ABC##DE##F##G#H##";
    bintree mytree;
    initbintree(&mytree, '#');
    createbintree4(&mytree, str);
    inorder(&mytree);
}