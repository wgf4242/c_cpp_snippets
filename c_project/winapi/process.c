
#include <stdio.h>
#include "windows.h"
#include "process.h"

int main() {
    // HMODULE pHinstance = GetModuleHandle(NULL);
    HMODULE pHinstance = GetModuleHandle("Kernel32.dll");
    // HMODULE pHinstance = GetModuleHandle("clion64.exe");
    // GetModuleHandle(NULL);  // �⽫��������Ӧ�ó�����
    printf("%llx", pHinstance);
    return 0;
}
