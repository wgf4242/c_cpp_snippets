
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	unsigned char number, snumber;
	scanf("%hhd", &number);
	snumber = ~number + 1;
	printf("%hhd\r\n", snumber);
	
	unsigned value = 200041203;  // 00ff00 ff00ff00
	value = ~value;
	printf("%d\r\n", value);
	value = ~value;
	printf("%d", value);
	return 0;

}