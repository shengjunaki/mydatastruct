#ifndef _MATRIX_C
#define _MATRIX_C
#include<stdio.h>
#include<memory.h>
#include<assert.h>
#include<stdlib.h>
#define elemtype int
#define MAXSIZE 50

typedef struct Triple
{
    int i,j;
    elemtype e;
}Triple;
typedef struct
{
    Triple data[MAXSIZE];
    int mu,nu,tu;
}SMatrix;

void CreateMatirx(SMatrix *M);
void PrintMatrix(SMatrix *M);
void CopyMatrix(SMatrix *M,SMatrix *T);
void TransposeMatrix(SMatrix *M,SMatrix*T);
void FastTransposeMatrix(SMatrix *M,SMatrix*T);
#endif
void CreateMatirx(SMatrix *M)
{
    FILE *fp=fopen("data.txt","r");
    if(!fp)exit(1);
    fscanf(fp,"%d %d",&M->mu,&M->nu);
    int value,k=0;
    for (int i=0;i<M->mu;++i)
    {
        for(int j=0;j<M->nu;++j)
        {
            if(fscanf(fp,"%d",&value),value)
            {
                M->data[k].e=value;
                M->data[k].i=i;
                M->data[k].j=j;
                ++k;
            }
        }
    }
    M->tu=k;
}
void PrintMatrix(SMatrix *M)
{
    printf("%d %d\n",M->mu,M->nu);
    for(int i=0;i<M->tu;++i)
    {
        printf("(%d,%d,%d)\n",M->data[i].i,M->data[i].j,M->data[i].e);
    }
}
void CopyMatrix(SMatrix *M,SMatrix *T)
{
    T->mu=M->mu;
    T->nu=M->nu;
    T->tu=M->tu;
    for(int i=0;i<M->tu;++i)
    {
        T->data[i].i=M->data[i].i;
        T->data[i].j=M->data[i].j;
        T->data[i].e=M->data[i].e;
    }
    
}
void TransposeMatrix(SMatrix *M,SMatrix*T)
{
    T->mu=M->nu;
    T->nu=M->mu;
    T->tu=M->tu;
    int q=0;
    if(M->tu!=0)
    {
        for (int col=0;col<M->nu;++col)
        {
            for(int p=0;p<M->tu;++p)
            {
                if(M->data[p].j==col)
                {
                    T->data[q].i=M->data[p].j;
                    T->data[q].j=M->data[p].i;
                    T->data[q].e=M->data[p].e;
                    ++q;
                }
            }
        }
    }
}
void FastTransposeMatrix(SMatrix *M,SMatrix*T)
{
    T->mu=M->nu;
    T->nu=M->mu;
    T->tu=M->tu;
    int *num=(int*)malloc(sizeof(int)*M->nu);
    assert(num);
    int *copt=(int*)malloc(sizeof(int)*M->nu);
    assert(copt);
    if(T->tu)
    {
        for(int col=0;col<M->nu;++col)
        {
            num[col]=0;
        }
        for(int t=0;t<M->tu;++t)
        {
            num[M->data[t].j]++;
        }
        copt[0]=0;
        for(int col=1;col<M->nu;++col)
        {
            copt[col]=copt[col-1]+num[col-1];
        }
        int q=0,col;
        for(int p=0;p<M->tu;++p)
        {
            col=M->data[p].j;
            q=copt[col];
            T->data[q].i=M->data[p].j;
            T->data[q].j=M->data[p].i;
            T->data[q].e=M->data[p].e;
            copt[col]++;
        }
    }
    free(num);
    free(copt);
}
int main()
{
    SMatrix sm,st;
    memset(&sm,0,sizeof(sm));
    CreateMatirx(&sm);
    FastTransposeMatrix(&sm,&st);
    PrintMatrix(&sm);
    PrintMatrix(&st);
    system("pause");
}