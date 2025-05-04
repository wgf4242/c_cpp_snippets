#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void left_align_sprintf();

void left_align_itoa();

void right_align_snprintf();

void basic();

void hex_to_str_manual();

void print_hex();

int main() {
    // basic();
    print_hex();

    // left_align_sprintf();
    // left_align_itoa();
    // right_align_snprintf();

    // hex_to_str_manual();
    return(0);

}

void print_hex() {// print as hex
    unsigned char digest[16];  // 使用 {0} 将所有元素初始化为0
    for (int i = 0; i < 16; ++i) {
        digest[i] = i + 'a';  // 或者其他你想要填充的数据
    }
    printf("Digest in hex format: ");
    for (int i = 0; i < 16; ++i) {
        printf("%02x", digest[i]);  // %02x 确保输出两位16进制数字，并且是小写
    }
}

void hex_to_str_manual() {
    // 712DA50903F0451B9E383FC05C1B7DA8 转为字符串
    char TABLE[20];
    char enc[16] = {0x71, 0x2D, 0xA5, 0x09, 0x03, 0xF0, 0x45, 0x1B, 0x9E, 0x38, 0x3F, 0xC0, 0x5C, 0x1B, 0x7D, 0xA8};
    char out[32] = {};
    strcpy(TABLE, "0123456789ABCDEF");
    for (int m = 0; m < 16; ++m )                    // 转16进制字符
    {
        *(unsigned __int8 *)(out + 2 * m) = TABLE[(int)(unsigned __int8)enc[m] >> 4];
        *(unsigned __int8 *)(out + 2 * m + 1) = TABLE[enc[m] & 0xF];
    }

    out[32] = '\0';
    printf("%s", out);
}

void basic() {
    int val;
    char str[20];

    strcpy(str, "98993489");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);

    strcpy(str, "runoob.com");
    val = atoi(str);
    printf("字符串值 = %s, 整型值 = %d\n", str, val);
}

void right_align_snprintf() {
    // 右对齐, n为长度+1，需要1个结束符
    char a[16];
    size_t i;
    int len = 12;
    i = snprintf(a, len + 1, "%012d", 12345);  // 第 1 种情况
    printf("i = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 000000012345
    i = snprintf(a, 8 + 1, "%012d", 12345);   // 第 2 种情况
    printf("i = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 00000001
    i = snprintf(a, 3 + 1, "%04d", 12345);   // 第 2 种情况
    printf("i = %lu, a = %s\n", i, a);    // 输出：i = 12, a = 00000001
}

void left_align_itoa() {
    char str[6];
    itoa(123, str, 10); // 3 转为了 [3, 0, 0,0,0,0]
    itoa(123, str, 16);
    printf("%s\n", str);
}

void left_align_sprintf() {
    char str[6];
    sprintf(str, "%d", 3); // 3 转为了 [3, 0, 0,0,0,0]
    printf("%s\n", str);
}

void number_to_string_compare() {
    char arr[] = "8eef";
    int x = 0x8eef;
    char result[5];

    sprintf(result, "%x", x); // 将 x 转换为十六进制字符串并保存到 result 中
    assert(strcmp(result, arr) == 0); // 断言 result 和 arr 相等


    char str1[] = "\x8a\xc1\x0a\xe0\x3c\x87\xe9\x9f";
    char enc1[17] = {0};
    for (int i = 0; i < 8; ++i) {
        sprintf(enc1 + i * 2, "%02x",(unsigned char ) str1[i]);
    }
    assert(strcmp(enc1, "8ac10ae03c87e99f") == 0);
}