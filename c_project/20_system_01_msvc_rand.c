// cl /W4 /O2 msvc_rand.c /Fe:msvc_rand.exe
#include <stdio.h>
#include <stdlib.h>

int main() {
    unsigned int seed = 0x666;
    srand(seed);

    printf("C 原生 MSVCRT rand() (种子: 0x666):\n");
    for (int i = 1; i <= 10; i++) {
        printf("第 %d 个: %d\n", i, rand());
    }

    return 0;
}