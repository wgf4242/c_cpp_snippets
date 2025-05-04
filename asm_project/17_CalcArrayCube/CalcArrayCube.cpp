#include<iostream>

// in x[3][2] are stored in memory asfollows: x[0][0], x[0][1], x[1][0], x[1][1], x[2][0], and x[2][1]
void CalcArrayCube(int* y, const int* x, int nrows, int ncols) {
	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			int k = i * ncols + j;
			y[k] = x[k] * x[k] * x[k];
		}
	}
}
int main(void) {
	const int nrows = 4;
	const int ncols = 3;
	int x[nrows][ncols] = { {1,2,3}, {4,5,6}, {7,8,9}, {10,11,12} };
	int y[nrows][ncols];

	CalcArrayCube(&y[0][0], &x[0][0], nrows, ncols);

	for (int i = 0; i < nrows; i++)
	{
		for (int j = 0; j < ncols; j++)
		{
			printf("(%2d, %2d) : ^%6d, %6d\n", i, j, x[i][j], y[i][j]);
		}
	}
	
	return 0;

}