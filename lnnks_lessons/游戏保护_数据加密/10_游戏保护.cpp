#include<iostream>

#include "hint.h"
int dimonds = 2500;
int main(void) {
	while (1) {
		std::cout << "当前钻石的余额为:" << dimonds;
		system("pause");
		dimonds = dimonds - 10;
	}

	return 0;

}