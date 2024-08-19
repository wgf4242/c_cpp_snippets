#include<windows.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<TlHelp32.h>

DWORD FindProcess() {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 pe32;
    pe32 = { sizeof(pe32) };
    BOOL ret = Process32First(hSnap, &pe32);
    while (ret)
    {
        if (!wcsncmp(pe32.szExeFile, L"mine.exe", 11)) {
            printf("Find winmine.exe Process %d\n", pe32.th32ProcessID);
            return pe32.th32ProcessID;
        }
        ret = Process32Next(hSnap, &pe32);
    }
    return 0;
}

void Inject(DWORD ProcessId, const char* szPath)
{
    //1.打开目标进程获取句柄
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
    printf("进程句柄:%p\n", hProcess);
    //2.在目标进程体内申请空间
    LPVOID lpAddress = VirtualAllocEx(hProcess, NULL, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    //3.写入DLL路径
    SIZE_T dwWriteLength = 0;
    WriteProcessMemory(hProcess, lpAddress, szPath, strlen(szPath), &dwWriteLength);
    //4.创建远程线程，回调函数使用 LoadLibrary 加载指定 dll
    HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, lpAddress, NULL, NULL);
    //5.等待返回（loadLibrary返回）
    WaitForSingleObject(hThread, -1);
    //6.释放空间
    VirtualFreeEx(hProcess, lpAddress, 0, MEM_RELEASE);
    //7.释放句柄
    CloseHandle(hProcess);
    CloseHandle(hThread);
}

int main() {
    DWORD ProcessId = FindProcess();
    while (!ProcessId) {
        printf("未找到扫雷程序，等待两秒中再试\n");
        Sleep(2000);
        ProcessId = FindProcess();
    }
    printf("开始注入进程...\n");
    Inject(ProcessId, "D:\MFCLibrary2.dll");
    printf("注入完毕\n");

}
