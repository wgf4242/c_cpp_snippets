#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include "Resource.h"
#include <string>

int g_counter = 0;

INT_PTR CALLBACK Dlgproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{

		break;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			// 获取按钮文本
			char buffer[256];
			//GetDlgItemTextA(hwnd, IDC_BUTTON1, buffer, sizeof(buffer));
			// 将文本转换为整数
			//int number = atoi(buffer);

			// 数字加1
			//number += 1;

			// 将新数字转换为字符串

			g_counter++;
			sprintf(buffer, "%d", g_counter);

			// 更新按钮文本
			SetDlgItemTextA(hwnd, IDC_BUTTON1, buffer);

			OutputDebugStringA("A01 random data Button1 Clicked\n");
		}
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);		//销毁窗口
		PostQuitMessage(NULL);		//传递退出消息
		break;
	}
	default:
		return FALSE;
		break;
	}
	return TRUE;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	// 创建模态对话框窗口
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, Dlgproc);

	return 0;
}