#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
    _asm {
        jz Label3;
        jnz Label3;
        _emit 0xE8;
    }
Label2:
    _asm {
        jz Label4;
        jnz Label4;
        _emit 0xE8;
    }


Label3:
    _asm {
        jz Label1;
        jnz Label1;
        _emit 0xE9;
    }
Label1:
    _asm {
        jz Label2;
        jnz Label2;
        _emit 0xE9;
    }
Label4:
    printf("ok2");

    return 0;
}