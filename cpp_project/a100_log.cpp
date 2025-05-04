// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include <windows.h>
#include <stdio.h>
#include <fstream>

// 定义函数指针类型
typedef int (*Printf_t)(const char* format, ...);
// 保存原始的 printf 函数指针
Printf_t Original_Printf = NULL;

// 保存原始函数的前5字节
static unsigned char original_bytes[5];
// 保存跳转指令
static unsigned char jump_bytes[5];

// hook 后的 printf 函数
int Hooked_Printf(const char* format, ...) {
	// 创建日志文件，记录更多信息
	std::ofstream log("hook_log.txt", std::ios::app);
	log << "Hook function called with format: " << format << "\n";
	log << "Original printf address: " << (void*)Original_Printf << "\n";
	log << "Current printf address: " << (void*)printf << "\n";
	log.close();

	// 先输出 "1"
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const char* extra = "1";
	DWORD written = 0;
	WriteFile(hConsole, extra, 1, &written, NULL);
	FlushFileBuffers(hConsole);

	// 恢复原始函数并调用
	DWORD oldProtect;
	VirtualProtect((LPVOID)printf, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((LPVOID)printf, original_bytes, 5);
	
	va_list args;
	va_start(args, format);
	int result = vprintf(format, args);
	va_end(args);
	
	// 重新应用 hook
	memcpy((LPVOID)printf, jump_bytes, 5);
	VirtualProtect((LPVOID)printf, 5, oldProtect, &oldProtect);
	
	return result;
}

void InstallHook() {
	std::ofstream log("hook_log.txt");
	log << "Installing hook...\n";
	log << "Original printf address: " << (void*)printf << "\n";
	
	// 保存原始函数的前5字节
	memcpy(original_bytes, printf, 5);
	log << "Original bytes: ";
	for(int i = 0; i < 5; i++) {
		log << std::hex << (int)original_bytes[i] << " ";
	}
	log << "\n";

	// 计算相对跳转地址
	DWORD jumpAddress = (DWORD)Hooked_Printf - (DWORD)printf - 5;
	
	// 构造跳转指令
	jump_bytes[0] = 0xE9;  // jmp 指令的操作码
	*(DWORD*)(&jump_bytes[1]) = jumpAddress;
	
	log << "Jump bytes: ";
	for(int i = 0; i < 5; i++) {
		log << std::hex << (int)jump_bytes[i] << " ";
	}
	log << "\n";
	
	// 修改内存保护属性并写入跳转指令
	DWORD oldProtect;
	BOOL protect = VirtualProtect((LPVOID)printf, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	log << "VirtualProtect result: " << protect << "\n";
	
	memcpy((LPVOID)printf, jump_bytes, 5);
	VirtualProtect((LPVOID)printf, 5, oldProtect, &oldProtect);
	
	log << "Hook installed\n";
	log.close();
}

void RemoveHook() {
	// 恢复原始函数
	DWORD oldProtect;
	VirtualProtect(printf, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(printf, original_bytes, 5);
	VirtualProtect(printf, 5, oldProtect, &oldProtect);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			const char* msg = "DLL Loaded\n";
			WriteConsoleA(hConsole, msg, strlen(msg), NULL, NULL);
			FlushFileBuffers(hConsole);
			InstallHook();
		}
		break;
	case DLL_PROCESS_DETACH:
		RemoveHook();
		break;
	}
	return TRUE;
}