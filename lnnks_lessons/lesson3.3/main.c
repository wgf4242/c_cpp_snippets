// C���� ���������ڴ�������ô����� 0-1=255 https://www.bilibili.com/video/BV1vW4y187Ui
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	// ע�⣺ -128 �� ����-128. �з������߽綼�Ǵ�����������,
	unsigned char value = 255;
	printf("��Ȼ�� value = %hhu \r\n", value);
	printf("�з��� value = %hhd \r\n", value);
	
	unsigned char valIn = 0;
	// 0-127
	printf("������һ��0-127������:");
	scanf("%hhd", &valIn);
	unsigned char valOut = 255 - valIn + 1;
	printf("�з���  valOut = %hhd \r\n �޷���  valOut = %hhu", valOut, valOut);
	return 0;
}