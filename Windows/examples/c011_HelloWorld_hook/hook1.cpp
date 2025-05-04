// 实现 调用HelloWorld3.exe的消息框
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

DWORD FindProcessId(const std::wstring& processName) {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processSnapshot);
	return 0;
}

int main()
{
	const std::wstring processName = L"HelloWorld3.exe";
	DWORD processId = FindProcessId(processName);

	if (processId == 0)
	{
		std::cout << "Process not found. Make sure your process is running and the name is correct.\n";
		return 0;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (hProcess == NULL)
	{
		std::cout << "Could not open the process. Make sure you have the required permissions.\n";
		return 0;
	}

	void* pAllocatedMem = VirtualAllocEx(hProcess, NULL, 512, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (pAllocatedMem == NULL)
	{
		std::cout << "Memory allocation failed.\n";
		return 0;
	}

	// You can change the following machine codes to whatever you want to inject
	unsigned char machineCodes[] = { 
		0x55, // push ebp
		0x6A, 0x00, 0x68, 0x40, 0x7B, 0x41, 0x00, 0x68, 0x70, 0x7B, 0x41, 0x00, 0x6A, 0x00, 0xFF, 0x15, 0x9C, 0xB0, 0x41, 0x00, // shellcode
		0x5d,0xc3 // pop ebp, ret

	};
	BOOL result = WriteProcessMemory(hProcess, pAllocatedMem, machineCodes, sizeof(machineCodes), NULL);
	if (!result)
	{
		std::cout << "Failed to inject machine codes.\n";
		return 0;
	}

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pAllocatedMem, NULL, 0, NULL);
	if (hThread == NULL)
	{
		std::cout << "Failed to create a remote thread.\n";
		return 0;
	}

	CloseHandle(hProcess);

	return 0;
}