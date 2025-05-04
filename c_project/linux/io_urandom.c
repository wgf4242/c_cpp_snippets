#include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"

unsigned int seed;
char flag[40];

int init_flag()
{
    int v1; // [rsp+108h] [rbp-8h]
    int fd; // [rsp+10Ch] [rbp-4h]

    fd = open("/dev/urandom", 0);
    if ( fd < 0 )
    {
        perror("rand error");
        exit(0);
    }
    read(fd, &seed, 4uLL);
    close(fd);
    srand(seed);
    v1 = open("flag", 0);
    if ( v1 < 0 )
    {
        perror("flag error");
        exit(0);
    }
    read(v1, flag, 0x100uLL);
    printf("%s", flag);
    return close(v1);
}

int main(int argc, char *argv[], char **env) {
    setbuf(stdout, NULL);
    init_flag();
    return 0;
}