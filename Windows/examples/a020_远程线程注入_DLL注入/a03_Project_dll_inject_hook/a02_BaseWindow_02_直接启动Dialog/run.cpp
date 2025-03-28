#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <direct.h>
#include <tchar.h>

// 启动目标进程并返回进程句柄
HANDLE StartTargetProcess(const char* targetPath) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    if (CreateProcess(targetPath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        return pi.hProcess;
    }
    /*if (CreateProcess(targetPath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        return pi.hProcess;
    }*/
    return NULL;
}

// 注入 DLL 到目标进程
BOOL InjectDLL(HANDLE hProcess, const char* dllPath) {
    SIZE_T dllPathLen = strlen(dllPath) + 1;
    LPVOID remoteDllPath = VirtualAllocEx(hProcess, NULL, dllPathLen, MEM_COMMIT, PAGE_READWRITE);
    if (!remoteDllPath) {
        return FALSE;
    }

    if (!WriteProcessMemory(hProcess, remoteDllPath, dllPath, dllPathLen, NULL)) {
        VirtualFreeEx(hProcess, remoteDllPath, 0, MEM_RELEASE);
        return FALSE;
    }

    HMODULE hKernel32 = GetModuleHandle("kernel32.dll");
    FARPROC loadLibraryAddr = GetProcAddress(hKernel32, "LoadLibraryA");
    if (!loadLibraryAddr) {
        VirtualFreeEx(hProcess, remoteDllPath, 0, MEM_RELEASE);
        return FALSE;
    }

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddr, remoteDllPath, 0, NULL);
    if (!hThread) {
        VirtualFreeEx(hProcess, remoteDllPath, 0, MEM_RELEASE);
        return FALSE;
    }

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    VirtualFreeEx(hProcess, remoteDllPath, 0, MEM_RELEASE);
    return TRUE;
}

void runproc() {
    TCHAR buffer[MAX_PATH] = _T("");

    // 获取当前工作目录
    _getcwd(buffer, MAX_PATH);
    TCHAR debugMessage[MAX_PATH * 2] = _T("");
    _stprintf(debugMessage, _T("Current directory: %s\n"), buffer);
    OutputDebugString(debugMessage);

    //const char* targetPath = "D:\\temp\\cprojects\\Project_dll_inject_hook\\Release\\a01_random_data.exe";
    const char* targetPath = "a01_random_data.exe";
    const char* dllPath = "a03_call_dll.dll";

    HANDLE hProcess = StartTargetProcess(targetPath);
    if (!hProcess) {
        OutputDebugStringA("Failed to start target process.\n");
    }
    else {
        if (!InjectDLL(hProcess, dllPath)) {
            OutputDebugStringA("Failed to inject DLL.\n");
        }
        //HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, GetThreadId(hProcess));
        //if (hThread) {
        //    ResumeThread(hThread);
        //    CloseHandle(hThread);
        //}
        //CloseHandle(hProcess);
    }
}