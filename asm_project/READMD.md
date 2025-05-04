## App List
15_ArrayElementsAccess: 11.1. Coding  Iterating through Array Elements

## 2.2. Coding   Simple Assembly  program / 快速入门
注意:cpp和asm文件文件名不要相同

1.右击项目 - Build Dependencies - Build Customizations - √ masm
2.新建Main.asm
3.右击Main.asm - 属性 - Item Type - Microsoft Macro Assembler
4.填写代码
5.工具栏处 Debug - 修改为 x86
6.右击项目 - 属性 - Linker - Advaned - Entry Point - start,   平台修改为 Win32(x86) (如果写x64要用x64语法)
;; 如果 用main.asm 并定义了 main PROC也许不用 设置 Entry Point 见03_Simple
Build时要注意选的是x64还是x86

调试窗口
Debug - Windows - Memory - Memory 1 
Debug - Windows - Disassembly

## 2.3. Installing a Syntax Highlighter

https://github.com/Trass3r/AsmHighlighter

## 4.3. Number Systems 16进制转2进制
![](https://s2.loli.net/2022/09/17/fHFvuL1ND4GxCjI.jpg)

# The Programmer's Model

## 5.5. Coding  One Register to Rule Them All - project 02_BackwardCompat
* 按2.2操作， 最后上方发布修改为 x64, 项目设置里也修改为x64
![](https://s2.loli.net/2022/09/18/OMr2z6CdwNke7Bs.jpg)

编译时会提示: 

```
1>LINK : error LNK2001: 无法解析的外部符号 mainCRTStartup
```

* 入口点: 5.右击项目 - 属性 - Linker - Advaned - Entry Point - main

## 5.6. Overview of the x86 Flags

Flag States

| 1    | Set         |
| ---- | ----------- |
| 0    | Reset/Clear |

### Status Flag / Visual Stdio Flags

Reflect outcome of arithmetic and logical operations performed by the CPU.

| Flags                | Description                                                  |
| -------------------- | ------------------------------------------------------------ |
| Overflow(OF)         | Set when the result of an __signed arithmetic__ operation is too large to<br />fit into the destination |
| Sign(SF)             | 0正 1负, Set when the result of an arithmetic or logical operation is **neagtive** |
| Zero(ZF)             | Set when the result of an arithmetic or logical operation is **zero** |
| Carry(CF)            | Set when the result of an **unsigned arithmetic** operation is too large to<br />fit into the destination |
| Parity(PF)           | Set if the **least-significant bytes** in the result contains an **even number** |
| Auxiliary Caarry(AC) | Set when an arithmetic operation causes a **carry** from **bit 3 to bit4 in an 8-bit operhand** |


| 标志位 | VS    | VS    |
| ------ | ----- | ----- |
| OF     | OV(1) | NV(0) |
| DF     | DN(1) | UP(0) |
| IF     | EI(1) | DI(0) |
| SF     | NG(1) | PL(0) |
| ZF     | ZR(1) | NZ(0) |
| AF     | AC(1) | NA(0) |
| PF     | PE(1) | PO(0) |
| CF     | CY(1) | NC(0) |

## 5.7. Overview of the Floating Point Unit / XMM Registers

SimD - Single Instruction/Multiple Data
MM只是Intel的商标-没意思。

MM0-XMM7总共8个128位的寄存器

FPU Data Register Stack 栈顶ST0-ST7

48 - bit Pointer Registers
* FPU Instruction Pointer
* FPU Data Pointer

16 - bit Control Register
*  Tag Register
*  Control Register
*  Status Register

通常不能直接操作异步，C/C++编译器提供了库函数指定一个回调函数，在FPU异常时调用回调访问16位值。


![](https://s2.loli.net/2022/09/18/EieMsQU6Lbp3VYf.jpg)


## 15.2. The SSE Execution Environment

![](https://s2.loli.net/2022/10/24/M3po68ZmN5CkRPQ.jpg)


# FAQ

## constant expected  E:\masm32\include\winextra.inc	11052	

https://blog.csdn.net/weixin_50836014/article/details/124873981


## LNK2017	没有 /LARGEADDRESSAWARE:NO，"ADDR32"到"enc"的重定位无效

链接器 -> 系统 -> 启用大地址 -> 选择否(/LARGEADDRESSAWARE:NO)
