sudo apt -y install gcc-multilib # 32位支持

[常用的Linux Hooking技术总结](https://mp.weixin.qq.com/s/AmOw6JQtkP7XXrisYtHq1Q)
[快速了解操作系统的文件系统设计](https://mp.weixin.qq.com/s/OOjhVuNLJr_r1jzVJRocXA)

[C++中如何调用.so共享库？](https://mp.weixin.qq.com/s/9viH3pGI_mpBXYPQhjJ0Iw)
[跟我学C++中级篇——Linux常见的异步编程方式](https://mp.weixin.qq.com/s/3WMJFHUSGFNOUe4U7YONRg)

## 编译为汇编

.s是汇编文件, 通过汇编生成可执行文件
```
gcc -S main.c # 会生成 main.s
gcc -c ./main.s -o main.o
```

## 编译/Link/gcc/

[C++编译优化之—so 动态库依赖](https://mp.weixin.qq.com/s/m7oVgk_lbtAAgwmH9zfvdA)
[Debug | 新手linux c++调试最佳利器--visual studio](https://zhuanlan.zhihu.com/p/27370373697)

```sh
# 在gcc编译时指定输出字符集，例如使用-fexec-charset=GBK选项。
gcc -m16 -march=i386 -o example example.c # 16位编译
gcc -m32 main.c       # 32位编译 "D:\mingw32\bin\gcc.exe"
gcc -fpie -pie main.c # 开启pie
gcc -Os -o a          # 编译优化
gcc -Os -ffunction-sections -fdata-sections -s -Wl,--gc-sections setkey.c
gcc -Os -ffunction-sections -fdata-sections -s setkey.c
gcc main.c -lm        # 连接数学库
gcc -o tcptunnel tcptunnel.o -lws2_32 # 链接 Winsock2 库。

gcc -fno-pie -no-pie main.c -o main
gcc -o test test.c // 默认情况下，不开启Canary保护
gcc -fno-stack-protector -o test test.c //禁用栈保护
gcc -fstack-protector -o test test.c //启用堆栈保护，不过只为局部变量中含有 char 数组的函数插入保护代码
gcc -fstack-protector-all -o test test.c //启用堆栈保护，为所有函数插入保护代码

# win 下编译输出 GBK编码
gcc -finput-charset=GBK -fexec-charset=GBK testadd.c -o main.exe
```

链接参数 LDFLAGS: -Wl,-Map=object.map,--cref,--gc-section

| Params                 | Desc                                                                                                |
| ---------------------- | --------------------------------------------------------------------------------------------------- |
| -g                     | 添加调试信息                                                                                        |
| -m32                   | 32 位编译                                                                                           |
| -m64                   | 64 位编译                                                                                           |
| -mx32                  | 将 int，long 和指针设为 32 位，适用于 X86-64                                                        |
| -static                | 静态链接, 打包所有函数, 在 Visualstudio 中 /MT, /MTD 在 配置属性 - C/C++ - 代码生成 - 运行库 中设置 |
| -s                     | strip 去符号 https://stackoverflow.com/questions/38675403/how-to-config-cmake-for-strip-file        |
|                        | 或直接 strip main.exe 来缩小体积                                                                    |
| -c                     | 编译对象(无 main)<br> gcc es3.c -c <br>gcc es3.o main.c -o es3 (编译 main 时包含 es3 对象)          |
| ---- PWN ---           |
| ---- PWN_NX(DEP) ---   |                                                                                                     |
| -z execstack           | 禁用 NX 保护                                                                                        |
| -z noexecstack         | 开启 NX 保护(默认) 堆栈禁止执行                                                                     |
| -                      |
| ---- PWN_RELRO ---     | GOT 写保护                                                                                          |
| -z norelro             | 关闭                                                                                                |
| -z lazy                | 部分开启, 默认                                                                                      |
| -z now                 | 全部开启                                                                                            |
| ---- PWN_PIE(ASLR) --- |                                                                                                     |
| -no-pie                | 关闭 PIE, 地址不随机                                                                                |
| -fpie -pie             | 开启 PIE，此时强度为 1                                                                              |
| -fPIE -pie             | 开启 PIE，此时为最高强度 2 代码段、数据段地址随机化                                                 |
| ---- PWN_CANARY ---    |                                                                                                     |
| -fno-stack-protector   | 禁用                                                                                                |
| -fstack-protector      | 开启                                                                                                |
| -fstack-protector-all  | 完全开启 堆栈溢出哨兵                                                                               |
| ---- PWN_FORTIFY ---   |                                                                                                     |
| -D_FORTIFY_SOURCE=1    | 较弱的检查                                                                                          |
| -D_FORTIFY_SOURCE=2    | 较强的检查 常用函数加强检查                                                                         |

最后上 upx 减小体积

pwn 参数总结

| PWN    | flag                                                            | Desc                       |
| ------ | --------------------------------------------------------------- | -------------------------- |
| NX     | -z execstack / -z noexecstack                                   | 关闭 / 开启                |
| Canary | -fno-stack-protector /-fstack-protector / -fstack-protector-all | 关闭 / 开启 / 全开启       |
| PIE    | -no-pie / -pie                                                  | 关闭 / 开启                |
| RELRO  | -z norelro / -z lazy / -z now                                   | 关闭 / 部分开启 / 完全开启 |


# FAQ

编译共享库 -shared时失败 `gcc -shared -o "libalg.so"  ./sort.o`
1. relocation `R_X86_64_PC32 against undefined symbol`
Q. -fPIC

## no such instruction: 'endbr64'

```
sudo apt-get remove binutils
sudo apt-get remove --auto-remove binutils
sudo apt install build-essential
```


# Article
[从零开始学习gcc基础内容之flag](https://mp.weixin.qq.com/s/eLIkD3-rrdB2TVGs7WijzQ)
[elf文件之不依赖标准库](https://mp.weixin.qq.com/s/Fn_IAT4KmRu7x4Fnldm71A)
[c++应用网络编程之十二Linux下的epoll模式分析](https://mp.weixin.qq.com/s/24WJG-pHO8ADSOwy0bulMw)

# Debug
[Linux程序调试工具指南](https://mp.weixin.qq.com/s/-0hddM9dynSPo8QmhZJDEQ)
