#include "stdio.h"

/**
 * 作用: 参数 x 左移参数n位
 */
#define SHL(x, n) ( ((x) & 0xFFFFFFFF) << n )
/**
 * 作用： 参数 x 逻辑左移参数n位
 */
#define ROL(x, n) ( SHL((x), n) | (x >> (32 - n) ))
#define ROR(x, y) ((unsigned)x >> y | (unsigned)x << (32 - y))

int main(int argc, char *argv[], char **env) {
    printf("ROL: %x\n", ROL(0xFFFF0000, 16));
    printf("ROR: %x\n", ROR(0x0000FFFF, 16));
    return 0;
}