#include"seqlist.h"
bool inc(seqlist*list)
{
    elemtype *newbase=(elemtype*)realloc(list->base,sizeof(elemtype)*(list->capacity+INC_SIZE));
    if(newbase==NULL)
    {
        printf("realloc error!!!");
        return false;
    }
    list->base=newbase;
    list->capacity+=INC_SIZE;
    return true;
}
void initseqlist(seqlist *list)
{
    list->base=(elemtype*)malloc(sizeof(elemtype)*SEQLIST_INIT_SIZE);
    assert(list->base!=NULL);
    list->capacity=SEQLIST_INIT_SIZE;
    list->size=0;
}
void push_back(seqlist * list,elemtype x)
{
    if(list->size==list->capacity&&!inc(list))
    {
        printf("enough,%d can't push in\n",x);
        return;
    }
    list->base[list->size]=x;
    list->size++;
}
void push_fornt(seqlist * list,elemtype x)
{
    if(list->size==list->capacity&&!inc(list))
    {
        printf("enough!!!,%d can't push in",x);
        return;
    }
    for(int i=list->size;i>0;--i)
    {
        list->base[i]=list->base[i-1];
    }
    list->base[0]=x;
    list->size++;
}
void show_list(seqlist *list){
    for(int i=0;i<list->size;++i)
    {
        printf("%d ",list->base[i]);
    }
    printf("\n");
}
void pop_back(seqlist *list)
{
    if(list->size==0)
    {
        printf("NONE,you can't delete anything\n");
        return;
    }
    --list->size;
}
void pop_fornt(seqlist *list)
{
    if(list->size==0)
    {
        printf("NONE,you can't delete anything\n");
        return;
    }
    for(int i=1;i<list->size;++i)
    {
        list->base[i-1]=list->base[i];
    }
    --list->size;
}
void insert_pos(seqlist *list ,int pos ,elemtype x){
    if(pos<0||pos>list->size)
    {
        printf("pos illegal!!!\n");
        return;
    }
    if(list->size==list->capacity&&!inc(list))
    {
        printf("enough!!!,%d can't insert in",x);
        return;
    }
    for(int i=list->size;i>pos;--i)
    {
        list->base[i]=list->base[i-1];
    }
    list->base[pos]=x;
    ++list->size;
}
int find(seqlist *list,elemtype key)
{
    for(int i=0;i<list->size;i++)
    {
        if(list->base[i]==key)
        {
            return i;
        }
    }
    return -1;
}
int length(seqlist *list){return list->size;}
void delete_pos(seqlist *list,int pos)
{
    if(pos<0||pos>list->size)
    {
        printf("pos illegal!!!\n");
        return;
    }
    for(int i=pos;i<list->size-1;++i){
         list->base[i]=list->base[i+1];
    }
    list->size--;
}
void delete_val(seqlist *list,int key)
{
    int pos=find(list,key);
    if(pos==-1)
    {
        printf("no this value!!!\n");
        return;
    }
    delete_pos(list,pos);
}
void sort(seqlist *list)
{
    for(int i=0;i<list->size-1;++i)
    {
        for(int j=0;j<list->size-i-1;++j)
        {
            if(list->base[j]>list->base[j+1])
            {
                elemtype tmp=list->base[j];
                list->base[j]=list->base[j+1];
                list->base[j+1]=tmp;
            }
        }
    }
}
void resver(seqlist *list)
{
    if(list->size==0||list->size==1)return;
    int low=0,high=list->size;
    elemtype tmp;
    while(low<high)
    {
        tmp=list->base[low];
        list->base[low]=list->base[high];
        list->base[high]=tmp;
        low++;
        high--;
    }
}
void clear(seqlist *list)
{
    list->size=0;
}
void destroy(seqlist *list)
{
    free(list->base);
    list->base=NULL;
    list->capacity=0;
    list->size=0;
}
void merge(seqlist *lt,seqlist *la,seqlist *lb){
    int ia=0,ib=0,ic=0;
    lt->capacity=la->size+lb->size;
    lt->base=(elemtype*)malloc(sizeof(elemtype)*lt->capacity);
    assert(lt->base!=NULL);
    while(ia<lt->capacity&&ib<lt->capacity)
    {
        if(la->base[ia]<lb->base[ib])lt->base[ic++]=la->base[ia++];
        else lt->base[ic++]=lb->base[ib++];
    }
    while(ia<la->size){
        lt->base[ic++]=la->base[ia++];
    }
    while(ib<lb->size){
        lt->base[ic++]=lb->base[ib++];
    }
    lt->size=lt->capacity;

}
/*int main(){
    seqlist mylist;
    initseqlist(&mylist);
    int select=1;
    int pos;
    elemtype item;
    while(select){
        printf("********************************************\n");
        printf("*1.push_back*************2.push_fornt*******\n");
        printf("*3.show_list*************4.pop_back*********\n");
        printf("*5.pop_front*************6.insert_pos*******\n");
        printf("*7.find******************8.lenght***********\n");
        printf("*9.delete_pos***********10.delete_val*******\n");
        printf("11.sort*****************12.resver***********\n");
        printf("13.clear**************auto:destroy**********\n");
        printf("*0.quit_system******************************\n");
        printf("********************************************\n");
        printf("please input:>");
        scanf("%d",&select);
        if(!select)break;
        switch (select)
        {
        case  1:printf("please input(-1)end:>");
                while(scanf("%d",&item),item!=-1)
                {
                     push_back(&mylist,item);
                }
                break;
        case  2:printf("please input(-1)end:>");
                while(scanf("%d",&item),item!=-1)
                {
                     push_fornt(&mylist,item);
                }
                break;
        case  3:show_list(&mylist);
                break;
        case  4:pop_back(&mylist);
                break;
        case  5:pop_fornt(&mylist);
                break;
        case  6:printf("please input pos and data:>");
                scanf("%d %d",&pos,&item);
                insert_pos(&mylist,pos,item);
                break;
        case  7:printf("please input the data to found:>");
                scanf("%d",&item);
                pos=find(&mylist,item);
                if(pos==-1)printf("not found!\n");
                else printf("index is %d\n",pos);
                break;
        case  8:printf("length is %d\n",length(&mylist));
                break;
        case  9:printf("input pos\n");
                scanf("%d",&pos);
                delete_pos(&mylist,pos);
                break;
        case 10:printf("input value\n");
                scanf("%d",&item);
                delete_val(&mylist,item);
                break;
        case 11:sort(&mylist);break;
        case 12:resver(&mylist);break;
        case 13:clear(&mylist);break;
        default:printf("error!!!\n");break;
        }
    }
    destroy(&mylist);
    return 0;
} */
int main(){
    seqlist mylist,youlist,list;
    initseqlist(&mylist);
    initseqlist(&youlist);
    push_back(&mylist,1);
    push_back(&mylist,3);
    push_back(&mylist,5);
    push_back(&mylist,7);
    push_back(&mylist,9);
    push_back(&youlist,2);
    push_back(&youlist,4);
    //push_back(&youlist,6);
    push_back(&youlist,8);
    //push_back(&youlist,10);
    merge(&list,&mylist,&youlist);
    show_list(&list);
    system("pause");
    return 0;
}
