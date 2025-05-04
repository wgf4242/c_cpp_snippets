// ### 5、PEB -> 检测ProcessHeap属性
// Reserved数组中一个未公开的位置叫作ProcessHeap，它被设置为加载器为进程分配的第一个堆的位置。
// ProcessHeap位于PEB结构的0x18处。
// 第一个堆头部有一个属性字段，它告诉内核这个堆是否在调试器中创建。
// 这些属性叫作ForceFlags和Flags。
// 在Windows XP系统中，ForceFlags属性位于堆头部偏移量0x10处；
// 在Windows 7系统中，对于32位的应用程序来说ForceFlags属性位于堆头部偏移量0x44处。

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
            mov eax, [eax + 10h]  
            mov result, eax  
        }  
    }  
    else  //W10也可以
    {  
        __asm  
            {  
            mov eax, fs:[30h]  
            mov eax, [eax + 18h]  
            mov eax, [eax + 44h]  
            mov result, eax  
        }  
    }  
    return result != 0;  
}