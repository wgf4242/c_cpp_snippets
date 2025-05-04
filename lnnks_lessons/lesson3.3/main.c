// C语言 负整数在内存中是怎么保存的 0-1=255 https://www.bilibili.com/video/BV1vW4y187Ui
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	// 注意： -128 求负 还是-128. 有符号数边界都是存在这种问题,
	unsigned char value = 255;
	printf("自然数 value = %hhu \r\n", value);
	printf("有符号 value = %hhd \r\n", value);
	
	unsigned char valIn = 0;
	// 0-127
	printf("请输入一个0-127的整数:");
	scanf("%hhd", &valIn);
	unsigned char valOut = 255 - valIn + 1;
	printf("有符号  valOut = %hhd \r\n 无符号  valOut = %hhu", valOut, valOut);
	return 0;
}