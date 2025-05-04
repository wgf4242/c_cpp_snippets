#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "string.h"

uint32_t d = 0x73637466;

void bf(char *s) {
    for (int i1 = 32; i1 < 128; ++i1) {
        for (int i2 = 32; i2 < 128; ++i2) {
            for (int i3 = 32; i3 < 128; ++i3) {
                for (int i4 = 32; i4 < 128; ++i4) {
                    s[0] = i1;
                    s[1] = i2;
                    s[2] = i3;
                    s[3] = i4;
                    //strcpy(s, "1234");
                    if (memcmp(s, "1234", 4) == 0) {
                        printf("%s\n", s);

                    }
                    //if (strcmp(s, "1234") == 0) { // 有个问题,不是\0结尾会多输出字符无法匹配
                    //    printf("%s\n", s);
                    //}
                }
            }
        }

    }

}

int main() {
    char inv[4] = {};
    bf(inv);
    return 0;
}