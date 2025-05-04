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
