#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	int a = 200;
	a = 1 + 1;
	printf("%d", sizeof(3.0L));  // 0LL, 0U, 0UL, 3.14, 0.0F, 0.0L
	// 小数一般识别为 double

	const char hourCount = 28;
	const int retSuccess = 0;
	const int retFail = 1;
	return retSuccess;
	// 属性 - C/C++ - 优化 - 优化- 已禁用
}