#include <windows.h>
#include <tlhelp32.h>  // ���ͷ�ļ���ʹ�ý��̿��չ���

void TerminateProcessTree(DWORD dwProcessId)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(hSnapShot, &pe))
	{
		do
		{
			if (pe.th32ParentProcessID == dwProcessId)
			{
				HANDLE hChildProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
				if (hChildProcess)
				{
					TerminateProcessTree(pe.th32ProcessID); // �ݹ���ֹ�ӽ���
					TerminateProcess(hChildProcess, 0);
					CloseHandle(hChildProcess);
				}
			}
		} while (Process32Next(hSnapShot, &pe));
	}
	CloseHandle(hSnapShot);
}
