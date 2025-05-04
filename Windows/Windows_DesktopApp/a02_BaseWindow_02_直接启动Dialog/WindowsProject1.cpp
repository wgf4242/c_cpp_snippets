#include <windows.h>
#include "Resource.h"

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