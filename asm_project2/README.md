http://www.asmirvine.com/  - Getting Started with MASM and Visual Studio 2022

# 环境配置

右击项目 bulid Dependencies - Masm √ (如果已勾上可能因为有其他vs进程，全部关闭后再启动)
项目属性 - Linker - System - Subsystem - Console
项目属性 - Linker - System - Advanced - Entry Point: main
项目属性 - Linker - General - 附加库目录 - 添加 Irvine目录
    添加后才能 INCLUDE Irvine32.inc
3.右击Main.asm - 属性 - Item Type - Microsoft Macro Assembler (没有说明 bulid Dependencies - Masm 有问题，关闭所有vstudio, 重操作)

Install AsmDude(vs2019) https://marketplace.visualstudio.com/items?itemName=Henk-JanLebbink.AsmDude
Install AsmDude(vs2022) https://marketplace.visualstudio.com/items?itemName=Henk-JanLebbink.AsmDude2
