@echo off
echo TCP 客户端编译脚本
echo.
echo 请选择编译模式：
echo 1. 控制台版本（有窗口，显示调试信息）
echo 2. 后台版本（无窗口，静默运行）
echo.
set /p choice=请输入选择 (1 或 2): 

if "%choice%"=="1" goto console
if "%choice%"=="2" goto background
echo 无效选择，默认编译控制台版本
goto console

:console
echo.
echo 正在编译控制台版本...
:: 检查是否安装了 GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到 GCC 编译器
    echo 请安装 MinGW-w64 或其他 GCC 发行版
    echo 推荐下载地址：https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)
gcc -Wall -Wextra -O2 -s -DCONSOLE_MODE -o client_console.exe client.c -lws2_32
if %errorlevel% == 0 (
    echo 编译成功！生成了 client_console.exe （控制台版本）
    echo 此版本会显示调试信息和运行状态
) else (
    echo 编译失败
)
goto end

:background
echo.
echo 正在编译后台版本...
:: 检查是否安装了 GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo 错误：未找到 GCC 编译器
    echo 请安装 MinGW-w64 或其他 GCC 发行版
    echo 推荐下载地址：https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)
gcc -Wall -Wextra -O2 -s -mwindows -o client.exe client.c -lws2_32
if %errorlevel% == 0 (
    echo 编译成功！生成了 client.exe （后台版本）
    echo 此版本运行时不会显示窗口，适合后台运行
    echo.
    echo 文件大小：
    dir client.exe | findstr client.exe
    echo.
    echo 使用方法：
    echo client.exe -i 服务器IP -p 端口号
    echo 例如：client.exe -i 101.201.56.60 -p 8090
    echo.
    echo 注意：后台版本运行时无窗口，需要通过任务管理器查看或结束进程
) else (
    echo 编译失败，请检查代码和编译环境
)

:end
echo.
pause