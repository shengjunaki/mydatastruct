#ifndef __STATICLIST_H_
#define __STATICLIST_H_

#include<stdio.h>
#define elemtype char
#define MAX_SIZE 20

typedef struct listnode
{
    elemtype data;
    int cur;
}listnode;
typedef listnode staticlist[MAX_SIZE];
int malloc_sl(staticlist &space);
void free_s(staticlist &space,int k);
void initslist(staticlist &space);
void insert(staticlist &space,elemtype x);
void showslist(staticlist &space);
void deletee(staticlist &space);

#endif 