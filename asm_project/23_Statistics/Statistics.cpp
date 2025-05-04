#include<iostream>

extern "C" bool CalcMeanStdevASM(const double* a, int n, double* mean, double* stdev);
bool CalcMeanStdevCPP(const double* a, int n, double* mean, double* stdev);
int main(void) {
	double a[] = { 2,5,6,7,12,45,67,12,9,0,1,3,21 };
	const int n = sizeof(a) / sizeof(double);
	
	double mean_cpp, stdev_cpp;
	double mean_asm, stdev_asm;

	CalcMeanStdevASM(a, n, &mean_asm, &stdev_asm);
	CalcMeanStdevCPP(a, n, &mean_cpp, &stdev_cpp);

	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = %g\n", i, a[i]);
	}

	printf("\n");
	printf("Assembly Mean:   %g Assembly Stdev : %g\n", mean_asm, stdev_asm);
	printf("CPP Mean:   %g CPP Stdev : %g\n", mean_cpp, stdev_cpp);

	return 0;

}
bool CalcMeanStdevCPP(const double* a, int n, double* mean, double* stdev) {
	if (n <= 1)
		return false;
	double sum = 0.0;

	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	*mean = sum / n;

	sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		double temp = a[i] - *mean; 
		sum += temp * temp;
	}
	*stdev = sqrt(sum / (n - 1));
	return true;
}