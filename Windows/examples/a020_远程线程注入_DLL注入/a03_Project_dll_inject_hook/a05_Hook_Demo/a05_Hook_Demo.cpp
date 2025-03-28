/*
* Hook show 函数, 在函数 启动前 弹出消息框, 结束后弹出消息框
* 未处理 卸载Hook
*/
// Debug编译版本才有效, Release需要 配置属性 - C/C++ - 优化 - 已禁用
#include <Windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

int g_counter = 1;
// 目标函数地址为 show
void show() {
    printf("Show: %d\n", g_counter++);
}

//const DWORD_PTR TARGET_ADDR = 0x12345678;
const DWORD_PTR TARGET_ADDR = (DWORD_PTR)&show;

BYTE originalBytes[9];    // 保存原始指令
BYTE* trampoline = nullptr; // 蹦床函数指针

// 消息框文本
const char* PRE_HOOK_MSG = "函数调用前";
const char* PRE_HOOK_TITLE = "钩子前置通知";
const char* POST_HOOK_MSG = "函数调用后";
const char* POST_HOOK_TITLE = "钩子后置通知";

// 汇编实现的钩子函数
__declspec(naked) void HookedFunction() {
    __asm {
        pushad                  // 保存所有寄存器状态
        push MB_OK
        push PRE_HOOK_TITLE     // 标题地址
        push PRE_HOOK_MSG       // 消息内容地址
        push 0
        call MessageBoxA        // 前置弹窗
        popad

        call trampoline         // 调用原始函数

        pushad
        push MB_OK
        push POST_HOOK_TITLE    // 后置弹窗标题
        push POST_HOOK_MSG      // 后置弹窗内容
        push 0
        call MessageBoxA
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
    BYTE* actualShowAddr = (BYTE*)TARGET_ADDR;
    
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
    trampoline = (BYTE*)VirtualAlloc(0, 0x64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
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

// 卸载钩子也需要修改
bool UninstallHook() {
    if (!trampoline) {
        return false;
    }
    
    // 获取show函数的实际地址
    BYTE* actualShowAddr = (BYTE*)TARGET_ADDR;
    
    // 检查函数开头是否是跳转指令(E9)
    if (actualShowAddr[0] == 0xE9) {
        // 计算跳转目标
        DWORD offset = *(DWORD*)(actualShowAddr + 1);
        actualShowAddr = actualShowAddr + 5 + offset;
    }

    // 恢复原始指令
    DWORD oldProtect;
    if (!VirtualProtect((void*)actualShowAddr, 5, PAGE_EXECUTE_READWRITE, &oldProtect)) {
        return false;
    }
    
    memcpy((void*)actualShowAddr, originalBytes, 5);
    VirtualProtect((void*)actualShowAddr, 5, oldProtect, &oldProtect);
    
    // 释放蹦床函数内存
    VirtualFree(trampoline, 0, MEM_RELEASE);
    trampoline = nullptr;
    
    return true;
}

// 示例使用
int main() {
    printf("安装钩子前调用原始函数:\n");
    show();
    
    printf("\n正在安装钩子...\n");
    if (InstallHook()) {
        printf("钩子安装成功!\n\n");
        
        printf("调用被钩住的函数:\n");
        show();
        
        printf("\n正在卸载钩子...\n");
        if (UninstallHook()) {
            printf("钩子卸载成功!\n\n");
            
            printf("钩子卸载后调用函数:\n");
            show();
        }
        else {
            printf("钩子卸载失败!\n");
        }
    }
    else {
        printf("钩子安装失败!\n");
    }
    
    printf("\n按任意键退出...");
    getchar();
    return 0;
}