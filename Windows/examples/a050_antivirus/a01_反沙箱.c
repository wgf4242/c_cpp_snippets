// 一些木马反制技巧 https://mp.weixin.qq.com/s/5Y6PjMVdUeEkmVXzVKuR0g
// 1.反沙箱 白名单机制。将所有常用软件的名称添加到白名单中，然后遍历当前系统中的进程。如果白名单中的程序没有一个在运行，则可以判定当前环境可能为沙箱，从而触发木马程序退出
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>

bool is_process_running(const char* process_name) {
    bool found = false;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return false;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return false;
    }

    do {
        if (strcmp(pe32.szExeFile, process_name) == 0) {
            found = true;
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return found;
}

int main() {
    if (!is_process_running("qq.exe") && !is_process_running("wechat.exe")) {
        return 0;
    }

    return 0;
}