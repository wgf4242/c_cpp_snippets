
#include <windows.h>
#include <stdio.h>

void add_to_startup(const char *appname, const char *path) {
    HKEY hKey;
    LONG result;

    result = RegOpenKeyEx(HKEY_CURRENT_USER,
                          "Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                          0, KEY_SET_VALUE, &hKey);

    if (result != ERROR_SUCCESS) {
        return;
    }

    result = RegSetValueEx(hKey, appname, 0, REG_SZ, (BYTE *)path, strlen(path) + 1);

    RegCloseKey(hKey);
}

int main(int argc, char *argv[]) {
    char path[MAX_PATH];
    if (GetModuleFileName(NULL, path, MAX_PATH) == 0) {
        return 1;
    }
    add_to_startup("MyAppName", path);
}