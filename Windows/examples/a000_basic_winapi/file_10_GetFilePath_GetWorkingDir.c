#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    char szPath[MAX_PATH];

    // 获取当前可执行文件的完整路径
    if (GetModuleFileNameA(NULL, szPath, MAX_PATH)) {
        printf("当前程序路径: %s\n", szPath);

        // 获取程序所在目录（去掉文件名）
        for (int i = strlen(szPath) - 1; i >= 0; i--) {
            if (szPath[i] == '\\') {
                szPath[i] = '\0';
                break;
            }
        }
        printf("程序所在目录: %s\n", szPath);
    }
    else {
        printf("获取路径失败，错误代码: %d\n", GetLastError());
    }

    char szCurrentDir[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, szCurrentDir);
    printf("当前工作目录: %s\n", szCurrentDir);
    // strcat_s(fullDllPath, MAX_PATH, "\\test_dll.dll");

    return 0;
}
//当前程序路径: F:\test_file01\x64\Debug\test_file01.exe
//程序所在目录: F:\test_file01\x64\Debug
//当前工作目录: F:\test_file01
