
// 默认指定 /Zc:wchar_t
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	// typedef unsigned short wchar_t;
	// WinNT.h

	// Unicode
	wchar_t c = L'A';
	wchar_t szBuffer[100] = L"A String";
	printf("%d\n", (int)wcslen(szBuffer));

	//wcscpy(szBuffer1, "abc");
	//wcscpy_s(szBuffer1,3, "abc");
	//printf("sz1 is %s\n", szBuffer1);

	wchar_t szBuffer1[4] = L""; // abc+1
	wcscpy_s(szBuffer1, 4, L"abc"); // 包含 '\0'
	printf("sz1 is %ls\n", szBuffer1);
	
	wcscpy(szBuffer1, L"ab"); // 安全问题
	printf("sz1 is %ls\n", szBuffer1);
	
	// _countof // stdlib.h

	return 0;

}