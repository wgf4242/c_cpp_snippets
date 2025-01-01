#include <stdio.h>

int add2(int a, int b)
{
	return a + b + 1;
}

int main() {
	int r1 = add2(3, 4);
	printf("%d", r1);
	return  0;
}