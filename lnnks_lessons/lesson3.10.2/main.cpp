
#include<iostream>
using namespace std;
int main(void) {
	int v1 = 1000;
	cout  << v1 - 1500 << endl; // -500

	unsigned short v2 = 1000;
	cout << v2 - 1500 << endl; // -500 unsigned short 升级为int
	
	cout << sizeof(3.0 - 2) << endl; // 8 , 3 double 8 Bytes
	cout << sizeof(3.0f - 2LL) << endl; // 4 , 3 float 4 B, 精度损失
	cout << sizeof((double)1 ) << endl; // 8
	
	
	int v3 = 1.3 + 1.7; // 自动(int)(1.3 + 1.7)
	cout << v3 << endl; // 3
	cout << (int)1.3 + (int)1.7 << endl; // 2


	// 低等级类型负数转换为高等级整数,会通过补1保留负数的属性
	char v4 = -1;
	int x = v4;
	cout << x << "," << hex <<  x << dec << endl;

	// 浮点数转为整数会丢弃小数部分,如果超出整数的保存范围,行为是未定义的.
	float f = 30.123;
	int t = f;
	cout << t << endl; // 丢弃小数 30

	float f1 = 30000000000000.00;
	int t1 = f1;
	cout << t1 << endl; // 负值


	return 0;

}