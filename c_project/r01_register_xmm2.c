#include <emmintrin.h>
#include <stdio.h>

int main() {
    unsigned int value = 0x12345678;
    unsigned long long xmm_value;

    __asm__ (
            "mov %[value], %%eax;"
            "movd %%eax, %[xmm_value];"
            : [xmm_value] "=x"(xmm_value)
    : [value] "r"(value)
    : "eax"
    );

    unsigned long long int test = xmm_value;
    printf("XMM Value: %llx\n", test);
    printf("XMM Value: %llx\n", xmm_value);

    __m128i xmm = _mm_set_epi32(0x12345678, 0x22345678, 0x32345678, 0x42345678);
    // Ð¡¶ËÐò, ÄÚ´æÎª 78 56 34 42   78 56 34 32   78 56 34 22   78 56 34 12

    char A[] = {0x78,0x56,0x34,0x12,0,0,0,0};
    short B[] = {4,5,6,7};

    __m128i a,b,v;
    a = _mm_loadl_epi64((const __m128i*)A);
    b = _mm_loadl_epi64((const __m128i*)B);
    v = _mm_unpacklo_epi64(a,b);
    printf("XMM Value: %llx\n", a);


    return 0;
}