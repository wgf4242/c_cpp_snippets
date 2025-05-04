# DllHook示例工程
1. 实现 动态判断 WindowsProject1.cpp 中 函数 UpdateUI 是否存在
2. Socket实现a02与a03dll通信

# 测试 
1. 选择Debug x86 配置编译
2. 先运行 a02 再运行a04

# TODO

# Inject

```c
bool Injector::Inject( HANDLE hProcess )
{
    //hProcess is a process with writing and reading access
    HANDLE hThread;
    void*  pLibRemote = 0;  
    string dllPath = "Some dll path";
    HMODULE hKernel32 = GetModuleHandle(__TEXT("Kernel32"));


    // pLibRemote = VirtualAllocEx(hProcess, NULL, sizeof(dllPath.c_str()), MEM_COMMIT, PAGE_READWRITE);
    pLibRemote = VirtualAllocEx(hProcess, NULL, dllPath.size() + sizeof(char), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    WriteProcessMemory(hProcess, pLibRemote, dllPath.c_str(), sizeof(dllPath.c_str()), NULL);

    hThread = CreateRemoteThread( hProcess, NULL, 0,    
                    (LPTHREAD_START_ROUTINE) ::GetProcAddress(hKernel32,"LoadLibraryA"), 
                    pLibRemote, 0, NULL );


    .
    .
    .

    CloseHandle(hThread);

    }
```

https://blog.csdn.net/weixin_43354152/article/details/145360457
https://blog.csdn.net/weixin_43360152/article/details/109066011
https://www.cnblogs.com/bruce1992/p/17437656.html
