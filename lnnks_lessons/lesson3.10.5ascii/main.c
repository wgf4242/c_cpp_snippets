
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {

	char u = 'A';
	printf("����һ��Сд��ĸ:");
	
	scanf("%c", &u);
	u = u - ('a' - 'A');
	printf("��������� %c, ASCIIֵ: %d\r\n", u, u);

	printf("ת����� \" \' \\ ");
	return 0;
}