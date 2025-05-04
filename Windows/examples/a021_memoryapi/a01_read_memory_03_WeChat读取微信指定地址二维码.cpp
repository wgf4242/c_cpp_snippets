// WindowsProject1.cpp : 定义应用程序的入口点。
// 注意x64只能读取x64

#include "framework.h"
#include "WindowsProject1.h"

#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <string>
#include <tlhelp32.h>
#include <psapi.h>
#pragma comment(lib, "Psapi.lib")

using namespace Gdiplus;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
HWND g_hStaticImage = NULL;                     // 图片控件句柄
HWND g_hEditPath = NULL;                        // 编辑框句柄
Image* g_pImage = NULL;                         // 当前加载的图片

// 此代码模块中包含的函数的前向声明:
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                LoadAndDisplayImage(HWND hWnd);
void                CleanupImage();
void                LoadImageFromMemory(HWND hWnd);
void OutputLoadedDllBaseAddresses(HWND hWnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // 初始化GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    hInst = hInstance; // 保存实例句柄

    // 直接显示About对话框
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), NULL, About);

    // 清理GDI+资源
    CleanupImage();
    GdiplusShutdown(gdiplusToken);

    return 0;
}

// 清理图片资源
void CleanupImage()
{
    if (g_pImage)
    {
        delete g_pImage;
        g_pImage = NULL;
    }
}

// 加载并显示图片
void LoadAndDisplayImage(HWND hWnd)
{
    // 获取编辑框中的文本
    WCHAR szPath[MAX_PATH] = { 0 };
    GetWindowText(g_hEditPath, szPath, MAX_PATH);

    // 清理之前的图片
    CleanupImage();

    // 加载新图片
    g_pImage = new Image(szPath);
    
    if (g_pImage && g_pImage->GetLastStatus() == Ok)
    {
        // 图片加载成功，强制重绘整个对话框
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }
    else
    {
        // 图片加载失败
        MessageBox(hWnd, L"无法加载图片，请检查路径是否正确。", L"错误", MB_OK | MB_ICONERROR);
        delete g_pImage;
        g_pImage = NULL;
    }
}

// 从内存加载图片
// 移除重复的 LoadImageFromMemory 函数定义
// 保留一个完整的 LoadImageFromMemory 函数实现
void LoadImageFromMemory(HWND hWnd)
{
    // 调用 OutputLoadedDllBaseAddresses 函数
    OutputLoadedDllBaseAddresses(hWnd);

    // 获取编辑框中的16进制字符串
    WCHAR szHexAddress[MAX_PATH] = { 0 };
    GetWindowText(GetDlgItem(hWnd, IDC_EDIT2_MEM), szHexAddress, MAX_PATH);

    // 将16进制字符串转换为内存地址
    unsigned long addr1 = 0;
    unsigned long ptrAddr1 = 0;
    swscanf_s(szHexAddress, L"%lx", &ptrAddr1);

    // 获取Wechat.exe的进程ID
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe))
        {
            do
            {
                if (_wcsicmp(pe.szExeFile, L"Wechat.exe") == 0)
                {
                    processID = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
    }

    if (processID == 0)
    {
        MessageBox(hWnd, L"无法找到 Wechat.exe 进程。", L"错误", MB_OK | MB_ICONERROR);
        return;
    }

    // 打开Wechat.exe进程
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL)
    {
        MessageBox(hWnd, L"无法打开 Wechat.exe 进程。", L"错误", MB_OK | MB_ICONERROR);
        return;
    }

    // 从目标进程读取 ptrAddr1 保存的地址值
    if (!ReadProcessMemory(hProcess, (LPCVOID)ptrAddr1, &addr1, sizeof(addr1), NULL))
    {
        DWORD error = GetLastError();
        WCHAR errorMsg[256];
        swprintf_s(errorMsg, L"无法读取地址值。错误代码: %lu", error);
        MessageBox(hWnd, errorMsg, L"错误", MB_OK | MB_ICONERROR);
        CloseHandle(hProcess);
        return;
    }

    // 将 addr1 的值显示到 IDC_EDIT3_ADDR
    WCHAR szAddr1[32];
    swprintf_s(szAddr1, L"%08X", addr1);
    SetWindowText(GetDlgItem(hWnd, IDC_EDIT3_ADDR), szAddr1);

    // 设置 IDC_STATIC3 的显示文字为 "指向"
    SetWindowText(GetDlgItem(hWnd, IDC_STATIC3), L"指向");

    // 初始缓冲区大小
    SIZE_T bufferSize = 0xE90; // 1KB
    BYTE* pImageData = new BYTE[bufferSize];
    SIZE_T bytesRead;

    // 读取 addr1 中的数据数量
    if (!ReadProcessMemory(hProcess, (LPCVOID)addr1, pImageData, bufferSize, &bytesRead))
    {
        DWORD error = GetLastError();
        WCHAR errorMsg[256];
        swprintf_s(errorMsg, L"无法读取内存地址。错误代码: %lu", error);
        MessageBox(hWnd, errorMsg, L"错误", MB_OK | MB_ICONERROR);
        CloseHandle(hProcess);
        delete[] pImageData;
        return;
    }

    // 如果需要，可以在这里动态调整缓冲区大小并继续读取

    // 使用GDI+从内存加载图片
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, bytesRead);
    if (hMem)
    {
        void* pMem = GlobalLock(hMem);
        memcpy(pMem, pImageData, bytesRead);
        IStream* pStream = nullptr;
        if (CreateStreamOnHGlobal(hMem, TRUE, &pStream) == S_OK)
        {
            CleanupImage(); // 清理之前的图片
            g_pImage = new Image(pStream);
            pStream->Release();
        }
        GlobalUnlock(hMem);
        GlobalFree(hMem);
    }

    CloseHandle(hProcess);
    delete[] pImageData;

    if (g_pImage && g_pImage->GetLastStatus() == Ok)
    {
        // 图片加载成功，强制重绘整个对话框
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);
    }
    else
    {
        MessageBox(hWnd, L"无法从内存加载图片。", L"错误", MB_OK | MB_ICONERROR);
        delete g_pImage;
        g_pImage = NULL;
    }
}

