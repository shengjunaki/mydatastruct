#ifndef SEQ_STACK_H
#define SEQ_STACK_H

#define MAXSIZE 100
typedef int ElemType;

typedef struct {
    ElemType data[MAXSIZE];
    int top;        // 栈顶元素索引，-1 表示空栈
} SeqStack;

/* 接口 */
int  init(SeqStack *s);
int  isfull(const SeqStack *s);
int  isempty(const SeqStack *s);
int  push(SeqStack *s, ElemType e);
int  pop(SeqStack *s, ElemType *e);
int  gettop(const SeqStack *s, ElemType *e);
void show(const SeqStack *s);
int  length(const SeqStack *s);
void clear(SeqStack *s);
void destroy(SeqStack *s);


#include <stdio.h>
#endif

int init(SeqStack *s) {
    s->top = -1;
    return 1;
}
int isfull(const SeqStack *s) {
    return s->top == MAXSIZE - 1;
}
int isempty(const SeqStack *s) {
    return s->top == -1;
}
int push(SeqStack *s, ElemType e) {
    if (isfull(s)) return 0;
    s->data[++(s->top)] = e;
    return 1;
}
int pop(SeqStack *s, ElemType *e) {
    if (isempty(s)) return 0;
    *e = s->data[(s->top)--];
    return 1;
}
int gettop(const SeqStack *s, ElemType *e) {
    if (isempty(s)) return 0;
    *e = s->data[s->top];
    return 1;
}
void show(const SeqStack *s) {
    printf("Stack(%d): ", length(s));
    for (int i = 0; i <= s->top; ++i)
        printf("%d ", s->data[i]);
    printf("\n");
}
int length(const SeqStack *s) {
    return s->top + 1;
}
void clear(SeqStack *s) {
    s->top = -1;
}
void destroy(SeqStack *s) {
    clear(s);
}

int main(void) {
    SeqStack s;
    int choice, ok, x;
    init(&s);
    do {
        printf("\n=== SeqStack Menu ===\n");
        printf("1-init 2-isfull 3-isempty 4-push 5-pop 6-gettop\n");
        printf("7-show 8-length 9-clear 10-destroy 0-exit\n");
        printf("select: ");
        if (scanf("%d", &choice) != 1) break;
        switch (choice) {
        case 1:  ok = init(&s);   printf("init %s\n", ok ? "ok" : "fail"); break;
        case 2:  printf("isfull=%d\n", isfull(&s)); break;
        case 3:  printf("isempty=%d\n", isempty(&s)); break;
        case 4:  printf("input elem to push: ");
                 scanf("%d", &x);
                 ok = push(&s, x);
                 printf("push %s\n", ok ? "ok" : "fail(stack full)"); break;
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