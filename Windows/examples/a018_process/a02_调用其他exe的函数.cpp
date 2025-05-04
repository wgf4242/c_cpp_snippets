#include <windows.h>
#include <stdio.h>

// 定义函数指针，假设 `add` 函数为 `int add(int, int)`
typedef int (*AddFunc)(int, int);

int main() {
	// 加载 add.exe
	HMODULE hModule = LoadLibrary(L"add.exe");
	if (!hModule) {
		printf("Failed to load add.exe\n");
		return -1;
	}

	// 确定函数地址
	// 函数地址 = 模块基地址 + 偏移地址 (相对地址)
	void* funcAddr = (void*)0x0001400111E5;

	// 转换为函数指针
	AddFunc add = (AddFunc)funcAddr;
	// int (*add)(int, int) = (int (*)(int, int))funcAddr;

	// 调用函数
	int a = 5, b = 3;
	int result = add(a, b);

	printf("Result of add(%d, %d): %d\n", a, b, result);

	// 卸载模块
	FreeLibrary(hModule);

	return 0;
}
