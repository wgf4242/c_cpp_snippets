
#include<iostream>
extern "C" bool CalcSphereAreaVolume(double r, double* sa, double* v);
int main(void) {

	double r[] = { 0.0, 1.0, 2.0,3.0,4.0,5.0,20.0,34.0 };
	int num_r = sizeof(r) / sizeof(double);
	
	for (int i = 0; i < num_r; i++)
	{
		double sa = -1;
		double v = -1;
		bool rv;
		rv = CalcSphereAreaVolume(r[i], &sa, &v);
		
		printf("rv: %d  r:%8.2lf   sa:%10.4lf  v:%10.4lf\n", rv, r[i], sa, v);
	
	}
	return 0;

}