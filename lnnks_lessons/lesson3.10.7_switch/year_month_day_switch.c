#include "stdio.h"

int main(void) {
    unsigned year, month, days;
    printf("请输入某年的月份:如22-10\r\n");
    scanf("%u-%u", &year, &month);

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            days = 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        default:
            printf("输入了错误的月份");
            break;
    }

    printf("%u", days);
}