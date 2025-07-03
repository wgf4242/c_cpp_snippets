
1. 加载Minhook src
Minhook项目的 include,src解压到 minhook目录
新建文件夹: 右击工程 - 添加 - 筛选器, minhook, 将include,src拖进来


# Minhook Header

```c
// 解除初始化 MinHook 库。你必须在程序的末尾调用此函数，且只能调用一次。
MH_STATUS WINAPI MH_Uninitialize(VOID);

// 创建一个针对指定目标函数的钩子，默认处于禁用状态。
// 参数:
// pTarget    [in] 指向目标函数的指针，该函数将被绕过函数覆盖。
// pDetour    [in] 指向绕过函数的指针，该函数将覆盖目标函数。
// ppOriginal [out] 指向蹦床函数的指针，该函数将用于调用原始目标函数。
//                  该参数可以为 NULL。
MH_STATUS WINAPI MH_CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID* ppOriginal);

// 创建一个针对指定 API 函数的钩子，默认处于禁用状态。
// 参数:
// pszModule  [in] 指向包含目标函数的已加载模块名称的指针。
// pszProcname [in] 指向目标函数名称的指针，该函数将被绕过函数覆盖。
// pDetour    [in] 指向绕过函数的指针，该函数将覆盖目标函数。
// ppOriginal [out] 指向蹦床函数的指针，该函数将用于调用原始目标函数。
//                  该参数可以为 NULL。
MH_STATUS WINAPI MH_CreateHookApi(
    LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal);

// 创建一个针对指定 API 函数的钩子，默认处于禁用状态。
// 参数:
// pszModule  [in] 指向包含目标函数的已加载模块名称的指针。
// pszProcname [in] 指向目标函数名称的指针，该函数将被绕过函数覆盖。
// pDetour    [in] 指向绕过函数的指针，该函数将覆盖目标函数。
// ppOriginal [out] 指向蹦床函数的指针，该函数将用于调用原始目标函数。
//                  该参数可以为 NULL。
// ppTarget   [out] 指向目标函数的指针，可与其他函数一起使用。
//                  该参数可以为 NULL。
MH_STATUS WINAPI MH_CreateHookApiEx(
    LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID* ppOriginal, LPVOID* ppTarget);
```