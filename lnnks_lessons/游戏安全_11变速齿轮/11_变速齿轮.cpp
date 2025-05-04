
#include <iostream>
#include <Windows.h>

int main(void) {

	unsigned tickStart = GetTickCount() * 10;
	system("pause");
	unsigned tickStop = GetTickCount() * 10;
	unsigned tickDiff = tickStop - tickStart;
	tickDiff = tickDiff / 1000;
	for (int i = 0; i < tickDiff; i++)
	{
		std::cout << "move once" << std::endl;
	}
	return 0;

}