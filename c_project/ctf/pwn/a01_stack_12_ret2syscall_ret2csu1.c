// gcc ret2csu1.c -fno-stack-protector -no-pie -o pwn -g -masm=intel
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>

void init();
void ohMyBackdoor(__int64_t a,__int64_t b,__int64_t c);

char *hello1 = "Which one you like more,write or puts?\n";
char *hello2 = "I hide some useful text in this elf.Remember to check it!\n";
char *gift1 = "/bin/cat";
char *gift2[] = {"/bin/cat","/flag",NULL};

// mov rax,SYS_execve; syscall;
size_t gift3 = (size_t)ohMyBackdoor + 0x40; 

void init()
{
    setvbuf(stderr,0,2,0);
    setvbuf(stdout,0,2,0);
    setvbuf(stdin,0,2,0);
}

void ohMyBackdoor(__int64_t a,__int64_t b,__int64_t c)
{
    // syscall(SYS_execve,a,b,c);
    if(a == 0x46616c6c77316e64 && b == 0x57616e7473414749 && c == 0x726c667269656e64)
    {
        __asm__
        (
            "mov rax,59;"
            "syscall;"          
        );
    }
}

int main()
{
    init();
    char message[0x20];
    __asm__
    (
        // syscall(SYS_write,STDOUT_FILENO,hello1,strlen(hello1));
        "mov rdi,1;"
        "mov rsi,[hello1];"
        "mov rdx,40;"
        "mov rax,1;"
        "syscall;"
        // syscall(SYS_write,STDOUT_FILENO,hello2,strlen(hello2));          
        "mov rdi,1;"
        "mov rsi,[hello2];"
        "mov rdx,59;"
        "mov rax,1;"
        "syscall;"
        // syscall(SYS_read,STDIN_FILENO,message,0x70);          
        "xor rdi,rdi;"
        "lea rsi,[rbp-0x20];"
        "mov rdx,0x70;"
        "mov rax,0;"
        "syscall;"          
    );
}