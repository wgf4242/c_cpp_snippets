
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {

	int value, a, b, c, d;
	scanf("%d", &value); // 1234, ����Ϊ����(int) 1234
	scanf("%3d", &value); // ����3λ
	// ����������:
	scanf("%d %d %d %d", &a, &b, &c, &d);
	// ��������ĸ�ʽ:
	scanf("%d.%d", &a, &b); //����22.56 a=22 b=56
	// scanf��������Ը�ʽ����ǰ�Ŀո�, ע:% c����

	return 0;

}