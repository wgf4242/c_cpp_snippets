#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <string>
#include <windows.h>
#include <Memoryapi.h>
#include <SIGNAL.H>
#include <process.h>

using namespace std;
#define FLAGLENGTH 36
#define SECNAME ".CRT$XCG"
#pragma section(SECNAME, long, read)

//uint8_t flag[FLAGLENGTH + 1] = "N0opa_G3Ey#zTXjmi5wIHd&5pRN2elaNjK*C";
uint8_t flag[FLAGLENGTH + 1];
uint8_t *pflag;
uint8_t bytes[] = {
        39, 68, 127, 235, 58, 143, 26, 46, 251, 65, 230, 70, 251, 89, 238, 66, 251, 73, 214, 70, 249, 73, 238, 133, 114,
        133, 179, 246, 58, 135, 179, 22, 249, 76, 242, 135, 55, 248, 49, 75, 130, 12, 246, 14, 114, 203, 179, 226, 13,
        160, 156, 137, 181, 73, 10, 14, 114, 12, 246, 133, 55, 240, 205, 75, 98, 3, 117, 138, 114, 12, 246, 133, 55,
        248, 123, 26, 183, 12, 246, 14, 114, 135, 179, 250, 179, 228, 240, 63, 176, 135, 179, 250, 115, 206, 125, 75,
        130, 143, 22, 13, 58, 129, 250, 139, 114, 12, 246, 14, 58, 135, 179, 46, 58, 13, 62, 133, 122, 135, 179, 254,
        115, 196, 199, 222, 115, 73, 14, 133, 55, 224, 247, 75, 130, 135, 179, 246, 255, 24, 51, 14, 114, 12, 246, 133,
        55, 244, 55, 230, 116, 61, 52, 133, 55, 244, 247, 204, 249, 73, 6, 207, 154, 7, 127, 206, 241, 236, 245, 70,
        255, 0, 115, 14, 114, 12, 246, 70, 249, 73, 214, 70, 115, 196, 125, 6, 249, 73, 6, 15, 186, 61, 38, 15, 55, 248,
        117, 75, 142, 13, 31, 126, 141, 243, 9, 70, 249, 73, 238, 133, 39, 244, 127, 30, 58, 135, 179, 22, 58, 143, 54,
        10, 249, 89, 2, 135, 98, 156, 190, 141, 182, 44, 171, 205
}; //put code here
DWORD protect = PAGE_READWRITE;
uint8_t info[] = {155, 169, 160, 175, 163, 161, 169, 236, 184, 163, 236, 184, 164, 169, 236, 171, 173, 161, 169, 237,
                  198, 149, 163, 185, 190, 236, 167, 169, 181, 246, 236};
uint8_t cmp[] = {114, 12, 246, 14, 0x8c, 0x69, 0x23, 0x69, 0x59, 0xa8, 0x06, 0xef, 0x2a, 0x1a, 0x56, 0xb6, 0x96, 0xac,
                 0xee, 0x92, 0x5c, 0xf2, 0xed, 0x0a, 0x5f, 0x36, 0x8e, 0x41, 0xa6, 0x36, 0x86, 0x72, 0x56, 0xd2, 0x54,
                 0xc2, 0x00, 0xc8, 0xa8, 0x00,};
void *meth;
HANDLE hThread = NULL;
unsigned threadID;

typedef NTSTATUS(NTAPI *pfnNtSetInformationThread)(
        _In_ HANDLE ThreadHandle,
        _In_ ULONG ThreadInformationClass,
        _In_ PVOID ThreadInformation,
        _In_ ULONG ThreadInformationLength
);

const ULONG ThreadHideFromDebugger = 0x11;

void HideFromDebugger() {
    HMODULE hNtDll = LoadLibrary(TEXT("ntdll.dll"));
    pfnNtSetInformationThread NtSetInformationThread = (pfnNtSetInformationThread)
            GetProcAddress(hNtDll, "NtSetInformationThread");
    NTSTATUS status = NtSetInformationThread(GetCurrentThread(),
                                             ThreadHideFromDebugger, NULL, 0);
}

void before() {
    pflag = (uint8_t * ) & hThread - 56;
    HANDLE mainThread;
    mainThread = GetCurrentThread();
    SetThreadAffinityMask(mainThread, 0x00000002);
    HideFromDebugger();
}

