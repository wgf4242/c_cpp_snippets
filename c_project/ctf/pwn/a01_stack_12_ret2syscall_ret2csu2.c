// gcc ret2csu2.c -fno-stack-protector -no-pie -z now -o pwn -g -masm=intel
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/mman.h> 

char *hello1 = "Ret2csu is easy,isn't it?\n";
char *hello2 = "Also a fun function in this elf.Remember to check it!\n";

void init()
{
    setvbuf(stderr,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stdin,0,2,0);
}

void ohMyBackdoor(__int64_t a,__int64_t b,__int64_t c)
{
    mprotect((void *)2,3,3);
}

int main()
{
    init();
    char message[0xf0];
    __asm__
    (
        // syscall(SYS_write,STDOUT_FILENO,hello1,strlen(hello1));
        "mov rdi,1;"
        "mov rdx,26;"
        "mov rax,1;"
        "mov rsi,[hello1];"
        "syscall;"
        // syscall(SYS_write,STDOUT_FILENO,hello2,strlen(hello2));          
        "mov rdi,1;"
        "mov rdx,54;"
        "mov rax,1;"
        "mov rsi,[hello2];"
        "syscall;"
        // syscall(SYS_read,STDIN_FILENO,message,0x100);          
        "xor rdi,rdi;"
        "mov rdx,0x100;"
        "mov rax,0;"
        "lea rsi,[rbp-0xf0];"
        "syscall;"          
    );
}