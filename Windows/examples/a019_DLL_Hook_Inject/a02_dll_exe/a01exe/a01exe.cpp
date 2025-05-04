#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "a01exe.h"


void dllFunc1(HMODULE h)
{
    // 定义函数指针类型，与ShowMessageBox的签名匹配
    typedef void (*ShowMessageBoxFunc)();

    // 获取ShowMessageBox函数的地址
    ShowMessageBoxFunc showMsgBox = (ShowMessageBoxFunc)GetProcAddress(h, "ShowMessageBox");
    if (showMsgBox == NULL) {
        // 获取函数地址失败
        std::cerr << "无法找到 ShowMessageBox 函数" << std::endl;
        return;
    }

    // 调用导出的函数
    showMsgBox();
}

int main()
{
	HMODULE hModule = LoadLibrary(TEXT("a02dll.dll"));
	if (hModule == NULL) {
		// 加载失败，输出错误信息并返回错误码
		printf("无法加载动态链接库\n");
		return 1;
	}

    dllFunc1(hModule);

    // 释放DLL
    FreeLibrary(hModule);
    std::cout << "Hello World!\n";
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
