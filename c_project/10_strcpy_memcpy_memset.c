#include <string.h>
#include <stdio.h>

// strcpy 拷贝字符串，遇到'\0'时结束
// memcpy 复制任意内容
// memset 初始化内存为某个字符
int main() {
    char a[100];
    // memset(a, '\0', sizeof(a));
    memset(a, '1', sizeof(a));
    printf("%s ", a);

    return 0;
}