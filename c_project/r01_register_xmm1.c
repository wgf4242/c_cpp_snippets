#include <stdio.h>

int main() {
    unsigned int values[4];

    __asm__ __volatile__(
            "movd %[data], %%xmm0" // 将数据加载到 XMM0 寄存器的低位
            :
            : [data] "r" (0x12345678)
    : "xmm0"
    );

    __asm__ __volatile__(
            "movd %%xmm0, %[result]" // 将 XMM0 寄存器中的数据存储到 result 数组中
            : [result] "=r" (*values)
    :
    : "xmm0"
    );

    for (int i = 0; i < 4; i++) {
        printf("%08x ", values[i]);
    }
    printf("\n");

    return 0;
}