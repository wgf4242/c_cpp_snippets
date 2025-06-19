@echo off
echo 正在编译 C 客户端...
echo.

:: 检查是否安装了 GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到 GCC 编译器
    echo 请安装 MinGW-w64 或其他 GCC 发行版
    echo 推荐下载地址：https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)

:: 编译程序
gcc -Wall -Wextra -O2 -s -o client.exe client.c -lws2_32
upx -9 client.exe

if %errorlevel% == 0 (
    echo 编译成功！生成了 client.exe
    echo.
    echo 文件大小：
    dir client.exe | findstr client.exe
    echo.
    echo 使用方法：
    echo client.exe -i 服务器IP -p 端口号
    echo 例如：client.exe -i 101.201.56.60 -p 8090
    echo.
    echo 查看帮助：client.exe -h
) else (
    echo 编译失败，请检查代码和编译环境
)

echo.
pause