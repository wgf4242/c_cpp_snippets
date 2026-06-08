# Windows内核进程基础概念讲义
[Link](https://www.bilibili.com/video/BV1tyRuB1ErW)

## 进程本质理解
### 核心概念
进程是空间上的概念，不是时间上的概念

这是理解进程最重要的认知起点。线程才是执行单位，进程本身不执行任何代码。

进程的本质可以用一个公式表达：
> 进程 = 独立的虚拟地址空间 + 资源容器

## CR3寄存器的核心作用
CR3寄存器是进程隔离的硬件基础：
- CR3存储当前进程的页目录基址（页表基址）
- 同一块物理内存，不同的CR3值会看到不同的虚拟地址映射
- 切换进程的本质就是切换CR3

```
进程A (CR3=0x1000)      进程B (CR3=0x2000)
    |                      |
    v                      v
虚拟地址 0x400000  --> 物理地址 0xABC000
虚拟地址 0x400000  --> 物理地址 0xDEF000
```

## 四个关键认知点
| 序号 | 认知点 | 说明 |
| :---: | --- | --- |
| 1 | 进程不执行代码 | 线程才是执行单位，进程只提供执行环境 |
| 2 | 进程是资源容器 | 包含地址空间、句柄表、令牌等资源 |
| 3 | 进程隔离的本质 | 不同CR3导致相同虚拟地址映射到不同物理地址 |
| 4 | 内核空间共享 | 所有进程的内核空间映射相同（高地址部分） |

## 二、三大结构体关系
### 结构体层次概览
Windows使用三个核心结构体来描述进程：

|结构体|所在层|主要职责|访问方式|
| ---- | ---- | ---- | ---- |
|PEB|用户态|存储用户态可见的进程信息|FS:[0x30] / GS:[0x60]|
|KPROCESS|内核态|调度相关信息|EPROCESS的第一个成员(Pcb)|
|EPROCESS|内核态|进程完整描述|PsGetCurrentProcess()|

### 1. PEB（Process Environment Block，进程环境块）
- 位置：用户态
- 访问方式：
  - x86：`FS:[0x30]`
  - x64：`GS:[0x60]`
- 职责：存储用户态可见的进程信息

### 2. KPROCESS（Kernel Process，内核进程块）
- 位置：内核态
- 访问方式：作为EPROCESS的第一个成员（Pcb字段）
- 职责：
  - CR3（页目录基址）
  - 进程优先级
  - 线程链表
  - 其他调度相关信息

### 3. EPROCESS（Executive Process，执行体进程块）
#### EPROCESS概述
EPROCESS（Executive Process）是Windows执行体层用于描述进程的核心数据结构。每当系统创建一个新进程时，内核都会分配一个EPROCESS结构体来存储该进程的所有管理信息。

#### EPROCESS的设计哲学
Windows内核采用分层设计，进程相关结构体也体现了这一思想：
```
┌─────────────────────────┐
│       EPROCESS          │ ← 执行体层：完整的进程管理信息
│   ┌─────────────────┐   │
│   │    KPROCESS     │   │ ← 内核层：调度相关的核心信息
│   │     (Pcb)       │   │
│   └─────────────────┘   │
└─────────────────────────┘
            │
            │ 指向
            ▼
┌─────────────────────────┐
│         PEB            │ ← 用户层：用户态可见的进程信息
└─────────────────────────┘
```
EPROCESS的第一个成员是KPROCESS（字段名Pcb），这种设计使得EPROCESS指针可以直接当作KPROCESS指针使用，简化了内核代码。

#### 如何获取EPROCESS
```c
// 获取当前进程的EPROCESS
PEPROCESS pEprocess = PsGetCurrentProcess();

// 通过PID获取EPROCESS
PEPROCESS pEprocess;
PsLookupProcessByProcessId(pid, &pEprocess);
```

#### 核心字段详解
##### 内嵌KPROCESS结构
|偏移|字段|类型|
| ---- | ---- | ---- |
|+0x000|Pcb|_KPROCESS|

Pcb（Process Control Block，进程控制块）是EPROCESS的第一个成员，类型为KPROCESS。
KPROCESS包含了进程调度所需的核心信息：
- `DirectoryTableBase`：页目录基址（CR3值），决定进程的虚拟地址空间
- `ThreadListHead`：属于该进程的所有线程链表
- `BasePriority`：进程基础优先级
- `Affinity`：处理器亲和性掩码

由于Pcb位于偏移0，EPROCESS指针可以直接强制转换为KPROCESS指针使用：
```c
PKPROCESS pkprocess = (PKPROCESS)pEprocess; // 合法转换
```

# 核心标识字段
## **UniqueProcessId (+0x0b4)**

|偏移|字段|类型|
| ---- | ---- | ---- |
|+0x0b4|UniqueProcessId|Ptr32 Void|

进程唯一标识符（PID），在系统范围内唯一标识一个进程。
PID的特点：
- 类型虽然是指针，但实际存储的是数值
- PID在进程生命周期内不变
- System进程的PID固定为4

**安全应用**

- 检测PID欺骗攻击（恶意进程伪造PID）



### 本次调试练习 Chapter 2



```bash
# windbg
dt _eprocess

// -- 遍历所有进程 , cid(ClientID)就是PID--
1: kd> !process 0 0

PROCESS 8ee1d040  SessionId: 1  Cid: 1bc88    Peb: 002fe000  ParentCid: 0db0
    DirBase: 3fff85e0  ObjectTable: a63d6640  HandleCount: 171.
    Image: InstDrv.exe
    
// --  --
1: kd> dt _eprocess 8ee1d040
nt!_EPROCESS
+0x000 Pcb              : _KPROCESS
+0x0b0 ProcessLock      : _EX_PUSH_LOCK
+0x0b4 UniqueProcessId  : 0x000001bc8 Void     // PID值, 修改为0任务管理器和x64dbg遍历不到, CE window能遍历到

// --  --
1: kd> dt _kprocess 8ee1d040
PROCESS 8ee32040  SessionId: 1  Cid: 0d34    Peb: 003a0000  ParentCid: 0db0
    DirBase: 3fff8820  ObjectTable: a2cb8f00  HandleCount: 171.
    Image: InstDrv.exe

// -- 修改PID --
1: kd> ed ffffffff`8ee32040+b4 0
```

## InheritedFromUniqueProcessId (+0x140)

| 偏移 | 字段 | 类型 |
| ---- | ---- | ---- |
| +0x140 | InheritedFromUniqueProcessId | Ptr32 Void |

父进程PID，记录创建当前进程的父进程标识。

**安全应用**
- 进程树分析：追踪进程创建链条
- 父进程伪装检测：恶意软件可能伪装成系统进程的子进程

---

## ImageFileName (+0x17c)
| 偏移 | 字段 | 类型 |
| ---- | ---- | ---- |
| +0x17c | ImageFileName | [15] UChar |

**进程映像文件名**，存储进程可执行文件的名称。

关键限制

- 缓冲区仅15字节
- 内核拷贝 `min(文件名长度+1, 15)` 字节
- 若文件名（含NULL）≤15字节，正常存储且有NULL结尾
- 若文件名（含NULL）>15字节，仅拷贝前15字节，无NULL结尾
- 不包含路径信息，仅有文件名

示例

```
notepad.exe        → "notepad.exe\0" （11字符+NULL，共12字节，正常）
verylongname.exe   → "verylongname.ex"（16字符>15，截断为前15字节，无NULL结尾）
LongFileName123.exe→ "LongFileName123"（19字符>15，截断为前15字节，无NULL结尾）
```

**注意**：读取ImageFileName时应始终限定最大长度为15，不能依赖NULL结尾。

安全应用
- 快速识别进程（但不可靠，因为可被修改）
- 进程伪装检测：恶意进程可能将此字段改为"svchost.exe"

---

## SeAuditProcessCreationInfo (+0x190)

| 偏移 | 字段 | 类型 |
| ---- | ---- | ---- |
| +0x190 | SeAuditProcessCreationInfo | SE_AUDIT_PROCESS_CREATION_INFO |

完整映像路径信息，用于安全审计。

**与ImageFileName的区别**

- 包含完整的文件路径
- 不受15字符限制

**获取完整路径的方式**

```c
// 通过SeAuditProcessCreationInfo获取
PUNICODE_STRING pImagePath = pEprocess->SeAuditProcessCreationInfo.ImageFileName;
```

---

# 进程链表字段

## ActiveProcessLinks (+0x0b8)

| 偏移 | 字段 | 类型 |
| ---- | ---- | ---- |
| +0x0b8 | ActiveProcessLinks | _LIST_ENTRY |

**全局活动进程双向链表**，这是Windows内核管理所有进程的核心数据结构。

**LIST_ENTRY结构**

```c
typedef struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink; // 指向下一个节点
    struct _LIST_ENTRY *Blink; // 指向上一个节点
} LIST_ENTRY;
```

**链表组织方式**

`PsActiveProcessHead`（全局链表头）
```
+----------+    +----------+    +----------+
| EPROCESS  |<-->| EPROCESS  |<-->| EPROCESS  |
| (进程A)   |    | (进程B)   |    | (进程C)   |
+----------+    +----------+    +----------+
```

**遍历进程的方法**

```c
PLIST_ENTRY pHead = PsActiveProcessHead;
PLIST_ENTRY pEntry = pHead->Flink;
while (pEntry != pHead) {
    PEPROCESS pEprocess = CONTAINING_RECORD(pEntry, EPROCESS, ActiveProcessLinks);
    // 处理进程...
    pEntry = pEntry->Flink;
}
```

**安全应用**
- **进程枚举**：遍历系统所有进程
- **进程隐藏**（DKOM）：通过断开链表节点隐藏进程
```c
// 断链隐藏（危险操作）
pTarget->ActiveProcessLinks.Flink->Blink = pTarget->ActiveProcessLinks.Blink;
pTarget->ActiveProcessLinks.Blink->Flink = pTarget->ActiveProcessLinks.Flink;
```

### 本次调试练习 p3

```bash
# SeAuditProcessCreationInfo 调试
+0x18c SecurityPort        : (null)
+0x190 SeAuditProcessCreationInfo : _SE_AUDIT_PROCESS_CREATION_INFO       # 点击链接

