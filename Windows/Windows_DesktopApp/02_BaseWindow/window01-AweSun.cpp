// cl.exe AweSun.cpp /link user32.lib /OUT:AweSun.exe
#include <windows.h>

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        // 关闭窗口时退出程序
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        // 默认消息处理
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    // 1. 定义窗口类（类名：OrayUI，ANSI字符串，去掉L前缀）
    const char CLASS_NAME[] = "OrayUI";
    WNDCLASSA wc = {0}; // 显式使用ANSI版本WNDCLASSA
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // 白色背景

    // 注册窗口类
    RegisterClassA(&wc); // 显式使用ANSI版本RegisterClassA

    // 2. 创建窗口（匹配JSON属性，改用ANSI版本CreateWindowExA）
    HWND hwnd = CreateWindowExA(
        24,                  // exStyle：对应JSON里的24
        CLASS_NAME,          // 窗口类名（ANSI）
        "远程桌面工具栏",    // 窗口标题（ANSI，去掉L前缀）
        2516713472,          // style：对应JSON里的2516713472
        // 窗口位置（居中）、尺寸（426x82，JSON第一个rectangle）
        CW_USEDEFAULT, CW_USEDEFAULT, 426, 82,
        NULL,       // 父窗口
        NULL,       // 菜单
        hInstance,  // 实例句柄
        NULL        // 附加参数
    );

    if (hwnd == NULL) {
        return 0;
    }

    // 3. 显示窗口
    ShowWindow(hwnd, nCmdShow);

    // 4. 消息循环（保持程序运行）
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}