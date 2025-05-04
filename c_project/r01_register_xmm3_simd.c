#include <stdio.h>
#include <xmmintrin.h>

// 辗转相除法（扩展欧几里得算法）求模反元素
unsigned long long mod_inverse(unsigned long long a,unsigned long long mod) {
    unsigned long long m0 = mod, t, q;
    unsigned long long x0 = 0, x1 = 1;

    if (mod == 1) return 0;  // 如果模是 1，则没有反元素

    while (a > 1) {
        // 商
        q = a / mod;
        t = mod;
        mod = a % mod;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    // 如果 x1 小于 0，则调整为正数
    if (x1 < 0) x1 += m0;

    return x1;
}
int main() {
    unsigned long long table[12] = {
            0x40b5849728dd2ebf,
            0x09980ca8185da95f,
            0x791aa6b732b16dfa,
            0xd456b2592eadcacf,
            0x0fc08390420d2baa,
            0xc0389ccd81273016,
            0xddae76627fa54df1,
            0xd4a20dca3cd8329b,
            0xcd5d0efb6d2cddd5,
            0x1e79ad02a16b88f9,
            0xd1311e521d06af9e,
            0x2e304c046c965302
    };
    const unsigned long long MOD = 1LL << 64 - 1; //MOD即规定了找逆元的运算范围，1LL << 64 - 1即表示了64位无符号整数的最大值，于这个范围之内取寻找逆元

    unsigned long long inv = mod_inverse(0xA142AF62CA5B79D7, MOD);
    unsigned long long original[12];
    for (int i = 0; i < 12; i++) {
        original[i] = (table[i] * inv);
    }
    __m128i data[7] = { 0 };
    for (int i = 0; i < 6; i++) {
        data[i] = _mm_loadu_si128((__m128i*)(original + 2 * i));
    }
    __m128i addNumber = _mm_set_epi64x(0xe2b7a692404d29f1, 0x22);
    data[5] = _mm_sub_epi64(data[5], addNumber);
    data[4] = _mm_sub_epi64(data[4], addNumber);
    data[2] = _mm_sub_epi64(data[2], addNumber);
    data[1] = _mm_sub_epi64(data[1], addNumber);


    __m128i x0rData = _mm_set_epi64x(0xa2e8cb53e715cedf, 0xbb6585dd9353093f);
    data[5] = _mm_xor_si128(data[4], data[5]);
    data[4] = _mm_xor_si128(data[3], data[4]);
    data[3] = _mm_xor_si128(data[2], data[3]);
    data[2] = _mm_xor_si128(data[2], data[1]);
    data[1] = _mm_xor_si128(data[0], data[1]);
    data[0] = _mm_xor_si128(data[0], x0rData);

    printf("%s", (char*)data);
    return 0;
}
//flag{33dfe56d-dc-c9478cea6641-6c0f-2a89a1b24b3a33-07fbc-4ccdff9-fe0a-9a5c30cff1fa-0aca40caf2-cc}