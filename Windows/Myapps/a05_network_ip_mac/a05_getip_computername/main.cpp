#define _WINSOCK_DEPRECATED_NO_WARNINGS
// 或在项目属性 - C/C++ - 预处理器，预处理器定义 添加_WINSOCK_DEPRECATED_NO_WARNINGS
//https ://blog.csdn.net/morningstar929/article/details/101024153/
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
#include <iphlpapi.h>
#pragma comment(lib,"Iphlpapi.lib")
#include <Windows.h>

int main()
{
    int wVersionRequested = MAKEWORD(2, 2);
    WSADATA lpWSAData;
    WSAStartup(wVersionRequested, &lpWSAData);
    //获取主机名
    char szHostName[128];
    if (gethostname(szHostName, 128) == 0)
    {
        std::cout << "本地计算机名称是：" << szHostName << std::endl;
    }
    //获取内网IP地址
    struct hostent* pHost;
    pHost = gethostbyname(szHostName);
    for (size_t i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
    {
        std::cout << "内网IP地址是：" << inet_ntoa(*(struct in_addr*)pHost->h_addr_list[i]) << std::endl;
    }

    WSACleanup();
    system("pause");
    return 0;
}