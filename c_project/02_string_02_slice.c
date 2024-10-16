#include <stdio.h>
#include <string.h>

void slice16_memcpy() {
    char original[32] = "12345678abcdefghABCDEFGH87654321";
    char result[17];
    memcpy(result, original, 16);
    result[16] = '\0';
    printf("截取的字符串: %s\n", result);
}

void slice16_strncpy() {
    char original[32] = "12345678abcdefghABCDEFGH87654321";
    char result[17];
    strncpy(result, original, 16);
    result[16] = '\0';
    printf("截取的字符串: %s\n", result);
}

int main() {
    char src[40];
    char dest[12];

    memset(dest, '\0', sizeof(dest));
    strcpy(src, "Hello World!");
    strncpy(dest, src, 5);
    dest[5] = '\0';   /* 手动加上终止符, 不然可能出问题 */

    printf("Result： %s\n", dest);
    return (0);
}