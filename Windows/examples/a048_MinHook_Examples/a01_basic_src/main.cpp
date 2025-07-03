#include <Windows.h>
#include "minhook/include/MinHook.h"
typedef int(WINAPI* fMessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);
fMessageBoxA pMessageBoxA = NULL;

int WINAPI HookMessageBoxA(HWND hwnd, LPCSTR l, LPCSTR l2, UINT l3)
{
    return pMessageBoxA(hwnd, "Hello World", l2, l3);
}

int main()
{
    MH_Initialize();

    MH_CreateHook(&MessageBoxA, &HookMessageBoxA, (LPVOID*)&pMessageBoxA);
    // MH_CreateHookApiEx ʹ��
    //MH_CreateHookApiEx(L"user32", "MessageBoxA", &HookMessageBoxA, (LPVOID*)&pMessageBoxA, NULL);
    
    //δhook
    MessageBoxA(NULL, "���", "title:", NULL);

    //hook��
    MH_EnableHook(&MessageBoxA);
    MessageBoxA(NULL, "���", "title:", NULL);

    MH_DisableHook(&MessageBoxA);
    MessageBoxA(NULL, "���2", "title:", NULL);

    MH_Uninitialize();

    return 0;
}