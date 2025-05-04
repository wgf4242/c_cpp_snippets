// gcc -m32 -shared -O2 mystrcmp.c -o mystrcmp.o
#include "stdio.h"

int strcmp(const char *s1, const char *s2){
    // static  int counter = 0;
    // printf("%02d strcmp called!\n", counter++);
    printf("%strcmp called!\n");

    while (*s1 && (*s1 == *s2)) {
        ++s1;
        ++s2;
    }

    return *s1 - *s2;
}