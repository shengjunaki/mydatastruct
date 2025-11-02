#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <assert.h>
#define Atomtype int
typedef enum
{
    HEAD,
    ATOM,
    CHILDLIST
} ElemTag;
typedef struct GLNode
{
    ElemTag tag;
    union
    {
        Atomtype atom;
        struct GLNode *hp;
    };
    struct GLNode *tp;
} GLNode, *GenList;
void initGenList(GenList &gl);
void createGenList(GenList &gl, const char *str);
bool sever(char *sub, char *hsub);
int GenListDeepth(GenList &gl);
void ShowGenList(GenList &gl);
bool GenListEmpty(GenList &gl);
int GenListLength(GenList &gl);
void createGenList(GenList &gl, const char *str)
{
    int n = strlen(str);
    char *sub = (char *)malloc(sizeof(char) * (n - 2));
    char *hsub = (char *)malloc(sizeof(char) * (n - 2));
    assert(sub != NULL && hsub != NULL);
    strncpy(sub, str + 1, n - 2);
    sub[n - 2] = '\0'; //'1,2,3'
    if (!gl)
    {
        gl = (GLNode *)malloc(sizeof(GLNode));
        assert(gl);
        gl->tag = HEAD;
        gl->hp = gl->tp = NULL;
    }
    GLNode *p = gl;
    while (strlen(sub))
    {
        p = p->tp = (GLNode *)malloc(sizeof(GLNode));
        assert(p);
        p->hp = p->tp = NULL;
        if (sever(sub, hsub))
        {
            if (hsub[0] == '(')
            {
                p->tag = CHILDLIST;
                createGenList(p->hp, hsub);
            }
            else
            {
                p->tag = ATOM;
                p->atom = atoi(hsub);
            }
        }
    }
}
bool sever(char *sub, char *hsub)
{
    if (*sub == '\0' || strcmp(sub, "()") == 0)
    {
        hsub[0] = '\0';
        return true;
    }

    int n = strlen(sub);
    int i = 0;
    char ch = sub[0];
    int k = 0;

    while (i < n && (ch != ',' || k != 0))
    {
        if (ch == '(')
            k++;
        else if (ch == ')')
            k--;
        i++;
        ch = sub[i];
    }

    if (i < n)
    {
        sub[i] = '\0';
        strcpy(hsub, sub);
        strcpy(sub, sub + i + 1);
    }
    else if (k != 0)
    {
        return false;
    }
    else
    {
        strcpy(hsub, sub);
        sub[0] = '\0';
    }

    return true;
}
void initGenList(GenList &gl)
{
    gl = NULL;
}
int GenListDeepth(GenList &gl)
{
    if (gl->tp == NULL)
        return 1;
    GLNode *p = gl->tp;
    int maxdepth = 0;

    int dep;
    while (p != NULL)
    {
        if (p->tag == CHILDLIST)
        {
            dep = GenListDeepth(p->hp);
            if (dep > maxdepth)
                maxdepth = dep;
        }
        p = p->tp;
    }
    return maxdepth + 1;
}
void ShowGenList(GenList &gl)
{
    GLNode *p = gl->tp;
    printf("(");
    while (p != NULL)
    {
        if (p->tag == ATOM)
        {
            printf("%d", p->atom);
            if (p->tp)
                printf(",");
            p = p->tp;
        }
        else if (p->tag == CHILDLIST)
        {
            ShowGenList(p->hp);
            if (p->tp)
                printf(",");
            p = p->tp;
        }
    }
    printf(")");
}
int GenListLength(GenList &gl)
{
    GLNode *p=gl->tp;
    int l=0;
    while(p)
    {
        ++l;
        p=p->tp;
    }
    return l;
}
bool GenListEmpty(GenList &gl)
{
    return gl->tp==NULL;
}
int main()
{
    GenList gl;
    initGenList(gl);
    const char *ga = "(1,2,3)";
    const char *gb = "(1,(2,3))";
    const char *gg = "(1,((3,4),2),5)";
    createGenList(gl, gg);
    ShowGenList(gl);
    printf("\n");
    printf("depth=%d\n",GenListDeepth(gl));
    printf("lepth=%d\n",GenListLength(gl));
}