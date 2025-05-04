#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
int main(void) {
	// 工具 - spy++ ，  检测窗口className
	if (FindWindowA("Sword2 Class", "Sword2 Window")) printf("检测到多开\n");
	return 0;

}