// 仅供调试练习
#include <stdio.h>

int main(int argc, char *argv[], char **env) {
    char buf[8];
    read(0, &buf, 0x20);
    printf("%s\n", buf);
    return 0;
}