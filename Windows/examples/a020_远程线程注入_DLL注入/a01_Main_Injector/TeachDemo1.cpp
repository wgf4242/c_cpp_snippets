// 配置属性 - 字符集- 未设置 会自动选择

#include "pch.h"
#include "resource.h"
#include "TeachDemo1.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

#define WECHAT_PROCESS_NAME "WeChat.exe"

INT_PTR CALLBACK DialogProc(_In_ HWND   hwndDlg, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
VOID InjectDll();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN), NULL, &DialogProc);
	return 0;
}

INT_PTR CALLBACK DialogProc(_In_ HWND   hwndDlg, _In_ UINT   uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG) {
		//MessageBox(NULL, "首次加载", "标题", 0);
	}

	if (uMsg == WM_CLOSE) {
		//MessageBox(NULL, "你点击了关闭", "标题", 0);
		EndDialog(hwndDlg, 0);
	}

	if (uMsg == WM_COMMAND) {
		if (wParam == INJECT_DLL) {
			InjectDll();
		}
		if (wParam == UN_DLL) {

		}
	}

	return FALSE;
}

//第一步 我们要拿到微信的进程句柄（有了句柄才能去操作微信的内存）
//通过微信的进程名称去找到微信pid
DWORD ProcessNameFindPID(LPCSTR ProcessName)
{
	//#include <TlHelp32.h>
	//第一步获取到整个系统的进程快照
	HANDLE ProcessAll = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);//获取整个系统的进程快照
	//第二步然后在快照里面对比ProcessName进程名称
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	do
	{
		// WeChat.exe
		//th32ProcessID 进程id  szExeFile进程名称

		if (strcmp(ProcessName, processInfo.szExeFile) == 0) {
			return processInfo.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &processInfo));
	//第三步 用找到的pid去打开进程获取到句柄
}


//第二步 我们要在微信内部申请一块内存用来放 dll的路径, 然后通过pid去打开微信进程获取到进程句柄
VOID InjectDll()
{
	CHAR pathStr[0x100] = { "D://temp//cprojects//a01_LoadDll//x64//Debug//example.dll" };
	//第一步我们先获取到微信的句柄
	DWORD PID = ProcessNameFindPID(WECHAT_PROCESS_NAME);

	if (PID == 0) {
		MessageBox(NULL, "没有找到微信进程或者微信没有启动", "错误", 0);
		return;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (NULL == hProcess) {
		MessageBox(NULL, "进程打开失败，可能权限不足或者关闭了应用", "错误", 0);
		return;
	}

	//第二步申请内存
	LPVOID dllAdd = VirtualAllocEx(hProcess, NULL, strlen(pathStr), MEM_COMMIT, PAGE_READWRITE);
	if (NULL == dllAdd) {
		MessageBox(NULL, "内存分配失败", "错误", 0);
		return;
	}

	//第三步写入dll路径到这个地址上面去
	if (WriteProcessMemory(hProcess, dllAdd, pathStr, strlen(pathStr), NULL) == 0) {
		MessageBox(NULL, "路径写入失败", "错误", 0);
		return;
	}
	CHAR test[0x100] = { 0 };
	sprintf_s(test, "写入的地址为：%p", dllAdd);
	OutputDebugString(test);

	HMODULE k32 = GetModuleHandle("Kernel32.dll");
	LPVOID loadAdd = GetProcAddress(k32, "LoadLibraryA");
	//LoadLibraryW(test.dll);
	CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAdd, dllAdd, 0, NULL);
}

//FreeLibrary() 卸载用到的函数 原理和上面是一样的! 作业
// 
//第三步 我们要写入dll路径 然后通过线程执行函数 去执行 loadLiaray 这个函数来加载我们写入路径的那个dll
