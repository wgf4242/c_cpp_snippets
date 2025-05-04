// PEB ->检测BeingDebugged属性
// Windows操作系统维护着每个正在运行的进程的PEB结构，它包含与这个进程相关的所有用户态参数。这些参数包括进程环境数据，环境数据包括环境变量、加载的模块列表、内存地址，以及调试器状态。

// 进程运行时，位置fs:[0x30]指向PEB的基地址。为了实现反调试技术，恶意代码通过这个位置检查BeingDebugged标志，这个标志标识进程是否正在被调试。

//32位
BOOL CheckDebug()  
{  
    int result = 0;  
    __asm  
        {  
        mov eax, fs:[30h]  
        mov al, BYTE PTR [eax + 2]   
    mov result, al  
    }  
    return result != 0;  
}

// 避免这种问题最简单的方法是在执行跳转指令前，手动修改零标志，强制执行跳转(或者不跳转)。

// 可以或者手动修改BeingDebugged属性值为0，后面会进行一次演示