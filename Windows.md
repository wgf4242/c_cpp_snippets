Google 搜索 Visual Studio tutorials | C++
https://learn.microsoft.com/en-us/cpp/get-started/?view=msvc-170

[C++课程资源.md](https://github.com/ritianpig/-/blob/main/C++%E8%AF%BE%E7%A8%8B%E8%B5%84%E6%BA%90.md)

# 1 错误处理

常见函数返回值的数据类型

void
bool
handle | 可操作对象,失败返回 NULL, INVALID_HANDLE_VALUE 值为-1
pvoid | 标识数据块的内存地址, 失败为 NULL
LONG/DWORD | 阅读 SDK

thread-local-storage 子线程处理错误，返回值指向已发生的错误, 具体错误调用

```c
DWORD GetLastError();
```

winerror.h 中包含了错误列表。

```
// MessageId: ERROR_SUCCESS
#define ERROR_SUCCESS                    0L
#define NO_ERROR 0L                                                 // dderror
```

每个错误分为: 消息 ID，消息文本，编号。

Windows 函数失败后应该马上调用 GetLastError, 因为其他函数调用后可能会改写, 成功调用的 Windows 函数可以用 ERROR_SUCCESS 改写此值。

已存在具名事件返回 ERROR_ALREADY_EXISTS

调试时 在监视 1 窗口(Watch 1)中输入 $err,hr 即可查看 GetLastError

[FormatMesage](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-formatmessage) 将错误代码转为文本描述。

## 1.1 定义自己的错误代码

设置线程的上一个错误代码，令自己的函数返回 FALSE, INVALID_HANDLE_VALUE, NULL 或其他适合值。

```
VOID SetLastError(DWORD dwErrCode)
```

| 位   | 31-30                                                        | 29                                             | 28       | 27-16                        | 15-0                       |
| ---- | ------------------------------------------------------------ | ---------------------------------------------- | -------- | ---------------------------- | -------------------------- |
| 内容 | 严重性                                                       | Microsoft                                      | 保留     | Facility                     | 异常代码                   |
| 含义 | 0 = 成功<br />1 = 信息（提示） <br />2 = 警告<br /> 3 = 错误 | 0 = Microsoft 定义的代码<br>1 = 客户定义的代码 | 必须为 0 | 前 256 个值由 Microsoft 保留 | Microsoft / 客户定义的代码 |

## 1.2 ErrorShow 示例程序

# 2 字符和字符串处理

有 2 个版本 CreateWindowEx, 平时只用 CreateWindowEx 即可 它是一个宏。默认会调 W 版本

CreateWindowExW 接受 Unicode // Wide
CreateWindowExA 接受 Unicode // Ansi

# 4 进程

## 4.1 编写第一个 Windows 应用程序

CUI 程序链接器开关 /SUBSYSTEM:CONSOLE
GUI 程序链接器开关 /SUBSYSTEM:WINDOWS

入口点 两种

```c
int WINAPI _tWinMain()
int _tmain()
```

`-entry:启动函数`

| 应用程序类型                             | 入口点函数            | 嵌入可执行文件的启动函数 |
| :--------------------------------------- | :-------------------- | :----------------------- |
| 处理 ANSI 字符和字符串的 GUI 应用程序    | \_tWinMain (WinMain)  | WinMainCRTStartup        |
| 处理 Unicode 字符和字符串的 GUI 应用程序 | \_tWinMain (wWinMain) | wWinMainCRTStartup       |
| 处理 ANSI 字符和字符串的 CUI 应用程序    | \_tmain (Main)        | mainCRTStartup           |
| 处理 Unicode 字符和字符串的 CUI 应用程序 | \_tmain (Wmain)       | wmainCRTStartup          |

/SUBSYSTEM:WINDOWS 会找 `WinMain` 或 `wWinMain` 找不到会返回 "unresolved external symbol" 否则根据情况选择 `WinMainCRTStartup` 或 `wWinMainCRTStartup`

# Windows 全新开发编程实例教程

## Theory/理论学习
[Windows 保护模式学习笔记](https://www.cnblogs.com/Here-is-SG/p/18734496#autoid-7-3-0)

## Visual Studio

- 头文件包含 prgama 和 ifndef 一样, 包含一次
  #prgama once
  #ifndef
  #define

## WindowsAPI/内存
[共享内存](https://mp.weixin.qq.com/s/025EdbUifGrxMQA3WY-OLQ)
[Win32 API · 内存操作](https://mp.weixin.qq.com/s/NGPb7YfMiZSBMJuVfrweLQ)
[Win32 API · 进程与线程](https://mp.weixin.qq.com/s/2WWt0GJ6uL0iPUQH9Q5QEA)
[通过修改物理内存实现跨进程内存读写](https://mp.weixin.qq.com/s/HBHJeTTNEQ5AVfarBenZZQ)
[使用 Windows API 查找 PID 和 PPID](https://mp.weixin.qq.com/s/zaz-Qed9ScbZihagcgsudw)
[C++内存读写 | 植物大战僵尸](https://www.bilibili.com/video/BV1jT421Q7si/)

| DLL Name | Description |
|-------------------|--------------------------------------------------|
| Kernel32 | Core functionality – memory, processes, files and hardware |
| Advapi32 | Service manager, registry |
| User32 | User interface |
| Ntdll | Low level API, not intended to be called directly |
| WSock32/ws2_32 | Low-level networking |
| Wininet | High-level networking (HTTP, FTP, etc) |

## 安全编程/免杀

- CTF\binary\Reverse\index.md

[免杀学习-基础-一](https://mp.weixin.qq.com/s/qpINhoeK3gBNrZrY_jH7Cw)
[Windows*Shellcode*内联汇编](https://secondbc.github.io/SecondBC/2023/06/19/Windows_Shellcode/)
[从 PE 资源加载和执行 shellcode](https://mp.weixin.qq.com/s/299TT25LXzWtymUPCvhGdQ)
[Windows 编程](https://secondbc.github.io/SecondBC/2022/12/04/Windows编程/)
[远程线程注入-极安御信网络安全系列课程-病毒分析](https://www.bilibili.com/video/BV1ww411U71g/)
[远程线程注入：让别的程序替你“干活”](https://mp.weixin.qq.com/s/yLjdfjm8_weCDvIocqDHbQ)
[PE 简单解析器](https://secondbc.github.io/SecondBC/2022/11/12/PE简单解析器/)
[一周学会 Windbg 调试器使用第 8 篇 - 何时使用 Windbg 进行动态调试](https://www.bilibili.com/video/BV1DX4y1b7bq/)
[极安御信网络安全系列课程-C++ shellcode 加载器原理](https://www.bilibili.com/video/BV19P411v7rX/)
[动态免杀系列 VEH异常处理内存动态免杀](https://mp.weixin.qq.com/s/CZgXZPkL2pGx1IvOtgFbeQ)
[让安全软件瑟瑟发抖：重生之我是天命进程](https://mp.weixin.qq.com/s/NrqiIjJNn7SAwp3Wgj8dMw)

## 安全编程/免杀/shellcode

#TODO [Video | 【全15集】恶意代码开发教程从零基础到精通](https://www.bilibili.com/video/BV113rfB5Euk)

[shellcode loader 的编写](https://mp.weixin.qq.com/s/sfxmWf9nCQeAc7PRRG5eaQ)
[在 ShellCode 里面使用异常处理(Win64 位平台)](https://mp.weixin.qq.com/s/I2lw1j63QsDmjtKyJalveg)

### dll/进程 注入/Hook
https://github.com/Joe1sn/S-inject

[[原创] 图解远程线程注入技术（新手向）](https://bbs.kanxue.com/thread-284080.htm)
[Windows钩子技术与恶意软件应用](https://mp.weixin.qq.com/s/m1tOR8eIVDUWQa12xyW__g)
[DLL 注入与 HOOK](https://secondbc.github.io/SecondBC/2022/12/12/DLL注入与HOOK/)
[DLL 显式调用及隐式调用](https://www.bilibili.com/video/BV1M44y1F79S/)
[dll 延迟加载技术](https://mp.weixin.qq.com/s/wxNQ7yn1W1s85hR8CZGeRQ)
[免杀基础之 DLL 远程线程注入](https://mp.weixin.qq.com/s/oaVq98wxbA6OOxoMcStBIw)
[【逆向学习】Windows 平台下的 DLL 注入](https://www.xunflash.top/archives/DLLInject.html)
[DLL 注入之 APC 注入](https://www.bilibili.com/video/BV1PB4y1f7eW/)
[exe 注入之全局钩子注入](https://mp.weixin.qq.com/s/l_hCz_Kbm_q2MPjUd5WPbw)
[远线程注入](https://mp.weixin.qq.com/s/CNZFytugjY2LZb_HqHf1EQ)
[浅析RDI-反射DLL注入](https://mp.weixin.qq.com/s/5huCKEoxrnWyFDdBmxI3dA)
[[原创]学习PE文件后的第一次实践项目之DLL反射型注入 ](https://bbs.kanxue.com/thread-284885.htm)
[【C++ Hook钩子技术(中)——Hook按键小精灵弹窗】从弹窗引发的Hook编程思考大爆炸，拨开表象寻求真实自我！突破常规思维，建立底层逻辑。](https://www.bilibili.com/video/BV1Mq421c7j8/)
[第十六课 拦截DLL注入](https://www.bilibili.com/video/BV1kr421g7ri/)
[Windows攻防对抗-DLL侧载篇](https://mp.weixin.qq.com/s/fZAu99uVUskO1T4-QIoVPg)
[进程注入](https://mp.weixin.qq.com/s/shIXAYlqRp4WjoRxvHUQHQ)

[#隐藏 | 浅谈进程隐藏技术](https://mp.weixin.qq.com/s/tHZbZGAaApRH8Ly-Nynb6Q)  [如何使用挂钩`NtQuerySystemInformation` API以隐藏特定进程的DLL注入技巧](https://blog.csdn.net/m0_57781768/article/details/133547992)
[#隐藏 | win10-win11进程隐藏小技巧](https://www.52pojie.cn/thread-1866668-1-1.html)
[#隐藏 | Windows进程隐藏技术揭秘 | WinDbg+OpenArk深度演示APT级伪装术](https://www.bilibili.com/video/BV19QjgzLEuf)

[重生之我在干免杀-利用 Windows 线程池 API：使用 IO 完成回调代理 DLL 加载](https://mp.weixin.qq.com/s/J5kokfj3bcb77Jl81l1AKg)
[游戏安全入门-扫雷分析&远程线程注入](https://mp.weixin.qq.com/s/3yxlMtOStHzgsATBMk0HQg)
[『免杀系列』DLL劫持](https://mp.weixin.qq.com/s/NqpZyIKg3FvrnotWzz06kg)
[利用Windows引导程序安全加载DLL](https://mp.weixin.qq.com/s/PYbuROGbtv7ZgJRJwiYv7g)
[反射DLL注入原理解析](https://mp.weixin.qq.com/s/6Mu7opmPBw7ICVYJgNG66g)
[Hollow | Windows进程空洞（Hollow Process ）注入](https://mp.weixin.qq.com/s/CPveNNu3qzhr4FGacxH_cQ)
[Hollow | Process Hollowing on Windows 11 24H2](https://hshrzd.wordpress.com/2025/01/27/process-hollowing-on-windows-11-24h2/)
[【原创】优雅地在 Hook 时替换 std::string 的内容](https://www.52pojie.cn/thread-1905246-1-1.html)
[高级进程注入之利用线程名和APC（下）](https://mp.weixin.qq.com/s/jfTTcUfyTladoRb1ZmvK2A)
["破碎注入"无痕注入不使用任何进程句柄的注入技术原理分析](https://mp.weixin.qq.com/s/mp_FcnPpvTEFPQ4LvBSE-A)

## 寻址

[动态寻找函数地址](https://mp.weixin.qq.com/s/zVJvggesZTtvvK__aR4jtw)

# Aritcle

[键盘消息 | [原创] 从应用层到 MCU，看 Windows 处理键盘输入 [1.在应用层调试 Notepad.exe (按键消费者)] ](https://bbs.kanxue.com/user-home-399589.htm)
[国外油管大神 C++游戏编程实战教程，新手 6 小时入门，并快速达到游戏开发能力（中英字](https://www.bilibili.com/video/BV16h4y1d766/)
[极安御信网络安全系列课程 Windows 编程基础-Windows 窗口 API 详解](https://www.bilibili.com/video/BV1cV4y1e7pq/)
[MinGW能不能调用MSVC生成的dll](https://www.bilibili.com/video/BV1na4y1D7eS/)

## API
CreateFileA,OpenFile,
[Windows API 简介](https://mp.weixin.qq.com/s/NBAYTCksJWpA-nCiVyX0Pw)
[Windows 远端线程执行任意 API 的设计与实现](https://mp.weixin.qq.com/s/bqLiDI-kt6dDIWyl-C3K0Q)
[windows-api-function-cheatsheets](https://github.com/snowcra5h/windows-api-function-cheatsheets)
[《Windows 恶意软件常见 API 一览》发布](https://mp.weixin.qq.com/s/GCNK3eLXYLWMGF6BW3Yy-A)
[系统调用-API函数调用过程](https://mp.weixin.qq.com/s/Ay2SAtwVZnCZmFaLofiw8g)

## network

[socket 网络编程的 5 大隐患](https://mp.weixin.qq.com/s/KDF0lTR7PiA4K2JQjsZxEg)

## MFC

[极安御信网络安全系列课程-Windows 逆向基础-MFC 源码分析(MFC 窗口创建机制)](https://www.bilibili.com/video/BV1Ym4y1q7FD/)

## Tools

[Dependency Ms](https://learn.microsoft.com/zh-cn/cpp/windows/understanding-the-dependencies-of-a-visual-cpp-application?view=msvc-170) [Win8 前](https://www.dependencywalker.com/) [Win8 后](https://github.com/lucasg/Dependencies)

# FAQ

# 查看 lib 文件/查看符号表

```sh
dumpbin -exports kernel32.lib
dumpbin -exports DLLTutorial.dll
```
