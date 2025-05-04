#include <Windows.h>
#include <iostream>

int main()
{
    CONTEXT TestContext;
    ZeroMemory(&TestContext, sizeof(CONTEXT)); // 将结构体清零
    TestContext.ContextFlags = CONTEXT_DEBUG_REGISTERS;


    if (GetThreadContext(GetCurrentThread(), &TestContext)) {
        if (TestContext.Dr0 != 0 || TestContext.Dr1 != 0 ||
            TestContext.Dr2 != 0 || TestContext.Dr3 != 0) {
            MessageBoxA(NULL, "硬件断点检测成功, 程序正在被调试！", "硬件断点检测", MB_OK);
        }
        else {
            MessageBoxA(NULL, "没有检测到硬件断点。", "硬件断点检测", MB_OK);
        }
    }
    else {
        DWORD dwError = GetLastError();
        std::cerr << "GetThreadContext failed with error: " << dwError << std::endl;
        MessageBoxA(NULL, "无法获取线程上下文信息。", "错误", MB_OK);
    }

    system("pause"); // 使用cin.get()或std::getchar()可能是一个更好的选择
    return 0;
}