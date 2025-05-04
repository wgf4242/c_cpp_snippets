#include<iostream>
extern "C" double FtoC(double deg_f);
extern "C" double CtoF(double deg_c);

int main(void) {

	double cel_temp = 30;
	double f_temp = 267;
	printf("Cel value : %10.4lf    Fah:   %10.4lf\n", cel_temp, CtoF(cel_temp));

	
	double deg_vals[] = { -476.89, -20, 0.0, 32.0, 90,-100,98.7, 200.45 };
	int nf = sizeof(deg_vals) / sizeof(double);
	
	for (int i = 0; i < nf; i++)
	{
		double deg_c = FtoC(deg_vals[i]);
		printf("i: %d f : %10.4lf c: %10.4lf \n", i, deg_vals[i], deg_c);
	}
	printf("\n");
	
	double deg_cvals[] = {-34,-90,45,16,89,-0.5,-45,100,-3,-10 };
	int nc = sizeof(deg_cvals) / sizeof(double);

	for (int i = 0; i < nc; i++)
	{
		double deg_f = CtoF(deg_cvals[i]);
		printf("i: %d c: %10.4lf     f : %10.4lf \n", i, deg_cvals[i], deg_f);
	}
	printf("\n");
	return 0;

}
