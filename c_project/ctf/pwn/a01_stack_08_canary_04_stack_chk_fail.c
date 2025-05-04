// gcc a.c -m32 -fstack-protector -no-pie -z noexecstack -z norelro -o a
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void getshell(void) {
    system("/bin/sh");
}

int main(int argc, char *argv[]) {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    char buf[100];
    read(0, buf, 200); //栈溢出
    printf(buf);
    return 0;
}
