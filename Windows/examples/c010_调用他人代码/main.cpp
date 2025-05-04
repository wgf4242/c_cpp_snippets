// https://www.bilibili.com/video/BV1aq421c7q5/
#pragma once
#include <Windows.h>

#include <stdio.h>
#include "stds.h"

#pragma data_seg("sdatas")
char shellcode[71] = "\x8B\x4c"; // x64dbg 选中代码右击 - 编辑 - 复制数据 - C样式Shellcode字符串
#pragma dataseg()
#pragma comment(linker, "/section:sdatas, RWE")  // 添加执行权限

extern GetHashCodePtr GetHashCodeByShellCode = (GetHashCodePtr)(LPVOID)shellcode;

int main() {
	DWORD ret_1 = GetHashCode("mpc\\ui\\title\\title.bmp");      // 自己实现的方式
	DWORD ret_2 = GetHashCodeByShellCode("mpc\\ui\\title\\title.bmp");  // 调用shellcode
	printf("GetHashCode              : %X\r\n", ret_1);
	printf("GetHashCodeByShellCode   : %X\r\n", ret_2);

	return 0;
}
