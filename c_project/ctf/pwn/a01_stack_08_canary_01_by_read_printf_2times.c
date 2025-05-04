// gcc a.c -no-pie -m32 -fstack-protector -z noexecstack -o a
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void getshell(void) {
    system("/bin/sh");
}

//不设置缓冲区
void init() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
}

void vuln() {
    char buf[100];
    for (int i = 0; i < 2; i++) {
        read(0, buf, 0x200);
        printf(buf);
    }
}

int main(void) {
    init();
    puts("Hello Hacker!");
    vuln();
    return 0;
}
