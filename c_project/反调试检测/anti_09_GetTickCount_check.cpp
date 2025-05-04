#include <Windows.h>
#include <iostream>

BOOL IsDebuggerPresentWithTiming() {
    DWORD startTick, endTick, elapsed;

    // 获取初始的 tick 计数
    startTick = GetTickCount();

    // 此处可以添加代码
    OutputDebugString(L"Debugger check...\n");
    // OutputDebugString("Debugger check...\n");

    // 获取结束的 tick 计数
    endTick = GetTickCount();

    // 计算经过的 tick 数
    elapsed = endTick - startTick;

    // 如果时间差超出预设值，则可能存在调试器。
    if (elapsed > 200) {
        return TRUE;
    }
    return FALSE;
}

int main() {
    if (IsDebuggerPresentWithTiming()) {
        std::cout << "可能检测到调试器！" << std::endl;
    }
    else {
        std::cout << "没有检测到调试器！" << std::endl;
    }
    return 0;
}