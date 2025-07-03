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

    // �����ʼ�� MinHook �⡣������ڳ����ĩβ���ô˺�������ֻ�ܵ���һ�Ρ�
    MH_STATUS WINAPI MH_Uninitialize(VOID);

    // ����һ�����ָ��Ŀ�꺯���Ĺ��ӣ�Ĭ�ϴ��ڽ���״̬��
    // ����:
    // pTarget    [in] ָ��Ŀ�꺯����ָ�룬�ú��������ƹ��������ǡ�
    // pDetour    [in] ָ���ƹ�������ָ�룬�ú���������Ŀ�꺯����
    // ppOriginal [out] ָ��Ĵ�������ָ�룬�ú��������ڵ���ԭʼĿ�꺯����
    //                  �ò�������Ϊ NULL��
    MH_STATUS WINAPI MH_CreateHook(LPVOID pTarget, LPVOID pDetour, LPVOID *ppOriginal);

    // ����һ�����ָ�� API �����Ĺ��ӣ�Ĭ�ϴ��ڽ���״̬��
    // ����:
    // pszModule  [in] ָ�����Ŀ�꺯�����Ѽ���ģ�����Ƶ�ָ�롣
    // pszProcname [in] ָ��Ŀ�꺯�����Ƶ�ָ�룬�ú��������ƹ��������ǡ�
    // pDetour    [in] ָ���ƹ�������ָ�룬�ú���������Ŀ�꺯����
    // ppOriginal [out] ָ��Ĵ�������ָ�룬�ú��������ڵ���ԭʼĿ�꺯����
    //                  �ò�������Ϊ NULL��
    MH_STATUS WINAPI MH_CreateHookApi(
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal);

    // ����һ�����ָ�� API �����Ĺ��ӣ�Ĭ�ϴ��ڽ���״̬��
    // ����:
    // pszModule  [in] ָ�����Ŀ�꺯�����Ѽ���ģ�����Ƶ�ָ�롣
    // pszProcname [in] ָ��Ŀ�꺯�����Ƶ�ָ�룬�ú��������ƹ��������ǡ�
    // pDetour    [in] ָ���ƹ�������ָ�룬�ú���������Ŀ�꺯����
    // ppOriginal [out] ָ��Ĵ�������ָ�룬�ú��������ڵ���ԭʼĿ�꺯����
    //                  �ò�������Ϊ NULL��
    // ppTarget   [out] ָ��Ŀ�꺯����ָ�룬������������һ��ʹ�á�
    //                  �ò�������Ϊ NULL��
    MH_STATUS WINAPI MH_CreateHookApiEx(
        LPCWSTR pszModule, LPCSTR pszProcName, LPVOID pDetour, LPVOID *ppOriginal, LPVOID *ppTarget);

    // �Ƴ��Ѵ����Ĺ��ӡ�
    // ����:
    // pTarget [in] ָ��Ŀ�꺯����ָ�롣
    MH_STATUS WINAPI MH_RemoveHook(LPVOID pTarget);

    // �����Ѵ����Ĺ��ӡ�
    // ����:
    // pTarget [in] ָ��Ŀ�꺯����ָ�롣
    //        ����ò���Ϊ MH_ALL_HOOKS���������Ѵ����Ĺ��ӽ�һ�����á�
    MH_STATUS WINAPI MH_EnableHook(LPVOID pTarget);

    // �����Ѵ����Ĺ��ӡ�
    // ����:
    // pTarget [in] ָ��Ŀ�꺯����ָ�롣
    //        ����ò���Ϊ MH_ALL_HOOKS���������Ѵ����Ĺ��ӽ�һ�����á�
    MH_STATUS WINAPI MH_DisableHook(LPVOID pTarget);

    // ���Ѵ����Ĺ����Ŷ��Ժ��á�
    // ����:
    // pTarget [in] ָ��Ŀ�꺯����ָ�롣
    //        ����ò���Ϊ MH_ALL_HOOKS���������Ѵ����Ĺ��ӽ��Ŷ����á�
    MH_STATUS WINAPI MH_QueueEnableHook(LPVOID pTarget);

    // ���Ѵ����Ĺ����Ŷ��Խ��á�
    // ����:
    // pTarget [in] ָ��Ŀ�꺯����ָ�롣
    //        ����ò���Ϊ MH_ALL_HOOKS���������Ѵ����Ĺ��ӽ��Ŷӽ��á�
    MH_STATUS WINAPI MH_QueueDisableHook(LPVOID pTarget);

    // һ����Ӧ�������Ŷӵĸ��ġ�
    MH_STATUS WINAPI MH_ApplyQueued(VOID);

    // �� MH_STATUS ת��Ϊ���ַ�����ʽ�����ơ�
    const char *WINAPI MH_StatusToString(MH_STATUS status);

#ifdef __cplusplus
}
#endif
