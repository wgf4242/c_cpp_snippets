// 由于调试器中启动进程与正常模式下启动进程有些不同，所以它们创建内存堆的方式也不同。
// 系统使用PEB结构偏移量0x68处的一个未公开位置，来决定如何创建堆结构。
// 如果这个位置的值为0x70，我们就知道进程正运行在调试器中。

BOOL CheckDebug()  
{  
    int result = 0;  
    __asm  
        {  
        mov eax, fs:[30h]  
        mov eax, [eax + 68h]  
        and eax, 0x70  
        mov result, eax  
    }  
    return result != 0;  
}
