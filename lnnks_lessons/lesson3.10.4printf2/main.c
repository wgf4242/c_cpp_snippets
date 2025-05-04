
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

	printf("%zd\r\n", sizeof(long long));  //自定义类型
	
	printf("%10hu %10hd\r\n", hd, hd);   // 右对齐10宽度       :         1          1
	printf("%-10hu %-10hd\r\n", hd, hd); //左对齐10宽度        :1          1
	printf("%010hu %010hd\r\n", hd, hd);   // 右对齐10宽度补0  :0000000001 0000000001
	printf("%0.10hu %0.10hd\r\n", hd, hd);   // 指定精度补零，同上

	printf("%.3Lf %.3LE\r\n", Lf, Lf);   // 精度 3位小数
	printf("%-20.10hu %-20.10hd\r\n", hd, hd); // 左对齐20宽度, 字符10宽度补0
	printf("%+hu %+hd\r\n", hd, hd);     // 有符号数显示符号位 正数+负数- :  1 +1 
	printf("%+hu*% hd\r\n", hd, hd);     // 正符号位为空格 1* 1
	
	printf("%#llo %#llX\r\n", lld, lld); // 01777777777777777777777 0XFFFFFFFFFFFFFFFF
	return 0;

}