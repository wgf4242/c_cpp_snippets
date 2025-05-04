// gcc -mpreferred-stack-boundary=2 -fno-stack-protector -z execstack -o shellcode shellcode.c
#include <string.h>
#include "stdio.h"

char shellcode[] = "\x31"; //
int main(int argc, char *argv[], char **env) {
    setbuf(stdout, NULL);
    int *ret;
    ret = (int*)&ret+2;
    (*ret) = (int)shellcode;

    return 0;
}
