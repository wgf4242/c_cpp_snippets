#include<iostream>

extern "C" int CountChar(wchar_t* s, wchar_t c);
int main(void) {
	// wchar,wprintf 是16位版本, 如果用char 汇编用 lodsb
	wchar_t c;
	wchar_t* s;
	s = (wchar_t*)L"Hello, assembly i awesome";
	c = L'e';
	
	wprintf(L"\n Test string: %s\n", s);
	wprintf(L"\n Search Character : %c Count:   %d\n", c,CountChar(s,c));
	
	
	return 0;

}