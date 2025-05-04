// scanf不安全，一定要用，通过宏定义忽略警告，写最前面
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	unsigned int MSalary = 0, WSalary = 0;
	unsigned ASalary = 0, YSalary = 0;

	printf("请输入爸爸的工资:");
	scanf("%u", &MSalary);
	printf("请输入妈妈的工资:");
	scanf("%u", &WSalary);

	ASalary = MSalary + WSalary;
	ASalary = ASalary / 2;

	YSalary = (MSalary + WSalary) * 12;

	printf("爸爸的工资是:[%u}\r\n妈妈的工资是[%u]\r\n家庭人的平均工资为:[%u]\r\n家庭年收为:[%u]", MSalary, WSalary, ASalary, YSalary);

	return 0;
}