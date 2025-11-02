#include"3_staticlist.h"
#include<iostream>
using namespace std;
int malloc_sl(staticlist &space)
{
    int i=space[1].cur;
    if(space[1].cur!=0)space[1].cur=space[i].cur;
    return i;
}
void initslist(staticlist &space)
{
    for(int i=1;i<MAX_SIZE-1;++i)
    {
        space[i].cur=i+1;
    }
    space[MAX_SIZE-1].cur=0;
    space[0].cur=-1;
}
void insert(staticlist &space,elemtype x)
{
    int i=malloc_sl(space);
    if(i==0)
    {
        printf("malloc error!!\n");
        return;
    }
    space[i].data=x;
    if(space[0].cur==-1)
    {
        space[i].cur=-1;
    }
    else
    {
        space[i].cur=space[0].cur;
    }
    space[0].cur=i;
}
void showslist(staticlist &space)
{
    int i=space[0].cur;
    while(i!=-1)
    {
        printf("%c-->",space[i].data);
        i=space[i].cur;
    }
    printf("nul\n");
}
void deletee(staticlist &space)
{
    int i=space[0].cur;
    space[0].cur=space[i].cur;
    // space[i].cur=space[1].cur;
    // space[1].cur=i;
    free_s(space,i);
}
void free_s(staticlist &space,int k)
{
    space[k].cur=space[1].cur;
    space[1].cur=k;
}
int main(){
    staticlist sl;
    initslist(sl);
    for(int i=0;i<3;++i)
    {
        insert(sl,'A'+i);
    }
    showslist(sl);
    system("pause");
    return 0;
}