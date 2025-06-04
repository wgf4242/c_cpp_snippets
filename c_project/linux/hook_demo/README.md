# Linux Hook技术实现示例

本项目根据文章 [常用的Linux Hooking技术总结](https://mp.weixin.qq.com/s/vEFLiGJl21eTxXRhbwA6zA) 实现了多种Linux Hook技术。

## 项目结构

```
.
├── hook_example.c           # 基本钩子函数实现
├── function_pointer_hook.c   # 函数指针封装hook
├── ld_preload_hook.c        # LD_PRELOAD动态链接库劫持
├── test_program.c           # 测试程序(配合LD_PRELOAD使用)
├── gcc_attribute_hook.c     # GCC特定语法hook
├── advanced_hook.c          # 高级hook库(多函数hook)
├── demo_program.c           # 演示程序
├── Makefile                 # 编译脚本
└── README.md               # 说明文档
```

## Hook技术说明

### 1. 钩子函数 (hook_example.c)

在程序中预定义好的钩子，在需要的时候，将hook函数挂接或者注册到钩子里。

**特点:**
- 程序内部预设hook指针
- 运行时动态挂接hook函数
- 可以在函数执行前、后或中间进行拦截

### 2. 函数指针封装 (function_pointer_hook.c)

通过函数指针重新定向函数调用。

**特点:**
- 简单直接的hook方式
- 编译时确定hook目标
- 适用于已知函数的hook

### 3. 动态链接库劫持 (ld_preload_hook.c)

使用LD_PRELOAD环境变量优先加载自定义的动态库，覆盖系统库中的同名函数。

**特点:**
- 无需修改目标程序
- 可以hook系统库函数
- 运行时动态注入

**优先级:** LD_PRELOAD > LD_LIBRARY_PATH > /etc/ld.so.cache > /lib > /usr/lib

### 4. GCC特定语法 (gcc_attribute_hook.c)

使用GCC的`__attribute__`语法实现库加载时的自动初始化。

**特点:**
- `__attribute__((constructor))` - 库加载时执行
- `__attribute__((destructor))` - 库卸载时执行
- 先于main函数执行

### 5. 高级Hook库 (advanced_hook.c)

实现多个函数的同时hook，包括malloc、free、printf等。

**特点:**
- 同时hook多个函数
- 使用RTLD_NEXT获取原函数
- 完整的库初始化和清理

## 编译和使用

### 编译所有示例

```bash
make all
```

### 运行测试

```bash
make test
```

### 单独编译

```bash
# 编译基本hook示例
make hook_example

# 编译LD_PRELOAD库
make libmyhook.so

# 编译高级hook库
make libadvancedhook.so
```

### 使用LD_PRELOAD

```bash
# 使用strcmp hook
LD_PRELOAD=./libmyhook.so ./test_program test

# 使用高级hook库
LD_PRELOAD=./libadvancedhook.so ./demo_program
```

## 使用示例

### 1. 基本钩子函数

```bash
./hook_example
```

输出:
```
NoHook: test
Hook:   test
```

### 2. LD_PRELOAD Hook

```bash
LD_PRELOAD=./libmyhook.so ./test_program hello
```

输出:
```
oops!!! hack function invoked. s1=<hello> s2=<test>
Incorrect password
```

### 3. 高级Hook库

```bash
LD_PRELOAD=./libadvancedhook.so ./demo_program
```

输出:
```
Advanced hook library loaded
[HOOKED] === Hook Demo Program ===
[HOOK] malloc(100) = 0x...
[HOOK] malloc(200) = 0x...
...
```

## 注意事项

1. **Linux环境**: LD_PRELOAD技术主要适用于Linux系统
2. **权限**: 某些hook可能需要特定权限
3. **调试**: 可以使用`LD_DEBUG=all`查看库加载过程
4. **安全**: Hook技术可能被安全软件检测为恶意行为

## 调试技巧

### 查看库加载过程

```bash
LD_DEBUG=all ./your_program 2>&1 | grep symbol
```

### 查看函数调用

```bash
strace -e trace=openat ./your_program
```

### 查看动态链接

```bash
ldd ./your_program
```

## 清理

```bash
make clean
```

## 参考资料

- [常用的Linux Hooking技术总结](https://mp.weixin.qq.com/s/vEFLiGJl21eTxXRhbwA6zA)
- GNU C Library文档
- GCC属性语法文档
- Linux动态链接器文档