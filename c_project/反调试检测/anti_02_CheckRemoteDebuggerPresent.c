// https://mp.weixin.qq.com/s/KPOt_ezHVwSNPlyblLByXQ
// CheckRemoteDebuggerPresent ��������̽����������Ƿ񱻵��ԣ�Ҳ����̽��ϵͳ���������Ƿ񱻵��ԡ��������������������̾����һ��ָ�򲼶�ֵ��ָ�롣���ָ���Ľ������ڱ����ԣ��������ָ�򲼶�ֵ��ָ����Ϊ TRUE��������ΪFALSE��
// ��xdbg��Ctrl+G����CheckRemoteDebuggerPresent�������ҵ��ú����Ļ����롣 ��17�е�����NtQueryInformationProcess������ 75D131D1 | FF15 F0A2D375            | call dword ptr ds:[<NtQueryInformationP |
// ��ѯ��ĳ�����̵�ProcessDebugPort�����ֵ��ϵͳ�����������ͨ�ŵĶ˿ھ����
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