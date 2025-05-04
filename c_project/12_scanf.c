#include "stdio.h"

int main(int argc, char *argv[], char **env) {
    unsigned int v1;
    v1 = 0;
    scanf("%5d", &v1); // 只能输入5位
    return 0;
}