#include <assert.h>
#include <stdio.h>
#include <malloc.h>

#define elemtype int
typedef struct listnode
{
    elemtype data;
    struct listnode *next;
} listnode;
typedef listnode *list;
void initlist(list *head);
void createlist_head(list *head);
void createlist_head1(list *head);
void createlist_back(list *head);
void showlist(list head);
void createlist_back1(list *head);
void initlist(list *head)
{
    *head = (listnode *)malloc(sizeof(listnode));
    assert(*head != NULL);
    (*head)->next = NULL;
}
void createlist_back(list *head)
{
    *head = (listnode *)malloc(sizeof(listnode));
    assert(*head != NULL);
    (*head)->data = 1;
    (*head)->next = NULL;
    listnode *p = *head;
    for (int i = 2; i < 10; ++i)
    {
        listnode *s = (listnode *)malloc(sizeof(listnode));
        assert(s != NULL);
        s->data = i;
        s->next = NULL;
        p->next = s;
        p = s;
    }
}
void createlist_head(list *head)
{
    *head = (listnode *)malloc(sizeof(listnode));
    assert(*head != NULL);
    (*head)->data = 1;
    (*head)->next = NULL;
    for (int i = 2; i < 10; ++i)
    {
        listnode *s = (listnode *)malloc(sizeof(listnode));
        assert(s != NULL);
        s->data = i;
        s->next = *head;
        *head = s;
    }
}
void showlist(list head)
{
    //    listnode *p=head;
    listnode *p = head->next;
    while (p != NULL)
    {
        printf("%d-->", p->data);
        p = p->next;
    }
    printf("NONE");
}
void createlist_head1(list *head)
{
    for (int i = 1; i < 10; ++i)
    {
        listnode *s = (listnode *)malloc(sizeof(listnode));
        assert(s != NULL);
        s->data = i;
        s->next = (*head)->next;
        (*head)->next = s;
    }
}
// 非常之牛逼！！！！
void createlist_back1(list *head)
{
    listnode *p = *head;
    for (int i = 1; i < 10; ++i)
    {
        p = p->next = (listnode *)malloc(sizeof(listnode)); // 先p->next=new 后p=next
        assert(p != NULL);
        p->data = i;
        p->next = NULL;
    }
}
int main()
{
    list mylist;
    initlist(&mylist);
    createlist_back1(&mylist);
    showlist(mylist);
    system("pause");
    return 0;
}
