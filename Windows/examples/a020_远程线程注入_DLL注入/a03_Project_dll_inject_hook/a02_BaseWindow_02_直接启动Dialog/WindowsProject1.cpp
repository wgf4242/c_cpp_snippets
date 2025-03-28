#include <windows.h>
#include "Resource.h"
#include "run.h"
#include "server.h" // 确保包含 server.h

// 添加一个全局变量来存储窗口句柄
HWND g_hWnd = NULL;

// 更新界面的函数
void UpdateUIImpl(const char* message) { // 重命名为 UpdateUIImpl
    if (g_hWnd) {
        // 假设有一个文本框控件用于显示信息，ID为IDC_TEXTBOX
        SetDlgItemTextA(g_hWnd, IDC_TEXTBOX, message);
    }
}

DWORD WINAPI ServerThread(LPVOID lpParam) {
    StartServer();
    return 0;
}

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
        g_hWnd = hwnd; // 保存窗口句柄
        //UpdateUI = UpdateUIImpl; // 初始化 UpdateUI 函数指针
        // 在对话框初始化时启动服务器线程
        CreateThread(NULL, 0, ServerThread, NULL, 0, NULL);
        break;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDC_Inject)
        {
            OutputDebugStringA("Button2 Clicked\n");
            runproc();
        }
        break;
    }
    case WM_CLOSE:
    {
        TerminateProcessTree(GetCurrentProcessId()); // 终止进程树
        DestroyWindow(hwnd);        //销毁窗口
        PostQuitMessage(NULL);      //传递退出消息
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