#include <windows.h>
#include <stdio.h>

int main() {
    // 分配一段内存
    int* pMemory = (int*)VirtualAlloc(NULL, sizeof(int), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (pMemory == NULL) {
        printf("内存分配失败。\n");
        return 1;
    }

    // 将数据写入内存
    *pMemory = 42;
    printf("初始值: %d\n", *pMemory);

    // 更改内存保护属性为只读
    DWORD oldProtect;
    if (VirtualProtect(pMemory, sizeof(int), PAGE_READONLY, &oldProtect)) {
        printf("内存保护属性已更改为只读。\n");
    }
    else {
        printf("无法更改内存保护属性。\n");
        VirtualFree(pMemory, 0, MEM_RELEASE);
        return 1;
    }

    // 尝试写入只读内存（这将导致程序崩溃）
    __try {
        *pMemory = 100;  // 由于内存现在是只读的，所以写入会触发访问冲突
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        printf("写入只读内存时发生异常。\n");
    }

    // 更改内存保护属性回可读写
    if (VirtualProtect(pMemory, sizeof(int), oldProtect, &oldProtect)) {
        *pMemory = 100;
        printf("新值: %d\n", *pMemory);
    }

    // 释放内存
    VirtualFree(pMemory, 0, MEM_RELEASE);
    return 0;
}
