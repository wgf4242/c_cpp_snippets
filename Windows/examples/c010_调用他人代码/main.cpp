// https://www.bilibili.com/video/BV1aq421c7q5/
#pragma once
#include <Windows.h>

#include <stdio.h>
#include "stds.h"

#pragma data_seg("sdatas")
char shellcode[71] = "\x8B\x4c"; // x64dbg ѡ�д����һ� - �༭ - �������� - C��ʽShellcode�ַ���
#pragma dataseg()
#pragma comment(linker, "/section:sdatas, RWE")  // ���ִ��Ȩ��

extern GetHashCodePtr GetHashCodeByShellCode = (GetHashCodePtr)(LPVOID)shellcode;

int main() {
	DWORD ret_1 = GetHashCode("mpc\\ui\\title\\title.bmp");      // �Լ�ʵ�ֵķ�ʽ
	DWORD ret_2 = GetHashCodeByShellCode("mpc\\ui\\title\\title.bmp");  // ����shellcode
	printf("GetHashCode              : %X\r\n", ret_1);
	printf("GetHashCodeByShellCode   : %X\r\n", ret_2);

	return 0;
}
