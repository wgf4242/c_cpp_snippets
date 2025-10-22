[[极简 Windows 驱动程序，C语言编写，了解驱动程序代码原理](https://mp.weixin.qq.com/s/JnglDCTIiLWw7dq2WPNq2A)](https://mp.weixin.qq.com/s/JnglDCTIiLWw7dq2WPNq2A)

1.有关依赖项的安装指南：

https://learn.microsoft.com/zh-cn/windows-hardware/drivers/download-the-wdk

2.dbgprint函数介绍:

https://learn.microsoft.com/zh-cn/windows-hardware/drivers/ddi/wdm/nf-wdm-dbgprint

3.代码详细解释如下：


| 行号 | 代码                                    | 注释与解释                                                   |
| ---- | --------------------------------------- | ------------------------------------------------------------ |
| 1    | [#define](javascript:;) _AMD64_         | 宏定义： 定义 _AMD64_ 宏，用于指示代码将针对 AMD64/x64 架构（即 64 位 Windows 系统）进行编译。这确保了编译工具链使用正确的头文件和库。 |
| 2    | [#include](javascript:;) <wdm.h>        | 头文件包含： 包含了 <wdm.h> 文件。WDM 是 Windows Driver Model（Windows 驱动程序模型）的缩写。这个头文件包含了所有编写 Windows 内核模式驱动程序所需的核心数据类型、函数原型和宏定义（例如 NTSTATUS、DriverEntry 和 STATUS_SUCCESS）。 |
| 3    | NTSTATUS DriverEntry(void* a, void* b){ | 驱动程序入口点函数： 这是 Windows 加载和初始化驱动程序时调用的第一个函数，类似于应用程序中的 main 函数。 |
| 3.1  | NTSTATUS                                | 返回值类型： 表示函数执行状态。驱动程序入口点必须返回一个状态码，表明初始化是否成功。 |
| 3.2  | DriverEntry                             | 函数名： 驱动程序的标准入口函数名称。                        |
| 3.3  | (void* a, void* b)                      | 参数： 驱动程序入口点通常接收两个参数，类型为 PDRIVER_OBJECT（驱动程序对象）和 PUNICODE_STRING（注册表路径字符串），但在此代码中被简化为通用的 void* a 和 void* b，表示不使用该参数。 |
| 5    | DbgPrint("Hello from Nirs Driver!");    | 调试输出： 调用 DbgPrint 函数，将字符串输出到内核调试器或调试日志 中。这行代码的目的是在驱动程序加载成功时，提供一个确认信息。 |
| 6    | return STATUS_SUCCESS;                  | 返回成功状态： 返回预定义的宏 STATUS_SUCCESS。这告诉 Windows 操作系统，驱动程序的初始化操作已成功完成，系统可以继续加载驱动程序。 |
| 7    | }                                       | DriverEntry 函数体的结束。                                   |