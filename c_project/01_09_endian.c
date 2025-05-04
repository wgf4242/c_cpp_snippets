#include "stdio.h"
#include "intrin.h"

void show_mem_rep(char *start, int n) {
    int i;
    for (i = 0; i < n; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

int main() {
    int i = 0x01234567;
    // Method1 Virtual C++
    int j = _byteswap_ulong(i); // 32bit in
    // _byteswap_ushort(unsigned short value); // 16bit
    // _byteswap_uint64(unsigned __int64 value); // 64bit

    // Method2 GCC
    int k = __builtin_bswap32(0x12345678); // https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
    // uint32_t __builtin_bswap32 (uint32_t x); // gcc
    // uint64_t __builtin_bswap64 (uint64_t x);

    show_mem_rep((char *) &j, sizeof(j));
    show_mem_rep((char *) &k, sizeof(j));
    getchar();
    return 0;
}