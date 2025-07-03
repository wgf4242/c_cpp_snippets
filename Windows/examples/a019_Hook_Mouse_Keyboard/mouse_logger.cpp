/**
 * Windows鼠标记录器 - 控制台输出版
 * 
 * 功能：记录用户的鼠标操作并在控制台中显示
 * 使用方法：在Windows系统中编译并运行此程序，按ESC键退出
 * 
 * 编译命令：
 * cl mouse_logger.cpp /link user32.lib
 */

#include <windows.h>
#include <stdio.h>
#include <time.h>

// 全局钩子句柄
HHOOK mouseHook;
HHOOK keyboardHook; // 用于捕获ESC键退出

// 获取当前时间的格式化字符串
void getCurrentTime(char* buffer, size_t bufferSize) {
    time_t rawtime;
    struct tm timeinfo;
    
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    
    strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", &timeinfo);
}

// 获取鼠标事件类型的字符串描述
void getMouseEventName(DWORD mouseData, WPARAM wParam, char* buffer, size_t bufferSize) {
    switch (wParam) {
        case WM_LBUTTONDOWN:
            strcpy_s(buffer, bufferSize, "左键按下");
            break;
        case WM_LBUTTONUP:
            strcpy_s(buffer, bufferSize, "左键释放");
            break;
        case WM_RBUTTONDOWN:
            strcpy_s(buffer, bufferSize, "右键按下");
            break;
        case WM_RBUTTONUP:
            strcpy_s(buffer, bufferSize, "右键释放");
            break;
        case WM_MBUTTONDOWN:
            strcpy_s(buffer, bufferSize, "中键按下");
            break;
        case WM_MBUTTONUP:
            strcpy_s(buffer, bufferSize, "中键释放");
            break;
        case WM_MOUSEWHEEL:
            if (GET_WHEEL_DELTA_WPARAM(mouseData) > 0) {
                strcpy_s(buffer, bufferSize, "滚轮向上");
            } else {
                strcpy_s(buffer, bufferSize, "滚轮向下");
            }
            break;
        case WM_MOUSEMOVE:
            strcpy_s(buffer, bufferSize, "鼠标移动");
            break;
        default:
            sprintf_s(buffer, bufferSize, "未知事件: 0x%04X", (unsigned int)wParam);
            break;
    }
}

// 键盘钩子回调函数（仅用于捕获ESC键退出）
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // 如果nCode小于0，必须调用CallNextHookEx
    if (nCode < 0) {
        return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
    }
    
    // 只处理按键按下事件
    if (wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        
        // 如果按下ESC键，发送退出消息
        if (kbStruct->vkCode == VK_ESCAPE) {
            char timeBuffer[64];
            getCurrentTime(timeBuffer, sizeof(timeBuffer));
            printf("[%s] 检测到Esc键，程序退出...\n", timeBuffer);
            PostQuitMessage(0);
        }
    }
    
    // 继续传递给下一个钩子
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

// 鼠标钩子回调函数
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // 如果nCode小于0，必须调用CallNextHookEx
    if (nCode < 0) {
        return CallNextHookEx(mouseHook, nCode, wParam, lParam);
    }
    
    // 处理鼠标事件
    MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;
    
    // 获取当前时间
    char timeBuffer[64];
    getCurrentTime(timeBuffer, sizeof(timeBuffer));
    
    // 获取鼠标事件类型
    char eventName[64];
    getMouseEventName(mouseStruct->mouseData, wParam, eventName, sizeof(eventName));
    
    // 在控制台输出鼠标信息
    // 对于鼠标移动事件，可以选择减少输出频率以避免刷屏
    if (wParam == WM_MOUSEMOVE) {
        // 可以通过静态变量控制输出频率，例如每10次移动输出一次
        static int moveCounter = 0;
        if (moveCounter++ % 10 == 0) {
            printf("[%s] %s: 位置(%ld, %ld)\n", 
                   timeBuffer, eventName, 
                   mouseStruct->pt.x, mouseStruct->pt.y);
        }
    } else {
        // 对于其他鼠标事件，全部输出
        printf("[%s] %s: 位置(%ld, %ld)\n", 
               timeBuffer, eventName, 
               mouseStruct->pt.x, mouseStruct->pt.y);
    }
    
    // 继续传递给下一个钩子
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

int main() {
    // 设置控制台编码为UTF-8，以正确显示中文
    // SetConsoleOutputCP(65001);
    // SetConsoleOutputCP(CP_UTF8);
    
    printf("==================================================\n");
    printf("Windows鼠标记录器 - 控制台输出版\n");
    printf("==================================================\n");
    printf("程序已启动，正在记录鼠标操作...\n");
    printf("按下Esc键可退出程序\n");
    printf("--------------------------------------------------\n");
    
    // 获取当前模块句柄
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // 安装低级鼠标钩子
    mouseHook = SetWindowsHookEx(
        WH_MOUSE_LL,        // 钩子类型：低级鼠标
        MouseProc,          // 回调函数
        hInstance,          // 实例句柄
        0                   // 全局钩子
    );
    
    if (mouseHook == NULL) {
        printf("安装鼠标钩子失败，错误代码: %d\n", GetLastError());
        return 1;
    }
    
    // 安装低级键盘钩子（仅用于捕获ESC键退出）
    keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,     // 钩子类型：低级键盘
        KeyboardProc,       // 回调函数
        hInstance,          // 实例句柄
        0                   // 全局钩子
    );
    
    if (keyboardHook == NULL) {
        printf("安装键盘钩子失败，错误代码: %d\n", GetLastError());
        UnhookWindowsHookEx(mouseHook);
        return 1;
    }
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // 卸载钩子
    UnhookWindowsHookEx(mouseHook);
    UnhookWindowsHookEx(keyboardHook);
    
    printf("鼠标记录器已停止\n");
    return 0;
}
