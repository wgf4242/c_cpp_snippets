#include <stdio.h>
#include <windows.h>

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
    char buffer[1024];
    GetWindowTextA(hWnd, buffer, sizeof(buffer));
    printf("子窗口文本：%s\n", buffer);
    return TRUE;
}

int main() {
    HWND hWnd = FindWindow(NULL, TEXT("腾讯会议")); // 查找窗口标题为"腾讯会议"的窗口
    if (hWnd == NULL) {
        printf("找不到窗口\n");
        return 0;
    }

    EnumChildWindows(hWnd, EnumChildProc, 0);

    return 0;
}