// "关于"框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        // 保存控件句柄
        g_hEditPath = GetDlgItem(hDlg, IDC_EDIT1);
        g_hStaticImage = GetDlgItem(hDlg, IDC_STATIC);
        
        // 设置编辑框默认值
        SetWindowText(g_hEditPath, L"输入文件路径");
        SetWindowText(GetDlgItem(hDlg, IDC_EDIT2_MEM), L"内存地址");
        SetWindowText(GetDlgItem(hDlg, IDC_STATIC2_SIZE), L"大小");
        
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            PostQuitMessage(0); // 关闭对话框时退出应用程序
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_BUTTON1)
        {
            // 处理按钮点击事件
            LoadAndDisplayImage(hDlg);
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_BUTTON2_MEM)
        {
            // 处理从内存加载图片的按钮点击事件
            LoadImageFromMemory(hDlg);
            return (INT_PTR)TRUE;
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hDlg, &ps);
            
            if (g_pImage && g_hStaticImage)
            {
                // 获取静态控件的位置和大小
                RECT rcStatic;
                GetWindowRect(g_hStaticImage, &rcStatic);
                POINT ptTopLeft = { rcStatic.left, rcStatic.top };
                ScreenToClient(hDlg, &ptTopLeft);
                
                int staticWidth = rcStatic.right - rcStatic.left;
                int staticHeight = rcStatic.bottom - rcStatic.top;
                
                // 创建GDI+绘图对象
                Graphics graphics(hdc);
                
                // 计算图片的缩放比例，保持宽高比
                UINT imgWidth = g_pImage->GetWidth();
                UINT imgHeight = g_pImage->GetHeight();
                
                float scaleX = (float)staticWidth / imgWidth;
                float scaleY = (float)staticHeight / imgHeight;
                float scale = min(scaleX, scaleY);
                
                // 计算居中显示的位置
                int destWidth = (int)(imgWidth * scale);
                int destHeight = (int)(imgHeight * scale);
                int destX = ptTopLeft.x + (staticWidth - destWidth) / 2;
                int destY = ptTopLeft.y + (staticHeight - destHeight) / 2;
                
                // 绘制图片
                graphics.DrawImage(g_pImage, destX, destY, destWidth, destHeight);
            }
            
            EndPaint(hDlg, &ps);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void OutputLoadedDllBaseAddresses(HWND hWnd)
{
    // 获取Wechat.exe的进程ID
    DWORD processID = 0;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hSnapshot, &pe))
        {
            do
            {
                if (_wcsicmp(pe.szExeFile, L"Wechat.exe") == 0)
                {
                    processID = pe.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnapshot, &pe));
        }
        CloseHandle(hSnapshot);
    }

    if (processID == 0)
    {
        MessageBox(hWnd, L"无法找到 Wechat.exe 进程。", L"错误", MB_OK | MB_ICONERROR);
        return;
    }

    // 打开Wechat.exe进程
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (hProcess == NULL)
    {
        MessageBox(hWnd, L"无法打开 Wechat.exe 进程。", L"错误", MB_OK | MB_ICONERROR);
        return;
    }

    // 枚举进程的模块
    HMODULE hMods[1024];
    DWORD cbNeeded;
    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            MODULEINFO modInfo;
            if (GetModuleInformation(hProcess, hMods[i], &modInfo, sizeof(modInfo)))
            {
                WCHAR szModName[MAX_PATH];
                if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(WCHAR)))
                {
                    WCHAR debugMsg[512];
                    swprintf_s(debugMsg, L"Module: %s, Base Address: 0x%p\n", szModName, modInfo.lpBaseOfDll);
                    OutputDebugString(debugMsg);
                }
            }
        }
    }

    CloseHandle(hProcess);
}