0: kd> dx ...
(*((ntkrpamp!_SE_AUDIT_PROCESS_CREATION_INFO *)0xa084eb90))
    [+0x000] ImageFileName            : 0x9ebcabe0 [Type: _OBJECT_NAME_INFORMATION *] # 点击ImageFileName

0: kd> dx -id 0,0,88e7b040 -r1 ((ntkrpamp!_OBJECT_NAME_INFORMATION *)0x9ebcabe0)
    [+0x000] Name                     : "\Device\HarddiskVolume1\Users\cc\Desktop\InstDrv.exe" [Type: _UNICODE_STRING] # 点击Name

0: kd> dx ...  # 获取到了最终位置路径
    [+0x004] Buffer                  : 0x9ebcabe8 : "\Device\HarddiskVolume1\Users\cc\Desktop\InstDrv.exe" [Type: wchar_t *]


# 链表调试
0: kd> dt _eprocess a084ea00
nt!_EPROCESS
+0x000 Pcb              : _KPROCESS
+0x0b0 ProcessLock      : _EX_PUSH_LOCK
+0x0b4 UniqueProcessId  : 0x000012a0 Void
+0x0b8 ActiveProcessLinks : _LIST_ENTRY [ 0xa850aab8 - 0x8ee320f8 ] # 从链表节点地址，-b8 获取 EPROCESS 基地址

