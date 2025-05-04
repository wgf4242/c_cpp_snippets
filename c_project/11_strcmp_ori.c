// gcc -m32 -shared -O2 mystrcmp.c -o mystrcmp.o
#include "stdio.h"
#include "assert.h"

int strcmp(const char *str1,const char *str2)
{
    /*不可用while(*str1++==*str2++)来比较，当不相等时仍会执行一次++，
    return返回的比较值实际上是下一个字符。应将++放到循环体中进行。*/
    while(*str1 == *str2)
    {
        assert((str1 != NULL) && (str2 != NULL));
        if(*str1 == '\0')
            return 0;
        str1++;
        str2++;
    }
    return *str1 - *str2;
}