#ifndef __SEQLIST_H__
#define __SEQLIST_H__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>

#define SEQLIST_INIT_SIZE 8
#define INC_SIZE 3
typedef int elemtype;
typedef struct seqlist
{
    elemtype *base;
    int capacity;
    int size;
}seqlist;
bool inc(seqlist*list);
void initseqlist(seqlist *list);
void push_back(seqlist * list,elemtype x);
void push_fornt(seqlist * list,elemtype x);
void show_list(seqlist *list);
void pop_back(seqlist *list);
void pop_fornt(seqlist *list);
void insert_pos(seqlist *list ,int pos ,elemtype x);
int find(seqlist *list,elemtype key);
int length(seqlist *list);
void delete_pos(seqlist *list,int pos);
void delete_val(seqlist *list,int key);
void sort(seqlist *list);
void resver(seqlist *list);
void clear(seqlist *list);
void destroy(seqlist *list);
void merge(seqlist *lt,seqlist *la,seqlist *lb);
#endif
