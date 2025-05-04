#include <unistd.h>
#include <string.h>
#include "stdio.h"

int main(int argc, char *argv[], char **env) {
    setbuf(stdout, NULL);
    char name[0x20];
    read(0, name, 0x20);
    printf("%s\n ", name);
    return 0;
}