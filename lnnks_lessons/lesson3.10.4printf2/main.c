
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void) {
	short hd  = 1;
	char hhd = 255;

	long long lld = 0xFFFFFFFFFFFFFFFF;
	long ld =  0xFFFFFFFF;
	
	long double Lf = 29.010000001;
	printf("%hd %hu\r\n", hd, hd);
	printf("%hhd %hhu\r\n", hhd, hhd);
	printf("%ld %lu\r\n", ld, ld);
	printf("%llo %llX\r\n", lld, lld); // 1777777777777777777777 FFFFFFFFFFFFFFFF
	printf("%Lf %LE\r\n", Lf, Lf);

	printf("%zd\r\n", sizeof(long long));  //�Զ�������
	
	printf("%10hu %10hd\r\n", hd, hd);   // �Ҷ���10���       :         1          1
	printf("%-10hu %-10hd\r\n", hd, hd); //�����10���        :1          1
	printf("%010hu %010hd\r\n", hd, hd);   // �Ҷ���10��Ȳ�0  :0000000001 0000000001
	printf("%0.10hu %0.10hd\r\n", hd, hd);   // ָ�����Ȳ��㣬ͬ��

	printf("%.3Lf %.3LE\r\n", Lf, Lf);   // ���� 3λС��
	printf("%-20.10hu %-20.10hd\r\n", hd, hd); // �����20���, �ַ�10��Ȳ�0
	printf("%+hu %+hd\r\n", hd, hd);     // �з�������ʾ����λ ����+����- :  1 +1 
	printf("%+hu*% hd\r\n", hd, hd);     // ������λΪ�ո� 1* 1
	
	printf("%#llo %#llX\r\n", lld, lld); // 01777777777777777777777 0XFFFFFFFFFFFFFFFF
	return 0;

}