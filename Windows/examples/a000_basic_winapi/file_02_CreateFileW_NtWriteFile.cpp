#include <windows.h>
#include <winternl.h>
#include <iostream>

// 定义 NtWriteFile 函数原型
typedef NTSTATUS(NTAPI* pfnNtWriteFile)(
    HANDLE FileHandle,
    HANDLE Event,
    PIO_APC_ROUTINE ApcRoutine,
    PVOID ApcContext,
    PIO_STATUS_BLOCK IoStatusBlock,
    PVOID Buffer,
    ULONG Length,
    PLARGE_INTEGER ByteOffset,
    PULONG Key);

int main()
{
    // 文件名
    wchar_t fileName[] = L"test.txt";

    // 创建文件
    HANDLE hFile = CreateFileW(
        fileName,                // 文件名
        GENERIC_READ | GENERIC_WRITE, // 访问权限
        0,                       // 不共享
        NULL,                    // 默认安全属性
        CREATE_ALWAYS,           // 始终创建新文件，如果存在则覆盖
        FILE_ATTRIBUTE_NORMAL,   // 正常文件属性
        NULL);                   // 模板文件句柄

    if (hFile == INVALID_HANDLE_VALUE)
    {
        std::wcerr << L"无法创建文件: " << GetLastError() << std::endl;
        return 1;
    }

    // 获取 ntdll.dll 的模块句柄并获取 NtWriteFile 的地址
    HMODULE hNtdll = GetModuleHandleW(L"ntdll.dll");
    pfnNtWriteFile NtWriteFile = (pfnNtWriteFile)GetProcAddress(hNtdll, "NtWriteFile");

    if (!NtWriteFile)
    {
        std::wcerr << L"无法获取 NtWriteFile 函数地址." << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // 写入缓冲区
    const char* writeBuffer = "Hello, World!";
    ULONG bufferLength = (strlen(writeBuffer)) * sizeof(char);
    
    //const wchar_t* writeBuffer = L"Hello, World!"; // 每个字符占2字节
    //ULONG bufferLength = (wcslen(writeBuffer)) * sizeof(wchar_t);
    IO_STATUS_BLOCK ioStatusBlock;

    // 调用 NtWriteFile 写入数据到文件
    NTSTATUS status = NtWriteFile(
        hFile,          // 文件句柄
        NULL,           // 事件（不使用）
        NULL,           // APC例程（不使用）
        NULL,           // APC上下文（不使用）
        &ioStatusBlock, // I/O状态块
        (PVOID)writeBuffer, // 缓冲区指针
        bufferLength,   // 缓冲区长度
        NULL,           // 字节偏移量（不使用）
        NULL            // 键（不使用）
    );

    if (!NT_SUCCESS(status))
    {
        std::wcerr << L"NtWriteFile 失败, 状态码: " << status << std::endl;
    }
    else
    {
        std::wcout << L"成功写入文件." << std::endl;
    }

    // 关闭文件句柄
    CloseHandle(hFile);

    return 0;
}