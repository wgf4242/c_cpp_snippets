
#include<iostream>

extern "C" bool SseSphereCalculator(double r, double* sa, double* v);
int main(void) {
	const double r[] = { -1.0,0.0,1.0,3.0,9.0,8.0,2.3,4.5,6.7 };
	int num_r = sizeof(r) / sizeof(double);
	
	for (int i = 0; i < num_r; i++)
	{
		double sa, v;
		bool rv;
		rv = SseSphereCalculator(r[i], &sa, &v);
		printf("rv: %d   r:%8.2lf  sa: %10.4lf  vol: %10.4lf\n", rv, r[i], sa, v);
	}
	return 0;

}