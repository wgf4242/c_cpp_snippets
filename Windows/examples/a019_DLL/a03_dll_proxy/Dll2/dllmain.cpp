// DLLProxying 下面是逗号
// cmd:  rundll32.exe DLLProxying.dll,whatever1
#include "pch.h"
#pragma comment(linker, "/export:whatever1=whatever.whatever1")

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, L"Dll Proxying!", L"Test", MB_OK);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}