0: kd> dt _eprocess 0xa850aab8-b8
nt!_EPROCESS
+0x000 Pcb              : _KPROCESS
+0x0b0 ProcessLock      : _EX_PUSH_LOCK
+0x0b4 UniqueProcessId  : 0x00001548 Void
+0x0b8 ActiveProcessLinks : _LIST_ENTRY [ 0x9ed140f8 - 0xa084eab8 ]   # 这是第一个

0: kd> dt _LIST_ENTRY a084ea00+b8
nt!_LIST_ENTRY
[ 0xa850aab8 - 0x8ee320f8 ]
+0x000 Flink            : 0xa850aab8 _LIST_ENTRY [ 0x9ed140f8 - 0xa084eab8 ]
+0x004 Blink            : 0x8ee320f8 _LIST_ENTRY [ 0xa084eab8 - 0x8ee1d0f8 ]

0: kd> dt 0xa850aab8 _LIST_ENTRY
nt!_LIST_ENTRY
[ 0x9ed140f8 - 0xa084eab8 ]
+0x000 Flink            : 0x9ed140f8 _LIST_ENTRY [ 0x8e453a38 - 0xa850aab8 ]
+0x004 Blink            : 0xa084eab8 _LIST_ENTRY [ 0xa850aab8 - 0x8ee320f8 ]

