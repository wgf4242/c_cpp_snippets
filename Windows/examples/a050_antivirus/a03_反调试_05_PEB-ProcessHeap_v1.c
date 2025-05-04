//我的例子
#include<Windows.h>
#include <iostream>
using namespace std;

int  main()
{
    int realt =0;
    __asm//w10、w8、w7
        {
        mov eax,fs:[0x30]
        mov eax,[eax+0x18]
        mov eax,[eax+0x44]  //ForceFlag 堆属性 
        mov realt,eax  
    }
    
    if (realt)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "没有调试" << endl;
    }

    getchar();
    return 0;
}

// 同样，恶意代码也可以检查Windows XP系统中偏移量0x0C处，
// 或者Windows 7系统中偏移量0x40处的Flags属性。
// 这个属性总与ForceFlags属性大致相同，但通常情况下Flags与值2进行比较。
BOOL CheckDebug()  
{  
    int result = 0;  
    DWORD dwVersion = GetVersion();  
    DWORD dwWindowsMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));  
    //for xp  
    if (dwWindowsMajorVersion == 5)  
    {  
        __asm  
            {  
            mov eax, fs:[30h]  
            mov eax, [eax + 18h]  
            mov eax, [eax + 0ch]  
            mov result, eax  
        }  
    }  
    else  
    {  
        __asm  
            {  
            mov eax, fs:[30h]  
            mov eax, [eax + 18h]  
            mov eax, [eax + 40h]  
            mov result, eax  
        }  
    }  
    return result != 2;  
}