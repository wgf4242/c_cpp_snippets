/*
x86 编译看 x64没效果
# __cdecl
6A 02             push    2               ; b
6A 01             push    1               ; a
E8 A7 F9 FF FF    call    j__add_cdecl
83 C4 08          add     esp, 8          ; 清理栈

# __fastcall
mov     edx, 3             ; b
mov     ecx, 2             ; a
call    j_@add1_fastcall@8 ; add1_fastcall(x,x)

# __stdcall
push    4               ; b
push    3               ; a
call    j__add2_stdcall@8 ; add2_stdcall(x,x)

## __fastcall/__stdcall 在函数里都是 被调用者 retn 8 栈清理
8B E5             mov     esp, ebp
5D                pop     ebp
C2 08 00          retn    8
*/

#include <stdio.h>

int __cdecl add_cdecl(int a, int b)
{
    return (a + b);
}

int __fastcall add1_fastcall(int a, int b)
{
    return (a + b);
}

int __stdcall add2_stdcall(int a, int b)
{
    return (a + b);
}


int main(int argc, char* argv[])
{
    add_cdecl(1, 2);
    add1_fastcall(2, 3);
    add2_stdcall(3, 4);
    return 0;
}