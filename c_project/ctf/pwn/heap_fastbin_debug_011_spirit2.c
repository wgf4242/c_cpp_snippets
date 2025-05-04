#include <stdio.h>
#include <stdlib.h>

int main() {
    malloc(0x10);
    size_t fake_chunk[10];
    fake_chunk[0] = 0;
    fake_chunk[1] = 0x21;
    fake_chunk[2] = 0;
    fake_chunk[3] = 0;
    fake_chunk[4] = 0;
    fake_chunk[5] = 0x21; // 不加时会报错 下一个chunk size 不合法
    free(&fake_chunk[2]); // 报错了

    return 0;
}
