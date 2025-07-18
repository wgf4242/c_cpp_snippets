# 编译
## curl编译
Developer Command Prompt for VS 2022 启动命令行
nmake /f Makefile.vc mode=static VC=14 debug=no RTLIBCFG=static ENABLE_IDN=no
nmake /f Makefile.vc mode=static VC=14 RTLIBCFG=static ENABLE_IDN=no

# Cmake

```
# 去除未使用的函数
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wunused-function")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-function")

# 设置CMake的构建类型为Release
set(CMAKE_BUILD_TYPE "Release")

## 设置编译器标志
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

## 设置为32位
set(CMAKE_C_COMPILER "D:/mingw32/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/mingw32/bin/g++.exe")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")




## 添加lz4库 未验证
link_directories(D:/mingw/lib) # 如果库不在默认搜索路径中，需指定目录
target_link_libraries(printDemo "D:\\mingw\\lib\\libstdc++exp.a")
target_link_libraries(printDemo lz4) # 假设库名为 lz4
```

# Make
./configure --prefix=/home/kali/Downloads/yafu/ecm_bin # 安装目录

```sh
LIBS += -L../msieve
LIBS += -lmsieve -ldl
# 即等于, -L指定查找路径 -l指定库
LIBS += -L../msieve -lmsieve -ldl

# INC加.h, LIBS加库
INC += -I../gmp_install/gmp-6.2.0/include
LIBS += -L../gmp_install/gmp-6.2.0/lib

```
Makefile.patch 使用 patch 命令生成 Makefile

**指定LIB目录的方式, 可用以下几种**

1. 用libtool，and specify the full pathname of the library
2. use the '-LLIBDIR' 配合下面
   - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the 'LD_RUN_PATH' environment variable
     during linking
   - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to '/etc/ld.so.conf'
   /bin/bash ./libtool   --mode=install /usr/bin/install -c ecm '/usr/local/bin' 
   libtool: install: /usr/bin/install -c ecm /usr/local/bin/ecm


# CMake
[使用CMake编译程序](https://mp.weixin.qq.com/s/rhFscfiSPq5SkSV-aEiT2g)
[Visual Studio 功能增强：CMake 目标视图](https://mp.weixin.qq.com/s/iNMX4vqwE3F_gVWZnKgLbA)
[CMake 中库文件的管理](https://mp.weixin.qq.com/s/n_rPdaqPeckW9iO_KyQ5rg)
[CMake:检测环境](https://mp.weixin.qq.com/s/OMSe7xkCgPEtm09Db8_YwQ)
[CMake最最最核心用法](https://mp.weixin.qq.com/s/uR78kMs6z38FzHRCIjgHeA)
[CMake入门教程 | 基础语法，静态库与动态库的制作和使用以及CMake流程控制](https://mp.weixin.qq.com/s/O90prTpwlIRQv8Tew3RMVw)
[CMake:利用CTest进行单元测试](https://mp.weixin.qq.com/s/OfC2CvAUFGMrTIh9FrR2XA)
[CMake 中多模块的管理](https://mp.weixin.qq.com/s/xPwWF0DVC3hqYZRR8MxWEA)
[一个简单的CMake入门之旅](https://mp.weixin.qq.com/s/nJcTKrjxF7je7Xy0oIfZ5g)
[GCC、CMake、CMakelist、Make、Makefile、Ninja啥关系？一图讲透！](https://mp.weixin.qq.com/s/a9iKuVEl6_TFrhbpjTejGw)
[CMake 备忘清单](https://mp.weixin.qq.com/s/N6mbeCOVC8q3QTwdVAZHdw)
[CMake:使用控制流](https://mp.weixin.qq.com/s/30twsD_3t3QUj-ge6AqJOg
[CMake:检测python解释器和python库](https://mp.weixin.qq.com/s/trL7AlZl7FgMoIBRzN_Fkw
[CMake:设置语言标准(三)](https://mp.weixin.qq.com/s/H7kLF4d_iQ2wkTFGlbI2vg
[CMake 指定程序构建类型](https://mp.weixin.qq.com/s/JOi6WA_uclvmdeTF2qjVXg)(9月28日)
[CMake 中流程控制与函数](https://mp.weixin.qq.com/s/T-mt9Mrh9BKny5wBeC3Htg)
[小白也可以玩转CMake之常用必备](https://mp.weixin.qq.com/s/pWbiS_fvbhrrJxSBXD6Mfw)
[CMake:检测外部库---使用pkg-config](https://mp.weixin.qq.com/s/sUCrI7P3tvHDYoAnPEXzLg)
[CMake:检测外部库---自定义find模块](https://mp.weixin.qq.com/s/37XSY6BwIblf4HFVkGcVQA)
[CMake 中构建和使用库文件](https://mp.weixin.qq.com/s/vFZERkhNeEILogoFE-FN5w)
[CMake:测试的其他补充（重要）](https://mp.weixin.qq.com/s/Zf3LpI5ZDqpNewhA3lVMpw)
[CMake: 检测Python模块和包](https://mp.weixin.qq.com/s/0gOYGsXx_ZGtisUK5eyvng)
[CMake:配置时运行自定义命令](https://mp.weixin.qq.com/s/PjqU8q9tkWYSgYu-Aglpfg)
[CMake：构建时为特定目标运行自定义命令](https://mp.weixin.qq.com/s/8YgyARRUYAy3K9A426HJhg)
[CMake: 配置时生成源码](https://mp.weixin.qq.com/s/Lv8FMN9WHdcWDNIUF5D4Wg)

## Makefile
[Makefile基础入门一：从编译小白到自动化构建达人](https://mp.weixin.qq.com/s/f4zbG0D5Sk6XtWLOjIg90A)
[Makefile学习笔记二：Makefile函数精讲，让构建系统更智能的10个技巧](https://mp.weixin.qq.com/s/0p2fLXyZyZxY7eCrgx9h5g)
[一些通用的Makefile文件模板](https://mp.weixin.qq.com/s/jKoGezTJKFbIw7Efiea2ww)
[从版本1到版本5如何编写牛逼的Makefile](https://mp.weixin.qq.com/s/a9vg0r7wRA84947CRl5beg)

## NMake

```sh
# Detour 编译
nmake /f Makefile
```

# FAQ

##　编译时依赖库怎样能打包到程序里呢

1. 静态链接　使用 -static 选项
gcc -o myprogram myprogram.c -static
2.  指定静态库
gcc -o myprogram myprogram.c -L/path/to/static/libraries -lmylib -static
https://tongyi.aliyun.com/qianwen/?sessionId=b1155bce89cd459ea6f65a0a06820f01
3. 设置 LD_LIBRARY_PATH：为了让程序知道去哪里找这些库文件，可以设置 LD_LIBRARY_PATH 环境变量。例如：
export LD_LIBRARY_PATH=/path/to/your/libraries:$LD_LIBRARY_PATH
4. 使用 rpath 或 runpath：在编译时，可以通过 -Wl,-rpath, 选项指定一个或多个搜索路径，使得程序在运行时能够找到库文件。例如：
gcc -o myprogram myprogram.c -L/path/to/your/libraries -lmylib -Wl,-rpath,/path/to/your/libraries
