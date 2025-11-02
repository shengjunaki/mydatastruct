#ifndef __SCLIST_H_
#define __SCLIST_H_

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#define elemtype int
typedef struct node
{
    elemtype data;
    struct node*next;
}node, *pnode;
typedef struct list
{
    pnode first;
    pnode last;
    int size;
}list;
void initsclist(list *list);
void push_back(list * list,elemtype x);
void push_fornt(list * list,elemtype x);
void show_list(list *list);
void pop_back(list *list);
void pop_fornt(list *list);
void insert_val(list *list ,int pos ,elemtype x);
node * find(list *list,elemtype key);
int length(list *list);
void delete_val(list *list,int key);
void sort(list *list);
void resver(list *list);
void clear(list *list);
void destroy(list *list);
void merge(list *lt,list *la,list *lb);
node *_buynode(elemtype x);

#endif