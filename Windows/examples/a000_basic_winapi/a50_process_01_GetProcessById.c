#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <wchar.h>

DWORD GetProcessIdByName(const char* processName) {
    wchar_t  wideProcessName[100];
    swprintf(wideProcessName, 100, L"%hs", processName);

    HANDLE hSnap;
    PROCESSENTRY32W pe32;
    DWORD pid = 0;

    hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    Process32FirstW(hSnap, &pe32);
    do {
        if (wcscmp(pe32.szExeFile, wideProcessName) == 0) {
            pid = pe32.th32ProcessID;
            break;
        }
    } while (Process32NextW(hSnap, &pe32));

    CloseHandle(hSnap);
    return pid;
}

int main() {
    DWORD pid = GetProcessIdByName("EmEditor.exe");
    printf("%lu\n", pid);
    return 0;
}