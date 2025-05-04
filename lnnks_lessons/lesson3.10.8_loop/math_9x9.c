#include "stdio.h"

int main(void) {
    unsigned x = 0, y = 0, mul;
    while (x++ < 9) {
        y = 0;
        while ((y++ < 9) && (y <= x)) {
//            if (x < y) break
//            y = 1 - 9
            mul = x * y;
            printf("%02ux%02u=%02u ", x, y, mul);
        }
        printf("\r\n");
    }
}