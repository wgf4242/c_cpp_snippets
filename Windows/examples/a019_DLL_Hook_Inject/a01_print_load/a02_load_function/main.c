#include <stdio.h>
#include <windows.h>

// 定义函数指针类型，要根据实际DLL中函数的参数和返回值类型来修改
typedef int(*MYFUNCTIONTYPE)(int, int);

int main() {
	HMODULE hModule = LoadLibrary(TEXT("a01_print_01.dll"));
	if (hModule == NULL) {
		// 加载失败，输出错误信息并返回错误码
		printf("无法加载动态链接库\n");
		return 1;
	}

	// 获取名为MyFunction（假设DLL中函数叫这个名字，需按实际改）的函数地址
	MYFUNCTIONTYPE pMyFunction = (MYFUNCTIONTYPE)GetProcAddress(hModule, "add");
	if (pMyFunction == NULL) {
		// 获取函数地址失败的处理
		printf("无法获取函数地址\n");
		FreeLibrary(hModule);
		return 1;
	}

	// 调用函数，传入参数，这里示例传入两个整数参数，按实际函数要求调整
	int result = pMyFunction(5, 3);
	printf("函数调用结果: %d\n", result);

	FreeLibrary(hModule);
	return 0;
}