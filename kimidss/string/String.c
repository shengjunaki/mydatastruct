#ifndef SSTRING_H
#define SSTRING_H

#include <stdio.h>
#include <stdbool.h>

#define MAXSTRLEN 20
typedef unsigned char u_char;
typedef u_char SString[MAXSTRLEN + 1];   /* S[0] 存放串长，S[1..S[0]] 存放字符 */

/* 基本操作 */
void InitString(SString S);              /* 生成空串 */
void StrAssign(SString S, const char *str); /* 把 C 串赋给 S */
void StrCopy(SString S, SString T);      /* 把串 T 复制给 S */
bool StrEmpty(SString S);                /* 判空 */
int  StrCompare(SString S, SString T);   /* 串比较，>0 表示 S>T */
int  StrLength(SString S);               /* 返回串长 */
void StrConcat(SString T, SString s1, SString s2); /* T = s1 + s2 */
void SubString(SString Sub, SString S, int pos, int len); /* Sub = 子串 */
int  StrIndex(SString S, SString T, int pos); /* 返回 T 在 S 中第 pos 个字符后首次出现的位置，0 表示未找到 */
void StrReplace(SString S, SString T, SString V); /* 用 V 替换 S 中所有不重叠的 T */
void StrInsert(SString S, int pos, SString T); /* 在 S 第 pos 个字符前插入 T */
void StrDelete(SString S, int pos, int len);   /* 删除 S 中从 pos 起 len 个字符 */
void StrClear(SString S);              /* 清空串 */
#include <string.h>
#endif

/* 初始化空串 */
void InitString(SString S)
{
    S[0] = 0;
}

/* 用 C 风格字符串赋值 */
void StrAssign(SString S, const char *str)
{
    int i;
    for (i = 1; i <= MAXSTRLEN && str[i - 1]; ++i)
        S[i] = str[i - 1];
    S[0] = i - 1;
}

/* 串复制 */
void StrCopy(SString S, SString T)
{
    int i;
    for (i = 0; i <= T[0]; ++i) S[i] = T[i];
}

/* 判空 */
bool StrEmpty(SString S)
{
    return S[0] == 0;
}

/* 串比较 */
int StrCompare(SString S, SString T)
{
    int i;
    for (i = 1; i <= S[0] && i <= T[0]; ++i)
        if (S[i] != T[i]) return S[i] - T[i];
    return S[0] - T[0];
}

/* 串长 */
int StrLength(SString S)
{
    return S[0];
}

/* 串联接 T = s1 + s2 ，超长截断 */
void StrConcat(SString T, SString s1, SString s2)
{
    int i, j;
    int cnt = 0;
    for (i = 1; i <= s1[0] && cnt < MAXSTRLEN; ++i, ++cnt)
        T[cnt + 1] = s1[i];
    for (j = 1; j <= s2[0] && cnt < MAXSTRLEN; ++j, ++cnt)
        T[cnt + 1] = s2[j];
    T[0] = cnt;
}

/* 求子串 Sub = S[pos..pos+len-1] */
void SubString(SString Sub, SString S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S[0] || len < 0)
    {
        Sub[0] = 0; return;
    }
    if (len > S[0] - pos + 1) len = S[0] - pos + 1;
    if (len > MAXSTRLEN) len = MAXSTRLEN;
    for (i = 1; i <= len; ++i) Sub[i] = S[pos + i - 1];
    Sub[0] = len;
}

/* 朴素模式匹配，返回 T 在 S 中第 pos 字符后首次出现位置，0 表示未找到 */
int StrIndex(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    if (pos < 1 || pos > S[0]) return 0;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j]) { ++i; ++j; }
        else { i = i - j + 2; j = 1; }
    }
    if (j > T[0]) return i - T[0];
    return 0;
}

/* 用 V 替换 S 中所有不重叠的 T */
void StrReplace(SString S, SString T, SString V)
{
    int pos = 1, i, k;
    SString tmp;
    if (T[0] == 0) return;
    while ((pos = StrIndex(S, T, pos)) != 0)
    {
        /* 删除 T */
        StrDelete(S, pos, T[0]);
        /* 插入 V */
        StrInsert(S, pos, V);
        pos += V[0];
    }
}

/* 在 S 第 pos 个字符前插入 T */
void StrInsert(SString S, int pos, SString T)
{
    int i;
    if (pos < 1 || pos > S[0] + 1) return;
    if (S[0] + T[0] > MAXSTRLEN)   /* 需要截断 */
    {
        int mv = MAXSTRLEN - T[0]; /* 原串能保留下来的长度 */
        if (mv < 0) mv = 0;
        /* 先移动后插入 */
        for (i = mv; i >= pos; --i)
            S[i + T[0]] = S[i];
        for (i = 1; i <= T[0] && pos + i - 1 <= MAXSTRLEN; ++i)
            S[pos + i - 1] = T[i];
        S[0] = MAXSTRLEN;
    }
    else
    {
        for (i = S[0]; i >= pos; --i) S[i + T[0]] = S[i];
        for (i = 1; i <= T[0]; ++i)   S[pos + i - 1] = T[i];
        S[0] += T[0];
    }
}

/* 删除 S 中从 pos 起 len 个字符 */
void StrDelete(SString S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S[0] || len <= 0) return;
    if (len > S[0] - pos + 1) len = S[0] - pos + 1;
    for (i = pos + len; i <= S[0]; ++i) S[i - len] = S[i];
    S[0] -= len;
}

/* 清空串 */
void StrClear(SString S)
{
    S[0] = 0;
}
int main(void)
{
    SString s1, s2, s3;
    InitString(s1);
    StrAssign(s1, "data");
    StrAssign(s2, "structure");
    StrConcat(s3, s1, s2);
    printf("s3 = ");
    for (int i = 1; i <= s3[0]; ++i) putchar(s3[i]);
    putchar('\n');
    return 0;
}