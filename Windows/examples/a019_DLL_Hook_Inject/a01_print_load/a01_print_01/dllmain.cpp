// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include <stdio.h>

// 导出 add 函数
extern "C" __declspec(dllexport) int add(int a, int b)
{
	return a + b;
}

// 新增函数，使用 char* 参数
extern "C" __declspec(dllexport) void printString(char* str)
{
    if (str != NULL) {
        printf("The string is: %s\n", str);
    }
}

// 新增返回 char* 的函数
extern "C" __declspec(dllexport) char* getString()
{
    static char result[] = "This is a string from DLL!";
    return result;
}

// 新增返回 int* 的函数
extern "C" __declspec(dllexport) int* getIntArray()
{
    static int arr[3] = { 1, 2, 3 };
    return arr;
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

// 定义一个简单的函数类型
typedef int (*MyFunction)(int);

// 一个示例函数
int addOne(int num) {
    return num + 1;
}

// 返回函数指针的函数
extern "C" __declspec(dllexport) MyFunction getFunction() {
    return addOne;
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

