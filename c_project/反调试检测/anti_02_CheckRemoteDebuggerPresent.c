// https://mp.weixin.qq.com/s/KPOt_ezHVwSNPlyblLByXQ
// CheckRemoteDebuggerPresent 不仅可以探测进程自身是否被调试，也可以探测系统其他进程是否被调试。函数接收两个参数进程句柄和一个指向布尔值的指针。如果指定的进程正在被调试，则函数会把指向布尔值的指针设为 TRUE，否则设为FALSE。
// 在xdbg中Ctrl+G搜索CheckRemoteDebuggerPresent，可以找到该函数的汇编代码。 在17行调用了NtQueryInformationProcess函数。 75D131D1 | FF15 F0A2D375            | call dword ptr ds:[<NtQueryInformationP |
// 查询了某个进程的ProcessDebugPort，这个值是系统用来与调试器通信的端口句柄。
#include <Windows.h>
#include <stdio.h>

int main()
{
    BOOL isDebuggerPresent = FALSE;
    DWORD processId = GetCurrentProcessId();
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

    if (processHandle == NULL) {
	   printf("Failed to open current process.\n");
    }

    BOOL result = CheckRemoteDebuggerPresent(processHandle, &isDebuggerPresent);
    if (result)
    {
	   if (isDebuggerPresent)
	   {
		  printf("Remote debugger is present.\n");
	   }
	   else
	   {
		  printf("Remote debugger is not present.\n");
	   }
    }
    else
    {
	   printf("Failed to check remote debugger presence.\n");
    }

    CloseHandle(processHandle);

    return 0;
}