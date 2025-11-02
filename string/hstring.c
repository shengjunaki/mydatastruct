#ifndef __HSTRING__
#define __HSTRING__

#include<stdio.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

typedef struct
{
    char *ch;
    int length;
}hstring;
void initstack(hstring *s);
void strassign(hstring *s,char *str);
#endif
void initstack(hstring *s)
{
    s->ch=NULL;
    s->length=0;
}
void strassign(hstring *s,char *str)
{
    int len=strlen(str);
    if(s->ch!=NULL)free(s->ch);
    s->ch=(char*)malloc(sizeof(char)*len);
    assert(s->ch!=NULL);
    for(int i=0;i<len;++i)
    {
        s->ch[i]=str[i];
    }
    s->length=len;
}
int main(){
    hstring s;
    initstack(&s);
    strassign(&s,"abc");
}