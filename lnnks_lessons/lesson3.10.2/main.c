
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {
	unsigned short v = 1;
	sizeof(v + v);
	unsigned v2 = 0xfffffff;
	unsigned v1 = v2 - -1;
	// v2��unsigned , ���� -1 ����ʱת�� unsigned int
	printf("%d", v1);
	return 0;
}