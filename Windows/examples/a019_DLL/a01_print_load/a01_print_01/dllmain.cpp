// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>

// 导出 add 函数
extern "C" __declspec(dllexport) int add(int a, int b)
{
	return a + b;
}


int add2(int a, int b)
{
	return a + b + 1;
}

struct MyStruct {
	int a;
	int b;
};

// 修改后的函数
int add3(struct MyStruct s) {
	return s.a + s.b + 2; // 返回 struct.a + struct.b + 2
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	struct MyStruct myStruct = { 5, 6 };

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        add2(3, 4);
        add3(myStruct);
		printf("Hello World\n");
		break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

