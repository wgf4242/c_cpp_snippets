
.s是汇编文件, 通过汇编生成可执行文件
gcc -S main.c # 会生成 main.s
gcc -c ./main.s -o main.o



# ASM `12_shellcode_asm_assembly.md`

xor dword ptr [rip],0x9f
imul eax, [rbp+rax*4+200h+cc1], 17h

mov  byte ptr [0x4000], al
mov dword ptr [0x4000], eax
mov qword ptr [0x4000], rax