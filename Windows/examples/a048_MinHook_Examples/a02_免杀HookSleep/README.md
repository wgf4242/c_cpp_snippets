Inline Hook 技术：当程序“拐个弯”，你还认得它吗？ https://mp.weixin.qq.com/s/g3OHASmUP-RevCH9TXueZg

图解
```
main() →
    MH_Initialize() → MH_CreateHookApi("Sleep") →
        修改 Sleep 的入口：jmp MyHookSleep

↓
Sleep(1000)
↓
MyHookSleep()
↓
    VirtualAlloc() → memcpy → XOR 解密 →
    CreateThread(执行 shellcode) →
    SecureZeroMemory + VirtualFree →
    fpSleep(ms) ← 调回原始 Sleep
↓
Sleep(500)
↓
fpSleep(ms) ← 已不再走解密路径
```