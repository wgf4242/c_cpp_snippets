
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void onClick() {
	unsigned ucall =  0x41fd40;
	unsigned object = 0x4cef08;
	unsigned damage = 999999999;
	
	_asm {
		push 0x28
		push damage
		mov ecx, object
		call ucall
	}
}
int main(void) {
	onClick();
	return 0;
}