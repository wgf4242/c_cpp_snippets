Q1: TLS回调是什么，Crackme1开了TLS回调，为什么搜不到字符串


Windows符号表离线下载
https://www.52pojie.cn/thread-1146411-1-1.html

# 总结
1.设置关闭tls，分析
2.运行到关键点(如弹出窗口)，点击暂停，看调用堆栈 40Xxx位置。
3.搜索模块 - 跨模块调用 - GetMessageA, MessageBoxA
4.查msdn

优化显示函数名:
1.用IDA加载程序，然后生成MAP，
2.x64dbg: SwissArmyKnife插件加载MAP

1.搜索String
2.搜索intermodular call
3.调用堆栈
4.nop call时push也nop，平栈。

设置:
1.关闭系统断点,TLS.
2.忽略异常 00000000-FFFFFFFF
3.xAnalyzer

说明
L宽字符, 2Bytes, 即L"\x2713"  . https://www.cnblogs.com/lanhaicode/p/10661428.html

Windows相关
MessageBoxA, GetMessage, GetDlgItemTextA
Ctrl+G: MessageBoxA, 返回点下断
## 快捷键
Shift+F 添加函数(右击-分析中)
Shift+L 添加函数

## 调试界面说明
![](https://s2.loli.net/2022/09/08/DwTrBJCKmvtq1xi.png)

## FAQ
下载符号： 符号窗口 -  右击 - 下载
# Reverse Engineering 2 Windows GUI Programs

## Crackme files
crackinglessons.com
https://github.com/cspinstructor/github-crackmes
https://crackinglessons.com/crackme1/

## Crackme1 - 5. Setting breakpoints on strings - Crackme1

x64dbg ,  
1. 设置 - × TLS回调 (即Thread Local Storage: 程序执行前自动执行的回调函数)
    - 如果没设置状态栏会提示 断在了TLS 回调。如何搜不到字符串。定位到程序领空再搜索字符串。
载入后，运行，输入。弹窗。右击 - 搜索范围 - 当前模块 - 字符串引用。
找到Wrongkey, 跳转。上面是Well Done

```asm
00401139 | 75 19                      | jne crackme1.401154                     | ; 断这里
0040113B | 68 E81A4100                | push crackme1.411AE8                    | 411AE8:"Congrats!"
00401140 | 68 F41A4100                | push crackme1.411AF4                    | 411AF4:"Well done!"
00401145 | 50                         | push eax                                |
00401146 | FF15 18D14000              | call dword ptr ds:[<&MessageBoxA>]      |
```

继续向上, 在GetDlgItemTextA下面断， 得到key

```asm
004010FB | FF15 10D14000              | call dword ptr ds:[<&GetDlgItemTextA>]  |
00401101 | B9 D81A4100                | mov ecx,crackme1.411AD8                 | 断这里 ; ecx:"cr4ckingL3ssons", 411AD8:"cr4ckingL3ssons"
00401106 | 8D45 D0                    | lea eax,dword ptr ss:[ebp-30]           |
00401109 | 0F1F80 00000000            | nop dword ptr ds:[eax],eax              |
```

## 1. Windows API functions

[MessageBox](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox)

```
int MessageBox(
  [in, optional] HWND    hWnd,
  [in, optional] LPCTSTR lpText,
  [in, optional] LPCTSTR lpCaption,
  [in]           UINT    uType
);
```

对照程序看

```asm
00401135 | 6A 00                      | push 0                                  | uType, 下一步可能跳1154 所以下面没有push 0
00401137 | 85C0                       | test eax,eax                            |
00401139 | 75 19                      | jne crackme1.401154                     |
0040113B | 68 E81A4100                | push crackme1.411AE8                    | lpCaption, 411AE8:"Congrats!"
00401140 | 68 F41A4100                | push crackme1.411AF4                    | lpText,    411AF4:"Well done!"
00401145 | 50                         | push eax                                |
00401146 | FF15 18D14000              | call dword ptr ds:[<&MessageBoxA>]      |
0040114C | 33C0                       | xor eax,eax                             |
0040114E | 8BE5                       | mov esp,ebp                             |
00401150 | 5D                         | pop ebp                                 |
00401151 | C2 1000                    | ret 10                                  |
00401154 | 68 001B4100                | push crackme1.411B00                    | lpCaption, 411B00:"Sorry"
00401159 | 68 081B4100                | push crackme1.411B08                    | lpText,    411B08:"Wrong serial key. Try again."
0040115E | 6A 00                      | push 0                                  | Parent Window
```

## 7. Pushing parameters to the stack
GetDlgItemTextA

https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getdlgitemtexta
```c
UINT GetDlgItemTextA(
  [in]  HWND  hDlg,
  [in]  int   nIDDlgItem, // The identifier of the control whose title or text is to be retrieved.
  [out] LPSTR lpString,
  [in]  int   cchMax     // The maximum length
);
```

```
004010EA | 6A 30                      | push 30                              | cchMax
004010EC | 8D45 D0                    | lea eax,dword ptr ss:[ebp-30]        |
004010EF | 50                         | push eax                             | hDlg
004010F0 | 68 E8030000                | push 3E8                             | nIIDlgItem
004010F5 | FF35 A0424100              | push dword ptr ds:[4142A0]           | hDlg
004010FB | FF15 10D14000              | call dword ptr ds:[<&GetDlgItemTextA |
```

Resource Hacker看 3E8: 1000 , 是Textbox
```
   CONTROL "", 1000, EDIT, ES_LEFT | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, 37, 42, 106, 14 
```

## 8. Bypassing messages


```
00401137 | 85C0                       | test eax,eax                         |
00401139 | 75 19                      | jne crackme1.401154                  | if eax=0, 进入welldone
0040113B | 68 E81A4100                | push crackme1.411AE8                 | 411AE8:"Congrats!"
00401140 | 68 F41A4100                | push crackme1.411AF4                 | 411AF4:"Well done!"
00401145 | 50                         | push eax                             |
; 按Space 修改后
00401139 | B0 01                      | mov al,0                             | if eax=0, 进入welldone
0040113B | 68 E81A4100                | push crackme1.411AE8                 | 411AE8:"Congrats!"
00401140 | 68 F41A4100                | push crackme1.411AF4                 | 411AF4:"Well done!"
00401145 | 50                         | push eax                             |
00401146 | FF15 18D14000              | call dword ptr ds:[<&MessageBoxA>]   |
```

修改完成后，
文件 - 补丁文件 -  补丁文件(Ctrl+P)

## 9. Bypassing using xor assembly, 异或赋值eax为0

Using this:

```asm
mov al, 0       ;0xFFFFFF00
```

Better way is:
```
xor eax, eax; 0x00000000
```


## 10. Breakpoints on Intermodular Calls

Search for - Current Module - Intermodular calls(跨模块调用)

断 GetMessageA, MessageBoxA

## 11. Breakpoints from Call Stack

x64dbg, 随便输入点击提示Wrong 之后，看Call Stack(调用堆栈Tab: Alt+K)

看 From 40xxxx。用户模块的。 右键- Follow From


## Crackme2

跟进F7关键call，看到createfile 
搜 msdn createfile

https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea

```
0040102C | 6A 00                      | push 0                               |
0040102E | 68 80000040                | push 40000080                        |
00401033 | 6A 03                      | push 3                               |
00401035 | 6A 00                      | push 0                               |
00401037 | 6A 01                      | push 1                               |
00401039 | 68 00000080                | push 80000000                        |
0040103E | 68 281B4100                | push crackme2.411B28                 | 创建文件;411B28:"keyfile.txt"
00401043 | FF15 00D04000              | call dword ptr ds:[<&CreateFileA>]   |
00401049 | 8BF0                       | mov esi,eax                          | eax返回值，赋值给esi
0040104B | 83FE FF                    | cmp esi,FFFFFFFF                     | if esi==-1 跳走
0040104E | 74 51                      | je crackme2.4010A1                   |
```

注意 call, return value 存在eax

## Crackme3 16. Removing Nag screens

x64dbg设置
1.关闭系统断点,TLS.
2.忽略异常 00000000-FFFFFFFF

追踪 - 自动略过(Ctrl+F8) , 找到Call , jne修改为jmp

```
00401024 | A3 A4424100                | mov dword ptr ds:[4142A4],eax        |
00401029 | 75 19                      | jne crackme3.401044                  |
0040102B | 6A 00                      | push 0                               |
0040102D | 68 D81A4100                | push crackme3.411AD8                 | 411AD8:"Opening Nag"
00401032 | 68 E41A4100                | push crackme3.411AE4                 | 411AE4:"I am a nag screen\nPlease remove me."
```

## 19. Removing Nag screen 2.mp4
问题2. 直接将部分代码nop

操作步骤：运行到关键点(如弹出窗口)，点击暂停，看调用堆栈 40Xxx位置。

## 20. Setting Registration Status
运行到如弹出窗口please register me，点击暂停，看调用堆栈 User Call.

找到在ret后。向上找到 register的call。

通过nop, 保持大小 修改 je.

## Crackme4 23. Extending Trial Periods / Trace使用

Trace - Animate Over(Ctrl+F8)  , 找到 Last Call
跟入 ，找到关键点

## Target
1.向下看到字符串。 nop 掉 push和call
2.运行程序，找到字符串，找到两处下断点 Nag not removed.
3.第1个不是recheck, 第2个断下向上找。1跳 nop je , 2跳 je -> jmp

## CrackMe7 - 27. Patching EAX register values
1.Tracing - Animte Over, 找到call F7

```
mov al, 1    - 2Bytes
```

Register eax usually stores
  - results of function calls.
  - operations 
  - comparisons.
Jumps are often based on the results stored in eax.

```
0040102C | 2BC1                       | sub eax,ecx                          | ; mov al, 1
0040102E | 85C0                       | test eax,eax                         |
00401030 | 74 05                      | je crackme7.401037                   | shoud not jump
00401032 | B8 02000000                | mov eax,2                            |
00401037 | 85C0                       | test eax,eax                         |
00401039 | 74 07                      | je crackme7.401042                   |
0040103B | 68 D81A4100                | push crackme7.411AD8                 | 411AD8:"Registered"
```

## Crackme8 28. Hardware Breakpoints
Definitions:
Hardware BP's are breakpoints on memory access .
Software BP's are breakpoints on instructions.
objectives:
1. Setting hardware breakpoints on RAM memory
2. Modifying data in RAM memory addresses directly

1.搜索 - 当前模块 - Seach For String reference
2.找到Register，进入，找上面的je。
3.找je上面的cmp 

0040385A | 833D D0607200 00           | cmp dword ptr ds:[7260D0],0          |

4.点击这行，在显示区/或反汇编区， 右击 dword ptr ds:[7260D0] ， Follow In Dump - Address 
5.转储区 右击地址第一个Byte, Breakpoint - Hardware,Access - Dword
6.重新运行
7.在cmp处。Follow In Dump - Address, 修改为01.生成补丁。

```asm
0040385A | 833D D0607200 00           | cmp dword ptr ds:[7260D0],0                    | 断在这里操作
00403861 | 8B45 EC                    | mov eax,dword ptr ss:[ebp-14]                  |
```

## Crackme9. 29. Memory Patching

1.搜String, 向上找je
2.使用了esi， esi来自eax，向上找到callA后 eax设置为FFFFFFF
3.步入call, 

00403A1D | C74424 04 2A827100         | mov dword ptr ss:[esp+4],crackme9.71822A       | 71822A:"ABC-123456" 存的字符串所以这里是原始地址。
                                                                                       | [esp+4]:&L"ABC-123456", 71822A:"ABC-123456"
00403A25 | E8 0E283100                | call crackme9.716238                           | 上面&L是存引用了, L: Unicode编码。2字节
00403A2A | C745 BC 02000000           | mov dword ptr ss:[ebp-44],2                    |
00403A31 | 8D45 F0                    | lea eax,dword ptr ss:[ebp-10]                  | [ebp-10]:L"ABC-123456"
00403A34 | 894424 04                  | mov dword ptr ss:[esp+4],eax                   | [esp+4]:&L"ABC-123456"
00403A38 | 8D45 EC                    | lea eax,dword ptr ss:[ebp-14]                  | [ebp-14]:L"aaaaaaaaaa"
00403A3B | 890424                     | mov dword ptr ss:[esp],eax                     | [esp]:&L"aaaaaaaaaa"
00403A3E | E8 11283100                | call crackme9.716254                           | 修改了eax
00403A43 | 89C6                       | mov esi,eax                                    |

4.在转储中跟随 71822A, 右击 Binary - Edit(Ctrl+E) 修改内存为CBA-123456 √保持大小
5.补丁文件
## 30. xAnalyzer
https://github.com/ThunderCls/xAnalyzer

下载
xAnalyzer.dp64
xAnalyzer.dp32
apis_def.zip

xAnalyzer.dp32  apis_def.zip 复制到x32/plugins 解压zip
xAnalyzer.dp64  apis_def.zip 复制到x64/plugins 解压zip

菜单 Plugins - xAnalyzer - Automatic Analysis
菜单 Plugins - xAnalyzer - Automatic Undefined Function

选中区域, 右击 - xAnalyzer

## ReverseMe2-by-Lena 31. Serial Phishing

```asm
0040106E | 68 79204000                | push reverseme2-by-lena.402079                 | LPCTSTR lpFileName = "Keyfile.dat"
00401073 | E8 0B020000                | call <JMP.&_CreateFileA@28>                    | 打开Keyfile.dat文件 CreateFileA
...

004010A3 | 68 1A214000                | push reverseme2-by-lena.40211A                 | 读取内容写入49211A LPVOID lpBuffer = "G111111111111111"
004010A8 | 50                         | push eax                                       | HANDLE hFile
004010A9 | E8 2F020000                | call <JMP.&_ReadFile@20>                       | ReadFile

...
004010B6 | 33F6                       | xor esi,esi                                    | esi:EntryPoint
004010B8 | 833D 73214000 10           | cmp dword ptr ds:[402173],10                   | 16个字符
004010BF | 7C 36                      | jl reverseme2-by-lena.4010F7                   |
004010C1 | 8A83 1A214000              | mov al,byte ptr ds:[ebx+40211A]                |
004010C7 | 3C 00                      | cmp al,0                                       | 是否字符串结束
004010C9 | 74 08                      | je reverseme2-by-lena.4010D3                   |
004010CB | 3C 47                      | cmp al,47                                      | 47:'G'
004010CD | 75 01                      | jne reverseme2-by-lena.4010D0                  |
004010CF | 46                         | inc esi                                        | G的计数器
004010D0 | 43                         | inc ebx                                        |
004010D1 | EB EE                      | jmp reverseme2-by-lena.4010C1                  |
004010D3 | 83FE 08                    | cmp esi,8                                      | G和8比
004010D6 | 7C 1F                      | jl reverseme2-by-lena.4010F7                   | >8成功
```
