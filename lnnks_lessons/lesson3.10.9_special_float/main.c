#include "stdio.h"
// Alepay


int main(void) {
    float a;
    printf("input nan\r\n");
    scanf("%f", &a);
    // nan特殊值满足以下2个条件

    if (!(a >= 1)) {
        printf("Not a >= 1\r\n");
    }
    if (!(a < 1)) {
        printf("Not a < 1");
    }

}