
#include<iostream>

extern "C" int CalcArraySquaresASM(int* y, int* x, int n);
int CalcArraySquaresCPP(int* y, int* x, int n);
int main(void) {

	int x[] = { 2,3,4,5,6,7,8,9 };

	const int n = sizeof(x) / sizeof(int);
	int y1[n];
	int y2[n];
	int asm_sum, cpp_sum;
	
	asm_sum = CalcArraySquaresASM(y2, x, n);
	cpp_sum = CalcArraySquaresCPP(y1, x, n);
	
	for (int i = 0; i < n; i++)
	{
		printf("i: %2d  x:%4d y1: %4d  y2:%4d\n", i, x[i], y1[i], y2[i]);
		printf("\n");
	}
	printf("Assembly sum: %d\n", asm_sum);
	printf("C++ sum: %d\n", cpp_sum);


	return 0;

}

int CalcArraySquaresCPP(int* y, int* x, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		y[i] = x[i] * x[i];
		sum += y[i];
	}
	return sum;
}