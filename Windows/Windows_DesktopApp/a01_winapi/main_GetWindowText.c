#include <stdio.h>
#include <windows.h>

int main() {
    HWND hWnd = FindWindow(NULL, TEXT("腾讯会议")); // 查找窗口标题为"腾讯会议"的窗口
    if (hWnd == NULL) {
        printf("找不到窗口\n");
        return 0;
    }

    char windowText[256];
    GetWindowTextA(hWnd, windowText, sizeof(windowText)); // 获取窗口标题的ANSI版本
    printf("窗口标题：%s\n", windowText);

    // 获取窗口的所有文本
    char buffer[1024];
    GetWindowTextA(hWnd, buffer, sizeof(buffer)); // 获取窗口文本的ANSI版本
    printf("窗口文本：%s\n", buffer);

    return 0;
}