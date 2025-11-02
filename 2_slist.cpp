#include"2_slist.h"
void initlist(list *list)
{
    list->first=list->last=(node*)malloc(sizeof(node));
    assert(list->first!=NULL);
    list->first->next=NULL;
    list->size=0;
}
/*void push_back(list * list,elemtype x)
{
    // node *s=(node*)malloc(sizeof(node));
    // assert(s!=NULL);
    // s->data=x;
    // s->next=NULL;
    node *s=_buynode(x);
    list->last->next=s;
    list->last=s;
    ++list->size;
}
void push_fornt(list * list,elemtype x)
{
    // node *s=(node*)malloc(sizeof(node));
    // assert(s!=NULL);
    // s->data=x;
    node *s=_buynode(x);
    s->next=list->first->next;
    list->first->next=s;
    if(list->size==0)
    {
        list->last=s;
    }
    ++list->size;
}*/
void push_fornt(list* list,elemtype x)
{
    insert(list,begin(list),x);
}
void push_back(list* list,elemtype x)
{
    insert(list,end(list),x);
}
void show_list(list *list)
{
    node *p=list->first->next;
    while(p!=NULL)
    {
        printf("%d->",p->data);
        p=p->next;
    }
    printf("nul\n");
}
void pop_back(list *list)
{
    if(!list->size)return;
    node*p=list->first;
    for(int i=0;i<list->size-1;++i)
    {
        p=p->next;
    }
    free(list->last);
    list->last=p;
    p->next=NULL;
    --list->size;
}
void pop_fornt(list *list)
{
    if(!list->size)return;
    node *p=list->first->next;
    list->first->next=p->next;//笔记1.这里千万不要p=p->next;不然p就该走到下一个节点了
    free(p);
    if(list->size==1)
    {
        list->last=list->first;
    }
    --list->size;
}
void insert_pos(list *list ,elemtype x)
{
    node *s=(node*)malloc(sizeof(node));
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    node *p=list->first;
    while(p->next!=NULL&&p->next->data<x)
    {
        p=p->next;
    } 
    if(p->next==NULL)list->last=s;
    s->next=p->next;
    p->next=s;
    ++list->size;
}
node * find(list *list,elemtype key)
{
    node *p=list->first->next;
    while(p!=NULL&&p->data!=key)
    {
        p=p->next;
    }
    return p;
}
int length(list *list)
{
    return list->size;
}
void delete_pos(list *list,int pos);
void delete_val(list *list,int key)
{
    if(!list->size)return;
    node *p=find(list,key);
    if(p==NULL)
    {
        printf("not exit!");
        return;
    }
    if(p==list->last)
    {
        pop_back(list);
    }
    else
    {
        node *q=p->next;
        p->data=q->data;
        p->next=q->next;
        free(q);
        --list->size;
    }
}
void sort(list *list)
{
    if(list->size==0||list->size==1)return;
    node *s=list->first->next;
    node *q=s->next;
    list->last=s;
    list->last->next=NULL;
    while(q!=NULL)
    {
        s=q;
        q=q->next;

        node *p=list->first;
        while(p->next!=NULL&&p->next->data<s->data)
        {
            p=p->next;
        } 
        if(p->next==NULL)list->last=s;
        s->next=p->next;
        p->next=s;

    }
}
void resver(list *list)
{
    if(list->size==0||list->size==1)return;
    node *p=list->first->next;
    node *q=p->next;

    list->last=p;
    list->last->next=NULL;
    while(q!=NULL)
    {
        p=q;
        q=p->next;
        p->next=list->first->next;
        list->first->next=p;
    }
}
void clear(list *list)
{
    if(!list->size)return;
    node *p=list->first->next;
    while(p!=NULL)
    {
        list->first->next=p->next;
        free(p);
        p=list->first->next;
    }
    list->last=list->first;
    list->size=0;
}
void destroy(list *list)
{
    clear(list);
    free(list->first);
    list->first=list->last=NULL;
}
node *_buynode(elemtype x)
{
    node *s=(node*)malloc(sizeof(node));
    assert(s!=NULL);
    s->data=x;
    s->next=NULL;
    return s;
}
it begin(list *list){return list->first->next;}
it end(list* list){return list->last->next;}
void insert(list *list,it pos,elemtype x)
{
    node *p=list->first;
    while(p->next!=pos)
    {
        p=p->next;
    }
    node *s=_buynode(x);
    s->next=p->next;
    p->next=s;
    if(pos==NULL)list->last=s;
    ++list->size;
}
int main(){
    list mylist;
    initlist(&mylist);
    elemtype item;
    node *p=NULL;
    int select;
    while(select){
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
        scanf("%d",&select);
        switch(select)
        {
            case 1:
            printf("please input(-1 end)");
            while(scanf("%d",&item),item!=-1)
            {
                push_back(&mylist,item);
            }
            break;
            case 2:
            printf("please input(-1 end)");
            while(scanf("%d",&item),item!=-1)
            {
                push_fornt(&mylist,item);
            }
            break;
            case 3:
            show_list(&mylist);
            break;
            case 4:pop_back(&mylist);break;
            case 5:pop_fornt(&mylist);break;
            case 6:
            printf("please input:");
            scanf("%d",&item);
            insert_pos(&mylist,item);
            case 7:
            printf("please input the data want to find:");
            scanf("%d",&item);
            p=find(&mylist,item);
            if(p==NULL)printf("not exit!!!\n");
            case 8:
            printf("length is %d",length(&mylist));break;
            case 10:
            printf("please input the data to deleted:");
            scanf("%d",&item);
            delete_val(&mylist,item);
            break;
            case 11:sort(&mylist);break;
            case 12:resver(&mylist);break;
            case 13:clear(&mylist);break;
            default:printf("ERROR!!!");

        }
    }
    destroy(&mylist);
    return 0;
}