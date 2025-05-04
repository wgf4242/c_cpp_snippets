#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t fake_chunk[10];
    fake_chunk[0] = 0;
    fake_chunk[1] = 0x21;
    fake_chunk[2] = 0;
    fake_chunk[3] = 0;
    free(&fake_chunk[2]); // 报错了


    return 0;
}
