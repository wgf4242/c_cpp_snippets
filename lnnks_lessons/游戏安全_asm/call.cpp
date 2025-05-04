#include<iostream>
int main(int argc, char const *argv[])
{
	unsigned Damage = 999999;
	unsigned beatProc = 0x41FD40;
	unsigned aim = 0x4CEF08;
	_asm {
		push 0x28
		push Damage
		mov ecx,aim
		call beatProc
	}
	
	return 0;
}