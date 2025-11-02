#ifndef LINK_STACK_H
#define LINK_STACK_H

typedef int ElemType;
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;   // LinkStack 就是栈顶指针
/* 接口 */
int  init(LinkStack *s);        // 把栈顶置空
int  isempty(const LinkStack *s);
int  push(LinkStack *s, ElemType e);
int  pop(LinkStack *s, ElemType *e);
int  gettop(const LinkStack *s, ElemType *e);
void show(const LinkStack *s);
int  length(const LinkStack *s);
void clear(LinkStack *s);
void destroy(LinkStack *s);
#include <stdio.h>
#include <stdlib.h>
#endif

int init(LinkStack *s) {
    *s = NULL;
    return 1;
}
int isempty(const LinkStack *s) {
    return *s == NULL;
}
int push(LinkStack *s, ElemType e) {
    StackNode *p = (StackNode*)malloc(sizeof(StackNode));
    if (!p) return 0;
    p->data = e;
    p->next = *s;
    *s = p;
    return 1;
}
int pop(LinkStack *s, ElemType *e) {
    if (isempty(s)) return 0;
    StackNode *p = *s;
    *e = p->data;
    *s = p->next;
    free(p);
    return 1;
}
int gettop(const LinkStack *s, ElemType *e) {
    if (isempty(s)) return 0;
    *e = (*s)->data;
    return 1;
}
void show(const LinkStack *s) {
    printf("Stack(%d): ", length(s));
    StackNode *p = *s;
    /* 从栈顶往栈底打印 */
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int length(const LinkStack *s) {
    int n = 0;
    StackNode *p = *s;
    while (p) { ++n; p = p->next; }
    return n;
}
void clear(LinkStack *s) {
    ElemType tmp;
    while (!isempty(s))
        pop(s, &tmp);
}
void destroy(LinkStack *s) {
    clear(s);
}
int main(void) {
    LinkStack s;
    int choice, ok, x;
    init(&s);
    do {
        printf("\n=== LinkStack Menu ===\n");
        printf("1-init 2-isfull 3-isempty 4-push 5-pop 6-gettop\n");
        printf("7-show 8-length 9-clear 10-destroy 0-exit\n");
        printf("select: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:  ok = init(&s);   printf("init %s\n", ok ? "ok" : "fail"); break;
        case 3:  printf("isempty=%d\n", isempty(&s)); break;
        case 4:  printf("input elem to push: ");
                 scanf("%d", &x);
                 ok = push(&s, x);
                 printf("push %s\n", ok ? "ok" : "fail"); break;
        case 5:  ok = pop(&s, &x);
                 printf("pop %s", ok ? "ok" : "fail(stack empty)");
                 if (ok) printf(", elem=%d", x);
                 printf("\n"); break;
        case 6:  ok = gettop(&s, &x);
                 printf("gettop %s", ok ? "ok" : "fail(stack empty)");
                 if (ok) printf(", top=%d", x);
                 printf("\n"); break;
        case 7:  show(&s); break;
        case 8:  printf("length=%d\n", length(&s)); break;
        case 9:  clear(&s); printf("cleared\n"); break;
        case 10: destroy(&s); printf("destroyed\n"); break;
        case 0:  printf("bye.\n"); break;
        default: printf("invalid choice\n");
        }
    } while (choice != 0);
    return 0;
}