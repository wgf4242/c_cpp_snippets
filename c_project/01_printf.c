# include <stdio.h>

void test_printf();

void test_snprintf();

int main(void) {
    // test_printf();
    test_snprintf();
    return 0;
}

void test_snprintf() {
    char str[10] = {0};
    int nLen = snprintf(str, sizeof(str), "123456789012345678");
    printf("str=%s\n", str);
    printf("nLen=%d\n", nLen);
    // str=123456789
    // nLen=18
}

void test_printf() {
    int a = 0x31;
    int b = 0xb;
    printf("int %d\n", a);
    printf("hex %x\n", a);
    printf("hex unsign %X\n", a);
    printf("char %c\n", a);
    printf(" %.2x", b); // 0b
    printf("输出指定长度4字符: %.4s\n", "123456");
}