0: kd> dt 0x8ee320f8 _LIST_ENTRY
nt!_LIST_ENTRY
[ 0xa084eab8 - 0x8ee1d0f8 ]
+0x000 Flink            : 0xa084eab8 _LIST_ENTRY [ 0xa850aab8 - 0x8ee320f8 ]
+0x004 Blink            : 0x8ee1d0f8 _LIST_ENTRY [ 0x8ee320f8 - 0x8ee426b8 ]
```





## EPROCESS结构之ThreadListHead解析
**基础信息**

- 偏移：`+0x1a0`
- 字段：`ThreadListHead`
- 类型：`_LIST_ENTRY`

**字段作用**

该字段为**进程线程链表头**，用于链接归属该进程的所有线程。
每个进程至少包含1个线程，可通过该双向链表遍历进程下全部线程。

**线程遍历代码示例**

```c
PLIST_ENTRY pHead = &pEProcess->ThreadListHead;
PLIST_ENTRY pEntry = pHead->Flink;
while (pEntry != pHead) {
    PETHREAD pThread = CONTAINING_RECORD(pEntry, ETHREAD, ThreadListEntry);
    // 处理线程...
    pEntry = pEntry->Flink;
}
```

**安全应用场景**

1. 线程枚举和分析
2. 检测隐藏线程
3. 线程注入检测

### 本次调试练习 p4

```bash
0: kd> dt _kprocess
+0x010 ProfileListHead  : _LIST_ENTRY
+0x018 DirectoryTableBase : Uint4B
+0x01c LdtDescriptor    : _KGDTENTRY
+0x024 Int21Descriptor  : _KIDTENTRY
+0x02c ThreadListHead   : _LIST_ENTRY    // 重点

0: kd> dt _kthread
+0x000 Header           : _DISPATCHER_HEADER
+0x1c4 SuspendEvent     : _KEVENT
+0x1d4 ThreadListEntry  : _LIST_ENTRY

0: kd> dt _ethread
+0x3ac Win32StartAddress : Ptr32 Void
+0x3b0 LegacyPowerObject : Ptr32 Void
+0x3b4 ThreadListEntry  : LIST_ENTRY

+0x19c HighestUserAddress : 0x7fff0000 Void
+0x1a0 ThreadListHead   : _LIST_ENTRY [ 0x9ef3ee34 - 0x9ed873f4 ]

