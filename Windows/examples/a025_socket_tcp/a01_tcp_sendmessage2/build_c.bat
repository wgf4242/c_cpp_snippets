@echo off
echo ���ڱ��� C �ͻ���...
echo.

:: ����Ƿ�װ�� GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ����δ�ҵ� GCC ������
    echo �밲װ MinGW-w64 ������ GCC ���а�
    echo �Ƽ����ص�ַ��https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)

:: �������
gcc -Wall -Wextra -O2 -s -o client.exe client.c -lws2_32
upx -9 client.exe

if %errorlevel% == 0 (
    echo ����ɹ��������� client.exe
    echo.
    echo �ļ���С��
    dir client.exe | findstr client.exe
    echo.
    echo ʹ�÷�����
    echo client.exe -i ������IP -p �˿ں�
    echo ���磺client.exe -i 101.201.56.60 -p 8090
    echo.
    echo �鿴������client.exe -h
) else (
    echo ����ʧ�ܣ��������ͱ��뻷��
)

echo.
pause