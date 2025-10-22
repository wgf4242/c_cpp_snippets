
## Foundation/LP

| 类型名       | 含义                                        | 等价于（现代 C/C++）    |
| --------- | ----------------------------------------- | ---------------- |
| `LP`      | Long Pointer                              |                  |
| `LPVOID`  | Long Pointer to VOID                      | `void*`          |
| `LPSTR`   | Long Pointer to STRing                    | `char*`          |
| `LPCSTR`  | Long Pointer to Const STRing              | `const char*`    |
| `LPWSTR`  | Long Pointer to Wide STRing               | `wchar_t*`       |
| `LPCWSTR` | Long Pointer to Const Wide STRing         | `const wchar_t*` |
| `LPTSTR`  | 根据是否定义 UNICODE 宏，可能是 `char*` 或 `wchar_t*` |                  |
| `LPCTSTR` | 同上，但为 `const`                             | `const TCHAR*`   |

## [MessageBoxW](https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-messageboxw)

MessageBoxW(hWndParent, v29, v28, 0x30);
0x30 警告图标
0x40 小写 _i_ 图标。

## File/ReadFile/CreateFileA

```c
BOOL (__stdcall *ReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead
    , LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)

HANDLE (__stdcall *CreateFileA)(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode
    , LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition
    , DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
```

