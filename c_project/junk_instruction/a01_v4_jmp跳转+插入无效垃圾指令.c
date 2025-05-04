#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    _asm {
    
        jmp $+5
        _emit 0x71
        _emit 2
        _emit 0xE9
        _emit 0xED
   }
 lable:
    printf("ok2");

    return 0;
}