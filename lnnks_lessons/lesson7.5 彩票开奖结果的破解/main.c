#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>

int main(void) {
	unsigned ends0, ends1, ends2, ends3, ends4;
	unsigned _ends0, _ends1, _ends2, _ends3, _ends4;
	unsigned srandV;
	unsigned Number;
	unsigned rights = 0, i = 0;
	printf("请输入五次开奖结果,用逗号分割:\r\n");
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
			printf("匹配到了关键的 srand-key:u", srandV);
			break;
		}

		while(1) {
			Number = rand();
			printf("下一次的开奖结果为:[%u]\r\n", Number);
			system("pause");
		}
		return 1;
	}
}