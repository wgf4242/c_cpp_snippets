// dllmain.cpp : 定义 DLL 应用程序的入口点。
// TARGET_ADDR , ptrShow_offset 值在程序更新后需要修改
#include "pch.h"
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <string> // 添加这行
#include <functional> // 添加这行
#include "client.h" // 修改为包含头文件而不是源文件

DWORD_PTR BASE = 0;
DWORD_PTR TARGET_ADDR = (DWORD_PTR)0x11A20;

BYTE originalBytes[9];    // 保存原始指令
BYTE* trampoline = nullptr; // 蹦床函数指针

__declspec(naked) void HookedFunction() {
    __asm {
        pushad                  // 保存所有寄存器状态, 加其他操作注意堆栈平衡
        //push esi
        //call label1
    //label1:
          popad
          ret
    }
}

/*
* 这是9个字节, 我也用9个字节
.text: 00B017D0 55                push    ebp
.text: 00B017D1 8B EC             mov     ebp, esp
.text: 00B017D3 81 EC C4 00 00 00 sub     esp, 0C4h
*/

// 初始化钩子
bool InstallHook() {
    // 获取show函数的实际地址（跳过可能的编译器生成的跳转指令）
    BYTE* actualShowAddr = BASE + (BYTE*)TARGET_ADDR;

    // 检查函数开头是否是跳转指令(E9)
    if (actualShowAddr[0] == 0xE9) {
        // 计算跳转目标
        DWORD offset = *(DWORD*)(actualShowAddr + 1);
        actualShowAddr = actualShowAddr + 5 + offset;
        printf("函数有跳转指令，实际地址: 0x%p\n", actualShowAddr);
    }

    // 1. 保存原始指令
    memcpy(originalBytes, actualShowAddr, 9);

    // 2. 创建蹦床函数（可执行内存）
    trampoline = (BYTE*)VirtualAlloc(0, 0x10, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (!trampoline) {
        printf("VirtualAlloc 失败，错误码: %d\n", GetLastError());
        return false;
    }

    // 复制原始指令
    memcpy(trampoline, originalBytes, 9);

    // 添加跳回原函数的JMP指令
    trampoline[9] = 0xE9; // JMP指令
    // 修正跳转地址计算
    //DWORD jumpAddr = (DWORD)(actualShowAddr + 9) - (DWORD)(trampoline + 9) + 5;
    DWORD jumpAddr = (DWORD)(actualShowAddr + 9) - (DWORD)(trampoline + 9) - 5; // 偏移地址 = 目的地址 - 跳转基地址(jmp的下一条指令的地址) - 5(E9 xx xx xx xx 跳转占5个字节)
    *(DWORD*)(trampoline + 9 + 1) = jumpAddr;

    // 3. 写入跳转指令到目标函数
    DWORD oldProtect;
    if (!VirtualProtect((void*)actualShowAddr, 9, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        printf("VirtualProtect 失败，错误码: %d\n", GetLastError());
        VirtualFree(trampoline, 0, MEM_RELEASE);
        trampoline = nullptr;
        return false;
    }

    *(BYTE*)actualShowAddr = 0xE9; // JMP
    *(DWORD*)(actualShowAddr + 1) = (DWORD)HookedFunction - (DWORD)actualShowAddr - 5;

    VirtualProtect((void*)actualShowAddr, 5, oldProtect, &oldProtect);

    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved)
{
    HMODULE hExe = NULL; // 初始化 hExe
    int offset = 0x1A014;
    uintptr_t ptr_g_counter;
    uintptr_t fnShow;
    int ptrShow_offset = 0x0011860;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBoxA(0, "Injected", "消息", 3); 

        //加载该DLL的进程的基址
        hExe = GetModuleHandle(NULL);
        char buffer[100];
        sprintf_s(buffer, "Process base address1: 0x%p\n", hExe);
        OutputDebugStringA(buffer);

        // 计算目标地址
        ptr_g_counter = (uintptr_t)hExe + offset;
        fnShow = (uintptr_t)hExe + ptrShow_offset;

        // 为了简化示例，我们直接输出目标地址，实际应用中你可能需要通过ReadProcessMemory来读取该地址的数据
        sprintf_s(buffer, "g_counter address: 0x%p\n", (void*)ptr_g_counter);
        OutputDebugStringA(buffer);

        BASE = (DWORD_PTR)hExe;
        InstallHook();
        // 调用客户端函数以发送数据到服务器
        SendDataToServer();

        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}