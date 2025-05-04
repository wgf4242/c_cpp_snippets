// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

#include <windows.h>
#include <stdio.h>

void InstallHook() {
	printf("Hook Installed\n");
}

void RemoveHook() {
	printf("Hook Removed\n");
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InstallHook();
		break;
	case DLL_PROCESS_DETACH:
		RemoveHook();
		break;
	}
	return TRUE;
}