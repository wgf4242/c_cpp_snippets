#include <string.h>
#include <malloc.h>
#include "stdio.h"

void strncpy_memcpy() {
    char a[] = "123\000456";
    char b[6];
    char c[6];
    strcpy(b ,a);  // 31 32 33 00 00 00 复制到0停止

    char *input = malloc(20);
    strcpy(input, "aaaabaaacaaadaaaeaaa");

    memcpy(c, a, 6); // 31 32 33 00 34 35 到0不停止
}

int main(int argc, char *argv[], char **env) {
    char name[] = "test printf";
    printf("%s\n", name);  //用printf输出

    char str1[15]; // 或 char *str1 = "test puts"
    strcpy(str1, "12345678901234");
    printf("test puts:");
    puts(str1);

    char a = 'T';
    putchar(a);
    printf("\n");

    strncpy_memcpy();
    return 0;
}