#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

int main(void) {
	unsigned ends0, ends1, ends2, ends3, ends4;
	unsigned _ends0, _ends1, _ends2, _ends3, _ends4;
	unsigned srandV;
	unsigned Number;
	unsigned rights = 0, i = 0;
	printf("��������ο������,�ö��ŷָ�:\r\n");
	scanf("%u,%u,%u,%u,%u", &ends0, &ends1, &ends2, &ends3, &ends4);
	srandV = time(0);
	while (srandV--) {
		srand(srandV);
		_ends0 = rand();
		_ends1 = rand();
		_ends2 = rand();
		_ends3 = rand();
		_ends4 = rand();
		if ((_ends0 == ends0) && (_ends1 == ends1) && (_ends2 == ends2) && (_ends3 == ends3) && (_ends4 == ends4)) {
			printf("ƥ�䵽�˹ؼ��� srand-key:u", srandV);
			break;
		}

		while(1) {
			Number = rand();
			printf("��һ�εĿ������Ϊ:[%u]\r\n", Number);
			system("pause");
		}
		return 1;
	}
}