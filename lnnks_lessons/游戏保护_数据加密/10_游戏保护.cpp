#include<iostream>

#include "hint.h"
int dimonds = 2500;
int main(void) {
	while (1) {
		std::cout << "��ǰ��ʯ�����Ϊ:" << dimonds;
		system("pause");
		dimonds = dimonds - 10;
	}

	return 0;

}