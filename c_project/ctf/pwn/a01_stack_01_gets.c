// gcc -fno-stack-protector -no-pie -z execstack pwn_vuln.c -o pwn1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


extern char *gets(char *s);
void win() {
    system("cat /flag");
}

void vuln() {
    char buf[32];
    puts("Input something:");
    gets(buf); 
}

int main() {
    // 禁用缓存，方便本地调试
    setvbuf(stdout, NULL, _IONBF, 0);
    vuln();
    return 0;
}