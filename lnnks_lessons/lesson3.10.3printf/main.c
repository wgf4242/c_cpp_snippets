
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	printf("HP=%d, MP=%o\r\n", 100, 8);
	printf("HP=%x, MP=%X\r\n", -255, 255);
	printf("HP=%f, MP=%f\r\n", 1.0f, 1.0);
	printf("HP=%a, MP=%A\r\n", 1.000, 100.0);
	printf("HP=%e, MP=%E\r\n", 10000000000.000, 100.00000000001);
	printf("HP=%g, MP=%G\r\n", 10000000000.000, 0.0001);
	printf("%%d \r\n", 100, 8);
	return 0;

}