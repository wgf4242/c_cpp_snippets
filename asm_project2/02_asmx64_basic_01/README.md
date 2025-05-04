[x64内联汇编——VS2019](https://blog.csdn.net/Zhang_Y_Q/article/details/136433131)

```
命令行：ml64 /Fo $(IntDir)%(fileName).obj /c %(fileName).asm
输出：$(IntDir)%(fileName).obj
引入外部函数(c)：EXTERN_C DWORD myAdd(DWORD u1, DWORD u2);
引入外部函数(asm)：EXTERN myAddOne:PROC
```