# -- 查看链表节点/Entry是节点  -- 
0: kd>dt _ethread 0x9ef3ee34-3b4
```
# 安全相关字段

## Protection (+0x2ee)

| 偏移   | 字段       | 类型             |
|--------|------------|------------------|
| +0x2ee | Protection | _PS_PROTECTION   |

进程保护级别，用于实现Protected Process (PP) 和 Protected Process Light (PPL)。

---

### PS_PROTECTION结构：
```c
typedef struct _PS_PROTECTION {
    union {
        UCHAR Level;
        struct {
            UCHAR Type  : 3;   // 保护类型
            UCHAR Audit : 1;   // 审计标志
            UCHAR Signer: 4;   // 签名者类型
        };
    };
} PS_PROTECTION;
```

## 保护类型（Type字段，3位）

| 值 | 枚举名                          | 含义                               |
|----|---------------------------------|------------------------------------|
| 0  | PsProtectedTypeNone             | 无保护                             |
| 1  | PsProtectedTypeProtectedLight   | Protected Process Light (PPL)      |
| 2  | PsProtectedTypeProtected        | Protected Process (PP)             |

---

### PS_PROTECTED_SIGNER（Signer字段，4位）

| 值 | 枚举名                          | 含义                               |
|----|---------------------------------|------------------------------------|
| 0  | PsProtectedSignerNone           | 无签名者                           |
| 1  | PsProtectedSignerAuthenticode   | Authenticode签名                   |
| 2  | PsProtectedSignerCodeGen        | 代码生成（.NET）                   |
| 3  | PsProtectedSignerAntimalware    | 反恶意软件（ELAM）                 |
| 4  | PsProtectedSignerLsa            | LSA（lsass.exe）                   |
| 5  | PsProtectedSignerWindows        | Windows系统组件                    |
| 6  | PsProtectedSignerWinTcb         | Windows可信计算基（最高级别）      |
| 7  | PsProtectedSignerWinSystem      | Windows系统（Win10+新增）          |

---

### 保护效果：
- 阻止未授权进程打开受保护进程的句柄
- 阻止内存读写、线程注入等操作
- 即使管理员权限也无法直接操作

### 本次调试练习 p5

```bash
0: kd> !process 0 0
PROCESS a084ea00 SessionId: 1 Cid: 12a0 Peb: 002ab000 ParentCid: 0db0
    DirBase: 3fff88e0 ObjectTable: aa4e1500 HandleCount: 442.
    Image: InstDrv.exe

PROCESS 8e453980 SessionId: 1 Cid: 1984 Peb: 002c3000 ParentCid: 1af8
    DirBase: 3fff89e0 ObjectTable: b00d2f00 HandleCount: 328.
    Image: cheatengine-i386.exe

0: kd> dt _eprocess a084ea00
+0x2ee Protection      : _PS_PROTECTION
+0x2ef HangCount      : 0y0000
+0x2ef GhostCount     : 0y0000

0: kd> dt _PS_PROTECTION
nt!_PS_PROTECTION
    +0x000 Level         : UChar
    +0x000 Type          : Pos 0, 3 Bits
    +0x000 Audit         : Pos 3, 1 Bit
    +0x000 Signer        : Pos 4, 4 Bits

0: kd> dx -id 0,0,88e7b040 -r1 (*((ntkrpamp!_PS_PROTECTION *)0xa084ecee))
(*((ntkrpamp!_PS_PROTECTION *)0xa084ecee)) [Type: _PS_PROTECTION]
    [+0x000] Level       : 0x0 [Type: unsigned char]
    [+0x000 ( 2: 0)] Type : 0x0 [Type: unsigned char]
    [+0x000 ( 3: 3)] Audit: 0x0 [Type: unsigned char]
    [+0x000 ( 7: 4)] Signer: 0x0 [Type: unsigned char]

