#include <windows.h>
#include <stdio.h>

void checkDebugger() {
    if (IsDebuggerPresent()) {
        ExitProcess(1);
}

// CheckRemoteDebuggerPresent 它不仅可以探测系统其他进程是否被调试
// 通过传递自身进程句柄还可以探测自身是否被调试。
BOOL CheckDebug()  
{  
    BOOL ret;  //ret存放结果的值
    CheckRemoteDebuggerPresent(GetCurrentProcess(), &ret);  
    return ret;  
}

int main() {
    checkDebugger();
    return 0;
}