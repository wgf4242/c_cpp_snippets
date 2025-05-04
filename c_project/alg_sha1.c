// 需要32位编译, 不会就用 Visual Studio
#include <string.h>
#include "stdio.h"

#include <windows.h>
typedef unsigned char _BYTE;

HMODULE __cdecl sha1(int sha_fn, int code_1, int size) {
    HMODULE result;
    FARPROC sha_update;
    HMODULE temp_var;
    char buffer[260];
    HMODULE module_handle;
    FARPROC sha_init;

    memset(buffer, 0, 256);
    result = LoadLibraryA("advapi32.dll");
    module_handle = result;
    if (result) {
        sha_init = GetProcAddress(module_handle, "A_SHAInit");
        sha_update = GetProcAddress(module_handle, "A_SHAUpdate");
        result = (HMODULE)GetProcAddress(module_handle, "A_SHAFinal");
        temp_var = result;
        if (sha_init) {
            if (sha_update) {
                if (result) {
                    ((void(__stdcall*)(char*)) sha_init)(buffer);
                    ((void(__stdcall*)(char*, int, int)) sha_update)(buffer, code_1, size);
                    return (HMODULE)((int(__stdcall*)(char*, int)) temp_var)(buffer, sha_fn);
                }
            }
        }
    }
    return result;
}


int main(int argc, char* argv[], char** env) {
    // setbuf(stdout, NULL);
    char sha[20];
    memset(sha, 0, sizeof(sha));

    char code1[6] = "123456";

    int size = 6;
    // 输入 code1, 输出 sha, 取size个字节
    sha1((int)sha, (int)code1, size);
    // sha: 7c4a8d09ca3762af61e59520943dc26494f8941b
    return 0;
}