#include <windows.h>
#include <stdio.h>

void main() {
    HKEY hKey;
    char SubKeyName[] = "SOFTWARE\\Microsoft\\Internet Explorer\\Security";
    char ValueName[] = "BlockXBM";

    BYTE ValueData[64];
    DWORD Buffer;

    //打开
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SubKeyName, 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
        printf("Error: Regedit cannot be opened!");
    } else {
        //读原来的键值
        Buffer = sizeof(ValueData);
        if (RegQueryValueEx(hKey, ValueName, 0, NULL, ValueData, &Buffer) != ERROR_SUCCESS) {
            //不存在
            //新建一个值为0的DWORD
            DWORD temp = 0;
            if (RegSetValueEx(hKey, ValueName, 0, REG_DWORD, (LPBYTE) &temp, sizeof(DWORD)) != ERROR_SUCCESS) {
                printf("Error: Create Value failed");
            }
            RegCloseKey(hKey);
        } else {
            //存在
            //改变值
            DWORD temp = 0;
            if (RegSetValueEx(hKey, ValueName, 0, REG_DWORD, (LPBYTE) &temp, sizeof(DWORD)) != ERROR_SUCCESS) {
                printf("Error: Change Value failed");
                RegCloseKey(hKey);
            }
        }
    }
}
