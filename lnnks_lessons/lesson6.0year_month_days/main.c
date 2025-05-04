#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "stdio.h"

int main(int argc, char* argv[], char** env) {
    unsigned year, month, days;
    scanf("%u-%u", &year, &month);

    for (int i = 1; i < 13; ++i) {
        month = i;
        days = 30 + ((month % 2) + (month >= 8)) % 2;
        days = days - (month == 2) * 2;
        days = days + ((month == 2) && (((year % 100) && (year % 4 == 0)) || (year % 400 == 0)));
        printf("%u年%u月 一共有%u天 \r\n", year, month, days);
    }
    return 0;
}