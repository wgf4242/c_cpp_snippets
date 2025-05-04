#include <stdio.h>
#include <windows.h>

BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam) {
    char buffer[1024];
    GetWindowTextA(hWnd, buffer, sizeof(buffer));
    printf("子窗口文本：%s\n", buffer);
    return TRUE;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    EnumChildWindows(hWnd, EnumChildProc, 0);
    return TRUE;
}

int main() {
    EnumWindows(EnumWindowsProc, 0);
    return 0;
}