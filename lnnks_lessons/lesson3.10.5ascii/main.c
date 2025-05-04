
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {

	char u = 'A';
	printf("输入一个小写字母:");
	
	scanf("%c", &u);
	u = u - ('a' - 'A');
	printf("您输入的是 %c, ASCII值: %d\r\n", u, u);

	printf("转义符号 \" \' \\ ");
	return 0;
}