@echo off
echo TCP �ͻ��˱���ű�
echo.
echo ��ѡ�����ģʽ��
echo 1. ����̨�汾���д��ڣ���ʾ������Ϣ��
echo 2. ��̨�汾���޴��ڣ���Ĭ���У�
echo.
set /p choice=������ѡ�� (1 �� 2): 

if "%choice%"=="1" goto console
if "%choice%"=="2" goto background
echo ��Чѡ��Ĭ�ϱ������̨�汾
goto console

:console
echo.
echo ���ڱ������̨�汾...
:: ����Ƿ�װ�� GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ����δ�ҵ� GCC ������
    echo �밲װ MinGW-w64 ������ GCC ���а�
    echo �Ƽ����ص�ַ��https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)
gcc -Wall -Wextra -O2 -s -DCONSOLE_MODE -o client_console.exe client.c -lws2_32
if %errorlevel% == 0 (
    echo ����ɹ��������� client_console.exe ������̨�汾��
    echo �˰汾����ʾ������Ϣ������״̬
) else (
    echo ����ʧ��
)
goto end

:background
echo.
echo ���ڱ����̨�汾...
:: ����Ƿ�װ�� GCC
gcc --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ����δ�ҵ� GCC ������
    echo �밲װ MinGW-w64 ������ GCC ���а�
    echo �Ƽ����ص�ַ��https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)
gcc -Wall -Wextra -O2 -s -mwindows -o client.exe client.c -lws2_32
if %errorlevel% == 0 (
    echo ����ɹ��������� client.exe ����̨�汾��
    echo �˰汾����ʱ������ʾ���ڣ��ʺϺ�̨����
    echo.
    echo �ļ���С��
    dir client.exe | findstr client.exe
    echo.
    echo ʹ�÷�����
    echo client.exe -i ������IP -p �˿ں�
    echo ���磺client.exe -i 101.201.56.60 -p 8090
    echo.
    echo ע�⣺��̨�汾����ʱ�޴��ڣ���Ҫͨ������������鿴���������
) else (
    echo ����ʧ�ܣ��������ͱ��뻷��
)

:end
echo.
pause