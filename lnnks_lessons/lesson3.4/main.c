#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void salary();

int main() {
	unsigned char value = 0xff;
	printf("%hhd %hhu", value, value); // -1 255

	unsigned short vshort = value;
	printf("\r\nvshort:%hd %hu", vshort, vshort); // 255 ,255

	char values = 0xff;
	short vshorts = values; // �з���ת��ʱ����λ������λ 0b11111111 11111111
	printf("\r\nvshort:%hd %hu", vshorts, vshort); // -1,255

	printf("\r\n���ʹ�СΪ:[%d]", sizeof(vshort));

	printf("\r\n-----------\r\n");

	salary();
	return 0;
}

void salary() {
	unsigned Salary = 0;
	unsigned SalaryEnd = 0; // ��������
	printf("������:\r\n");
	scanf("%u", &Salary);

	// �㷨 <3000ʱΪ3000, ����3000ʱ ʵ�ʹ���
	// ���� if > < ?:
	printf("����������:[%d]\r\n", SalaryEnd);
	
}