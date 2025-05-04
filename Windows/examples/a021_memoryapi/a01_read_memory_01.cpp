/*
要注意 x64 才能读取 x64
*/
#include <windows.h>
#include <iostream>

int main() {
    // 目标进程的 PID (可以通过任务管理器或其他方式获取)
    DWORD processID = 23828; // 替换为目标进程的实际 PID

    // 打开目标进程，获取句柄
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL) {
        std::cerr << "无法打开目标进程，错误代码：" << GetLastError() << std::endl;
        return 1;
    }

    // 假设已知要读取的内存地址
    LPCVOID targetAddress = (LPCVOID)0x2E8A9BE2010; // 替换为实际的内存地址

    // 修改内存保护属性以确保可读
    DWORD oldProtect;
    
    // 存储读取到的数据的缓冲区，长度为16字节
    BYTE buffer[16] = { 0 }; // 16字节缓冲区
    SIZE_T bytesRead;

    // 使用 ReadProcessMemory 读取目标进程的内存
    BOOL result = ReadProcessMemory(hProcess, targetAddress, buffer, sizeof(buffer), &bytesRead);
    if (!result) {
        std::cerr << "读取内存失败，错误代码：" << GetLastError() << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    // 输出读取到的数据
    std::cout << "读取到的数据: ";
    for (SIZE_T i = 0; i < bytesRead; ++i) {
        printf("%02X ", buffer[i]); // 以十六进制格式打印每个字节
    }
    std::cout << std::endl;

    std::cout << "读取的字节数: " << bytesRead << std::endl;

    // 关闭进程句柄
    CloseHandle(hProcess);

    return 0;
}