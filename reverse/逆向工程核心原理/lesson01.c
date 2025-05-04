// x86 编译
#include<Windows.h>
#include<tchar.h>

int _tmain(int arg, TCHAR* argv[])
{
	MessageBoxW(NULL,
		L"Hello world",
		L"first program", MB_OK);
}