
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main(void) {
	unsigned short v = 1;
	sizeof(v + v);
	unsigned v2 = 0xfffffff;
	unsigned v1 = v2 - -1;
	// v2是unsigned , 所以 -1 计算时转成 unsigned int
	printf("%d", v1);
	return 0;
}