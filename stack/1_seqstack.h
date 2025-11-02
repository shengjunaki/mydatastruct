#ifndef __SEQSTACK__
#define __SEQSTACK__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define elemtype int
#define STACK_INIT_SIZE 8
typedef struct seqstack
{
    elemtype *base;
    int capacity;
    int top;
}seqstack;

void initstack(seqstack *s);

#endif