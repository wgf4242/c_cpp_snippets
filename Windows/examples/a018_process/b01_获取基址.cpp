//加载该DLL的进程的基址
HMODULE hExe = GetModuleHandle(NULL);
char buffer[100];
sprintf_s(buffer, "Process base address1: 0x%p\n", hExe);
OutputDebugStringA(buffer);