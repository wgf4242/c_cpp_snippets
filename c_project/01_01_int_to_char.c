#include "stdio.h"

void int_to_char();

void char_to_int();

int main() {
    char buf[30] = "\0" "1234"; // 首字符为 \0

    int_to_char();
    char_to_int();
    return (0);

}

void char_to_int() {
    char *str = "1234";
    for (int i = 0; i < 1; ++i) {
        printf("0x%x\n", *((int *)str + i));
    }
}

void int_to_char() {
    int val = 0x12345678;
    for (int i = 0; i < 4; ++i) {
        printf("%d\n", *((char *) &val + i));
    }
}
