#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <exception>
#include "sha1.h"

int sha1_test(BYTE* input);
int Filter_div0(int dwExceptionCode);
void sha1(BYTE* input);
void decode(unsigned int* string);
void trigger_exception();
void hook();

#ifdef _WIN64
#pragma comment(linker,"/INCLUDE:_tls_used")
#else
#pragma comment(linker,"/INCLUDE:__tls_used")
#endif // _WIN64

void NTAPI MY_TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved);
//TLS
void NTAPI MY_TLS_CALLBACK(PVOID DllHandle, DWORD Reason, PVOID Reserved)
{
    dbg = IsDebuggerPresent();
}

extern "C"
#ifdef _WIN64
#pragma const_seg(".CRT$XLX")
const
#else
#pragma data_seg(".CRT$XLX")
#endif
PIMAGE_TLS_CALLBACK pTLS_CALLBACKs[] = { MY_TLS_CALLBACK,0 };
#pragma data_seg()
#pragma const_seg()


unsigned int check[100];
unsigned int enc[] = { 0x64744c9a,0x47c2ff1,0xa2d74292,0x85bef77e,0x711fcbf7,0x669e1609,0x6bbd9db6,0x6941c8a4,0xb16e48b3,0xde321186,0x5251e8c2,0xfb8f95a7,0x711fcbf7,0xcb5c3fad,0x36568af5,0xfb8f95a7,0x82acf96a,0x75dcd570,0x7ef00e40,0xfb8f95a7,0x4be9314a,0xcb5c3fad,0xa2d74292,0xde321186,0xfb8f95a7,0x46927fa8,0xb16e48b3,0xd7c1a410,0x567375c3,0x711fcbf7,0xfb8f95a7,0x9c19f0f3,0xd035e914,0xfb8f95a7,0x6941c8a4,0xb7d1395,0xd7c1a410,0xc87a7c7e,0xfb8f95a7,0xd7c1a410,0xde321186,0x5251e8c2,0xfb8f95a7,0xd5380c52,0xbea99d3b,0xcedb7952,0xfb8f95a7,0x73456320,0xd7c1a410,0xde321186,0xfb8f95a7,0x581d99e5,0xa2d74292,0x711fcbf7,0xfb8f95a7,0x6372812,0xfb8f95a7,0x73456320,0xcedb7952,0xef53e254,0xfb8f95a7,0x9f12424d,0x669e1609,0xfb8f95a7,0x9c19f0f3,0xfecf7685,0xb7d1395,0x1833e8b1,0xfb8f95a7,0x9f66dd04,0xa2d74292,0xd7c1a410,0xfb8f95a7,0x6941c8a4,0x866caf4f,0x47c2ff1,0x64744c9a,0xfb8f95a7,0xd5380c52,0xcedb7952,0xde321186,0x81453d43,0xcb5c3fad,0xb16e48b3,0xc578f843,0xcedb7952,0xde321186,0xe38c6f07,0x8b9e97a8,0x8fdf9edf,0xd1868b96,0x93afd1d1,0x8d8bdf85,0x989edf86,0xdf91969e,0xf5c3a0c1,0 };
//moectf{F1nd_th3_SEH_7hen_B1a5t_My_Fla9_and_Y0u_Can_Get_A_Cup_Of_Milk_Tea_From_YunZh1Jun}
char right[] = { "TTTTQQQQQQQLLLLL!!!!!\nThis is your flag!!!\nHave fun in moectf2022 and insist on learning reverse engineering!\n" };
char wrong[] = { "What a pity...Plz try again >_<\n" };
int pass = 1, dbg = 0;

int main()
{
    void (*phook)();
    phook = trigger_exception;

    if (dbg)
        phook = hook;

    BYTE input[100];
    char* result;

    puts("This is a surprise!");
    printf("Give me your flag: ");
    scanf_s("%s", input, 100);

    if (strlen((const char*)input) != 88)
    {
        puts("Wrong length!");
        return 0;
    }

    sha1(input);

    for (int i = 0; i < 88; i++)
    {
        pass = pass && (check[i] == enc[i]);
        if (!pass)
            break;
    }

    __try {
        phook();
    }
    __except (Filter_div0(GetExceptionCode())) {
        decode(enc + 88);
        printf("%s", (char*)(enc + 88));
        return 0;
    }

    if (pass)
        result = right;
    else
        result = wrong;

    printf("%s", result);

    return 0;
}

void sha1(BYTE* input)
{
    pass = sha1_test(input);
}

int sha1_test(BYTE* input)
{
    BYTE tmp[2];
    BYTE buf[SHA1_BLOCK_SIZE];
    SHA1_CTX ctx;

    for (int j = 0; j < 88; j++)
    {
        tmp[0] = input[j];

        sha1_init(&ctx);
        sha1_update(&ctx, tmp, 1);
        sha1_final(&ctx, buf);

        check[j] = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

        //printf("%#x,", check);
    }
    //printf("\n");
    return pass;
}

void decode(unsigned int* string)
{
    for (int i = 0; i < 8; i++)
        string[i] ^= 0xffffffff;
}

void trigger_exception()
{
    int i = 1 / pass;
}

void hook()
{
    int i = 1 + pass;
}

int Filter_div0(int dwExceptionCode)
{
    if (dwExceptionCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
        return EXCEPTION_EXECUTE_HANDLER;

    return EXCEPTION_CONTINUE_SEARCH;
}