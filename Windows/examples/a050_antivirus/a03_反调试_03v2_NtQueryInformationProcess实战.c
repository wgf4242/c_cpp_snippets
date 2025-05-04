//可以运行的例子
#include<Windows.h>
#include <iostream>
#include <winternl.h>

using namespace std;

typedef NTSTATUS(CALLBACK* NtQueryInformationProcessPtr)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength OPTIONAL
);

int main()
{
    int debugPort = 0;
    HMODULE hModule = LoadLibrary(TEXT("Ntdll.dll"));
    NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hModule, "NtQueryInformationProcess");
    NtQueryInformationProcess(GetCurrentProcess(), (PROCESSINFOCLASS)0x7, &debugPort, sizeof(debugPort), NULL);
    cout << debugPort << endl;
    getchar();
    return 0;
}