// cl /Od /EHsc main.cpp user32.lib /link /SUBSYSTEM:WINDOWS

/*
TLS_CALLBACK     Reason=1
TLS_CALLBACK_2   Reason=1

TLS_CALLBACK     Reason=2
TLS_CALLBACK_2   Reason=2

TLS_CALLBACK     Reason=2
TLS_CALLBACK_2   Reason=2

Reason = 1 → DLL_PROCESS_ATTACH
Reason = 2 → DLL_THREAD_ATTACH
Reason = 3 → DLL_THREAD_DETACH
Reason = 0 → DLL_PROCESS_DETACH
*/

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(lib,"ntdll.lib")

extern "C" NTSTATUS NTAPI NtQueryInformationProcess(HANDLE hProcess, ULONG InfoClass, PVOID Buffer, ULONG Length, PULONG ReturnLength);

#define NtCurrentProcess() (HANDLE)-1


void NTAPI __stdcall TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
    char buf[128];
    sprintf_s( buf, "[1]TLS_CALLBACK Reason = %lu", Reason );

    if (IsDebuggerPresent())
    {
        MessageBoxA(NULL, "[1]TLS_CALLBACK: Debugger Detected!", "TLS Callback", MB_OK);
//      ExitProcess(1);
    }
    else
    {
        // MessageBoxA(NULL, "[1]TLS_CALLBACK: No Debugger Present!...", "TLS Callback", MB_OK);
        MessageBoxA(NULL, buf, "[1]TLS Callback", MB_OK);
    }
}

void NTAPI __stdcall TLS_CALLBACK_2(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
    char buf[128];
    sprintf_s( buf, "[2]TLS_CALLBACK Reason = %lu", Reason );

    HANDLE DebugPort = NULL;
    if (!NtQueryInformationProcess(
        NtCurrentProcess(),
        7,          // ProcessDebugPort
        &DebugPort, // If debugger is present, it will be set to -1 | Otherwise, it is set to NULL
        sizeof(HANDLE),
        NULL))
    {
        if (DebugPort)
        {
            MessageBoxA(NULL, "[2]TLS_CALLBACK2: Debugger detected!", "TLS callback", MB_ICONSTOP);
        }

        else
        {
            MessageBoxA(NULL, buf, "[2]TLS callback", MB_ICONINFORMATION);
            // MessageBoxA(NULL, "[2]TLS_CALLBACK2: No debugger detected", "TLS callback", MB_ICONINFORMATION);
        }
    }
}

//linker spec通知链接器PE文件要创建TLS目录，注意X86和X64的区别
#ifdef _M_IX86
#pragma comment (linker, "/INCLUDE:__tls_used")
#pragma comment (linker, "/INCLUDE:__tls_callback")
#else
#pragma comment (linker, "/INCLUDE:_tls_used")
#pragma comment (linker, "/INCLUDE:_tls_callback")
#endif
//创建TLS段
EXTERN_C
#ifdef _M_X64
#pragma const_seg (".CRT$XLB")
const
#else
#pragma data_seg (".CRT$XLB")
#endif
//end linker

//tls import定义多个回调函数
PIMAGE_TLS_CALLBACK _tls_callback[] = { TLS_CALLBACK, TLS_CALLBACK_2, 0 };
#pragma data_seg ()
#pragma const_seg ()
//end 

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{

    MessageBoxA(NULL, "Hello Wolrd!...:)", "main()", MB_OK);
    return 0;

}
