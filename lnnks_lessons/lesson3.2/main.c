// scanf����ȫ��һ��Ҫ�ã�ͨ���궨����Ծ��棬д��ǰ��
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	unsigned int MSalary = 0, WSalary = 0;
	unsigned ASalary = 0, YSalary = 0;

	printf("������ְֵĹ���:");
	scanf("%u", &MSalary);
	printf("����������Ĺ���:");
	scanf("%u", &WSalary);

	ASalary = MSalary + WSalary;
	ASalary = ASalary / 2;

	YSalary = (MSalary + WSalary) * 12;

	printf("�ְֵĹ�����:[%u}\r\n����Ĺ�����[%u]\r\n��ͥ�˵�ƽ������Ϊ:[%u]\r\n��ͥ����Ϊ:[%u]", MSalary, WSalary, ASalary, YSalary);

	return 0;
}