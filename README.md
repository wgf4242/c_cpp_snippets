# 基础学习

[隐藏的细节：编译与链接](https://www.bilibili.com/video/BV1TN4y1375q)
[底层】动态链接库(dll)是如何工作的？](https://www.bilibili.com/video/BV1vB4y1V7gR)
地址引用的使用 见 scripts/Crypto_tea.c
[环境 | 【C&C++】VSCode 配置使用 MSVC 编译链接 C/C++程序](https://www.bilibili.com/video/BV11G411P7sM)

## 视频学习

- lnnks B 站 + https://ke.qq.com/course/5623715
- [rkvir 逆向工程学院](https://space.bilibili.com/447734880/video)
- [KKB 新职课 C++开发工程师 V4 ](https://www.ruike1.com/thread-59675-1-1.html)
- [C++ Linux 服务器开发高级架构师课程](https://www.ruike1.com/thread-52601-1-1.html)
- [火哥 Windows 内核课程（上+下)](https://www.ruike1.com/thread-54920-1-1.html)
- [rkvir 逆向工程学院](https://space.bilibili.com/447734880)

# C 学习

## 标准

C 开始追求的是自由、信任，相信程序员可以写好代码。

|          | ANSI C   |          | ISO C99     | ISO C11       |
| -------- | -------- | -------- | ----------- | ------------- |
| auto     | enum     | short    | inline      | Alignas       |
| break    | extern   | signed   | restrict    | Alignof       |
| case     | float    | sizeof   | Bool        | Atomic        |
| char     | for      | static   | \_Complex   | Generic       |
| const    | goto     | struct   | \_Imaginary | Noreturn      |
| continue | if       | switch   |             | Static_assert |
| default  | int      | typedef  |             | Thread_local  |
| do       | lone     | union    |             |               |
| double   | register | unsigned |             |               |
| else     | return   | void     |             |               |
| volatile | while    |          |             |               |

| C++ 语言标准历程 |      |                        |
| ---------------- | ---- | ---------------------- |
| ISO C++ 98       | 1998 | Vc++ 6.0 BorLand C++   |
| ISO C++ 03       | 2003 | VisuaL Studio C++ 2010 |
| ISO C++ 11       | 2011 | Visual Studio C++ 2012 |
| ISO C++ 14 :     | 2014 | Visual Studio C++ 2015 |
| ISO C++ 17       | 2017 | Visual Studio C++ 2019 |

自然数数据类型表
| 类型名称 | 内存占用 | 取值范围(十进制) | 取值范围(十六进制) |
| ---------------------- | -------- | ---------------------------- | -------------------- |
| unsigned char | 1 Byte | 0-255 | 0-0xFF |
| unsigned short | 2 Byte | 0-65535 | 0-0xFFFF |
| unsigned int | 4 Byte | 0-4294967295 | 0-0xFFFFFFFF |
| unsigned | 4 byte | 0-4294967295 | 0-0xFFFFFFFF |
| unsigned long | 4 Byte | 8-4294967295 | 0-0xFFFFFFFF |
| unsigned long long | 8 Byte | 0-18,446,744,073,709,551,615 | 0-0xFFFFFFFFFFFFFFFF |
| unsigned long long int | 8 Byte | 0-18,446,744,073,709,551.615 | 0-0xFFFFFFFFFFFFFFFF |

有符号数据类型表

```
在16位机中unsigned int 等同于unsigned short
在部分64位编译器中unsigned 1ong等同于unsigned long 1ong
源于C语言标准:
unsigned short 占用储存空间不能大于unsigned int
unsigned 1ong 占用空间不能小于unsigned int
```

| 类型名称      | 内存占用 | 取值范围(十进制)                                            | 取值范围(十六进制)  |
| ------------- | -------- | ----------------------------------------------------------- | ------------------- |
| \_BOOL        | 1 Byte   | 0,1                                                         |                     |
| char          | 1 Byte   | -128-127                                                    | 0-0xFF              |
| short         | 2 Byte   | -32768-32761                                                | 0-0xFFFF            |
| int           | 4 Byte   | -2,147,483,648-2147483647                                   | 0-0XFFFFFFFF        |
| signed        | 4 byte   | -2,147,483,648-2147483647                                   | 0-0xFFFFFFFF        |
| long          | 4 Byte   | -2,147,483,648-2147483647                                   | 0-0xFFFFFFFF        |
| long long     | 8 Byte   | -9,223,372,036,854,775,808-9,223,372,036,854,775,807        | 0-0xFFFFFFFFFFFFFFF |
| long long int | 8 Byte   | -9, 223, 372, 036,854,775, 808-9, 223, 372,036,854, 775,807 | 0-0xFFFFFFFFFFFFFFF |

```
在16位机中 int 等同于 short
在部分64位编译器中 long 等同于 long long
源于C语言标准:
short 占用储存空间不能大于 int
long 占用空间不能小于 int
```

```c
char*  s="1234"; // 不可修改数据
char[] s="1234"; // 可修改数据
```

### float

https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)FloatingPoint.html

### 类型转换

表达式中类型转换规则
[1] char short 会升级为 int 有些时候会升级为 unsigned int
[2] 两种类型及以上的运算,会升级为最高级的类型
[3] 赋值运算会造成,类型升级或者类型降级

| 类型等级表         |                                     |
| ------------------ | ----------------------------------- |
| 类型名称           | 类型名称 sizeof(int) = sizoef(long) |
| long double        | long double                         |
| double             | double                              |
| float              | float                               |
| unsigned long long | unsigned long long                  |
| long long          | long long                           |
| unsigned long      | unsigned long                       |
| long               | unsigned int                        |
| unsigned int       | long                                |
| int                | int                                 |

[1] 高等级整数转换为低等级整数时,超出的二进制位会丢弃,可以用%快速进行计算
Example:
int x=-2;
char v = x; 相等于 v=x%256; 256 来自 char 数据类型 8bit 2 的八次方

[2]低等级类型负数转换为高等级整数,会通过补 1 保留负数的属性
[3]将整数转换成一个浮点数,如果超出浮点数的范围,行为是未定义的.
[4]将浮点数转为整数会丢弃小数部分,如果超出整数的保存范围,行为是未定义的.

### printf

https://cplusplus.com/reference/cstdio/printf/

| _length_ | d i           | u o x X                | f F e E g G a A | c      | s         | p      | n               |
| :------- | :------------ | :--------------------- | :-------------- | :----- | :-------- | :----- | :-------------- |
| _(none)_ | int           | unsigned int           | double          | int    | char\*    | void\* | int\*           |
| hh       | signed char   | unsigned char          |                 |        |           |        | signed char\*   |
| h        | short int     | unsigned short int     |                 |        |           |        | short int\*     |
| l        | long int      | unsigned long int      |                 | wint_t | wchar_t\* |        | long int\*      |
| ll       | long long int | unsigned long long int |                 |        |           |        | long long int\* |
| j        | intmax_t      | uintmax_t              |                 |        |           |        | intmax_t\*      |
| z        | size_t        | size_t                 |                 |        |           |        | size_t\*        |
| t        | ptrdiff_t     | ptrdiff_t              |                 |        |           |        | ptrdiff_t\*     |
| L        |               |                        | long double     |        |           |        |                 |

printf 函数转换说明

| 转换说明 | 输出                                                                    |
| -------- | ----------------------------------------------------------------------- |
| %d       | 有符号十进制整数 int                                                    |
| %        | 有符号十进制整数 int                                                    |
| %u       | 无符号十进制整数 unsigned                                               |
| %0       | 无符号八进制整数 unsigned                                               |
| %x       | 无符号十六进制数 ff (小写) unsigned                                     |
| %X       | 无符号十六进制数 FF (大写) unsigned                                     |
| %f       | 浮点数,十进制计数法 double                                              |
| 8        | 浮点数,科学计数法 le5 double                                            |
| %E       | 浮点数,科学计数法 1E5 double                                            |
| %g       | 根据值自动选择%f 和%e , %e 格式用于指数小于-4 或者大于等于精度时 double |
| %G       | 根据值自动选择%f 和%E , %E 格式用于指数小于-4 或者大于等于精度时 double |
| %C       | 单个字符                                                                |
| %p       | 指针                                                                    |
| %5       | 字符串                                                                  |
| %a       | 浮点数十六进制数 double                                                 |
| %A       | 浮点数十六进制数 double                                                 |

printf 函数转换说明修饰符

| 修饰符  | 输出                                                        |
| ------- | ----------------------------------------------------------- |
| h       | 配合整数类型一起使用 %hd short、unsigned short %hu 、       |
| hh      | 配合整数类型一起使用 singed char %hd、unsigned char %hhu    |
| l       | 配合整数类型一起使用 %ld long %lu unsigned long             |
| ll(C99) | 配合整数类型一起使用 %lld long long %llu unsigned long long |
| L       | 配合浮点是数类型使用 %Lf long double %Le                    |
| z(C99)  | 配合整数类型一起使用,表达 sizeof 的结果 sizet 类型%zd       |
| t(C99)  | 配合整数类型一起使用,表示指针值的差, ptrdiff_t 类型         |
| j       | 配合整数类型使用,表达 intmax_t uintmax_t 类型的值           |

| 修饰符 | 输出                                                                                                                                             |
| ------ | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| 数字   | 最小字段宽度%4d                                                                                                                                  |
| .数字  | 精度 <br />对于%e %E %f 表示小数部分的位数,<br />对于%g 和%G 表示有效数字最大位数 <br />对于%s,表示字符最大数量<br />对于整数,表示数字的最小位数 |
| -      | 字符对齐模式改为左对齐                                                                                                                           |
| +      | 显示数字的符号                                                                                                                                   |
| 空格   | 当值为正数时 符号位显示空格                                                                                                                      |
| #      | 对于%o 添加 0 对于%x 添加 0x 对于%X 添加 0X 对于浮点数添加小数。                                                                                 |
| 0      | 用 0 来填充字符串,对于整数如果指定了精度或者-标记 则忽略该标记                                                                                   |

### scanf

scanf 函数转换说明

| 转换说明        | 输出                      |
| --------------- | ------------------------- |
| %d %i           | 有符号十进制整数 int      |
| %c              | 字符 char                 |
| %s              | 字符串                    |
| %o              | 有符号八进制整数 int      |
| %p              | 内存地址                  |
| %u              | 无符号十进制整数 unsigned |
| %x %X           | 有符号十六进制整数        |
| %e %f %g a(C99) | 浮点数 float              |
| %E %F %G A(C99) | 浮点数 float              |

scanf 函数修饰说明

| 修饰符  | 输出                                                                                          |
| ------- | --------------------------------------------------------------------------------------------- |
| 数字    | 最大字符宽度%2d                                                                               |
| h       | 配合整数类型一起使用 %hd short、 %hu unsigned short                                           |
| hh      | 配合整数类型一起使用 signed char %hhd、unsigned char %hhu                                     |
| l       | 配合整数类型一起使用%ld long %lu unsigned long 配合浮点数类型一起使用%lf %le 表示 double 类型 |
| ll(C99) | 配合整数类型一起使用 %lld long long %llu unsigned long long                                   |
| L       | 合浮点是数类型使用 %Lf long double %Le                                                        |
| z(C99)  | 配合整数类型一起使用,表达 sizeof 的结果 size_t 类型 %zd                                       |
| t(C99)  | 配合整数类型一起使用,表示指针值的差, ptrdiff_t 类型                                           |
| j       | 配合整数类型使用,表达 intmax_t uintmax_t 类型的值                                             |

### xor

任意数 x 异或 其类型(无符号) 最大值 x ^ 255 = ~x
~x ^ x = 255
x ^ x = 0
x ^ 0 = x

## Visio Studio2022 安装

- √ C++ 桌面开发
- √ 适用于最新 v143 生成工具的 C++ MFC

### 环境与设置

**新建项目** 选中解决方案:添加-新建项目。
一个解决方案里可能有多个项目。右击项目，设为启动项目。

**打包发布**
集成库: 右击项目-属性-C/C++ - 代码生成 - 运行库：多线程/MT，MT 模式下是把库集成了。

**配置选项**
项目属性:
C 语言标准： 旧 msvc = C99
平台工具集： 相当于库文件。旧的兼容好点
选项 - 环境 -导入导出配置 配置文件位置

**添加依赖** ：右击项目 - 生成依赖项 - 项目依赖项
**导出模板** ：菜单栏 - 项目- 导出模板

**生成调试信息** : 配置属性 - 链接器 - 调试

### 编译器与错误

编译错误: C 开头, 实际是使用 cl.exe 编译
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Tools\MSVC\14.29.30133\bin\Hostx64\x86\cl.exe

```s
main.c(5,2): error C2143: 语法错误: 缺少“;”(在“return”的前面)
```

链接错误 LNK 表示, 实际是用 link.exe 链接 这时.obj 已经生成

```s
// #include <stdio.h>
main.obj : error LNK2001: 无法解析的外部符号 _printf
```

## 变量

**数据类型关键字**

| Classic C | C90    | C99         |
| --------- | ------ | ----------- |
| char      | signed | Bool        |
| short     | void   | \_Complex   |
| int       |        | \_Imaginary |
| unsigned  |        |             |
| long t    |        |             |
| loat      |        |             |

**标识符定义规则**

- 可以采用大写字母、小写字母、数字、(下划线)命名一个标识符,但是不能使用数字作为第一个字符.
- 不能和其他标识符重名.
- 不能和关键字以及保留标识符重名.
- 不要超过编译器支持的最大标识符长度(63)［C90 为 6 个字符］.
- 外部标识符长度不要超过(31).
- 标识符是大小写敏感的,比如 Age 和 age 是不同的标识符.

命名: i*,m*,o* 或 Input*,Modify\_,Output
**标识符定义的其他建议**

- 标识符应该能够直观的表达标识符的意义,提高程序的可读性
- 不推荐使用＿(下划线或者双下划线)开头命名标识符.

// 0LL, 0U, 0UL, 3.14, 0.0F, 0.0L
// 小数一般识别为 double

**特殊值**
nan 见 sec_app1.c, nan > 1 == false, nan < 1 == false

## 调试

调试 - 窗口 - 反汇编。 查看汇编代码，和源代码。

[Linux C/C++ 调试的那些“歪门邪道”](https://mp.weixin.qq.com/s/Rkrm2rpCVsVVsmUGzkn65A)

## 插入汇编

```c
// 花指令， emit插入机器码 e9是jmp
    __asm {
        jz label
        jnz label
        _emit 0xe9
        label:
    }
```

# C++项目推荐

10 日 c++实战狂练
https://light-city.club/sc/practical_exercises/10_day_practice/10_day/
一、一个项目就能入门 C++：
https://github.com/Light-City/CPlusPlusThings
二、C++实现的算法合集：C-Plus-Plus
https://github.com/TheAlgorithms/C-Plus-Plus
三、进阶指南：CppTemplateTutorial
https://github.com/wuye9036/CppTemplateTutorial
一、写一个小型 STL 库：MyTinySTL
https://github.com/Alinshans/MyTinySTL
二、小实战—俄罗斯广块：Tinytetris
https://github.com/taylorconor/tinytetris
三、学习下大佬们的代码，做个计算器：calculator
https://github.com/microsoft/calculator
四、TinyWebServer（3.6k+ star）
https://github.com/qinguoyi/TinyWebServer
以上所有资源的百度网盘地址：
链接: https://pan.baidu.com/s/11t9DU2faWzzc7YmveKjLWg 提取码: gggn
如果地址失效，可以加 qijianShow，备注 322，我会发你最新链接

## 单引号与双引号

https://blog.csdn.net/xiebs/article/details/93466116
单引号 -> ascii 码
双引号 -> 字符串->内存地址

## `char*` 与 char[]区别

```c
char ch1[] = "hello world";//字符数组, 大小不可变, 可修改 ch1[i]=1;

//指针 2种赋值
char * ch3; // 1
  ch3 = "hello world";//字符指针, 大小可变
char * ch3 = "hello world";// 2 字符指针, 大小可变
char * ch3; // 3
  ch3[0] = 'a';
  ch3[1] = 'b';
char *ch3 = malloc(sizeof(char) * 10); // 4
  ch3[0] = 'A';

char s[] = "Some String"; // 5
  char *ch3 = s;
  ch3[1] = 'v';

strcpy(ch3, ch1);
printf("%s\n", ch1); // 这里不会执行的，上面出错了


```

## puts/putchar/printf

**puts(s)**
`s`可以是字符数组名或字符串常量。输出时遇到`'\0'`自动将其转换为`'\n'`，即输出字符串后换行。
puts()函数有返回值，如果输出成功，则返回换行符号`'\n'`，否则返回`EOF`（End Of File）。

**putchar(x)**
输出单个字符，x 可以是一个字符常量、一个数组元素或一个整型数字（将输出其值所对应的编码符号，以 ASCII 码为例，当整型变量 ch 超出 8 位变量的范围时，ch 则会变强制转化为 8 位变量（即取其低八位传过去输出），当为负数的时候，由于计算机存储负数是用补码表示的，所以传过去的二进制补码也被当做正数处理，也是取其低八位）。

**printf("%s"，s)**
s 可以是字符数组名或字符串常量。输出时遇到'\0'结束。

## 调用约定

### thiscall

```asm
push ebx             ; 4Bytes
push eax             ; 4Bytes
mov ecx,edi          ; thiscall, 类的指针放到ecx,  ecx代表的是对象
call sword2ui.41FD40 ;
...
ret 8                ; 平栈 8/4=2可知2个参数
```
## CMake

```text
# https://cmake.org/cmake/help/latest/command/set_target_properties.html
set_target_properties(nosymbol PROPERTIES OUTPUT_NAME "hello")
set_target_properties(nosymbol PROPERTIES LINK_FLAGS -s)               # strip 去符号

set_target_properties(new_thing PROPERTIES PREFIX "")                  # 文件名前缀 new_thing是小工程名
set_target_properties(new_thing PROPERTIES OUTPUT_NAME "better_name")  # 文件名
set_target_properties(new_thing PROPERTIES SUFFIX ".so.1")             # 文件名后缀

# ollvm
set(CMAKE_CXX_FLAGS "-s -mllvm -bcf ")
```

**exclude**

```
// https://stackoverflow.com/questions/24491129/excluding-directory-somewhere-in-file-structure-from-cmake-sourcefile-list

set (EXCLUDE_DIR "/hide/")
file (GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c")
foreach (TMP_PATH ${SOURCE_FILES})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM SOURCE_FILES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

// https://cmake.org/pipermail/cmake/2007-August/015837.html
FILE(GLOB_RECURSE files "*.c")
FOREACH(item ${files})
  IF(${item} MATCHES "foo/main.c")
    LIST(REMOVE_ITEM files ${item})
  ENDIF(${item} MATCHES "foo/main.c")
ENDFOREACH(item)
MESSAGE(STATUS "${files}")
```

# Windows API

[【NTAPI】Windows 未公开 API 介绍——可以快速的关机 API](https://www.bilibili.com/video/BV1MP4y1f7Eg)
[03:25【NTAPI】Windows 未公开 API 介绍——可以“自动消失”的消息框 API](https://www.bilibili.com/video/BV1QT41157tt)
[06:54【NTAPI】Windows 未公开 API 介绍——可以“假冒”系统进程的 API](https://www.bilibili.com/video/BV1DZ4y1q7zG)
[06:38【NTAPI】Windows 未公开 API 介绍——可以制造蓝屏的 API](https://www.bilibili.com/video/BV1734y1Y7fN)

# lnnks Lessions

## C 语言

### 按位取反运算

```c
unsigned char x;
~x + x = char最大值 // 和自己的取反数相加=最大值
~x + x = 255

// 求负算法
sx = 255 - x + 1
sx = ~x + x -x + 1 = ~x + 1
原码:x  补码:~x + 1 , 汇编指令为neg
```

## 3.7 游戏内存写入/调试 火炬之光 2

在 Windows 操作系统中,每个进程都有独立的内存空间,x86 架构下,这个内存空间为 4Gb,这个
是虚拟内存,通过驱动层的映射管理,虚拟内存会映射到物理内存中.

![](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/20220901231555.jpg)

先找到 float 型的 HP 地址，右击 什么访问了内存地址。

![img](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/wps2.jpg)

x32dbg 打开，Alt+A 附加到火炬之光，Ctrl+G 跳到 50a200，下断点

![img](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/wps7.jpg)

用到 ecx, ret 后，向上找 ecx。发现用到 eax

![](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/wps8.jpg)

![](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/image-20220901230458550.png)

eax 来自这个 call 的返回值。进入 call

![img](https://gitee.com/wgf4242/vue3start/raw/vite2tmp/imgs/wps6.jpg)

调用了基址为 27699D0

即指针为 27699D0 -> 2c -> 558 为 HP 地址。

## CE 搜索

Openprocess 找不到进程。可能是 hook 了。ce 或者在驱动层处理了。

打开没问题，搜索不到 0，可能是驱动层破坏了读写函数 readmemory, writememory.

搜索正常但找不到数据。1.数据类型错了。2.数据加密了。

网游修改 hp 没变化： 阻断 ClientHP = ServerHP 这个操作。拔网线。

## 如何查找坐标。

找到人物的基址的后，在浏览相关内存区域。适用于加密坐标。

1.关联查找法 2.通过显示，调用函数，找到显示之前的加密解密过程。但是成本太高。用关联查找法比较适合。

## 网游数据的查找：

对于持续自动回复，可能修改没有效果。等回复满之后再进行修改。
有的游戏这时会不发送回复数据包，修改才有效果。国内有些写的不行持续发回血包会引起没效果。这时拔线来修改。

掉线怎么办。--- 把掉线干掉。

## 干掉双开/多开保护

启动 main
入口站： x64dbg - 模块 - 右击程序 - 在反汇编窗口中找到入口点

C3 - ret
55 - push ebp

x64dbg, 右击 - 补丁 - 恢复选择项

示例剑侠情缘 2, 右击属性 - 兼容性 XP SP3, 简化的颜色模式 16 位色。 启动参数添加 -window 进行窗口化。

思路 1： main 的所有 call 下断点。看是哪些执行，哪里退出。跟入关键 call
思路 2： 游戏启动是死循环，找到位置。

```asm
0042BE12 | FF15 24514300              | call dword ptr ds:[<&_GetModuleHandl | 这里检测
0042BE18 | 50                         | push eax                             | eax:"MZ?"
0042BE19 | E8 62D4FDFF                | call sword2.409280                   | 退出
0042BE1E | 8945 A0                    | mov dword ptr ss:[ebp-60],eax        |
0042BE21 | 50                         | push eax                             | eax:"MZ?"
0042BE22 | E8 69060000                | call sword2.42C490                   |
```

```asm
00409322 | 68 709F4300                | push sword2.439F70                   | 439F70:"Sword2 Window"
00409327 | 68 609F4300                | push sword2.439F60                   | 439F60:"Sword2 Class"
0040932C | FF15 44514300              | call dword ptr ds:[<&_FindWindowA@8> | if (FindWindowA("Sword2 Class", "Sword2 Window"))
00409332 | 85C0                       | test eax,eax                         |
00409334 | 74 07                      | je sword2.40933D                     | 关键比较
00409336 | 68 D09F4300                | push sword2.439FD0                   | 439FD0:"Program is still running"
0040933B | EB 54                      | jmp sword2.409391                    |
0040933D | 8B7424 14                  | mov esi,dword ptr ss:[esp+14]        | [esp+14]:"MZ?"
00409341 | 56                         | push esi                             | esi:"MZ?"
```

## 游戏安全\_全屏秒杀如何实现 , 练习找数据有能力

lesson3.10

血量变化
造成伤害时，HP = HP - Damage
情况 1. 被攻击后 判断 < 0, 死亡。
情况 2. 有线程循环检测 <0

测试 1 ，HP 改成-200。

杀死方法 1.造成伤害，触发判断， 伤害来源，攻击目标，伤害值
怪物保存: 1. 列表-数组(性能高, 不灵活) 2. 链表(插入方便)

通过逆向分析，找到线索。

造成伤害，右击 HP 地址 - 找出什么写入了地址。 1.回复血的地址（回血直接出现） 2.被攻击地址 B（被攻击后出现）
sub [esi+10], edi
edi 是伤害, esi:人物对象指针, esi+10 是 HP。把 esi 换成怪物指针。变成怪物掉血

x32dbg 附加到 B 地址，到函数顶部。这个函数是攻击或被攻击。

调用约定。函数作用。函数参数。函数返回值。

- 传参时：栈不平衡。解决 1.调用者平栈 2.自己平栈

```
push ebx             ; 4Bytes
push edx             ; 4Bytes
mov ecx,edi          ; thiscall, 类的指针放到ecx,  ecx代表的是对象
                     ; ecx=4cef08, 人物4cef18， 所以是人物调用的。被打的call, onAttacked()
call sword2ui.41FD40 ;
...
ret 8                ; 平栈 8/4=2可知2个参数
```

调用这个函数就能模拟这个过程。

怎样找怪物列表？ 1.鼠标移到人身上触发。
逻辑 1.1 鼠标地址 xy 1.2 xy 和怪物的 xy 比较 1.3 有重叠关系触发 要依次比较每个怪物。 2.游戏里人在走 坐标在变。坐标怎样改变 依次找到每个怪物，随机做出走的动作。

## 干掉启动弹窗/软件安全

启动时提示插入光盘。
Ctrl+G: MessageBoxA, 返回 ret 处下断。返回后向上找。

软件设计的安全和平衡性问题：
返回值和参数。

启动检测函数只测 1 点 return true, false 在安全上不好。
要和启动初始化做到一起比较安全。

True 和 true 区别
true 1 bool 1 字节
false 0 bool 1 字节

TRUE 1 4 字节 自定义类型
FALSE 0 4 字节

软件、游戏可动态分析，病毒不适合动态分析。
sub esp,2c 分配栈空间 2C/4=11
https://docs.microsoft.com/en-us/windows/win32/debug/debugging-functions

## 游戏穿墙/游戏安全

1.找坐标 2.找写入地址 3.前方穿墙判断 ，怎样确定一个 大致范围？。A 点为判断之上。B 点没墙可触发的点。缩小 AB 范围。
在 X 处停下。Ctrl+F9, F7, 在上一行 call 下断点。如果 A 把 B 跳过去了。可疑。 4.穿墙信息作用：通过穿墙信息可以复制出地图信息。

![](https://s2.loli.net/2022/09/09/HRyonTc8J5Q6iP2.jpg)

1.swtich 语法, 在 41ebc9 地址，esi==2 走 0 停。 2.找出改写了地址。撞墙。找到 2 个。 3.跟进找到一段 ecx+80 有关。硬件断点-写入。 看视频吧有点长：游戏安全\_中文字符串长度怎么求 游戏穿墙 4.最后找到 and eax,0xf0, 保留高位 改为 0x00 不保留，成功。

## 游戏保护/数据加密

修改赋值运算。重载操作符。 见 游戏保护\_数据加密。

## 游戏安全/变速齿轮

修改 windows 提供的 GetTickCount 函数
x64dbg, Attach 程序。
Ctrl+G -> GetTickCount
然后将 retn 改成

```
add eax,eax   ; 2倍速
retn


shl eax,2     ; 4倍速
retn
```

## CE Hook_Demo

工具 - 添加内存, 申请到了 900000 地址。 1.在修改 HP 的地方 JMP 900000.  
2.在 900000 处写 HOOK 汇编。

| Instruction | opCode         | Asm                   |
| ----------- | -------------- | --------------------- |
| 00900000    | 81 FEO8EFCF 04 | cmp esi,04CFEF08      |
| 00900006    | 7502           | jne 990000A           |
| 00900008    | 31FF           | xor edi.edi           |
| 0090000A    | 297E10         | sub [esi+10] , edi    |
| 0090000D    | 8B4610         | mov eax, [esi+10]     |
| 00900010    | E9A3FDB1FF     | jmp Sword2Ul.exe+1FDB |

## 游戏安全\_HOOK_CRC32 检测致命弱点

CRC32 检测 1.检测时会读取内存。
2.CE 检测是什么访问了这个地址。 3.最后可能有一个比较, 干掉即可

CRC 检测升级：
方法 1.多套几层 CRC32
方法 2.新建进程检测
方法 3.每次操作后换一块内存，擦除之前的内存

# CS 结构客户端过验证

万能注入-找内存位置 1.比如 sql 注入输入 or。 然后用 CE 查找 类型选字符串: or, (搜不到可能是加密了) 2.全部添加, 取一半修改为 o1r

x64dbg 附加进程,
由于是有日志写到文件的，WriteFile, WriteFileA 下断点。
g WriteFile
g WriteFileA
F2 断，运行，触发，看堆栈, 分析。
取消 Writefile 断点, Ctrl+F9, F8 执行到返回去上层找,
关键 je 前面就是比较算法或者过滤。进入 call

1.关键字符串（and select or) 2.我们输入的字符串(老板号 or '1'=1)

正则或者 find 过滤，匹配后一定有一个 if (1) xxxx. findstr 找不到返回-1
向上跳可能是 while

# 游戏安全

3D 游戏坐标转换
GAMES101: 现代计算机图形学入门 https://sites.cs.ucsb.edu/~lingqi/teaching/games101.html
前 4 章 基础。MVP 矩阵

## 游戏安全/Articles

[CE OD 结合运用 断点找寻游戏地址 ](https://bbs.kanxue.com/thread-177440.htm)

# Videos

[从零开始游戏逆向反外挂辅助开发 c++公开课天龙魔兽 lxl](https://www.bilibili.com/video/BV1z14y1h7wi/)

# Articles

[C 语言实现 SM4 加解密算法](https://blog.csdn.net/weixin_45582916/article/details/121429713)
[C 语言实现 RC4 加解密算法](https://blog.csdn.net/weixin_45582916/article/details/121429688)
[C 语言实现 DES 加解密算法](https://blog.csdn.net/weixin_45582916/article/details/121429594)
[C 语言实现 AES 加解密算法](https://blog.csdn.net/weixin_45582916/article/details/121429445)
[C 语言实现 TEA 系列加解密算法](https://blog.csdn.net/weixin_45582916/article/details/121425780)
[Snippets](https://github.com/woodruffw/snippets/blob/4fcc1e0/mersenne/mersenne.c)

[教你编写年轻人的第一个动态链接库 比 HelloWorld 简单](https://www.bilibili.com/video/BV1MF411w7Z9)

[Http Get 请求简单实例（C++）](https://mp.weixin.qq.com/s/SMiMScCpgTAEvhBzSQ8h0g)

[[原创]通过 DLL 注入魔改植物大战僵尸(2)——僵尸篇](https://bbs.pediy.com/thread-264406.htm)
[[原创]通过 DLL 注入魔改植物大战僵尸(1)——准备工作](https://bbs.pediy.com/thread-264356.htm)

[C++多线程开发之互斥锁](https://mp.weixin.qq.com/s/ldDPha366xUCXfn_SUshWg)
[C/C++内存泄漏-原因、避免以及定位](https://mp.weixin.qq.com/s/hXRdYtOncTgtSm8C4EICJg)
[每天学点 C++之共享数据](https://mp.weixin.qq.com/s/mvzcFMkvgNmpkRQZI8GWWQ)
[C++第三方开发库 libcurl](https://mp.weixin.qq.com/s/u7HMfXUifR76Aiw5rJNb7g)
[Linux 下 C/C++ 多线程 SSH 扫描与暴力攻击](https://mp.weixin.qq.com/s/QjKzIVs1FL0Iidwj0xW_PA)

## 基础

[C++ 提高篇 : struct 和 class 区别](https://mp.weixin.qq.com/s/LCAyOc0V22pXY0T0xK6JqQ)
[C++提高篇：深拷贝与浅拷贝](https://mp.weixin.qq.com/s/MNuBdltrhdxgFasD990ksQ)
[跟我学 c++中级篇——省略号的巧妙应用](https://mp.weixin.qq.com/s/8x5NRfq6F5yIaHfAf0lGVQ)
[每天学点 C++之条件竞争](https://mp.weixin.qq.com/s/HYBMfsei965gzMKmxsXtuQ)
[每天学点 C++之限时等待](https://mp.weixin.qq.com/s/toPz6SI4A_RHtmise7bzOQ)
[C++提高篇：类的初始化列表](https://mp.weixin.qq.com/s/eMVlwroTBsG7-j0oUPWDww)


## QT

[Qt 教程-公众号](https://mp.weixin.qq.com/s/PjMXKhW-7VO_w4r0tM19TQ)

## ASM 汇编

[Udemy 高分付费课程（中英字幕）从零开始学习 x86 汇编语言编程 Assembly Language - 构建超过 50 个汇编程序](https://www.bilibili.com/video/BV1XS4y1p7hw)
https://docs.microsoft.com/zh-cn/cpp/assembler/inline/defining-asm-blocks-as-c-macros?view=msvc-170

## 调试器

[从零开始编写简易调试器](https://mp.weixin.qq.com/s/ah29tzVT2B_4mx5wxSNlzA)

## Package

* 命令行 | CLI11 或 cxxopts、Boost.Program_options、
## Book

深度探索 C++对象模型
STL 源码剖析

## 操作系统

- 内存管理机制
- 文件管理机制
- 设备管理机制
- 进程线程管理机制
