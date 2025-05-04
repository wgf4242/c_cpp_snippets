#include <stdlib.h>
#include "stdio.h"

int main(int argc, char *argv[], char **env) {
    int *a = malloc(0x100);
    int *padding = malloc(0x20);
    int *b = malloc(0x100);
    int *c = malloc(0x100);
    free(a);
    free(b);
    printf("Now\n");
    return 0;
}