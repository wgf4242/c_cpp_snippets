# include <stdio.h>
# include <Windows.h>

/*
函数原型：
BOOL WINAPI CreateProcess(
  _In_opt_     LPCTSTR lpApplicationName,
  _Inout_opt_  LPTSTR lpCommandLine,
  _In_opt_     LPSECURITY_ATTRIBUTES lpProcessAttributes,
  _In_opt_     LPSECURITY_ATTRIBUTES lpThreadAttributes,
  _In_         BOOL bInheritHandles,
  _In_         DWORD dwCreationFlags,
  _In_opt_     LPVOID lpEnvironment,
  _In_opt_     LPCTSTR lpCurrentDirectory,
  _In_         LPSTARTUPINFO lpStartupInfo,
  _Out_        LPPROCESS_INFORMATION lpProcessInformation
);
*/

int main(int argc, char* argv[])
{
    TCHAR commandLine[] = TEXT("notepad");
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    bool bRet = CreateProcess(
        NULL,
        commandLine,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi);
    int error = GetLastError();
    if (bRet)
    {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);

        printf("进程ID：%d\n", pi.dwProcessId);
        printf("线程ID：%d\n", pi.dwThreadId);
    }
    system("pause");
    return 0;
}