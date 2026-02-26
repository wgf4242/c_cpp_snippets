#include <windows.h>
#include <stdio.h>

struct ustring {
    DWORD Length;
    DWORD MaximumLength;
    PUCHAR Buffer;
};

// 这里的函数名可以是任意的，但地址必须指向 SystemFunction033
typedef NTSTATUS(WINAPI* _RC4)(struct ustring* data, struct ustring* key);

void rc4_crypt(unsigned char* data, DWORD dataLen, char* keyStr) {
    // 1. 获取动态链接库句柄并查找函数
    HMODULE hAdvapi = LoadLibraryA("advapi32.dll");
    _RC4 SystemFunction033 = (_RC4)GetProcAddress(hAdvapi, "SystemFunction033");

    // 2. 构造 ustring 结构体
    DWORD keyLen = (DWORD)strlen(keyStr);
    struct ustring _data = { dataLen, dataLen, data };
    struct ustring _key = { keyLen, keyLen, (PUCHAR)keyStr };

    // 3. 执行加密/解密
    SystemFunction033(&_data, &_key);
}

int main() {
    // 测试数据：flag
    unsigned char buf[] = "flag";
    char myKey[] = "12345678";

    // 加密 (注意：buf 的长度不包含末尾的 \0，所以用 4 而不是 sizeof)
    rc4_crypt(buf, 4, myKey);

    // 输出结果
    printf("Output Hex: ");
    for (int i = 0; i < 4; i++) {
        printf("%02x", buf[i]);
    } // dd9f58b3

    rc4_crypt(buf, 4, myKey);
    printf("\nOutput String: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", buf[i]);
    } // flag
    return 0;
}