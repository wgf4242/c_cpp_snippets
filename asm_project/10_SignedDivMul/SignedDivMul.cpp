
#include<iostream>

extern "C" int IntegerMulDiv(int a, int b, int* prod, int* quo, int* rem);
int main(void) {

	int a = 21, b = 9;
	int prod = 0, quo = 0, rem = 0;
	int rv;

	rv = IntegerMulDiv(a, b, &prod, &quo, &rem);
	
	printf("Input a: %4d      b:     %4d\n", a, b);
	printf("Output rv: %4d  prod: %4d   quo: %4d      rem  %4d\n", rv, prod, quo, rem);
	
	return 0;

}