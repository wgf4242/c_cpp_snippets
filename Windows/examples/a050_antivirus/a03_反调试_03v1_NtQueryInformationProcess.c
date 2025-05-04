// NtQueryInformationProcess
// 这个函数是Ntdll.dll中一个API，它用来提取一个给定进程的信息。
// 它的第一个参数是进程句柄，第二个参数告诉我们它需要提取进程信息的类型。
// 如果设置第二个参数指定特定值并调用该函数，相关信息就会设置到第三个参数。
// 第二个参数是一个枚举类型，其中与反调试有关的成员有ProcessDebugPort(0x7)、ProcessDebugObjectHandle(0x1E)和ProcessDebugFlags(0x1F)。
// 例如将该参数置为ProcessDebugPort，如果进程正在被调试，则返回调试端口，否则返回0。

BOOL CheckDebug()  
{  
    int debugPort = 0;  
    HMODULE hModule = LoadLibrary("Ntdll.dll");  
    NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hModule, "NtQueryInformationProcess");  
    NtQueryInformationProcess(GetCurrentProcess(), 0x7, &debugPort, sizeof(debugPort), NULL);  
    return debugPort != 0;  
}  

BOOL CheckDebug()  
{  
    HANDLE hdebugObject = NULL;  
    HMODULE hModule = LoadLibrary("Ntdll.dll");  
    NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hModule, "NtQueryInformationProcess");  
    NtQueryInformationProcess(GetCurrentProcess(), 0x1E, &hdebugObject, sizeof(hdebugObject), NULL);  
    return hdebugObject != NULL;  
}  

BOOL CheckDebug()  
{  
    BOOL bdebugFlag = TRUE;  
    HMODULE hModule = LoadLibrary("Ntdll.dll");  
    NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hModule, "NtQueryInformationProcess");  
    NtQueryInformationProcess(GetCurrentProcess(), 0x1F, &bdebugFlag, sizeof(bdebugFlag), NULL);  
    return bdebugFlag != TRUE;  
}