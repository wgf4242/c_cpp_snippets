
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {

	int value, a, b, c, d;
	scanf("%d", &value); // 1234, 处理为整数(int) 1234
	scanf("%3d", &value); // 保留3位
	// 输入多个内容:
	scanf("%d %d %d %d", &a, &b, &c, &d);
	// 设置输入的格式:
	scanf("%d.%d", &a, &b); //输入22.56 a=22 b=56
	// scanf函数会忽略格式定义前的空格, 注:% c除外

	return 0;

}