typedef void(__cdecl *_PVFV)();

__declspec(allocate(SECNAME)) _PVFV dummy[] = {before};

class Base {
public:
    uint8_t *input;

    Base(uint8_t *s) {
        input = s;
    }

    Base() {
        if (IsDebuggerPresent()) {
            exit(-1);
        }
        CONTEXT ctx = {};
        ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;
        if (GetThreadContext(GetCurrentThread(), &ctx)) {
            if (ctx.Dr0 != 0 || ctx.Dr1 != 0 || ctx.Dr2 != 0 || ctx.Dr3 != 0) {
                exit(-1);
            }
        }
    }

    virtual void imple() {
        for (int i = 0; i < FLAGLENGTH; i++) {
            input[i] = ((input[i] & 0xaa) >> 0x1) | ((input[i] & 0x55) << 0x1);
            input[i] = ((input[i] & 0xcc) >> 0x2) | ((input[i] & 0x33) << 0x2);
            input[i] = ((input[i] & 0xf0) >> 0x4) | ((input[i] & 0xf) << 0x4);
        }
    }
};

class DeCrypt : public virtual Base {
public:
    DeCrypt(uint8_t *s) {
        input = s;
    }

    DeCrypt() {}

    virtual void imple() {
        int size = sizeof(bytes);
        meth = VirtualAlloc(NULL, size, MEM_COMMIT, protect);
        uint8_t *write = (uint8_t *) meth;
        for (int i = 0; i < size; i++) {
            write[i] = bytes[i] ^ input[i % 4];
        }
        VirtualProtect(meth, size, PAGE_EXECUTE_READ, &protect);

    }
};

unsigned __stdcall checkdebug(void *pArguments) {
    while (true) {
        for (int i = 0; i < sizeof(bytes); i++) {
            if (*((uint8_t *) meth + i) == 0xcc) {
                exit(-1);
            }
        }
    }
    return 0;
}

class Exec : public virtual Base {
public:
    Exec() {
        this->imple();
    }

    virtual void exec() {
        typedef void(*fptr)(unsigned int, uint32_t *, uint32_t *);
        fptr my_fptr = reinterpret_cast<fptr>(reinterpret_cast<uint64_t>(meth));
        uint8_t info[] = "Welcome to the game!\nYour key: ";
        my_fptr(12, (uint32_t * ) & input[4], (uint32_t * ) & info[0]);
        my_fptr(12, (uint32_t * ) & input[20], (uint32_t * ) & info[16]);
    }

    virtual void imple() {
        hThread = (HANDLE) _beginthreadex(NULL, 0, checkdebug, &bytes, 0, &threadID);
        SetThreadAffinityMask(hThread, 0x00000001);
        Sleep(100);
    }
};

void real_cmp() {
    uint8_t success[] = {6, 32, 102, 54, 48, 96, 38, 123};
    if (!strncmp((char *) cmp, (char *) pflag, FLAGLENGTH)) {
        for (auto c: success) {
            printf("%c", c ^ 0x55);
        }
    }
}

class Fin : public Exec, public DeCrypt {
public:
    Fin(uint8_t *s) {
        input = s;
        uint64_t *pVirtualFunctionTable = (uint64_t * ) * ((uint64_t * )
        this + 4);
        DWORD old;
        //修改内存属性
        VirtualProtect(pVirtualFunctionTable, 4, PAGE_READWRITE, &old);
        pVirtualFunctionTable[0] = (uint64_t) real_cmp;
        VirtualProtect(pVirtualFunctionTable, 4, old, &old);
    }

    void imple() {
        uint8_t success[] = {6, 32, 102, 54, 48, 96, 38, 123};
        if (!strncmp((char *) cmp + 4, (char *) input, FLAGLENGTH)) {
            for (auto c: success) {
                printf("%c", c ^ 0x55);
            }
        }
    }
};

int main() {
    cout << "Welcome to the game!\nYour key: ";
    scanf_s("%s", (char *) flag, FLAGLENGTH + 1);
    if (strlen((char *) flag) != FLAGLENGTH) {
        exit(0);
    }
    Base *base = new Base(flag);
    base->imple();
    delete[] base;
    DeCrypt *dec = new DeCrypt(flag);
    dec->imple();
    delete[] dec;
    Fin *fin = new Fin(flag);
    fin->exec();
    fin->imple();
    delete[] fin;

}