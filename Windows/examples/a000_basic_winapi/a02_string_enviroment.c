#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
int main() {
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];

	GetSystemDirectory(tzPath, MAX_PATH); // C:\windows\system32
    return 0;
}