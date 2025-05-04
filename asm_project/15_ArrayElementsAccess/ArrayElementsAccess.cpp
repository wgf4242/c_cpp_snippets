
#include<iostream>

extern "C" int CalcArraySumASM(int* x, int n);

int CalcArraySumCPP(int* x, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += *x++;
	}return sum;
}
int main(void) {
	
	int x[] = { 1,3,4,5,10,8,45 };
	int n = sizeof(x) / sizeof(int);
	int asm_sum, cpp_sum;
	asm_sum = CalcArraySumASM(x, n);
	cpp_sum = CalcArraySumCPP(x, n);
	
	printf("Assembly sum = %d\n", asm_sum);
	printf("C++ sum = %d\n", cpp_sum);


	
	return 0;

}