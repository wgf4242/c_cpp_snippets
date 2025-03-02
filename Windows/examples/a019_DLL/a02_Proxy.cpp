#include "pch.h"

extern "C" __declspec(dllexport) VOID CALLBACK ShowMessageBox(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	MessageBox(hwnd, L"Function Called!", L"Test", MB_OK);
}

BOOL WINAPI DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// rundll32.exe Dll1.dll,ShowMessageBox
		//rundll32.exe Dll1.dll,DllMain
		MessageBox(NULL, L"Dll Proxying!", L"Test", MB_OK);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}