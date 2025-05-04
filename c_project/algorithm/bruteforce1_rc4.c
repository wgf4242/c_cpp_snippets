#include <stdio.h>
#include <string.h>

void bf(size_t count, char start, char anEnd, void (*callback)(const char *), char *enc);
void print_combination(const char *combination);

#include <string.h>
#include <assert.h>
#include "stdio.h"

// 初始化函数
void rc4_init(unsigned char *s, unsigned char *key, unsigned long Len) {
    int i = 0, j = 0;
    // char k[256]={0};
    unsigned char k[256] = {0};
    unsigned char tmp = 0;
    for (i = 0; i < 256; i++) {
        s[i] = i;
        k[i] = key[i % Len];
    }
    for (i = 0; i < 256; ++i) {
        j = (j + s[i] + k[i]) % 256;
        tmp = s[i];
        s[i] = s[j]; // 交换 s[i] 和 s[j]
        s[j] = tmp;
    }
}

/* 加解密 */
void rc4_crypt(unsigned char *s, unsigned char *Data, unsigned long Len) {
    int i = 0, j = 0, t = 0;
    unsigned long k = 0;
    unsigned char tmp;
    for (k = 0; k < Len; ++k) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        tmp = s[i];
        s[i] = s[j]; // 交换 s[i] 和 s[j]
        s[j] = tmp;
        t = (s[i] + s[j]) % 256;
        Data[k] ^= s[t];
    }
}


int main() {
    setbuf(stdout, NULL);

    size_t count =4;
    char start = 0x20, end = 0x7f;

    bf(count, start, end, print_combination, NULL);
    return 0;
}

void bf(size_t count, char start, char anEnd, void (*callback)(const char *), char *enc) {
    char arr[count + 1];
    arr[count] = '\0';

    for (size_t i = 0; i < count; ++i) {
        arr[i] = start;
    }

    while (1) {
        (*callback)(arr);

        ssize_t j;
        for (j = count - 1; j >= 0; --j) {

            char key[count + 1];

            char sbox[256];
            char data[] = {0x64, 0x0F, 0xDD, 0xF4, 0xF8, 0xB9, 0x73, 0x51, 0xB2, 0x38, 0xD2, 0xC7, 0xA8, 0xFC, 0xB9, 0x09, 0x51, 0x3C, 0x6D, 0x28, 0x99, 0xE3, 0x9D, 0x42, 0x7B, 0x30, 0x84, 0x80, 0x75, 0x91};
            memcpy(key, arr, count);
            rc4_init(sbox, key, strlen(key));
            rc4_crypt(sbox, data, strlen(data));

            char enc[17] = {0};
            for (int i = 0; i < strlen(data); ++i) {
                sprintf(enc + i, "%c",(unsigned char ) data[i]);
            }

            // TODO: change flag
            if (strcmp(enc, "flag{tH14.l4_F@kKkEeeE---f41g}") == 0) {
                printf("get key: %s\n", key);
                return;
            }

            if (arr[j] == anEnd) {
                if (j == 0) return; // 已完成
                arr[j] = start;
            } else {
                arr[j]++;
                break;
            }
        }
    }
}

void print_combination(const char *combination) {
    printf("%s\n", combination);
}
