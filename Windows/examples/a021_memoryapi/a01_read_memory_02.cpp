/*
1. 先打开记事本, 本程序会修改记事本的内存
2. 设置targetAddr 要确认为可读地址, 32位程序不可读64位程序, 读取的内容会写到记事本中
*/

#include "pch.h"
#include <windows.h>
#include <tlhelp32.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996) 

// 要读取的内存地址, 确认地址可读
LPCVOID targetAddr = (LPCVOID)0x2E8A9BE2010;

BOOL CALLBACK EnumChildWindowProc(HWND hWnd, LPARAM lParam);//枚举记事本中的子窗口
char mess[999999];
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HWND nphWnd = ::FindWindow("notepad", NULL);
	if (nphWnd)
	{
		char temp[1024];
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof(pe32);
		HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//获得进程列表的快照，第一个参数可以有其他选项，详细请参考MSDN
		if (hProcessSnap == INVALID_HANDLE_VALUE)
		{
			::MessageBox(NULL, "CreateToolhelp32Snapshot error", "error", MB_OK);
			return 0;
		}
		HANDLE hProcess;
		BOOL bMore = ::Process32First(hProcessSnap, &pe32);//获得第一个进程的信息
		while (bMore)
		{
			::wsprintf(temp, "%s", pe32.szExeFile);
			if (!::strcmp(temp, "notepad.exe"))
			{
				hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, false, (DWORD)pe32.th32ProcessID);
				if (hProcess == NULL)
				{
					::wsprintf(temp, "%s", "打开进程失败!");
					::strcat(mess, temp);
				}
				else
				{
					::wsprintf(temp, "%s", "打开进程成功!");
					::strcat(mess, temp);
					//读取内存中内容
					int tmp;
					SIZE_T dwNumberOfBytesRead; // 修改类型为 SIZE_T
					
					if (!::ReadProcessMemory(hProcess, targetAddr, &tmp, 4, &dwNumberOfBytesRead))
					{
						DWORD errorCode = ::GetLastError(); // 获取错误代码
						::wsprintf(temp, "读取失败, 错误代码: %lu", errorCode); // 添加错误代码到信息中
						::strcat(mess, temp);
					}
					else
					{
						::wsprintf(temp, "%x", tmp);
						::strcat(mess, temp);
					}
				}
				break;
			}
			bMore = ::Process32Next(hProcessSnap, &pe32);//获得其他进程信息
		}
		::EnumChildWindows(nphWnd, EnumChildWindowProc, 0);//获得记事本的edit窗口，打印进程信息
		return 0;
	}
	else
	{
		::MessageBox(NULL, "please open notepad", "error", MB_OK);
		return 0;
	}
}
BOOL CALLBACK EnumChildWindowProc(HWND hWnd, LPARAM lParam)
{
	char temp1[256];
	if (hWnd)
	{
		::GetClassName(hWnd, temp1, 255);
		if (!::strcmp(temp1, "Edit"))//得到edit子窗口句柄
		{
			::SendMessage(hWnd, WM_SETTEXT, 0, (LPARAM)mess);
			return 0;
		}
	}
	return true;
}