/*
 *  MinHook - The Minimalistic API Hooking Library for x64/x86
 *  Copyright (C) 2009-2017 Tsuda Kageyu.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
 *  OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if !(defined _M_IX86) && !(defined _M_X64) && !(defined __i386__) && !(defined __x86_64__)
    #error MinHook supports only x86 and x64 systems.
#endif

#include <windows.h>

// MinHook Error Codes.
typedef enum MH_STATUS
{
    // Unknown error. Should not be returned.
    MH_UNKNOWN = -1,

    // Successful.
    MH_OK = 0,

    // MinHook is already initialized.
    MH_ERROR_ALREADY_INITIALIZED,

    // MinHook is not initialized yet, or already uninitialized.
    MH_ERROR_NOT_INITIALIZED,

    // The hook for the specified target function is already created.
    MH_ERROR_ALREADY_CREATED,

    // The hook for the specified target function is not created yet.
    MH_ERROR_NOT_CREATED,

    // The hook for the specified target function is already enabled.
    MH_ERROR_ENABLED,

    // The hook for the specified target function is not enabled yet, or already
    // disabled.
    MH_ERROR_DISABLED,

    // The specified pointer is invalid. It points the address of non-allocated
    // and/or non-executable region.
    MH_ERROR_NOT_EXECUTABLE,

    // The specified target function cannot be hooked.
    MH_ERROR_UNSUPPORTED_FUNCTION,

    // Failed to allocate memory.
    MH_ERROR_MEMORY_ALLOC,

    // Failed to change the memory protection.
    MH_ERROR_MEMORY_PROTECT,

    // The specified module is not loaded.
    MH_ERROR_MODULE_NOT_FOUND,

    // The specified function is not found.
    MH_ERROR_FUNCTION_NOT_FOUND
}
MH_STATUS;

// Can be passed as a parameter to MH_EnableHook, MH_DisableHook,
// MH_QueueEnableHook or MH_QueueDisableHook.
#define MH_ALL_HOOKS NULL

#ifdef __cplusplus
extern "C" {
#endif

    // Initialize the MinHook library. You must call this function EXACTLY ONCE
    // at the beginning of your program.
    MH_STATUS WINAPI MH_Initialize(VOID);

    // 解除初始化 MinHook 库。你必须在程序的末尾调用此函数，且只能调用一次。
    MH_STATUS WINAPI MH_Uninitialize(VOID);

    // 创建一个针对指定目标函数的钩子，默认处于禁用状态。
    // 参数:
    // pTarget    [in] 指向目标函数的指针，该函数将被绕过函数覆盖。
    // pDetour    [in] 指向绕过函数的指针，该函数将覆盖目标函数。
    // ppOriginal [out] 指向蹦床函数的指针，该函数将用于调用原始目标函数。
    //                  该参数可以为 NULL。
    MH_STATUS WINAPI MH_CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID *ppOriginal);

    // 创建一个针对指定 API 函数的钩子，默认处于禁用状态。
    // 参数:
    // pszModule  [in] 指向包含目标函数的已加载模块名称的指针。
    // pszProcname [in] 指向目标函数名称的指针，该函数将被绕过函数覆盖。
    // pDetour    [in] 指向绕过函数的指针，该函数将覆盖目标函数。
    // ppOriginal [out] 指向蹦床函数的指针，该函数将用于调用原始目标函数。
    //                  该参数可以为 NULL。
    MH_STATUS WINAPI MH_CreateHookApi(
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal);

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
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal, LPVOID *ppTarget);

    // 移除已创建的钩子。
    // 参数:
    // pTarget [in] 指向目标函数的指针。
    MH_STATUS WINAPI MH_RemoveHook(LPVOID pTarget);

    // 启用已创建的钩子。
    // 参数:
    // pTarget [in] 指向目标函数的指针。
    //        如果该参数为 MH_ALL_HOOKS，则所有已创建的钩子将一并启用。
    MH_STATUS WINAPI MH_EnableHook(LPVOID pTarget);

    // 禁用已创建的钩子。
    // 参数:
    // pTarget [in] 指向目标函数的指针。
    //        如果该参数为 MH_ALL_HOOKS，则所有已创建的钩子将一并禁用。
    MH_STATUS WINAPI MH_DisableHook(LPVOID pTarget);

    // 将已创建的钩子排队以后用。
    // 参数:
    // pTarget [in] 指向目标函数的指针。
    //        如果该参数为 MH_ALL_HOOKS，则所有已创建的钩子将排队启用。
    MH_STATUS WINAPI MH_QueueEnableHook(LPVOID pTarget);

    // 将已创建的钩子排队以禁用。
    // 参数:
    // pTarget [in] 指向目标函数的指针。
    //        如果该参数为 MH_ALL_HOOKS，则所有已创建的钩子将排队禁用。
    MH_STATUS WINAPI MH_QueueDisableHook(LPVOID pTarget);

    // 一次性应用所有排队的更改。
    MH_STATUS WINAPI MH_ApplyQueued(VOID);

    // 将 MH_STATUS 转换为其字符串形式的名称。
    const char *WINAPI MH_StatusToString(MH_STATUS status);

#ifdef __cplusplus
}
#endif
