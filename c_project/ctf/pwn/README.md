
设置好缓冲区防止输出问题
```c
setvbuf(stdout, 0, 2, 0);
setvbuf(stdin, 0, 1, 0);
setvbuf(stderr, 0, 2, 0);
```
[出题 pwn SCTF2023 SycLang出题思路](https://ywhkkx.github.io/2023/06/21/SycLang出题思路/)
[出题 pwn SCTF2023Compiler出题思路](https://ywhkkx.github.io/2023/06/21/Compiler%E5%87%BA%E9%A2%98%E6%80%9D%E8%B7%AF/)
[CAT_DE出题思路](https://ywhkkx.github.io/2023/06/11/CAT_DE%E5%87%BA%E9%A2%98%E6%80%9D%E8%B7%AF/)
[SMC的实现方法](https://www.cnblogs.com/Here-is-SG/p/17153081.html)
[分享C++ PWN 出题经历——深入研究异常处理机制](https://mp.weixin.qq.com/s/8f1FUxD3pSOa-wxpYwiceA)