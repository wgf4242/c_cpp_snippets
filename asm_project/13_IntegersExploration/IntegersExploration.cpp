#include<iostream>

extern "C" char GlChar = 10;
extern "C" short GlShort = 20;
extern "C" int GlInt= 30;
extern "C" long long GlLongLong = 344566;

extern "C" void IntegerAddition(char a , short b,int c,long long d);
int main(void) {
	
	//IntegerAddition(3, 5, -37, 11);
	IntegerAddition(3, 5, -37, 0x1100000001);
	
	printf("Char value %d\n", GlChar);
	printf("Short value %d\n", GlShort);
	printf("Int value %d\n", GlInt);
	printf("LongLong value %lld\n", GlLongLong);

	return 0;

}