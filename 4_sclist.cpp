#include "4_sclist.h"
void initsclist(list *list)
{
    node *s = (node *)malloc(sizeof(node));
    assert(s != NULL);
    list->first = list->last = s;
    list->last->next = list->first;
    list->size = 0;
}
node *_buynode(elemtype x)
{
    node *s = (node *)malloc(sizeof(node));
    assert(s != NULL);
    s->data = x;
    s->next = NULL;
    return s;
}
void push_back(list *list, elemtype x)
{
    node *s = _buynode(x);
    list->last->next = s;
    list->last = s;
    list->last->next = list->first;
    ++list->size;
}
void push_fornt(list *list, elemtype x)
{
    node *s = _buynode(x);
    s->next = list->first->next;
    list->first->next = s;
    if (list->first == list->last)
        list->last = s;
    ++list->size;
}
void show_list(list *list)
{
    node *p = list->first->next;
    while (p != list->first)
    {
        printf("%d-> ", p->data);
        p = p->next;
    }
    printf("nul\n");
}
void pop_back(list *list)
{
    if (list->size == 0)
        return;
    node *p = list->first;
    while (p->next != list->last)
    {
        p = p->next;
    }
    free(list->last);
    list->last = p;
    list->last->next = list->first;
    --list->size;
}
void pop_fornt(list *list)
{
    if (list->size == 0)
        return;
    node *p = list->first->next;
    list->first->next = p->next;
    free(p);
    if (list->size == 1)
    {
        list->last = list->first;
    }
    --list->size;
}
void insert_val(list *list, elemtype x)
{
    node *p = list->first;
    while (p->next != list->last && p->next->data < x)
    {
        p = p->next;
    }
    if (p->next == list->last && p->next->data < x)
    {
        push_back(list, x);
    }
    else
    {
        node *s = _buynode(x);
        s->next = p->next;
        p->next = s;
        ++list->size;
    }
}
node *find(list *list, elemtype key)
{
    if (list->size == 0)
    {
        printf("no element\n");
        return NULL;
    }
    node *p = list->first->next;
    while (p != list->first && p->data != key)
    {
        p = p->next;
    }
    if (p == list->first)
        return NULL;
    return p;
}
int length(list *list)
{
    return list->size;
}
void delete_val(list *list, int key)
{
    if (list->size == 0)
        return;
    node *p = find(list, key);
    if (!p)
    {
        printf("not exit!!!\n");
        return;
    }
    if (p == list->last)
        pop_back(list);
    else
    {
        node *q = p->next;
        p->data = q->data;
        p->next = q->next;
        free(q);
        --list->size;
    }
}
void sort(list *list)
{
    if (list->size == 0 || list->size == 1)
        return;
    node *s = list->first->next;
    node *q = s->next;
    list->last->next = NULL;
    list->last = s;
    list->last->next = list->first;
    while (q != NULL)
    {
        s = q;
        q = q->next;
        node *p = list->first;
        while (p->next != list->last && p->next->data < s->data)
        {
            p = p->next;
        }
        if (p->next == list->last && p->next->data < s->data)
        {
            s->next = list->last->next;
            list->last->next = s;
            list->last = s;
        }
        else
        {
            s->next = p->next;
            p->next = s;
        }
    }
}
void resver(list *list)
{
    if (list->size == 0 || list->size == 1)
        return;
    node *p = list->first->next;
    node *q = p->next;
    list->last->next = NULL;
    list->last = p;
    list->last->next = list->first;
    while (q)
    {
        p = q;
        q = q->next;
        p->next = list->first->next;
        list->first->next = p;
    }
}
void clear(list *list)
{
    node *p=list->first->next;
    while(p!=list->first)
    {
        list->first->next=p->next;
        free(p);
        p=list->first->next;
    }
    list->last=list->first;
    list->last->next=list->first;
    list->size=0;
}
void destroy(list *list)
{
    clear(list);
    free(list->first);
    list->first=list->last=NULL;
}
int main()
{
    list mylist;
    initsclist(&mylist);

    elemtype item;
    node *p = NULL;
    int select;
    while (select)
    {
        printf("********************************************\n");
        printf("*1.push_back*************2.push_fornt*******\n");
        printf("*3.show_list*************4.pop_back*********\n");
        printf("*5.pop_front*************6.insert_val*******\n");
        printf("*7.find******************8.lenght***********\n");
        printf("*no.delete_pos***********10.delete_val*******\n");
        printf("11.sort*****************12.resver***********\n");
        printf("13.clear**************auto:destroy**********\n");
        printf("*0.quit_system******************************\n");
        printf("********************************************\n");
        printf("please input:>");
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            printf("please input(-1 end)");
            while (scanf("%d", &item), item != -1)
            {
                push_back(&mylist, item);
            }
            break;
        case 2:
            printf("please input(-1 end)");
            while (scanf("%d", &item), item != -1)
            {
                push_fornt(&mylist, item);
            }
            break;
        case 3:
            show_list(&mylist);
            break;
        case 4:
            pop_back(&mylist);
            break;
        case 5:
            pop_fornt(&mylist);
            break;
        case 6:
            printf("please input:");
            scanf("%d", &item);
            insert_val(&mylist, item);
            break;
        case 7:
            printf("please input the data want to find:");
            scanf("%d", &item);
            p = find(&mylist, item);
            if (p == NULL)
                printf("not exit!!!\n");
        case 8:
            printf("length is %d\n", length(&mylist));
            break;
        case 10:
            printf("please input the data to deleted:");
            scanf("%d", &item);
            delete_val(&mylist, item);
            break;
        case 11:
            sort(&mylist);
            break;
        case 12:
            resver(&mylist);
            break;
        case 13:
            clear(&mylist);
            break;
        default:
            printf("ERROR!!!");
        }
    }
    // destroy(&mylist);
    return 0;
}