# _PS_PROTECTION 修改为 0x62
0: kd> eb ffffffff`a084ecee 62
0: kd> dx -id 0,0,88e7b040 -r1 (*((ntkrpamp!_PS_PROTECTION *)0xa084ecee))
(*((ntkrpamp!_PS_PROTECTION *)0xa084ecee)) [Type: _PS_PROTECTION]
    [+0x000] Level       : 0x62 [Type: unsigned char]
    [+0x000 ( 2: 0)] Type : 0x2 [Type: unsigned char]
    [+0x000 ( 3: 3)] Audit: 0x0 [Type: unsigned char]
    [+0x000 ( 7: 4)] Signer: 0x6 [Type: unsigned char]
    
# 修改后 CE x64dbg, tasklist 无法打开/结束进程
```



0x62 位域拆分对照表
```
0 1 1 0 | 0     | 0 1 0
Signer  | audit | type
```



| 字段   | 占用位   | 二进制值 | 十进制值 | 对应枚举/含义                     |
|--------|----------|----------|----------|----------------------------------|
| Type   | 位0~2    | 010      | 2        | PsProtectedTypeProtected（PP 进程） |
| Audit  | 位3      | 0        | 0        | 无审计                           |
| Signer | 位4~7    | 0110     | 6        | PsProtectedSignerWinTcb（系统最高权限） |


# 对象管理字段

## ObjectTable (+0x15c)

| 偏移    | 字段名       | 类型                  |
|---------|--------------|-----------------------|
| +0x15c  | ObjectTable  | Ptr32 _HANDLE_TABLE   |

进程句柄表指针，指向该进程的私有句柄表。

句柄表的作用：
- 存储进程打开的所有内核对象句柄
- 句柄是用户态访问内核对象的凭证
- 每个进程有独立的句柄表，句柄值仅在本进程内有效

安全应用：
- 句柄枚举：遍历进程打开的所有对象
- 句柄劫持：复制或修改其他进程的句柄
- 句柄泄露检测：分析未关闭的句柄

## 本次调试练习 p6

```bash
0: kd> !process 0 0
PROCESS a843a040  SessionId: 1  Cid: 06c8  Peb: 002fc000  ParentCid: 0db0
    DirBase: 3fff81c0  ObjectTable: ab137540  HandleCount: 484.
    Image: InstDrv.exe

0: kd> dt _eprocess a843a040
+0x15c ObjectTable    : 0xab137540 _HANDLE_TABLE
+0x160 DebugPort      : (null)

0: kd> dt 0xab137540 _HANDLE_TABLE
+0x008 TableCode      : 0x8d200001  # Tablecode 低2位表示层级, 二进制, 共1/2/3级, dd 解析时需要去掉

0: kd> dd 0x8d200000
8d200000  8d236000 8d209000 00000000 00000000

0: kd> dq 8d236000
ReadVirtual: 8d236000 not properly sign extended
8d236000  00000000`00000000  f01f0003`978f0b09
8d236010  f8000001`8cc16af9  501f0003`8f3e4ea9
8d236060  70000003`90c36519  481f0003`9ea2ea29
8d236070  501f0003`9ee1fa99  8d236ca0`00000000

0: kd> dt 0xab137540 _HANDLE_TABLE
nt!_HANDLE_TABLE
    +0x00c QuotaProcess     : 0xa843a040 _EPROCESS
    +0x010 HandleTableList  : _LIST_ENTRY [ 0x821d5960 - 0xa2d9d390 ]

0: kd> dt a2d9d390-10 _HANDLE_TABLE
nt!_HANDLE_TABLE
    +0x00c QuotaProcess     : 0xa090ea00 _EPROCESS
    +0x010 HandleTableList  : _LIST_ENTRY [ 0xab137550 - 0xb48da450 ]
    +0x17c ImageFileName      : [15] "SearchFilterHo"
    +0x190 SeAuditProcessCreationInfo : _SE_AUDIT_PROCESS_CREATION_INFO
```

