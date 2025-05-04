#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p1, *p2, *p3, *p4, *p5;
    size_t fake_chunk[4];
    fake_chunk[0] = 0;
    fake_chunk[1] = 0x70;
    p1 = malloc(0x60);
    p2 = malloc(0x60);
    free(p1);
    free(p1); // double free 执行时报错

    return 0;
}

/*
gdb out
b main
vmmap 查看内存情况，
ni 执行到 malloc
malloc(0x10)，但却申请了0x21大小的空间
heap
*/