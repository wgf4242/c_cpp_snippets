#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void salary();

int main() {
	unsigned char value = 0xff;
	printf("%hhd %hhu", value, value); // -1 255

	unsigned short vshort = value;
	printf("\r\nvshort:%hd %hu", vshort, vshort); // 255 ,255

	char values = 0xff;
	short vshorts = values; // 有符号转换时，高位补符号位 0b11111111 11111111
	printf("\r\nvshort:%hd %hu", vshorts, vshort); // -1,255

	printf("\r\n类型大小为:[%d]", sizeof(vshort));

	printf("\r\n-----------\r\n");

	salary();
	return 0;
}

void salary() {
	unsigned Salary = 0;
	unsigned SalaryEnd = 0; // 最终收入
	printf("收入金额:\r\n");
	scanf("%u", &Salary);

	// 算法 <3000时为3000, 大于3000时 实际工资
	// 不用 if > < ?:
	printf("最终收入是:[%d]\r\n", SalaryEnd);
	
}