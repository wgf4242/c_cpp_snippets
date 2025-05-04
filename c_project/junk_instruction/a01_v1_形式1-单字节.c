#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    _asm {
        jz start; //jz 和 jnz 同时出现，导致永恒跳转
        jnz start;
        _emit 0xE8; //这个地方就是故意插入的花指令 CALL + 地址
    }
start:
    printf("ok!");
    return 0;
}