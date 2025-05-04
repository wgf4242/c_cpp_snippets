/*
1. dllexportviewer WeChatWin.dll 查看到  StartWechat, 
2. X64dbg启动 wechat.exe Ctrl+G定位到startwechat 下断。重新运行程序
3. Alt+K根据堆栈 找到上一层位置, 有1个参数是基址, 另一个但没分析出来
*/
#include <stdio.h>
#include <windows.h>

// 定义 StartWechat 函数指针类型

int main() {
    typedef int(*StartWechatFunc)(int, int);
    // 加载 DLL
    HINSTANCE hDll = LoadLibrary("WeChatWin.dll");
    StartWechatFunc startWechat = (StartWechatFunc)GetProcAddress(hDll, "StartWechat");
    // 调用函数并传入两个 0
    int result = startWechat(0, 0);
    printf("函数调用结果: %d", result);
    FreeLibrary(hDll);

    return 0;
}
