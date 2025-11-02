#ifndef __SLIST_H_
#define __SLIST_H_
#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#define elemtype int
typedef struct node
{
    elemtype data;
    struct node* next;
}node,*pnode;
typedef struct list
{
    pnode first;
    pnode last;
    size_t size;
}list;
void initlist(list *list);
void push_back(list * list,elemtype x);
void push_fornt(list * list,elemtype x);
void show_list(list *list);
void pop_back(list *list);
void pop_fornt(list *list);
void insert_pos(list *list ,int pos ,elemtype x);
node * find(list *list,elemtype key);
int length(list *list);
void delete_pos(list *list,int pos);
void delete_val(list *list,int key);
void sort(list *list);
void resver(list *list);
void clear(list *list);
void destroy(list *list);
void merge(list *lt,list *la,list *lb);
//////////////////////////////////////////////////////
typedef node* it;
node *_buynode(elemtype x);
it begin(list *list);
it end(list *list);
void insert(list *list,it pos,elemtype x);
#endif