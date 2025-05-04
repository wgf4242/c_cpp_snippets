#include<iostream>

extern "C" bool CalcMinMax(const float* a, int n, float* min, float* max);

int main(void) {
	float a[] = { 20,-34,56,87,-90,12,0,-0.0,-89 };
	
	const int n = sizeof(a) / sizeof(float);

	float min, max;

	CalcMinMax(a, n, &min, &max);
	for (int i = 0; i < n; i++)
	{
		printf("a[%2d] = %8.2f\n", i, a[i]);
	}
	printf("\n");
	printf("Minimum:  %8.2f    Maximum: %8.2f\n", min, max);
	return 0;

}